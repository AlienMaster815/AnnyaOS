#define _SAL_INTERNALS_
#include "Sal.h"

PSAL_ALLOCATION_OBJECT SalContextObjectManager::CreateAllocationObject(){
    return this->ObjectManager.AllocateObject();
}

void SalContextObjectManager::DestroyAllocationObject(PSAL_ALLOCATION_OBJECT Object){
    this->ObjectManager.FreeObject(Object);
}

SAL_STATUS SalContextObjectManager::AllocateSectionSpace(
    PSAL_ALLOCATION_OBJECT  Object, 
    SIZE                    Size, 
    SIZE                    Alignment
){
    if((!Object) || (!Size) || (!Alignment)){
        return STATUS_INVALID_PARAMETER;
    }
    PSAL_ALLOCATION_OBJECT  TmpObject;
    SIZE                    TmpBase = 0x00;
    SIZE                    TmpHint;
    while(1){
        bool FoundAllocation = true;
        ForEachListEntry(TmpObject, &this->SectionAllocations, Peers){
            if(RangeInterferes(TmpBase, Size, TmpObject->AllocationBase, TmpObject->AllocationSize)){
                FoundAllocation = false;
                break;
            }
        }
        if(FoundAllocation){
            break;
        }
        TmpHint = ROUND_UP64(TmpObject->AllocationBase + TmpObject->AllocationSize, Alignment);
        if(TmpHint == TmpBase){
            TmpHint += Alignment;
        }
        TmpBase = TmpHint;
    }
    Object->AllocationBase = TmpBase;
    return STATUS_SUCCESS;
}

SAL_STATUS SalContextObjectManager::ReAllocateSectionSpace(
    PSAL_ALLOCATION_OBJECT  Object, 
    SIZE                    Size, 
    SIZE                    Alignment
){
    if((!Object) || ((Size) && (!Alignment))){
        return STATUS_INVALID_PARAMETER;
    }
    SAL_STATUS Status;
    ListDeleteItem(&Object->Peers);
    if(!Size){
        return STATUS_SUCCESS;
    }
    Status = this->AllocateSectionSpace(Object, Size, Alignment);
    if(Status == STATUS_SUCCESS){
        Object->AllocationSize = Size;
        Object->AllocationAlignment = Alignment;
        ListAddTail(&Object->Peers, &this->SectionAllocations);
    }
    return Status;
}

bool SalContextObjectManager::SetupContextObject(SIZE SectionOffsetBase){
    bool Status;
    this->SectionOffsetBase = SectionOffsetBase;
    Status = pthread_mutex_init(&this->SectionAllocationsLock, nullptr) ? false : true;
    if(!Status){
        return Status;
    }
    Status = this->ObjectManager.SetupAllocationObjectManager();
    if(!Status){
        return Status;
    }
    return true;
}

void SalContextObjectManager::CleanupContext(){
    PSAL_ALLOCATION_OBJECT  TmpObject;
    PSAL_ALLOCATION_OBJECT  TmpObjectSafe;
    pthread_mutex_lock(&this->SectionAllocationsLock);
    ForEachListEntrySafe(TmpObject, TmpObjectSafe, &this->SectionAllocations, Peers){
        ListDeleteItem(&TmpObject->Peers);
        this->DestroyAllocationObject(TmpObject);
    }
    if(this->FinalizedSection){
        SalFreeMemory(this->FinalizedSection);
    }
    pthread_mutex_unlock(&this->SectionAllocationsLock);
}

PSAL_ALLOCATION_OBJECT SalContextObjectManager::AllocateSectionData(SIZE Size, SIZE Alignment){
    SAL_STATUS Status;
    PSAL_ALLOCATION_OBJECT NewObject;
    pthread_mutex_lock(&this->SectionAllocationsLock);
    NewObject = this->CreateAllocationObject();
    if(!NewObject){
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _ERROR_OUT;
    }
    Status = this->AllocateSectionSpace(NewObject, Size, Alignment);
    if(Status != STATUS_SUCCESS){
        this->DestroyAllocationObject(NewObject);
        NewObject = 0x00;
        goto _ERROR_OUT;
    }
    NewObject->AllocationSize = Size;
    NewObject->AllocationAlignment = Alignment;
    NewObject->Address = SalAllocateMemory(Size, Alignment);
    if(!NewObject->Address){
        this->DestroyAllocationObject(NewObject);
        NewObject = 0x00;
        goto _ERROR_OUT;
    }
    ListAddTail(&NewObject->Peers, &this->SectionAllocations);
_ERROR_OUT:
    pthread_mutex_unlock(&this->SectionAllocationsLock);
    return NewObject;
}

void SalContextObjectManager::FreeSectionData(PSAL_ALLOCATION_OBJECT Object){
    if(!Object){
        return;
    }
    pthread_mutex_lock(&this->SectionAllocationsLock);
    SalFreeMemory(Object->Address);
    this->ReAllocateSectionSpace(Object, 0, 0);
    this->DestroyAllocationObject(Object);
    pthread_mutex_unlock(&this->SectionAllocationsLock);
}

PVOID SalContextObjectManager::GetSectionDataAddress(PSAL_ALLOCATION_OBJECT Object){
    return Object->Address;
}

SIZE SalContextObjectManager::GetSectionDataOffset(PSAL_ALLOCATION_OBJECT Object){
    return Object->AllocationBase;
}

SAL_STATUS SalContextObjectManager::DefineSectionData(PSAL_ALLOCATION_OBJECT* Out, SIZE Offset, SIZE Size, SIZE Alignment){
    if((!Out) || (!Size) || (!Alignment)){
        return STATUS_INVALID_PARAMETER;
    }
    *Out = 0x00;
    PSAL_ALLOCATION_OBJECT TmpObject;
    SAL_STATUS Status = STATUS_SUCCESS;
    PSAL_ALLOCATION_OBJECT NewObject;
    pthread_mutex_lock(&this->SectionAllocationsLock);
    ForEachListEntry(TmpObject, &this->SectionAllocations, Peers){
        if(RangeInterferes(Offset, Size, TmpObject->AllocationBase, TmpObject->AllocationSize)){
            Status = STATUS_ALLOCATION_COLISION;
            goto _ERROR_OUT;
        }
    }
    NewObject = this->CreateAllocationObject();
    if(!NewObject){
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _ERROR_OUT;
    }
    NewObject->Address = SalAllocateMemory(Size, Alignment);
    if(!NewObject->Address){
        this->DestroyAllocationObject(NewObject);
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _ERROR_OUT;
    }
    NewObject->AllocationBase = Offset;
    NewObject->AllocationSize = Size;
    NewObject->AllocationAlignment = Alignment;
    ListAddTail(&NewObject->Peers, &this->SectionAllocations);
    *Out = NewObject;
_ERROR_OUT:
    pthread_mutex_unlock(&this->SectionAllocationsLock);
    return Status;    
}

SAL_STATUS SalContextObjectManager::ReAllocateSectionData(PSAL_ALLOCATION_OBJECT Object, SIZE Size, SIZE Alignment){
    if((!Object) || ((Size) && (!Alignment))){
        return STATUS_INVALID_PARAMETER;
    }else if(!Size){
        this->FreeSectionData(Object);
        return STATUS_SUCCESS;
    }
    SAL_STATUS Status = STATUS_SUCCESS;
    pthread_mutex_lock(&this->SectionAllocationsLock);
    SIZE TmpBase = Object->AllocationBase;
    SIZE TmpSize = Object->AllocationSize;
    SIZE TmpAlginment = Object->AllocationAlignment;
    PVOID TmpAddress = Object->Address;
    SIZE CopySize;
    Object->Address = SalAllocateMemory(Size, Alignment);
    if(!Object->Address){
        Object->Address = TmpAddress;
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _ERROR_OUT;
    }
    Status = this->ReAllocateSectionSpace(Object, Size, Alignment);
    if(Status != STATUS_SUCCESS){
        Object->AllocationBase = TmpBase;
        Object->AllocationSize = TmpSize;
        Object->AllocationAlignment = TmpAlginment;
        SalFreeMemory(Object->Address);
        Object->Address = TmpAddress;
        ListAddTail(&Object->Peers, &this->SectionAllocations);
        goto _ERROR_OUT;
    }
    CopySize = MIN(TmpSize, Size);
    memcpy(Object->Address, TmpAddress, CopySize);
    SalFreeMemory(TmpAddress);
_ERROR_OUT:
    pthread_mutex_unlock(&this->SectionAllocationsLock);
    return Status;
}

SAL_STATUS SalContextObjectManager::FinalizeSection(SIZE SectionSize){
    if(!SectionSize){
        return STATUS_INVALID_PARAMETER;
    }
    SAL_STATUS Status = STATUS_SUCCESS;
    PSAL_ALLOCATION_OBJECT TmpObject;
    SIZE LastSectionAddress = SectionSize;
    SIZE TmpSize;
    pthread_mutex_lock(&this->SectionAllocationsLock);
    ForEachListEntry(TmpObject, &this->SectionAllocations, Peers){
        TmpSize = ROUND_UP64(TmpObject->AllocationBase + TmpObject->AllocationSize, SectionSize);
        if(TmpSize > LastSectionAddress){
            LastSectionAddress = TmpSize;
        }
    }
    if(this->FinalizedSection){
        SalFreeMemory(this->FinalizedSection);
        this->FinalizedSection = 0x00;
        this->FinalizedSectionSize = 0x00;
    }
    this->FinalizedSection = SalAllocateMemory(LastSectionAddress, SectionSize);
    if(!this->FinalizedSection){
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _ERROR_OUT;
    }
    this->FinalizedSectionSize = LastSectionAddress;

    ForEachListEntry(TmpObject, &this->SectionAllocations, Peers){
        memcpy(
            (PVOID)(((SIZE)(UINT8*)this->FinalizedSection) + ((SIZE)TmpObject->AllocationBase)), 
            TmpObject->Address,
            TmpObject->AllocationSize
        );
    }
_ERROR_OUT:
    pthread_mutex_unlock(&this->SectionAllocationsLock);
    return Status;
}

PVOID SalContextObjectManager::GetSectionAddressBase(){
    return this->FinalizedSection;
}
SIZE SalContextObjectManager::GetSectionOffsetBase(){
    return this->SectionOffsetBase;
}
SIZE SalContextObjectManager::GetSectionSize(){
    return this->FinalizedSectionSize;
}
