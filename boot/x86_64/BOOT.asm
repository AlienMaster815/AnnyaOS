bits 32
;=====================================================================
;                 Multiboot Header
section .multiboot_header
global MBOOTHEADER
align 4
MBOOTHEADER:
    dd 0xE85250D6             ; Magic number
    dd 0                      ; ARCHITECTURE (0 for i386/x86_64)
    dd MBOOTEND - MBOOTHEADER ; Header Length
    dd 0x100000000 - (0xE85250D6 + 0x00 + (MBOOTEND - MBOOTHEADER)) 
    dw 0
    dw 0
    dd 8
MBOOTEND:
;======================================================================
section .data
multiboot_info_ptr dd 0

%define STACK_SIZE 16 * 1024

section .text

global start

MBoot dd 0
FOO dd 0

extern SetUpPages
extern Lou_kernel_start
extern enable_paging

global gdt64.pointer
global gdt64.code_segment
global gdt64.data_segment

start:
    mov [multiboot_info_ptr], ebx  ; Store Multiboot info pointer

    mov esp, stack_top             ; Set up the stack

    call check_cpuid               ; Check for CPUID support
    call check_long_mode           ; Check if the CPU supports long mode

    call SetUpPages                ; Set up paging
    call enable_paging             ; Enable paging (transition to long mode)

    lgdt [gdt64.pointer]           ; Load the GDT
    jmp gdt64.code_segment:long_mode_start ; Jump to 64-bit mode

check_cpuid:
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
    je .no_cpuid
    ret
.no_cpuid:
    mov al, "C"
    jmp error

check_long_mode:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode
    ret
.no_long_mode:
    mov al, "L"
    jmp error

error:
    ; Print "ERR: X" where X is the error code
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt

section .bss
align 4096
stack_bottom:
    resb STACK_SIZE         ; Allocate 16KB for the stack
stack_top:                  ; This is the top of the stack (the end of the reserved space)

section .data
align 16
global tss64
tss64:
    dw 0                  ; Reserved 4
    dq stack_top          ; RSP0 (kernel stack pointer) - Kernel mode stack 8 + 4 = 12
    dq 0                  ; RSP1 - Optional for other privilege levels 8 + 12 = 20
    dq 0                  ; RSP2 - Optional for other privilege levels 8 + 20 = 28
    dq 0                  ; Reserved 8 + 28 = 36
    dq 0                  ; IST1 - Interrupt Stack Table 1 (optional) 8 + 36 = 44
    dq 0                  ; IST2 - Optional 8 + 44 = 52
    dq 0                  ; IST3 - Optional 8 + 52 = 60
    dq 0                  ; IST4 - Optional 8 + 60 = 68
    dq 0                  ; IST5 - Optional 8 + 68 = 76
    dq 0                  ; IST6 - Optional 8 + 76 = 84
    dq 0                  ; IST7 - Optional 8 + 84 = 92
    dq 0                  ; Reserved        8 + 92 = 100
    dw 0                  ; RESERVED        104  
tss64_end:


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
section .text

long_mode_start:
    mov ax, gdt64.data_segment ; Load the data segment in 64-bit mode
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    ;mov rax, cr4       ; Read CR4
    ;or rax, (1 << 18)  ; Set OSXSAVE bit (bit 18)
    ;mov cr4, rax       ; Write back to CR4

    ; XSAVE is supported, now you can use XGETBV safely
    ;mov ecx, 0
    ;xgetbv
    ;or eax, 0b111
    ;mov ecx, 0
    ;xsetbv

    mov rcx, [multiboot_info_ptr] ; Load multiboot info
    mov rdx, [FOO]                ; Load FOO (if needed)
    call Lou_kernel_start         ; Start the kernel
    jmp $


global LouKeGetStackSize
global LouKeGetBspStackBottom
global FlushTss
global GetGdtBase

GetGdtBase:
    mov rax, gdt64
    ret

LouKeGetStackSize:
    mov rax, STACK_SIZE 
    ret

LouKeGetBspStackBottom:
    mov rax, stack_bottom
    ret

global LoadTaskRegister

global InstallGDT

InstallGDT:
    lgdt [rcx]
    mov ax, 0x28
    ltr ax
    push 0x08
    lea rax, [rel .reload_CS]
    push rax
    retfq

.reload_CS:
    mov   ax, 0x10
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax
    mov   ss, ax
    ret
    
no_xsave:
    hlt    