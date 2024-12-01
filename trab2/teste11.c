#include "cria_func.h"
#include <stdio.h>

typedef void (*func_ptr)();

typedef void (*func_ptr2)(char* p);

void printaParam1(char* x, char* s) { printf("esta é: %s%s", x, s); }

int main(void) {
    func_ptr f_ret, f_test;
    unsigned char codigo[4000];
    unsigned char codigo2[4000];

    DescParam params[1];
    DescParam params2[2];

    char* palav, *palav2;
    params[0].tipo_val = PTR_PAR; /* a nova função passa para mult um valor inteiro */
    params[0].orig_val = IND;     /* que é o valor corrente da variavel i */
    params[0].valor.v_ptr = &palav;

    params2[0].tipo_val = PTR_PAR; /* a nova função passa para mult um valor inteiro */
    params2[0].orig_val = IND;     /* que é o valor corrente da variavel i */
    params2[0].valor.v_ptr = &palav2;

    params2[1].tipo_val = PTR_PAR;
    params2[1].orig_val = PARAM;

    cria_func(printaParam1, params2, 2, codigo2);
    f_ret = (func_ptr2)codigo2;

    cria_func(printf, params, 1, codigo);
    f_test = (func_ptr)codigo;

    char* palavras[] = {"abacate\n", "banana\n", "churrasco\n"};

    for (int i = 0; i <3; i++) {
        palav = palavras[i];
        palav2 = palavras[2-i];
        f_ret("mágica\n");
        f_test();
    }

    return 0;
    }