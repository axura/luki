/*
Program tests the functions to be used for the processing of FPGA to MCU data
Recieves the data, takes out the twelve bytes, includes the terminal character "0x0D"
Removes the zero-padding for the ECC bits. Then appends to the end. 
Sorts everything into char arrays before adding in timestamp and crc.
*/

#include<stdio.h>
#include<stdlib.h>

void toByteArr ( unsigned char* array, unsigned long long value , int array_size);


int main (void){

    return EXIT_SUCCESS;
}


/* 
    Function for converting any integer type data into a char array. 
    This function is to be used for crc and unix time values mostly. 
    See the constants for the sizes of each data variable type.    
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
