#include "drivers/watchdog/watchdog_drv.h"

void watchdog_drv_init(watchdog_drv_timeout_duration_e timeout_duration)
{
    watchdog_drv_feed();

    system_utils_disable_interrupts();
    WDTCSR |= (1 << WDCE);
    WDTCSR |=  (1 << WDE) |
               (timeout_duration & ((1 << WDP0) | (1 << WDP1) | (1 << WDP2))) |
               ((timeout_duration >> 3) << WDP3);
    WDTCSR &= ~(1 << WDIE);
    system_utils_enable_interrupts();
}