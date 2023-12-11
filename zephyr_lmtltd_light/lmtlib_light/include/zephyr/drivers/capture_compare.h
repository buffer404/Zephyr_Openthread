
/**
 * @file
 * @brief
 */

#ifndef ZEPHYR_INCLUDE_RADIO_H_
#define ZEPHYR_INCLUDE_RADIO_H_

#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/sys_clock.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef void (*cc_callback_t)(const struct device *dev, void *buf, size_t len, void *user_data);

	struct capture_config_t
	{
		bool circle_capture : 1;
		bool half_transfer_callback : 1;
	};

	/**  @cond INTERNAL_HIDDEN */
	typedef int (*cc_transmit_t)(const struct device *dev, void *buf, size_t len, k_timeout_t timeout);
	typedef int (*cc_transmit_async_t)(const struct device *dev, void *buf, size_t len, cc_callback_t cb);
	typedef int (*cc_receive_configure_t)(const struct device *dev, struct capture_config_t config, void *buf, size_t len, cc_callback_t cb, void *user_data);
	typedef int (*cc_receive_enable_t)(const struct device *dev);
	typedef int (*cc_receive_disable_t)(const struct device *dev);
	typedef int (*cc_receive_pause_t)(const struct device *dev);
	typedef int (*cc_receive_resume_t)(const struct device *dev);

	__subsystem struct cc_capture_compare_api
	{
		cc_transmit_t transmit;
		cc_transmit_async_t transmit_async;
		cc_receive_configure_t receive_configure;
		cc_receive_enable_t receive_enable;
		cc_receive_disable_t receive_disable;
		cc_receive_pause_t receive_pause;
		cc_receive_resume_t receive_resume;
	};

	/**
	 * @brief
	 *
	 * @param
	 *
	 * @return a negative error code on error
	 */
	__syscall int cc_transmit(const struct device *dev, uint32_t *buf, size_t len, k_timeout_t timeout);

	static inline int z_impl_cc_transmit(const struct device *dev, uint32_t *buf, size_t len, k_timeout_t timeout)
	{
		const struct cc_capture_compare_api *api = dev->api;

		return api->transmit(dev, buf, len, timeout);
	}

	/**
	 * @brief
	 *
	 * @param
	 *
	 * @return a negative error code on error
	 */
	__syscall int cc_transmit_async(const struct device *dev, uint32_t *buf, size_t len, cc_callback_t cb);

	static inline int z_impl_cc_transmit_async(const struct device *dev, uint32_t *buf, size_t len, cc_callback_t cb)
	{
		const struct cc_capture_compare_api *api = dev->api;

		return api->transmit_async(dev, buf, len, cb);
	}

	/**
	 * @brief
	 *
	 * @param
	 *
	 * @return a negative error code on error
	 */
	__syscall int cc_receive_configure(const struct device *dev, struct capture_config_t config, uint32_t *buf, size_t len, cc_callback_t cb, void *user_data);

	static inline int z_impl_cc_receive_configure(const struct device *dev, struct capture_config_t config, uint32_t *buf, size_t len, cc_callback_t cb, void *user_data)
	{
		const struct cc_capture_compare_api *api = dev->api;

		return api->receive_configure(dev, config, buf, len, cb, user_data);
	}

	/**
	 * @brief
	 *
	 * @param
	 *
	 * @return a negative error code on error
	 */
	__syscall int cc_receive_enable(const struct device *dev);

	static inline int z_impl_cc_receive_enable(const struct device *dev)
	{
		const struct cc_capture_compare_api *api = dev->api;

		return api->receive_enable(dev);
	}
#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#include <syscalls/capture_compare.h>

#endif /* ZEPHYR_INCLUDE_RADIO_H_ */
