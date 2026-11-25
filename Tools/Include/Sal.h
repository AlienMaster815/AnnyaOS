//Section Allocation Library
#ifndef _SAL_H
#define _SAL_H

#include <ShDef.h>

typedef enum{
    STATUS_SUCCESS = 0,
    STATUS_INVALID_PARAMETER,
    STATUS_INSUFFICIENT_RESOURCES,
    STATUS_ALLOCATION_COLISION,
}SAL_STATUS;

#ifdef _SAL_INTERNALS_

#define SAL_API extern "C"
#define SAL_EXPORT __attribute__((visibility("default")))

#define SalAllocateType(Type)           (Type*)SalAllocateMemory(sizeof(Type), GET_ALIGNMENT(Type))
#define SalAllocateArray(Type, Members) (Type*)SalAllocateMemory(sizeof(Type) * Members, GET_ALIGNMENT(Type))

typedef struct _SAL_ALLOCATION_OBJECT{
    ListHeader      Peers;
    PVOID           Address;
    SIZE            AllocationBase;
    SIZE            AllocationSize;
    SIZE            AllocationAlignment;
}SAL_ALLOCATION_OBJECT, * PSAL_ALLOCATION_OBJECT;

typedef struct _SAL_ALLOCATION_OBJECT_NODE{
    ListHeader              Peers;
    UINT64                  NodeMap;
    SAL_ALLOCATION_OBJECT   NodeItems[64];   
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

SAL_EXPORT
SAL_API
HANDLE 
SalCreateSectionContext(SIZE SectionOffsetBase);

SAL_EXPORT
SAL_API
void 
SalDestroySectionContext(HANDLE Context);

SAL_EXPORT
SAL_API
HANDLE 
SalAllocateSectionData(
    HANDLE  Context, 
    SIZE    Size, 
    SIZE    Alignment
);

SAL_EXPORT
SAL_API
void
SalFreeSectionData(
    HANDLE  Context, 
    HANDLE  Object
);

SAL_EXPORT
SAL_API
PVOID                           
SalGetSectionDataAddress(
    HANDLE Context, 
    HANDLE Object
);

SAL_EXPORT
SAL_API
SIZE 
SalGetSectionDataOffset(
    HANDLE Context, 
    HANDLE Object
);

SAL_EXPORT
SAL_API
SAL_STATUS 
SalDefineSectionData(
    HANDLE  Context, 
    HANDLE* Out, 
    SIZE    Offset, 
    SIZE    Size, 
    SIZE    Alignment
);

SAL_EXPORT
SAL_API
SAL_STATUS 
SalReAllocateSectionData(
    HANDLE  Context,
    HANDLE  Object,
    SIZE    Size,
    SIZE    Alignment
);

SAL_EXPORT
SAL_API
SAL_STATUS
SalFinalizeSection(
    HANDLE  Context,
    SIZE    SectionSize
);

SAL_EXPORT
SAL_API
PVOID
SalGetSectionAddressBase(HANDLE Context);

SAL_EXPORT
SAL_API
SIZE
SalGetSectionOffsetBase(HANDLE Context);

SAL_EXPORT
SAL_API
SIZE
SalGetSectionSize(HANDLE Context);

#endif
#endif