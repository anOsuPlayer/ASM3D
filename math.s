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

    vpxor %xmm0, %xmm0, %xmm0
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

    vpxor %ymm1, %ymm1, %ymm1
    vmovups %ymm1, (%rax)
    vmovups %ymm1, 32(%rax)

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
    vmovups (%rcx), %xmm0
    vmulps %xmm0, %xmm0, %xmm0
    vhaddps %xmm0, %xmm0, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    sqrtss %xmm0, %xmm0

    movss %xmm0, -4(%rbp)
    movl -4(%rbp), %eax

    ret

.global vneg
vneg:
    vmovups (%rcx), %xmm0
    vmovups negate_mask(%rip), %xmm1
    vmulps %xmm0, %xmm1, %xmm0
    vmovups %xmm0, (%rdx)

    ret

.global vnorm
vnorm:
    call vmod
    movl %eax, -4(%rbp)
    vbroadcastss -4(%rbp), %xmm0

    vmovups (%rcx), %xmm1
    vdivps %xmm0, %xmm1, %xmm0

    vmovups %xmm0, (%rdx)

    ret

.global vndc
vndc:
    vbroadcastss 12(%rcx), %xmm0
    vmovups (%rcx), %xmm1
    vdivps %xmm0, %xmm1, %xmm0
    vmovups %xmm0, (%rdx)

    ret

.global vdot
vdot:
    vmovups (%rcx), %xmm0
    vmovups (%rdx), %xmm1
    vmulps %xmm0, %xmm1, %xmm0
    pxor %xmm2, %xmm2
    vhaddps %xmm0, %xmm0, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0

    movss %xmm0, -4(%rbp)
    movl -4(%rbp), %eax

    ret

.global vcross
vcross:
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

    ret

.global _256_mulmv
_256_mulmv:
    vmovups (%rdx), %xmm1

    vmovups (%rcx), %xmm0
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    movss %xmm0, (%r8)

    vmovups 16(%rcx), %xmm0
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    movss %xmm0, 4(%r8)

    vmovups 32(%rcx), %xmm0
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    movss %xmm0, 8(%r8)

    vmovups 48(%rcx), %xmm0
    vmulps %xmm0, %xmm1, %xmm0
    vhaddps %xmm0, %xmm0, %xmm2
    vhaddps %xmm2, %xmm2, %xmm0
    movss %xmm0, 12(%r8)

    ret

.global _512_mulmv
_512_mulmv:
    vmovups (%rcx), %zmm1
    vbroadcasti32x4 (%rdx), %zmm2
    vmulps %zmm1, %zmm2, %zmm1

    vmovshdup %zmm1, %zmm2
    vaddps %zmm2, %zmm1, %zmm1
    vpermilps $0x4E, %zmm1, %zmm2
    vaddps %zmm2, %zmm1, %zmm1

    movl $0x1111, %eax 
    kmovw %eax, %k1
    vcompressps %zmm1, %zmm1 {%k1}{z}
    vmovups %xmm1, (%r8)

    ret

.global _256_mulqq
_256_mulqq:
    movss 12(%rcx), %xmm0
    mulss (%rdx), %xmm0
    movss %xmm0, %xmm1
    movss (%rcx), %xmm0
    mulss 12(%rdx), %xmm0
    addss %xmm0, %xmm1
    movss 4(%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    addss %xmm0, %xmm1
    movss 8(%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    subss %xmm0, %xmm1

    movss %xmm1, (%r8)

    movss 12(%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    movss %xmm0, %xmm1
    movss (%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    subss %xmm0, %xmm1
    movss 4(%rcx), %xmm0
    mulss 12(%rdx), %xmm0
    addss %xmm0, %xmm1
    movss 8(%rcx), %xmm0
    mulss (%rdx), %xmm0
    addss %xmm0, %xmm1

    movss %xmm1, 4(%r8)

    movss 12(%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    movss %xmm0, %xmm1
    movss (%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    addss %xmm0, %xmm1
    movss 4(%rcx), %xmm0
    mulss (%rdx), %xmm0
    subss %xmm0, %xmm1
    movss 8(%rcx), %xmm0
    mulss 12(%rdx), %xmm0
    addss %xmm0, %xmm1

    movss %xmm1, 8(%r8)

    movss 12(%rcx), %xmm0
    mulss 12(%rdx), %xmm0
    movss %xmm0, %xmm1
    movss (%rcx), %xmm0
    mulss (%rdx), %xmm0
    subss %xmm0, %xmm1
    movss 4(%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    subss %xmm0, %xmm1
    movss 8(%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    subss %xmm0, %xmm1

    movss %xmm1, 12(%r8)

    ret

.global _512_mulqq
_512_mulqq:
    movss 12(%rcx), %xmm0
    mulss (%rdx), %xmm0
    movss %xmm0, %xmm1
    movss (%rcx), %xmm0
    mulss 12(%rdx), %xmm0
    addss %xmm0, %xmm1
    movss 4(%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    addss %xmm0, %xmm1
    movss 8(%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    subss %xmm0, %xmm1

    movss %xmm1, (%r8)

    movss 12(%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    movss %xmm0, %xmm1
    movss (%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    subss %xmm0, %xmm1
    movss 4(%rcx), %xmm0
    mulss 12(%rdx), %xmm0
    addss %xmm0, %xmm1
    movss 8(%rcx), %xmm0
    mulss (%rdx), %xmm0
    addss %xmm0, %xmm1

    movss %xmm1, 4(%r8)

    movss 12(%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    movss %xmm0, %xmm1
    movss (%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    addss %xmm0, %xmm1
    movss 4(%rcx), %xmm0
    mulss (%rdx), %xmm0
    subss %xmm0, %xmm1
    movss 8(%rcx), %xmm0
    mulss 12(%rdx), %xmm0
    addss %xmm0, %xmm1

    movss %xmm1, 8(%r8)

    movss 12(%rcx), %xmm0
    mulss 12(%rdx), %xmm0
    movss %xmm0, %xmm1
    movss (%rcx), %xmm0
    mulss (%rdx), %xmm0
    subss %xmm0, %xmm1
    movss 4(%rcx), %xmm0
    mulss 4(%rdx), %xmm0
    subss %xmm0, %xmm1
    movss 8(%rcx), %xmm0
    mulss 8(%rdx), %xmm0
    subss %xmm0, %xmm1

    movss %xmm1, 12(%r8)

    ret
