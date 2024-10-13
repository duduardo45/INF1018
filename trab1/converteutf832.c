/*
trabalho feito sozinho por:
Eduardo Eugênio de Souza 2310822 3WC
*/

#include <stdio.h>
#include "converteutf832.h"

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida);
int convUtf32p8(FILE *arquivo_entrada, FILE *arquivo_saida);

#define BOM 0xFEFF

typedef unsigned int uint;

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida) {

    // por estar usando um computador já little endian, o BOM já está na versão correta em memória
    uint byte = BOM;
    int utf32_char;
    int i = 0;
    unsigned char ajuste;
    fwrite(&byte, sizeof(uint), 1, arquivo_saida);
    if (ferror(arquivo_saida)) {
        fprintf(stderr, "Erro de gravacao.\n");
        return -1;
    }

    while ((byte = getc(arquivo_entrada)) != EOF) {

        if (ferror(arquivo_entrada)) {
            fprintf(stderr, "Erro de leitura.\n");
            return -1;
        }


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
                if (ferror(arquivo_entrada)) {
                    fprintf(stderr, "Erro de leitura.\n");
                    return -1;
                }
                utf32_char <<=6;
                utf32_char |= byte & 0x3F;
            }
        }
        else {
            utf32_char = byte;
        }
        // escreve de acordo com a arquitetura do computador usado, neste caso little endian
        fwrite(&utf32_char, sizeof(uint), 1, arquivo_saida); 
        if (ferror(arquivo_saida)) {
            fprintf(stderr, "Erro de gravacao.\n");
            return -1;
        }
    }
    return 0;
}

uint inverte_int(uint n) {
    unsigned char bytes[4];
    for (int i=0;i<4;i++) {
        bytes[i] = (n >> (8*i)); // & 0xFF; desnecessário por questão de tipo usado
    }
    n = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]);
    return n;
}

int convUtf32p8(FILE *arquivo_entrada, FILE *arquivo_saida) {

    uint char32;
    int i;
    unsigned char out[4];
    
    fread(&char32, sizeof(uint), 1, arquivo_entrada);
    if (ferror(arquivo_entrada)) {
            fprintf(stderr, "Erro de leitura.\n");
            return -1;
        }

    int little_endian = char32 == (uint) BOM;
    int big_endian = char32 == inverte_int((uint) BOM);

    if (!little_endian && !big_endian) {
        fprintf(stderr, "BOM invalido.\n");
        return -1;
    }

    while (fread(&char32, sizeof(uint), 1, arquivo_entrada) == 1) {
        if (ferror(arquivo_entrada)) {
            fprintf(stderr, "Erro de leitura.\n");
            return -1;
        }

        if (big_endian) char32 = inverte_int(char32);
        
        for (i = 31; i;i--) if ((char32 >> i) & 1) break;
        i++; // conta a quantidade de bits não nulos

        if (i < 8) {
            out[0] = char32;
            fwrite(out,sizeof(unsigned char), 1, arquivo_saida);
        }
        else if (i < 12) {
            out[0] = 0b11000000 | ((char32 >>  6) & 0b00011111);
            out[1] = 0b10000000 | ( char32        & 0b00111111);
            fwrite(out,sizeof(unsigned char), 2, arquivo_saida);
        }
        else if (i < 17) {
            out[0] = 0b11100000 | ((char32 >> 12) & 0b00001111);
            out[1] = 0b10000000 | ((char32 >>  6) & 0b00111111);
            out[2] = 0b10000000 | ( char32        & 0b00111111);
            fwrite(out,sizeof(unsigned char), 3, arquivo_saida);
        }
        else if (i < 22) {
            out[0] = 0b11110000 | ((char32 >> 18) & 0b00000111);
            out[1] = 0b10000000 | ((char32 >> 12) & 0b00111111);
            out[2] = 0b10000000 | ((char32 >>  6) & 0b00111111);
            out[3] = 0b10000000 | ( char32        & 0b00111111);
            fwrite(out,sizeof(unsigned char), 4, arquivo_saida);
        }
        else {
            fprintf(stderr, "Caractere nao representavel por utf-8.\n");
            return -1;
        }
        if (ferror(arquivo_saida)) {
            fprintf(stderr, "Erro de gravacao.\n");
            return -1;
        }
    }
    return 0;
}

// int cria_big_endian(FILE* entrada, FILE* saida) {
//     uint char32;
//     while (fread(&char32, sizeof(uint), 1, entrada) == 1) {
//         char32 = inverte_int(char32);
//         fwrite(&char32,4,1,saida);
//     }
//     return 0;
// }

// int main(void) {

//     FILE* utf8 = fopen("utf8.txt", "rb");
//     FILE* Sutf32 = fopen("conv832.txt", "wb");
//     convUtf8p32(utf8,Sutf32);

//     FILE* utf32 = fopen("utf32.txt", "rb");
//     FILE* Sutf8 = fopen("conv328.txt", "wb");
//     convUtf32p8(utf32,Sutf8);

//     FILE* utf32 = fopen("utf32.txt", "rb");
//     FILE* Sbig = fopen("utf32-big.txt", "wb");
//     cria_big_endian(utf32,Sbig);

//     FILE* utf32big = fopen("utf32-big.txt", "rb");
//     FILE* Sutf8big = fopen("utf8-big.txt", "wb");
//     convUtf32p8(utf32big,Sutf8big);

//     return 0;
// }