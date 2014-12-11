#include<stdio.h>
#include<stdint.h>
#include "crc32.c"

#define input_len 4
#define byte_len 8

unsigned char toBinary ( unsigned char* message );
void printMessage ( unsigned char * message );
void printEntries ( void );
void printEntriesR (void);
void toBinaryArr ( unsigned char* message );

unsigned char binary_message[input_len];

/*
int main (int argc, char *argv[]){
    unsigned char input[byte_len];
    unsigned char message[input_len];
    unsigned char mask = 0b10000000;
    unsigned int crcT, crcR;
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
        message[j] = toBinary(input);
    }
        
    crcT = crc32b( message);
    printf("transmitted message crc: %04x\n", crcT);
    
    //change the message a bit;
    message[2] ^= mask;
    printf("recieved message\n");
    
    crcR = crc32b( message);
    printf("recieved message crc: %04x\n", crcR);

    if (crcR != crcT){
        printf("error detected\n");
    } else {
        printf("no error detected\n");
    }
       
    return 0;
}*/

int main (int argc, char *argv[]){
    unsigned char input[byte_len];
    unsigned char message[input_len];
    unsigned int crcT, crcR;
    unsigned char temp;
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
        message[j] = toBinary(input);
    }

    createTable();
    crcT = checksum( message );
    printf("the transmitted checksum is %04x\n",crcT);
    
    //modifying sent message
//    message[1] += 0xF;
//    message[2] ^= 0x1;
/*
      temp = message[1];
      message[1] = message[3];
      message[3] = temp;
*/

    //crcT ^= 0x1;
    
    crcR = checksum( message );
//    crcR ^= 0x1;
    
    printf("the recieved checksum is %04x\n",crcR);
    crcR ^= crcT;    
    if (crcR != 0){
        printf("error detected\n");
    } else {
        printf("no error\n");
    }
    
    return 0;
}

void printMessage ( unsigned char * message ){
    int j;
    for (j = 0; j < input_len; j++ ){
        printf("message[%d] = %04x\n",j,message[j]);
    }
    
    return;
}

void printEntries ( void ){
    unsigned int i;
    unsigned char message[1];
    
    for (i = 0; i <= max_entry; i++){
        message[0] = i;
        printf("%04x crc:%04x\n", i, crc32b(message));
    }
    return;
}

void printEntriesR (void){
    unsigned int i;
    unsigned char message[1];
    
    for ( i = 0xFF; i > 0; i-- ){
        message[0] = i;
        printf("%04x crc:%04x\n", i, crc32b(message));    
    }
    message[0] = 0;
    printf("%04x crc:%04x\n", i, crc32b(message));    
    
    return;
    
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

void toBinaryArr ( unsigned char* message ){
    unsigned char binary_message[input_len] = {0};
    int i = 0;
    int j = 0;
    int k = 0;
    for (j = 0; j < input_len; j++){
        for(i = 0; i < byte_len; i++){
            binary_message[j] = (binary_message[j] << 1) + message[k];
            k++;
//            printf("%d\n", binary_message);
        }
        printf("binary message index %d: %04x\n", j, binary_message[j]);
    }
//    printf("hexadecimal value = %04x\n", binary_message);
    return;
}
