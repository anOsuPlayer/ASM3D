.section .data

.global QUATERNION
QUATERNION:     .quad   0
.global VIEW
VIEW:           .quad   0
.global PERSPECTIVE
PERSPECTIVE:    .quad   0

.align 16
.global Angle
Angle:
    yaw:    .float  0
    pitch:  .float  0
    roll:   .float  0
    .float          0

.align 16
.global Pos
Pos:
    x:      .float  0
    y:      .float  0
    z:      .float  0
    .float          0

.global FOV    
FOV:        .float  70.0
.global AR
AR:         .float  0
.global Near
Near:       .float  .5
.global Far
Far:        .float  150.0

.section .text
.global setup_camera
setup_camera:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call make_vec
    movq %rax, QUATERNION(%rip)

    call make_matrix
    movq %rax, VIEW(%rip)

    call make_matrix
    movq %rax, PERSPECTIVE(%rip)

    call update

    addq $32, %rsp
    popq %rbp
    ret

.global free_camera
free_camera:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq QUATERNION(%rip), %rcx
    call free_vec

    movq VIEW(%rip), %rcx
    call free_matrix

    movq PERSPECTIVE(%rip), %rcx
    call free_matrix

    addq $32, %rsp
    popq %rbp
    ret

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

    vmovups Angle(%rip), %xmm0

    movq $2, %rax
    cvtsi2ss %rax, %xmm2
    vbroadcastss %xmm2, %xmm2
    vdivps %xmm2, %xmm0, %xmm0
    
    vmovups %xmm0, -16(%rbp)
    
    vpxorq %xmm0, %xmm0, %xmm0

    vmovups %xmm0, -32(%rbp)
    vmovups %xmm0, -48(%rbp)
    vmovups %xmm0, -64(%rbp)

    flds -16(%rbp)
    fsincos
    fstps -20(%rbp)
    fstps -24(%rbp)

    flds -12(%rbp)
    fsincos
    fstps -36(%rbp)
    fstps -44(%rbp)

    leaq -32(%rbp), %rcx
    leaq -48(%rbp), %rdx
    leaq -64(%rbp), %r8
    call mulqq

    vmovups %xmm0, -48(%rbp)
    flds -8(%rbp)
    fsincos
    fstps -36(%rbp)
    fstps -48(%rbp)

    leaq -64(%rbp), %rcx
    leaq -48(%rbp), %rdx
    movq QUATERNION(%rip), %r8
    call mulqq

    addq $96, %rsp
    popq %rbp
    ret

.global update_view
update_view:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movq VIEW(%rip), %r15

    movl $1, %eax
    cvtsi2ss %eax, %xmm0
    movss %xmm0, (%r15)
    movss %xmm0, 20(%r15)
    movss %xmm0, 40(%r15)
    movss %xmm0, 60(%r15)

    movq QUATERNION(%rip), %rax
    vmovups (%rax), %xmm0
    vmulps %xmm0, %xmm0, %xmm0
    vmovups %xmm0, -16(%rbp)

    movl $2, %eax
    cvtsi2ss %eax, %xmm2

    movss -12(%rbp), %xmm0
    addss -8(%rbp), %xmm0
    mulss %xmm2, %xmm0
    movss (%r15), %xmm1
    subss %xmm0, %xmm1
    movss %xmm1, (%r15)

    movss -16(%rbp), %xmm0
    addss -8(%rbp), %xmm0
    mulss %xmm2, %xmm0
    movss 20(%r15), %xmm1
    subss %xmm0, %xmm1
    movss %xmm1, 20(%r15)

    movss -16(%rbp), %xmm0
    addss -12(%rbp), %xmm0
    mulss %xmm2, %xmm0
    movss 40(%r15), %xmm1
    subss %xmm0, %xmm1
    movss %xmm1, 40(%r15)

    movq QUATERNION(%rip), %rax
    vmovups (%rax), %xmm0
    vmovups %xmm0, -16(%rbp)

    movss -16(%rbp), %xmm0
    mulss -12(%rbp), %xmm0
    movss -8(%rbp), %xmm1
    mulss -4(%rbp), %xmm1

    vsubss %xmm0, %xmm1, %xmm3
    mulss %xmm2, %xmm3
    movss %xmm3, 4(%r15)
    vaddss %xmm0, %xmm1, %xmm3
    mulss %xmm2, %xmm3
    movss %xmm3, 16(%r15)

    movss -16(%rbp), %xmm0
    mulss -8(%rbp), %xmm0
    movss -12(%rbp), %xmm1
    mulss -4(%rbp), %xmm1

    vsubss %xmm0, %xmm1, %xmm3
    mulss %xmm2, %xmm3
    movss %xmm3, 32(%r15)
    vaddss %xmm0, %xmm1, %xmm3
    mulss %xmm2, %xmm3
    movss %xmm3, 8(%r15)

    movss -12(%rbp), %xmm0
    mulss -8(%rbp), %xmm0
    movss -16(%rbp), %xmm1
    mulss -4(%rbp), %xmm1

    vsubss %xmm0, %xmm1, %xmm3
    mulss %xmm2, %xmm3
    movss %xmm3, 24(%r15)
    vaddss %xmm0, %xmm1, %xmm3
    mulss %xmm2, %xmm3
    movss %xmm3, 36(%r15)

    call make_vec
    movq %rax, -24(%rbp)

    vmovups (%r15), %xmm0
    vmovups %xmm0, (%rax)
    movq %rax, %rcx
    movq %rax, %rdx
    call vneg
    movq %rax, %rcx
    leaq Pos(%rip), %rdx
    call vdot
    movq %rax, %xmm0
    movss %xmm0, 12(%r15)

    movq -24(%rbp), %rax
    vmovups 16(%r15), %xmm0
    vmovups %xmm0, (%rax)
    movq %rax, %rcx
    movq %rax, %rdx
    call vneg
    movq %rax, %rcx
    leaq Pos(%rip), %rdx
    call vdot
    movq %rax, %xmm0
    movss %xmm0, 28(%r15)

    movq -24(%rbp), %rax
    vmovups 32(%r15), %xmm0
    vmovups %xmm0, (%rax)
    movq %rax, %rcx
    movq %rax, %rdx
    call vneg
    movq %rax, %rcx
    leaq Pos(%rip), %rdx
    call vdot
    movq %rax, %xmm0
    movss %xmm0, 44(%r15)

    movq -24(%rbp), %rcx
    call free_vec

    addq $64, %rsp
    popq %rbp
    ret

.global update_perspective
update_perspective:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movq PERSPECTIVE(%rip), %r15

    movss FOV(%rip), %xmm0
    movss %xmm0, -4(%rbp)

    movq $360, %rcx
    cvtsi2ss %rcx, %xmm0
    movss %xmm0, -8(%rbp)

    flds -4(%rbp)
    fldpi
    fmul %st(1)
    fstp %st(1)
    flds -8(%rbp)
    fdivr %st(1)
    fptan
    fstps -4(%rbp)
    fstps -4(%rbp)

    movss -4(%rbp), %xmm0
    rcpss %xmm0, %xmm0

    fstp %st(0)

    movss %xmm0, 20(%r15)

    movss AR(%rip), %xmm1
    divss %xmm1, %xmm0

    movss %xmm0, (%r15)

    movss Far(%rip), %xmm0
    subss Near(%rip), %xmm0
    rcpss %xmm0, %xmm0

    movss Far(%rip), %xmm1
    mulss %xmm1, %xmm0

    movss %xmm0, 40(%r15)

    flds Near(%rip)
    fchs
    fstps -4(%rbp)

    movss -4(%rbp), %xmm2
    mulss %xmm0, %xmm2

    movss %xmm2, 44(%r15)

    movq $1, %rax
    cvtsi2ss %rax, %xmm0

    movss %xmm0, 56(%r15)

    addq $64, %rsp
    popq %rbp
    ret
