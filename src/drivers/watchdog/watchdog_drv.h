#ifndef WATCHDOG_DRV_H
#define WATCHDOG_DRV_H

/* STANDARD INCLUDES */

/* LOCAL INCLUDES */
#include "avr/io.h"
#include "common/system_utils.h"
#include "drivers/watchdog/watchdog_drv.h"


/* MACRO FUNCTION DEFINITIONS */
#define watchdog_drv_feed() __asm__ __volatile__ ("wdr")

/* ENUMERATIONS */
typedef enum
{
    WATCHDOG_DRV_TIMEOUT_DURATION_16MS = 0,
    WATCHDOG_DRV_TIMEOUT_DURATION_32MS,
    WATCHDOG_DRV_TIMEOUT_DURATION_64MS,
    WATCHDOG_DRV_TIMEOUT_DURATION_125MS,
    WATCHDOG_DRV_TIMEOUT_DURATION_250MS,
    WATCHDOG_DRV_TIMEOUT_DURATION_500MS,
    WATCHDOG_DRV_TIMEOUT_DURATION_1S,
    WATCHDOG_DRV_TIMEOUT_DURATION_2S,
    WATCHDOG_DRV_TIMEOUT_DURATION_4S,
    WATCHDOG_DRV_TIMEOUT_DURATION_8S
} watchdog_drv_timeout_duration_e;

/* FUNCTION PROTOTYPES */
void watchdog_drv_init(watchdog_drv_timeout_duration_e timeout_duration);

#endif /* WATCHDOG_DRV_H */
