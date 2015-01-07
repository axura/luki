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
 
    /* Convert to local time format. */
    /*
    c_time_string = ctime(&current_time);
 
    if (c_time_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current time.");
        return EXIT_FAILURE;
    }
    */ 
    /* Print to stdout. */
    //(void) printf("Current time is %s", c_time_string);
    
    //testing toByteArr function using random value
    unsigned long long test_int = 0x11DEADBEEF;
    printf("test_int = %llx\n", test_int);
    unsigned char test_array[unix_time_size]; //4 bytes long, this needs to be specified. 
    toByteArr( test_array, test_int, unix_time_size);
    
    return EXIT_SUCCESS;
}

//appending in the crc bits
void toByteArr ( unsigned char* array, unsigned long long value , int array_size){
    int i;
    //int j = 0;
    unsigned char ch;
    
    for( i = 0; i < array_size; i++){
        ch = value >> (8*i); //little endian, taking in the least sig 8 bits first
        array[i] = ch; 
    }
    
    /*this was used previously in main.c for crc32 calculations
    for(i = 1; i <= array_size; i++){
        ch = value >> (value_bit_no - 8*i);
        array[array_size + j] = ch;
        j++;
    }*/
    
    for(i=0; i < array_size; i++){
        printf("message[%d]: %04x\n", i, array[i]);
    }
    return;
}

