#include<stdio.h>
#include "crc32.c"

int main (void){
    unsigned char message = 0b11111110;
    printf("message: %d\n",(int) message);
    
    unsigned int result;
    result = crc32b( &message );
    printf("result: %d\n", result);
    
    return 0;
}

