[bits 64]


global kernel_freeze
kernel_freeze:
    hlt
    jmp kernel_freeze
    ret
