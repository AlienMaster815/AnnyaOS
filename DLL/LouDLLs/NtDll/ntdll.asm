section .text

global NtGetPeb
global NtGetTeb


NtGetPeb:
    mov rax, qword[gs:0x60]
    ret

NtGetTeb:
    mov rax, qword[gs:0x30]
    ret