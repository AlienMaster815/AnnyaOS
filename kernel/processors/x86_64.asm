global SetUpSmpPageing

global StoreAdvancedRegisters
global RestoreAdvancedRegisters
global SetGS
global GetRBP
global GetGS
global RecreateDisasemblyIssue
global SetTEB
global SetPEB
global GetPEB
global GetGSValue

section .rodata
gdt64:
    dq 0 ; Null segment
.code_segment: equ $ - gdt64 ;8
    dq 0x00AF9A000000FFFF ; 64-bit Code segment (CS)
.data_segment: equ $ - gdt64 ; 10
    dq 0x00AF92000000FFFF ; 64-bit Data segment (DS)
.user_code_segment: equ $ - gdt64 ; 18
    dq 0x00AFFA000000FFFF ; 64-bit User mode Code segment (CS)
.user_data_segment: equ $ - gdt64 ; 20
    dq 0x00AFF20000000FFFF ; 64-bit User mode Data segment (DS)
.system_code_segment: equ $ - gdt64 ; 28
    dq 0x00AF92000000FFFF ; 64-bit System mode Code segment (CS)
.system_data_segment: equ $ - gdt64 ; 30
    dq 0x00AF92000000FFFF ; 64-bit System mode Data segment (DS)
.interrupt_code_segment: equ $ - gdt64 ; 38
    dq 0x00AF9A000000FFFF ; 64-bit Interrupt Code segment (CS)
.interrupt_data_segment: equ $ - gdt64 ; 40
    dq 0x00AF92000000FFFF ; 64-bit Interrupt Data segment (DS)
.syscall_code_segment: equ $ - gdt64 ; 48
    dq 0x00AF9A000000FFFF ; 64-bit Syscall Code segment (CS)
.syscall_data_segment: equ $ - gdt64 ; 50
    dq 0x00AF92000000FFFF ; 64-bit Syscall Data segment (DS)
.pointer:
    dw $ - gdt64 - 1 ; length
    dq gdt64 ; address


section .data
    fpu_control_word dq 0x037F ; Set FPU control word to default value (e.g., rounding to nearest, full precision)

    ;extern uint64_t SmpStackTop;  // Externally declared stack top
    ;extern uint64_t SmpStackBottom;  // Externally declared stack bottom
    global SmpStackTop
    global SmpStackBottom


Temp_gdt_start:
    ; Null descriptor
    dq 0x0000000000000000
    ; Code segment descriptor (base=0, limit=4GB, 4KB granularity, 32-bit, executable, readable)
    dq 0x00CF9A000000FFFF
    ; Data segment descriptor (base=0, limit=4GB, 4KB granularity, 32-bit, writable)
    dq 0x00CF92000000FFFF
Temp_gdt_end:


section .bss
align 16
    TempStack resb 4096  ; Temporary stack
    SmpStackTop resb 4096  ; 64-bit stack

section .text
    global init_fpu
    global WakeTheFuckUpBoys
    global getTrampolineAddress
    extern fpu_control_word
    extern  GetIdtAsmTailCall
    extern  GetGdtAsmTailCall
    global GetWakeTheFuckUpBoysEnd

extern TURN_FPU_ON

init_fpu:
    sub rsp, 8          ; Align stack
    fninit              ; Initialize FPU (clears all status flags)
    fldcw [fpu_control_word] ; Load FPU control word
    add rsp, 8          ; Restore stack
    call TURN_FPU_ON
    ret

[BITS 32]
section .text.trampoline
global WakeTheFuckUpBoys
extern page_table_l4
extern gdt64

WakeTheFuckUpBoys:


WakeTheFuckUpBoysEnd:
[BITS 64]

getTrampolineAddress:
    mov rax, WakeTheFuckUpBoys
    ret

GetWakeTheFuckUpBoysEnd:
    mov rax, WakeTheFuckUpBoysEnd
    ret


GetCr4:
    mov rax, cr4
    ret



StoreAdvancedRegisters:
	XSAVE [RCX]
	ret

RestoreAdvancedRegisters:
	XRSTOR [RCX]
	ret

global InitializeXSave

InitializeXSave:
    mov rax, cr4       ; Read CR4
    or rax, (1 << 18)  ; Set OSXSAVE bit (bit 18)
    mov cr4, rax       ; Write back to CR4

    ; XSAVE is supported, now you can use XGETBV safely
    mov ecx, 0
    xgetbv
    or eax, 0b111
    mov ecx, 0
    xsetbv


GetRBP:
    mov rax, rbp
    ret

RecreateDisasemblyIssue:
    ret

SetTEB:
    mov qword[gs:0x30], RCX
    ret

SetPEB:
    mov qword[gs:0x60], RCX
    ret

GetPEB:
    mov rax, qword[gs:0x60]
    ret

GetGSValue:
    mov rax, qword[gs:rcx]
    ret