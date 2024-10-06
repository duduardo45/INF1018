#include <stdio.h>

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida);
int convUtf32p8(FILE *arquivo_entrada, FILE *arquivo_saida);


int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida) {

    int byte;
    while ((byte = getc(arquivo_entrada)) != EOF) {
        printf("Byte: 0x%x\n", byte);  // Print the byte in hexadecimal form
    }
    return 0;
}

int convUtf32p8(FILE *arquivo_entrada, FILE *arquivo_saida) {

    return 0;
}

int main(void) {

    FILE* e = fopen("utf8.txt", "rb");
    convUtf8p32(e,NULL);

    return 0;
}