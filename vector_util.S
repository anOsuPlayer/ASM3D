.section .data

negate_mask:        .float -1.0, -1.0, -1.0, -1.0

.section .text

.global make_vec
make_vec:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq $16, %rcx
    call malloc

    pxor %xmm0, %xmm0
    vmovups %xmm0, (%rax)

    addq $32, %rsp
    popq %rbp
    ret

.global vneg
vneg:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    vmovups (%rcx), %xmm0
    vmovups negate_mask(%rip), %xmm1
    vmulps %xmm0, %xmm1, %xmm0
    vmovups %xmm0, (%rdx)

    addq $32, %rsp
    popq %rbp
    ret

.global vmod
vmod:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    vmovups (%rcx), %xmm0
    vmulps %xmm0, %xmm0, %xmm0
    vhaddps %xmm0, %xmm0, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    sqrtss %xmm0, %xmm0

    movss %xmm0, -4(%rbp)
    movl -4(%rbp), %eax

    addq $32, %rsp
    popq %rbp
    ret

.global vnorm
vnorm:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call vmod
    movl %eax, -4(%rbp)
    vbroadcastss -4(%rbp), %xmm0

    vmovups (%rcx), %xmm1
    vdivps %xmm0, %xmm1, %xmm0

    vmovups %xmm0, (%rdx)

    addq $32, %rsp
    popq %rbp
    ret

.global vndc
vndc:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    vbroadcastss 12(%rcx), %xmm0
    vmovups (%rcx), %xmm1
    vdivps %xmm1, %xmm0, %xmm0
    vmovups %xmm0, (%rdx)

    addq $32, %rsp
    popq %rbp
    ret

.global vdot
vdot:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    vmovups (%rcx), %xmm0
    vmovups (%rdx), %xmm1
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0

    movss %xmm0, -4(%rbp)
    movl -4(%rbp), %eax

    addq $32, %rsp
    popq %rbp
    ret

.global vcross
vcross:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movss 4(%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    movss 8(%rcx), %xmm1
    mulss 4(%rdx), %xmm1

    subss %xmm1, %xmm0
    movss %xmm0, (%r8)

    movss (%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    movss 8(%rcx), %xmm1
    mulss (%rdx), %xmm1

    subss %xmm0, %xmm1
    movss %xmm1, 4(%r8)

    movss (%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    movss 4(%rcx), %xmm1
    mulss (%rdx), %xmm1

    subss %xmm1, %xmm0
    movss %xmm0, 8(%r8)

    addq $48, %rsp
    popq %rbp
    ret

.global free_vec
free_vec:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call free

    addq $32, %rsp
    popq %rbp
    ret

