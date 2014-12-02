#include<stdio.h>
#include<ctype.h>
#include<stdint.h>

#define message_len 8

uint8_t toBinary ( int* message );

int main(void){
    char ch;
    int message[message_len];
    int i = 0;
    uint8_t sent;
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

    return 0;
}

uint8_t toBinary ( int* message ){
    uint8_t binary_message = 0;
    int i= 0;
    for(i = 0; i < message_len; i++){
        binary_message = (binary_message << 1) + message[0];
    }
    printf("hexadecimal value = %04x\n", binary_message);
    return binary_message;
}

//function to learn to use switch function
void usingSwitch (void) {
    

}
