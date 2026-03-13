.section .data



.section .text
.global make_vec
make_vec:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq $16, %rcx
    call malloc

    vpxorq %xmm0, %xmm0, %xmm0
    vmovups %xmm0, (%rax)

    addq $32, %rsp
    popq %rbp
    ret

.global make_matrix
make_matrix:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq $64, %rcx
    call malloc

    vpxorq %zmm1, %zmm1, %zmm1
    vmovups %zmm1, (%rax)

    addq $32, %rsp
    popq %rbp
    ret

.global free_vec
free_vec:
.global free_matrix
free_matrix:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    call free

    addq $32, %rsp
    popq %rbp
    ret
