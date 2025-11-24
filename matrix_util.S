.section .data



.section .text

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

.global mult_matrix_vec
mult_matrix_vec:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    vmovups (%rdx), %xmm1
    vpxor %xmm2, %xmm2, %xmm2

    vmovups (%rcx), %xmm0
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    movss %xmm0, (%r8)

    vmovups 16(%rcx), %xmm0
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    movss %xmm0, 4(%r8)

    vmovups 32(%rcx), %xmm0
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    movss %xmm0, 8(%r8)

    vmovups 48(%rcx), %xmm0
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    vhaddps %xmm0, %xmm0, %xmm0
    movss %xmm0, 12(%r8)

    addq $48, %rsp
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
