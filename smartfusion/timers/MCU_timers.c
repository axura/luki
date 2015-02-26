/*
 * handles the following timers:
 *    - RTC: used to retreive time in seconds (Unix format)
 *    - timer 1: for timestamp microsecond precision
 *    - timer 2: to check for FPGA timing out. 
 */

#include "../../drivers/mss_rtc/mss_rtc.h"
#include "../../drivers/mss_timer/mss_timer.h"
#include "../../other/FPGA_IRQ/FPGA_IRQ.h"
#include "MCU_timers.h"

#include <string.h>
#include "../../drivers/mss_uart/mss_uart.h"

//extern int timestamp_read_ptr;

void init_MCU_RTC ( void ){
		MSS_RTC_init();
		MSS_RTC_configure( MSS_RTC_NO_COUNTER_RESET );
		MSS_RTC_set_rtc_count( (uint64_t) 0x0 ); //set start counting value from 0
		MSS_RTC_start();
}

void init_MCU_TM1 ( void ){
    MSS_TIM1_init( MSS_TIMER_PERIODIC_MODE );
    MSS_TIM1_load_immediate( TM1_sec_value );
    MSS_TIM1_start();
    MSS_TIM1_enable_irq();		
}

void init_MCU_TM2 ( void ){
		MSS_TIM1_init( MSS_TIMER_ONE_SHOT_MODE );
    MSS_TIM1_load_immediate( TM2_load_value );
    MSS_TIM1_start();
    MSS_TIM1_enable_irq();	
	
}

void Timer1_IRQHandler( void ){
		MSS_TIM1_clear_irq();
		MSS_TIM1_load_immediate( TM1_sec_value );
		return;
}

void Timer2_IRQHandler( void ){
		MSS_TIM2_clear_irq();
		TM2_option = MCU_RESET;
		return;
}

unsigned long long get_time( void ){
		uint32_t curr_microseconds_time;
		uint64_t curr_seconds_time;
		uint64_t curr_time;
		uint8_t test_str[32];
		curr_seconds_time = MSS_RTC_get_seconds_count();
//		curr_microseconds_time = (uint32_t) ((g_FrequencyPCLK0 - MSS_TIM1_get_current_value( ))/34426.2);
		curr_microseconds_time = (uint32_t) MSS_TIM1_get_current_value( )/4;
		curr_time = (curr_seconds_time << 24) + (uint64_t) curr_microseconds_time;
					MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"\n\r" );
					MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"current time timestamp:" );
					sprintf((char *) test_str, "%llx", curr_time);
					MSS_UART_polled_tx_string( &g_mss_uart0, test_str );
					MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"\n\r" );
	
		return (curr_time);
}

int updateTimestampPtr ( int index_ptr ){
		if (index_ptr >= TIMESTAMP_FIFO_SIZE ){
				return 0;//wrap back to starting index of FIFO again
		} else {				
				return (index_ptr + 1);
		}
}

void checkTimer2 ( void ){
		if (heartbeat_signal){
				MSS_TIM2_load_immediate( TM2_load_value );
				heartbeat_signal = 0;
		}
		return;
}

/*
testing code to be put in main while loop after initialisation of UART, GPIO and timers. 
test with switch 1(GPIO_8), and will send to realTerm terminal via UART the current timestamp
will also include the timestamp FIFO size
*/
#if 0
			if (no_of_timestamps > 0 && temp_time_size != no_of_timestamps){
					temp_timestamp = MCU_TIME_FIFO.time_FIFO[timestamp_save_ptr].timestamp;
					MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"\n\r" );
					MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"timestamp number:" );
					sprintf((char *) test_str, "%d", no_of_timestamps);
					MSS_UART_polled_tx_string( &g_mss_uart0, test_str );
					MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"\n\r" );
					MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"timestamp time:" );
//					MCU_TIME_FIFO.time_FIFO[timestamp_save_ptr].timestamp = 0x30;
					sprintf((char *) test_str, "%llx", MCU_TIME_FIFO.time_FIFO[timestamp_save_ptr].timestamp);
					MSS_UART_polled_tx_string( &g_mss_uart0, test_str );
					MSS_UART_polled_tx_string( &g_mss_uart0,(const uint8_t*)"\n\r" );	
					timestamp_save_ptr = updateTimestampPtr ( timestamp_save_ptr );
					temp_time_size = no_of_timestamps;
			}
#elsif 
