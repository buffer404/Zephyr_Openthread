/**
 * @file
 * @brief
 */

#ifndef ZEPHYR_INCLUDE_RADIO_CONTROLLER_H_
#define ZEPHYR_INCLUDE_RADIO_CONTROLLER_H_

#include <zephyr/device.h>
#include <zephyr/sys/crc.h>
#include <zephyr/types.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/zephyr.h>

#ifdef __cplusplus
extern "C"
{
#endif
	enum radio_device_action
	{
		radio_device_action_registration_complete,
		radio_device_action_set,
		radio_device_action_data,
	};

	enum radio_event_table
	{
		radio_registration_complete = BIT(1),
		radio_registration_requested  = BIT(2),
		radio_pin_state_changed  = BIT(3),
		radio_receive_packet  = BIT(4),
	};

	struct radio_data
	{
		void *data_ptr;
		size_t data_size;
	};

	typedef uint32_t radio_port_id;
	typedef void (*radio_device_callback_t)(const struct device *dev, uint32_t pin, enum radio_device_action action, void *data, size_t data_size);

	/**  @cond INTERNAL_HIDDEN */
	typedef int (*radio_controller_port_registration_t)(const struct device *dev, const struct device *port, radio_device_callback_t callback);
	typedef int (*radio_controller_pin_registration_t)(const struct device *dev, radio_port_id port_id, uint32_t pin);
	typedef int (*radio_controller_port_remove_t)(const struct device *dev, radio_port_id port_id);
	typedef int (*radio_controller_pin_remove_t)(const struct device *dev, radio_port_id port_id, uint32_t pin);
	typedef int (*radio_controller_port_set_t)(const struct device *dev, radio_port_id port_id, struct radio_data *data);
	typedef int (*radio_controller_pin_set_t)(const struct device *dev, radio_port_id port_id, uint32_t pin);
	typedef int (*radio_controller_get_events_pointer_t)(const struct device *dev, struct k_event **events_pointer);

	__subsystem struct radio_controller_api
	{
		radio_controller_port_registration_t port_registration;
		radio_controller_pin_registration_t pin_registration;
		radio_controller_port_remove_t port_remove;
		radio_controller_pin_remove_t pin_remove;
		radio_controller_port_set_t port_set;
		radio_controller_pin_set_t pin_set;
		radio_controller_get_events_pointer_t get_events_pointer;
	};

	/**
	 * @brief
	 *
	 * @param dev
	 * @param sub_dev
	 * @param type
	 *
	 * @return return port_id value or a negative error code on error
	 */
	__syscall int radio_controller_port_registration(const struct device *dev, const struct device *port, radio_device_callback_t callback);

	static inline int z_impl_radio_controller_port_registration(const struct device *dev, const struct device *port, radio_device_callback_t callback)
	{
		const struct radio_controller_api *api = dev->api;

		return api->port_registration(dev, port, callback);
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
	__syscall int radio_controller_pin_registration(const struct device *dev, radio_port_id port_id, uint32_t pin);

	static inline int z_impl_radio_controller_pin_registration(const struct device *dev, radio_port_id port_id, uint32_t pin)
	{
		const struct radio_controller_api *api = dev->api;

		return api->pin_registration(dev, port_id, pin);
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
	__syscall int radio_controller_port_remove(const struct device *dev, radio_port_id port_id);

	static inline int z_impl_radio_controller_port_remove(const struct device *dev, radio_port_id port_id)
	{
		const struct radio_controller_api *api = dev->api;

		return api->port_remove(dev, port_id);
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
	__syscall int radio_controller_pin_remove(const struct device *dev, radio_port_id port_id, uint32_t pin);

	static inline int z_impl_radio_controller_pin_remove(const struct device *dev, radio_port_id port_id, uint32_t pin)
	{
		const struct radio_controller_api *api = dev->api;

		return api->pin_remove(dev, port_id, pin);
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
	__syscall int radio_controller_port_set(const struct device *dev, radio_port_id port_id, struct radio_data *data);

	static inline int z_impl_radio_controller_port_set(const struct device *dev, radio_port_id port_id, struct radio_data *data)
	{
		const struct radio_controller_api *api = dev->api;

		return api->port_set(dev, port_id, data);
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
	__syscall int radio_controller_pin_set(const struct device *dev, radio_port_id port_id, uint32_t pin);

	static inline int z_impl_radio_controller_pin_set(const struct device *dev, radio_port_id port_id, uint32_t pin)
	{
		const struct radio_controller_api *api = dev->api;

		return api->pin_set(dev, port_id, pin);
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
	__syscall int radio_controller_get_events_pointer(const struct device *dev, struct k_event **events_pointer);

	static inline int z_impl_radio_controller_get_events_pointer(const struct device *dev, struct k_event **events_pointer)
	{
		const struct radio_controller_api *api = dev->api;

		return api->get_events_pointer(dev, events_pointer);
	}

	
#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#include <syscalls/radio_controller.h>

#endif /* ZEPHYR_INCLUDE_RADIO_CONTROLLER_H_ */
