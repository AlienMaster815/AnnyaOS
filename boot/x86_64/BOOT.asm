bits 32
;=====================================================================
;                 Multiboot Header
bits 32
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


    
no_xsave:
    hlt    

bits 32
section .text

global SetUpPages
global enable_paging
global clear_cr2

extern page_table_l4
extern page_table_l3
extern page_table_l2

SetUpPages:
    mov eax, page_table_l3
    or eax, 0b111
    mov [page_table_l4], eax

    mov eax, page_table_l2
    or eax, 0b111
    mov [page_table_l3], eax

    mov ecx, 0
    .loop: 

        mov eax, 0x200000
        mul ecx
        or eax, 0b10000011
        mov [page_table_l2 + ecx * 8], eax
        inc ecx
        cmp ecx, 512
        jne .loop
    ret

enable_paging:
    ; pass page table location to cpu

    mov eax, page_table_l4
    mov cr3, eax

    ; enable PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret

bits 32

section .bss
align 4096
page_table_l4:
    resq  512      ; Allocate space for the L4 table (PML4), containing one entry
page_table_l3:
    resq 512   ; 1024 entries for the L3 table (PDPT)
page_table_l2:
    resq  512; 524288 entries for the L2 table (PDT)


global page_table_l4
global page_table_l3  
global page_table_l2


section .text.trampoline
global WakeTheFuckUpBoys
extern page_table_l4
extern gdt64

WakeTheFuckUpBoys:


WakeTheFuckUpBoysEnd:
