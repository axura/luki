#include<stdio.h>

#define max_entry 0xFF

unsigned int crc32b(unsigned char *message);
void createTable ( void );
unsigned int checksum( unsigned char *message);
