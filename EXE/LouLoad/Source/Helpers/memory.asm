[BITS 64]
section .text

;void LouLoadMemCpy(Destination, Source, Count)
LouLoadMemCpy:
    ;check errors
    cmp rcx, 0
    je .InvalidParameterError
    cmp rdx, 0
    je .InvalidParameterError
    cmp r8, 0
    je .InvalidParameterError
    
    push rbx
    push rcx
    push rdx
    push r8
    
    .MemCpyLoop:

    mov bl, [rdx]
    mov [rcx], bl 

    inc rcx
    inc rdx
    dec r8
    jnz .MemCpyLoop

    pop r8
    pop rdx
    pop rcx
    pop rbx
    ret

    .InvalidParameterError:
        ret

;void LouLoadMemSet(Destination, Value, Count)
LouLoadMemSet:
    cmp rcx, 0
    je .InvalidParameterError
    cmp r8, 0
    je .InvalidParameterError

    push rcx
    push r8

    .MemSetLoop:

    mov [rcx], dl

    inc rcx
    dec r8
    jnz .MemSetLoop

    pop r8
    pop rcx
    ret

    .InvalidParameterError:
        ret

;int LouLoadMemCmp
LouLoadMemCmp:
    cmp rcx, 0
    je .InvalidParameterError
    cmp rdx, 0
    je .InvalidParameterError
    cmp r8, 0
    je .InvalidParameterError

    push rbx
    push rcx
    push rdx
    push r8
    
    .MemCmpLoop:

    mov al, [rcx]
    mov bl, [rdx]

    cmp al, bl
    jne .DiferenceFound

    inc rcx
    inc rdx
    dec r8
    jnz .MemCmpLoop

    .DiferenceFound:
    sub al, bl

    pop r8
    pop rdx
    pop rcx
    pop rbx
    ret
    
    .InvalidParameterError:
    ret