#include <stdio.h>
#include "converteutf832.h"

int main(void) {
    printf("oi\n");

    FILE* utf8 = fopen("utf8.txt", "rb");
    FILE* Sutf32 = fopen("conv832.txt", "wb");
    convUtf8p32(utf8,Sutf32);
printf("oi\n");
    FILE* utf32 = fopen("utf32.txt", "rb");
    FILE* Sutf8 = fopen("conv328.txt", "wb");
    convUtf32p8(utf32,Sutf8);
printf("oi\n");
    // FILE* utf32 = fopen("utf32.txt", "rb");
    // FILE* Sbig = fopen("utf32-big.txt", "wb");
    // cria_big_endian(utf32,Sbig);
printf("oi\n");
    FILE* utf32big = fopen("utf32-big.txt", "rb");
    FILE* Sutf8big = fopen("utf8-big.txt", "wb");
    convUtf32p8(utf32big,Sutf8big);
printf("oi\n");
    return 0;
}