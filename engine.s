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

    movss -28(%rbp), %xmm0
    ucomiss Far(%rip), %xmm0
    jae compute_point_Cquit

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

    vpxor %xmm1, %xmm1, %xmm1

    movss -40(%rbp), %xmm0
    ucomiss %xmm1, %xmm0
    jb compute_point_Cquit
    movss -40(%rbp), %xmm0
    ucomiss Width(%rip), %xmm0
    ja compute_point_Cquit

    movss -36(%rbp), %xmm0
    ucomiss %xmm1, %xmm0
    jb compute_point_Cquit
    movss -36(%rbp), %xmm0
    ucomiss Height(%rip), %xmm0
    ja compute_point_Cquit

    jmp compute_point_quit
    compute_point_Cquit:
    
    movq $0, %rax
    jmp compute_point_end

    compute_point_quit:
    movq -8(%rbp), %rax
    vmovups -40(%rbp), %xmm0
    vmovups %xmm0, (%rax)
    movq $1, %rax

    compute_point_end:

    addq $64, %rsp
    popq %rbp
    ret

.global compute_line
compute_line:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp

    movq %rdx, -8(%rbp)
    movq %r8, -16(%rbp)
    movq %r9, -24(%rbp)

    movq %rcx, %rdx
    movq VIEW(%rip), %rcx
    leaq -48(%rbp), %r8
    call mulmv

    movq PERSPECTIVE(%rip), %rcx
    leaq -48(%rbp), %rdx
    leaq -64(%rbp), %r8
    call mulmv

    movq -8(%rbp), %rdx
    movq VIEW(%rip), %rcx
    leaq -48(%rbp), %r8
    call mulmv

    movq PERSPECTIVE(%rip), %rcx
    leaq -48(%rbp), %rdx
    leaq -80(%rbp), %r8
    call mulmv

    movq -16(%rbp), %rax
    vmovups -64(%rbp), %xmm0
    vmovups %xmm0, (%rax)
    movq -24(%rbp), %rax
    vmovups -80(%rbp), %xmm0
    vmovups %xmm0, (%rax)

    movq $1, %rax

    addq $128, %rsp
    popq %rbp
    ret
