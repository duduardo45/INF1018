.data
.text
.globl criafunc

criafunc:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq %rdi, -8(%rbp)

call *%rdi

movq -8(%rbp), %rdi
movq %rbp, %rsp
popq %rbp
ret
