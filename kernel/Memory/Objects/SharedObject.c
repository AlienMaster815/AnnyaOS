#include <LouAPI.h>

static mutex_t GlobalPointerManagerLock = {0}; 
static XARRAY GlobalPointerManager = {0};

LOUSTATUS 
LouKeUnRegisterSharedObject(
    LPWSTR ObjectName
){
    if(!ObjectName){
        return STATUS_INVALID_PARAMETER;
    }
    MutexLock(&GlobalPointerManagerLock);
    RTL_ATOM Atom;
    LOUSTATUS Status = LouKeAddAtom(ObjectName, wcslen(ObjectName), &Atom);
    if(Status != STATUS_SUCCESS){
        MutexUnlock(&GlobalPointerManagerLock);
        return Status;
    }

    if(LouKeXaIsIndexUsed(&GlobalPointerManager, Atom)){
        //free the Track
        LouKeXaFreeUint64(&GlobalPointerManager, Atom);
        //Free The Tracking Reference
        LouKeDeleteAtom(Atom);
        Status = STATUS_SUCCESS;
    }else {
        Status = STATUS_UNSUCCESSFUL;
    }
    LouKeDeleteAtom(Atom); //add atom creates a second reference so delete again to delete the atom from the table
    MutexUnlock(&GlobalPointerManagerLock);
    return Status;        
}

LOUSTATUS
LouKeRegisterSharedObjectEx(
    LPWSTR      ObjectName,
    PVOID       Object,
    PRTL_ATOM   OutAtom
){
    if(!ObjectName || !Object){
        return STATUS_INVALID_PARAMETER;
    }

    MutexLock(&GlobalPointerManagerLock);
    RTL_ATOM Atom;
    LOUSTATUS Status = LouKeAddAtom(ObjectName, wcslen(ObjectName), &Atom);
    if(Status != STATUS_SUCCESS){
        MutexUnlock(&GlobalPointerManagerLock);
        return Status;
    }


    //check if there is already a tracker
    if(LouKeXaIsIndexUsed(&GlobalPointerManager, Atom)){
        //delete Atom Reference and Return error
        LouKeDeleteAtom(Atom);
        MutexUnlock(&GlobalPointerManagerLock);
        return STATUS_INVALID_PARAMETER;
    }
    LouKeXaStore(&GlobalPointerManager, Atom, Object, KERNEL_GENERIC_MEMORY);
    if(OutAtom){
        *OutAtom = Atom;
    }
    MutexUnlock(&GlobalPointerManagerLock);
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeRegisterSharedObject(
    LPWSTR  ObjectName,
    PVOID   Object
){
   return LouKeRegisterSharedObjectEx(ObjectName, Object, 0);
}

LOUSTATUS LouKeGetSharedObjectFromAtom(
    RTL_ATOM    Atom,
    PVOID*      OutPtr
){
    if(!Atom || !OutPtr){
        return STATUS_INVALID_PARAMETER;
    }
    MutexLock(&GlobalPointerManagerLock);
    if(!LouKeXaIsIndexUsed(&GlobalPointerManager, Atom)){
        //delete Atom Reference and Return error
        LouKeDeleteAtom(Atom);
        MutexUnlock(&GlobalPointerManagerLock);
        return STATUS_INVALID_PARAMETER;
    }
    UINT64 Out;
    LOUSTATUS Status = LouKeXaGet(&GlobalPointerManager, Atom, &Out);
    if(Status != STATUS_SUCCESS){
        LouKeDeleteAtom(Atom);
        MutexUnlock(&GlobalPointerManagerLock);
        return Status;
    }
    *OutPtr = (PVOID)Out;
    MutexUnlock(&GlobalPointerManagerLock);
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeGetSharedObjectEx(
    LPWSTR      ObjectName,
    PVOID*      OutPtr,
    PRTL_ATOM   OutAtom
){
    if(!ObjectName || !OutPtr){
        return STATUS_INVALID_PARAMETER;
    }
    MutexLock(&GlobalPointerManagerLock);
    RTL_ATOM Atom;
    LOUSTATUS Status = LouKeAddAtom(ObjectName, wcslen(ObjectName), &Atom);
    if(Status != STATUS_SUCCESS){
        MutexUnlock(&GlobalPointerManagerLock);
        return Status;
    }
    
    //check existence
    if(!LouKeXaIsIndexUsed(&GlobalPointerManager, Atom)){
        //delete Atom Reference and Return error
        LouKeDeleteAtom(Atom);
        MutexUnlock(&GlobalPointerManagerLock);
        return STATUS_INVALID_PARAMETER;
    }

    UINT64 Out;
    Status = LouKeXaGet(&GlobalPointerManager, Atom, &Out);
    if(Status != STATUS_SUCCESS){
        LouKeDeleteAtom(Atom);
        MutexUnlock(&GlobalPointerManagerLock);
        return Status;
    }
    *OutPtr = (PVOID)Out;
    if(OutAtom){
        *OutAtom = Atom;
    }
    MutexUnlock(&GlobalPointerManagerLock);
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeGetSharedObject(
    LPWSTR  ObjectName,
    PVOID*  OutPtr
){
    return LouKeGetSharedObjectEx(ObjectName, OutPtr, 0x00);  
}