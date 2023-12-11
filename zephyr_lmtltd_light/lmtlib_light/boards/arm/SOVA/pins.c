#include <zephyr/init.h>
#include <stm32_ll_gpio.h>
#include <zephyr/kernel.h>


static int gpio_sub_init(const struct device *port) {
/*
При включении CONFIG_CLOCK_CONTROL, драйвер Zephyr (v2.7.99) инициализирует все
нужные регистры Master Clock Output 1 (MCO1), кроме записи в регистр
GPIOA->MODER8 (регистр для настройки выхода PA8) режима Alternate function mode.
Поэтому запись производится вручную ниже. MCO1 - PA8 - Ethernet PHY clock в
SOVA427; MCO2 - PC9 - не используется в SOVA427;
*/
#ifndef CONFIG_NET_L2_ETHERNET
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
#endif
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_11, LL_GPIO_MODE_INPUT);

//#ifdef CONFIG_ADC_ADS869X
//  LL_GPIO_SetPinMode(GPIOE, LL_GPIO_PIN_15, LL_GPIO_MODE_OUTPUT);
//  LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_15);
//  // k_busy_wait(1);
//  LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_15);
//  LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_15);
//#endif
  return 0;
}
SYS_INIT(gpio_sub_init, POST_KERNEL, 48);