void dump(void *p, int n);

int main (void) {
  char p[] = "A\n$";
  dump(p, sizeof(p));
  return 0;
}