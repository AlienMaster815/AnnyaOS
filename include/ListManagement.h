#ifndef _LIST_MANAGEMENT_H
#define _LIST_MANAGEMENT_H

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

#ifdef _LIST_MANAGER_INTERNALS_
typedef struct _LIST_OBJECT{
    mutex_t     Lock;
    LIST_LINK   Head;
    PLIST_LINK  Tail;
}LIST_OBJECT, * PLIST_OBJECT;
#else
typedef void* PLIST_OBJECT;
#endif

void LouKeLinkObjectToListHead(PLIST_OBJECT ListObject, void* Object);
void LouKeLinkObjectToListTail(PLIST_OBJECT ListObject, void* Object);
void LouKeUnlinkObjectFromList(PLIST_OBJECT ListObject, void* Object);

#ifdef __cplusplus
}
#endif
#endif