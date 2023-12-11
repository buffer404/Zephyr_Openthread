/*
 * Copyright (c) 2022 Maxim Kolchurin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT zephyr_w1_stm32_tim

/**
 * @brief Driver for 1-Wire Master using STM32 TIM and DMA requests for
 controlling GPIO.
 * Principle of operation:
 * Use 2 DMA channel:
 * * 1 read IDR GPIO register
 * * 2 write bit to BSSR register
 * GPIO sets as Output; Open Drain
 *
 * Steps (exclude DMA and TIM configure steps):
 * 1. Set the time for reading to CCR1
 *    Set the time for writing to CCR2
 * 2. Write 0 to GPIO Output register
 * 3. Start DMA and Counter
 * When CCR1 or CCR2 occurs DMA request will write/read value to BSSR/IDR
 register;
 * 4. release sync semaphore in ISR (TIM Update event), stop DMA and counter
 * """
 *   ‾\___./‾‾‾‾‾.‾‾‾‾.
 *       BSSR   IDR  ARR
 *         ↑     ↓    ↓
 *        MEM   MEM  ISR
 * """
 * Buffer for DMA request (both channels) must be N+1 (N - bits count) to avoid
 DMA complete interrupt
 *

 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stm32_ll_tim.h>
#include <zephyr/drivers/clock_control/stm32_clock_control.h>
#include <zephyr/drivers/dma.h>
#include <zephyr/drivers/dma/dma_stm32.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/w1.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

LOG_MODULE_REGISTER(w1_stm32_tim, CONFIG_W1_LOG_LEVEL);

#define CLK_DIV 1000000
#define W1_1_LENGTH 6
#define W1_0_LENGTH 60

#define W1_READ_LENGTH_A 6
#define W1_READ_LENGTH_B 9

#define W1_SLOT_TIME 70
/*
 * Reset:
 *   ‾‾‾‾‾‾|\_____/|‾‾‾|\__:__/‾‾‾‾‾|
 *   RECOV.|   A   | B | RD|     C  |
 */
#define W1_RESET_RECOVERY 0
#define W1_RESET_A 480
#define W1_RESET_B 70
#define W1_RESET_C 410
#define W1_RESET_TIMEOUT 1000
struct stream {
  const struct device *dma_dev;
  uint32_t channel; /* stores the channel for dma or mux */
  struct dma_config dma_cfg;
  struct dma_block_config dma_blk_cfg;
  uint8_t priority;
  bool src_addr_increment;
  bool dst_addr_increment;
  int fifo_threshold;
};

struct w1_gpio_config {
  /** w1 controller config, common to all drivers */
  struct w1_master_config master_config;
  /** GPIO used for 1-Wire communication */
  struct gpio_dt_spec gpio_dt;
  TIM_TypeDef *timer;
  struct stm32_pclken pclken;

  uint32_t gpio_port;
  uint32_t pin;
  uint8_t channel_num;
  uint32_t chanel_reg;
  void (*tim_irq_enable)(TIM_TypeDef *TIMx);
  void (*tim_irq_disable)(TIM_TypeDef *TIMx);
  void (*cc_dma_req_enable)(TIM_TypeDef *TIMx);
  void (*cc_dma_req_disable)(TIM_TypeDef *TIMx);
  void (*enable_irq)(const struct device *dev);
};
struct w1_gpio_data {
  /** w1 controller data, common to all drivers */
  struct w1_master_data master_data;
  bool overdrive_active;

  /* tim clock */
  uint32_t tim_clk;
  /* dma */
  struct k_sem status_sem;
  volatile uint32_t status_flags;
  struct stream dma_rx;
  struct stream dma_tx;

  /* dma mem */
  volatile uint32_t bsrr[2];
  volatile uint32_t idr[2];
};

static inline int w1_gpio_configure_output(const struct gpio_dt_spec *spec) {
  int ret = gpio_pin_configure_dt(spec, GPIO_OUTPUT | GPIO_OPEN_DRAIN);
  gpio_pin_set_dt(spec, 1);
  return ret;
}

__attribute__((unused)) static inline int
w1_gpio_configure_input(const struct gpio_dt_spec *spec) {
  return gpio_pin_configure_dt(spec, GPIO_INPUT);
}

static void dma_callback(const struct device *dev, void *arg, uint32_t channel,
                         int status) {
  UNUSED(dev);
  UNUSED(arg);
  UNUSED(channel);
  UNUSED(status);
}

static void tim_stm32_isr_handler(const struct device *dev) {
  const struct w1_gpio_config *cfg = ((const struct device *)dev)->config;
  struct w1_gpio_data *data = ((const struct device *)dev)->data;

  LL_TIM_ClearFlag_UPDATE(cfg->timer);
  LL_TIM_ClearFlag_CC1(cfg->timer);
  LL_TIM_ClearFlag_CC2(cfg->timer);
  LL_TIM_ClearFlag_CC3(cfg->timer);
  LL_TIM_ClearFlag_CC4(cfg->timer);

  dma_stop(data->dma_tx.dma_dev, data->dma_tx.channel);
  dma_stop(data->dma_rx.dma_dev, data->dma_rx.channel);
  LL_TIM_DisableCounter(cfg->timer);
  LL_TIM_SetCounter(cfg->timer, 0);

  k_sem_give(&data->status_sem);
}

static int tim_stm32_dma_tx_load(const struct device *dev, const uint8_t *buf,
                                 size_t len) {
  struct w1_gpio_data *data = dev->data;
  const struct w1_gpio_config *cfg = dev->config;
  struct dma_block_config *blk_cfg;
  int ret;

  /* remember active TX DMA channel (used in callback) */
  struct stream *stream = &data->dma_tx;

  blk_cfg = &stream->dma_blk_cfg;

  /* prepare the block for this TX DMA channel */
  memset(blk_cfg, 0, sizeof(struct dma_block_config));
  blk_cfg->block_size = len;

  blk_cfg->source_address = (uint32_t)buf;
  blk_cfg->source_addr_adj = DMA_ADDR_ADJ_NO_CHANGE;
  blk_cfg->dest_address = (uint32_t) & ((GPIO_TypeDef *)(cfg->gpio_port))->BSRR;
  blk_cfg->dest_addr_adj = DMA_ADDR_ADJ_NO_CHANGE;

  /* give the fifo mode from the DT */
  blk_cfg->fifo_mode_control = data->dma_tx.fifo_threshold;

  /* direction is given by the DT */
  stream->dma_cfg.head_block = blk_cfg;
  /* give the client dev as arg, as the callback comes from the dma */
  stream->dma_cfg.user_data = (void *)dev;
  /* pass our client origin to the dma: data->dma_tx.dma_channel */
  stream->dma_cfg.complete_callback_en = 0;

  ret =
      dma_config(data->dma_tx.dma_dev, data->dma_tx.channel, &stream->dma_cfg);
  /* the channel is the actual stream from 0 */
  if (ret != 0) {
    return ret;
  }

  /* gives the request ID to the dma mux */
  return dma_start(data->dma_tx.dma_dev, data->dma_tx.channel);
}

static int tim_stm32_dma_rx_load(const struct device *dev, const uint8_t *buf,
                                 size_t len) {
  struct w1_gpio_data *data = dev->data;
  const struct w1_gpio_config *cfg = dev->config;
  struct dma_block_config *blk_cfg;
  int ret;

  /* retrieve active RX DMA channel (used in callback) */
  struct stream *stream = &data->dma_rx;

  blk_cfg = &stream->dma_blk_cfg;

  /* prepare the block for this RX DMA channel */
  memset(blk_cfg, 0, sizeof(struct dma_block_config));
  blk_cfg->block_size = len;

  blk_cfg->dest_address = (uint32_t)buf;
  blk_cfg->dest_addr_adj = DMA_ADDR_ADJ_NO_CHANGE;

  blk_cfg->source_address =
      (uint32_t) & ((GPIO_TypeDef *)(cfg->gpio_port))->IDR;
  blk_cfg->source_addr_adj = DMA_ADDR_ADJ_NO_CHANGE;

  /* give the fifo mode from the DT */
  blk_cfg->fifo_mode_control = data->dma_rx.fifo_threshold;

  /* direction is given by the DT */
  stream->dma_cfg.head_block = blk_cfg;
  stream->dma_cfg.user_data = (void *)dev;
  stream->dma_cfg.complete_callback_en = 0;

  /* pass our client origin to the dma: data->dma_rx.channel */
  ret =
      dma_config(data->dma_rx.dma_dev, data->dma_rx.channel, &stream->dma_cfg);
  /* the channel is the actual stream from 0 */
  if (ret != 0) {
    return ret;
  }

  /* gives the request ID to the dma mux */
  return dma_start(data->dma_rx.dma_dev, data->dma_rx.channel);
}

static int get_tim_clk(const struct stm32_pclken *pclken, uint32_t *tim_clk) {
  int r;
  const struct device *clk;
  uint32_t bus_clk, apb_psc;

  clk = DEVICE_DT_GET(STM32_CLOCK_CONTROL_NODE);

  r = clock_control_get_rate(clk, (clock_control_subsys_t *)pclken, &bus_clk);
  if (r < 0) {
    return r;
  }

#if defined(CONFIG_SOC_SERIES_STM32H7X)
  if (pclken->bus == STM32_CLOCK_BUS_APB1) {
    apb_psc = STM32_D2PPRE1;
  } else {
    apb_psc = STM32_D2PPRE2;
  }
#else
  if (pclken->bus == STM32_CLOCK_BUS_APB1) {
    apb_psc = STM32_APB1_PRESCALER;
  }
#if !defined(CONFIG_SOC_SERIES_STM32F0X) && !defined(CONFIG_SOC_SERIES_STM32G0X)
  else {
    apb_psc = STM32_APB2_PRESCALER;
  }
#endif
#endif

#if defined(RCC_DCKCFGR_TIMPRE) || defined(RCC_DCKCFGR1_TIMPRE) ||             \
    defined(RCC_CFGR_TIMPRE)
  /*
   * There are certain series (some F4, F7 and H7) that have the TIMPRE
   * bit to control the clock frequency of all the timers connected to
   * APB1 and APB2 domains.
   *
   * Up to a certain threshold value of APB{1,2} prescaler, timer clock
   * equals to HCLK. This threshold value depends on TIMPRE setting
   * (2 if TIMPRE=0, 4 if TIMPRE=1). Above threshold, timer clock is set
   * to a multiple of the APB domain clock PCLK{1,2} (2 if TIMPRE=0, 4 if
   * TIMPRE=1).
   */

  if (LL_RCC_GetTIMPrescaler() == LL_RCC_TIM_PRESCALER_TWICE) {
    /* TIMPRE = 0 */
    if (apb_psc <= 2u) {
      LL_RCC_ClocksTypeDef clocks;

      LL_RCC_GetSystemClocksFreq(&clocks);
      *tim_clk = clocks.HCLK_Frequency;
    } else {
      *tim_clk = bus_clk * 2u;
    }
  } else {
    /* TIMPRE = 1 */
    if (apb_psc <= 4u) {
      LL_RCC_ClocksTypeDef clocks;

      LL_RCC_GetSystemClocksFreq(&clocks);
      *tim_clk = clocks.HCLK_Frequency;
    } else {
      *tim_clk = bus_clk * 4u;
    }
  }
#else
  /*
   * If the APB prescaler equals 1, the timer clock frequencies
   * are set to the same frequency as that of the APB domain.
   * Otherwise, they are set to twice (×2) the frequency of the
   * APB domain.
   */
  if (apb_psc == 1u) {
    *tim_clk = bus_clk;
  } else {
    *tim_clk = bus_clk * 2u;
  }
#endif

  return 0;
}

static int tim_read_write_bit(const struct device *dev, uint32_t write_time,
                              bool *read_value, uint32_t read_time,
                              uint32_t total_time, k_timeout_t timeout) {
  const struct w1_gpio_config *cfg = dev->config;
  struct w1_gpio_data *data = dev->data;

  bool start_polarity = 0;
  bool isWriteOnly = read_value == NULL ? true : false;

  /* 0:15 - set; 16:31 - reset */
  data->bsrr[0] = BIT(cfg->pin);

  LL_TIM_SetAutoReload(cfg->timer, total_time);

  LL_TIM_EnableDMAReq_CC2(cfg->timer);
  LL_TIM_OC_SetCompareCH2(cfg->timer, write_time);
  data->bsrr[0] = BIT(cfg->pin);
  tim_stm32_dma_tx_load(dev, (const uint8_t *)data->bsrr, sizeof(data->bsrr));
  LL_TIM_CC_EnableChannel(cfg->timer, LL_TIM_CHANNEL_CH2);

  if (!isWriteOnly) {
    LL_TIM_EnableDMAReq_CC1(cfg->timer);
    LL_TIM_OC_SetCompareCH1(cfg->timer, read_time);
    data->idr[0] = 0;
    tim_stm32_dma_rx_load(dev, (const uint8_t *)data->idr, sizeof(data->idr));
    LL_TIM_CC_EnableChannel(cfg->timer, LL_TIM_CHANNEL_CH1);
  }

  w1_gpio_configure_output(&cfg->gpio_dt);
  gpio_pin_set_dt(&cfg->gpio_dt, start_polarity);

  LL_TIM_EnableCounter(cfg->timer);

  int ret = k_sem_take(&data->status_sem, timeout);

  w1_gpio_configure_output(&cfg->gpio_dt);

  if (!isWriteOnly) {
    *read_value = (data->idr[0] & BIT(cfg->pin)) ? 1 : 0;
    LL_TIM_CC_DisableChannel(cfg->timer, LL_TIM_CHANNEL_CH1);
    LL_TIM_DisableDMAReq_CC1(cfg->timer);
  }
  LL_TIM_CC_DisableChannel(cfg->timer, LL_TIM_CHANNEL_CH2);
  LL_TIM_DisableDMAReq_CC2(cfg->timer);

  return ret;
}

static int tim_write_bit(const struct device *dev, uint8_t bit) {
  uint32_t bit_length = (bit) ? W1_1_LENGTH : W1_0_LENGTH;
  return tim_read_write_bit(dev, bit_length, NULL, 0, W1_SLOT_TIME,
                            K_USEC(CONFIG_W1_ZEPHYR_STM32_TIM_BIT_TIMEOUT));
}

static int tim_read_bit(const struct device *dev, uint8_t *bit) {
  return tim_read_write_bit(dev, W1_READ_LENGTH_A, (bool *)bit,
                            W1_READ_LENGTH_A + W1_READ_LENGTH_B, W1_SLOT_TIME,
                            K_USEC(CONFIG_W1_ZEPHYR_STM32_TIM_BIT_TIMEOUT));
}

static int w1_gpio_reset_bus(const struct device *dev) {
  bool bit;
  int ret = tim_read_write_bit(dev, W1_RESET_A, &bit, W1_RESET_A + W1_RESET_B,
                               W1_RESET_A + W1_RESET_B + W1_RESET_C,
                               K_USEC(W1_RESET_TIMEOUT));
  if (ret != 0) {
    return ret;
  }
  return bit ? 0 : 1;
}

static int w1_tim_read_bit(const struct device *dev) {
  uint8_t bit = 0;
  int err = tim_read_bit(dev, &bit);
  return (err < 0) ? err : bit;
}

static int w1_tim_write_bit(const struct device *dev, const bool bit) {
  return tim_write_bit(dev, bit);
}

static int w1_gpio_read_byte(const struct device *dev) {
  uint8_t rx_byte = 0;
  uint8_t bit;
  int err;

  for (int i = 0; i < 8; i++) {
    bit = 0;
    err = tim_read_bit(dev, &bit);
    rx_byte |= (bit << i);
    if (err < 0) {
      return err;
    }
  }
  return rx_byte;
}

static int w1_gpio_write_byte(const struct device *dev, const uint8_t byte) {
  int err;

  for (int i = 0; i < 8; i++) {
    err = tim_write_bit(dev, ((byte & (0x1 << i)) >> i));
    if (err < 0) {
      return err;
    }
  }
  return 0;
}

static int w1_gpio_configure(const struct device *dev,
                             enum w1_settings_type type, uint32_t value) {
  const struct w1_gpio_config *cfg = dev->config;
  struct w1_gpio_data *data = dev->data;
  UNUSED(cfg);
  UNUSED(data);
  UNUSED(value);
  int ret;
  switch (type) {
  case W1_SETTING_SPEED:
    ret = 0;
    break;
  case W1_SETTING_STRONG_PULLUP:
  default:
    ret = -ENOTSUP;
  }
  return ret;
}

static int tim_stm32_init(const struct device *dev) {

  struct w1_gpio_data *data = dev->data;
  const struct w1_gpio_config *cfg = dev->config;

  const struct device *clk = DEVICE_DT_GET(STM32_CLOCK_CONTROL_NODE);

  int r = clock_control_on(clk, (clock_control_subsys_t *)&cfg->pclken);
  if (r < 0) {
    LOG_ERR("Could not initialize clock (%d)", r);
    return r;
  }

  r = get_tim_clk(&cfg->pclken, &data->tim_clk);
  if (r < 0) {
    LOG_ERR("Could not obtain timer clock (%d)", r);
    return r;
  }

  if (data->tim_clk <= CLK_DIV) {
    LOG_ERR("Timer freq is too slow, %d Hz", data->tim_clk);
    return -ENODEV;
  }

  LL_TIM_InitTypeDef init = {0};
  init.Prescaler = (data->tim_clk / CLK_DIV) - 1;
  init.CounterMode = LL_TIM_COUNTERMODE_UP;
  init.Autoreload = 0u;
  init.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(cfg->timer, &init);

  LL_TIM_DisableARRPreload(cfg->timer);
  LL_TIM_SetTriggerOutput(cfg->timer, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(cfg->timer);
  LL_TIM_SetUpdateSource(cfg->timer, LL_TIM_UPDATESOURCE_COUNTER);

  LL_TIM_OC_DisablePreload(cfg->timer, LL_TIM_CHANNEL_CH1);
  LL_TIM_OC_DisablePreload(cfg->timer, LL_TIM_CHANNEL_CH2);
  LL_TIM_CC_DisablePreload(cfg->timer);
  LL_TIM_EnableUpdateEvent(cfg->timer);
  LL_TIM_EnableIT_UPDATE(cfg->timer);
  LL_TIM_CC_SetDMAReqTrigger(cfg->timer, LL_TIM_CCDMAREQUEST_CC);

  /* TODO: ifdef(debug) */

#ifdef CONFIG_STM32H7
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_TIM3_STOP);
#elif CONFIG_SOC_STM32WB55XX
  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_TIM2_STOP);
  LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(LL_C2_DBGMCU_APB1_GRP1_TIM2_STOP);
#elif CONFIG_SOC_SERIES_STM32F4X
  LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_APB2_GRP1_TIM1_STOP);
#endif

  return 0;
}

static int w1_gpio_init(const struct device *dev) {
  const struct w1_gpio_config *cfg = dev->config;
  struct w1_gpio_data *data = dev->data;

  if (!device_is_ready(cfg->gpio_dt.port)) {
    LOG_ERR("Device %s is not ready", cfg->gpio_dt.port->name);
    return -ENODEV;
  }

  int ret = gpio_pin_configure_dt(&cfg->gpio_dt, GPIO_OPEN_DRAIN | GPIO_OUTPUT);

  if (ret < 0) {
    LOG_ERR("%d failed to configure %s pin %d", ret, cfg->gpio_dt.port->name,
            cfg->gpio_dt.pin);
    return -EINVAL;
  }

  data->overdrive_active = false;
  ret = tim_stm32_init(dev);
  if (ret != 0) {
    LOG_ERR("Failed to init stm32 timer, %d", ret);
    return -ENODEV;
  }
  cfg->enable_irq(dev);
  k_sem_reset(&data->status_sem);

  return 0;
}

static const struct w1_driver_api w1_gpio_driver_api = {
    .reset_bus = w1_gpio_reset_bus,
    .read_bit = w1_tim_read_bit,
    .write_bit = w1_tim_write_bit,
    .read_byte = w1_gpio_read_byte,
    .write_byte = w1_gpio_write_byte,
    .configure = w1_gpio_configure,
};

#define TIMER_NODE(inst) DT_INST_PHANDLE(inst, timer)

#define IRQ_CONFIG_FUNC(inst)                                                  \
  static void pwm_stm32_irq_config_func_##inst(const struct device *dev) {     \
    IRQ_CONNECT(DT_IRQ_BY_NAME(TIMER_NODE(inst), global, irq),                 \
                DT_IRQ(TIMER_NODE(inst), priority), tim_stm32_isr_handler,     \
                DEVICE_DT_INST_GET(inst), 0);                                  \
    irq_enable(DT_IRQ_BY_NAME(TIMER_NODE(inst), global, irq));                 \
  }
#define IRQ_INIT(inst) .enable_irq = pwm_stm32_irq_config_func_##inst,

#define DT_CLK(index, node)                                                    \
  { .bus = DT_CLOCKS_CELL(node, bus), .enr = DT_CLOCKS_CELL(node, bits) }

#define TIM_DMA_CHANNEL_INIT(index, dir, dir_cap, src_dev, dest_dev)           \
  .dma_dev = DEVICE_DT_GET(STM32_DMA_CTLR(index, dir)),                        \
  .channel = DT_INST_DMAS_CELL_BY_NAME(index, dir, channel),                   \
  .dma_cfg =                                                                   \
      {                                                                        \
          .dma_slot = STM32_DMA_SLOT(index, dir, slot),                        \
          .channel_direction = STM32_DMA_CONFIG_DIRECTION(                     \
              STM32_DMA_CHANNEL_CONFIG(index, dir)),                           \
          .source_data_size = STM32_DMA_CONFIG_##src_dev##_DATA_SIZE(          \
              STM32_DMA_CHANNEL_CONFIG(index, dir)),                           \
          .dest_data_size = STM32_DMA_CONFIG_##dest_dev##_DATA_SIZE(           \
              STM32_DMA_CHANNEL_CONFIG(index, dir)),                           \
          .source_burst_length = 1, /* SINGLE transfer */                      \
          .dest_burst_length = 1,   /* SINGLE transfer */                      \
          .channel_priority =                                                  \
              STM32_DMA_CONFIG_PRIORITY(STM32_DMA_CHANNEL_CONFIG(index, dir)), \
          .dma_callback = dma_callback,                                        \
          .block_count = 1,                                                    \
                                                                               \
  },                                                                           \
  .src_addr_increment = STM32_DMA_CONFIG_##src_dev##_ADDR_INC(                 \
      STM32_DMA_CHANNEL_CONFIG(index, dir)),                                   \
  .dst_addr_increment = STM32_DMA_CONFIG_##dest_dev##_ADDR_INC(                \
      STM32_DMA_CHANNEL_CONFIG(index, dir)),                                   \
  .fifo_threshold =                                                            \
      STM32_DMA_FEATURES_FIFO_THRESHOLD(STM32_DMA_FEATURES(index, dir)),

#define TIM_DMA_CHANNEL(id, dir, DIR, src, dest)                               \
  .dma_##dir = {COND_CODE_1(DT_INST_DMAS_HAS_NAME(id, dir),                    \
                            (TIM_DMA_CHANNEL_INIT(id, dir, DIR, src, dest)),   \
                            (NULL))},

#define TIM_DMA_STATUS_SEM(inst)                                               \
  .status_sem = Z_SEM_INITIALIZER(w1_gpio_data_##inst.status_sem, 0, 1),

#define REG_TIM_CHAN(ch)                                                       \
  .channel_num = ch, .chanel_reg = DT_CAT(LL_TIM_CHANNEL_CH, ch),              \
  .tim_irq_enable = LL_TIM_EnableIT_UPDATE,                                    \
  .tim_irq_disable = LL_TIM_DisableIT_UPDATE,                                  \
  .cc_dma_req_enable = DT_CAT(LL_TIM_EnableDMAReq_CC, ch),                     \
  .cc_dma_req_disable = DT_CAT(LL_TIM_DisableDMAReq_CC, ch)

#define W1_ZEPHYR_GPIO_INIT(inst)                                              \
  IRQ_CONFIG_FUNC(inst)                                                        \
  static const struct w1_gpio_config w1_gpio_cfg_##inst = {                    \
      .timer = (TIM_TypeDef *)DT_REG_ADDR(TIMER_NODE(inst)),                   \
      .pclken = DT_CLK(inst, TIMER_NODE(inst)),                                \
      .gpio_dt = GPIO_DT_SPEC_INST_GET_BY_IDX(inst, ctrl_gpios, 0),            \
      .master_config.slave_count = W1_INST_SLAVE_COUNT(inst),                  \
      REG_TIM_CHAN(DT_INST_PROP(inst, tim_channel)),                           \
      .gpio_port = DT_INST_PROP_BY_PHANDLE_IDX(inst, ctrl_gpios, 0, reg),      \
      .pin = DT_INST_GPIO_PIN_BY_IDX(inst, ctrl_gpios, 0),                     \
      IRQ_INIT(inst)};                                                         \
  static struct w1_gpio_data w1_gpio_data_##inst = {                           \
      TIM_DMA_CHANNEL(inst, rx, RX, PERIPHERAL, MEMORY)                        \
          TIM_DMA_CHANNEL(inst, tx, TX, MEMORY, PERIPHERAL)                    \
              TIM_DMA_STATUS_SEM(inst)};                                       \
  DEVICE_DT_INST_DEFINE(inst, &w1_gpio_init, NULL, &w1_gpio_data_##inst,       \
                        &w1_gpio_cfg_##inst, POST_KERNEL,                      \
                        CONFIG_W1_INIT_PRIORITY, &w1_gpio_driver_api);

DT_INST_FOREACH_STATUS_OKAY(W1_ZEPHYR_GPIO_INIT)
