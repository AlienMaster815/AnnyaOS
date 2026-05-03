section .text

global NtGetPeb
global NtGetTeb
global LouGetPeb
global LouGetTeb
global LouRaiseException

NtGetPeb:
LouGetPeb:
    mov rax, qword[gs:0x60]
    ret

NtGetTeb:
LouGetTeb:
    mov rax, qword[gs:0x30]
    ret




LouRaiseException:

    ret