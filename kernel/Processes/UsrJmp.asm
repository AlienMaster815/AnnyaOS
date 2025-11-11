section .User

global UsrJmp
global LOOP

extern KernelUserArea
UsrJmp: 
    mov ax, (4 * 8) | 3
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov ax, 0x28 | 3
    mov gs, ax

    mov rax, rsp 
    push (4 * 8) | 3
    push rax
    pushfq
    push (3 * 8) | 3
    push rcx
    iretq


LOOP:
    jmp $

global EXECUTE_THREAD_JUMP

EXECUTE_THREAD_JUMP:
    mov ax, (4 * 8) | 3
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov ax, 0x28 | 3
    mov gs, ax

    mov rax, rsp 
    push (4 * 8) | 3
    push rax
    pushfq
    push (3 * 8) | 3
    push r9
    iretq

TestUserFunction:

    jmp $
