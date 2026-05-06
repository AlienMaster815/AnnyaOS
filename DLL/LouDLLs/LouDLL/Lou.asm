[BITS 64]
section .text

global NtGetPeb
global NtGetTeb
global LouGetPeb
global LouGetTeb
global LouRaiseException
global LouCaptureNtContext

extern LouGetFloatStoreImplementation

NtGetPeb:
LouGetPeb:
    mov rax, qword[gs:0x60]
    ret

NtGetTeb:
LouGetTeb:
    mov rax, qword[gs:0x30]
    ret

LouCaptureNtCtxHomeRegs:
    push r15
    lea r15, [rsp + 24] 
    push r14
    push r13
    push r12
    push r11
    push r10
    push rax
    push rdx

    xor r11, r11            
    .loop:
    mov r12, rcx            ;   PNT_AMD64_CONTEXT 
    mov r14, r15            ;   Shadow[0]
    mov rax, r11            ;   i
    mov r13, 8              ;   sizeof(MACHINE_REGISTER)
    mul r13                 ;   i * sizeof(MACHINE_REGISTER)
    add r12, rax            ;   PNT_AMD64_CONTEXT->P[i]Home
    add r14, rax            ;   Shadow[i]
    mov qword r10, [r14]    ;   PNT_AMD64_CONTEXT->P[i]Home = Shadow[i]
    mov qword [r12], r10
    inc r11                 ;   i++
    cmp r11, 6              ;   while(i < 6) || == P6Home
    jne .loop               ;   {}

    pop rdx
    pop rax
    pop r10
    pop r11
    pop r13
    pop r14
    pop r15
    ret

LouCaputreControl:
    push r15
    lea r15, [rsp + 0x18] 
    mov qword [rcx + 0x98], r15
    pop r15
    mov qword [rcx + 0xA0], rbp
    push rax
    mov qword rax, [rsp + 0x10]
    mov qword [rcx + 0xF8], rax
    pushfq
    pop rax
    mov dword [rcx + 0x44], eax ; using eax to autoand because NTCONTEXT only supports the eflags data
    pop rax
ret

LouCaptureInteger:
    mov qword [rcx + 0x0078], rax
    mov qword [rcx + 0x0080], rcx
    mov qword [rcx + 0x0088], rdx
    mov qword [rcx + 0x0090], rbx
    mov qword [rcx + 0x00A8], rsi
    mov qword [rcx + 0x00B0], rdi
    mov qword [rcx + 0x00B8], r8
    mov qword [rcx + 0x00C0], r9
    mov qword [rcx + 0x00C8], r10
    mov qword [rcx + 0x00D0], r11
    mov qword [rcx + 0x00D8], r12
    mov qword [rcx + 0x00E0], r13
    mov qword [rcx + 0x00E8], r14
    mov qword [rcx + 0x00F0], r15
ret 

LouCaptureSegments:
    mov [rcx + 0x38], cs
    mov [rcx + 0x3A], ds
    mov [rcx + 0x3C], es
    mov [rcx + 0x3E], fs
    mov [rcx + 0x40], gs
    mov [rcx + 0x42], ss
    ret
ret

LouCaptureFloatingPoint:
    stmxcsr [rcx + 0x34]
    push rax
    call LouGetFloatStoreImplementation

    cmp rax, 0
    je .NoFloatSaving
    cmp rax, 1
    je .UseFsave
    cmp rax, 2
    je .UseXsave
    cmp rax, 3
    je .UseFxsave

.UseFsave:
    fsave [rcx + 0x0100]
    frstor [rcx + 0x0100]
    pop rax
    ret

.UseXsave:
    push rdx
    mov  eax, 0b11
    xor  edx, edx
    XSAVE [rcx + 0x0100]
    pop rdx
    pop rax
	ret

.UseFxsave:
    fxsave64  [rcx + 0x0100]
    pop rax
    ret

.NoFloatSaving:
    pop rax
    ret

LouCaptureNtContext:
    ;RCX/param1 has the PNT_AMD64_CONTEXT   
    
    call LouCaptureNtCtxHomeRegs
    push rax
    push rbx
    mov dword rax, [rcx + 0x30]
    cmp rax, 0
    je .nothing_else
    cmp rax, 0x0010000B
    je .Full
    cmp rax, 0x0010001F
    je .Full
    
    mov rbx, rax
    and rbx, 0x0F
    cmp rbx, 0x0F 
    je .Full
    cmp rbx, 0x01
    je .CtxControl 
    cmp rbx, 0x02
    je .CtxInteger
    cmp rbx, 0x04
    je .CtxSegs
    cmp rbx, 0x08
    je .CtxFloats
    cmp rbx, 0x10
    je .nothing_else
    cmp rbx, 0x03
    je .CtxCI
    cmp rbx, 0x05
    je .CtxCS
    cmp rbx, 0x09
    je .CtxCF
    cmp rbx, 0x07
    je .CtxCIS
    cmp rbx, 0x0B
    je .CtxCIF
    cmp rbx, 0x0D
    je .CtxCSF
    cmp rbx, 0x06
    je .CtxIS
    cmp rbx, 0x0A
    je .CtxIF
    cmp rbx, 0x0C
    je .CtxSF
    cmp rbx, 0x0E
    je .CtxISF
    jmp .nothing_else

    .CtxIS:
        pop rax
        pop rbx
        call LouCaptureInteger
        call LouCaptureSegments
        ret

    .CtxIF:
        pop rax
        pop rbx
        call LouCaptureInteger
        call LouCaptureFloatingPoint
        ret

    .CtxSF:
        pop rax
        pop rbx
        call LouCaptureSegments
        call LouCaptureFloatingPoint
        ret

    .CtxISF:
        pop rax
        pop rbx
        call LouCaptureInteger
        call LouCaptureSegments
        call LouCaptureFloatingPoint
        ret
    .CtxControl:
        pop rax
        pop rbx
        call LouCaputreControl
        ret
    .CtxInteger:
        pop rax
        pop rbx
        call LouCaptureInteger
        ret
    .CtxSegs:
        pop rax
        pop rbx
        call LouCaptureSegments
        ret
    .CtxFloats:
        pop rax
        pop rbx
        call LouCaptureFloatingPoint
        ret
    .CtxCI:
        pop rax
        pop rbx
        call LouCaputreControl
        call LouCaptureInteger
        ret
    .CtxCS:
        pop rax
        pop rbx
        call LouCaputreControl
        call LouCaptureSegments
        ret

    .CtxCF:
        pop rax
        pop rbx
        call LouCaputreControl
        call LouCaptureFloatingPoint
        ret
    .CtxCIS:
        pop rax
        pop rbx
        call LouCaputreControl
        call LouCaptureInteger
        call LouCaptureSegments
        ret
    .CtxCIF:
        pop rax
        pop rbx
        call LouCaputreControl
        call LouCaptureInteger
        call LouCaptureFloatingPoint
        ret
    .CtxCSF:
        pop rax
        pop rbx
        call LouCaputreControl
        call LouCaptureSegments
        call LouCaptureFloatingPoint
        ret

    .Full:    
    pop rax
    pop rbx
    call LouCaputreControl
    call LouCaptureInteger
    call LouCaptureSegments
    call LouCaptureFloatingPoint
    .nothing_else:
    ret