/*
 * header file for MCU_timers.c 
 * contains the functions for UART data handling
 *
 */

#include <stdint.h>
#include "../../drivers/mss_uart/mss_uart.h"
#include "../../drivers/at25df641/at25df641.h"

#define UART_RX_TOTAL_SIZE 		28
#define UART_FIFO_SIZE				488
#define UART_RX_BUFF_SIZE 		1
#define	CRC32_SIZE						4
/*
 *UART GLOBAL VARIABLES
 */

//static uint8_t MCU_UART_FIFO[UART_FIFO_SIZE];

static uint8_t UART_rx_buff[UART_RX_TOTAL_SIZE];
static uint8_t UART_input[1];
//static int UART_read_ptr = 0; 
//static int UART_save_ptr = 0; //pointer index in fifo for next to store in flash
//static uint32_t flash_write_adr = 0x10;
//static int UART_byte_count = 0;
/*
 * UART function prototypes
 */

void init_MCU_UART ( void );
void uart0_rx_handler( void );
int updateUARTptr ( int ind_ptr );
