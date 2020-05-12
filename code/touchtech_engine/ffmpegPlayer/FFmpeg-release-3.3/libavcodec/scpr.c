﻿/*
 * ScreenPressor decoder
 *
 * Copyright (c) 2017 Paul B Mahol
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avcodec.h"
#include "bytestream.h"
#include "internal.h"

#define TOP  0x01000000
#define BOT    0x010000

typedef struct RangeCoder {
    unsigned   code;
    unsigned   range;
    unsigned   code1;
} RangeCoder;

typedef struct PixelModel {
    unsigned    freq[256];
    unsigned    lookup[16];
    unsigned    total_freq;
} PixelModel;

typedef struct SCPRContext {
    AVFrame        *last_frame;
    AVFrame        *current_frame;
    GetByteContext  gb;
    RangeCoder      rc;
    PixelModel      pixel_model[3][4096];
    unsigned        op_model[6][7];
    unsigned        run_model[6][257];
    unsigned        range_model[257];
    unsigned        count_model[257];
    unsigned        fill_model[6];
    unsigned        sxy_model[4][17];
    unsigned        mv_model[2][513];
    unsigned        nbx, nby;
    unsigned        nbcount;
    unsigned       *blocks;
    unsigned        cbits;
    int             cxshift;

    int           (*get_freq)(RangeCoder *rc, unsigned total_freq, unsigned *freq);
    int           (*decode)(GetByteContext *gb, RangeCoder *rc, unsigned cumFreq, unsigned freq, unsigned total_freq);
} SCPRContext;

static void init_rangecoder(RangeCoder *rc, GetByteContext *gb)
{
    rc->code1 = 0;
    rc->range = 0xFFFFFFFFU;
    rc->code  = bytestream2_get_be32(gb);
}

static void reinit_tables(SCPRContext *s)
{
    int comp, i, j;

    for (comp = 0; comp < 3; comp++) {
        for (j = 0; j < 4096; j++) {
            if (s->pixel_model[comp][j].total_freq != 256) {
                for (i = 0; i < 256; i++)
                    s->pixel_model[comp][j].freq[i] = 1;
                for (i = 0; i < 16; i++)
                    s->pixel_model[comp][j].lookup[i] = 16;
                s->pixel_model[comp][j].total_freq = 256;
            }
        }
    }

    for (j = 0; j < 6; j++) {
        unsigned *p = s->run_model[j];
        for (i = 0; i < 256; i++)
            p[i] = 1;
        p[256] = 256;
    }

    for (j = 0; j < 6; j++) {
        unsigned *op = s->op_model[j];
        for (i = 0; i < 6; i++)
            op[i] = 1;
        op[6] = 6;
    }

    for (i = 0; i < 256; i++) {
        s->range_model[i] = 1;
        s->count_model[i] = 1;
    }
    s->range_model[256] = 256;
    s->count_model[256] = 256;

    for (i = 0; i < 5; i++) {
        s->fill_model[i] = 1;
    }
    s->fill_model[5] = 5;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 16; i++) {
            s->sxy_model[j][i] = 1;
        }
        s->sxy_model[j][16] = 16;
    }

    for (i = 0; i < 512; i++) {
        s->mv_model[0][i] = 1;
        s->mv_model[1][i] = 1;
    }
    s->mv_model[0][512] = 512;
    s->mv_model[1][512] = 512;
}

static int decode(GetByteContext *gb, RangeCoder *rc, unsigned cumFreq, unsigned freq, unsigned total_freq)
{
    rc->code -= cumFreq * rc->range;
    rc->range *= freq;

    while (rc->range < TOP && bytestream2_get_bytes_left(gb) > 0) {
        unsigned byte = bytestream2_get_byte(gb);
        rc->code = (rc->code << 8) | byte;
        rc->range <<= 8;
    }

    return 0;
}

static int get_freq(RangeCoder *rc, unsigned total_freq, unsigned *freq)
{
    if (total_freq == 0)
        return AVERROR_INVALIDDATA;

    rc->range = rc->range / total_freq;

    if (rc->range == 0)
        return AVERROR_INVALIDDATA;

    *freq = rc->code / rc->range;

    return 0;
}

static int decode0(GetByteContext *gb, RangeCoder *rc, unsigned cumFreq, unsigned freq, unsigned total_freq)
{
    int t;

    if (total_freq == 0)
        return AVERROR_INVALIDDATA;

    t = rc->range * (uint64_t)cumFreq / total_freq;

    rc->code1 += t + 1;
    rc->range = rc->range * (uint64_t)(freq + cumFreq) / total_freq - (t + 1);

    while (rc->range < TOP && bytestream2_get_bytes_left(gb) > 0) {
        unsigned byte = bytestream2_get_byte(gb);
        rc->code = (rc->code << 8) | byte;
        rc->code1 <<= 8;
        rc->range <<= 8;
    }

    return 0;
}

static int get_freq0(RangeCoder *rc, unsigned total_freq, unsigned *freq)
{
    if (rc->range == 0)
        return AVERROR_INVALIDDATA;

    *freq = total_freq * (uint64_t)(rc->code - rc->code1) / rc->range;

    return 0;
}

static int decode_value(SCPRContext *s, unsigned *cnt, unsigned maxc, unsigned step, unsigned *rval)
{
    GetByteContext *gb = &s->gb;
    RangeCoder *rc = &s->rc;
    unsigned totfr = cnt[maxc];
    unsigned value;
    unsigned c = 0, cumfr = 0, cnt_c = 0;
    int i, ret;

    if ((ret = s->get_freq(rc, totfr, &value)) < 0)
        return ret;

    while (c < maxc) {
        cnt_c = cnt[c];
        if (value >= cumfr + cnt_c)
            cumfr += cnt_c;
        else
            break;
        c++;
    }
    if ((ret = s->decode(gb, rc, cumfr, cnt_c, totfr)) < 0)
        return ret;

    cnt[c] = cnt_c + step;
    totfr += step;
    if (totfr > BOT) {
        totfr = 0;
        for (i = 0; i < maxc; i++) {
            unsigned nc = (cnt[i] >> 1) + 1;
            cnt[i] = nc;
            totfr += nc;
        }
    }

    cnt[maxc] = totfr;
    *rval = c;

    return 0;
}

static int decode_unit(SCPRContext *s, PixelModel *pixel, unsigned step, unsigned *rval)
{
    GetByteContext *gb = &s->gb;
    RangeCoder *rc = &s->rc;
    unsigned totfr = pixel->total_freq;
    unsigned value, x = 0, cumfr = 0, cnt_x = 0;
    int i, j, ret, c, cnt_c;

    if ((ret = s->get_freq(rc, totfr, &value)) < 0)
        return ret;

    while (x < 16) {
        cnt_x = pixel->lookup[x];
        if (value >= cumfr + cnt_x)
            cumfr += cnt_x;
        else
            break;
        x++;
    }

    c = x * 16;
    cnt_c = 0;
    while (c < 256) {
        cnt_c = pixel->freq[c];
        if (value >= cumfr + cnt_c)
            cumfr += cnt_c;
        else
            break;
        c++;
    }
    if (x >= 16 || c >= 256) {
        return AVERROR_INVALIDDATA;
    }

    if ((ret = s->decode(gb, rc, cumfr, cnt_c, totfr)) < 0)
        return ret;

    pixel->freq[c] = cnt_c + step;
    pixel->lookup[x] = cnt_x + step;
    totfr += step;
    if (totfr > BOT) {
        totfr = 0;
        for (i = 0; i < 256; i++) {
            unsigned nc = (pixel->freq[i] >> 1) + 1;
            pixel->freq[i] = nc;
            totfr += nc;
        }
        for (i = 0; i < 16; i++) {
            unsigned sum = 0;
            unsigned i16_17 = i << 4;
            for (j = 0; j < 16; j++)
                sum += pixel->freq[i16_17 + j];
            pixel->lookup[i] = sum;
        }
    }
    pixel->total_freq = totfr;

    *rval = c & s->cbits;

    return 0;
}

static int decompress_i(AVCodecContext *avctx, uint32_t *dst, int linesize)
{
    SCPRContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    int cx = 0, cx1 = 0, k = 0, clr = 0;
    int run, r, g, b, off, y = 0, x = 0, z, ret;
    unsigned backstep = linesize - avctx->width;
    const int cxshift = s->cxshift;
    unsigned lx, ly, ptype;

    reinit_tables(s);
    bytestream2_skip(gb, 2);
    init_rangecoder(&s->rc, gb);

    while (k < avctx->width + 1) {
        ret = decode_unit(s, &s->pixel_model[0][cx + cx1], 400, &r);
        if (ret < 0)
            return ret;

        cx1 = (cx << 6) & 0xFC0;
        cx = r >> cxshift;
        ret = decode_unit(s, &s->pixel_model[1][cx + cx1], 400, &g);
        if (ret < 0)
            return ret;

        cx1 = (cx << 6) & 0xFC0;
        cx = g >> cxshift;
        ret = decode_unit(s, &s->pixel_model[2][cx + cx1], 400, &b);
        if (ret < 0)
            return ret;

        cx1 = (cx << 6) & 0xFC0;
        cx = b >> cxshift;

        ret = decode_value(s, s->run_model[0], 256, 400, &run);
        if (ret < 0)
            return ret;

        clr = (b << 16) + (g << 8) + r;
        k += run;
        while (run-- > 0) {
            if (y >= avctx->height)
                return AVERROR_INVALIDDATA;

            dst[y * linesize + x] = clr;
            lx = x;
            ly = y;
            x++;
            if (x >= avctx->width) {
                x = 0;
                y++;
            }
        }
    }
    off = -linesize - 1;
    ptype = 0;

    while (x < avctx->width && y < avctx->height) {
        ret = decode_value(s, s->op_model[ptype], 6, 1000, &ptype);
        if (ret < 0)
            return ret;
        if (ptype == 0) {
            ret = decode_unit(s, &s->pixel_model[0][cx + cx1], 400, &r);
            if (ret < 0)
                return ret;

            cx1 = (cx << 6) & 0xFC0;
            cx = r >> cxshift;
            ret = decode_unit(s, &s->pixel_model[1][cx + cx1], 400, &g);
            if (ret < 0)
                return ret;

            cx1 = (cx << 6) & 0xFC0;
            cx = g >> cxshift;
            ret = decode_unit(s, &s->pixel_model[2][cx + cx1], 400, &b);
            if (ret < 0)
                return ret;

            clr = (b << 16) + (g << 8) + r;
        }
        if (ptype > 5)
            return AVERROR_INVALIDDATA;
        ret = decode_value(s, s->run_model[ptype], 256, 400, &run);
        if (ret < 0)
            return ret;

        switch (ptype) {
        case 0:
            while (run-- > 0) {
                if (y >= avctx->height)
                    return AVERROR_INVALIDDATA;

                dst[y * linesize + x] = clr;
                lx = x;
                ly = y;
                x++;
                if (x >= avctx->width) {
                    x = 0;
                    y++;
                }
            }
            break;
        case 1:
            while (run-- > 0) {
                if (y >= avctx->height)
                    return AVERROR_INVALIDDATA;

                dst[y * linesize + x] = dst[ly * linesize + lx];
                lx = x;
                ly = y;
                x++;
                if (x >= avctx->width) {
                    x = 0;
                    y++;
                }
            }
            clr = dst[ly * linesize + lx];
            break;
        case 2:
            while (run-- > 0) {
                if (y < 1 || y >= avctx->height)
                    return AVERROR_INVALIDDATA;

                clr = dst[y * linesize + x + off + 1];
                dst[y * linesize + x] = clr;
                lx = x;
                ly = y;
                x++;
                if (x >= avctx->width) {
                    x = 0;
                    y++;
                }
            }
            break;
        case 4:
            while (run-- > 0) {
                uint8_t *odst = (uint8_t *)dst;

                if (y < 1 || y >= avctx->height ||
                    (y == 1 && x == 0))
                    return AVERROR_INVALIDDATA;

                if (x == 0) {
                    z = backstep;
                } else {
                    z = 0;
                }

                r = odst[(ly * linesize + lx) * 4] +
                    odst[((y * linesize + x) + off - z) * 4 + 4] -
                    odst[((y * linesize + x) + off - z) * 4];
                g = odst[(ly * linesize + lx) * 4 + 1] +
                    odst[((y * linesize + x) + off - z) * 4 + 5] -
                    odst[((y * linesize + x) + off - z) * 4 + 1];
                b = odst[(ly * linesize + lx) * 4 + 2] +
                    odst[((y * linesize + x) + off - z) * 4 + 6] -
                    odst[((y * linesize + x) + off - z) * 4 + 2];
                clr = ((b & 0xFF) << 16) + ((g & 0xFF) << 8) + (r & 0xFF);
                dst[y * linesize + x] = clr;
                lx = x;
                ly = y;
                x++;
                if (x >= avctx->width) {
                    x = 0;
                    y++;
                }
            }
            break;
        case 5:
            while (run-- > 0) {
                if (y < 1 || y >= avctx->height ||
                    (y == 1 && x == 0))
                    return AVERROR_INVALIDDATA;

                if (x == 0) {
                    z = backstep;
                } else {
                    z = 0;
                }

                clr = dst[y * linesize + x + off - z];
                dst[y * linesize + x] = clr;
                lx = x;
                ly = y;
                x++;
                if (x >= avctx->width) {
                    x = 0;
                    y++;
                }
            }
            break;
        }

        if (avctx->bits_per_coded_sample == 16) {
            cx1 = (clr & 0x3F00) >> 2;
            cx = (clr & 0x3FFFFF) >> 16;
        } else {
            cx1 = (clr & 0xFC00) >> 4;
            cx = (clr & 0xFFFFFF) >> 18;
        }
    }

    return 0;
}

static int decompress_p(AVCodecContext *avctx,
                        uint32_t *dst, int linesize,
                        uint32_t *prev, int plinesize)
{
    SCPRContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    int ret, temp, min, max, x, y, cx = 0, cx1 = 0;
    int backstep = linesize - avctx->width;
    const int cxshift = s->cxshift;

    if (bytestream2_get_byte(gb) == 0)
        return 0;
    bytestream2_skip(gb, 1);
    init_rangecoder(&s->rc, gb);

    ret  = decode_value(s, s->range_model, 256, 1, &min);
    ret |= decode_value(s, s->range_model, 256, 1, &temp);
    min += temp << 8;
    ret |= decode_value(s, s->range_model, 256, 1, &max);
    ret |= decode_value(s, s->range_model, 256, 1, &temp);
    if (ret < 0)
        return ret;

    max += temp << 8;
    memset(s->blocks, 0, sizeof(*s->blocks) * s->nbcount);

    while (min <= max) {
        int fill, count;

        ret  = decode_value(s, s->fill_model,  5,   10, &fill);
        ret |= decode_value(s, s->count_model, 256, 20, &count);
        if (ret < 0)
            return ret;

        while (min < s->nbcount && count-- > 0) {
            s->blocks[min++] = fill;
        }
    }

    for (y = 0; y < s->nby; y++) {
        for (x = 0; x < s->nbx; x++) {
            int sy1 = 0, sy2 = 16, sx1 = 0, sx2 = 16;

            if (s->blocks[y * s->nbx + x] == 0)
                continue;

            if (((s->blocks[y * s->nbx + x] - 1) & 1) > 0) {
                ret  = decode_value(s, s->sxy_model[0], 16, 100, &sx1);
                ret |= decode_value(s, s->sxy_model[1], 16, 100, &sy1);
                ret |= decode_value(s, s->sxy_model[2], 16, 100, &sx2);
                ret |= decode_value(s, s->sxy_model[3], 16, 100, &sy2);
                if (ret < 0)
                    return ret;

                sx2++;
                sy2++;
            }
            if (((s->blocks[y * s->nbx + x] - 1) & 2) > 0) {
                int i, j, by = y * 16, bx = x * 16;
                int mvx, mvy;

                ret  = decode_value(s, s->mv_model[0], 512, 100, &mvx);
                ret |= decode_value(s, s->mv_model[1], 512, 100, &mvy);
                if (ret < 0)
                    return ret;

                mvx -= 256;
                mvy -= 256;

                if (by + mvy + sy1 < 0 || bx + mvx + sx1 < 0 ||
                    by + mvy + sy1 >= avctx->height || bx + mvx + sx1 >= avctx->width)
                    return AVERROR_INVALIDDATA;

                for (i = 0; i < sy2 - sy1 && (by + sy1 + i) < avctx->height && (by + mvy + sy1 + i) < avctx->height; i++) {
                    for (j = 0; j < sx2 - sx1 && (bx + sx1 + j) < avctx->width && (bx + mvx + sx1 + j) < avctx->width; j++) {
                        dst[(by + i + sy1) * linesize + bx + sx1 + j] = prev[(by + mvy + sy1 + i) * plinesize + bx + sx1 + mvx + j];
                    }
                }
            } else {
                int run, r, g, b, z, bx = x * 16 + sx1, by = y * 16 + sy1;
                unsigned clr, ptype = 0;

                for (; by < y * 16 + sy2 && by < avctx->height;) {
                    ret = decode_value(s, s->op_model[ptype], 6, 1000, &ptype);
                    if (ptype == 0) {
                        ret = decode_unit(s, &s->pixel_model[0][cx + cx1], 400, &r);
                        if (ret < 0)
                            return ret;

                        cx1 = (cx << 6) & 0xFC0;
                        cx = r >> cxshift;
                        ret = decode_unit(s, &s->pixel_model[1][cx + cx1], 400, &g);
                        if (ret < 0)
                            return ret;

                        cx1 = (cx << 6) & 0xFC0;
                        cx = g >> cxshift;
                        ret = decode_unit(s, &s->pixel_model[2][cx + cx1], 400, &b);
                        if (ret < 0)
                            return ret;

                        clr = (b << 16) + (g << 8) + r;
                    }
                    if (ptype > 5)
                        return AVERROR_INVALIDDATA;
                    ret = decode_value(s, s->run_model[ptype], 256, 400, &run);
                    if (ret < 0)
                        return ret;

                    switch (ptype) {
                    case 0:
                        while (run-- > 0) {
                            if (by >= avctx->height)
                                return AVERROR_INVALIDDATA;

                            dst[by * linesize + bx] = clr;
                            bx++;
                            if (bx >= x * 16 + sx2 || bx >= avctx->width) {
                                bx = x * 16 + sx1;
                                by++;
                            }
                        }
                        break;
                    case 1:
                        while (run-- > 0) {
                            if (bx == 0) {
                                if (by < 1)
                                    return AVERROR_INVALIDDATA;
                                z = backstep;
                            } else {
                                z = 0;
                            }

                            if (by >= avctx->height)
                                return AVERROR_INVALIDDATA;

                            clr = dst[by * linesize + bx - 1 - z];
                            dst[by * linesize + bx] = clr;
                            bx++;
                            if (bx >= x * 16 + sx2 || bx >= avctx->width) {
                                bx = x * 16 + sx1;
                                by++;
                            }
                        }
                        break;
                    case 2:
                        while (run-- > 0) {
                            if (by < 1 || by >= avctx->height)
                                return AVERROR_INVALIDDATA;

                            clr = dst[(by - 1) * linesize + bx];
                            dst[by * linesize + bx] = clr;
                            bx++;
                            if (bx >= x * 16 + sx2 || bx >= avctx->width) {
                                bx = x * 16 + sx1;
                                by++;
                            }
                        }
                        break;
                    case 3:
                        while (run-- > 0) {
                            if (by >= avctx->height)
                                return AVERROR_INVALIDDATA;

                            clr = prev[by * plinesize + bx];
                            dst[by * linesize + bx] = clr;
                            bx++;
                            if (bx >= x * 16 + sx2 || bx >= avctx->width) {
                                bx = x * 16 + sx1;
                                by++;
                            }
                        }
                        break;
                    case 4:
                        while (run-- > 0) {
                            uint8_t *odst = (uint8_t *)dst;

                            if (by < 1 || by >= avctx->height)
                                return AVERROR_INVALIDDATA;

                            if (bx == 0) {
                                z = backstep;
                            } else {
                                z = 0;
                            }

                            r = odst[((by - 1) * linesize + bx) * 4] +
                                odst[(by * linesize + bx - 1 - z) * 4] -
                                odst[((by - 1) * linesize + bx - 1 - z) * 4];
                            g = odst[((by - 1) * linesize + bx) * 4 + 1] +
                                odst[(by * linesize + bx - 1 - z) * 4 + 1] -
                                odst[((by - 1) * linesize + bx - 1 - z) * 4 + 1];
                            b = odst[((by - 1) * linesize + bx) * 4 + 2] +
                                odst[(by * linesize + bx - 1 - z) * 4 + 2] -
                                odst[((by - 1) * linesize + bx - 1 - z) * 4 + 2];
                            clr = ((b & 0xFF) << 16) + ((g & 0xFF) << 8) + (r & 0xFF);
                            dst[by * linesize + bx] = clr;
                            bx++;
                            if (bx >= x * 16 + sx2 || bx >= avctx->width) {
                                bx = x * 16 + sx1;
                                by++;
                            }
                        }
                        break;
                    case 5:
                        while (run-- > 0) {
                            if (by < 1 || by >= avctx->height)
                                return AVERROR_INVALIDDATA;

                            if (bx == 0) {
                                z = backstep;
                            } else {
                                z = 0;
                            }

                            clr = dst[(by - 1) * linesize + bx - 1 - z];
                            dst[by * linesize + bx] = clr;
                            bx++;
                            if (bx >= x * 16 + sx2 || bx >= avctx->width) {
                                bx = x * 16 + sx1;
                                by++;
                            }
                        }
                        break;
                    }

                    if (avctx->bits_per_coded_sample == 16) {
                        cx1 = (clr & 0x3F00) >> 2;
                        cx = (clr & 0x3FFFFF) >> 16;
                    } else {
                        cx1 = (clr & 0xFC00) >> 4;
                        cx = (clr & 0xFFFFFF) >> 18;
                    }
                }
            }
        }
    }

    return 0;
}

static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    SCPRContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    AVFrame *frame = data;
    int ret, type;

    if (avctx->bits_per_coded_sample == 16) {
        if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
            return ret;
    }

    if ((ret = ff_reget_buffer(avctx, s->current_frame)) < 0)
        return ret;

    bytestream2_init(gb, avpkt->data, avpkt->size);

    type = bytestream2_peek_byte(gb);

    if (type == 2) {
        s->get_freq = get_freq0;
        s->decode = decode0;
        frame->key_frame = 1;
        ret = decompress_i(avctx, (uint32_t *)s->current_frame->data[0],
                           s->current_frame->linesize[0] / 4);
    } else if (type == 18) {
        s->get_freq = get_freq;
        s->decode = decode;
        frame->key_frame = 1;
        ret = decompress_i(avctx, (uint32_t *)s->current_frame->data[0],
                           s->current_frame->linesize[0] / 4);
    } else if (type == 17) {
        uint32_t clr, *dst = (uint32_t *)s->current_frame->data[0];
        int x, y;

        frame->key_frame = 1;
        bytestream2_skip(gb, 1);
        if (avctx->bits_per_coded_sample == 16) {
            uint16_t value = bytestream2_get_le16(gb);
            int r, g, b;

            r = (value      ) & 31;
            g = (value >>  5) & 31;
            b = (value >> 10) & 31;
            clr = (r << 16) + (g << 8) + b;
        } else {
            clr = bytestream2_get_le24(gb);
        }
        for (y = 0; y < avctx->height; y++) {
            for (x = 0; x < avctx->width; x++) {
                dst[x] = clr;
            }
            dst += s->current_frame->linesize[0] / 4;
        }
    } else if (type == 0 || type == 1) {
        frame->key_frame = 0;

        ret = av_frame_copy(s->current_frame, s->last_frame);
        if (ret < 0)
            return ret;

        ret = decompress_p(avctx, (uint32_t *)s->current_frame->data[0],
                           s->current_frame->linesize[0] / 4,
                           (uint32_t *)s->last_frame->data[0],
                           s->last_frame->linesize[0] / 4);
    } else {
        return AVERROR_PATCHWELCOME;
    }

    if (ret < 0)
        return ret;

    if (avctx->bits_per_coded_sample != 16) {
        ret = av_frame_ref(data, s->current_frame);
        if (ret < 0)
            return ret;
    } else {
        uint8_t *dst = frame->data[0];
        int x, y;

        ret = av_frame_copy(frame, s->current_frame);
        if (ret < 0)
            return ret;

        // scale up each sample by 8
        for (y = 0; y < avctx->height; y++) {
            // If the image is sufficiently aligned, compute 8 samples at once
            if (!(((uintptr_t)dst) & 7)) {
                uint64_t *dst64 = (uint64_t *)dst;
                int w = avctx->width>>1;
                for (x = 0; x < w; x++) {
                    dst64[x] = (dst64[x] << 3) & 0xFCFCFCFCFCFCFCFCULL;
                }
                x *= 8;
            } else
                x = 0;
            for (; x < avctx->width * 4; x++) {
                dst[x] = dst[x] << 3;
            }
            dst += frame->linesize[0];
        }
    }

    frame->pict_type = frame->key_frame ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;

    FFSWAP(AVFrame *, s->current_frame, s->last_frame);

    frame->data[0]     += frame->linesize[0] * (avctx->height - 1);
    frame->linesize[0] *= -1;

    *got_frame = 1;

    return avpkt->size;
}

static av_cold int decode_init(AVCodecContext *avctx)
{
    SCPRContext *s = avctx->priv_data;

    switch (avctx->bits_per_coded_sample) {
    case 16: avctx->pix_fmt = AV_PIX_FMT_RGB0; break;
    case 24:
    case 32: avctx->pix_fmt = AV_PIX_FMT_BGR0; break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unsupported bitdepth %i\n", avctx->bits_per_coded_sample);
        return AVERROR_INVALIDDATA;
    }

    s->get_freq = get_freq0;
    s->decode = decode0;

    s->cxshift = avctx->bits_per_coded_sample == 16 ? 0 : 2;
    s->cbits = avctx->bits_per_coded_sample == 16 ? 0x1F : 0xFF;
    s->nbx = (avctx->width + 15) / 16;
    s->nby = (avctx->height + 15) / 16;
    s->nbcount = s->nbx * s->nby;
    s->blocks = av_malloc_array(s->nbcount, sizeof(*s->blocks));
    if (!s->blocks)
        return AVERROR(ENOMEM);

    s->last_frame = av_frame_alloc();
    s->current_frame = av_frame_alloc();
    if (!s->last_frame || !s->current_frame)
        return AVERROR(ENOMEM);

    return 0;
}

static av_cold int decode_close(AVCodecContext *avctx)
{
    SCPRContext *s = avctx->priv_data;

    av_freep(&s->blocks);
    av_frame_free(&s->last_frame);
    av_frame_free(&s->current_frame);

    return 0;
}

AVCodec ff_scpr_decoder = {
    .name             = "scpr",
    .long_name        = NULL_IF_CONFIG_SMALL("ScreenPressor"),
    .type             = AVMEDIA_TYPE_VIDEO,
    .id               = AV_CODEC_ID_SCPR,
    .priv_data_size   = sizeof(SCPRContext),
    .init             = decode_init,
    .close            = decode_close,
    .decode           = decode_frame,
    .capabilities     = AV_CODEC_CAP_DR1,
    .caps_internal    = FF_CODEC_CAP_INIT_THREADSAFE |
                        FF_CODEC_CAP_INIT_CLEANUP,
};
