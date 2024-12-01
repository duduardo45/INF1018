#include "cria_func.h"
#include <stdio.h>

typedef int (*func_ptr)();

void printaParam1(char* x) { printf("%s\n",x); }

int main(void) {
    func_ptr f_ret;
    unsigned char codigo[4000];

    DescParam params[1];

    char* palav;
    params[0].tipo_val = PTR_PAR; /* a nova função passa para mult um valor inteiro */
    params[0].orig_val = IND;     /* que é o valor corrente da variavel i */
    params[0].valor.v_ptr = &palav;

    cria_func(printaParam1, params, 1, codigo);
    f_ret = (func_ptr)codigo;

    char* palavras[] = {"abacate", "banana", "churrasco"};

    for (int i = 0; i <3; i++) {
        palav = palavras[i];
        f_ret();
    }

    return 0;
    }