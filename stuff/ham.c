//testing stuff for hamming test. 
#include<stdio.h>
#include<stdint.h>

#define message_len 16
#define check_len 12
#define input_len 8
#define p1_index 0
#define p2_index 1
#define p4_index 3
#define p8_index 7
#define p1 1
#define p2 2
#define p4 4
#define p8 8

int findParityS ( int *message, int p_index, int p_value);

int main (void){
    int message[] = {1,1,1,1,1,1,1,0};
    int sent[message_len];
    int i;
    int j = 0;
    
    printf("message: ");
    for( i=0; i< input_len; i++){
        printf("%d", message[i]);
    }
    printf("\n");
    
    
    for (i = 0; i < message_len; i++){
        switch(i){
            case p1_index:
                sent[p1_index] = findParityS( message, p1_index, p1);
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
    
    //printing the sent message.
    printf("sent code: [");
    for(i = 0; i < message_len; i++){
        printf("%d,", sent[i]);
    }
    printf("]\n");
    return 0;
}

//look for the parity bit in the message. the value to be inserted
//this is using even parity bits so therefore there will always be a even no of 1's generated
int findParityS ( int *message, int p_index, int p_value){
    int EvenParityCount = 0;
    int i = 0;
    int j;
    i = p_index; //start from the index given
    while ( i < check_len ){
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
        i--;
        i += p_value; 
    }
    
    return 0;
}
