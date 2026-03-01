#ifndef STDLIB_H
#define STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>


#ifdef __cplusplus
}
#endif

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



#ifndef _CSTD_LIB_H
#define _CSTD_LIB_H

static inline void* LouKeCastToUnalignedPointer(void* pointer){
	return pointer;
}

#ifdef __cplusplus
extern "C" {
#endif


#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#ifndef _KERNEL_MODULE_
int __cxa_guard_acquire(int64_t *guard);
void __cxa_guard_release(int64_t *guard);
void __cxa_guard_abort(int64_t *);





#endif

#ifdef __cplusplus
}
#endif


#endif

