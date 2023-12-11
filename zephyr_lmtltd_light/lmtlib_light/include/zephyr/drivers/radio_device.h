/**
 * @file
 * @brief
 */

#ifndef ZEPHYR_INCLUDE_RADIO_DEVICE_H_
#define ZEPHYR_INCLUDE_RADIO_DEVICE_H_

#include <zephyr/device.h>
#include <zephyr/sys/crc.h>
#include <zephyr/types.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/zephyr.h>

#ifdef __cplusplus
extern "C"
{
#endif

	enum radio_device_type
	{
		RADIO_NAN,
		RADIO_GPIO_START,
		RADIO_TDM_GPIO,
		RADIO_BASIC_GPIO,
		/* for new gpio */
		RADIO_GPIO_END = 0xFF,
		RADIO_SENSOR_START,
		RADIO_NOOLITE_SENSOR,
		/* for new sensors */
		RADIO_SENSOR_END = 0x1FE,
	};

	struct radio_packet
	{
		enum radio_device_type type;
		struct device *device;
		void *data;
		size_t data_len;
	};

	/**  @cond INTERNAL_HIDDEN */
	typedef int (*radio_device_receive_t)(const struct device *dev, bool bit, uint32_t length, bool registration, struct radio_packet *pkt_ptr);
	typedef int (*radio_device_get_tx_t)(const struct device *dev, struct radio_packet *pkt_ptr, uint32_t *value, uint32_t *length);
	typedef int (*radio_device_compare_t)(const struct device *dev, struct radio_packet *pkt_ptr0, struct radio_packet *pkt_ptr1);

	__subsystem struct radio_device_driver_api
	{
		radio_device_receive_t receive;
		radio_device_get_tx_t get_tx;
		radio_device_compare_t compare;
	};

	/**
	 * @brief
	 *
	 * @param dev
	 * @param bit
	 * @param length
	 *
	 * @return a negative error code on error
	 */
	__syscall int radio_device_receive(const struct device *dev, bool bit, uint32_t length, bool registration, struct radio_packet *pkt_ptr);

	static inline int z_impl_radio_device_receive(const struct device *dev, bool bit, uint32_t length, bool registration, struct radio_packet *pkt_ptr)
	{
		const struct radio_device_driver_api *api = dev->api;

		return api->receive(dev, bit, length, registration, pkt_ptr);
	}

	/**
	 * @brief
	 *
	 * @param dev
	 * @param sub_dev
	 * @param type
	 *
	 * @return a negative error code on error
	 */
	__syscall int radio_device_compare(const struct device *dev, struct radio_packet *pkt_ptr0, struct radio_packet *pkt_ptr1);

	static inline int z_impl_radio_device_compare(const struct device *dev, struct radio_packet *pkt_ptr0, struct radio_packet *pkt_ptr1)
	{
		const struct radio_device_driver_api *api = dev->api;

		return api->compare(dev, pkt_ptr0, pkt_ptr1);
	}

	/**
	 * @brief
	 *
	 * @param dev
	 * @param pkt_ptr
	 *
	 * @return a negative error code on error
	 */
	__syscall int radio_device_get_tx(const struct device *dev, struct radio_packet *pkt_ptr, uint32_t *value, uint32_t *length);
	
	static inline int z_impl_radio_device_get_tx(const struct device *dev, struct radio_packet *pkt_ptr, uint32_t *value, uint32_t *length)
	{
		const struct radio_device_driver_api *api = dev->api;

		return api->get_tx(dev, pkt_ptr, value, length);
	}
#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#include <syscalls/radio_device.h>

#endif /* ZEPHYR_INCLUDE_RADIO_DEVICE_H_ */
