bits 64
default rel

section .data

REGISTERULONG dd 0
BUFFERULONG dd 0

section .text

global LouKeMachineLevelReadRegisterUlong
global LouKeMachineLevelWriteRegisterUlong

LouKeMachineLevelReadRegisterUlong:

    ret

LouKeMachineLevelWriteRegisterUlong:

    ret
