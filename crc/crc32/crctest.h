//header files for naive version of crc checksum

#include<stdio.h>
#include<ctype.h>
#include<stdint.h>
#include<string.h>

#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */
//length of the message to be sent
#define message_len 8

//function prototypes
//finds the checksum
uint8_t crcNaive(uint8_t message);

//converts an integer message array into a stream of binary numbers
uint8_t toBinary ( int* message );

