#include "cria_func.h"
#include <stdio.h>
#include <string.h>

typedef char* (*func_ptr)();

char* retorna2(char* a) { return strcat(a, " a banana"); }

char fixa[] = "testando";

int main(void) {
  func_ptr f_ret;
  unsigned char codigo[500];

  DescParam params[1];

  params[0].tipo_val =
      PTR_PAR; /* o 1o parâmetro de memcmp é um inteiro */
  params[0].orig_val = FIX;
  params[0].valor.v_ptr = fixa;


  cria_func(retorna2, params, 1, codigo);
  f_ret = (func_ptr)codigo;

  printf("%s\n", f_ret());

  return 0;
}