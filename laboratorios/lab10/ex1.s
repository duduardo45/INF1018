/*
struct X {
  int val;
  struct X *next;
};

int add (struct X *x) {
  int a = 0;
  for (; x != NULL; x = x->next)
    a += x->val;
  return a;
}
*/

.text
.globl add

add:
    pushq %rbp
    movq %rsp, %rbp
    movl $0, %eax
    L1:
        cmpq $0, %rdi
        je END
        addl (%rdi), %eax
        movq 8(%rdi), %rdi
        jmp L1
    END:
    leave
    ret
