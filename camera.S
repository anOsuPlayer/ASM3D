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

.global update_quaternion
update_quaternion:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp


    addq $128, %rsp
    popq %rbp
    ret

.global update_view
update_view:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp


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
