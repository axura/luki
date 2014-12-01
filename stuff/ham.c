//testing stuff for hamming test. 
#include<stdio.h>
#include<stdint.h>

#define message_len 16
#define input_len 8

int main (void){
    int message[] = {1,1,1,1,1,1,1,0};
    int sent[message_len];
    int i;
    int j = 0;
    for (i = 0; i+j < message_len; i++){
        if(i < input_len){
            sent[i] = message[i];
        } else {
            sent[i] = 0;
        }
    }
    return 0;
}
