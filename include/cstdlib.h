#ifndef _CSTD_LIB_H
#define _CSTD_LIB_H

#include <cstdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define STRUNCATE 80
#define EINVAL 22
#define ERANGE 34


#define IS_CPP __cplusplus
#define IS_X86 __i386__
#define IS_X86_64 __x86_64__


#define VOID 	void
#define VOIDP	void*

typedef struct  _ListHeader{
    struct _ListHeader* LastHeader;
    struct _ListHeader* NextHeader;
}ListHeader, * PListHeader;

#ifdef __cplusplus
#define UNUSED [[maybe_unused]]
#define UNINIT [[uninitialized]]
#else
#define UNUSED __attribute__((unused))
#define UNINIT __attribute__((uninitialized))
#endif

#define ROUND_UP(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_DOWN64(value, multiple) \
    ((value) / (multiple) * (multiple))



static inline void* LouKeCastToUnalignedPointer(void* pointer){
	return pointer;
}

#ifndef _USER_MODE_CODE_
#define ABS(x) (((x) < 0) ? -(x) : (x)) 
int abs(int x);
#ifndef _KERNEL_MODULE_
int __cxa_guard_acquire(int64_t *guard);
void __cxa_guard_release(int64_t *guard);
void __cxa_guard_abort(int64_t *);
#endif
#endif

#ifdef __cplusplus
}
#endif


#endif

