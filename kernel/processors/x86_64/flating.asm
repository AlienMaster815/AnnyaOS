[bits 64]

section .text

extern GetFxSaveForkPointer
extern SetFxSaveForkPointerData

global StoreAdvancedRegisters
global RestoreAdvancedRegisters
global enable_fxsave
global InitializeXSave
global initialize_fpu
global initialize_thread_fpu_state
global initialize_thread_fxsave_state
global InitializeXSaveThread
global fxrstor_handler
global fxsave_handler
global save_fpu_state
global restore_fpu_state

restore_fpu_state:
    frstor [rcx]
    ret

save_fpu_state:
    fsave [rcx]
    ret

fxsave_handler:
    fxsave64  [rcx]
    ret

fxrstor_handler:
    fxrstor64 [rcx]
    ret

StoreAdvancedRegisters: ;push:pop because of void
    push rax
    push rdx
    mov  eax, 0b11
    xor  edx, edx
    XSAVE [RCX]
    pop rdx
    pop rax
	ret

RestoreAdvancedRegisters: ;push:pop because of void
    push rax
    push rdx
    mov  eax, 0b11
    xor  edx, edx
    XRSTOR [RCX]
    pop rdx
    pop rax
	ret



;common ops


;x87 states

initialize_fpu:
    jmp $

    mov rax, cr0
    and rax, ~(1 << 2)
    and rax, ~(1 << 3)
    mov cr0, rax
    fninit
    ret

initialize_thread_fpu_state: ;RCX holds new context RDX holds current
    jmp $
    fsave  [rdx]
    fsave  [rcx]
    frstor [rdx]
    ret

;fxsave state


enable_fxsave:
    push rax
    push rcx
    mov rax, cr0
    and ax,  0xFFFB
    or  ax,  0x02
    mov cr0, rax

    mov rax, cr4
    or  ax,  (3 << 9) 
    mov cr4, rax
    call GetFxSaveForkPointer
    mov rcx, rax 
    fxsave64 [rcx]
    call SetFxSaveForkPointerData
    pop rcx
    pop rax
    ret

initialize_thread_fxsave_state: ;RCX holds new context RDX holds current
    ;caller should raise IRQL to HIGH_LEVEL before calling
    fxsave  [rdx]
    fninit
    fxsave  [rcx]
    fxrstor [rdx]
    ret

InitializeXSave:
    
    jmp $

    mov rax, cr4
    or  rax, (1 << 9)
    or  rax, (1 << 18)
    mov cr4, rax
    
    mov ecx, 0
    mov eax, 0b11
    mov edx, 0
    xsetbv
    
    fninit
    ret

InitializeXSaveThread: ; RCX=new, RDX=current
    ; caller at HIGH_LEVEL

    jmp $

    mov eax, 0b11
    xor edx, edx
    xsave  [rdx]

    fninit

    mov eax, 0b11
    xor edx, edx
    xsave  [rcx]

    mov eax, 0b11
    xor edx, edx
    xrstor [rdx]
    ret
