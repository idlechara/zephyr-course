#ifdef CONFIG_ENABLE_ASSIGNMENT_3_LOGIC
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <string.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define HEARTBEAT_THREAD_STACK_SIZE 512
#define HEARTBEAT_THREAD_PRIORITY 7

#define LED_NODE DT_ALIAS(assignment_3_led)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);


void heartbeat_thread_fn(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    if (!gpio_is_ready_dt(&led)) return;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return;

    /* Log configuration for testing */
    LOG_INF("=== LED Config ===");
    LOG_INF("Blink time: %d ms", CONFIG_LED_BLINKING_TIME_MILIS);
    LOG_INF("Brightness: %d%%", CONFIG_LED_BRIGHTNESS);
    LOG_INF("Fade duration: %d ms", CONFIG_LED_FADE_DURATION);
    #ifdef CONFIG_ENABLE_LED_DEBUGGING
        LOG_INF("Debug: ENABLED");
        LOG_INF("Custom pattern: %s", CONFIG_CUSTOM_BLINK_PATTERN);
    #endif

    while (1) {

        #ifdef CONFIG_ENABLE_EXPERT_SETTINGS
            /* Use custom pattern if expert settings enabled */
            static const char *pattern = CONFIG_CUSTOM_BLINK_PATTERN;
            static uint32_t pattern_len = 0;
            static uint32_t pattern_idx = 0;


            if (pattern_len == 0) pattern_len = strlen(pattern);

            bool state = (pattern[pattern_idx] == '1');
            pattern_idx = (pattern_idx + 1) % pattern_len;

            if (state) {
                gpio_pin_set_dt(&led, 1);
                if (CONFIG_ENABLE_LED_DEBUGGING) LOG_INF("LED ON");
            } else {
                gpio_pin_set_dt(&led, 0);
                if (CONFIG_ENABLE_LED_DEBUGGING) LOG_INF("LED OFF");
            }
            k_msleep(CONFIG_LED_FADE_DURATION);
        #else
            /* Default simple blink */
            if (gpio_pin_toggle_dt(&led) < 0) return;
            LOG_INF("LED toggle");
            k_msleep(CONFIG_LED_BLINKING_TIME_MILIS);
        #endif /* END CONFIG_ENABLE_EXPERT_SETTINGS */
    }
}

K_THREAD_DEFINE(heartbeat_tid, HEARTBEAT_THREAD_STACK_SIZE,
                heartbeat_thread_fn, NULL, NULL, NULL,
                HEARTBEAT_THREAD_PRIORITY, 0, 0);
#endif /* CONFIG_ENABLE_ASSIGNMENT_3_LOGIC */