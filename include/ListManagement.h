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

#define ListMemberIsNotNull(Item, Member) ((UINTPTR)(Item) + offsetof(typeof(*(Item)), Member) != 0x00)

#define ListItemToType(Header, Type, Member) ((Type*)(UINTPTR)(CONTAINER_OF(Header, Type, Member)))
#define LListItemToType(Header, Type, Member) ((Type*)(UINTPTR)(CONTAINER_OF(Header, Type, Member)))

#define ForEachListItem(Position, Node) for((Position) = Node; Position; (Position) = (Position)->NextHeader)
#define ForEachLListItem(Position, Node) ForEachListItem(Position, Node)

#define ForEachListEntry(Position, Node, Member) for((Position) = ListItemToType((Node), typeof(*(Position)), Member); ListMemberIsNotNull(Position, Member); (Position) = ListItemToType((Position)->Member.NextHeader, typeof(*(Position)), Member)) 
#define ForEachListEntrySafe(Position,N, Node, Member) for((Position) = ListItemToType((Node), typeof(*(Position)), Member); ListMemberIsNotNull(Position, Member) && (N = ListItemToType(Position->Member.NextHeader, typeof(*N), Member), true); Position = N) 

#define ForEachLListEntry(Position, N, Node, Member) ForEachListEntry(Position, N, Node, Member)
#define ForEachLListEntrySafe(Position, N, Node, Member) ForEachListEntrySafe(Position, N, Node, Member)

#define ListItemToTypeOrNull(Header, Type, Member) ((Type*)(UINTPTR)(Header ? CONTAINER_OF(Header, Type, Member) : 0x00))


static inline void LouKeListAddTail(PListHeader Tail, PListHeader Header){
    while(Header->NextHeader){
        Header = Header->NextHeader;
    }
    Header->NextHeader = Tail;
    Tail->LastHeader = Header;
}

static inline void LouKeLListDeleteItem(PListHeader Item){
    PListHeader LastHeader = (PListHeader)(UINT64)LouKeGetAtomic64FromUint64((UINT64*)&Item->LastHeader);
    PListHeader NextHeader = (PListHeader)(UINT64)LouKeGetAtomic64FromUint64((UINT64*)&Item->NextHeader);
    if(LastHeader){
        LouKeSetAtomic64FromUint64((UINT64*)&LastHeader->NextHeader, (int64_t)(UINT64)(UINTPTR)NextHeader);
    }
    if(NextHeader){
        LouKeSetAtomic64FromUint64((UINT64*)&NextHeader->LastHeader, (int64_t)(UINT64)(UINTPTR)LastHeader);
    }
}

#define LouKeLListDeleteAll(Head) LouKeLListDeleteItem(Head)


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

#define LouKeListDeleteAll(Head) LouKeListDeleteItem(Head)

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




#define ForEachIf(Condition) if(!(Condition)){} else

#ifdef __cplusplus
}
#endif
#endif