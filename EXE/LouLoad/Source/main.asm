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
MultibootDataPointer dd 0

section .bss 

StackTop:
    resb  16 * 1024
StackBase:

section .text

global LouLoaderMain

;0xFFFFF800000000000 will be kernel space

LouLoaderMain:
    mov ebp, StackBase
    mov esp, StackBase
    mov [MultibootDataPointer], eax

    call CheckCpuId    
    call CheckLongMode
    call SetUpPageTables



    jmp $


CheckCpuId:
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
    je .NoCpuId
    ret
.NoCpuId:
    mov al, "C"
    jmp Error

CheckLongMode:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .NoLongMode
    ret
.NoLongMode:
    mov al, "L"
    jmp Error

Error:
    ; Print "ERR: X" where X is the error code
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt

SetUpPageTables:

    ret

section .bss
align 4096
PageTableL4:
    resq 512
PageTableL3Loader:
    resq 512
PageTableL3Kernel:
    resq 512
PageTableL2Loader:
    resq 512
PageTableL2Kernel:
    resq 512
