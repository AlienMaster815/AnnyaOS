#ifndef STDLIB_H
#define STDLIB_H


#include <stdint.h>

#define STRUNCATE 80
#define EINVAL 22
#define ERANGE 34


#ifdef __cplusplus
#define UNUSED [[maybe_unused]]
#define UNINIT [[uninitialized]]
#else
#define UNUSED __attribute__((unused))
#define UNINIT __attribute__((uninitialized))
#endif

#define VOID void
#define VOIDP void*

#define LOUSTATUS uint32_t

#define IS_CPP __cplusplus
#define IS_X86 __i386__
#define IS_X86_64 __x86_64__

#ifndef _KERNEL_MODULE_

#define ROUND_UP(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_DOWN64(value, multiple) \
    ((value) / (multiple) * (multiple))

#define ABS(x) \
    (((x) < 0) ? -(x) : (x))
int abs(int x);

#else

#define ROUND_UP(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#endif

#endif 

