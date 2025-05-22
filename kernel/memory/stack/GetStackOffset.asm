section .text

global GetStackBackset

GetStackBackset:
    mov rax, rsp
    sub rax, rcx
    ret
