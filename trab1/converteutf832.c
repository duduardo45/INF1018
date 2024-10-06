#include <stdio.h>

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida);
int convUtf32p8(FILE *arquivo_entrada, FILE *arquivo_saida);

#define BOM 0xFEFF


int inverte_int(int n) {
    unsigned char bytes[4];
    for (int i=0;i<4;i++) {
        bytes[i] = (n >> (8*i)); // & 0xFF;
        // printf("%x %x %x\n", bytes[i],(n << (8*i)),n);
    }
    n = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]);
    return n;
}

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida) {

    // por estar usando um computador já little endian, o BOM já está na versão correta em memória
    unsigned int byte = BOM;
    int utf32_char;
    int i = 0;
    unsigned char ajuste;
    fwrite(&byte, sizeof( unsigned int), 1, arquivo_saida);

    while ((byte = getc(arquivo_entrada)) != EOF) {
        printf("%x\n", byte);
        if (0x80 & byte) {
            i = -1; // isso pois o primeiro byte é diferente
            ajuste = 0xFF;
            while (0x80 & byte) {
                i++;
                byte <<= 1;
                ajuste >>= 1;
            }
            utf32_char = (byte>>(i+1)) & ajuste;
            for (;i;i--) {
                byte = getc(arquivo_entrada);
                utf32_char <<=6;
                utf32_char |= byte & 0x3F;
            }
            printf("caracter %x --> ",utf32_char);
            // utf32_char = inverte_int(utf32_char); // necessário pois meu computador é little endian
            printf("caracter %x\n",utf32_char);
        }
        else {
            utf32_char = byte;
        }
        // escreve de acordo com a arquitetura do computador usado, neste caso little endian
        fwrite(&utf32_char, sizeof(unsigned int), 1, arquivo_saida); 
    }
    return 0;
}

int convUtf32p8(FILE *arquivo_entrada, FILE *arquivo_saida) {

    return 0;
}

int main(void) {

    FILE* utf8 = fopen("utf8.txt", "rb");
    FILE* Sutf32 = fopen("conv832.txt", "wb");
    convUtf8p32(utf8,Sutf32);

    return 0;
}