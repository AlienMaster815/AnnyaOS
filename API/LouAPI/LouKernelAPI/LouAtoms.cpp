//Copyright GPL-2 Tyler Grenier (2024 - 2026)
#include <LouDDK.h>

KERNEL_EXPORT LONG LouKeRtlCompareUtf16StringSafe(LPWSTR String1, LPWSTR String2, BOOLEAN CaseInSensitive, SIZE Length);

typedef struct _ATOM_MANAGER{
    mutex_t     ManagerLock;
    ListHeader  Atoms;
    XARRAY      GlobalTable;
}ATOM_MANAGER, * PATOM_MANAGER;

typedef struct _ATOM_TRACKER{
    ListHeader          Peers;
    UINT64              AtomID;    
    LPWSTR              AtomName;
    KERNEL_REFERENCE    Reference;
    ULONG               NameLength;
    BOOLEAN             LocalAtom;
    XARRAY              LocalTable;
}ATOM_TRACKER, * PATOM_TRACKER;

static ATOM_MANAGER LousineAtomManager = {0}; 

static LOUSTATUS GetAtomTracker(
    LPWSTR          AtomName,
    ULONG           NameLength,
    BOOLEAN         Local, 
    PRTL_ATOM       OutAtom,
    ULONG           Process
){
    if(!AtomName || !NameLength){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status;
    PATOM_TRACKER TmpTracker;
    ForEachListEntry(TmpTracker, &LousineAtomManager.Atoms, Peers){
        if(TmpTracker->LocalAtom == Local){
            if(Local){
                UINT64 Out;
                Status = LouKeXaGet(&TmpTracker->LocalTable, Process, &Out);
                if(Status != STATUS_SUCCESS){
                    continue;
                }
                PATOM_TRACKER ProcessTracker = (PATOM_TRACKER)Out;
                if((ProcessTracker->NameLength == NameLength) && (!LouKeRtlCompareUtf16StringSafe(AtomName, ProcessTracker->AtomName, true, NameLength))){
                    LouKeAcquireReference(&TmpTracker->Reference);
                    LouKeAcquireReference(&ProcessTracker->Reference);
                    *OutAtom = (RTL_ATOM)TmpTracker->AtomID;
                    return STATUS_SUCCESS;
                }
            }else{
                if((TmpTracker->NameLength == NameLength) && (!LouKeRtlCompareUtf16StringSafe(AtomName, TmpTracker->AtomName, true, NameLength))){
                    LouKeAcquireReference(&TmpTracker->Reference);
                    *OutAtom = (RTL_ATOM)TmpTracker->AtomID;
                    return STATUS_SUCCESS;
                }
            }      
        }
    }

    return STATUS_NO_SUCH_FILE;
}

static LOUSTATUS AllocateGlobalAtom(
    LPWSTR      AtomName,
    ULONG       NameLength,
    PRTL_ATOM   OutAtom
){
    MutexLock(&LousineAtomManager.ManagerLock);
    LOUSTATUS Status;

    Status = GetAtomTracker(AtomName, NameLength, false, OutAtom, 0);
    if((Status == STATUS_SUCCESS) || (Status == STATUS_INVALID_PARAMETER)){
        MutexUnlock(&LousineAtomManager.ManagerLock);
        return Status;
    }


    PATOM_TRACKER NewTracker = LouKeMallocType(ATOM_TRACKER, KERNEL_GENERIC_MEMORY);
    NewTracker->NameLength = NameLength;
    NewTracker->AtomName = LouKeMallocArray(WCHAR, NameLength + 1, KERNEL_GENERIC_MEMORY);
    wcsncpy(NewTracker->AtomName, AtomName, NameLength);
    NewTracker->LocalAtom = false;
    NewTracker->AtomID = 1;

    Status = LouKeXarrayAllocateUint64(
        &LousineAtomManager.GlobalTable,
        &NewTracker->AtomID,
        NewTracker,
        0xFFFF,
        KERNEL_GENERIC_MEMORY
    );
    if(Status != STATUS_SUCCESS){
        MutexUnlock(&LousineAtomManager.ManagerLock);
        LouKeFree(NewTracker);
        return Status;
    }
    LouKeAcquireReference(&NewTracker->Reference);
    LouKeListAddTail(&NewTracker->Peers, &LousineAtomManager.Atoms);

    *OutAtom = (RTL_ATOM)NewTracker->AtomID;

    MutexUnlock(&LousineAtomManager.ManagerLock);
    return STATUS_SUCCESS;
}

static LOUSTATUS AllocateLocalGlobalAtomTracker(
    PATOM_TRACKER*  TrackerOut,
    LPWSTR          AtomName,
    ULONG           NameLength,
    ULONG           Process
){
    if(!AtomName || !NameLength){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status;
    PATOM_TRACKER TmpTracker;
    ForEachListEntry(TmpTracker, &LousineAtomManager.Atoms, Peers){
        if(TmpTracker->LocalAtom == true){
            UINT64 Out = 0;
            Status = LouKeXaGet(&TmpTracker->LocalTable, Process, &Out);
            if(Status == STATUS_SUCCESS){
                continue;
            }   
            *TrackerOut = TmpTracker;
            LouKeAcquireReference(&TmpTracker->Reference);
            return STATUS_SUCCESS;
        }
    }

    TmpTracker = LouKeMallocType(ATOM_TRACKER, KERNEL_GENERIC_MEMORY);
    TmpTracker->LocalAtom = true;
    TmpTracker->AtomID = 1;
    
    Status = LouKeXarrayAllocateUint64(
        &LousineAtomManager.GlobalTable,
        &TmpTracker->AtomID,
        TmpTracker,
        0xFFFF,
        KERNEL_GENERIC_MEMORY
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    LouKeAcquireReference(&TmpTracker->Reference);
    LouKeListAddTail(&TmpTracker->Peers, &LousineAtomManager.Atoms);
    *TrackerOut = TmpTracker;
    return STATUS_SUCCESS;
}

static LOUSTATUS AllocateLocalAtom(
    LPWSTR      AtomName,
    ULONG       NameLength,
    PRTL_ATOM   OutAtom,
    ULONG       Process
){
    MutexLock(&LousineAtomManager.ManagerLock);
    LOUSTATUS Status = GetAtomTracker(AtomName, NameLength, true, OutAtom, Process);
    if((Status == STATUS_SUCCESS) || (Status == STATUS_INVALID_PARAMETER)){
        MutexUnlock(&LousineAtomManager.ManagerLock);
        return Status;
    }

    PATOM_TRACKER GlobalTracker = 0x00; 
    Status = AllocateLocalGlobalAtomTracker(
        &GlobalTracker,
        AtomName, 
        NameLength,
        Process
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("AllocateLocalAtom::SERIOUS_ERROR\n");
        LouKeDebugTrap(); //this is a BSOD not recoverable and probably points to a stack corruption or vm corruption
    }

    PATOM_TRACKER LocalTracker = LouKeMallocType(ATOM_TRACKER, KERNEL_GENERIC_MEMORY);
    LouKeAcquireReference(&LocalTracker->Reference);
    LocalTracker->NameLength = NameLength;
    LocalTracker->AtomName = LouKeMallocArray(WCHAR, NameLength + 1, KERNEL_GENERIC_MEMORY);
    wcsncpy(LocalTracker->AtomName, AtomName, NameLength);    

    *OutAtom = (RTL_ATOM)GlobalTracker->AtomID; 
    LouKeXaStore(&GlobalTracker->LocalTable, Process, LocalTracker, KERNEL_GENERIC_MEMORY);
    MutexUnlock(&LousineAtomManager.ManagerLock);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeAddAtomEx(
    LPWSTR      AtomName,
    ULONG       NameLength,
    PRTL_ATOM   OutAtom,
    UINT64      Flags
){
    if(!AtomName || !NameLength || !OutAtom){
        return STATUS_INVALID_PARAMETER;
    }

    LOUSTATUS Status;

    if(Flags & ADD_ATOM_FLAG_LOCAL){
        Status = AllocateLocalAtom(
            AtomName,
            NameLength,
            OutAtom,
            LouKeGetProcessIdentification()
        );
        if(Status != STATUS_SUCCESS){
            return Status;
        }
    }else{
        Status = AllocateGlobalAtom(
            AtomName,
            NameLength,
            OutAtom
        );
        if(Status != STATUS_SUCCESS){
            return Status;
        }
    }
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeAddAtom(
    LPWSTR      AtomName,
    ULONG       Length,
    PRTL_ATOM   Atom
){
    return LouKeAddAtomEx(AtomName, Length, Atom, 0);
}

KERNEL_EXPORT
LOUSTATUS
LouKeDeleteAtom(
    RTL_ATOM    Atom
){
    if(!Atom){
        return STATUS_INVALID_PARAMETER;
    }
    UINT64 Out;
    PATOM_TRACKER GlobalTracker = 0; 
    PATOM_TRACKER LocalTracker = 0; 
    ULONG ProcessID;

    MutexLock(&LousineAtomManager.ManagerLock);
    LOUSTATUS Status = LouKeXaGet(&LousineAtomManager.GlobalTable, Atom, &Out);
    if(Status != STATUS_SUCCESS){
        MutexUnlock(&LousineAtomManager.ManagerLock);
        return Status;
    }
    GlobalTracker = (PATOM_TRACKER)Out;
    if(!GlobalTracker->LocalAtom){
        goto _CHECK_FREE_GLOBAL;
    }
    ProcessID = LouKeGetProcessIdentification();
    Status = LouKeXaGet(&GlobalTracker->LocalTable, ProcessID, &Out);
    if(Status != STATUS_SUCCESS){
        MutexUnlock(&LousineAtomManager.ManagerLock);
        return Status;
    }
    LocalTracker = (PATOM_TRACKER)Out;
    LouKeReleaseReference(&LocalTracker->Reference);
    if(!LouKeGetReferenceCount(&LocalTracker->Reference)){
        LouKeXaFreeUint64(&GlobalTracker->LocalTable, ProcessID);
        LouKeFree(LocalTracker->AtomName);
        LouKeFree(LocalTracker);
    }
_CHECK_FREE_GLOBAL:
    LouKeReleaseReference(&GlobalTracker->Reference);
    if(!LouKeGetReferenceCount(&GlobalTracker->Reference)){
        LouKeListDeleteItem(&GlobalTracker->Peers);
        LouKeXaFreeUint64(&LousineAtomManager.GlobalTable, Atom);
        if(GlobalTracker->AtomName)LouKeFree(GlobalTracker->AtomName);
        LouKeFree(GlobalTracker);
    }  

    MutexUnlock(&LousineAtomManager.ManagerLock);
    return STATUS_SUCCESS;
}