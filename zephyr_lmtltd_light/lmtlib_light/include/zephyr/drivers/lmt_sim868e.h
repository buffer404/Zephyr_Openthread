
#ifndef ZEPHYR_INCLUDE_DRIVERS_LMTSIM868E_H_
#define ZEPHYR_INCLUDE_DRIVERS_LMTSIM868E_H_

#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/sys/byteorder.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*lmtmdm_restart_t)(const struct device *dev);

__subsystem struct lmtmodem_driver_api {
	lmtmdm_restart_t restart;
};


#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_LMTSIM868E_H_ */
