
/**
 * @file
 * @brief 
 */

#ifndef ZEPHYR_INCLUDE_RADIO_H_
#define ZEPHYR_INCLUDE_RADIO_H_

#include <zephyr/device.h>
#include <zephyr/sys/crc.h>
#include <zephyr/types.h>
#include <zephyr/sys/byteorder.h>
#include <drivers/radio_device.h>

#ifdef __cplusplus
extern "C" {
#endif

enum radio_driver_settings_type {
	RADIO_SETTING_FREQ,
	RADIO_SETTING_MODULATION,
	RADIO_SETTING_BW,
};

typedef void (*radio_rx_callback_t)(const struct device *dev, uint32_t *data, size_t length, void *user_data);

/**  @cond INTERNAL_HIDDEN */
typedef int (*radio_configure_t)(const struct device *dev, enum radio_driver_settings_type type, uint32_t value);
typedef int (*radio_rx_configure_t)(const struct device *dev, radio_rx_callback_t callback, void *user_data);
typedef int (*radio_tx_transmit_t)(const struct device *dev, uint32_t *data, size_t length);
typedef int (*radio_rx_enable_t)(const struct device *dev);
typedef int (*radio_tx_enable_t)(const struct device *dev);

__subsystem struct radio_driver_api {
	radio_configure_t configure;
	radio_rx_configure_t rx_configure;
	radio_tx_transmit_t transmit;
	radio_rx_enable_t rx_enable;
	radio_tx_enable_t tx_enable;
};


/**
 * @brief configure radio device
 *
 * @param dev radio device
 * @param type type of parameter
 * @param value parameter register
 *
 * @return a negative error code on error
 */
__syscall int radio_configure(const struct device *dev, enum radio_driver_settings_type type, uint32_t value);

static inline int z_impl_radio_configure(const struct device *dev, enum radio_driver_settings_type type, uint32_t value)
{
	const struct radio_driver_api *api = dev->api;

	return api->configure(dev, type, value);
}

/**
 * @brief 
 * 
 */
__syscall int radio_rx_configure(const struct device *dev, radio_rx_callback_t callback, void *user_data);

static inline int z_impl_radio_rx_configure(const struct device *dev, radio_rx_callback_t callback, void *user_data)
{
	const struct radio_driver_api *api = dev->api;

	return api->rx_configure(dev, callback, user_data);
}

/**
 * @brief 
 * 
 */
__syscall int radio_tx_transmit(const struct device *dev, uint32_t *data, size_t length);

static inline int z_impl_radio_tx_transmit(const struct device *dev, uint32_t *data, size_t length)
{
	const struct radio_driver_api *api = dev->api;

	return api->transmit(dev, data, length);
}

/**
 * @brief 
 * 
 */
__syscall int radio_rx_enable(const struct device *dev);

static inline int z_impl_radio_rx_enable(const struct device *dev)
{
	const struct radio_driver_api *api = dev->api;

	return api->rx_enable(dev);
}

/**
 * @brief 
 * 
 */
__syscall int radio_tx_enable(const struct device *dev);

static inline int z_impl_radio_tx_enable(const struct device *dev)
{
	const struct radio_driver_api *api = dev->api;

	return api->tx_enable(dev);
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#include <syscalls/radio.h>

#endif /* ZEPHYR_INCLUDE_RADIO_H_ */
