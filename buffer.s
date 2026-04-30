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
    movl $0xff800000, %eax
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
    movl $0xff800000, %eax
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
    movl $0xff800000, %eax
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
    movl $0xff800000, %eax
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
    movl $0xff800000, %eax
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
    movl $0xff800000, %eax
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
    movl $0xff800000, %eax
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
    movl $0xff800000, %eax
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
    cvtss2si Width(%rip), %eax
    cvtss2si %xmm1, %ecx
    mull %ecx
    cvtss2si %xmm0, %ecx
    addl %ecx, %eax

    cmpl $0, %eax
    jl put0
    cmpl PIXELS(%rip), %eax
    jg put0

    movq ZBUFFER(%rip), %rcx
    movss (%rcx, %rax, 4), %xmm2
    ucomiss %xmm3, %xmm2
    ja put0
        movq CBUFFER(%rip), %rdx
        movss %xmm3, (%rcx, %rax, 4)
        movl %r8d, (%rdx, %rax, 4)
    put0:
    ret
    