section .text 

    global NtLowLouAplcSetInformation
    extern LouAlpcSetInformation

    NtLowLouAplcSetInformation:
        sub rsp, 0x28
        mov r9,  0x04
        mov [rsp + 0x38], rdx
        lea r8, [rsp + 0x38] 
        lea rdx, [r9 + 4]
        call LouAlpcSetInformation
        add rsp, 0x28
        ret