/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(min_application, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   500

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

void main(void)
{
	gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);

	LOG_INF("Start cycle");
	while (1) {
		gpio_pin_set_dt(&led0, (int)1);
		k_msleep(SLEEP_TIME_MS);
		gpio_pin_set_dt(&led0, (int)0);
		
		gpio_pin_set_dt(&led1, (int)1);
		k_msleep(SLEEP_TIME_MS);
		gpio_pin_set_dt(&led1, (int)0);
		
		gpio_pin_set_dt(&led2, (int)1);
		k_msleep(SLEEP_TIME_MS);
		gpio_pin_set_dt(&led2, (int)0);
	}
}
