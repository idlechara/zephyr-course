#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <idlechara_sensor.h>

#define SLEEP_TIME_MS 500

static const struct device *my_sensor = DEVICE_DT_GET(DT_NODELABEL(idlechara_sensor));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    bool led_state = true;

    if(!device_is_ready(my_sensor)){
        return 0;
    }
    while (1) {
        led_state = !led_state;
        int rc = sensor_sample_fetch(my_sensor);
        if (rc <0) { 
            LOG_ERR("fetch did not succeed :c %d", rc);
            k_msleep(SLEEP_TIME_MS);    
            continue;
        }
        LOG_INF("fetch done - led is on!");
        k_msleep(SLEEP_TIME_MS);


        struct sensor_value val;
        rc = sensor_channel_get(my_sensor, SENSOR_CHAN_GREEN, &val);
        if (rc <0) { 
            LOG_ERR("get did not succeed :c %d", rc);
            k_msleep(SLEEP_TIME_MS);    
            continue;
        }
        LOG_INF("get done - led is off!");
        k_msleep(SLEEP_TIME_MS);

    }
    return 0;
}
