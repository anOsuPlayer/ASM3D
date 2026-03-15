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

.align 16
.global Pos
Pos:
    x:      .float  0
    y:      .float  0
    z:      .float  0

.global FOV    
FOV:        .float  70.0
.global AR
AR:         .float  0

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

    

    addq $96, %rsp
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

.global update_perspective
update_perspective:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp



    addq $64, %rsp
    popq %rbp
    ret
