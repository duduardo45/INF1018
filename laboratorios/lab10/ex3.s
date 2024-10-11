/*
struct X {
  int val1;
  int val2;
};

int f(int i, int v);

int f(int i, int v) {
  if (i >= v)
    return i;
  else
    return v;
}

void boo (struct X *px, int n, int val) {
  while (n--) {
    px->val2 = f(px->val1, val);
    px++;
  }
}

*/
.globl boo
.globl f
.text

/*
f:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    cmpl %esi, %edi
    jg ELSE
    movl %edi, %eax
    leave
    ret
    ELSE:
    movl %esi, %eax
    leave
    ret
*/
boo:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    L1:
    cmpl $0, %esi
    je END

    movq %rdi, -8(%rbp)
    movl %esi, -12(%rbp)
    movl (%rdi), %edi
    movl %edx, %esi
    call f
    movq -8(%rbp), %rdi
    addl %eax, 4(%rdi)
    addq $8, %rdi

    movl -12(%rbp), %esi
    subl $1, %esi
    jmp L1
    END:
    leave
    ret
