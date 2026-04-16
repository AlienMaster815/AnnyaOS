
bits 64
default rel

global GetPageValue
global clear_cr2

GetPageValue:
    ;rcx has the address
    ;rdx has the flags
    mov rax, rcx ; rax now is address
    or rax, rdx  ; bitwise by flags
    ret
    

clear_cr2:
    mov rax, 0
    mov cr2, rax
    ret