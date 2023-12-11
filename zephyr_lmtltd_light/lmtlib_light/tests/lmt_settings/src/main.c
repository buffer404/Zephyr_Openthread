/*
 * Copyright (c) 2022 Thomas Stranger
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/ztest.h>
#include <zephyr/lmt/settings.h>
#include "string.h"

void test_lmt_settings_basic(void)
{
    char msg[] = "value1";
    int len = strlen(msg) + 1;
    lmt_settings_save_key_value("key1", msg, len );
    char a[len];
    lmt_settings_get_key_value("key1", a, len);
    zassert_equal(a, msg, "key1 not equal key2");
}

void test_main(void)
{
	ztest_test_suite(lmt_settings, ztest_user_unit_test(test_lmt_settings_basic));

	ztest_run_test_suite(lmt_settings);
}
