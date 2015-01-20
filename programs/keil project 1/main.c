/*
	Project that allows the user to send a series of ascii from the computer to the smartfusion. 
	The data is then used, added to a timestamp and then has crc appended. 
	Intend to store the array of information in SPI flash
*/
#include "other/crc32/crc32.h"
#include "drivers/mss_rtc/mss_rtc.h"
#include "drivers/mss_uart/mss_uart.h"
#include "drivers/mss_watchdog/mss_watchdog.h"

#include <stdio.h>
#include <stdint.h>
#include <time.h>

//function prototypes used for debugging in main
void InitGreeting ( void );

int main (void){
		
	
		//initiate the UART and RTC
    MSS_WD_disable(); //disable the watchdog 
    
    MSS_RTC_init();	
	
	  MSS_UART_init
    (
				&g_mss_uart0,
        MSS_UART_115200_BAUD,
        MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
    ); 

		InitGreeting();
		
	
	while (1) {
		;
	}
	
}

void InitGreeting ( void ){
    MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"\n\r\n\r*********************************************************************\n\r" );
    MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"Testing. RTC, UART have been initialised. Watchdog disabled\n\r" );

		return;
}
