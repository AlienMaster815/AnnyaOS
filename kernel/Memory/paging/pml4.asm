
bits 64

default rel

global SetCr3

SetCr3:
    mov cr3, rcx
    ret