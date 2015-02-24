/*
program contains functions used to calculate checksum for data of n bytes. 
unsigned int crc32b(unsigned char * message) function is taken from:
http://stackoverflow.com/questions/21001659/crc32-algorithm-implementation-in-c-without-a-look-up-table-and-with-a-public-li

*/


#include<stdio.h>
#include"crc32.h"

unsigned int crcTable[no_of_entries_table];

void createTable ( void ){
    unsigned int i;
    unsigned char message[2];
    
    for (i = 0; i <= max_entry; i++){
        message[0] = i;
        message[1] = 0;
        crcTable[i] = crc32b(message);
    }
    return;
}

unsigned int checksumByte( unsigned char *message, int start_ind, unsigned int total_checksum){
    unsigned char data;
    data = message[start_ind];
    data = message[start_ind] ^ (total_checksum >> ( WIDTH - 8 ));
    total_checksum = crcTable[data] ^ (total_checksum << 8);
    return total_checksum;
}

unsigned int checksum( unsigned char *message){
    int byte_i;
    unsigned char data;
    unsigned int total_checksum = 0;
    
    for(byte_i = 0; byte_i < message_len_byte; byte_i++){
        data = message[byte_i] ^ (total_checksum >> ( WIDTH - 8 ));
        total_checksum = crcTable[data] ^ (total_checksum << 8);
    }
    return total_checksum;
}


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
