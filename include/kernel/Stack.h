#ifndef _STACK_H
#define _STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _STACK_INTERNALS_
typedef PVOID PLOUSINE_STACK; 
#else

typedef struct _LOUSINE_STACK{  
    ListHeader                  Peers;
    PLAZY_ALLOCATION_TRACKER    AllocationData;

}LOUSINE_STACK, * PLOUSINE_STACK;

#endif



#ifdef __cplusplus
}
#endif
#endif

