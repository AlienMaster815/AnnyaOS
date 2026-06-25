BITS 64
section .text

global MsvcAbiJump

MsvcAbiJump:
    mov rsp, rdx
    mov rbp, rsp
    mov rcx, rdi
    jmp rsi
