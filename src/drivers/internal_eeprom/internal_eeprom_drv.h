#ifndef INTERNAL_EEPROM_DRV_H
#define INTERNAL_EEPROM_DRV_H

/* STANDARD INCLUDES */
#include <stdint.h>

/* LOCAL INCLUDES */
#include "avr/io.h"
#include "common/system_utils.h"

/* FUNCTION PROTOTYPES */
void internal_eeprom_drv_write_byte(uint8_t *p_data, uint16_t addr);
void internal_eeprom_drv_read_byte(uint8_t *p_data, uint16_t addr);

#endif /* INTERNAL_EEPROM_DRV_H */
