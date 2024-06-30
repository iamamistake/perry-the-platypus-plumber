#include "drivers/internal_eeprom/internal_eeprom_drv.h"

void internal_eeprom_drv_write_byte(uint8_t *p_data, uint16_t addr)
{
    while (EECR & (1 << EEPE));

    EEARH = (uint8_t)(addr >> 8);
    EEARL = (uint8_t)(addr);

    EEDR = *p_data;

    system_utils_disable_interrupts();
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
    system_utils_enable_interrupts();
}

void internal_eeprom_drv_read_byte(uint8_t *p_data, uint16_t addr)
{
    while (EECR & (1 << EEPE));

    EEARH = (uint8_t)(addr >> 8);
    EEARL = (uint8_t)(addr);

    EECR |= (1 << EERE);
    *p_data = EEDR;
}