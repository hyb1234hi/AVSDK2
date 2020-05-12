﻿/*
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

#ifndef COMPAT_ATOMICS_SUNCC_STDATOMIC_H
#define COMPAT_ATOMICS_SUNCC_STDATOMIC_H

#include <atomic.h>
#include <mbarrier.h>
#include <stddef.h>
#include <stdint.h>

#define ATOMIC_FLAG_INIT 0

#define ATOMIC_VAR_INIT(value) (value)

#define atomic_init(obj, value) \
do {                            \
    *(obj) = (value);           \
} while(0)

#define kill_dependency(y) ((void)0)

#define atomic_thread_fence(order) \
    __machine_rw_barrier();

#define atomic_signal_fence(order) \
    ((void)0)

#define atomic_is_lock_free(obj) 0

typedef intptr_t atomic_flag;
typedef intptr_t atomic_bool;
typedef intptr_t atomic_char;
typedef intptr_t atomic_schar;
typedef intptr_t atomic_uchar;
typedef intptr_t atomic_short;
typedef intptr_t atomic_ushort;
typedef intptr_t atomic_int;
typedef intptr_t atomic_uint;
typedef intptr_t atomic_long;
typedef intptr_t atomic_ulong;
typedef intptr_t atomic_llong;
typedef intptr_t atomic_ullong;
typedef intptr_t atomic_wchar_t;
typedef intptr_t atomic_int_least8_t;
typedef intptr_t atomic_uint_least8_t;
typedef intptr_t atomic_int_least16_t;
typedef intptr_t atomic_uint_least16_t;
typedef intptr_t atomic_int_least32_t;
typedef intptr_t atomic_uint_least32_t;
typedef intptr_t atomic_int_least64_t;
typedef intptr_t atomic_uint_least64_t;
typedef intptr_t atomic_int_fast8_t;
typedef intptr_t atomic_uint_fast8_t;
typedef intptr_t atomic_int_fast16_t;
typedef intptr_t atomic_uint_fast16_t;
typedef intptr_t atomic_int_fast32_t;
typedef intptr_t atomic_uint_fast32_t;
typedef intptr_t atomic_int_fast64_t;
typedef intptr_t atomic_uint_fast64_t;
typedef intptr_t atomic_intptr_t;
typedef intptr_t atomic_uintptr_t;
typedef intptr_t atomic_size_t;
typedef intptr_t atomic_ptrdiff_t;
typedef intptr_t atomic_intmax_t;
typedef intptr_t atomic_uintmax_t;

static inline void atomic_store(intptr_t *object, intptr_t desired)
{
    *object = desired;
    __machine_rw_barrier();
}

#define atomic_store_explicit(object, desired, order) \
    atomic_store(object, desired)

static inline intptr_t atomic_load(intptr_t *object)
{
    __machine_rw_barrier();
    return *object;
}

#define atomic_load_explicit(object, order) \
    atomic_load(object)

#define atomic_exchange(object, desired) \
    atomic_swap_ptr(object, desired)

#define atomic_exchange_explicit(object, desired, order) \
    atomic_exchange(object, desired)

static inline int atomic_compare_exchange_strong(intptr_t *object, intptr_t *expected,
                                                 intptr_t desired)
{
    intptr_t  old = *expected;
    *expected = atomic_cas_ptr(object, old, desired);
    return *expected == old;
}

#define atomic_compare_exchange_strong_explicit(object, expected, desired, success, failure) \
    atomic_compare_exchange_strong(object, expected, desired)

#define atomic_compare_exchange_weak(object, expected, desired) \
    atomic_compare_exchange_strong(object, expected, desired)

#define atomic_compare_exchange_weak_explicit(object, expected, desired, success, failure) \
    atomic_compare_exchange_weak(object, expected, desired)

static inline intptr_t atomic_fetch_add(intptr_t *object, intptr_t operand)
{
    return atomic_add_ptr_nv(object, operand) - operand;
}

#define atomic_fetch_sub(object, operand) \
    atomic_fetch_add(object, -(operand))

static inline intptr_t atomic_fetch_or(intptr_t *object, intptr_t operand)
{
    intptr_t old;
    do {
        old = atomic_load(object);
    } while (!atomic_compare_exchange_strong(object, old, old | operand));
    return old;
}

static inline intptr_t atomic_fetch_xor(intptr_t *object, intptr_t operand)
{
    intptr_t old;
    do {
        old = atomic_load(object);
    } while (!atomic_compare_exchange_strong(object, old, old ^ operand));
    return old;
}

static inline intptr_t atomic_fetch_and(intptr_t *object, intptr_t operand)
{
    intptr_t old;
    do {
        old = atomic_load(object);
    } while (!atomic_compare_exchange_strong(object, old, old & operand));
    return old;
}

#define atomic_fetch_add_explicit(object, operand, order) \
    atomic_fetch_add(object, operand)

#define atomic_fetch_sub_explicit(object, operand, order) \
    atomic_fetch_sub(object, operand)

#define atomic_fetch_or_explicit(object, operand, order) \
    atomic_fetch_or(object, operand)

#define atomic_fetch_xor_explicit(object, operand, order) \
    atomic_fetch_xor(object, operand)

#define atomic_fetch_and_explicit(object, operand, order) \
    atomic_fetch_and(object, operand)

#define atomic_flag_test_and_set(object) \
    atomic_exchange(object, 1)

#define atomic_flag_test_and_set_explicit(object, order) \
    atomic_flag_test_and_set(object)

#define atomic_flag_clear(object) \
    atomic_store(object, 0)

#define atomic_flag_clear_explicit(object, order) \
    atomic_flag_clear(object)

#endif /* COMPAT_ATOMICS_SUNCC_STDATOMIC_H */
