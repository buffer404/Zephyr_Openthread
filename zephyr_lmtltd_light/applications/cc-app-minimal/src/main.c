
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include <zephyr/logging/log.h>
#include <zephyr/net/ieee802154_radio.h>
#include <zephyr/net/openthread.h>
LOG_MODULE_REGISTER(min_application, LOG_LEVEL_INF);

int main()
{
	openthread_start(openthread_get_default_context());
}
