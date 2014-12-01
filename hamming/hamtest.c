/*testing code version 1 for hamming algorithm. 
made by Yue (Alice) Kang 1/12/2014 (Monday)
for 8 bit messages. 

*/
#include<stdio.h>
#include<stdint.h>

#define message_len 16
#define input_len 8
#define p1 0
#define p2 1
#define p4 3
#define p8 7

//function prototypes
//uint16_t toBinary ( int* message );
uint16_t insertParity ( int* message );

int main (int argc, char* argv[]){
    uint8_t message; 
    int i;
    uint16_t sent;  

    for (i = 0; i < input_len; i++){
        printf("input from command line: %c\n", argv[1][i]);
        message[i] = ((int) argv[1][i]) - '0';
        printf("index %d: %d\n", i, message[i]);
    }

    sent = 

    return 0;
}

uint16_t insertParity (int* message ){
    int* new_message_bits[message_length];
    int i;
    int j;
    
    for (i = 0; i < message_length; i++){
        if ( i+1 == p1 || i+1 == p2 || i+1 == p4 || i+1 == p8 ){
            //have to calculate the number of bits
        } else if ( i < (input_len + 4)){
            new_message_bits[
        }
    }
}
