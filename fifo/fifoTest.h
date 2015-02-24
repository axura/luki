/*
    header file for fifoTest.c 
    below contain the structs for timestamp and UART input on the controller unit
*/

#include <stdint.h>

#define UART_RX_TOTAL_SIZE 28
#define TIMESTAMP_SIZE     8

typedef struct timestamp_raw{
		unsigned long long timestamp;
		uint8_t time_prefix;
}timestampEntry;

typedef struct timestampFIFO{
		timestampEntry time_FIFO[64];
} timestamp_FIFO;

typedef struct UART_InputBuff{
		uint8_t UART_byte[UART_RX_TOTAL_SIZE];
}UART_input_buff;

typedef struct UART_RxFifo{
		UART_input_buff input_array[64];
}UART_RX_FIFO;
