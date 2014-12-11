/* This is the basic CRC-32 calculation with some optimization but no
table lookup. The the byte reversal is avoided by shifting the crc reg
right instead of left and by using a reversed 32-bit word to represent
the polynomial.
   When compiled to Cyclops with GCC, this function executes in 8 + 72n
instructions, where n is the number of bytes in the input message. It
should be doable in 4 + 61n instructions.
   If the inner loop is strung out (approx. 5*8 = 40 instructions),
it would take about 6 + 46n instructions. */
#include<stdio.h>
#include"crc32.h"

#define no_of_entries_table 256
#define message_len_byte 4

unsigned int table[no_of_entries_table];

unsigned int crc32b(unsigned char *message) {
   int i, j;
   unsigned int byte, crc, mask;

   i = 0; 
   crc = 0xFFFFFFFF;
   while (message[i] != 0) { 
      byte = message[i];            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
      i = i + 1;
   }
   return ~crc;
}

void createTable ( void ){
    unsigned int i;
    unsigned char message[1];
    
    for (i = 0; i <= max_entry; i++){
        message[0] = i;
        table[i] = crc32b(message);
//        printf("%04x crc:%04x\n", i, table[i]);
    }
    return;
}

unsigned int checksum( unsigned char *message){
    int i;
    unsigned int total_checksum = 0;
    
    for(i = 0; i < message_len_byte; i++){
        total_checksum += table[message[i]];
        printf("checksum of %04x is %04x\n", message[i], table[message[i]]);
    }
    return total_checksum;
}
