//Section Allocation Library
#ifndef _SAL_H
#define _SAL_H

#include <cstdlib>
#include <mutex>
#include <pthread.h>

#define GET_ALIGNMENT(x)        alignof(x)

#define SalAllocateType(Type)           (Type*)SalAllocateMemory(sizeof(Type), GET_ALIGNMENT(Type))
#define SalAllocateArray(Type, Members) (Type*)SalAllocateMemory(sizeof(Type) * Members, GET_ALIGNMENT(Type))

typedef unsigned int UINT32; 

typedef uintptr_t UINTPTR;
typedef void* PVOID;
typedef void* HANDLE;
typedef unsigned char UINT8;

#define SAL_API extern "C"
#define SAL_EXPORT __attribute__((visibility("default")))

typedef unsigned long long SIZE, UINT64, uint64_t;

typedef enum{
    STATUS_SUCCESS = 0,
    STATUS_INVALID_PARAMETER,
    STATUS_INSUFFICIENT_RESOURCES,
    STATUS_ALLOCATION_COLISION,
}SAL_STATUS;

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

#ifdef _SAL_INTERNALS_

typedef struct _SAL_ALLOCATION_OBJECT{
    ListHeader      Peers;
    PVOID           Address;
    SIZE            AllocationBase;
    SIZE            AllocationSize;
    SIZE            AllocationAlignment;
}SAL_ALLOCATION_OBJECT, * PSAL_ALLOCATION_OBJECT;

typedef struct _SAL_ALLOCATION_OBJECT_NODE{
    ListHeader              Peers;
//#ifdef __x86_64__
    UINT64                  NodeMap;
    SAL_ALLOCATION_OBJECT   NodeItems[64];   
//#else 
//    UINT32                  NodeMap;
//    UINT64                  NodeMap[32];
//#endif
}SAL_ALLOCATION_OBJECT_NODE, * PSAL_ALLOCATION_OBJECT_NODE;

typedef class SalAllocationObjectManager{
    private:
        ListHeader                  NodeList;
        pthread_mutex_t             NodeListLock;
        PSAL_ALLOCATION_OBJECT_NODE AllocateNode();
        void                        FreeNode(PSAL_ALLOCATION_OBJECT_NODE Node);
        PSAL_ALLOCATION_OBJECT      _AllocateObject();
    public:
        bool                        SetupAllocationObjectManager();
        PSAL_ALLOCATION_OBJECT      AllocateObject();
        void                        FreeObject(PSAL_ALLOCATION_OBJECT Object);
}SAL_ALLOCATION_OBJECT_MANAGER, * PSAL_ALLOCATION_OBJECT_MANAGER;

typedef class SalContextObjectManager{
    private:
        SAL_ALLOCATION_OBJECT_MANAGER   ObjectManager;
        ListHeader                      SectionAllocations;
        pthread_mutex_t                 SectionAllocationsLock;
        PVOID                           FinalizedSection;
        SIZE                            SectionOffsetBase;
        SIZE                            FinalizedSectionSize;
        PSAL_ALLOCATION_OBJECT          CreateAllocationObject();
        void                            DestroyAllocationObject(PSAL_ALLOCATION_OBJECT Object);
        SAL_STATUS                      AllocateSectionSpace(PSAL_ALLOCATION_OBJECT Object, SIZE Size, SIZE Alignment);
        SAL_STATUS                      ReAllocateSectionSpace(PSAL_ALLOCATION_OBJECT Object, SIZE Size, SIZE Alignment);
    public:
        bool                            SetupContextObject(SIZE SectionOffsetBase);
        void                            CleanupContext();
        PSAL_ALLOCATION_OBJECT          AllocateSectionData(SIZE Size, SIZE Alignment);
        void                            FreeSectionData(PSAL_ALLOCATION_OBJECT Object);
        PVOID                           GetSectionDataAddress(PSAL_ALLOCATION_OBJECT Object);
        SIZE                            GetSectionDataOffset(PSAL_ALLOCATION_OBJECT Object);
        SAL_STATUS                      DefineSectionData(PSAL_ALLOCATION_OBJECT* Out, SIZE Offset, SIZE Size, SIZE Alignment);
        SAL_STATUS                      ReAllocateSectionData(PSAL_ALLOCATION_OBJECT Object, SIZE Size, SIZE Alignment);
        SAL_STATUS                      FinalizeSection(SIZE SectionSize);
        PVOID                           GetSectionAddressBase();
        SIZE                            GetSectionOffsetBase();
        SIZE                            GetSectionSize();
}SAL_CONTEXT_OBJECT_MANAGER, * PSAL_CONTEXT_OBJECT_MANAGER;

typedef struct _SECTION_CONTEXT_OBJECT{
    SAL_CONTEXT_OBJECT_MANAGER  SalContextObjectManager;
}SECTION_CONTEXT_OBJECT, * PSECTION_CONTEXT_OBJECT;

PVOID SalAllocateMemory(SIZE Size, SIZE Alignment);
void SalFreeMemory(PVOID Data);

    

#else

#endif
#endif