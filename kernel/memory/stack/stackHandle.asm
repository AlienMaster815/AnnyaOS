Bits 64

default rel

section .data

StackSize dw 0
StackBase dq 0
FunctionPointer dd 0
FunctionParameters dd 0
StackTop dd 0
;StackBase dd 0

section .text

;global ___chkstk_ms
;global __chkstk ;ntoskrnl too
global RunStack


extern LouKeStackPanic
extern LouKeGetStackSize

;___chkstk_ms:


;	jmp $

