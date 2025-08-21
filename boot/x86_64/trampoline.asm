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

jmp $
