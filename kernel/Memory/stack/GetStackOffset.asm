section .text
default rel

global GetStackBackset

GetStackBackset:
    mov rax, rsp
    sub rax, rcx
    ret
