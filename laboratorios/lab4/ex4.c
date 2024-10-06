/* programa 1*/
#include <stdio.h>

int main (void) {
  int x = 0xffffffff;
  int y = 2;
  printf("x=%d, y=%d\n", x, y);
  printf("x é menor do que y? %s\n", (x<y)?"sim":"nao");

/* programa 2*/
  unsigned int a = 0xffffffff;
  unsigned int b = 2;
  printf("x=%d, y=%d\n", a, b);
  printf("x é menor do que y? %s\n", (a<b)?"sim":"nao");

/* programa 3*/
  int p = 0xffffffff;
  unsigned int q = 2;
  printf("x=%d, y=%d\n", p, q);
  printf("x é menor do que y? %s\n", (p<q)?"sim":"nao");


  return 0;
}