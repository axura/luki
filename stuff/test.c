#include<stdio.h>
#include<ctype.h>
#include<stdint.h>

uint8_t toBinary ( int* message );

int main(void){
    char ch;
    int message[8];
    int i = 0;
    while (((ch = getchar()) != EOF) && (ch != '\n')){
//        printf("%c\n",ch);
//        ch = getchar();
        message[i] = (int) (ch - '0');
        i++;
    }

    for (i = 0; i < 8; i++){
        printf("index %d: %d\n", i, message[i]);
    }
    
//    printf ("message: %04x\n", message);

    return 0;
}

uint8_t toBinary ( int* message ){
    uint8_t binary_message = 0;
    
    return binary_message;
}
