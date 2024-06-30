#ifndef USER_APPLICATION_H
#define USER_APPLICATION_H

/* STANDARD INCLUDES */
#include <stdint.h>

/* LOCAL INCLUDES */
#include "components/scheduler/scheduler.h"
#include "drivers/uart/uart_drv.h"
#include "drivers/internal_eeprom/internal_eeprom_drv.h"

/* MACRO DEFINITIONS */
// This flag can be enabled to simulate an EEPROM memory in the system RAM instead (used for debugging purposes only)
#define USER_APPLICATION_SIMULATE_EEPROM                    (0)

#define USER_APPLICATION_MAX_LOOPBACK_PACKET_SIZE           (72)

/* ENUMERATIONS */
typedef enum
{
    USER_APPLICATION_STATE_MACHINE_STATE_RECEPTION = 0,
    USER_APPLICATION_STATE_MACHINE_STATE_TRANSMISSION
} user_application_state_machine_state_e;

typedef enum
{
    USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_RECEIVED_DATA = 0,
    USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_INTERNAL,
    USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_TRANSMITTED_DATA
} user_application_state_machine_event_type_e;

/* STRUCTURES */
typedef struct __attribute__((packed))
{
    user_application_state_machine_event_type_e type;
    uint8_t data;
} user_application_state_machine_event_data_t;

/* FUNCTION PROTOTYPES */
void user_application_init(void);
void user_application_run(void);

#endif /* USER_APPLICATION_H */
