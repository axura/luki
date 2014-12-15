/*crc32.h includes the functions used for a 32bit checksum.
The functions were taken from the following resources and modified accordingly: 
*/

/* constants
max_entry - the maxiumum index in the createTable array. 
no_of_entries_table - used to declare the table size. 
message_len_byte - the size of the message in bytes. When not testing, should be 28. 
WIDTH - size of the crc in bits.
*/

#include<stdio.h>

#define max_entry 0xFF
#define no_of_entries_table 256
#define message_len_byte 28
#define WIDTH 8*4  //size of the crc is 32 bit

/*
creates a table of all possible 8-bit integers. 
Index is the 8-bit integer data, and the array stores the checksum. 
This function is to be used at the beginning before any checksum is calculated
*/
void createTable ( void );

/*
given an 8-bit array of data, the function will find the overall checksum. 
It will find the individual checksum of each byte in the message array, before
finding the total checksum.
*/
unsigned int checksum( unsigned char *message);


/*calculates the 32CRC checksum for an array of 8-bit integers. Client code should not need to call this function. 

 This is the basic CRC-32 calculation with some optimization but no
table lookup. The the byte reversal is avoided by shifting the crc reg
right instead of left and by using a reversed 32-bit word to represent
the polynomial.
   When compiled to Cyclops with GCC, this function executes in 8 + 72n
instructions, where n is the number of bytes in the input message. It
should be doable in 4 + 61n instructions.
   If the inner loop is strung out (approx. 5*8 = 40 instructions),
it would take about 6 + 46n instructions. */
unsigned int crc32b(unsigned char *message);

