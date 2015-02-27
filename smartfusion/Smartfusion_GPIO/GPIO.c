/*
 * GPIO pins for the FPGA - MCU IO line. 
 * This program handles the interrupts from the FPGA
 * 
 */
 
#include "../../drivers/mss_gpio/mss_gpio.h"
#include "../../other/MCU_timers/MCU_timers.h"
#include "FPGA_IRQ.h"


extern timestamp_FIFO MCU_TIME_FIFO;
extern int no_of_timestamps;
extern int timestamp_read_ptr;
extern int timestamp_save_ptr;

void FPGA_IRQ_init ( int FPGA_base_config ){
		MSS_GPIO_init();
	
    MSS_GPIO_config( ERROR_SEM , MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_POSITIVE );
    MSS_GPIO_config( ERROR_RM , MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_POSITIVE );
    MSS_GPIO_config( RECONFIG_DONE , MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_POSITIVE );
    MSS_GPIO_config( RECONFIG, MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_POSITIVE );
    MSS_GPIO_config( ImAlive , MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_POSITIVE );
	
		MSS_GPIO_enable_irq( ERROR_SEM );
    MSS_GPIO_enable_irq( ERROR_RM );
    MSS_GPIO_enable_irq( RECONFIG_DONE );
    MSS_GPIO_enable_irq( RECONFIG );	
    MSS_GPIO_enable_irq( ImAlive );
	
		return;
}

/*  
 * handler functions for the interrupts alerting of an event. 
 */
void GPIO0_IRQHandler( void ){
		MCU_TIME_FIFO.time_FIFO[timestamp_read_ptr].timestamp = get_time( );
		MCU_TIME_FIFO.time_FIFO[timestamp_read_ptr].id_prefix = ERROR_SEM_PREFIX;
		timestamp_read_ptr = updateTimestampPtr ( timestamp_read_ptr );
		MSS_GPIO_clear_irq( ERROR_SEM );
		no_of_timestamps++;
		return;
}

void GPIO1_IRQHandler( void ){
		MCU_TIME_FIFO.time_FIFO[timestamp_read_ptr].timestamp = get_time( );
		MCU_TIME_FIFO.time_FIFO[timestamp_read_ptr].id_prefix = ERROR_RM_PREFIX;
		timestamp_read_ptr = updateTimestampPtr ( timestamp_read_ptr );
		MSS_GPIO_clear_irq( ERROR_RM );
		no_of_timestamps++;
		return;
}

void GPIO3_IRQHandler( void ){
		MCU_TIME_FIFO.time_FIFO[timestamp_read_ptr].timestamp = get_time( );
		MCU_TIME_FIFO.time_FIFO[timestamp_read_ptr].id_prefix = RECONFIG_DONE_PREFIX;
		timestamp_read_ptr = updateTimestampPtr ( timestamp_read_ptr );
		MSS_GPIO_clear_irq( RECONFIG_DONE );
		no_of_timestamps++;
		return;
}

void GPIO8_IRQHandler( void ){	
		MCU_TIME_FIFO.time_FIFO[timestamp_read_ptr].timestamp = get_time( );
		MCU_TIME_FIFO.time_FIFO[timestamp_read_ptr].id_prefix = RECONFIG_PREFIX;
		timestamp_read_ptr = updateTimestampPtr ( timestamp_read_ptr );
		MSS_GPIO_clear_irq( RECONFIG );
		no_of_timestamps++;
		return;
}

/*
 * handler for when recieving the heartbeat signal.
 * raise the heartbeat signal flag. 
 */
void GPIO6_IRQHandler( void ){
		heartbeat_signal = 1;
		return;
}
