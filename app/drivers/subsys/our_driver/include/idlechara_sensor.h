#pragma once

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C"{
#endif


struct  idlechara_sensor_driver_api{
    struct sensor_driver_api sensor;
    int (*set_data)(const struct device* dev, int data);
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
    return ((const struct idlechara_sensor_driver_api *)dev->api)->sensor.sample_fetch(dev, chan);
};
static inline int idlechara_sensor_channel_get(const struct device* dev, enum sensor_channel chan, struct sensor_value *val){
    return ((const struct idlechara_sensor_driver_api *)dev->api)->sensor.channel_get(dev, chan, val);
}
static inline int idlechara_sensor_set_data(const struct device* dev, int data){
    return ((const struct idlechara_sensor_driver_api *)dev->api)->set_data(dev,data);
}


#ifdef __cplusplus
}
#endif