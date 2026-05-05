.section .data

.global DPOS
DPOS:           .float .03125
.global DROT
DROT:           .float .001745

.global SPEED
SPEED:          .float 1.0
.global SENS
SENS:           .float 1.0

.section .text
.global directional_move
directional_move:
    movq CCURRENT(%rip), %r14

    movq 8(%r14), %r15
    addq %rcx, %r15
    vbroadcastss %xmm1, %xmm2

    vmovups (%r15), %xmm0
    vbroadcastss DPOS(%rip), %xmm1
    vmulps %xmm0, %xmm1, %xmm0
    vmulps %xmm0, %xmm2, %xmm3

    movq 24(%r14), %rax

    vmovups (%rax), %xmm1
    vaddps %xmm3, %xmm1, %xmm0
    vmovups %xmm0, (%rax)
    
    leaq (%rax), %rax
    movl $0, 12(%rax)
    ret
