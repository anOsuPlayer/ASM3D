.section .data

.global VIEW
VIEW:           .quad   0
.global PERSPECTIVE
PERSPECTIVE:    .quad   0
.global QUATERNION
QUATERNION:     .quad   0

.align 16
.global Angle
Angle:
    Yaw:    .float  0
    Pitch:  .float  0
    Roll:   .float  0

.align 16
.global Pos
Pos:
    CX:     .float  0
    CY:     .float  0
    CZ:     .float  0

.section .text
.global setup_camera
setup_camera:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    vpxorq %xmm0, %xmm0, %xmm0
    vmovups %xmm0, Angle(%rip)
    vmovups %xmm0, Pos(%rip)

    call make_vec
    movq %rax, QUATERNION(%rip)

    call make_matrix
    movq %rax, VIEW(%rip)

    call make_matrix
    movq %rax, PERSPECTIVE(%rip)

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
