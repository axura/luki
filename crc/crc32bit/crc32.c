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
#define WIDTH 8*4  //size of the crc is 32 bit

unsigned int crcTable[no_of_entries_table];

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
        crcTable[i] = crc32b(message);
//        printf("%04x crc:%04x\n", i, crcTable[i]);
    }
    return;
}

unsigned int checksum( unsigned char *message){
    int byte_i;
    unsigned char data;
    unsigned int total_checksum = 0;
    
    for(byte_i = 0; byte_i < message_len_byte; byte_i++){
        data = message[byte_i] ^ (total_checksum >> ( WIDTH - 8 ));
        total_checksum = crcTable[message[data]] ^ (total_checksum << 8);
        printf(" byte: %04x data: %04x crc: %04x\n", message[byte_i], data, crcTable[message[data]]);
    }
    return total_checksum;
}
