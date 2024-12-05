.text
.globl teste

teste:
    pushq %rbp
    movq %rbp, %rsp
    subq $32, %rsp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq %rdx, -24(%rbp)
    movq $0x12232332323, %r8
    movl (%r8), %edi
    movl (%r8), %esi
    movl (%r8), %edx
    movq $0x1223233232334343, %r8
    movq %r8, %rdi
    movq %r8, %rsi
    movq %r8, %rdx
    movq $47548738975, %rax
    movq $0x4754873895, %rax
    movq $0x4754873895, %rdi
    movq (%r8), %rdi
    movq (%r8), %rsi
    movq (%r8), %rdx
    movl (%r8), %edi
    movl (%r8), %esi
    movl (%r8), %edx
    movq $0x4754873895, %rsi
    movq $0x4754873895, %rdx
    movl $4, %edi
    movl $4, %esi
    movl $4, %edx
    call *%rax
    movl %edi, %eax
    movq -8(%rbp), %rdi
    movq -16(%rbp), %rdi
    movq -24(%rbp), %rdi
    movq -8(%rbp), %rsi
    movq -16(%rbp), %rsi
    movq -24(%rbp), %rsi
    movq -8(%rbp), %rdx
    movq -16(%rbp), %rdx
    movq -24(%rbp), %rdx
    movl -8(%rbp), %edi
    movl -16(%rbp), %edi
    movl -24(%rbp), %edi
    movl -8(%rbp), %esi
    movl -16(%rbp), %esi
    movl -24(%rbp), %esi
    movl -8(%rbp), %edx
    movl -16(%rbp), %edx
    movl -24(%rbp), %edx
    

leave
ret