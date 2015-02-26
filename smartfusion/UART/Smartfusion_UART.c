/*
 * UART input from FPGA handler
 */

#include "MCU_UART.h"
extern int UART_byte_count;
extern int UART_read_ptr;
extern int UART_save_ptr;

extern uint8_t MCU_UART_FIFO[UART_FIFO_SIZE];

void init_MCU_UART ( void ){
	
    MSS_UART_init(&g_mss_uart0, MSS_UART_115200_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
    MSS_UART_set_rx_handler( &g_mss_uart0, uart0_rx_handler, MSS_UART_FIFO_SINGLE_BYTE );
		return;
} 

int updateUARTptr ( int ind_ptr ){
		if (ind_ptr >= UART_FIFO_SIZE){
				return 0;
		} else {
				return (ind_ptr + 1);
		}
}


void uart0_rx_handler( void ){
		size_t UART_rx_size;
		UART_rx_size = MSS_UART_get_rx( &g_mss_uart0, UART_input, UART_RX_BUFF_SIZE ); 
		MCU_UART_FIFO[UART_read_ptr] = UART_input[0];
		MSS_UART_polled_tx( &g_mss_uart0, &MCU_UART_FIFO[UART_read_ptr], UART_rx_size);
		UART_read_ptr = updateUARTptr( UART_read_ptr );
		UART_byte_count += UART_rx_size;
		return;
}

