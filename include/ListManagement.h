#ifndef _LIST_MANAGEMENT_H
#define _LIST_MANAGEMENT_H

#include <stdbool.h>
#include <kernel/threads.h>

#ifdef __cplusplus
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

static inline void LouKeListAddTail(PListHeader Tail, PListHeader Header){
    while(Header->NextHeader){
        Header = Header->NextHeader;
    }
    Header->NextHeader = Tail;
    Tail->LastHeader = Header;
}

static inline void LouKeListDeleteItem(PListHeader Item){
    PListHeader LastHeader = Item->LastHeader;
    PListHeader NextHeader = Item->NextHeader;
    if(LastHeader){
        LastHeader->NextHeader = NextHeader;
    }
    if(NextHeader){
        NextHeader->LastHeader = LastHeader;
    }
}

static inline void LouKeListInsertInFront(
    PListHeader Item, 
    PListHeader LastItem
){
    PListHeader NextItem = 0;
    if(LastItem){
        NextItem = LastItem->NextHeader;
    }
    Item->NextHeader = NextItem;
    if(NextItem){
        NextItem->LastHeader = Item;
    }
    Item->LastHeader = LastItem;
}

void  LouKeLinkObjectToListHead(PLIST_OBJECT ListObject, PLIST_LINK Link);
void  LouKeLinkObjectToListTail(PLIST_OBJECT ListObject, PLIST_LINK Link);
void  LouKeUnlinkObjectFromList(PLIST_OBJECT ListObject, PLIST_LINK Link);
void* LouKeLinkGetMemberWithFunction(PLIST_OBJECT ListObject, LIST_SEARCH_FUNC Func, void* Param);

#define ListItemToType(Header, Type, Member) ((Type*)(UINTPTR)(Header ? CONTAINER_OF(Header, Type, Member) : 0x00))



#define ForEachIf(Condition) if(!(Condition)){} else

#ifdef __cplusplus
}
#endif
#endif