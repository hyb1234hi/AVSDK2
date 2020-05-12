﻿/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/modules/audio_coding/codecs/isac/fix/source/pitch_estimator.h"

#include "webrtc/common_audio/signal_processing/include/signal_processing_library.h"
#include "webrtc/modules/audio_coding/codecs/isac/fix/source/settings.h"
#include "webrtc/modules/audio_coding/codecs/isac/fix/source/structs.h"
#include "webrtc/system_wrappers/include/compile_assert_c.h"

// Number of segments in a pitch subframe.
static const int kSegments = 5;

// A division factor of 1/5 in Q15.
static const int16_t kDivFactor = 6553;

// Interpolation coefficients; generated by design_pitch_filter.m.
// Coefficients are stored in Q14.
static const int16_t kIntrpCoef[PITCH_FRACS][PITCH_FRACORDER] = {
  {-367, 1090, -2706,  9945, 10596, -3318,  1626, -781,  287},
  {-325,  953, -2292,  7301, 12963, -3320,  1570, -743,  271},
  {-240,  693, -1622,  4634, 14809, -2782,  1262, -587,  212},
  {-125,  358,  -817,  2144, 15982, -1668,   721, -329,  118},
  {   0,    0,    -1,     1, 16380,     1,    -1,    0,    0},
  { 118, -329,   721, -1668, 15982,  2144,  -817,  358, -125},
  { 212, -587,  1262, -2782, 14809,  4634, -1622,  693, -240},
  { 271, -743,  1570, -3320, 12963,  7301, -2292,  953, -325}
};

static __inline size_t CalcLrIntQ(int16_t fixVal,
                                  int16_t qDomain) {
  int32_t roundVal = 1 << (qDomain - 1);

  return (fixVal + roundVal) >> qDomain;
}

void WebRtcIsacfix_PitchFilter(int16_t* indatQQ, // Q10 if type is 1 or 4,
                                                       // Q0 if type is 2.
                               int16_t* outdatQQ,
                               PitchFiltstr* pfp,
                               int16_t* lagsQ7,
                               int16_t* gainsQ12,
                               int16_t type) {
  int    k, ind, cnt;
  int16_t sign = 1;
  int16_t inystateQQ[PITCH_DAMPORDER];
  int16_t ubufQQ[PITCH_INTBUFFSIZE + QLOOKAHEAD];
  const int16_t Gain = 21299;     // 1.3 in Q14
  int16_t oldLagQ7;
  int16_t oldGainQ12, lagdeltaQ7, curLagQ7, gaindeltaQ12, curGainQ12;
  size_t indW32 = 0, frcQQ = 0;
  const int16_t* fracoeffQQ = NULL;

  // Assumptions in ARM assembly for WebRtcIsacfix_PitchFilterCoreARM().
  COMPILE_ASSERT(PITCH_FRACORDER == 9);
  COMPILE_ASSERT(PITCH_DAMPORDER == 5);

  // Set up buffer and states.
  memcpy(ubufQQ, pfp->ubufQQ, sizeof(pfp->ubufQQ));
  memcpy(inystateQQ, pfp->ystateQQ, sizeof(inystateQQ));

  // Get old lag and gain value from memory.
  oldLagQ7 = pfp->oldlagQ7;
  oldGainQ12 = pfp->oldgainQ12;

  if (type == 4) {
    sign = -1;

    // Make output more periodic.
    for (k = 0; k < PITCH_SUBFRAMES; k++) {
      gainsQ12[k] = (int16_t)(gainsQ12[k] * Gain >> 14);
    }
  }

  // No interpolation if pitch lag step is big.
  if (((lagsQ7[0] * 3 >> 1) < oldLagQ7) || (lagsQ7[0] > (oldLagQ7 * 3 >> 1))) {
    oldLagQ7 = lagsQ7[0];
    oldGainQ12 = gainsQ12[0];
  }

  ind = 0;

  for (k = 0; k < PITCH_SUBFRAMES; k++) {
    // Calculate interpolation steps.
    lagdeltaQ7 = lagsQ7[k] - oldLagQ7;
    lagdeltaQ7 = (int16_t)WEBRTC_SPL_MUL_16_16_RSFT_WITH_ROUND(
                  lagdeltaQ7, kDivFactor, 15);
    curLagQ7 = oldLagQ7;
    gaindeltaQ12 = gainsQ12[k] - oldGainQ12;
    gaindeltaQ12 = (int16_t)(gaindeltaQ12 * kDivFactor >> 15);

    curGainQ12 = oldGainQ12;
    oldLagQ7 = lagsQ7[k];
    oldGainQ12 = gainsQ12[k];

    // Each frame has 4 60-sample pitch subframes, and each subframe has 5
    // 12-sample segments. Each segment need to be processed with
    // newly-updated parameters, so we break the pitch filtering into
    // two for-loops (5 x 12) below. It's also why kDivFactor = 0.2 (in Q15).
    for (cnt = 0; cnt < kSegments; cnt++) {
      // Update parameters for each segment.
      curGainQ12 += gaindeltaQ12;
      curLagQ7 += lagdeltaQ7;
      indW32 = CalcLrIntQ(curLagQ7, 7);
      frcQQ = ((indW32 << 7) + 64 - curLagQ7) >> 4;

      if (frcQQ == PITCH_FRACS) {
        frcQQ = 0;
      }
      fracoeffQQ = kIntrpCoef[frcQQ];

      // Pitch filtering.
      WebRtcIsacfix_PitchFilterCore(PITCH_SUBFRAME_LEN / kSegments, curGainQ12,
        indW32, sign, inystateQQ, ubufQQ, fracoeffQQ, indatQQ, outdatQQ, &ind);
    }
  }

  // Export buffer and states.
  memcpy(pfp->ubufQQ, ubufQQ + PITCH_FRAME_LEN, sizeof(pfp->ubufQQ));
  memcpy(pfp->ystateQQ, inystateQQ, sizeof(pfp->ystateQQ));

  pfp->oldlagQ7 = oldLagQ7;
  pfp->oldgainQ12 = oldGainQ12;

  if (type == 2) {
    // Filter look-ahead segment.
    WebRtcIsacfix_PitchFilterCore(QLOOKAHEAD, curGainQ12, indW32, 1, inystateQQ,
                ubufQQ, fracoeffQQ, indatQQ, outdatQQ, &ind);
  }
}


void WebRtcIsacfix_PitchFilterGains(const int16_t* indatQ0,
                                    PitchFiltstr* pfp,
                                    int16_t* lagsQ7,
                                    int16_t* gainsQ12) {
  int  k, n, m;
  size_t ind, pos, pos3QQ;

  int16_t ubufQQ[PITCH_INTBUFFSIZE];
  int16_t oldLagQ7, lagdeltaQ7, curLagQ7;
  const int16_t* fracoeffQQ = NULL;
  int16_t scale;
  int16_t cnt = 0, tmpW16;
  size_t frcQQ, indW16 = 0;
  int32_t tmpW32, tmp2W32, csum1QQ, esumxQQ;

  // Set up buffer and states.
  memcpy(ubufQQ, pfp->ubufQQ, sizeof(pfp->ubufQQ));
  oldLagQ7 = pfp->oldlagQ7;

  // No interpolation if pitch lag step is big.
  if (((lagsQ7[0] * 3 >> 1) < oldLagQ7) || (lagsQ7[0] > (oldLagQ7 * 3 >> 1))) {
    oldLagQ7 = lagsQ7[0];
  }

  ind = 0;
  pos = ind + PITCH_BUFFSIZE;
  scale = 0;
  for (k = 0; k < PITCH_SUBFRAMES; k++) {

    // Calculate interpolation steps.
    lagdeltaQ7 = lagsQ7[k] - oldLagQ7;
    lagdeltaQ7 = (int16_t)WEBRTC_SPL_MUL_16_16_RSFT_WITH_ROUND(
                   lagdeltaQ7, kDivFactor, 15);
    curLagQ7 = oldLagQ7;
    oldLagQ7 = lagsQ7[k];

    csum1QQ = 1;
    esumxQQ = 1;

    // Same as function WebRtcIsacfix_PitchFilter(), we break the pitch
    // filtering into two for-loops (5 x 12) below.
    for (cnt = 0; cnt < kSegments; cnt++) {
      // Update parameters for each segment.
      curLagQ7 += lagdeltaQ7;
      indW16 = CalcLrIntQ(curLagQ7, 7);
      frcQQ = ((indW16 << 7) + 64 - curLagQ7) >> 4;

      if (frcQQ == PITCH_FRACS) {
        frcQQ = 0;
      }
      fracoeffQQ = kIntrpCoef[frcQQ];

      pos3QQ = pos - (indW16 + 4);

      for (n = 0; n < PITCH_SUBFRAME_LEN / kSegments; n++) {
        // Filter to get fractional pitch.

        tmpW32 = 0;
        for (m = 0; m < PITCH_FRACORDER; m++) {
          tmpW32 += ubufQQ[pos3QQ + m] * fracoeffQQ[m];
        }

        // Subtract from input and update buffer.
        ubufQQ[pos] = indatQ0[ind];

        tmp2W32 = WEBRTC_SPL_MUL_16_32_RSFT14(indatQ0[ind], tmpW32);
        tmpW32 += 8192;
        tmpW16 = tmpW32 >> 14;
        tmpW32 = tmpW16 * tmpW16;

        if ((tmp2W32 > 1073700000) || (csum1QQ > 1073700000) ||
            (tmpW32 > 1073700000) || (esumxQQ > 1073700000)) {  // 2^30
          scale++;
          csum1QQ >>= 1;
          esumxQQ >>= 1;
        }
        csum1QQ += tmp2W32 >> scale;
        esumxQQ += tmpW32 >> scale;

        ind++;
        pos++;
        pos3QQ++;
      }
    }

    if (csum1QQ < esumxQQ) {
      tmp2W32 = YoumeWebRtcSpl_DivResultInQ31(csum1QQ, esumxQQ);

      // Gain should be half the correlation.
      tmpW32 = tmp2W32 >> 20;
    } else {
      tmpW32 = 4096;
    }
    gainsQ12[k] = (int16_t)WEBRTC_SPL_SAT(PITCH_MAX_GAIN_Q12, tmpW32, 0);
  }

  // Export buffer and states.
  memcpy(pfp->ubufQQ, ubufQQ + PITCH_FRAME_LEN, sizeof(pfp->ubufQQ));
  pfp->oldlagQ7 = lagsQ7[PITCH_SUBFRAMES - 1];
  pfp->oldgainQ12 = gainsQ12[PITCH_SUBFRAMES - 1];

}
