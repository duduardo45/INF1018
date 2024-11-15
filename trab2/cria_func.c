/* Bruno Azambuja Carvalho 2310956 3WC */
/* Eduardo Eugênio de Souza 2310822 3WC */
#include "cria_func.h"
#include <stdio.h>

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
  unsigned char assembly[23] = {0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x10, 0x48, 0x89, 0x7d, 0xf8, 0xff, 0xd7, 0xf8,0x48, 0x89, 0xec, 0x5d, 0xc3};

  for (int i = 0; i < 23; i++) {
    codigo[i] = assembly[i];
  }
}
