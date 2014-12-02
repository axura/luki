/*testing code version 1 for hamming algorithm. 
made by Yue (Alice) Kang 1/12/2014 (Monday)
for 8 bit messages. 

*/
#include<stdio.h>
#include<stdint.h>

#define message_len 16
#define check_len 12
#define input_len 8
#define p1_index 0
#define p2_index 1
#define p4_index 3
#define p8_index 7

//function prototypes
uint16_t toBinary ( int* message );
uint16_t insertParity ( int* message );
int findParityS ( int *message, int p_index, int p_value);
void binToArr (uint16_t message, int* array);
int checkError ( int *message );

int main (int argc, char* argv[]){
    int input[input_len]; 
    uint16_t sent;
    uint16_t recieve;
    int recieve_arr[message_len] = {0};
    int i;

    for (i = 0; i < input_len; i++){
//        printf("input from command line: %c\n", argv[1][i]);
        input[i] = ((int) argv[1][i]) - '0';
        printf("index %d: %d\n", i, input[i]);
    }

    sent = insertParity( input );
//    printf("%04x\n",sent);
    
    //transmition of recieve
    recieve = sent;
//    recieve ^= 0x10;
//    recieve ^= 0x2000;  

    //checking recieve
    binToArr (recieve, recieve_arr);
    
    printf("recieve_a: [");
    for (i =0; i < message_len; i++){
        printf("%d,", recieve_arr[i]);
    } 
    printf("]\n");
    
    if (checkError (recieve_arr) == 1){
        printf("error detected\n");
    } else {
        printf("no error detected\n");
    }

    return 0;
}

void binToArr (uint16_t message, int* array){
    int i;
    uint16_t mask = 0x8000;
    uint16_t temp;
    for( i=0; i< message_len; i++){
//        printf("message: %04x\n",message);
        temp = message & mask;
        if (temp == 0){
            array[i] = 0;
        } else {
            array[i] = 1;
        }
        
        message = message << 1;
//        printf("index: %d message: %04x temp: %04x\n", i, message, temp);
    }

    return;
}

uint16_t insertParity (int* message ){
//    int message[] = {1,1,0,1,0,1,0,1};
    int sent[message_len];
    int i;
    int j = 0;
    
    for (i = 0; i < message_len; i++){
        switch(i){
            case p1_index:
                sent[p1_index] = -1;
                break;
            case p2_index:
                sent[p2_index] = -1;
                break;
            case p4_index:
                sent[p4_index] = -1;
                break;
            case p8_index:
                sent[p8_index] = -1;
                break;
            case 12:
                sent[i] = 0;
                break;
            case 13:
                sent[i] = 0;
                break;
            case 14:
                sent[i] = 0;
                break;
            case 15:
                sent[i] = 0;
                break;
            default:
                sent[i] = message[j];
                j++;
                break;
        
        }
    }
    
    //finding the parity bits
    sent[p1_index] = findParityS( sent, p1_index, 1 );
    sent[p2_index] = findParityS( sent, p2_index, 2 );
    sent[p4_index] = findParityS( sent, p4_index, 4 );
    sent[p8_index] = findParityS( sent, p8_index, 8 );    

    //printing the sent message.
    printf("sent code: [");
    for(i = 0; i < message_len; i++){
        printf("%d,", sent[i]);
    }
    printf("]\n");
    return (toBinary(sent));
}

uint16_t toBinary ( int* message ){
    uint16_t binary_message = 0;
    int i= 0;
    for(i = 0; i < message_len; i++){
        binary_message = (binary_message << 1) + message[i];
    }
//    printf("hexadecimal value = %04x\n", binary_message);
    return binary_message;
}

int checkError ( int *message ){
    int p1, p2, p4, p8;
    p1 = findParityS( message, p1_index, 1);
    p2 = findParityS( message, p2_index, 2);
    p4 = findParityS( message, p4_index, 4);
    p8 = findParityS( message, p8_index, 8);

    printf("p1: %d\n", p1);
    printf("p2: %d\n", p2);
    printf("p4: %d\n", p4);
    printf("p8: %d\n", p8);
    
    if (p1 == 1 || p2 == 1 || p4 == 1 || p8 == 1){
        return 1;
    } else {
        return 0;
    }
}

int findParityS ( int *message, int p_index, int p_value){
    int EvenParityCount = 0;
    int i = 0;
    int j;
    i = p_index; //start from the index given
    while ( i < check_len ){
//        printf("index: %d\n", i);
        for (j = p_value; j > 0; j--){
            if ( i >= check_len ){
                break;
            }
            if ( message[i] == 1){
                EvenParityCount ++;
            }
            i++;
        }
        //skip the number of bits
//        printf("EvenParityCount: %d\n", EvenParityCount);
        i += p_value; 
    }
    
    if (EvenParityCount % 2 == 0){
        return 0;
    } else {
        return 1;
    }
}
