.section .data

depthbuf:       .string "@&%QWNM0gB$#DR8mHXKAUbOGpV4d9h6PkqwSE2]ayjxY5Zenol[utl13If}C{iF|)7JvTLs?z/*cr!+<>;=^,:'-."
buflen:         .long   89

.section .text

.global render_assets
render_assets:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call render_points
    call render_lines

    addq $32, %rsp
    popq %rbp
    ret

.global project
project:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movq %rcx, -8(%rbp)
    movq %rdx, -16(%rbp)

    call make_vec
    movq %rax, -24(%rbp)

    movq VIEW(%rip), %rcx
    movq -8(%rbp), %rdx
    movq -16(%rbp), %r8
    call mult_matrix_vec

    movq PERSPECTIVE(%rip), %rcx
    movq -16(%rbp), %rdx
    movq -24(%rbp), %r8
    call mult_matrix_vec

    vmovups (%r8), %xmm0
    vbroadcastss 12(%r8), %xmm1
    vdivps %xmm1, %xmm0, %xmm0

    movq -24(%rbp), %rcx
    call free_vec

    movq -16(%rbp), %rax
    vmovups %xmm0, (%rax)

    addq $64, %rsp
    popq %rbp
    ret

.global draw_point
draw_point:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movss (%rcx), %xmm0
    movss %xmm0, -4(%rbp)
    movq $1, %rax
    cvtsi2ss %rax, %xmm0
    movss -4(%rbp), %xmm1
    addss %xmm0, %xmm1
    movss %xmm1, -4(%rbp)

    subss 4(%rcx), %xmm0
    movss %xmm0, -8(%rbp)

    movq $2, %rax
    cvtsi2ss %rax, %xmm1

    movss -4(%rbp), %xmm0
    divss %xmm1, %xmm0
    movss %xmm0, -4(%rbp)
    movss -8(%rbp), %xmm0
    divss %xmm1, %xmm0
    movss %xmm0, -8(%rbp)

    movl screen_w(%rip), %ebx
    cvtsi2ss %ebx, %xmm0
    movss -4(%rbp), %xmm1
    mulss %xmm1, %xmm0
    cvttss2si %xmm0, %eax
    movl %eax, -4(%rbp)

    movl screen_h(%rip), %ebx
    cvtsi2ss %ebx, %xmm0
    movss -8(%rbp), %xmm1
    mulss %xmm1, %xmm0
    roundss $2, %xmm0, %xmm0
    cvttss2si %xmm0, %eax
    movl %eax, -8(%rbp)

    movl buflen(%rip), %ebx
    cvtsi2ss %ebx, %xmm0
    movss 8(%rcx), %xmm1
    mulss %xmm1, %xmm0
    cvttss2si %xmm0, %eax
    movl %eax, -12(%rbp)

    cmpl $0, %eax
    jl draw_point1
    cmpq buflen(%rip), %rax
    jg draw_point1

    leaq depthbuf(%rip), %r8
    movzxb (%r8, %rax, 1), %r8

    draw_point0:

    cmpl $0, -4(%rbp)
    jl draw_point1
    cmpl $0, -8(%rbp)
    jl draw_point1

    movl screen_w(%rip), %eax
    cmpl -4(%rbp), %eax
    jl draw_point1
    movl screen_h(%rip), %eax
    cmpl -8(%rbp), %eax
    jl draw_point1

    movl screen_w(%rip), %eax
    incl %eax
    movl -8(%rbp), %ebx
    xorq %rdx, %rdx
    mull %ebx

    addl -4(%rbp), %eax

    movq frame(%rip), %rcx
    addq %rax, %rcx
    movb %r8b, (%rcx)

    draw_point1:

    vmovdqu -16(%rbp), %xmm0

    addq $32, %rsp
    popq %rbp
    ret

.global draw_line
draw_line:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movq %rdx, -8(%rbp)
    call draw_point
    vmovdqu %xmm0, -24(%rbp)
    movq -8(%rbp), %rcx
    call draw_point
    vmovdqu %xmm0, -40(%rbp)

    addq $64, %rsp
    popq %rbp
    ret

.global render_points
render_points:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq POINTS(%rip), %r15
    
    movl pointcount(%rip), %eax
    movl %eax, -4(%rbp)

    call make_vec
    movq %rax, -16(%rbp)

    cmpl $0, -4(%rbp)
    je render_points1

        render_points0:

            movq (%r15), %rcx
            movq -16(%rbp), %rdx

            call project
            movq %rax, %rcx

            call draw_point

            addq psize(%rip), %r15

        decl -4(%rbp)
        cmpl $0, -4(%rbp)
        jne render_points0

    render_points1:

    movq -16(%rbp), %rcx
    call free_vec

    addq $32, %rsp
    popq %rbp
    ret

.global render_lines
render_lines:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq LINES(%rip), %r15
    
    movl linescount(%rip), %eax
    movl %eax, -4(%rbp)

    call make_vec
    movq %rax, -16(%rbp)

    cmpl $0, -4(%rbp)
    je render_lines1

        render_lines0:

            movq (%r15), %rcx
            movq -16(%rbp), %rdx

            call project
            movq %rax, %rcx

            movq 8(%r15), %rcx
            movq -16(%rbp), %rdx

            call project
            movq %rax, %rdx

            call draw_line

            addq lsize(%rip), %r15

        decl -4(%rbp)
        cmpl $0, -4(%rbp)
        jne render_lines0

    render_lines1:

    movq -16(%rbp), %rcx
    call free_vec

    addq $32, %rsp
    popq %rbp
    ret
