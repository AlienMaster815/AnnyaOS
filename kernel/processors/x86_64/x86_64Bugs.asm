[bits 64]

section .text

global X86_64DivisionBug
global X86_64MemoryReferenceBug64Read
global X86_64MemoryReferenceBug64Write

X86_64DivisionBug:
    mov rax, Rcx
    mov rbx, Rdx
    xor rdx, rdx
    div rbx             
    ret


X86_64MemoryReferenceBug64Read:
    mov rax, [rcx + rdx * 8]
    ret

X86_64MemoryReferenceBug64Write:
    mov [rcx + rdx * 8], r8
    ret