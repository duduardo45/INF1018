/*
int add2 (struct X *x) {
  if (x == NULL) return 0;
  else return x->val + add2(x->next);
}
*/

.text
.globl add2

add2:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    cmpq $0, %rdi
    je END
    movl (%rdi), %r10d
    movl %r10d, -4(%rbp)
    movq 8(%rdi), %rdi
    call add2
    addl -4(%rbp), %eax
    leave
    ret
    END:
    movl $0, %eax
    leave 
    ret
