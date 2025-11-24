.section .data



.section .text

.global render_assets
render_assets:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call render_points

    addq $32, %rsp
    popq %rbp
    ret

.global project
project:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movq %rcx, -8(%rbp)
    movq %rdx, -16(%rbp)

    call make_vec
    movq %rax, -24(%rbp)

    movq VIEW(%rip), %rcx
    movq -8(%rbp), %rdx
    movq -16(%rbp), %r8
    call mult_matrix_vec

    // movq PERSPECTIVE(%rip), %rcx
    // movq -16(%rbp), %rdx
    // movq -24(%rbp), %r8
    // call mult_matrix_vec

    // movq -24(%rbp), %rcx
    // call vndc

    // vmovups -24(%rbp), %xmm0

    movq -24(%rbp), %rcx
    call free_vec

    movq -16(%rbp), %rax
    // vmovups %xmm0, (%rax)

    addq $48, %rsp
    popq %rbp
    ret

dbg:    .string "%lf %lf %lf\n"

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

            addq $8, %r15

        decl -4(%rbp)
        cmpl $0, -4(%rbp)
        jne render_points0

    render_points1:

    movq -16(%rbp), %rcx
    call free_vec

    addq $32, %rsp
    popq %rbp
    ret
