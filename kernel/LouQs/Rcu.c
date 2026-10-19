#define _RCU_INTERNALS
#include <LouAPI.h>

#define SRCU_READ_COPY_POINTER      0 
#define SRCU_WRITE_COPY_POINTER     1

KERNEL_EXPORT
LOUSTATUS 
LouKeCreateSrcuObject(
    PSRCU_OBJECT*   ObjectOut, 
    SIZE            ObjectSize, 
    SIZE            ObjectAlignment,
    UINT64          AllocationFlags
){
    if((!ObjectOut) || (!ObjectSize) || (!ObjectAlignment)){
        return STATUS_INVALID_PARAMETER;
    }
    PSRCU_OBJECT NewObject = LouKeMallocType(SRCU_OBJECT, KERNEL_GENERIC_MEMORY);
    if(!NewObject){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    
    NewObject->Items[SRCU_READ_COPY_POINTER] = LouKeMallocEx(ObjectSize, ObjectAlignment, AllocationFlags);
    if(!NewObject->Items[SRCU_READ_COPY_POINTER]){
        LouKeFree(NewObject);
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    NewObject->Items[SRCU_WRITE_COPY_POINTER] = LouKeMallocEx(ObjectSize, ObjectAlignment, AllocationFlags);
    if(!NewObject->Items[SRCU_WRITE_COPY_POINTER]){
        LouKeFree(NewObject->Items[SRCU_READ_COPY_POINTER]);
        LouKeFree(NewObject);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    NewObject->ItemSize = ObjectSize;

    *ObjectOut = NewObject;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
PVOID 
LouKeSrcuReadObjectAcquire(
    PSRCU_OBJECT SrcuObject
){
    MutexSynchronizeNoBlocking(&SrcuObject->ReadLock); //this function dosent block instead it yeilds if mutex is locked
    LouKeAtomicIncrement(&SrcuObject->Readers);
    return SrcuObject->Items[SRCU_READ_COPY_POINTER];
}

KERNEL_EXPORT
void 
LouKeSrcuReadObjectRelease(
    PSRCU_OBJECT SrcuObject
){
    LouKeAtomicDecrement(&SrcuObject->Readers);
}

KERNEL_EXPORT
PVOID 
LouKeSrcuWriteObjectAcquire(
    PSRCU_OBJECT SrcuObject
){
    MutexLock(&SrcuObject->WriteLock);
    return SrcuObject->Items[SRCU_WRITE_COPY_POINTER];
}

void LouKeSrcuWriteObjectRelease(PSRCU_OBJECT SrcuObject){
    MutexLock(&SrcuObject->ReadLock); //lock new readers
    while(LouKeGetAtomic(&SrcuObject->Readers)){ //wait for all Other readers to leave
        LouKeYieldExecution();
    } 
    memcpy(SrcuObject->Items[SRCU_READ_COPY_POINTER], SrcuObject->Items[SRCU_WRITE_COPY_POINTER], SrcuObject->ItemSize); //copy writer data to reader data
    //memory fences happen in the unlocks
    MutexUnlock(&SrcuObject->ReadLock);
    MutexUnlock(&SrcuObject->WriteLock);
}