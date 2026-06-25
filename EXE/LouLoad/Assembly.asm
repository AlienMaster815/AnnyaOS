BITS 64

section .text

global InstallGDT
global SetCr3
global SetNewStack

InstallGDT:
    lgdt [rcx]
    push 0x08
    lea rax, [rel .reload_CS]
    push rax   
    retfq

.reload_CS:
    mov   ax, 0x10
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax
    mov   ss, ax
    ret


SetCr3:
    mov cr3, rcx
    ret

