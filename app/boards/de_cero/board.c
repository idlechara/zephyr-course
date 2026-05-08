#include <zephyr/init.h>
#include <zephyr/kernel.h>

static int board_de_cero_init(void)
{
    /* Board-specific initialization can be added here if needed */
    printk("Board Initialized\n");
    return 0;
}

SYS_INIT(board_de_cero_init, APPLICATION, 0);