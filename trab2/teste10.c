#include "cria_func.h"
#include <stdio.h>

typedef int (*func_ptr)();

int retornaParam1(int x) { return x; }

int main(void) {
    func_ptr f_ret;
    unsigned char codigo[4000];

    DescParam params[1];

    int i;
    params[0].tipo_val = INT_PAR; /* a nova função passa para mult um valor inteiro */
    params[0].orig_val = IND;     /* que é o valor corrente da variavel i */
    params[0].valor.v_ptr = &i;

    cria_func(retornaParam1, params, 1, codigo);
    f_ret = (func_ptr)codigo;

    for (i = 1; i <=10; i++) {
        printf("%d\n", f_ret()); /* a nova função não recebe argumentos */
    }

    return 0;
    }