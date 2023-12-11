#include <zephyr/init.h>

#include <stm32_ll_gpio.h>
#include <stm32_ll_rcc.h>
#include <stm32f1xx.h>

static int mco_pinPA8_init(const struct device *port) {
  
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT_50MHz);
  LL_GPIO_SetPinMode(GPIOE, LL_GPIO_PIN_15, LL_GPIO_MODE_OUTPUT_50MHz);
  LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_15);
  // LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
  /* LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_PLLCLK_DIV_2); */

  return 0;
}
SYS_INIT(mco_pinPA8_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);