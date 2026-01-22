.section .text

.global start_thread
start_thread:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    #ifdef _WIN32

        movq %rdx, %r8
        movq $0, %rdx
        movq $0, %r9

    #else

        movq %rcx, %rdi
        movq $0, %rsi
        movq $0, %rcx

    #endif

    call pthread_create

    addq $32, %rsp
    popq %rbp
    ret

.global twait
twait:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    twait0:
        decq %rcx
        cmpq $0, %rcx
        jne twait0

    addq $32, %rsp
    popq %rbp
    ret

.global twait_ms
twait_ms:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq %rcx, %rax
    movq $1000, %rbx
    xorq %rdx, %rdx
    imulq %rbx

    call twait

    addq $32, %rsp
    popq %rbp
    ret

.global twait_flag
twait_flag:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    twait_flag0:
        cmpb %dl, (%rcx)
        je twait_flag1
        cmpb $1, exitv(%rip)
        je twait_flag1

    jmp twait_flag0
    twait_flag1:

    addq $32, %rsp
    popq %rbp
    ret

.global join_thread
join_thread:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    #ifdef _WIN32

        movq $0, %rdx

    #else 

        movq %rcx, %rdi
        movq $0, %rsi

    #endif

    call pthread_join

    addq $32, %rsp
    popq %rbp
    ret
