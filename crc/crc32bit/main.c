#include<stdio.h>
#include<stdint.h>
#include "crc32.c"

#define input_len 28
#define byte_len 8

unsigned char toBinary ( unsigned char* message );

int main (int argc, char *argv[]){
    unsigned char input[byte_len];
    unsigned char message;
    int i;
    int j;  
    int k=0;
    
    for (j = 0; j < input_len; j++){
        for (i = 0; i < byte_len; i++){
//            printf("input from command line: %c\n", argv[1][k]);
            input[i] = ((uint8_t) argv[1][k]) - '0';
//            printf("index %d: %d\n", i, input[i]);
            k++;
        }    
        message = toBinary(input);
    
        printf("message = %04x\n",message);
    }
    
    
       
    return 0;
}

unsigned char toBinary ( unsigned char* message ){
    unsigned char binary_message = 0;
    int i= 0;
    for(i = 0; i < byte_len; i++){
        binary_message = (binary_message << 1) + message[i];
//        printf("%d\n", binary_message);
    }
//    printf("hexadecimal value = %04x\n", binary_message);
    return binary_message;
}
