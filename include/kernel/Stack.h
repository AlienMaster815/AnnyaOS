#ifndef _STACK_H
#define _STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#define GET_RETURN_ADDRESS(x) __builtin_return_address(x)

#define GetRSP() ({ \
    unsigned long long rsp; \
    __asm__ __volatile__ ("mov %%rsp, %0" : "=r"(rsp)); \
    rsp; \
})

#define GetRBP() ({ \
    unsigned long long rbp; \
    __asm__ __volatile__ ("mov %%rbp, %0" : "=r"(rbp)); \
    rbp; \
})

#ifndef _STACK_INTERNALS_
typedef PVOID PLOUSINE_STACK; 

PVOID 
LouKeCreateStack(
    UINT32  ProcessID,
    SIZE    VSize,
    SIZE    CommitSize,
    BOOLEAN HighMem,
    UINT64  PageFlags
);

#else

typedef struct _LOUSINE_STACK{  
    ListHeader                  Peers;
    PVOID                       Stack;
}LOUSINE_STACK, * PLOUSINE_STACK;

#endif



#ifdef __cplusplus
}
#endif
#endif

