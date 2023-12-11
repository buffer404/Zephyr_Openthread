#ifndef __HDLC_ZEPHYR__
#define __HDLC_ZEPHYR__

#include <zephyr/device.h>
#include <zephyr/types.h>


typedef void (*hdlc_callback_t)(const struct device *dev, uint8_t *buf, uint32_t size);

int hdlc_send(const struct device * dev, uint8_t *buf, uint32_t size);
int hdlc_set_recv(const struct device *dev, hdlc_callback_t callback);

int hdlc_set_user_data(const struct device *dev, void* user_data);
void* hdlc_get_user_data(const struct device *dev);
#endif /* __HDLC_ZEPHYR__ */