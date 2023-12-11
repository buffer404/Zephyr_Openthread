#ifndef __ADG_708_H__
#define __ADG_708_H__
#include "zephyr/types.h"
#include "zephyr/device.h"

int adg708_reset(const struct device* dev);
int adg708_select_channel(const struct device* dev, uint32_t channel);

#endif //__ADG_708_H__