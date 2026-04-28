.section .data

.align 32
    plane_mask: .long 0, 3, 1, 4, 2, 5, 6, 7

.section .text
.global compute_point
compute_point:    
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movq %rdx, -8(%rbp)
    movq %rcx, %rdx
    movq VIEW(%rip), %rcx
    leaq -24(%rbp), %r8
    call mulmv

    movl -16(%rbp), %ecx
    movl %ecx, -44(%rbp)

    movq PERSPECTIVE(%rip), %rcx
    leaq -24(%rbp), %rdx
    leaq -40(%rbp), %r8
    call mulmv

    movss -28(%rbp), %xmm0
    ucomiss Near(%rip), %xmm0
    jbe compute_point_Cquit

    movss -28(%rbp), %xmm0
    ucomiss Far(%rip), %xmm0
    jae compute_point_Cquit

    leaq -40(%rbp), %rcx
    leaq -40(%rbp), %rdx
    call vndc

    fld1
    fadds -40(%rbp)
    fstps -40(%rbp)

    fld1
    fsubs -36(%rbp)
    fstps -36(%rbp)

    movq $2, %rax
    cvtsi2ss %rax, %xmm2

    movss Width(%rip), %xmm0
    divss %xmm2, %xmm0
    mulss -40(%rbp), %xmm0
    movss %xmm0, -40(%rbp)

    movss Height(%rip), %xmm0
    divss %xmm2, %xmm0
    mulss -36(%rbp), %xmm0
    movss %xmm0, -36(%rbp)

    vpxor %xmm1, %xmm1, %xmm1

    movss -40(%rbp), %xmm0
    ucomiss %xmm1, %xmm0
    jb compute_point_Cquit
    movss -40(%rbp), %xmm0
    ucomiss Width(%rip), %xmm0
    ja compute_point_Cquit

    movss -36(%rbp), %xmm0
    ucomiss %xmm1, %xmm0
    jb compute_point_Cquit
    movss -36(%rbp), %xmm0
    ucomiss Height(%rip), %xmm0
    ja compute_point_Cquit

    jmp compute_point_quit
    compute_point_Cquit:
    
    movq $0, %rax
    jmp compute_point_end

    compute_point_quit:
    movq -8(%rbp), %rax
    movl -44(%rbp), %ecx
    movl %ecx, -32(%rbp)
    vmovups -40(%rbp), %xmm0
    vmovups %xmm0, (%rax)
    movq $1, %rax

    compute_point_end:

    addq $64, %rsp
    popq %rbp
    ret

.global compute_line
compute_line:
    pushq %rbp
    movq %rsp, %rbp
    subq $256, %rsp

    movq %r8, -8(%rbp)
    movq %r9, -16(%rbp)
    movq %rdx, -24(%rbp)

    movq %rcx, %rdx
    movq VIEW(%rip), %rcx
    leaq -48(%rbp), %r8
    call mulmv
    movl -40(%rbp), %ecx
    movl %ecx, -200(%rbp)

    leaq -48(%rbp), %rdx
    movq PERSPECTIVE(%rip), %rcx
    leaq -64(%rbp), %r8
    call mulmv
    vmovups -64(%rbp), %xmm0
    vmovups %xmm0, -48(%rbp)

    movq -24(%rbp), %rdx
    movq VIEW(%rip), %rcx
    leaq -64(%rbp), %r8
    call mulmv
    movl -56(%rbp), %ecx
    movl %ecx, -204(%rbp)

    leaq -64(%rbp), %rdx
    movq PERSPECTIVE(%rip), %rcx
    leaq -80(%rbp), %r8
    call mulmv
    vmovups -80(%rbp), %xmm0
    vmovups %xmm0, -64(%rbp)

    movq $0, -168(%rbp)
    vpxor %xmm15, %xmm15, %xmm15
    vmovdqa plane_mask(%rip), %ymm14

    compute_line_loop:
        vbroadcastss -36(%rbp), %xmm0
        vaddps -48(%rbp), %xmm0, %xmm1
        vsubps -48(%rbp), %xmm0, %xmm2

        vmovups %xmm1, -128(%rbp)
        vmovups %xmm2, -112(%rbp)

        vmovups -128(%rbp), %ymm0
        vpermps %ymm0, %ymm14, %ymm0
        vmovups %ymm0, -128(%rbp)

        vbroadcastss -52(%rbp), %xmm0
        vaddps -64(%rbp), %xmm0, %xmm1
        vsubps -64(%rbp), %xmm0, %xmm2

        vmovups %xmm1, -160(%rbp)
        vmovups %xmm2, -144(%rbp)

        vmovups -160(%rbp), %ymm0
        vpermps %ymm0, %ymm14, %ymm0
        vmovups %ymm0, -160(%rbp)

        leaq -128(%rbp), %rdx
        addq -168(%rbp), %rdx
        movss (%rdx), %xmm0

        leaq -160(%rbp), %rcx
        addq -168(%rbp), %rcx
        movss (%rcx), %xmm1

        ucomiss %xmm15, %xmm1
        jae compute_line_loop0

            ucomiss %xmm15, %xmm0
            jb compute_line_Cquit

        jmp compute_line_loop1

        compute_line_loop0:
        ucomiss %xmm15, %xmm0
        jae compute_line_loop_cont
        
        jmp compute_line_loop2

        compute_line_loop1:
            movss %xmm0, %xmm2
            subss %xmm1, %xmm0
            divss %xmm0, %xmm2
            vbroadcastss %xmm2, %xmm2

            vmovups -64(%rbp), %xmm0
            vsubps -48(%rbp), %xmm0, %xmm0
            vmulps %xmm0, %xmm2, %xmm0
            
            vmovups -48(%rbp), %xmm1
            vaddps %xmm1, %xmm0, %xmm0
            vmovups %xmm0, -64(%rbp)

            jmp compute_line_loop_cont
        compute_line_loop2:
            movss %xmm0, %xmm2
            subss %xmm1, %xmm0
            divss %xmm0, %xmm2
            vbroadcastss %xmm2, %xmm2

            vmovups -64(%rbp), %xmm0
            vsubps -48(%rbp), %xmm0, %xmm0
            vmulps %xmm0, %xmm2, %xmm0
            
            vmovups -48(%rbp), %xmm1
            vaddps %xmm1, %xmm0, %xmm0
            vmovups %xmm0, -48(%rbp)

        compute_line_loop_cont:
    addq $4, -168(%rbp)
    cmpq $24, -168(%rbp)
    jb compute_line_loop

    leaq -48(%rbp), %rcx
    leaq -48(%rbp), %rdx
    call vndc
    leaq -64(%rbp), %rcx
    leaq -64(%rbp), %rdx
    call vndc

    fld1
    fadds -48(%rbp)
    fstps -48(%rbp)
    fld1
    fsubs -44(%rbp)
    fstps -44(%rbp)

    fld1
    fadds -64(%rbp)
    fstps -64(%rbp)
    fld1
    fsubs -60(%rbp)
    fstps -60(%rbp)

    movq $2, %rax
    cvtsi2ss %rax, %xmm2

    movss Width(%rip), %xmm0
    divss %xmm2, %xmm0
    mulss -48(%rbp), %xmm0
    movss %xmm0, -48(%rbp)
    movss Height(%rip), %xmm0
    divss %xmm2, %xmm0
    mulss -44(%rbp), %xmm0
    movss %xmm0, -44(%rbp)

    movss Width(%rip), %xmm0
    divss %xmm2, %xmm0
    mulss -64(%rbp), %xmm0
    movss %xmm0, -64(%rbp)
    movss Height(%rip), %xmm0
    divss %xmm2, %xmm0
    mulss -60(%rbp), %xmm0
    movss %xmm0, -60(%rbp)

    vpxor %xmm1, %xmm1, %xmm1

    jmp compute_line_quit
    compute_line_Cquit:
    
    movq $0, %rax
    jmp compute_line_end

    compute_line_quit:
    movq -16(%rbp), %rax
    movl -200(%rbp), %ecx
    movl %ecx, -40(%rbp)
    vmovups -48(%rbp), %xmm0
    vmovups %xmm0, (%rax)

    movq -8(%rbp), %rax
    movl -204(%rbp), %ecx
    movl %ecx, -52(%rbp)
    vmovups -64(%rbp), %xmm0
    vmovups %xmm0, (%rax)

    movq $1, %rax

    compute_line_end:

    addq $256, %rsp
    popq %rbp
    ret
