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
.global clear_bufs
clear_bufs:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %zmm2
    vpbroadcastd ENGINE_BG(%rip), %zmm1
    
    movq ZBUFFER(%rip), %rax
    movq CBUFFER(%rip), %rdx

    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    clear_bufs0:
        vmovaps %zmm2, (%rax)
        vmovdqa32 %zmm1, (%rdx)
    addq $64, %rax
    addq $64, %rdx
    cmpq %rcx, %rax
    jb clear_bufs0

    vzeroupper
    ret

.global clear_bufs_nth
clear_bufs_nth:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %ymm0
    vpbroadcastd ENGINE_BG(%rip), %ymm1
    
    movq ZBUFFER(%rip), %rax
    movq CBUFFER(%rip), %rdx

    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    clear_bufs_nth0:
        vmovntps %ymm0, (%rax)
        vmovntdq %ymm1, (%rdx)
    addq $32, %rax
    addq $32, %rdx
    cmpq %rcx, %rax
    jb clear_bufs_nth0

    vzeroupper
    ret

.global clear_bufs_dual
clear_bufs_dual:
    movl $0x7f800000, %eax
    vmovd %eax, %xmm0
    vbroadcastss %xmm0, %ymm0
    vpbroadcastd ENGINE_BG(%rip), %ymm1
    
    movq ZBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    clear_bufs_dual0:
        vmovaps %ymm0, (%rax)
    addq $32, %rax
    cmpq %rcx, %rax
    jb clear_bufs_dual0

    movq CBUFFER(%rip), %rax
    movq %rax, %rcx
    addq BUFSIZE(%rip), %rcx
    clear_bufs_dual1:
        vmovdqa %ymm1, (%rax)
    addq $32, %rax
    cmpq %rcx, %rax
    jb clear_bufs_dual1

    vzeroupper
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
    jl put0
        movq CBUFFER(%rip), %rdx
        movss %xmm3, (%rcx, %rax, 4)
        movl %r8d, (%rdx, %rax, 4)
    put0:
    ret
    