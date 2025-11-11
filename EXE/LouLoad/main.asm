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

section .text

global LouLoaderMain

LouLoaderMain:

    jmp $