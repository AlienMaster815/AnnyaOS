BITS 16
;Copyright GPL-2 Tyler Grenier (2024 - 2026)
;
;structure notes:
;PML4 for BSP contains some 64 bit coded tables
;and is often random and dosent map low bases
;therefore it is not safe for all processesors 
;to imidiately use this value until comfortably 
;in long mode and inside the actual kernel 
;thats why a startup table is given
;
;the kernel is required to be under 1 gigabyte
;and the kernel space from the base to the base
;plus ram limit mirrors physical space so we
;can safely assume that one PML2 for kernel space 
;is all thats required and that the kernel will 
;be in this 1 gigabyte block of ram
;
;all values are configured inside the kernel and
;are here for reading only to maintain stability
;
;kernel data (LKSEB) layout pointed by ecx:
;

; UINT64        Kernel Entry For APs            : ecx + 0x0000
; UINT64        Pml4 : BSP Table                : ecx + 0x0008 
; UINT64[3]     Gdt32                           : ecx + 0x0010
; UINT64[7]     Gdt64                           : ecx + 0x0028
; UINT16[3]     GDTP32                          : ecx + 0x0060
; UINT16        Boot Stack                      ; ecx + 0x0066
; UINT32        Reserved 2                      ; ecx + 0x0068
; UINT32        LKSEBEX                         : ecx + 0x006C
; UINT32        32 Bit Stack                    : ecx + 0x0070
; UINT32        Reserved 3                      ; ecx + 0x0074
; UINT16[5]     GDTP64                          : ecx + 0x0078
;
; kernel data layout (LKSEBEX) pointed by LKSEBEX in LKSEB:
; UINT64[512]   Pml4 : Startup Table            ; LKSEBEX + 0x0000
; UINT64[512]   Pml3 : Startup Table Low        ; LKSEBEX + 0x1000
; UINT64[512]   Pml2 : Startup Table Low        ; LKSEBEX + 0x2000
; UINT64[512]   Pml3 : Startup Table High       ; LKSEBEX + 0x3000
; UINT64[512]   Pml2 : Startup Table High       ; LKSEBEX + 0x4000

[org 0x8000]

TrampolineStart:
    mov bx, [0] 
    cli
    mov ax, [bx + 0x0066]
    mov cx, bx
    mov bx, ax

    mov bp, bx
    mov sp, bp

    mov bx, cx

    push bx

    lgdt[bx + 0x0060]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:ProtectedMode 
    jmp $

BITS 32
ProtectedMode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax	

    pop ecx
    and ecx, 0xFFFF

    mov eax, [ecx + 0x0070]
    mov ebp, eax
    mov esp, ebp

    mov eax, ecx 
    push eax
    
    mov eax, [ecx + 0x006C]
    mov cr3, eax

    mov eax, cr4
    or eax, (1 << 5) | (1 << 4)
    mov cr4, eax
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    pop ecx
    
    lgdt [ecx + 0x0078]
    
    push ecx

    jmp 0x08:LongModeStart 

BITS 64
LongModeStart:
    mov ax, 0x10
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    and rcx, 0xFFFFFFFF

    mov rax, [rcx + 0x0070]
    mov rbp, rax
    mov rsp, rbp
    
    jmp [rcx]