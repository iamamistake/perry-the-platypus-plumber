#include "commons/system_config.h"

void system_config_clock_init(void)
{
    system_utils_disable_interrupts();
    CLKPR = (1 << CLKPCE);
    CLKPR = SYSTEM_CONFIG_CLOCK_DESIRED_SETTING;
    system_utils_enable_interrupts();
}
