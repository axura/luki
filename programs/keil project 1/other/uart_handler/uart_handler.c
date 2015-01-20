#include "drivers/mss_uart/mss_uart.h"
#include "other/uart_handler/uart_handler.h"

void uart0_rx_handler( void ){
		size_t rx_size;
		uint8_t rx_buff[UART_RX_BUFF_SIZE];
		uint32_t rx_idx  = 0;
		rx_size = MSS_UART_get_rx( &g_mss_uart0, rx_buff, sizeof(rx_buff) );  
		process_rx_data( rx_buff, rx_size);
		return;
}

void process_rx_data( uint8_t* rx_message, size_t rx_size ){
	
	MSS_UART_polled_tx( &g_mss_uart0,rx_message, rx_size );
	return;
}