#pragma once

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C"{
#endif

__subsystem struct idlechara_sensor_driver_api {
    int (*sample_fetch)(const struct device* dev,  enum sensor_channel chan);
    int (*channel_get)(const  struct device* dev, enum sensor_channel chan, struct sensor_value *val);
};

// even better

// __subsystem struct idlechara_sensor_api {
//     .sample_fetch = idlechara_sensor_sample_fetch,
//     .channel_get = idlechara_sensor_channel_get,
// };

struct idlechara_sensor_config {
    struct gpio_dt_spec pin;
};

struct idlechara_sensor_data {
    int state;
};


static inline int idlechara_sensor_sample_fetch(const struct device* dev, enum sensor_channel chan){
    return DEVICE_API_GET(idlechara_sensor, dev)->sample_fetch(dev, chan);
};
static inline int idlechara_sensor_channel_get(const struct device* dev, enum sensor_channel chan, struct sensor_value *val){
    return DEVICE_API_GET(idlechara_sensor, dev)->channel_get(dev, chan, val);
}


#ifdef __cplusplus
}
#endif