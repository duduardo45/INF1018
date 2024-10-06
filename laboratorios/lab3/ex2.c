#include <stdio.h>

int odd_ones(unsigned int x) {
  /* escreva seu código aqui */
  unsigned short impar, i;
  impar = 0;
  for (i = 0; i < sizeof(x)*8; i++) {
    impar = impar ^ (x & 0x1);
    x = x>>1;
  }
  return impar;
}
int main() {
  printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
  printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
  return 0;
}