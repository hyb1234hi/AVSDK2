﻿/*
 *  Copyright 2013-15 ARM Limited and Contributors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of ARM Limited nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY ARM LIMITED AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL ARM LIMITED AND CONTRIBUTORS BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * NE10 Library : test_suite_fft_float32.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "NE10_dsp.h"
#include "NE10_macros.h"
#include "seatest.h"
#include "unit_test_common.h"


/* ----------------------------------------------------------------------
** Global defines
** ------------------------------------------------------------------- */

/* Max FFT Length and double buffer for real and imag */
#define TEST_LENGTH_SAMPLES (32768)
#define MIN_LENGTH_SAMPLES_CPX (4)
#define MIN_LENGTH_SAMPLES_REAL (MIN_LENGTH_SAMPLES_CPX*2)

#define TEST_COUNT 10000000

/* ----------------------------------------------------------------------
** Test input data for F32
** Generated by the MATLAB rand() function
** ------------------------------------------------------------------- */

static ne10_float32_t testInput_f32[TEST_LENGTH_SAMPLES * 2];

/* ----------------------------------------------------------------------
** Defines each of the tests performed
** ------------------------------------------------------------------- */

//input and output
static ne10_float32_t * guarded_in_c = NULL;
static ne10_float32_t * guarded_in_neon = NULL;
static ne10_float32_t * in_c = NULL;
static ne10_float32_t * in_neon = NULL;

static ne10_float32_t * guarded_out_c = NULL;
static ne10_float32_t * guarded_out_neon = NULL;
static ne10_float32_t * out_c = NULL;
static ne10_float32_t * out_neon = NULL;

static ne10_float32_t snr = 0.0f;

static ne10_int64_t time_c = 0;
static ne10_int64_t time_neon = 0;
static ne10_float32_t time_speedup = 0.0f;
static ne10_float32_t time_savings = 0.0f;

static ne10_fft_cfg_float32_t cfg_c;
static ne10_fft_cfg_float32_t cfg_neon;

static ne10_int32_t test_c2c_alloc (ne10_int32_t fftSize);

void test_fft_c2c_1d_float32_conformance()
{
    ne10_int32_t i = 0;
    ne10_int32_t fftSize = 0;
    ne10_int32_t flag_result = NE10_OK;

    fprintf (stdout, "----------%30s start\n", __FUNCTION__);

    for (fftSize = MIN_LENGTH_SAMPLES_CPX; fftSize <= TEST_LENGTH_SAMPLES; fftSize *= 2)
    {
        fprintf (stdout, "FFT size %d\n", fftSize);
        flag_result = test_c2c_alloc (fftSize);
        if (flag_result == NE10_ERR)
        {
            return;
        }

        /* FFT test */
        memcpy (in_c, testInput_f32, 2 * fftSize * sizeof (ne10_float32_t));
        memcpy (in_neon, testInput_f32, 2 * fftSize * sizeof (ne10_float32_t));

        GUARD_ARRAY (out_c, fftSize * 2);
        GUARD_ARRAY (out_neon, fftSize * 2);

        ne10_fft_c2c_1d_float32_c ( (ne10_fft_cpx_float32_t*) out_c, (ne10_fft_cpx_float32_t*) in_c, cfg_c, 0);
        ne10_fft_c2c_1d_float32_neon ( (ne10_fft_cpx_float32_t*) out_neon, (ne10_fft_cpx_float32_t*) in_neon, cfg_neon, 0);

        CHECK_ARRAY_GUARD (out_c, fftSize * 2);
        CHECK_ARRAY_GUARD (out_neon, fftSize * 2);

        //conformance test
        snr = CAL_SNR_FLOAT32 (out_c, out_neon, fftSize * 2);
        assert_false ( (snr < SNR_THRESHOLD));

        /* IFFT test */
        memcpy (in_c, testInput_f32, 2 * fftSize * sizeof (ne10_float32_t));
        memcpy (in_neon, testInput_f32, 2 * fftSize * sizeof (ne10_float32_t));

        GUARD_ARRAY (out_c, fftSize * 2);
        GUARD_ARRAY (out_neon, fftSize * 2);

        ne10_fft_c2c_1d_float32_c ( (ne10_fft_cpx_float32_t*) out_c, (ne10_fft_cpx_float32_t*) in_c, cfg_c,  1);
        ne10_fft_c2c_1d_float32_neon ( (ne10_fft_cpx_float32_t*) out_neon, (ne10_fft_cpx_float32_t*) in_neon, cfg_neon, 1);

        CHECK_ARRAY_GUARD (out_c, fftSize * 2);
        CHECK_ARRAY_GUARD (out_neon, fftSize * 2);

        //conformance test
        snr = CAL_SNR_FLOAT32 (out_c, out_neon, fftSize * 2);
        assert_false ( (snr < SNR_THRESHOLD));

        NE10_FREE (cfg_c);
        NE10_FREE (cfg_neon);
    }
}

void test_fft_c2c_1d_float32_performance()
{
    ne10_int32_t i = 0;
    ne10_int32_t fftSize = 0;
    ne10_int32_t flag_result = NE10_OK;
    ne10_int32_t test_loop = 0;

    fprintf (stdout, "----------%30s start\n", __FUNCTION__);
    fprintf (stdout, "%25s%20s%20s%20s%20s\n", "FFT Length", "C Time in ms", "NEON Time in ms", "Time Savings", "Performance Ratio");

    for (fftSize = MIN_LENGTH_SAMPLES_CPX; fftSize <= TEST_LENGTH_SAMPLES; fftSize *= 2)
    {
        fprintf (stdout, "FFT size %d\n", fftSize);

        /* FFT test */
        memcpy (in_c, testInput_f32, 2 * fftSize * sizeof (ne10_float32_t));
        memcpy (in_neon, testInput_f32, 2 * fftSize * sizeof (ne10_float32_t));
        flag_result = test_c2c_alloc (fftSize);
        if (flag_result == NE10_ERR)
        {
            return;
        }

        test_loop = TEST_COUNT / fftSize;

        GET_TIME
        (
            time_c,
        {
            for (i = 0; i < test_loop; i++)
                ne10_fft_c2c_1d_float32_c ( (ne10_fft_cpx_float32_t*) out_c, (ne10_fft_cpx_float32_t*) in_c, cfg_c, 0);
        }
        );
        GET_TIME
        (
            time_neon,
        {
            for (i = 0; i < test_loop; i++)
                ne10_fft_c2c_1d_float32_neon ( (ne10_fft_cpx_float32_t*) out_neon, (ne10_fft_cpx_float32_t*) in_neon, cfg_neon, 0);
        }
        );

        time_speedup = (ne10_float32_t) time_c / time_neon;
        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
        ne10_log (__FUNCTION__, "Float FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);

        /* IFFT test */
        memcpy (in_c, out_c, 2 * fftSize * sizeof (ne10_float32_t));
        memcpy (in_neon, out_c, 2 * fftSize * sizeof (ne10_float32_t));

        GET_TIME
        (
            time_c,
        {
            for (i = 0; i < test_loop; i++)
                ne10_fft_c2c_1d_float32_c ( (ne10_fft_cpx_float32_t*) out_c, (ne10_fft_cpx_float32_t*) in_c, cfg_c, 1);
        }
        );
        GET_TIME
        (
            time_neon,
        {
            for (i = 0; i < test_loop; i++)
                ne10_fft_c2c_1d_float32_neon ( (ne10_fft_cpx_float32_t*) out_neon, (ne10_fft_cpx_float32_t*) in_neon, cfg_neon, 1);
        }
        );

        time_speedup = (ne10_float32_t) time_c / time_neon;
        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
        ne10_log (__FUNCTION__, "Float FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);

        NE10_FREE (cfg_c);
        NE10_FREE (cfg_neon);
    }
}

void test_fft_r2c_1d_float32_conformance()
{

    ne10_int32_t i = 0;
    ne10_int32_t fftSize = 0;
    ne10_fft_r2c_cfg_float32_t cfg;

    fprintf (stdout, "----------%30s start\n", __FUNCTION__);

    for (fftSize = MIN_LENGTH_SAMPLES_REAL; fftSize <= TEST_LENGTH_SAMPLES; fftSize *= 2)
    {
        fprintf (stdout, "FFT size %d\n", fftSize);

        /* FFT test */
        memcpy (in_c, testInput_f32, fftSize * sizeof (ne10_float32_t));
        memcpy (in_neon, testInput_f32, fftSize * sizeof (ne10_float32_t));
        cfg = ne10_fft_alloc_r2c_float32 (fftSize);
        if (cfg == NULL)
        {
            fprintf (stdout, "======ERROR, FFT alloc fails\n");
            return;
        }

        GUARD_ARRAY (out_c, (fftSize / 2 + 1) * 2);
        GUARD_ARRAY (out_neon, (fftSize / 2 + 1) * 2);

        ne10_fft_r2c_1d_float32_c ( (ne10_fft_cpx_float32_t*) out_c, in_c, cfg);
        ne10_fft_r2c_1d_float32_neon ( (ne10_fft_cpx_float32_t*) out_neon, in_neon, cfg);

        CHECK_ARRAY_GUARD (out_c, (fftSize / 2 + 1) * 2);
        CHECK_ARRAY_GUARD (out_neon, (fftSize / 2 + 1) * 2);

        //conformance test
        snr = CAL_SNR_FLOAT32 (out_c, out_neon, (fftSize / 2 + 1) * 2);
        assert_false ( (snr < SNR_THRESHOLD));

        /* IFFT test */
        for (i = 1; i < (fftSize / 2); i++)
        {
            in_c[2 * i] = testInput_f32[2 * i];
            in_c[2 * i + 1] = testInput_f32[2 * i + 1];
            in_c[2 * (fftSize - i)] = in_c[2 * i];
            in_c[2 * (fftSize - i) + 1] = -in_c[2 * i + 1];
        }
        in_c[0] = testInput_f32[0];
        in_c[1] = 0;
        in_c[fftSize] = testInput_f32[1];
        in_c[fftSize + 1] = 0;
        memcpy (in_neon, in_c, fftSize * 2 * sizeof (ne10_float32_t));

        GUARD_ARRAY (out_c, fftSize);
        GUARD_ARRAY (out_neon, fftSize);

        ne10_fft_c2r_1d_float32_c (out_c, (ne10_fft_cpx_float32_t*) in_c, cfg);
        ne10_fft_c2r_1d_float32_neon (out_neon, (ne10_fft_cpx_float32_t*) in_neon, cfg);

        CHECK_ARRAY_GUARD (out_c, fftSize);
        CHECK_ARRAY_GUARD (out_neon, fftSize);

        //conformance test
        snr = CAL_SNR_FLOAT32 (out_c, out_neon, fftSize);
        assert_false ( (snr < SNR_THRESHOLD));

        NE10_FREE (cfg);
    }
}

void test_fft_r2c_1d_float32_performance()
{

    ne10_int32_t i = 0;
    ne10_int32_t fftSize = 0;
    ne10_fft_r2c_cfg_float32_t cfg;
    ne10_int32_t test_loop = 0;

    fprintf (stdout, "----------%30s start\n", __FUNCTION__);
    fprintf (stdout, "%25s%20s%20s%20s%20s\n", "FFT Length", "C Time in ms", "NEON Time in ms", "Time Savings", "Performance Ratio");

    for (fftSize = MIN_LENGTH_SAMPLES_REAL; fftSize <= TEST_LENGTH_SAMPLES; fftSize *= 2)
    {
        fprintf (stdout, "FFT size %d\n", fftSize);

        /* FFT test */
        memcpy (in_c, testInput_f32, fftSize * sizeof (ne10_float32_t));
        memcpy (in_neon, testInput_f32, fftSize * sizeof (ne10_float32_t));
        cfg = ne10_fft_alloc_r2c_float32 (fftSize);
        if (cfg == NULL)
        {
            fprintf (stdout, "======ERROR, FFT alloc fails\n");
            return;
        }
        test_loop = TEST_COUNT / fftSize;

        GET_TIME
        (
            time_c,
        {
            for (i = 0; i < test_loop; i++)
                ne10_fft_r2c_1d_float32_c ( (ne10_fft_cpx_float32_t*) out_c, in_c, cfg);
        }
        );
        GET_TIME
        (
            time_neon,
        {
            for (i = 0; i < test_loop; i++)
                ne10_fft_r2c_1d_float32_neon ( (ne10_fft_cpx_float32_t*) out_neon, in_neon, cfg);
        }
        );

        time_speedup = (ne10_float32_t) time_c / time_neon;
        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
        ne10_log (__FUNCTION__, "Float FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);

        /* IFFT test */
        for (i = 1; i < (fftSize / 2); i++)
        {
            in_c[2 * i] = testInput_f32[2 * i];
            in_c[2 * i + 1] = testInput_f32[2 * i + 1];
            in_c[2 * (fftSize - i)] = in_c[2 * i];
            in_c[2 * (fftSize - i) + 1] = -in_c[2 * i + 1];
        }
        in_c[0] = testInput_f32[0];
        in_c[1] = 0;
        in_c[fftSize] = testInput_f32[1];
        in_c[fftSize + 1] = 0;
        memcpy (in_neon, in_c, fftSize * 2 * sizeof (ne10_float32_t));

        GET_TIME
        (
            time_c,
        {
            for (i = 0; i < test_loop; i++)
                ne10_fft_c2r_1d_float32_c (out_c, (ne10_fft_cpx_float32_t*) in_c, cfg);
        }
        );
        GET_TIME
        (
            time_neon,
        {
            for (i = 0; i < test_loop; i++)
                ne10_fft_c2r_1d_float32_neon (out_neon, (ne10_fft_cpx_float32_t*) in_neon, cfg);
        }
        );

        time_speedup = (ne10_float32_t) time_c / time_neon;
        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
        ne10_log (__FUNCTION__, "Float FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);

        NE10_FREE (cfg);
    }
}

static void my_test_setup (void)
{
    ne10_log_buffer_ptr = ne10_log_buffer;
    ne10_int32_t i;

    /* init input memory */
    guarded_in_c = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_float32_t));
    guarded_in_neon = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_float32_t));
    in_c = guarded_in_c + ARRAY_GUARD_LEN;
    in_neon = guarded_in_neon + ARRAY_GUARD_LEN;

    /* init dst memory */
    guarded_out_c = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_float32_t));
    guarded_out_neon = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_float32_t));
    out_c = guarded_out_c + ARRAY_GUARD_LEN;
    out_neon = guarded_out_neon + ARRAY_GUARD_LEN;

    for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
    {
        testInput_f32[i] = (ne10_float32_t) (drand48() * 32768.0f - 16384.0f);
    }
}

static void my_test_teardown (void)
{
    NE10_FREE (guarded_in_c);
    NE10_FREE (guarded_in_neon);
    NE10_FREE (guarded_out_c);
    NE10_FREE (guarded_out_neon);
}

void test_fft_c2c_1d_float32()
{
#if defined (SMOKE_TEST)||(REGRESSION_TEST)
    test_fft_c2c_1d_float32_conformance();
#endif

#if defined (PERFORMANCE_TEST)
    test_fft_c2c_1d_float32_performance();
#endif
}

void test_fft_r2c_1d_float32()
{
#if defined (SMOKE_TEST)||(REGRESSION_TEST)
    test_fft_r2c_1d_float32_conformance();
#endif

#if defined (PERFORMANCE_TEST)
    test_fft_r2c_1d_float32_performance();
#endif
}

void test_fixture_fft_c2c_1d_float32 (void)
{
    test_fixture_start();               // starts a fixture

    fixture_setup (my_test_setup);

    run_test (test_fft_c2c_1d_float32);       // run tests

    fixture_teardown(my_test_teardown);

    test_fixture_end();                 // ends a fixture
}

void test_fixture_fft_r2c_1d_float32 (void)
{
    test_fixture_start();               // starts a fixture

    fixture_setup (my_test_setup);

    run_test (test_fft_r2c_1d_float32);       // run tests

    fixture_teardown(my_test_teardown);

    test_fixture_end();                 // ends a fixture
}

ne10_int32_t test_c2c_alloc (ne10_int32_t fftSize)
{
    NE10_FREE (cfg_c);
    NE10_FREE (cfg_neon);

    cfg_c = ne10_fft_alloc_c2c_float32_c (fftSize);
    if (cfg_c == NULL)
    {
        fprintf (stdout, "======ERROR, FFT alloc fails\n");
        return NE10_ERR;
    }

    cfg_neon = ne10_fft_alloc_c2c_float32_neon (fftSize);
    if (cfg_neon == NULL)
    {
        NE10_FREE (cfg_c);
        fprintf (stdout, "======ERROR, FFT alloc fails\n");
        return NE10_ERR;
    }
    return NE10_OK;
}
