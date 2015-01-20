#include "../../drivers/mss_uart/mss_uart.h"

void InitGreeting ( void ){
    MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"\n\r\n\r*********************************************************************\n\r" );
    MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"Testing. RTC, UART have been initialised. Watchdog disabled\n\r" );
    MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"CRC table has been created successfully\n\r" );
		return;
}