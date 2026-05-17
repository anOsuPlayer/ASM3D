.section .data

.global ZBUFFER
ZBUFFER:            .quad 0

.global CBUFFER
CBUFFER:            .quad 0

.global BUFSIZE
BUFSIZE:            .quad 0
.global PIXELS
PIXELS:             .long 0

.global ENGINE_BG
ENGINE_BG:          .long 0x00000000

.section .text
.global _256_clear_bufs
_256_clear_bufs:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %ymm0
    vpbroadcastd ENGINE_BG(%rip), %ymm1
    
    movq ZBUFFER(%rip), %rax
    movq CBUFFER(%rip), %rdx

    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _256_clear_bufs0:
        vmovaps %ymm0, (%rax)
        vmovdqa %ymm1, (%rdx)
    addq $32, %rax
    addq $32, %rdx
    cmpq %rcx, %rax
    jb _256_clear_bufs0
    ret

.global _512_clear_bufs
_512_clear_bufs:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %zmm1
    vpbroadcastd ENGINE_BG(%rip), %zmm2
    
    movq ZBUFFER(%rip), %rax
    movq CBUFFER(%rip), %rdx

    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _512_clear_bufs0:
        vmovdqa64 %zmm1, (%rax)
        vmovdqa64 %zmm2, (%rdx)
    addq $64, %rax
    addq $64, %rdx
    cmpq %rcx, %rax
    jb _512_clear_bufs0
    ret

.global _256_clear_bufs_nth
_256_clear_bufs_nth:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %ymm0
    vpbroadcastd ENGINE_BG(%rip), %ymm1
    
    movq ZBUFFER(%rip), %rax
    movq CBUFFER(%rip), %rdx

    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _256_clear_bufs_nth0:
        vmovntps %ymm0, (%rax)
        vmovntdq %ymm1, (%rdx)
    addq $32, %rax
    addq $32, %rdx
    cmpq %rcx, %rax
    jb _256_clear_bufs_nth0
    ret

.global _512_clear_bufs_nth
_512_clear_bufs_nth:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %zmm1
    vpbroadcastd ENGINE_BG(%rip), %zmm2
    
    movq ZBUFFER(%rip), %rax
    movq CBUFFER(%rip), %rdx

    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _512_clear_bufs_nth0:
        vmovntps %zmm1, (%rax)
        vmovntdq %zmm2, (%rdx)
    addq $64, %rax
    addq $64, %rdx
    cmpq %rcx, %rax
    jb _512_clear_bufs_nth0
    ret

.global _256_clear_bufs_dual
_256_clear_bufs_dual:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %ymm0
    vpbroadcastd ENGINE_BG(%rip), %ymm1
    
    movq ZBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _256_clear_bufs_dual0:
        vmovaps %ymm0, (%rax)
    addq $32, %rax
    cmpq %rcx, %rax
    jb _256_clear_bufs_dual0

    movq CBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _256_clear_bufs_dual1:
        vmovdqa %ymm1, (%rax)
    addq $32, %rax
    cmpq %rcx, %rax
    jb _256_clear_bufs_dual1
    ret

.global _512_clear_bufs_dual
_512_clear_bufs_dual:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %zmm1
    vpbroadcastd ENGINE_BG(%rip), %zmm2
    
    movq ZBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _512_clear_bufs_dual0:
        vmovaps %zmm1, (%rax)
    addq $64, %rax
    cmpq %rcx, %rax
    jb _512_clear_bufs_dual0

    movq CBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _512_clear_bufs_dual1:
        vmovdqa32 %zmm2, (%rax)
    addq $64, %rax
    cmpq %rcx, %rax
    jb _512_clear_bufs_dual1
    ret

.global _256_clear_bufs_nthd
_256_clear_bufs_nthd:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %ymm0
    vpbroadcastd ENGINE_BG(%rip), %ymm1
    
    movq ZBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _256_clear_bufs_nthd0:
        vmovntps %ymm0, (%rax)
    addq $32, %rax
    cmpq %rcx, %rax
    jb _256_clear_bufs_nthd0

    movq CBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _256_clear_bufs_nthd1:
        vmovntdq %ymm1, (%rax)
    addq $32, %rax
    cmpq %rcx, %rax
    jb _256_clear_bufs_nthd1
    ret

.global _512_clear_bufs_nthd
_512_clear_bufs_nthd:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %zmm1
    vpbroadcastd ENGINE_BG(%rip), %zmm2
    
    movq ZBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _512_clear_bufs_nthd0:
        vmovntps %zmm1, (%rax)
    addq $64, %rax
    cmpq %rcx, %rax
    jb _512_clear_bufs_nthd0

    movq CBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    _512_clear_bufs_nthd1:
        vmovntdq %zmm2, (%rax)
    addq $64, %rax
    cmpq %rcx, %rax
    jb _512_clear_bufs_nthd1
    ret

.global put
put:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    cvtss2si Width(%rip), %eax
    cvtss2si %xmm1, %ecx
    imull %ecx, %eax
    cvtss2si %xmm0, %ecx
    addl %ecx, %eax
    decl %eax

    cmpl $0, %eax
    jl put0
    cmpl PIXELS(%rip), %eax
    jg put0

    movq ZBUFFER(%rip), %rcx
    movss (%rcx, %rax, 4), %xmm5
    ucomiss %xmm3, %xmm5
    jb put0
        cmpq $0, %r8
        je put1
            movq (%r8), %r8
            cmpq $0, %r8
            je put1
                vpxor %xmm0, %xmm0, %xmm0
                vpxor %xmm1, %xmm1, %xmm1
                movq %rax, %r14
                movq ENGINE_TIME(%rip), %r9
                xchgq %r8, %r9
                call *%r9
                movq %rax, %r8
                movq %r14, %rax

                jmp put2
        put1:
            movl $0x00ffffff, %r8d
        put2:

        movq ZBUFFER(%rip), %rcx
        movq CBUFFER(%rip), %rdx
        movss %xmm3, (%rcx, %rax, 4)
        movl %r8d, (%rdx, %rax, 4)
    put0:

    addq $64, %rsp
    popq %rbp
    ret

.global _256_put_line
_256_put_line:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    vmovups (%rdx), %xmm0
    vsubps (%rcx), %xmm0, %xmm0
    vmovups %xmm0, %xmm1
    
    movl $0x7fffffff, %eax
    movd %eax, %xmm0
    vbroadcastss %xmm0, %xmm2
    vandps %xmm1, %xmm2, %xmm3
    vpextrd $1, %xmm3, %eax
    movd %eax, %xmm2
    vmaxss %xmm3, %xmm2, %xmm3
    vbroadcastss %xmm3, %xmm3

    cvtss2si %xmm3, %r15d
    cmpl $0, %r15d
    jnz _256_put_line0
        vmovups (%rcx), %xmm0
        vpextrd $1, %xmm0, %eax
        vmovd %eax, %xmm1
        vpextrd $2, %xmm0, %eax
        vmovd %eax, %xmm3
        movq $0, %r8
        call put

        addq $64, %rsp
        popq %rbp
        ret
    _256_put_line0:

    movl $1, %eax
    cvtsi2ss %eax, %xmm2

    vmovups (%rcx), %xmm5
    vpxor %xmm4, %xmm4, %xmm4

    vdivps %xmm3, %xmm1, %xmm7
    vdivps %xmm3, %xmm2, %xmm2

    cvtss2si %xmm3, %ecx
    cvtss2si Width(%rip), %esi
    
    cmpq $0, %r8
    je _256_put_line1
        movq (%r8), %r8
    _256_put_line1:
    movq %r8, -8(%rbp)
    cmpq $0, %r8
    je _256_put_line_loop_fixed

        _256_put_line_loop:
            movl %esi, %eax
            vmovups %xmm5, %xmm0
            vcvtps2dq %xmm0, %xmm0
            vpextrd $1, %xmm0, %edx
            mull %edx
            movd %xmm0, %edx
            addl %edx, %eax
            decl %eax

            cmpl $0, %eax
            jl l256put0
            cmpl PIXELS(%rip), %eax
            jg l256put0

            movq ZBUFFER(%rip), %rdx
            movss (%rdx, %rax, 4), %xmm6
            vpextrd $2, %xmm5, %r15d
            movd %r15d, %xmm0
            ucomiss %xmm0, %xmm6
            jb l256put0
                movss %xmm0, -28(%rbp)
                movq -8(%rbp), %r8

                movss %xmm4, %xmm0
                vpxor %xmm1, %xmm1, %xmm1
                movq %rax, -16(%rbp)
                movq %rcx, -24(%rbp)
                movq ENGINE_TIME(%rip), %r9
                xchgq %r8, %r9
                call *%r9
                movq %rax, %r15
                movq -16(%rbp), %rax
                movq -24(%rbp), %rcx

                movq ZBUFFER(%rip), %rdx
                movss -28(%rbp), %xmm0
                movss %xmm0, (%rdx, %rax, 4)
                movq CBUFFER(%rip), %rdx
                movl %r15d, (%rdx, %rax, 4)
            l256put0:

            vaddps %xmm4, %xmm2, %xmm4
            vaddps %xmm5, %xmm7, %xmm5
        decl %ecx
        cmpl $0, %ecx
        jnz _256_put_line_loop

    jmp _256_put_line_end

        _256_put_line_loop_fixed:
            movl %esi, %eax
            vmovups %xmm5, %xmm0
            vcvtps2dq %xmm0, %xmm0
            vpextrd $1, %xmm0, %edx
            mull %edx
            movd %xmm0, %edx
            addl %edx, %eax
            decl %eax

            cmpl $0, %eax
            jl l256put1
            cmpl PIXELS(%rip), %eax
            jg l256put1

            movq ZBUFFER(%rip), %rdx
            movss (%rdx, %rax, 4), %xmm6
            vpextrd $2, %xmm5, %r15d
            movd %r15d, %xmm0
            ucomiss %xmm0, %xmm6
            jb l256put1
                movq ZBUFFER(%rip), %rdx
                movss -28(%rbp), %xmm0
                movss %xmm0, (%rdx, %rax, 4)
                movq CBUFFER(%rip), %rdx
                movl $0x00ffffff, (%rdx, %rax, 4)
            l256put1:

            vaddps %xmm4, %xmm2, %xmm4
            vaddps %xmm5, %xmm7, %xmm5
        decl %ecx
        cmpl $0, %ecx
        jnz _256_put_line_loop_fixed

    _256_put_line_end:

    addq $64, %rsp
    popq %rbp
    ret

.global _512_put_line
_512_put_line:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    vmovups (%rdx), %xmm0
    vsubps (%rcx), %xmm0, %xmm0
    vmovups %xmm0, %xmm1
    
    movl $0x7fffffff, %eax
    movd %eax, %xmm0
    vbroadcastss %xmm0, %xmm2
    vandps %xmm1, %xmm2, %xmm3
    vpextrd $1, %xmm3, %eax
    movd %eax, %xmm2
    vmaxss %xmm3, %xmm2, %xmm3
    vbroadcastss %xmm3, %xmm3

    cvtss2si %xmm3, %r15d
    cmpl $0, %r15d
    jnz _512_put_line0
        vmovups (%rcx), %xmm0
        vpextrd $1, %xmm0, %eax
        vmovd %eax, %xmm1
        vpextrd $2, %xmm0, %eax
        vmovd %eax, %xmm3
        movq $0, %r8
        call put

        addq $64, %rsp
        popq %rbp
        ret
    _512_put_line0:

    movl $1, %eax
    cvtsi2ss %eax, %xmm2

    vmovups (%rcx), %xmm5
    vpxor %xmm4, %xmm4, %xmm4

    vdivps %xmm3, %xmm1, %xmm7
    vdivps %xmm3, %xmm2, %xmm2

    cvtss2si %xmm3, %ecx
    cvtss2si Width(%rip), %esi
    
    cmpq $0, %r8
    je _512_put_line1
        movq (%r8), %r8
    _512_put_line1:
    movq %r8, -8(%rbp)
    cmpq $0, %r8
    je _512_put_line_loop_fixed

        _512_put_line_loop:
            movl %esi, %eax
            vmovups %xmm5, %xmm0
            vcvtps2dq %xmm0, %xmm0
            vpextrd $1, %xmm0, %edx
            mull %edx
            movd %xmm0, %edx
            addl %edx, %eax
            decl %eax

            cmpl $0, %eax
            jl l512put0
            cmpl PIXELS(%rip), %eax
            jg l512put0

            movq ZBUFFER(%rip), %rdx
            movss (%rdx, %rax, 4), %xmm6
            vpextrd $2, %xmm5, %r15d
            movd %r15d, %xmm0
            ucomiss %xmm0, %xmm6
            jb l512put0
                movss %xmm0, -28(%rbp)
                movq -8(%rbp), %r8

                movss %xmm4, %xmm0
                vpxor %xmm1, %xmm1, %xmm1
                movq %rax, -16(%rbp)
                movq %rcx, -24(%rbp)
                movq ENGINE_TIME(%rip), %r9
                xchgq %r8, %r9
                call *%r9
                movq %rax, %r15
                movq -16(%rbp), %rax
                movq -24(%rbp), %rcx

                movq ZBUFFER(%rip), %rdx
                movss -28(%rbp), %xmm0
                movss %xmm0, (%rdx, %rax, 4)
                movq CBUFFER(%rip), %rdx
                movl %r15d, (%rdx, %rax, 4)
            l512put0:

            vaddps %xmm4, %xmm2, %xmm4
            vaddps %xmm5, %xmm7, %xmm5
        decl %ecx
        cmpl $0, %ecx
        jnz _512_put_line_loop

    jmp _512_put_line_end

        _512_put_line_loop_fixed:
            movl %esi, %eax
            vmovups %xmm5, %xmm0
            vcvtps2dq %xmm0, %xmm0
            vpextrd $1, %xmm0, %edx
            mull %edx
            movd %xmm0, %edx
            addl %edx, %eax
            decl %eax

            cmpl $0, %eax
            jl l512put1
            cmpl PIXELS(%rip), %eax
            jg l512put1

            movq ZBUFFER(%rip), %rdx
            movss (%rdx, %rax, 4), %xmm6
            vpextrd $2, %xmm5, %r15d
            movd %r15d, %xmm0
            ucomiss %xmm0, %xmm6
            jb l512put1
                movq ZBUFFER(%rip), %rdx
                movss -28(%rbp), %xmm0
                movss %xmm0, (%rdx, %rax, 4)
                movq CBUFFER(%rip), %rdx
                movl $0x00ffffff, (%rdx, %rax, 4)
            l512put1:

            vaddps %xmm4, %xmm2, %xmm4
            vaddps %xmm5, %xmm7, %xmm5
        decl %ecx
        cmpl $0, %ecx
        jnz _512_put_line_loop_fixed

    _512_put_line_end:

    addq $64, %rsp
    popq %rbp
    ret
    