#ifndef _SHARED_DEFINITIONS_H
#define _SHARED_DEFINITIONS_H

#include <cstdlib>
#include <mutex>
#include <pthread.h>

#define GET_ALIGNMENT(x)        alignof(x)

typedef unsigned int UINT32; 

typedef uintptr_t UINTPTR;
typedef void* PVOID;
typedef void* HANDLE;
typedef unsigned char UINT8;

typedef unsigned long long SIZE, UINT64, uint64_t;

typedef struct _ListHeader{
    struct _ListHeader* NextHeader;
    struct _ListHeader* LastHeader;
}ListHeader, * PListHeader;

static inline void ListAddTail(PListHeader Tail, PListHeader Header){
    while(Header->NextHeader){
        Header = Header->NextHeader;
    }
    Header->NextHeader = Tail;
    Tail->LastHeader = Header;
}

static inline void ListDeleteItem(PListHeader Item){
    PListHeader LastHeader = Item->LastHeader;
    PListHeader NextHeader = Item->NextHeader;
    if(LastHeader){
        LastHeader->NextHeader = NextHeader;
    }
    if(NextHeader){
        NextHeader->LastHeader = LastHeader;
    }
    Item->NextHeader = 0x00;
    Item->LastHeader = 0x00;
}

static inline bool RangeInterferes(uint64_t AddrA, uint64_t SizeA, uint64_t AddrB, uint64_t SizeB){
    return !( (AddrA + SizeA <= AddrB) || (AddrB + SizeB <= AddrA));
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define CONTAINER_OF(ptr, type, field_name) ((type *)(((char *)ptr) - offsetof(type, field_name)))
#define OFFSET_OF(Type, Field) offsetof(Type, Field)

#define ListItemToTypeOrNull(Header, Type, Member) \
    ((Type*)(UINTPTR)((Header) ? CONTAINER_OF((Header), Type, Member) : 0x00))
#define ListMemberIsNotNull(Item, Member) ((Item) != NULL)

#define ForEachListEntry(Position, Node, Member) \
    for((Position) = ListItemToTypeOrNull(((Node)->NextHeader), typeof(*(Position)), Member); \
        ListMemberIsNotNull((Position), Member); \
        (Position) = ListItemToTypeOrNull((Position)->Member.NextHeader, typeof(*(Position)), Member))

#define ForEachListEntrySafe(Position, N, Node, Member) \
    for((Position) = ListItemToTypeOrNull(((Node)->NextHeader), typeof(*(Position)), Member); \
        ListMemberIsNotNull((Position), Member) && ((N) = ListItemToTypeOrNull((Position)->Member.NextHeader, typeof(*(N)), Member), true); \
        (Position) = (N))

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#endif