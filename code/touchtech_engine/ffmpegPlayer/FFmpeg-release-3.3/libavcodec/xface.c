﻿/*
 * Copyright (c) 1990 James Ashton - Sydney University
 * Copyright (c) 2012 Stefano Sabatini
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

/**
 * @file
 * X-Face common data and utilities definition.
 */

#include "libavutil/avassert.h"

#include "xface.h"

void ff_big_add(BigInt *b, uint8_t a)
{
    int i;
    uint8_t *w;
    uint16_t c;

    a &= XFACE_WORDMASK;
    if (a == 0)
        return;
    w = b->words;
    c = a;
    for (i = 0; i < b->nb_words && c; i++) {
        c += *w;
        *w++ = c & XFACE_WORDMASK;
        c >>= XFACE_BITSPERWORD;
    }
    if (i == b->nb_words && c) {
        av_assert0(b->nb_words < XFACE_MAX_WORDS);
        b->nb_words++;
        *w = c & XFACE_WORDMASK;
    }
}

void ff_big_div(BigInt *b, uint8_t a, uint8_t *r)
{
    int i;
    uint8_t *w;
    uint16_t c, d;

    a &= XFACE_WORDMASK;
    if (a == 1 || b->nb_words == 0) {
        *r = 0;
        return;
    }

    /* treat this as a == WORDCARRY and just shift everything right a WORD */
    if (a == 0) {
        i = --b->nb_words;
        w = b->words;
        *r = *w;
        while (i--) {
            *w = *(w + 1);
            w++;
        }
        *w = 0;
        return;
    }
    i = b->nb_words;
    w = b->words + i;
    c = 0;
    while (i--) {
        c <<= XFACE_BITSPERWORD;
        c += *--w;
        d = c / (uint16_t)a;
        c = c % (uint16_t)a;
        *w = d & XFACE_WORDMASK;
    }
    *r = c;
    if (b->words[b->nb_words - 1] == 0)
        b->nb_words--;
}

void ff_big_mul(BigInt *b, uint8_t a)
{
    int i;
    uint8_t *w;
    uint16_t c;

    a &= XFACE_WORDMASK;
    if (a == 1 || b->nb_words == 0)
        return;
    if (a == 0) {
        /* treat this as a == WORDCARRY and just shift everything left a WORD */
        av_assert0(b->nb_words < XFACE_MAX_WORDS);
        i = b->nb_words++;
        w = b->words + i;
        while (i--) {
            *w = *(w - 1);
            w--;
        }
        *w = 0;
        return;
    }
    i = b->nb_words;
    w = b->words;
    c = 0;
    while (i--) {
        c += (uint16_t)*w * (uint16_t)a;
        *(w++) = c & XFACE_WORDMASK;
        c >>= XFACE_BITSPERWORD;
    }
    if (c) {
        av_assert0(b->nb_words < XFACE_MAX_WORDS);
        b->nb_words++;
        *w = c & XFACE_WORDMASK;
    }
}

const ProbRange ff_xface_probranges_per_level[4][3] = {
    //  black      grey       white
    { {  1, 255}, {251, 0}, {  4, 251} }, /* Top of tree almost always grey */
    { {  1, 255}, {200, 0}, { 55, 200} },
    { { 33, 223}, {159, 0}, { 64, 159} },
    { {131,   0}, {  0, 0}, {125, 131} }, /* Grey disallowed at bottom */
};

const ProbRange ff_xface_probranges_2x2[16] = {
    { 0,   0},  {38,   0}, {38,  38},  {13, 152},
    {38,  76},  {13, 165}, {13, 178},  { 6, 230},
    {38, 114},  {13, 191}, {13, 204},  { 6, 236},
    {13, 217},  { 6, 242}, { 5, 248},  { 3, 253},
};

/*
 * The "guess the next pixel" tables follow. Normally there are 12
 * neighbour pixels used to give 1<<12 cases as we get closer to the
 * upper left corner lesser numbers of neighbours are available.
 *
 * Each byte in the tables represents 8 boolean values starting from
 * the most significant bit.
 */

static const uint8_t g_00[] = {
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0xe3, 0xdf, 0x05, 0x17,
    0x05, 0x0f, 0x00, 0x1b, 0x0f, 0xdf, 0x00, 0x04, 0x00, 0x00,
    0x0d, 0x0f, 0x03, 0x7f, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1d,
    0x45, 0x2f, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x0a, 0xff, 0xff,
    0x00, 0x04, 0x00, 0x05, 0x01, 0x3f, 0xcf, 0xff, 0x10, 0x01,
    0x80, 0xc9, 0x0f, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x1b, 0x1f, 0xff, 0xff, 0x4f, 0x54, 0x07, 0x1f, 0x57, 0x47,
    0xd7, 0x3d, 0xff, 0xff, 0x5f, 0x1f, 0x7f, 0xff, 0x7f, 0x7f,
    0x05, 0x0f, 0x01, 0x0f, 0x0f, 0x5f, 0x9b, 0xdf, 0x7f, 0xff,
    0x5f, 0x1d, 0x5f, 0xff, 0x0f, 0x1f, 0x0f, 0x5f, 0x03, 0x1f,
    0x4f, 0x5f, 0xf7, 0x7f, 0x7f, 0xff, 0x0d, 0x0f, 0xfb, 0xff,
    0xf7, 0xbf, 0x0f, 0x4f, 0xd7, 0x3f, 0x4f, 0x7f, 0xff, 0xff,
    0x67, 0xbf, 0x56, 0x25, 0x1f, 0x7f, 0x9f, 0xff, 0x00, 0x00,
    0x00, 0x05, 0x5f, 0x7f, 0x01, 0xdf, 0x14, 0x00, 0x05, 0x0f,
    0x07, 0xa2, 0x09, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x5f,
    0x18, 0xd7, 0x94, 0x71, 0x00, 0x05, 0x1f, 0xb7, 0x0c, 0x07,
    0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x1f, 0x84, 0x8f, 0x05, 0x15,
    0x05, 0x0f, 0x4f, 0xff, 0x87, 0xdf, 0x05, 0x01, 0x10, 0x00,
    0x0f, 0x0f, 0x00, 0x08, 0x05, 0x04, 0x04, 0x01, 0x4f, 0xff,
    0x9f, 0x8f, 0x4a, 0x40, 0x5f, 0x5f, 0xff, 0xfe, 0xdf, 0xff,
    0x7f, 0xf7, 0xff, 0x7f, 0xff, 0xff, 0x7b, 0xff, 0x0f, 0xfd,
    0xd7, 0x5f, 0x4f, 0x7f, 0x7f, 0xdf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x77, 0xdf, 0x7f, 0x4f, 0xef, 0xff, 0xff, 0x77, 0xff,
    0xff, 0xff, 0x6f, 0xff, 0x0f, 0x4f, 0xff, 0xff, 0x9d, 0xff,
    0x0f, 0xef, 0xff, 0xdf, 0x6f, 0xff, 0xff, 0xff, 0x4f, 0xff,
    0xcd, 0x0f, 0x4f, 0xff, 0xff, 0xdf, 0x00, 0x00, 0x00, 0x0b,
    0x05, 0x02, 0x02, 0x0f, 0x04, 0x00, 0x00, 0x0c, 0x01, 0x06,
    0x00, 0x0f, 0x20, 0x03, 0x00, 0x00, 0x05, 0x0f, 0x40, 0x08,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x0c, 0x0f, 0x01, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x14, 0x01, 0x05,
    0x01, 0x15, 0xaf, 0x0f, 0x00, 0x01, 0x10, 0x00, 0x08, 0x00,
    0x46, 0x0c, 0x20, 0x00, 0x88, 0x00, 0x0f, 0x15, 0xff, 0xdf,
    0x02, 0x00, 0x00, 0x0f, 0x7f, 0x5f, 0xdb, 0xff, 0x4f, 0x3e,
    0x05, 0x0f, 0x7f, 0xf7, 0x95, 0x4f, 0x0d, 0x0f, 0x01, 0x0f,
    0x4f, 0x5f, 0x9f, 0xdf, 0x25, 0x0e, 0x0d, 0x0d, 0x4f, 0x7f,
    0x8f, 0x0f, 0x0f, 0xfa, 0x04, 0x4f, 0x4f, 0xff, 0xf7, 0x77,
    0x47, 0xed, 0x05, 0x0f, 0xff, 0xff, 0xdf, 0xff, 0x4f, 0x6f,
    0xd8, 0x5f, 0x0f, 0x7f, 0xdf, 0x5f, 0x07, 0x0f, 0x94, 0x0d,
    0x1f, 0xff, 0xff, 0xff, 0x00, 0x02, 0x00, 0x03, 0x46, 0x57,
    0x01, 0x0d, 0x01, 0x08, 0x01, 0x0f, 0x47, 0x6c, 0x0d, 0x0f,
    0x02, 0x00, 0x00, 0x00, 0x0b, 0x4f, 0x00, 0x08, 0x05, 0x00,
    0x95, 0x01, 0x0f, 0x7f, 0x0c, 0x0f, 0x01, 0x0e, 0x00, 0x00,
    0x0f, 0x41, 0x00, 0x00, 0x04, 0x24, 0x0d, 0x0f, 0x0f, 0x7f,
    0xcf, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00,
    0x06, 0x26, 0xcf, 0x05, 0xcf, 0x7f, 0xdf, 0xdf, 0x00, 0x00,
    0x17, 0x5f, 0xff, 0xfd, 0xff, 0xff, 0x46, 0x09, 0x4f, 0x5f,
    0x7f, 0xfd, 0xdf, 0xff, 0x0a, 0x88, 0xa7, 0x7f, 0x7f, 0xff,
    0xff, 0xff, 0x0f, 0x04, 0xdf, 0x7f, 0x4f, 0xff, 0x9f, 0xff,
    0x0e, 0xe6, 0xdf, 0xff, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xec,
    0x8f, 0x4f, 0x7f, 0xff, 0xdf, 0xff, 0x0f, 0xcf, 0xdf, 0xff,
    0x6f, 0x7f, 0xff, 0xff, 0x03, 0x0c, 0x9d, 0x0f, 0x7f, 0xff,
    0xff, 0xff,
};

static const uint8_t g_01[] = {
    0x37, 0x73, 0x00, 0x19, 0x57, 0x7f, 0xf5, 0xfb, 0x70, 0x33,
    0xf0, 0xf9, 0x7f, 0xff, 0xff, 0xff,
};

static const uint8_t g_02[] = {
    0x50,
};

static const uint8_t g_10[] = {
    0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0xf3, 0x5f, 0x84, 0x04,
    0x17, 0x9f, 0x04, 0x23, 0x05, 0xff, 0x00, 0x00, 0x00, 0x02,
    0x03, 0x03, 0x33, 0xd7, 0x05, 0x03, 0x5f, 0x3f, 0x17, 0x33,
    0xff, 0xff, 0x00, 0x80, 0x02, 0x04, 0x12, 0x00, 0x11, 0x57,
    0x05, 0x25, 0x05, 0x03, 0x35, 0xbf, 0x9f, 0xff, 0x07, 0x6f,
    0x20, 0x40, 0x17, 0x06, 0xfa, 0xe8, 0x01, 0x07, 0x1f, 0x9f,
    0x1f, 0xff, 0xff, 0xff,
};

static const uint8_t g_20[] = {
    0x04, 0x00, 0x01, 0x01, 0x43, 0x2e, 0xff, 0x3f,
};

static const uint8_t g_30[] = {
    0x11, 0x11, 0x11, 0x11, 0x51, 0x11, 0x13, 0x11, 0x11, 0x11,
    0x13, 0x11, 0x11, 0x11, 0x33, 0x11, 0x13, 0x11, 0x13, 0x13,
    0x13, 0x13, 0x31, 0x31, 0x11, 0x01, 0x11, 0x11, 0x71, 0x11,
    0x11, 0x75,
};

static const uint8_t g_40[] = {
    0x00, 0x0f, 0x00, 0x09, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0f,
    0x00, 0x4e, 0xe4, 0x0d, 0x10, 0x0f, 0x00, 0x0f, 0x44, 0x4f,
    0x00, 0x1e, 0x0f, 0x0f, 0xae, 0xaf, 0x45, 0x7f, 0xef, 0xff,
    0x0f, 0xff, 0x00, 0x09, 0x01, 0x11, 0x00, 0x01, 0x1c, 0xdd,
    0x00, 0x15, 0x00, 0xff, 0x00, 0x10, 0x00, 0xfd, 0x00, 0x0f,
    0x4f, 0x5f, 0x3d, 0xff, 0xff, 0xff, 0x4f, 0xff, 0x1c, 0xff,
    0xdf, 0xff, 0x8f, 0xff, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x15,
    0x01, 0x07, 0x00, 0x01, 0x02, 0x1f, 0x01, 0x11, 0x05, 0x7f,
    0x00, 0x1f, 0x41, 0x57, 0x1f, 0xff, 0x05, 0x77, 0x0d, 0x5f,
    0x4d, 0xff, 0x4f, 0xff, 0x0f, 0xff, 0x00, 0x00, 0x02, 0x05,
    0x00, 0x11, 0x05, 0x7d, 0x10, 0x15, 0x2f, 0xff, 0x40, 0x50,
    0x0d, 0xfd, 0x04, 0x0f, 0x07, 0x1f, 0x07, 0x7f, 0x0f, 0xbf,
    0x0d, 0x7f, 0x0f, 0xff, 0x4d, 0x7d, 0x0f, 0xff,
};

static const uint8_t g_11[] = {
    0x01, 0x13, 0x03, 0x7f,
};

static const uint8_t g_21[] = {
    0x17,
};

static const uint8_t g_31[] = {
    0x55, 0x57, 0x57, 0x7f,
};

static const uint8_t g_41[] = {
    0x01, 0x01, 0x01, 0x1f, 0x03, 0x1f, 0x3f, 0xff,
};

static const uint8_t g_12[] = {
    0x40,
};

static const uint8_t g_22[] = {
    0x00,
};

static const uint8_t g_32[] = {
    0x10,
};

static const uint8_t g_42[] = {
    0x10,
};

void ff_xface_generate_face(uint8_t *dst, uint8_t * const src)
{
    int h, i, j, k, l, m;

    for (j = 0; j < XFACE_HEIGHT; j++) {
        for (i = 0; i < XFACE_WIDTH; i++) {
            h = i + j * XFACE_WIDTH;
            k = 0;

            /*
               Compute k, encoding the bits *before* the current one, contained in the
               image buffer. That is, given the grid:

                l      i
                |      |
                v      v
               +--+--+--+--+--+
          m -> | 1| 2| 3| 4| 5|
               +--+--+--+--+--+
               | 6| 7| 8| 9|10|
               +--+--+--+--+--+
          j -> |11|12| *|  |  |
               +--+--+--+--+--+

               the value k for the pixel marked as "*" will contain the bit encoding of
               the values in the matrix marked from "1" to "12". In case the pixel is
               near the border of the grid, the number of values contained within the
               grid will be lesser than 12.
             */

            for (l = i - 2; l <= i + 2; l++) {
                for (m = j - 2; m <= j; m++) {
                    if (l <= 0 || l >= i && m == j)
                        continue;
                    if (l <= XFACE_WIDTH && m > 0)
                        k = 2*k + src[l + m * XFACE_WIDTH];
                }
            }

            /*
              Use the guess for the given position and the computed value of k.

              The following table shows the number of digits in k, depending on
              the position of the pixel, and shows the corresponding guess table
              to use:

                 i=1  i=2  i=3       i=w-1 i=w
               +----+----+----+ ... +----+----+
           j=1 |  0 |  1 |  2 |     |  2 |  2 |
               |g22 |g12 |g02 |     |g42 |g32 |
               +----+----+----+ ... +----+----+
           j=2 |  3 |  5 |  7 |     |  6 |  5 |
               |g21 |g11 |g01 |     |g41 |g31 |
               +----+----+----+ ... +----+----+
           j=3 |  5 |  9 | 12 |     | 10 |  8 |
               |g20 |g10 |g00 |     |g40 |g30 |
               +----+----+----+ ... +----+----+
            */

#define GEN(table) dst[h] ^= (table[k>>3]>>(7-(k&7)))&1

            switch (i) {
            case 1:
                switch (j) {
                case 1:  GEN(g_22); break;
                case 2:  GEN(g_21); break;
                default: GEN(g_20); break;
                }
                break;
            case 2:
                switch (j) {
                case 1:  GEN(g_12); break;
                case 2:  GEN(g_11); break;
                default: GEN(g_10); break;
                }
                break;
            case XFACE_WIDTH - 1:
                switch (j) {
                case 1:  GEN(g_42); break;
                case 2:  GEN(g_41); break;
                default: GEN(g_40); break;
                }
                break;
            case XFACE_WIDTH:
                switch (j) {
                case 1:  GEN(g_32); break;
                case 2:  GEN(g_31); break;
                default: GEN(g_30); break;
                }
                break;
            default:
                switch (j) {
                case 1:  GEN(g_02); break;
                case 2:  GEN(g_01); break;
                default: GEN(g_00); break;
                }
                break;
            }
        }
    }
}
