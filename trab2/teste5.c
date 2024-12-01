#include "cria_func.h"
#include <stdio.h>

typedef int (*func_ptr)();

int retorna2(int x, int y, int z) { return 2 * x * y * z; }

int main(void) {
  func_ptr f_ret;
  unsigned char codigo[500];

  DescParam params[3];

  params[0].tipo_val =
      INT_PAR; /* o 1o parâmetro de memcmp é um inteiro */
  params[0].orig_val = FIX;
  params[0].valor.v_int = 10;

  params[1].tipo_val = INT_PAR; /* o 2o parâmetro de memcmp é um inteiro */
  params[1].orig_val = FIX;
  params[1].valor.v_int = 5;

  params[2].tipo_val = INT_PAR; /* o terceiro parâmetro de memcmp é um inteiro */
  params[2].orig_val = FIX;
  params[2].valor.v_int = 2;

  cria_func(retorna2, params, 3, codigo);
  f_ret = (func_ptr)codigo;

  printf("%d\n", f_ret());


  return 0;
}