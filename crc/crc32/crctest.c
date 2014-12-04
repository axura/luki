#include "crctest.h"
#include<stdint.h>
#include<stdio.h>
#include<ctype.h>


//used to convert the input from command line into binary bits
uint8_t toBinary ( int* message ){
    uint8_t binary_message = 0;
    int i= 0;
    for(i = 0; i < message_len; i++){
        binary_message = (binary_message << 1) + message[i];
        printf("%d\n", binary_message);
    }
    printf("hexadecimal value = %04x\n", binary_message);
    return binary_message;
}

//naive version of the crc algorithm
uint8_t crcNaive(uint8_t message){
    uint8_t  remainder;	

    /*
     * Initially, the dividend is the remainder.
     */
    remainder = message;

    /*
     * For each bit position in the message....
     */
    for (uint8_t bit = 8; bit > 0; --bit)
    {
        /*
         * If the uppermost bit is a 1...
         */
        if (remainder & 0x80)
        {
            /*
             * XOR the previous remainder with the divisor.
             */
            remainder ^= POLYNOMIAL;
        }

        /*
         * Shift the next bit of the message into the remainder.
         */
        remainder = (remainder << 1);
    }

    /*
     * Return only the relevant bits of the remainder as CRC.
     */
    return (remainder >> 4);

}   /* crcNaive() */
