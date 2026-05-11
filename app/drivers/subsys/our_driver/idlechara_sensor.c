#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <idlechara_sensor.h>

#define DT_DRV_COMPAT idlechara_sensor

LOG_MODULE_REGISTER(idlechara_sensor, LOG_LEVEL_INF);

static int idlechara_sensor_init(const struct device* dev){
    const struct idlechara_sensor_config *config = dev->config;
    int ret;

    if(!gpio_is_ready_dt(&config->pin)){
        return -ENODEV;
    }
    ret = gpio_pin_configure_dt(&config->pin, GPIO_OUTPUT_INACTIVE);
    if(ret < 0){
        return ret;
    }
    if(IS_ENABLED(CONFIG_IDLECHARA_SENSOR_INIT_STATE)){
        idlechara_sensor_set_state(dev, 1);
    }
    return 0;
}

static int idlechara_sensor_sample_fetch_impl(const struct device* dev, enum sensor_channel chan) {
    if(chan != SENSOR_CHAN_GREEN && chan != SENSOR_CHAN_ALL) return -ENOTSUP; // Do not support other cases :ccc

    const struct idlechara_sensor_config *config = dev->config;
    struct idlechara_sensor_data *data = dev->data;

    gpio_pin_set_dt(&config->pin, 1); // turn on

    return 0;
};

static int idlechara_sensor_channel_get_impl(const struct device* dev, enum sensor_channel chan, struct sensor_value *val) {
    // only one channel at a time
    if ( chan != SENSOR_CHAN_GREEN) return -ENOTSUP;

    const struct idlechara_sensor_config *config = dev->config;
    struct idlechara_sensor_data *data = dev->data;

    gpio_pin_set_dt(&config->pin, 0);

    // According to the spec, this should return a value
    val->val1 = data->state;
    val->val2 = 0;

    return 0;
};


static DEVICE_API(sensor, idlechara_sensor_driver_api)  = {
    .channel_get = idlechara_sensor_channel_get_impl,
    .sample_fetch = idlechara_sensor_sample_fetch_impl,
};



#define IDLECHARA_SENSOR_DEFINE(n)                                         \
    static struct idlechara_sensor_data idlechara_sensor_data_##n;               \
    static const struct idlechara_sensor_config idlechara_sensor_config_##n = {  \
        .pin = GPIO_DT_SPEC_INST_GET(n, pin),                        \
    };                                                               \
    DEVICE_DT_INST_DEFINE(n, idlechara_sensor_init, NULL,                  \
        &idlechara_sensor_data_##n, &idlechara_sensor_config_##n,                \
        POST_KERNEL, CONFIG_GPIO_INIT_PRIORITY,                      \
        &idlechara_sensor_driver_api);

DT_INST_FOREACH_STATUS_OKAY(IDLECHARA_SENSOR_DEFINE)