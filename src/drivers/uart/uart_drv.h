#ifndef UART_DRV_H
#define UART_DRV_H

/* STANDARD INCLUDES */
#include <stdbool.h>
#include <stdint.h>

/* LOCAL INCLUDES */
#include "avr/io.h"
#include "avr/interrupt.h"
#include "common/system_config.h"
#include "components/scheduler/scheduler.h"

/* CALLBACK HANDLER TYPEDEFS  */
typedef void (*uart_drv_transmit_cplt_handler_t)(void *p_event_data, uint8_t event_data_size);
typedef void (*uart_drv_receive_cplt_handler_t)(void *p_event_data, uint8_t event_data_size);

/* ENUMERATIONS */
typedef enum
{
    UART_DRV_DATA_BITS_5 = 0,
    UART_DRV_DATA_BITS_6,
    UART_DRV_DATA_BITS_7,
    UART_DRV_DATA_BITS_8,
} uart_drv_data_bits_e;

typedef enum
{
    UART_DRV_PARITY_MODE_EVEN = 0,
    UART_DRV_PARITY_MODE_ODD
} uart_drv_parity_mode_e;

typedef enum
{
    UART_DRV_PARITY_STATUS_DISABLED = 0,
    UART_DRV_PARITY_STATUS_ENABLED
} uart_drv_parity_status_e;

typedef enum
{
    UART_DRV_STOP_BITS_1 = 0,
    UART_DRV_STOP_BITS_2
} uart_drv_stop_bits_e;

/* STRUCTURES */
typedef struct
{
    uart_drv_transmit_cplt_handler_t uart_drv_transmit_cplt_handler;
    uart_drv_receive_cplt_handler_t uart_drv_receive_cplt_handler;
} uart_drv_event_handlers_t;

typedef struct __attribute__((packed))
{
    uint32_t baud_rate;
    struct __attribute__((packed))
    {
        uart_drv_data_bits_e data_bits_num      : 2;
        uart_drv_parity_status_e parity_status  : 1;
        uart_drv_parity_mode_e parity_mode      : 1;
        uart_drv_stop_bits_e stop_bits          : 1;
    } data_frame_params;
    uart_drv_event_handlers_t event_handlers;
} uart_drv_init_params_t;

typedef struct __attribute__((packed))
{
    uint8_t data;
} uart_drv_event_data_t;

/* FUNCTION PROTOTYPES */
void uart_drv_init(uart_drv_init_params_t *init_params);
void uart_drv_trigger_transmit(uint8_t data);

#endif /* UART_DRV_H */
