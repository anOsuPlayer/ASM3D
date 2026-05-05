.section .data

.global CCURRENT
CCURRENT:       .quad   0

.global AR
AR:             .float  0

.global Width
Width:          .float  0
.global Height    
Height:         .float  0

.section .text
.global update
update:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call update_quaternion
    call update_view
    call update_perspective

    addq $32, %rsp
    popq %rbp
    ret

.global update_quaternion
update_quaternion:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp

    movq CCURRENT(%rip), %r14

    movq 24(%r14), %rax
    vmovups 16(%rax), %xmm0

    movq $2, %rax
    cvtsi2ss %rax, %xmm2
    vbroadcastss %xmm2, %xmm2
    vdivps %xmm2, %xmm0, %xmm0
    
    vmovups %xmm0, -16(%rbp)
    
    vpxor %xmm0, %xmm0, %xmm0

    vmovups %xmm0, -32(%rbp)
    vmovups %xmm0, -48(%rbp)
    vmovups %xmm0, -64(%rbp)

    movss -16(%rbp), %xmm0
    call qcos
    movss %xmm0, -20(%rbp)
    movss -16(%rbp), %xmm0
    call qsin
    movss %xmm0, -24(%rbp)

    movss -12(%rbp), %xmm0
    call qcos
    movss %xmm0, -36(%rbp)
    movss -12(%rbp), %xmm0
    call qsin
    movss %xmm0, -44(%rbp)

    leaq -32(%rbp), %rcx
    leaq -48(%rbp), %rdx
    leaq -64(%rbp), %r8
    call mulqq

    vpxor %xmm0, %xmm0, %xmm0
    vmovups %xmm0, -48(%rbp)

    movss -8(%rbp), %xmm0
    call qcos
    movss %xmm0, -36(%rbp)
    movss -8(%rbp), %xmm0
    call qsin
    movss %xmm0, -48(%rbp)

    leaq -64(%rbp), %rcx
    leaq -48(%rbp), %rdx
    movq (%r14), %r8
    call mulqq

    addq $96, %rsp
    popq %rbp
    ret

.global update_view
update_view:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movq CCURRENT(%rip), %r14

    movq 8(%r14), %r15

    movq $1, %rax
    cvtsi2ss %rax, %xmm0
    movss %xmm0, 4(%r15)
    movss %xmm0, 24(%r15)
    movss %xmm0, 32(%r15)
    movss %xmm0, 60(%r15)

    movq (%r14), %rax
    vmovups (%rax), %xmm0
    vmovups %xmm0, -32(%rbp)
    
    movq $2, %rax
    cvtsi2ss %rax, %xmm2
    vbroadcastss %xmm2, %xmm2

    vmulps %xmm0, %xmm0, %xmm0
    vmulps %xmm2, %xmm0, %xmm0
    vmovups %xmm0, -16(%rbp)

    movss -16(%rbp), %xmm0
    addss -8(%rbp), %xmm0
    movss 4(%r15), %xmm1
    subss %xmm0, %xmm1
    movss %xmm1, 4(%r15)

    movss -16(%rbp), %xmm0
    addss -12(%rbp), %xmm0
    movss 24(%r15), %xmm1
    subss %xmm0, %xmm1
    movss %xmm1, 24(%r15)

    movss -12(%rbp), %xmm0
    addss -8(%rbp), %xmm0
    movss 32(%r15), %xmm1
    subss %xmm0, %xmm1
    movss %xmm1, 32(%r15)

    movss -32(%rbp), %xmm0
    mulss -28(%rbp), %xmm0
    movss -24(%rbp), %xmm1
    mulss -20(%rbp), %xmm1
    subss %xmm1, %xmm0
    mulss %xmm2, %xmm0
    movss %xmm0, (%r15)

    movss -24(%rbp), %xmm0
    mulss -28(%rbp), %xmm0
    movss -32(%rbp), %xmm1
    mulss -20(%rbp), %xmm1
    addss %xmm1, %xmm0
    mulss %xmm2, %xmm0
    movss %xmm0, 8(%r15)

    movss -32(%rbp), %xmm0
    mulss -24(%rbp), %xmm0
    movss -20(%rbp), %xmm1
    mulss -28(%rbp), %xmm1
    addss %xmm1, %xmm0
    mulss %xmm2, %xmm0
    movss %xmm0, 16(%r15)

    movss -28(%rbp), %xmm0
    mulss -24(%rbp), %xmm0
    movss -20(%rbp), %xmm1
    mulss -32(%rbp), %xmm1
    subss %xmm1, %xmm0
    mulss %xmm2, %xmm0
    movss %xmm0, 20(%r15)

    movss -32(%rbp), %xmm0
    mulss -28(%rbp), %xmm0
    movss -24(%rbp), %xmm1
    mulss -20(%rbp), %xmm1
    addss %xmm1, %xmm0
    mulss %xmm2, %xmm0
    movss %xmm0, 36(%r15)

    movss -32(%rbp), %xmm0
    mulss -24(%rbp), %xmm0
    movss -28(%rbp), %xmm1
    mulss -20(%rbp), %xmm1
    subss %xmm1, %xmm0
    mulss %xmm2, %xmm0
    movss %xmm0, 40(%r15)

    movq 24(%r14), %rax
    
    leaq (%rax), %rcx
    leaq -48(%rbp), %rdx
    call vneg

    leaq -48(%rbp), %rcx
    movq %r15, %rdx
    call vdot
    movl %eax, 12(%r15)

    addq $16, %r15

    movl $0, 12(%r15)
    leaq -48(%rbp), %rcx
    movq %r15, %rdx
    call vdot
    movl %eax, 12(%r15)

    addq $16, %r15

    movl $0, 12(%r15)
    leaq -48(%rbp), %rcx
    movq %r15, %rdx
    call vdot
    movl %eax, 12(%r15)

    addq $64, %rsp
    popq %rbp
    ret

.global update_perspective
update_perspective:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movq CCURRENT(%rip), %r14

    movq 16(%r14), %r15

    fldpi
    movl $360, %eax
    cvtsi2ss %eax, %xmm0
    movss %xmm0, -4(%rbp)
    fdivs -4(%rbp)
    fmuls 32(%r14)
    fptan
    fdiv %st(1), %st(0)
    fsts 20(%r15)
    fdivs AR(%rip)
    fstps (%r15)
    fstps -4(%rbp)

    fld1
    fstps 56(%r15)

    movss 40(%r14), %xmm0
    addss 36(%r14), %xmm0
    movss 40(%r14), %xmm1
    subss 36(%r14), %xmm1
    divss %xmm1, %xmm0
    movss %xmm0, 40(%r15)

    movq $-2, %rax
    cvtsi2ss %rax, %xmm2
    movss 40(%r14), %xmm0
    mulss 36(%r14), %xmm0
    mulss %xmm2, %xmm0
    divss %xmm1, %xmm0
    movss %xmm0, 44(%r15)

    addq $64, %rsp
    popq %rbp
    ret
