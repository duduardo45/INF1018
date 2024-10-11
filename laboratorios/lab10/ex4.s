/*
int f(int x);

void map2 (int* um, int * outro, int n) {
  int i;
  for (i=0; i<n; i++)
    *(outro+i) = f(*(um+i));
}
*/

.globl map2
.text

map2:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq %r12, -8(%rbp)
    movq %r13, -16(%rbp)
    movq %r14, -24(%rbp)

    movl $0, %r10d
    movq %rdi, %r12
    movq %rsi, %r13
    movl %edx, %r14d
    L1:
        cmpl %edx, %r12d
        jge END

        movl %r10d, -28(%rbp)
        imull $4, %r10d
        movslq %r10d, %r10
        addq %r10, %rdi
        movl (%rdi), %edi
        call f
        movq %r12, %rdi
        movq %r13, %rsi
        movl %r14d, %edx
        movl -28(%rbp), %r10d

        imull $4, %r10d
        movslq %r10d, %r10
        addq %r10, %rsi

        movl %eax, (%rsi)

        movl -28(%rbp), %r10d
        addl $1, %r10d
        jmp L1
    END:
    
    movq -8(%rbp), %r12 
    movq -16(%rbp), %r13
    movq -24(%rbp), %r14
    leave
    ret
        
