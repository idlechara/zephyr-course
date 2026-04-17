#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "assignment_3.h" // Surprise! (reminder to self, check kconfig)

/* The devicetree node identifier for the "app-led" alias. */
#define APP_LED DT_ALIAS(app_led) // damm this thing is case sensitive
static const struct gpio_dt_spec app_led = GPIO_DT_SPEC_GET(APP_LED, gpios);


int main(void)
{
    if (!gpio_is_ready_dt(&app_led)) return 0;
    if (gpio_pin_configure_dt(&app_led, GPIO_OUTPUT_ACTIVE) < 0) return 0;
    static bool app_led_state = false;

    while (1) {
        app_led_state = !app_led_state;
        gpio_pin_set_dt(&app_led, app_led_state);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
