#include <stdio.h>

unsigned char switch_byte(unsigned char x) {
    unsigned char temp;
    temp = x >> 4;
    x = (x << 4) | temp;
    return x;
}


unsigned char rotate_left(unsigned char x, int n) {
    unsigned char temp;
    if (n >= 8) n = n%8; // pode-se assumir de acordo com o enunciado mas prefiro garantir.
    temp = x >> (8-n);
    x = (x << n) | temp;
    return x;
}


int main(void) {

    unsigned char x;
    x = 0xab;
    printf("%x\n",switch_byte(x));
    x = 0x61;
    printf("%x\n",rotate_left(x,1));
    printf("%x\n",rotate_left(x,2));
    printf("%x\n",rotate_left(x,7));
    return 0;
}