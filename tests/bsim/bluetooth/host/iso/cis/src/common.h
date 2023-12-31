/*
 * Common functions and helpers for ISO tests
 *
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>

#include <zephyr/sys/atomic.h>

#include "bs_types.h"
#include "bs_tracing.h"
#include "bstests.h"

#define CREATE_FLAG(flag) static atomic_t flag = (atomic_t) false
#define SET_FLAG(flag)    (void)atomic_set(&flag, (atomic_t) true)
#define UNSET_FLAG(flag)  (void)atomic_set(&flag, (atomic_t) false)
#define TEST_FLAG(flag)   (atomic_get(&flag) == (atomic_t) true)
#define WAIT_FOR_FLAG_SET(flag)                                                                    \
	while (!(bool)atomic_get(&flag)) {                                                         \
		(void)k_sleep(K_MSEC(1));                                                          \
	}
#define WAIT_FOR_FLAG_UNSET(flag)                                                                  \
	while ((bool)atomic_get(&flag)) {                                                          \
		(void)k_sleep(K_MSEC(1));                                                          \
	}

#define WAIT_TIME (30e6) /* 30 seconds*/

#define FAIL(...)                                                                                  \
	do {                                                                                       \
		bst_result = Failed;                                                               \
		bs_trace_error_time_line(__VA_ARGS__);                                             \
	} while (0)

#define PASS(...)                                                                                  \
	do {                                                                                       \
		bst_result = Passed;                                                               \
		bs_trace_info_time(1, __VA_ARGS__);                                                \
	} while (0)

extern struct bt_conn *default_conn;
extern atomic_t flag_connected;
extern atomic_t flag_conn_updated;

void test_init(void);
void test_tick(bs_time_t HW_device_time);
