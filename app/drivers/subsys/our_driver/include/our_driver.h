#pragma once

#include <zephyr/device.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C"{
#endif

__subsystem struct our_driver_api {
    int (*set_state)(const struct device* dev,  int state);
    int (*get_state)(const struct device* dev);
    int (*get_gpio)(const  struct device* dev);
};

static inline int our_driver_get_gpio(const struct device* dev) {
    return DEVICE_API_GET(our, dev)->get_gpio(dev);
};

static inline int our_driver_set_gpio(const struct device* dev) {
    return DEVICE_API_GET(our, dev)->get_gpio(dev);
};

static inline int our_driver_set_state(const struct device* dev, int state) {
    return DEVICE_API_GET(our, dev)->set_state(dev, state);
};

#ifdef __cplusplus
}
#endif