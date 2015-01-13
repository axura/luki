/*
Program tests the functions to be used for the processing of FPGA to MCU data
Recieves the data, takes out the twelve bytes, includes the terminal character "0x0D"
Removes the zero-padding for the ECC bits. Then appends to the end. 
Sorts everything into char arrays before adding in timestamp and crc.
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define byte_len 8
#define input_len 12 //input length in terms of bytes
#define full_message_len 4
#define ecc_byte_len 3

void toByteArr ( unsigned char* array, unsigned long long value , int array_size);
unsigned char toBinary ( unsigned char* message );
uint8_t hexToChar (uint8_t high_word, uint8_t low_word);
uint8_t findHex (uint8_t value);
void removeZero ( uint8_t * input, uint8_t * ecc );
void removeZeroFive ( uint8_t * input, uint8_t* ecc, int input_ind, int ecc_ind );

int main (int argc, char *argv[]){
    unsigned char input[input_len];
    unsigned char ecc_arr[ecc_byte_len];
//    unsigned char message[full_message_len];
    int i;
    int k=0;
    
    for (i = 0; i < input_len; i++){
        input[i] = hexToChar( argv[1][k], argv[1][k+1] );
        printf("message[%d]: %02x\n",i ,input[i]);
        k = k + 2;
    }    
//can print properly the arrays using little endianess. 
    removeZero ( input, ecc_arr );
    
    return EXIT_SUCCESS;
}

void removeZero ( uint8_t * input, uint8_t * ecc ){
    removeZeroFive( input, ecc, 0, 0);

    return;
}

//remove zero for 5 bytes. 
void removeZeroFive ( uint8_t * input, uint8_t* ecc, int input_ind, int ecc_ind ){
    int i;
    int k = 0;
    int j = ecc_ind;
    unsigned long long ecc_temp = 0;
    unsigned long long temp;
    
    for (i = input_ind; i < (input_ind + 8); i++){
        temp = input[i];
        ecc_temp = ecc_temp | (temp << 5*k);
        printf("temp << k = %llx input = %02x: ecc_temp = %llx\n",temp << 5*k, input[i],  ecc_temp);
        k++;
    }
    return;
}


uint8_t hexToChar (uint8_t high_word, uint8_t low_word){
    uint8_t result;
    
    high_word = findHex( high_word );
    low_word = findHex( low_word );
    
    result = (high_word << 4) + low_word;
    printf("result: %02x\n",result);
    return result;
}

uint8_t findHex (uint8_t value){
    if (value >= '0' && value <= '9'){
        value = value - '0';
    } else if (value >= 'a'){
        value = value - 'a' + 10;
    } else {
        value = value - 'A' + 10;
    }

    return value;
}

//this function does not need to be used in the actual keil project
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

/* 
    Function for converting any integer type data into a char array. 
    This function is to be used for crc and unix time values mostly. 
    See the constants for the sizes of each data variable type.
    for the value entered in, the most significant byte is on the left. 
*/
void toByteArr ( unsigned char* array, unsigned long long value , int array_size){
    int i;
    unsigned char ch;
    
    for( i = 0; i < array_size; i++){
        ch = value >> (8*i); //little endian, taking in the least sig 8 bits first
        array[i] = ch; 
    }
    
    /*print code*/
    for(i=0; i < array_size; i++){
        printf("message[%d]: %04x\n", i, array[i]);
    }
    /* end of print code */
    
    return;
}


/* scrapwork
   char ch; 

    while ((ch = getchar()) != EOF){
        if (ch >= '0' && ch <= '9'){
            ch = ch - '0';
        } else if (ch >= 'a') {
            ch = ch - 'a' + 10;
        } else {
            ch = ch - 'A' + 10;
        }
        printf("%02x\n", (uint8_t ) ch);
        
        ch = getchar();
        printf("second: %02x\n", (uint8_t ) ch);

    }

*/
