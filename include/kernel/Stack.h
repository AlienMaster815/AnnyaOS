#ifndef _STACK_H
#define _STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _STACK_INTERNALS_
typedef PVOID PLOUSINE_STACK; 

PVOID 
LouKeCreateStack(
    UINT32  ProcessID,
    SIZE    VSize,
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

