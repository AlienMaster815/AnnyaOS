section .text

global NtGetPeb
global NtGetTeb
global LouGetPeb
global LouGetTeb

NtGetPeb:
LouGetPeb:
    mov rax, qword[gs:0x60]
    ret

LouGetTeb:
NtGetTeb:
    mov rax, qword[gs:0x30]
    ret