#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <our_driver.h>

#define SLEEP_TIME_MS 500

static const struct device *our_device = DEVICE_DT_GET_ANY(our_driver);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    bool led_state = true;

    if(!device_is_ready(our_device)){
        return 0;
    }
    while (1) {
        led_state = !led_state;
        our_driver_set_state(our_device, led_state);
        LOG_INF("LED state - new : %s", led_state ? "ON" : "OFF");
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}
