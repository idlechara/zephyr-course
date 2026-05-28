#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <idlechara_sensor.h>
#include <zephyr/shell/shell.h>

#define SLEEP_TIME_MS 500

static const struct device *my_sensor = DEVICE_DT_GET(DT_NODELABEL(idlechara_sensor));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

static int cmd_sensor_fetch(const struct shell *shell, size_t argc, char **argv)
{
    int rc = sensor_sample_fetch(my_sensor);
    if (rc <0) {
        shell_print(shell, "fetch did not succeed :c %d", rc);
        return -1;
    }
    shell_print(shell, "fetch done - led is on!");
    return 0;
}

static int cmd_sensor_read(const struct shell *shell, size_t argc, char **argv)
{
    struct sensor_value val;
    int rc = sensor_channel_get(my_sensor, SENSOR_CHAN_GREEN, &val);
    if (rc <0) {
        shell_print(shell, "get did not succeed :c %d", rc);
        return -1;
    }
    shell_print(shell, "get done - led is off!");
    return 0;
}

// command sensor with two subcomands, fetch and read 
static int cmd_sensor(const struct shell *shell, size_t argc, char **argv)
{
    if (argc < 2) {
        shell_print(shell, "Usage: sensor <fetch|read>");
        return -1;
    }

    shell_print(shell, "Sensor command received: %s", argv[1]);

    return 0;
}

static int cmd_sensor_info(const struct shell *shell, size_t argc, char **argv)
{
    shell_print(shell, "Device (sensor) Name: %s", my_sensor->name);
    shell_print(shell, "Ready state: %s", device_is_ready(my_sensor) ? "Ready" : "Not Ready");
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor, 
    SHELL_CMD(fetch, NULL, "Fetch sensor data", cmd_sensor_fetch),
    SHELL_CMD(read, NULL, "Read sensor data", cmd_sensor_read),
    SHELL_CMD(info, NULL, "Get sensor info", cmd_sensor_info),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Custom sensor commands", cmd_sensor);

int main(void)
{
    bool led_state = true;

    if(!device_is_ready(my_sensor)){
        return 0;
    }
    // while (1) {
    //     led_state = !led_state;
    //     int rc = sensor_sample_fetch(my_sensor);
    //     if (rc <0) { 
    //         LOG_ERR("fetch did not succeed :c %d", rc);
    //         k_msleep(SLEEP_TIME_MS);    
    //         continue;
    //     }
    //     // LOG_INF("fetch done - led is on!");
    //     k_msleep(SLEEP_TIME_MS);


    //     struct sensor_value val;
    //     rc = sensor_channel_get(my_sensor, SENSOR_CHAN_GREEN, &val);
    //     if (rc <0) { 
    //         LOG_ERR("get did not succeed :c %d", rc);
    //         k_msleep(SLEEP_TIME_MS);    
    //         continue;
    //     }
    //     // LOG_INF("get done - led is off!");
    //     k_msleep(SLEEP_TIME_MS);

    // }
    return 0;
}
