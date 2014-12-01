//testing stuff for hamming test. 
#include<stdio.h>
#include<stdint.h>

#define message_len 16
#define input_len 8
#define p1_index 0
#define p2_index 1
#define p4_index 3
#define p8_index 7

int main (void){
    int message[] = {1,1,1,1,1,1,1,0};
    int sent[message_len];
    int i;
    int j = 0;
    for (i = 0; i+j < message_len; i++){        
        switch(i+j){
            case p1_index:
                sent[p1_index] = 0;
                j++;
            case p2_index:
                sent[p2_index] = 0;
                j++;
            case p4_index:
                sent[p1_index] = 0;
                j++;
            case p8_index:
                sent[p1_index] = 0;
                j++;
            case 12:
                //case that it has reached the last four bits. 
                sent[12] = 0;
                sent[13] = 0;
                sent[14] = 0;
                sent[15] = 0;
            default:
                sent[i+j] = message[i];
        
        }
    }
    
    return 0;
}
