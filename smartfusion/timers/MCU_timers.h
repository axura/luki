/*
 * header file for MCU_timers.c 
 * The following functions declared: 
 */

#include <stdint.h>

#define second_rtc_match			255
#define TM2_load_value				0x0000FFFF
#define MCU_RESET							1
#define	TM2_NO_RELOAD					0
#define TIMESTAMP_FIFO_SIZE		64
#define TM1_sec_value					4000

typedef struct timestamp_raw{
		unsigned long long timestamp;
		uint8_t time_prefix;
}timestampEntry;

typedef struct timestampFIFO{
		timestampEntry time_FIFO[TIMESTAMP_FIFO_SIZE];
} timestamp_FIFO;

//static timestamp_FIFO MCU_TIME_FIFO;

static unsigned long long MCU_seconds_time = 0;
static int TM2_option = TM2_NO_RELOAD;

void init_MCU_RTC ( void );
void init_MCU_TM1 ( void );
void init_MCU_TM2 ( void );
void Timer1_IRQHandler( void );
void Timer2_IRQHandler( void );
unsigned long long get_time( void );
int updateTimestampPtr ( int index_ptr );
void checkTimer2 ( void );
