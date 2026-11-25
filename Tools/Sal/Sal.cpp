#define _SAL_INTERNALS_
#include "Sal.h"

PVOID SalAllocateMemory(SIZE Size, SIZE Alignment){
    if(!Size){
        return 0x00;
    }
    if(Alignment < sizeof(void*)){
        Alignment = sizeof(void*);
    }
    SIZE AlignedSize = (Size + Alignment - 1) & ~(Alignment - 1);
    PVOID NewData = aligned_alloc(Alignment, AlignedSize);
    if(!NewData) {
        return 0x00;
    }
    memset(NewData, 0, AlignedSize);
    return NewData;
}

void SalFreeMemory(PVOID Data){
    free(Data);
}

SAL_EXPORT
SAL_API
HANDLE 
SalCreateSectionContext(SIZE SectionOffsetBase){
    PSECTION_CONTEXT_OBJECT NewContext = SalAllocateType(SECTION_CONTEXT_OBJECT);
    if(!NewContext){
        return (HANDLE)0x00;
    }
    bool Status = NewContext->SalContextObjectManager.SetupContextObject(SectionOffsetBase);
    if(!Status){
        SalFreeMemory(NewContext);
        return 0x00;
    }
    return (HANDLE)NewContext;
}

SAL_EXPORT
SAL_API
void 
SalDestroySectionContext(HANDLE Context){
    if(!Context){
        return;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    SectionContext->SalContextObjectManager.CleanupContext();
    SalFreeMemory(SectionContext);
}

SAL_EXPORT
SAL_API
HANDLE 
SalAllocateSectionData(
    HANDLE  Context, 
    SIZE    Size, 
    SIZE    Alignment
){
    if((!Context) || (!Size) || (!Alignment)){
        return 0x00;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return (HANDLE)SectionContext->SalContextObjectManager.AllocateSectionData(Size, Alignment);
}

SAL_EXPORT
SAL_API
void
SalFreeSectionData(
    HANDLE  Context, 
    HANDLE  Object
){
    if((!Context) || (!Object)){
        return;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    SectionContext->SalContextObjectManager.FreeSectionData((PSAL_ALLOCATION_OBJECT)Object);
}

SAL_EXPORT
SAL_API
PVOID                           
SalGetSectionDataAddress(
    HANDLE Context, 
    HANDLE Object
){
    if((!Context) || (!Object)){
        return 0x00;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return SectionContext->SalContextObjectManager.GetSectionDataAddress((PSAL_ALLOCATION_OBJECT)Object);
}

SAL_EXPORT
SAL_API
SIZE 
SalGetSectionDataOffset(
    HANDLE Context, 
    HANDLE Object
){
    if((!Context) || (!Object)){
        return 0x00;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return SectionContext->SalContextObjectManager.GetSectionDataOffset((PSAL_ALLOCATION_OBJECT)Object);
}

SAL_EXPORT
SAL_API
SAL_STATUS 
SalDefineSectionData(
    HANDLE  Context, 
    HANDLE* Out, 
    SIZE    Offset, 
    SIZE    Size, 
    SIZE    Alignment
){
    if((!Context) || (!Out) || (!Size) || (!Alignment)){
        return STATUS_INVALID_PARAMETER;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return SectionContext->SalContextObjectManager.DefineSectionData((PSAL_ALLOCATION_OBJECT*)Out, Offset, Size, Alignment);
}

SAL_EXPORT
SAL_API
SAL_STATUS 
SalReAllocateSectionData(
    HANDLE  Context,
    HANDLE  Object,
    SIZE    Size,
    SIZE    Alignment
){
    if((!Context) || (!Object) || ((Size) && (!Alignment))){
        return STATUS_INVALID_PARAMETER;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return SectionContext->SalContextObjectManager.ReAllocateSectionData((PSAL_ALLOCATION_OBJECT)Object, Size, Alignment);
}

SAL_EXPORT
SAL_API
SAL_STATUS
SalFinalizeSection(
    HANDLE  Context,
    SIZE    SectionSize
){
    if((!Context) || (!SectionSize)){
        return STATUS_INVALID_PARAMETER;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return SectionContext->SalContextObjectManager.FinalizeSection(SectionSize);
}

SAL_EXPORT
SAL_API
PVOID
SalGetSectionAddressBase(HANDLE Context){
    if(!Context){
        return 0x00;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return SectionContext->SalContextObjectManager.GetSectionAddressBase();
}

SAL_EXPORT
SAL_API
SIZE
SalGetSectionOffsetBase(HANDLE Context){
    if(!Context){
        return 0x00;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return SectionContext->SalContextObjectManager.GetSectionOffsetBase();
}

SAL_EXPORT
SAL_API
SIZE
SalGetSectionSize(HANDLE Context){
    if(!Context){
        return 0x00;
    }
    PSECTION_CONTEXT_OBJECT SectionContext = (PSECTION_CONTEXT_OBJECT)Context;
    return SectionContext->SalContextObjectManager.GetSectionSize();
}
