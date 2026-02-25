#ifndef _LIST_MANAGEMENT_H
#define _LIST_MANAGEMENT_H
 
#include <stdbool.h>
#include <kernel/atomic.h>

#ifndef _MUTEX_STRUCTURE_DEFINITION
#define _MUTEX_STRUCTURE_DEFINITION
typedef struct _mutex_t{
    atomic_t locked;
    atomic_t Handle;
    atomic_t PrivaledgeLevel;
    atomic_t ThreadOwnerLow;
    atomic_t ThreadOwnerHigh;
} mutex_t;
#endif

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" { 
#endif



typedef struct _LIST_LINK{
    struct _LIST_LINK*  FLink;
    struct _LIST_LINK*  BLink;
}LIST_LINK, * PLIST_LINK;

typedef struct _LIST_OBJECT{
    mutex_t     Lock;
    LIST_LINK   Head;
    bool        Initialized;
}LIST_OBJECT, * PLIST_OBJECT;

typedef bool (*LIST_SEARCH_FUNC)(PLIST_LINK Link, void* Params); 

void  LouKeLinkObjectToListHead(PLIST_OBJECT ListObject, PLIST_LINK Link);
void  LouKeLinkObjectToListTail(PLIST_OBJECT ListObject, PLIST_LINK Link);
void  LouKeUnlinkObjectFromList(PLIST_OBJECT ListObject, PLIST_LINK Link);
void* LouKeLinkGetMemberWithFunction(PLIST_OBJECT ListObject, LIST_SEARCH_FUNC Func, void* Param);


#ifdef __cplusplus
}
#endif
#endif