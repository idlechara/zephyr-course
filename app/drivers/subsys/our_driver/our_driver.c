#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include <our_driver.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_config {
    struct gpio_dt_spec pin;
};

struct our_driver_data {
    int state;
};

static int our_driver_init(const struct device* dev){
    const struct our_driver_config *config = dev->config;
    int ret;

    if(!gpio_is_ready_dt(&config->pin)){
        return -ENODEV;
    }
    ret = gpio_pin_configure_dt(&config->pin, GPIO_OUTPUT_INACTIVE);
    if(ret < 0){
        return ret;
    }
    if(IS_ENABLED(CONFIG_OUR_DRIVER_INIT_STATE)){
        our_driver_set_state(dev, 1);
    }
    return 0;
}

int our_driver_get_gpio_impl(const struct device* dev){
    const struct our_driver_config* config = dev->config;
    return config->pin.pin; 
}

int our_driver_get_state_impl(const struct device* dev){
    const struct our_driver_config *config = dev->config;
    return gpio_pin_get_dt(&config->pin);
}

int our_driver_set_state_impl(const struct device* dev, int state){
    const struct our_driver_config *config = dev->config;
    struct our_driver_data *data = dev->data;
    data->state = state;
    return gpio_pin_set_dt(&config->pin, state);
}

static const struct our_driver_api our_driver_api = {
    .set_state = our_driver_set_state_impl,
    .get_state = our_driver_get_state_impl,
    .get_gpio  = our_driver_get_gpio_impl,
};

#define OUR_DRIVER_DEFINE(n)                                         \
    static struct our_driver_data our_driver_data_##n;               \
    static const struct our_driver_config our_driver_config_##n = {  \
        .pin = GPIO_DT_SPEC_INST_GET(n, pin),                        \
    };                                                               \
    DEVICE_DT_INST_DEFINE(n, our_driver_init, NULL,                  \
        &our_driver_data_##n, &our_driver_config_##n,                \
        POST_KERNEL, CONFIG_GPIO_INIT_PRIORITY,                      \
        &our_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE)