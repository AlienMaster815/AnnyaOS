#ifndef _LOUQS_H
#define _LOUQS_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif
 
typedef struct  _LOUQ{
    ListHeader                  Peers;
    spinlock_t                  LOUQLock;
    mutex_t                     LouQtex;
    struct _LOUQ_COMPLETION*    Completion;
}LOUQ, * PLOUQ;

typedef struct _LOUQ_WAIT{
    LOUQ    LouQHeader;
}LOUQ_WAIT, * PLOUQ_WAIT;

typedef struct _LOUQ_WORK{
    ListHeader          CurrentWorkList;
    LOUQ                LouQHeader;
    DELAYED_FUNCTION    Work;
}LOUQ_WORK, * PLOUQ_WORK;



static inline void LouKeLouQInitializeWork(PLOUQ_WORK Work, DELAYED_CALLBACK Callback){
    Work->Work.DelayedFunction = Callback;
}

#ifndef _KERNEL_MODULE_

LOUSTATUS LouKeStartWork(PLOUQ_WORK Work);

#else

KERNEL_EXPORT LOUSTATUS LouKeStartWork(PLOUQ_WORK Work);
 
#endif
#ifdef __cplusplus
}
#endif
#endif 