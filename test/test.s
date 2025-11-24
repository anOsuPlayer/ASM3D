.section .data

f:          .float  1.2

dbg:        .string "%lf %lf"

.section .text

.global main
main:
	pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    flds f(%rip)
    fptan
    fstps -4(%rbp)
    fstps -8(%rbp)

    leaq dbg(%rip), %rcx
    movss -4(%rbp), %xmm0
    cvtss2sd %xmm0, %xmm0
    movq %xmm0, %rdx
    movss -8(%rbp), %xmm0
    cvtss2sd %xmm0, %xmm0
    movq %xmm0, %r8
    call printf

    addq $48, %rsp
    popq %rbp
    ret
