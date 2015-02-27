/*
 * header file for FPGA_IRQ.c
 *
 */
 
#define scrubbing_config	0
#define DPR_config				1

/*
 * GPIO pins for FPGA interrupt types. 
 * The names for the prefix and type may change
 * The GPIO pin needs to be defined.
 */

#define ERROR_SEM					MSS_GPIO_0
#define ERROR_RM					MSS_GPIO_1
#define RECONFIG_DONE			MSS_GPIO_3
#define RECONFIG					MSS_GPIO_8
#define ImAlive						MSS_GPIO_6

#define ERROR_SEM_PREFIX	0x7E
#define ERROR_RM_PREFIX		0X3C
#define RECONFIG_DONE_PREFIX 0X24
#define RECONFIG_PREFIX		0X1F

static int heartbeat_signal = 0;
/*
 * Initialisation function for FPGA IRQ lines
 * Sets the GPIO lines to receive interrupts on rising edge
 */
void FPGA_IRQ_init ( int FPGA_base_config );

/*
 * GPIO interrupt handlers. 
 * The last interrupt handler handles the heartbeat signal 
 * All other interrupts indicate FPGA event.
 * For the latter case, a timestamp will be generated to the timestamp FIFO
 */
void GPIO0_IRQHandler( void );
void GPIO1_IRQHandler( void );
void GPIO3_IRQHandler( void );
void GPIO6_IRQHandler( void );
void GPIO8_IRQHandler( void );
