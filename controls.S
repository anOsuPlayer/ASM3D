.section .data

CONTROL_THREAD:         .long   0

.align 16
move_forward:           .byte   119
move_back:              .byte   115
move_left:              .byte   97
move_right:             .byte   100
move_up:                .byte   122
move_down:              .byte   120

look_up:                .byte   105
look_down:              .byte   107
look_left:              .byte   106
look_right:             .byte   108
roll_left:              .byte   117
roll_right:             .byte   111

fov_up:                 .byte   99
fov_down:               .byte   118

reset:                  .byte   114
reload:                 .byte   101
quit:                   .byte   113

dfov:                   .float  .5
dm:                     .float  .2
dl:                     .float  .01745

.section .text

.global start_input
start_input:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    leaq CONTROL_THREAD(%rip), %rcx
    leaq input(%rip), %rdx
    call start_thread

    addq $32, %rsp
    popq %rbp
    ret

.global join_input
join_input:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq CONTROL_THREAD(%rip), %rcx
    call join_thread

    addq $32, %rsp
    popq %rbp
    ret

.global input
input:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    input0:
        movb $1, framelock(%rip)

        call _getch
        cmpb %al, quit(%rip)
        je input1

        movq cpos(%rip), %rcx

        cmpb move_forward(%rip), %al
        jne input2
            movss (%rcx), %xmm0
            addss dm(%rip), %xmm0
            movss %xmm0, (%rcx)
            jmp inputend
        input2:
        cmpb move_back(%rip), %al
        jne input3
            movss (%rcx), %xmm0
            subss dm(%rip), %xmm0
            movss %xmm0, (%rcx)
            jmp inputend
        input3:
        cmpb move_left(%rip), %al
        jne input4
            movss 4(%rcx), %xmm0
            addss dm(%rip), %xmm0
            movss %xmm0, 4(%rcx)
            jmp inputend
        input4:
        cmpb move_right(%rip), %al
        jne input5
            movss 4(%rcx), %xmm0
            subss dm(%rip), %xmm0
            movss %xmm0, 4(%rcx)
            jmp inputend
        input5:
        cmpb move_up(%rip), %al
        jne input6
            movss 8(%rcx), %xmm0
            addss dm(%rip), %xmm0
            movss %xmm0, 8(%rcx)
            jmp inputend
        input6:
        cmpb move_down(%rip), %al
        jne input7
            movss 8(%rcx), %xmm0
            subss dm(%rip), %xmm0
            movss %xmm0, 8(%rcx)
            jmp inputend
        input7:

        cmpb look_up(%rip), %al
        jne input8
            movss cpitch(%rip), %xmm0
            addss dl(%rip), %xmm0
            movss %xmm0, cpitch(%rip)
            jmp inputend
        input8:
        cmpb look_down(%rip), %al
        jne input9
            movss cpitch(%rip), %xmm0
            subss dl(%rip), %xmm0
            movss %xmm0, cpitch(%rip)
            jmp inputend
        input9:
        cmpb look_left(%rip), %al
        jne input10
            movss cyaw(%rip), %xmm0
            addss dl(%rip), %xmm0
            movss %xmm0, cyaw(%rip)
            jmp inputend
        input10:
        cmpb look_right(%rip), %al
        jne input11
            movss cyaw(%rip), %xmm0
            subss dl(%rip), %xmm0
            movss %xmm0, cyaw(%rip)
            jmp inputend
        input11:
        cmpb roll_left(%rip), %al
        jne input12
            movss croll(%rip), %xmm0
            addss dl(%rip), %xmm0
            movss %xmm0, croll(%rip)
            jmp inputend
        input12:
        cmpb roll_right(%rip), %al
        jne input13
            movss croll(%rip), %xmm0
            subss dl(%rip), %xmm0
            movss %xmm0, croll(%rip)
            jmp inputend
        input13:

        cmpb reset(%rip), %al
        jne input14
            call center
            jmp inputend
        input14:
        cmpb reload(%rip), %al
        jne input15
            call free_assets
            call make_assets
        input15:

        cmpb fov_up(%rip), %al
        jne input16
            movss fov(%rip), %xmm0
            movss maxfov(%rip), %xmm1
            ucomiss %xmm0, %xmm1
            jle inputend

            movss fov(%rip), %xmm0
            addss dfov(%rip), %xmm0
            movss %xmm0, fov(%rip)
            jmp inputend
        input16:
        cmpb fov_down(%rip), %al
        jne input17
            movss fov(%rip), %xmm0
            movss minfov(%rip), %xmm1
            ucomiss %xmm0, %xmm1
            jle inputend

            movss fov(%rip), %xmm0
            subss dfov(%rip), %xmm0
            movss %xmm0, fov(%rip)
            jmp inputend
        input17:

    inputend:
    jmp input0

    input1:
    movb $1, exitv(%rip)
    movb $1, framelock(%rip)

    addq $32, %rsp
    popq %rbp
    ret
