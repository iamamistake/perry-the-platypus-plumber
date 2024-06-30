#include "commons/system_utils.h"

void system_utils_enable_interrupts(void)
{
    SREG |= (1 << SREG_I);
}

void system_utils_disable_interrupts(void)
{
    SREG &= ~(1 << SREG_I);
}
