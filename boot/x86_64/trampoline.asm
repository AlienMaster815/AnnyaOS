BITS 16
[org 0x8000]
cli
lgdt[Gdtr]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp 0x08:ProtectedMode 
jmp $

GdtStart:
GdtNullSegment:
dq 0x0000000000000000
GdtCodeSegment:        
dq 0x00CF9A000000FFFF
GdtDataSegment:
dq 0x00CF92000000FFFF
GdtEnd:

Gdtr:
dw GdtEnd - GdtStart - 1
dd GdtStart

BITS 32
ProtectedMode:
mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax	

mov ebp, [0x7000]
mov esp, ebp

call EnablePaging

lgdt [gdt64.pointer]
jmp gdt64.code_segment:long_mode_start

EnablePaging:
    mov eax, [0x7010]
    mov cr3, eax
    
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret

gdt64:
dq 0
.code_segment: equ $ - gdt64
dq 0x00AF9A000000FFFF
.data_segment: equ $ - gdt64
dq 0x00AF92000000FFFF
.UserCode: equ $ - gdt64
dq 0x00A09A000000FFFF
.UserData: equ $ - gdt64
dq 0x00A092000000FFFF
.TssSegment: equ $ - gdt64  
dq 0
dq 0
.pointer:
dw $ - gdt64 - 1          
dq gdt64         

BITS 64
section .text

long_mode_start:
    mov ax, gdt64.data_segment ; Load the data segment in 64-bit mode
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    jmp [0x7008]