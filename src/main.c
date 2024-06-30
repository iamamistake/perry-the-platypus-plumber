#include "main.h"

int main(void)
{
    system_config_clock_init();
    watchdog_drv_init(WATCHDOG_DRV_TIMEOUT_DURATION_1S);

    user_application_init();

    while (1)
    {
        watchdog_drv_feed();
        user_application_run();
    }

    return 0;
}