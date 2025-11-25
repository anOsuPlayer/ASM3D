.section .data

.global cpos
cpos:           .quad   0

.global cdir
cdir:           .quad   0
.global cup
cup:            .quad   0
cright:         .quad   0

.global axy
axy:            .float  0
.global ayz
ayz:            .float  0

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

    call update_direction
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
    movq %rax, cdir(%rip)
    call make_vec
    movq %rax, cup(%rip)
    call make_vec
    movq %rax, cright(%rip)

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

    movq cdir(%rip), %rax
    movl $0, (%rax)
    movl $0, 4(%rax)
    movl $0, 8(%rax)

    movq cup(%rip), %rax
    movl $0, (%rax)
    movl $0, 4(%rax)
    movl $0, 8(%rax)

    movl $0, axy(%rip)
    movl $0, ayz(%rip)

    movss deffov(%rip), %xmm0
    movss %xmm0, fov(%rip)

    addq $32, %rsp
    popq %rbp
    ret

.global update_direction
update_direction:
    pushq %rbp
    movq %rsp, %rbp
    subq $92, %rsp

    movss axy(%rip), %xmm0
    movss %xmm0, mathin(%rip)
    call wsincos
    movss mathout1(%rip), %xmm0
    movss %xmm0, -4(%rbp)
    movss mathout2(%rip), %xmm0
    movss %xmm0, -8(%rbp)

    movss ayz(%rip), %xmm0
    movss %xmm0, mathin(%rip)
    call wsincos
    movss mathout1(%rip), %xmm0
    movss %xmm0, -12(%rbp)
    movss mathout2(%rip), %xmm0
    movss %xmm0, -16(%rbp)

    movq cdir(%rip), %rax

    movss -4(%rbp), %xmm0
    movss -12(%rbp), %xmm1
    vmulss %xmm0, %xmm1, %xmm0
    movss %xmm0, (%rax)

    movss -8(%rbp), %xmm0
    movss -12(%rbp), %xmm1
    vmulss %xmm0, %xmm1, %xmm0
    movss %xmm0, 4(%rax)

    movl -16(%rbp), %ecx
    movl %ecx, 8(%rax)

    call make_vec
    movq %rax, -24(%rbp)

    movq $1, %rcx
    cvtsi2ss %rcx, %xmm0
    movss %xmm0, 8(%rax)

    movq cdir(%rip), %rcx
    movq -24(%rbp), %rdx
    movq cright(%rip), %r8
    call vcross

    movq cright(%rip), %rcx
    movq cdir(%rip), %rdx
    movq cup(%rip), %r8
    call vcross

    movq -24(%rbp), %rcx
    call free_vec

    addq $92, %rsp
    popq %rbp
    ret

.global update_view
update_view:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movq VIEW(%rip), %r15

    call make_vec
    movq %rax, -8(%rbp)

    movq cright(%rip), %rcx
    vmovups (%rcx), %xmm0
    vmovups %xmm0, (%r15)

    movq cup(%rip), %rcx
    vmovups (%rcx), %xmm0
    vmovups %xmm0, 16(%r15)

    movq cdir(%rip), %rcx
    vmovups (%rcx), %xmm0
    vmovups %xmm0, 32(%r15)

    movq -8(%rbp), %rax

    movq cright(%rip), %rcx
    movq %rax, %rdx
    call vneg
    movq %rax, %rcx
    movq cpos(%rip), %rdx
    call vdot
    movl %eax, 48(%r15)

    movq -8(%rbp), %rax

    movq cup(%rip), %rcx
    movq %rax, %rdx
    call vneg
    movq %rax, %rcx
    movq cpos(%rip), %rdx
    call vdot
    movl %eax, 52(%r15)

    movq -8(%rbp), %rax

    movq cdir(%rip), %rcx
    movq %rax, %rdx
    call vneg
    movq %rax, %rcx
    movq cpos(%rip), %rdx
    call vdot
    movl %eax, 56(%r15)

    movq $1, %rax
    cvtsi2ss %rax, %xmm0
    movss %xmm0, 60(%r15)

    movq -8(%rbp), %rcx
    call free_vec

    addq $48, %rsp
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
    movq cdir(%rip), %rcx
    call free_vec
    movq cup(%rip), %rcx
    call free_vec
    movq cright(%rip), %rcx
    call free_vec

    movq VIEW(%rip), %rcx
    call free_matrix
    movq PERSPECTIVE(%rip), %rcx
    call free_matrix

    addq $32, %rsp
    popq %rbp
    ret
