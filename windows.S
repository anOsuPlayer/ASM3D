.section .data

#if defined(_WIN32)

    STDOUT_H:           .long   -11

    .align 16
    CONSOLE_INFO_BUF:
        CI_SIZE:        .long   0
        CI_CURSOR:      .long   0
        ATTRIB:         .word   0
        LEFT:           .word   0
        TOP:            .word   0
        RIGHT:          .word   0
        BOTTOM:         .word   0
        MAX_SIZE:       .long   0

#endif

.global screen_w
screen_w:           .long   0
.global screen_h
screen_h:           .long   0

.section .text

.global get_screen_size
get_screen_size:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    #if defined(_WIN32)

        movl STDOUT_H(%rip), %ecx
        call GetStdHandle

        movq %rax, %rcx
        leaq CONSOLE_INFO_BUF(%rip), %rdx
        call GetConsoleScreenBufferInfo

        movw RIGHT(%rip), %ax
        subw LEFT(%rip), %ax
        incw %ax
        cwtl

        cmpl %eax, screen_w(%rip)
        je get_screen_size0
            movb $1, framelock(%rip)
        get_screen_size0:

        movl %eax, screen_w(%rip)

        movw BOTTOM(%rip), %ax
        subw TOP(%rip), %ax
        incw %ax
        cwtl

        cmpl %eax, screen_h(%rip)
        je get_screen_size1
            movb $1, framelock(%rip)
        get_screen_size1:

        movl %eax, screen_h(%rip)

    #else

        movq $0, %rdi
        movq $0x5413, %rsi
        leaq -16(%rbp), %rdx
        call ioctl

        movzxw -16(%rbp), %ax
        cmpl %eax, screen_h(%rip)
        je get_screen_size0
            movb $1, framelock(%rip)
        get_screen_size0:

        movl %eax, screen_h(%rip)

        movzxw -14(%rbp), %ax
        cmpl %eax, screen_w(%rip)
        je get_screen_size1
            movb $1, framelock(%rip)
        get_screen_size1:

        movl %eax, screen_w(%rip)

    #endif

    addq $48, %rsp
    popq %rbp
    ret
