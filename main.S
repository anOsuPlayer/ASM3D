.section .data


.section .text

.global main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    call get_screen_size

    call start_input
    call set_camera
    call make_assets

    call render

    call free_assets
    call free_camera
    call join_input

    addq $48, %rsp
    popq %rbp
    ret
