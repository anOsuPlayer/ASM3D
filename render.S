.section .data

.global frame
frame:              .quad 0

.global exitv
exitv:          .byte   0
.global framelock
framelock:      .byte   1

.section .text

.global make_frame
make_frame:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movl screen_w(%rip), %eax
    movl screen_h(%rip), %ebx
    xorq %rdx, %rcx
    imull %ebx

    addl %ebx, %eax

    movl %eax, %ecx
    call malloc

    movq %rax, frame(%rip)

    addq $32, %rsp
    popq %rbp
    ret

.global free_frame
free_frame:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq frame(%rip), %rcx
    call free

    addq $32, %rsp
    popq %rbp
    ret
