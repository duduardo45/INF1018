#include <stdio.h>

int main(void) {

    unsigned int x;
    unsigned int res;
    x = 0x87654321;

    // teste de byte shift:
    res = x>>4;
    printf("%u >> %u\n", x, res);
    printf("%x >> %x\n", x, res);

    // recupera byte menos significativo:
    res = x & 0x000000FF;
    printf("%u >> %u\n", x, res);
    printf("%x >> %x\n", x, res);

    // recupera byte mais significativo tornando os outros 1:
    res = x | 0x00FFFFFF;
    printf("%u >> %u\n", x, res);
    printf("%x >> %x\n", x, res);

    return 0;
}