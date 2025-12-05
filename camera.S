.section .data

.global cpos
cpos:           .quad   0

.global orientation
orientation:

.global cyaw
cyaw:           .float  0
.global cpitch
cpitch:         .float  0
.global croll
croll:          .float  0

.global quaternion
quaternion:     .quad   0
.global VIEW
VIEW:           .quad   0

.global fov
fov:            .float  70.0

.global maxfov
maxfov:         .float  105.0
.global minfov
minfov:         .float  40.0

deffov:         .float  70.0

near:           .float  .5
far:            .float  150.0

.global ratio
ratio:          .float  0

.global PERSPECTIVE
PERSPECTIVE:    .quad   0

.section .text

.global update
update:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call update_quaternion
    call update_view
    call update_ratio
    call update_perspective

    addq $32, %rsp
    popq %rbp
    ret

.global set_camera
set_camera:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call make_vec
    movq %rax, cpos(%rip)
    call make_vec
    movq %rax, quaternion(%rip)

    call make_matrix
    movq %rax, VIEW(%rip)
    call make_matrix
    movq %rax, PERSPECTIVE(%rip)

    call center
    call update

    addq $32, %rsp
    popq %rbp
    ret

.global center
center:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq cpos(%rip), %rax
    movl $0, (%rax)
    movl $0, 4(%rax)
    movl $0, 8(%rax)

    movl $0, cyaw(%rip)
    movl $0, cpitch(%rip)
    movl $0, croll(%rip)

    movss deffov(%rip), %xmm0
    movss %xmm0, fov(%rip)

    addq $32, %rsp
    popq %rbp
    ret

d: .string "%lf %lf %lf %lf\n"

.global update_quaternion
update_quaternion:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp

    movq quaternion(%rip), %rax
    pxor %xmm0, %xmm0
    vmovups %xmm0, (%rax)

    call make_vec
    movq %rax, -8(%rbp)

    vmovups orientation(%rip), %xmm0
    movl $2, %eax
    cvtsi2ss %eax, %xmm1
    vbroadcastss %xmm1, %xmm1
    vdivps %xmm1, %xmm0, %xmm0
    vmovups %xmm0, -24(%rbp)

    movss -24(%rbp), %xmm0
    movss %xmm0, mathin(%rip)
    call msincos
    movss mathout1(%rip), %xmm0
    movss %xmm0, -48(%rbp)
    movss mathout2(%rip), %xmm0
    movss %xmm0, -44(%rbp)

    movss -20(%rbp), %xmm0
    movss %xmm0, mathin(%rip)
    call msincos
    movss mathout1(%rip), %xmm0
    movss %xmm0, -40(%rbp)
    movss mathout2(%rip), %xmm0
    movss %xmm0, -36(%rbp)

    movss -16(%rbp), %xmm0
    movss %xmm0, mathin(%rip)
    call msincos
    movss mathout1(%rip), %xmm0
    movss %xmm0, -32(%rbp)
    movss mathout2(%rip), %xmm0
    movss %xmm0, -28(%rbp)

    movq -8(%rbp), %rax
    movss -48(%rbp), %xmm0
    movss %xmm0, 12(%rax)
    movss -44(%rbp), %xmm0
    movss %xmm0, 8(%rax)

    movq quaternion(%rip), %rax
    movss -40(%rbp), %xmm0
    movss %xmm0, 12(%rax)
    movss -36(%rbp), %xmm0
    movss %xmm0, 4(%rax)

    movq -8(%rbp), %rcx
    movq quaternion(%rip), %rdx
    movq quaternion(%rip), %r8
    call qmul

    movq -8(%rbp), %rax
    
    pxor %xmm0, %xmm0
    vmovups %xmm0, (%rax)
    
    movss -32(%rbp), %xmm0
    movss %xmm0, 12(%rax)
    movss -28(%rbp), %xmm0
    movss %xmm0, (%rax)

    movq quaternion(%rip), %rcx
    movq -8(%rbp), %rdx
    movq quaternion(%rip), %r8
    call qmul

    movq quaternion(%rip), %rcx
    movq quaternion(%rip), %rdx
    call vnorm

    movq -8(%rbp), %rcx
    call free_vec

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

    movq quaternion(%rip), %rax
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

    movq quaternion(%rip), %rax
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
    movq cpos(%rip), %rdx
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
    movq cpos(%rip), %rdx
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
    movq cpos(%rip), %rdx
    call vdot
    movq %rax, %xmm0
    movss %xmm0, 44(%r15)

    movq -24(%rbp), %rcx
    call free_vec

    addq $64, %rsp
    popq %rbp
    ret

.global update_ratio
update_ratio:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movl screen_w(%rip), %eax
    subl $2, %eax
    cvtsi2ss %rax, %xmm0
    movl screen_h(%rip), %eax
    subl $2, %eax
    cvtsi2ss %rax, %xmm1
    divss %xmm1, %xmm0

    movss %xmm0, ratio(%rip)

    addq $32, %rsp
    popq %rbp
    ret

.global update_perspective
update_perspective:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movq PERSPECTIVE(%rip), %r15

    movss fov(%rip), %xmm0
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

    movss ratio(%rip), %xmm1
    divss %xmm1, %xmm0

    movss %xmm0, (%r15)

    movss far(%rip), %xmm0
    subss near(%rip), %xmm0
    rcpss %xmm0, %xmm0

    movss far(%rip), %xmm1
    mulss %xmm1, %xmm0

    movss %xmm0, 40(%r15)

    flds near(%rip)
    fchs
    fstps -4(%rbp)

    movss -4(%rbp), %xmm2
    mulss %xmm0, %xmm2

    movss %xmm2, 44(%r15)

    movq $1, %rax
    cvtsi2ss %rax, %xmm0

    movss %xmm0, 56(%r15)

    addq $48, %rsp
    popq %rbp
    ret

.global free_camera
free_camera:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq cpos(%rip), %rcx
    call free_vec
    movq quaternion(%rip), %rcx
    call free_vec

    movq VIEW(%rip), %rcx
    call free_matrix
    movq PERSPECTIVE(%rip), %rcx
    call free_matrix

    addq $32, %rsp
    popq %rbp
    ret
