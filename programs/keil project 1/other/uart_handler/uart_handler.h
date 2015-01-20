#include "drivers/mss_uart/mss_uart.h"

#define UART_RX_BUFF_SIZE 16

void uart0_rx_handler( void );
void process_rx_data( uint8_t* rx_message, size_t rx_size );