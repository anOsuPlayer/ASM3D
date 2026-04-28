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
    movq VIEW(%rip), %r15
    addq %rcx, %r15
    cvtsi2ss %edx, %xmm2
    vbroadcastss %xmm2, %xmm2

    vmovups (%r15), %xmm0
    vbroadcastss DPOS(%rip), %xmm1
    vmulps %xmm0, %xmm1, %xmm0
    vmulps %xmm0, %xmm2, %xmm3

    vmovups Pos(%rip), %xmm1
    vaddps %xmm3, %xmm1, %xmm0
    vmovups %xmm0, Pos(%rip)
    
    leaq Pos(%rip), %rax
    movl $0, 12(%rax)
    ret
