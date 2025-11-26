.section .data

HANDLE:             .quad 0
HANDLE_NAME:        .string "assets.txt"
HANDLE_MODE:        .string "r"

fscanf_read1:       .string "%d"
fscanf_read2:       .string "%f %f %f"

.global POINTS
POINTS:             .quad 0
.global pointcount
pointcount:         .long 0
.global psize
psize:              .quad 8

.global LINES
LINES:              .quad 0
.global linescount
linescount:         .long 0
.global lsize
lsize:              .quad 16

.global SURFACES
SURFACES:           .quad 0
.global surfacescount
surfacescount:      .long 0
.global ssize
ssize:              .quad 24

.section .text

.global make_assets
make_assets:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp

    leaq HANDLE_NAME(%rip), %rcx
    leaq HANDLE_MODE(%rip), %rdx
    call fopen
    movq %rax, HANDLE(%rip)

    movq HANDLE(%rip), %rcx
    leaq fscanf_read1(%rip), %rdx
    leaq -8(%rbp), %r8
    movq $0, %rax
    call fscanf

    make_assets0:

        movq HANDLE(%rip), %rcx
        leaq fscanf_read1(%rip), %rdx
        leaq -16(%rbp), %r8
        movq $0, %rax
        call fscanf

        cmpl $0, -16(%rbp)
        jne make_assets1

            call make_point
            movq %rax, -24(%rbp)

            movq HANDLE(%rip), %rcx
            leaq fscanf_read2(%rip), %rdx
            leaq -32(%rbp), %r8
            leaq -40(%rbp), %r9
            leaq -48(%rbp), %rax
            movq %rax, 32(%rsp)
            movq $0, %rax
            call fscanf

            movq -24(%rbp), %rax

            movl -32(%rbp), %ecx
            movl %ecx, (%rax)
            movl -40(%rbp), %ecx
            movl %ecx, 4(%rax)
            movl -48(%rbp), %ecx
            movl %ecx, 8(%rax)

            jmp make_assets3

        make_assets1:
        cmpl $1, -16(%rbp)
        jne make_assets2


            jmp make_assets3

        make_assets2:
        cmpl $2, -16(%rbp)
        jne make_assets3


        make_assets3:

    decl -8(%rbp)
    cmpl $0, -8(%rbp)
    jne make_assets0

    movq HANDLE(%rip), %rcx
    call fclose

    addq $96, %rsp
    popq %rbp
    ret

.global make_point
make_point:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    incl pointcount(%rip)
    movl pointcount(%rip), %eax
    movl psize(%rip), %ebx
    xorq %rdx, %rdx
    imull %ebx

    movl %eax, -4(%rbp)

    cmpl $1, pointcount(%rip)
    jne make_point0

        movl $400, %ecx
        call malloc
        movq %rax, POINTS(%rip)

    make_point0:

    movq POINTS(%rip), %rax
    movzx -4(%rbp), %rcx
    addq %rcx, %rax
    subq psize(%rip), %rax
    movq %rax, -16(%rbp)

    movq $1, %rax
    cvtsi2ss %rax, %xmm6

    call make_vec
    movss %xmm6, 12(%rax)
    movq %rax, %rcx
    
    movq -16(%rbp), %rax
    movq %rcx, (%rax)

    movq %rcx, %rax

    addq $48, %rsp
    popq %rbp
    ret

.global make_line
make_line:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    incl linescount(%rip)
    movl linescount(%rip), %eax
    movl lsize(%rip), %ebx
    xorq %rdx, %rdx
    imull %ebx

    movl %eax, -4(%rbp)

    cmpl $1, linescount(%rip)
    jne make_line0

        movl $800, %ecx
        call malloc
        movq %rax, LINES(%rip)

    make_line0:

    movq LINES(%rip), %rax
    movzx -4(%rbp), %rcx
    addq %rcx, %rax
    subq lsize(%rip), %rax
    movq %rax, -12(%rbp)

    movq $1, %rax
    cvtsi2ss %rax, %xmm6

    call make_vec
    movss %xmm6, 12(%rax)
    movq %rax, %rcx
    call make_vec
    movss %xmm6, 12(%rax)
    movq %rax, %rdx

    movq -12(%rbp), %rax
    movq %rcx, (%rax)
    movq %rdx, 8(%rax)
    
    addq $32, %rsp
    popq %rbp
    ret

.global make_surface
make_surface:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    incl surfacescount(%rip)
    movl surfacescount(%rip), %eax
    movl ssize(%rip), %ebx
    xorq %rdx, %rdx
    imull %ebx

    movl %eax, -4(%rbp)

    cmpl $1, surfacescount(%rip)
    jne make_surface0

        movl $1200, %ecx
        call malloc
        movq %rax, SURFACES(%rip)

    make_surface0:

    movq SURFACES(%rip), %rax
    movzx -4(%rbp), %rcx
    addq %rcx, %rax
    subq ssize(%rip), %rax
    movq %rax, -12(%rbp)
    
    movq $1, %rax
    cvtsi2ss %rax, %xmm6

    call make_vec
    movss %xmm6, 12(%rax)
    movq %rax, %rcx
    call make_vec
    movss %xmm6, 12(%rax)
    movq %rax, %rdx
    call make_vec
    movss %xmm6, 12(%rax)
    movq %rax, %r8

    movq -12(%rbp), %rax
    movq %rcx, (%rax)
    movq %rdx, 8(%rax)
    movq %rdx, 16(%r8)
    
    addq $32, %rsp
    popq %rbp
    ret

.global free_assets
free_assets:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    cmpq $0, POINTS(%rip)
    je free_assets0

        movq POINTS(%rip), %r15
        free_points0:

            movq (%r15), %rcx
            call free_vec
            addq psize(%rip), %r15

        decl pointcount(%rip)
        cmpl $0, pointcount(%rip)
        jne free_points0

        movq POINTS(%rip), %rcx
        call free
    free_assets0:
    
    cmpq $0, LINES(%rip)
    je free_assets1

        movq LINES(%rip), %r15
        free_lines0:

            movq (%r15), %rcx
            call free_vec
            movq 8(%r15), %rcx
            call free_vec
            addq lsize(%rip), %r15

        decl linescount(%rip)
        cmpl $0, linescount(%rip)
        jne free_lines0

        movq LINES(%rip), %rcx
        call free
    free_assets1:

    cmpq $0, SURFACES(%rip)
    je free_assets2

        movq SURFACES(%rip), %r15
        free_surfaces0:

            movq (%r15), %rcx
            call free_vec
            movq 8(%r15), %rcx
            call free_vec
            movq 16(%r15), %rcx
            call free_vec
            addq ssize(%rip), %r15

        decl surfacescount(%rip)
        cmpl $0, surfacescount(%rip)
        jne free_surfaces0

        movq SURFACES(%rip), %rcx
        call free
    free_assets2:

    addq $32, %rsp
    popq %rbp
    ret
