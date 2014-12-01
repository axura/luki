/*simple crc algorithm function testing
this file was created on 27/11/2014
compile with "gcc -Wall -Werror crctest.c -std=c99"
got the function from
http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
made modifications accordingly
*/
#include<stdio.h>
#include<ctype.h>
#include<stdint.h>
#include<string.h>

#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */
#define message_len 8

uint8_t crcNaive(uint8_t message);
uint8_t toBinary ( int* message );

int main(int argc, char *argv[]){
    int message[message_len];
    int i = 0;
    uint8_t sent;
    uint16_t sent_code;
    uint8_t crc;
    uint16_t receive;

    printf("input: %s\n", argv[1]);

    for (i = 0; i < message_len; i++){
        printf("input from command line: %c\n", argv[1][i]);
        message[i] = ((int) argv[1][i]) - '0';
        printf("index %d: %d\n", i, message[i]);
    }
    
    sent = toBinary(message);
    receive = sent << message_len;
    printf ("message: %04x\n", sent);
    
    crc = crcNaive( sent );
    printf("crcNaive: %04x\n", crc);
    
    receive = crc;
    sent_code = receive;
    
    //altering recieve to check that they are different
    receive ^= 1;

    printf("sent: %04x\n", sent_code);
    printf("received: %04x\n", receive);
    
    if ((receive ^ sent_code) == 0){
        printf("no error detected\n");
    } else {
        printf("error detected\n");
    }

    return 0;
}


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
