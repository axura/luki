#include<stdio.h>
#include<ctype.h>
#include<stdint.h>

#define message_len 8

uint8_t toBinary ( int* message );
void binToArr (uint8_t message, int* array);

int main(void){
    char ch;
    int message[message_len];
    int i = 0;
    uint8_t sent;
    int sent_arr[message_len] = {0};
    while (((ch = getchar()) != EOF) && (ch != '\n')){
//        printf("%c\n",ch);
//        ch = getchar();
        message[i] = (int) (ch - '0');
        i++;
    }

    for (i = 0; i < message_len; i++){
        printf("index %d: %d\n", i, message[i]);
    }
    
    sent = toBinary(message);
    printf ("message: %04x\n", sent);
    
    binToArr( sent, sent_arr );
        
    for( i = 0; i < message_len; i++ ){
        printf("sent_arr_%d: %d\n", i, sent_arr[i]);
    }

    return 0;
}

uint8_t toBinary ( int* message ){
    uint8_t binary_message = 0;
    int i= 0;
    for(i = 0; i < message_len; i++){
        binary_message = (binary_message << 1) + message[i];
    }
    printf("hexadecimal value = %04x\n", binary_message);
    return binary_message;
}

//converting a binary value to binary. 
void binToArr (uint8_t message, int* array){
    int i;
    uint8_t mask = 0x80;
    uint8_t temp;
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
