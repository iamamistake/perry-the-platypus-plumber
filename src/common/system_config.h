#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

/* STANDARD INCLUDES */
#include <stdint.h>

/* LOCAL INCLUDES */
#include "avr/io.h"
#include "commons/system_utils.h"

/* ENUMERATIONS */
typedef enum
{
    SYSTEM_CONFIG_CLOCK_16MHZ = 0,
    SYSTEM_CONFIG_CLOCK_8MHZ,
    SYSTEM_CONFIG_CLOCK_4MHZ,
    SYSTEM_CONFIG_CLOCK_2MHZ,
    SYSTEM_CONFIG_CLOCK_1MHZ,
    SYSTEM_CONFIG_CLOCK_500KHZ,
    SYSTEM_CONFIG_CLOCK_250KHZ,
    SYSTEM_CONFIG_CLOCK_125KHZ,
    SYSTEM_CONFIG_CLOCK_62_5KHZ
} system_config_clock_e;

/* MACRO DEFINITIONS */
// Note: The fuse bits have already been programmed so as to source the clock from the on-board external 16MHz crystal oscillator
#define SYSTEM_CONFIG_CLOCK_SOURCE_BASE_FREQ        (16000000U)

// This setting can be changed by the user to effectively change the CPU core clock frequency
#define SYSTEM_CONFIG_CLOCK_DESIRED_SETTING         (SYSTEM_CONFIG_CLOCK_16MHZ)

#define SYSTEM_CONFIG_CPU_CORE_CLOCK_FREQ           (SYSTEM_CONFIG_CLOCK_SOURCE_BASE_FREQ/(1 << SYSTEM_CONFIG_CLOCK_DESIRED_SETTING))

/* FUNCTION PROTOTYPES */
void system_config_clock_init(void);

#endif /* SYSTEM_CONFIG_H */
