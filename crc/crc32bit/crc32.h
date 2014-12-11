/*crc32.h includes the functions used for a 32bit checksum.
The functions were taken from the following resources and modified accordingly:
 
*/

#include<stdio.h>

#define max_entry 0xFF
#define no_of_entries_table 256
#define message_len_byte 4
#define WIDTH 8*4  //size of the crc is 32 bit

//calculates the 32CRC checksum for an array of 8-bit integers. 
unsigned int crc32b(unsigned char *message);

/*
creates a table of all possible 8-bit integers. 
Index is the 8-bit integer data, and the array stores the checksum. 
This function is to be used at the beginning before any checksum is calculated
*/
void createTable ( void );

/*
given an 8-bit array of data, the function will find the overall checksum. 
It will find the individual checksum of each byte in the message array, before
bitwise XOR with the total remainder.
*/
unsigned int checksum( unsigned char *message);
