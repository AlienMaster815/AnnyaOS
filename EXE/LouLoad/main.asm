bits 32
;=====================================================================
;                 Multiboot Header
section .multiboot_header
global MBOOTHEADER
align 8
MBOOTHEADER:
    dd 0xE85250D6             ; Magic number
    dd 0                      ; ARCHITECTURE (0 for i386/x86_64)
    dd MBOOTEND - MBOOTHEADER ; Header Length
    dd 0x100000000 - (0xE85250D6 + 0x00 + (MBOOTEND - MBOOTHEADER))
    dw 5                      ; Tag type: Framebuffer
    dw 0                      
    dd 20                     
    dd 640                    ; Width
    dd 480                    ; Height
    dd 32                     ; Depth (bits per pixel)
    align 8
    dw 0                      ; Tag type: End
    dw 0                      ; Flags
    dd 8                      ; Size of this tag (always 8)
MBOOTEND:
;======================================================================

section .data

section .text

global LouLoaderSetup

MulitibootInfo dd 0

LouLoaderCheckCpuID:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    je .NoCpuID
    ret 
.NoCpuID:
    mov al, "C"
    jmp LouLoaderSetupError

LouLoaderCheckLongMode:
    mov eax, 0x80000001
    cpuid 
    test edx, 1 << 29
    jz .LouLoaderNoLongMode
    ret
.LouLoaderNoLongMode:
    mov al, "L"
    jmp LouLoaderSetupError

LouLoaderSetupLoaderPages:
    ;set l4
    mov eax, LoaderPageL3
    or eax, 0b111 ; user present writable
    mov [LoaderPageL4], eax
    ;set l3
    mov eax, LoaderPageL2
    or eax, 0b111 ; user present writable
    mov [LoaderPageL3], eax

    ;set l2
    mov ecx, 0
    .L2Loop:
    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011 ;Large kernel present writeable page
    mov [LoaderPageL2 + ecx * 8], eax
    inc ecx
    cmp ecx, 512
    jne .L2Loop
    ret

LouLoaderEnableLoaderPages:
    ;Set The Control Register 3 To The Address
    mov eax, LoaderPageL4
    mov cr3, eax
    
    ;enable the Page Attribute Extension In Control Register 4
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ;Enable Long Mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ;enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    ret


LouLoaderSetup:

    mov [MulitibootInfo], ebx
    mov ebp, LoaderStackTop
    mov esp, ebp
    
    call LouLoaderCheckCpuID
    call LouLoaderCheckLongMode

    call LouLoaderSetupLoaderPages
    call LouLoaderEnableLoaderPages

    lgdt [gdt64.pointer]
    
    jmp gdt64.code_segment:LouLoaderLongModeTrampoline

LouLoaderSetupError:
    ; Print "ERR: X" where X is the error code
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt
    jmp $

section .note.GNU-stack progbits ;dear gnu, fuck you
section .bss
align 4096
LoaderPageL4:
    resq 512
LoaderPageL3:
    resq 512
LoaderPageL2:
    resq 512
LoaderStackBottom:
    resb    16 * 1024
LoaderStackTop:
    resq    2 ;mingw is trying to access the 8 bytes above the stack

section .rodata
gdt64:
    dq 0                     ; Null segment
.code_segment: equ $ - gdt64  ; Offset for Code Segment
    dq 0x00AF9A000000FFFF     ; 64-bit Code Segment (CS)
.data_segment: equ $ - gdt64  ; Offset for Data Segment
    dq 0x00AF92000000FFFF     ; 64-bit Data Segment (DS)
.UserCode: equ $ - gdt64
    dq 0x00A09A000000FFFF     ; User Code Segment (64-bit, DPL = 3)
.UserData: equ $ - gdt64
    dq 0x00A092000000FFFF     ; User Data Segment (DPL = 3, writable)
.TssSegment: equ $ - gdt64  
    dq 0    ; null untill assigned later
    dq 0
.pointer:
    dw $ - gdt64 - 1          ; GDT length (size)
    dq gdt64                  ; GDT base address

bits 64

extern LouLoaderStart

section .text

LouLoaderLongModeTrampoline:

    mov ax, gdt64.data_segment
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    xor rcx, rcx
    xor rdx, rdx

    mov ecx, [MulitibootInfo]    
    mov rdx, rbp

    call LouLoaderStart
    
    jmp $