/*simple crc algorithm function testing
this file was created on 27/11/2014
compile with "gcc -Wall -Werror crctest.c -std=c99"
got the function from
http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
*/
#include<stdio.h>
#include<stdint.h>

#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */


uint8_t crcNaive(uint8_t message);

int main (int argc, char *argv[]){

    uint8_t message = 0xff;
    uint8_t result;
    
    result = crcNaive(message);
    
    printf("%d\n", result);

    return 0;

}

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
