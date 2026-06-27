#ifndef _KERNEL_DEBUGING_H
#define _KERNEL_DEBUGING_H

#define DEBUG_TRAP \
    struct { \
        uint16_t limit; \
        uint64_t base; \
    } PACKED idtr = {0, 0}; \
    __asm__ volatile("lidt %0" : : "m"(idtr)); \
    __asm__ volatile("int $3") \

#endif