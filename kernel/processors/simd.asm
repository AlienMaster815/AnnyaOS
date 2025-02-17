section .text

global simd_copy
global enable_sse1

simd_copy:
    movups xmm0, [rdx]  ; Load 128-bit from source
    movups [rcx], xmm0  ; Store 128-bit to destination
    ret;
