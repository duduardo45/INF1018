#include "cria_func.h"
#include <stdio.h>

typedef int (*func_ptr)(int x);

int retornaParam1(int x) { return x; }

int main(void) {
  func_ptr f_ret;
  unsigned char codigo[500];

  DescParam params[2];

  cria_func(retornaParam1, params, 2, codigo);
  f_ret = (func_ptr)codigo;

  printf("%d\n", f_ret(10));

  return 0;
}