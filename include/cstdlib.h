#ifndef _CSTD_LIB_H
#define _CSTD_LIB_H

#ifdef __cplusplus
extern "C" {
#endif


#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#ifndef _KERNEL_MODULE_
int __cxa_guard_acquire(int64_t *guard);
void __cxa_guard_release(int64_t *guard);
void __cxa_guard_abort(int64_t *);

static inline void* LouKeCastToUnalignedPointer(void* pointer){
	return pointer;
}



#endif

#ifdef __cplusplus
}
#endif


#endif