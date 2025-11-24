.section .data

frame:          .quad   0

.global exitv
exitv:          .byte   0
.global framelock
framelock:      .byte   1

clear:          .string "cls"

statpos:        .ascii "x:%+08.3lf y:%+08.3lf z:%+08.3lf"
statdir:        .ascii "dx:%+08.3lf dy:%+08.3lf dz:%+08.3lf"
statcup:        .ascii "ux:%+08.3lf uy:%+08.3lf uz:%+08.3lf"
statang:        .ascii "axy:%+08.5lf ayz:%+08.5lf"
statcam:        .ascii "fov:%+08.3lf ar:%+08.5lf"

newline:        .byte   10
border:         .byte   35
void:           .byte   32

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

.global style_frame
style_frame:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movl $0, -4(%rbp)
    movq frame(%rip), %rax

    movl $0, -8(%rbp)
    style_frame0:

        cmpl $0, -4(%rbp)
        je style_frame2

            movl -4(%rbp), %ecx
            movb newline(%rip), %bl

            movb %bl, (%rax, %rcx, 1)

            incl -4(%rbp)

        style_frame2:

        movl $0, -12(%rbp)
        style_frame1:

            movl -4(%rbp), %ecx
            
            cmpl $0, -12(%rbp)
            je style_frame3

            cmpl $0, -8(%rbp)
            je style_frame3

            movl screen_w(%rip), %edx
            decl %edx
            cmpl %edx, -12(%rbp)
            je style_frame3

            movl screen_h(%rip), %edx
            decl %edx
            cmpl %edx, -8(%rbp)
            je style_frame3
            
                movb void(%rip), %bl
                jmp style_frame4
            
            style_frame3:
            
                movb border(%rip), %bl
            
            style_frame4:

            movb %bl, (%rax, %rcx, 1)

            incl -4(%rbp)
        
        incl -12(%rbp)
        movl screen_w(%rip), %edx
        cmpl %edx, -12(%rbp)
        jl style_frame1

    incl -8(%rbp)
    movl screen_h(%rip), %edx
    cmpl %edx, -8(%rbp)
    jl style_frame0

    movl -4(%rbp), %ecx
    movb $0, (%rax, %rcx, 1)

    addq $3, %rax
    movl screen_w(%rip), %ebx
    addq %rbx, %rax

    movq %rax, %rcx
    leaq statpos(%rip), %rdx
    movq $32, %r8
    call memcpy

    incq %rcx
    addq %rbx, %rcx

    leaq statdir(%rip), %rdx
    movq $35, %r8
    call memcpy

    incq %rcx
    addq %rbx, %rcx

    leaq statcup(%rip), %rdx
    movq $35, %r8
    call memcpy

    incq %rcx
    addq %rbx, %rcx

    leaq statang(%rip), %rdx
    movq $25, %r8
    call memcpy

    incq %rcx
    addq %rbx, %rcx

    leaq statcam(%rip), %rdx
    movq $24, %r8
    call memcpy

    addq $64, %rsp
    popq %rbp
    ret

.global print_frame
print_frame:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp

    movq cpos(%rip), %rax

    movl (%rax), %ecx
    call ss2sd
    movq %rcx, %rdx

    movl 4(%rax), %ecx
    call ss2sd
    movq %rcx, %r8
    
    movl 8(%rax), %ecx
    call ss2sd
    movq %rcx, %r9

    movq cdir(%rip), %rax

    movl (%rax), %ecx
    call ss2sd
    movq %rcx, 32(%rsp)

    movl 4(%rax), %ecx
    call ss2sd
    movq %rcx, 40(%rsp)
    
    movl 8(%rax), %ecx
    call ss2sd
    movq %rcx, 48(%rsp)

    movq cup(%rip), %rax

    movl (%rax), %ecx
    call ss2sd
    movq %rcx, 56(%rsp)

    movl 4(%rax), %ecx
    call ss2sd
    movq %rcx, 64(%rsp)
    
    movl 8(%rax), %ecx
    call ss2sd
    movq %rcx, 72(%rsp)

    movl axy(%rip), %ecx
    call ss2sd
    movq %rcx, 80(%rsp)

    movl ayz(%rip), %ecx
    call ss2sd
    movq %rcx, 88(%rsp)

    movl fov(%rip), %ecx
    call ss2sd
    movq %rcx, 96(%rsp)

    movl ratio(%rip), %ecx
    call ss2sd
    movq %rcx, 104(%rsp)

    movq $0, %rax
    movq frame(%rip), %rcx

    call printf

    addq $128, %rsp
    popq %rbp
    ret

.global clear_frame
clear_frame:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    leaq clear(%rip), %rcx
    call system

    addq $32, %rsp
    popq %rbp
    ret

.global free_frame
free_frame:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    cmpq $0, frame(%rip)
    je free_frame0

        movq frame(%rip), %rcx
        call free
    
    free_frame0:

    addq $32, %rsp
    popq %rbp
    ret

.global buffer_frame
buffer_frame:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    call get_screen_size

    leaq framelock(%rip), %rcx
    movb $1, %dl
    call twait_flag

    movb $0, framelock(%rip)

    cmpb $1, rebuffer(%rip)
    jne buffer_frame0
        
        call free_frame
        call make_frame
        call style_frame

        call update

        call render_assets

        movb $0, rebuffer(%rip)

    buffer_frame0:

    addq $48, %rsp
    popq %rbp
    ret

.global render
render:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    render0:
        call buffer_frame

        call clear_frame
        call print_frame

    cmpb $1, exitv(%rip)
    jne render0

    call free_frame

    addq $48, %rsp
    popq %rbp
    ret
