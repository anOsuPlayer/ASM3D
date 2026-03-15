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

    vpxorq %xmm0, %xmm0, %xmm0
    vmovups %xmm0, (%rax)

    addq $32, %rsp
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

.global make_matrix
make_matrix:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq $64, %rcx
    call malloc

    vpxorq %zmm1, %zmm1, %zmm1
    vmovups %zmm1, (%rax)

    addq $32, %rsp
    popq %rbp
    ret

.global free_matrix
free_matrix:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call free

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
    pxor %xmm2, %xmm2
    vhaddps %xmm0, %xmm0, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0

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


.global mulmv
mulmv:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp
    
    vmovups (%rcx), %xmm0
    vmovups (%rdx), %xmm1
    vmulps %xmm0, %xmm1, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    vhaddps %xmm0, %xmm0, %xmm1
    movss %xmm1, (%r8)

    vmovups 16(%rcx), %xmm0
    vmovups (%rdx), %xmm1
    vmulps %xmm0, %xmm1, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    vhaddps %xmm0, %xmm0, %xmm1
    movss %xmm1, 4(%r8)

    vmovups 32(%rcx), %xmm0
    vmovups (%rdx), %xmm1
    vmulps %xmm0, %xmm1, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    vhaddps %xmm0, %xmm0, %xmm1
    movss %xmm1, 8(%r8)

    vmovups 48(%rcx), %xmm0
    vmovups (%rdx), %xmm1
    vmulps %xmm0, %xmm1, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    vhaddps %xmm0, %xmm0, %xmm1
    movss %xmm1, 12(%r8)

    addq $48, %rsp
    popq %rbp
    ret

.global mulqq
mulqq:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp


    addq $64, %rsp
    popq %rbp
    ret
