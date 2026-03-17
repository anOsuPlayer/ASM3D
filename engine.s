.section .data



.section .text
.global compute
compute:    
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    

    addq $48, %rsp
    popq %rbp
    ret
