/*Code copied from Wikipedia.
Test program for finding unix time. 
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define crc_size 4
#define unix_time_size 7

void toByteArr ( unsigned char* array, unsigned long long value , int array_size);
 
int main(void)
{
    time_t current_time;
    //char* c_time_string;
 
    /* Obtain current time as seconds elapsed since the Epoch. */
    current_time = time(NULL);
 
    if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to compute the current time.");
        return EXIT_FAILURE;
    } else {
        printf("%llu seconds since the epoch began \n", (unsigned long long) current_time);
    }
 
    //testing toByteArr function using random value
    unsigned long long test_int = 0x11DEADBEEF;
    printf("test_int = %llx\n", test_int);
    unsigned char test_array[unix_time_size]; //4 bytes long, this needs to be specified. 
    toByteArr( test_array, test_int, unix_time_size);
    
    //testing crc, which is 3 bytes shorter
    int crc_test = 0xDEAFBEAD;
    unsigned char crc_array[4];
    printf("\ncrc test value = %llx\n", (unsigned long long) crc_test);
    toByteArr ( crc_array, (unsigned long long) crc_test , crc_size);
     
    
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

