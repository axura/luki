/*simple crc algorithm function testing
this file was created on 27/11/2014
compile with "gcc -Wall -Werror crctest.c -std=c99"
got the function from
http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
made modifications accordingly
main program function. takes in the 8-bit binary input from the command line as a string. 
Converts it to uint8_t type, and then passes into the CRC algorithm to find the remainder. This is appended to the "sent" message
There is a block under a commented section where the "receive" message is intentionally modified, to model when errors have occured during transaction.
variables declared
sent: contains the message bitwise, and with the crc initial appended at the end
recieve: contains the crc result of the sent variable

if the result from the crc operation on receive variable is zero, then it is error-free.
*/

#include<stdio.h>
#include<ctype.h>
#include<stdint.h>
#include<string.h>
#include"crctest.h"

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
