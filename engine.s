.section .data



.section .text
.global compute_point
compute_point:    
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movq %rdx, -8(%rbp)
    movq %rcx, %rdx
    movq VIEW(%rip), %rcx
    leaq -24(%rbp), %r8
    call mulmv

    movq PERSPECTIVE(%rip), %rcx
    leaq -24(%rbp), %rdx
    leaq -40(%rbp), %r8
    call mulmv

    movss -28(%rbp), %xmm0
    ucomiss Near(%rip), %xmm0
    jbe compute_point_Cquit

    leaq -40(%rbp), %rcx
    leaq -40(%rbp), %rdx
    call vndc

    fld1
    fadds -40(%rbp)
    fstps -40(%rbp)

    fld1
    fsubs -36(%rbp)
    fstps -36(%rbp)

    movq $2, %rax
    cvtsi2ss %rax, %xmm2

    movss Width(%rip), %xmm0
    divss %xmm2, %xmm0
    mulss -40(%rbp), %xmm0
    movss %xmm0, -40(%rbp)

    movss Height(%rip), %xmm0
    divss %xmm2, %xmm0
    mulss -36(%rbp), %xmm0
    movss %xmm0, -36(%rbp)

    jmp compute_point_quit
    compute_point_Cquit:
    movq $-1, %rax
    cvtsi2ss %rax, %xmm0
    movss %xmm0, -28(%rbp)

    compute_point_quit:
    movq -8(%rbp), %rax
    vmovups -40(%rbp), %xmm0
    vmovups %xmm0, (%rax)

    addq $64, %rsp
    popq %rbp
    ret
