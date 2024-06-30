#include "drivers/uart/uart_drv.h"

static bool uart_drv_transmit_in_progress = false;
static uart_drv_event_handlers_t uart_drv_event_handlers = {.uart_drv_transmit_cplt_handler = NULL,
                                                            .uart_drv_receive_cplt_handler = NULL};

void uart_drv_init(uart_drv_init_params_t *init_params)
{
    const uint32_t baud_rate_prescaler = ((SYSTEM_CONFIG_CPU_CORE_CLOCK_FREQ/16)/(init_params->baud_rate)) - 1;

    UBRR0H = (uint8_t)(baud_rate_prescaler >> 8);
    UBRR0L = (uint8_t)(baud_rate_prescaler);

    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << TXCIE0) | (1 << RXCIE0);
    UCSR0C = (init_params->data_frame_params.data_bits_num << UCSZ00) |
             (init_params->data_frame_params.stop_bits <<  USBS0) |
             (init_params->data_frame_params.parity_status << UPM01) |
             ((init_params->data_frame_params.parity_status && init_params->data_frame_params.parity_mode) << UPM00);

    uart_drv_event_handlers = init_params->event_handlers;

    scheduler_init();
}

void uart_drv_trigger_transmit(uint8_t data)
{
    while (uart_drv_transmit_in_progress);
    uart_drv_transmit_in_progress = true;
    UDR0 = data;
}

ISR(USART_TX_vect)
{
    UCSR0A |= (1 << TXC0);
    uart_drv_transmit_in_progress = false;

    if (uart_drv_event_handlers.uart_drv_transmit_cplt_handler)
    {
        scheduler_event_put(NULL, 0, uart_drv_event_handlers.uart_drv_transmit_cplt_handler);
    }
}

ISR(USART_RX_vect)
{
    uart_drv_event_data_t event_data = {.data = UDR0};

    if (uart_drv_event_handlers.uart_drv_receive_cplt_handler)
    {
        scheduler_event_put(&event_data, sizeof(event_data), uart_drv_event_handlers.uart_drv_receive_cplt_handler);
    }
}