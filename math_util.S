.section .data

.global mathin
mathin:

.global mathout1
mathout1:   .space  16
.global mathout2
mathout2:   .space  16

.section .text

.global ss2sd
ss2sd:
    movq %rcx, %xmm0
    cvtss2sd %xmm0, %xmm0
    movq %xmm0, %rcx
    ret

.global sd2ss
sd2ss:
    movq %rcx, %xmm0
    cvtsd2ss %xmm0, %xmm0
    movq %xmm0, %rcx
    ret

.global sin
sin:
    flds mathin(%rip)
    fsin
    fstps mathout1(%rip)
    ret

.global cos
cos:
    flds mathin(%rip)
    fcos
    fstps mathout1(%rip)
    ret

.global wsincos
wsincos:
    flds mathin(%rip)
    fsincos
    fstps mathout1(%rip)
    fstps mathout2(%rip)
    ret
