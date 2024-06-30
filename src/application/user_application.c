#include "application/user_application.h"

static void user_application_uart_transmit_event_callback(void *p_event_data, uint8_t event_data_size);
static void user_application_uart_receive_event_callback(void *p_event_data, uint8_t event_data_size);
static void user_application_state_machine_event_handler(void *p_event_data, uint8_t event_data_size);

void user_application_init(void)
{
    uart_drv_init_params_t app_uart_init_params = {.baud_rate = 2400,
                                                   .data_frame_params = {.data_bits_num = UART_DRV_DATA_BITS_8,
                                                                         .parity_status = UART_DRV_PARITY_STATUS_DISABLED,
                                                                         .stop_bits = UART_DRV_STOP_BITS_1},
                                                   .event_handlers = {.uart_drv_transmit_cplt_handler = user_application_uart_transmit_event_callback,
                                                                      .uart_drv_receive_cplt_handler = user_application_uart_receive_event_callback}};
    uart_drv_init(&app_uart_init_params);
    scheduler_init();
}

void user_application_run(void)
{
    scheduler_execute();
}

static void user_application_uart_transmit_event_callback(void *p_event_data, uint8_t event_data_size)
{
    user_application_state_machine_event_data_t event_data = {.type = USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_TRANSMITTED_DATA};
    user_application_state_machine_event_handler(&event_data, sizeof(event_data));
}

static void user_application_uart_receive_event_callback(void *p_event_data, uint8_t event_data_size)
{
    user_application_state_machine_event_data_t event_data = {.type = USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_RECEIVED_DATA,
                                                              .data = ((uart_drv_event_data_t *)(p_event_data))->data};
    user_application_state_machine_event_handler(&event_data, sizeof(event_data));
}

static void user_application_state_machine_event_handler(void *p_event_data, uint8_t event_data_size)
{
    static user_application_state_machine_state_e user_application_state_machine_state = USER_APPLICATION_STATE_MACHINE_STATE_RECEPTION;
    static uint16_t current_loopback_cache_index = 0;

    #if USER_APPLICATION_SIMULATE_EEPROM
    static uint8_t user_application_simulated_eeprom[USER_APPLICATION_MAX_LOOPBACK_PACKET_SIZE];
    #endif

    user_application_state_machine_event_data_t *event_data = (user_application_state_machine_event_data_t *)(p_event_data);

    switch (user_application_state_machine_state)
    {
        case USER_APPLICATION_STATE_MACHINE_STATE_RECEPTION:
        {
            switch (event_data->type)
            {
                case USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_RECEIVED_DATA:
                {
                    #if USER_APPLICATION_SIMULATE_EEPROM
                    user_application_simulated_eeprom[current_loopback_cache_index++] = event_data->data;
                    #else
                    internal_eeprom_drv_write_byte(&event_data->data, current_loopback_cache_index++);
                    #endif

                    if (current_loopback_cache_index == USER_APPLICATION_MAX_LOOPBACK_PACKET_SIZE)
                    {
                        current_loopback_cache_index = 0;
                        user_application_state_machine_state = USER_APPLICATION_STATE_MACHINE_STATE_TRANSMISSION;
                        user_application_state_machine_event_data_t new_event_data = {.type = USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_INTERNAL};
                        scheduler_event_put(&new_event_data, sizeof(new_event_data), user_application_state_machine_event_handler);
                    }
                }
                break;

                default:
                {
                    // ERR_INVALID_EVENT_TYPE_IN_RECEPTION_STATE
                }
                break;
            }
        }
        break;

        case USER_APPLICATION_STATE_MACHINE_STATE_TRANSMISSION:
        {
            switch (event_data->type)
            {
                case USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_INTERNAL:
                case USER_APPLICATION_STATE_MACHINE_EVENT_TYPE_TRANSMITTED_DATA:
                {
                    #if USER_APPLICATION_SIMULATE_EEPROM
                    uart_drv_trigger_transmit(user_application_simulated_eeprom[current_loopback_cache_index++]);
                    #else
                    uint8_t read_cached_data;
                    internal_eeprom_drv_read_byte(&read_cached_data, current_loopback_cache_index++);
                    uart_drv_trigger_transmit(read_cached_data);
                    #endif

                    if (current_loopback_cache_index == USER_APPLICATION_MAX_LOOPBACK_PACKET_SIZE)
                    {
                        current_loopback_cache_index = 0;
                        user_application_state_machine_state = USER_APPLICATION_STATE_MACHINE_STATE_RECEPTION;
                    }
                }
                break;

                default:
                {
                    // ERR_INVALID_EVENT_TYPE_IN_TRANSMISSION_STATE
                }
                break;
            }
        }
        break;

        default:
        {
            // ERR_INVALID_USER_APPLICATION_STATE_MACHINE_STATE
        }
        break;
    }
}