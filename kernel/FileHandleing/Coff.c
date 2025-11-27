#include "Coff.h"



static mutex_t LITMutex = {0}; 
static LOADED_IMAGE_TRACKER MasterTracker = {0};

static void CreateLoadedImageEntry(
    PCFI_OBJECT CfiObject
){
    PLOADED_IMAGE_TRACKER TmpTracker = &MasterTracker;
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PLOADED_IMAGE_TRACKER)TmpTracker->Peers.NextHeader;
    }
    TmpTracker->Peers.NextHeader = (PListHeader)LouKeMallocType(LOADED_IMAGE_TRACKER, KERNEL_GENERIC_MEMORY);
    TmpTracker = (PLOADED_IMAGE_TRACKER)TmpTracker->Peers.NextHeader;
    TmpTracker->LoadedObject = CfiObject;
    LouKeAcquireReference(&TmpTracker->LoadedObject->Reference);
}

static bool LookForLoadedImageEntry(PCFI_OBJECT Object){
    PLOADED_IMAGE_TRACKER TmpTracker = (PLOADED_IMAGE_TRACKER)MasterTracker.Peers.NextHeader;
    while(TmpTracker){
        if((UINT64)TmpTracker->LoadedObject == (UINT64)Object){
            return true;
        }
        TmpTracker = (PLOADED_IMAGE_TRACKER)TmpTracker->Peers.NextHeader;
    }
    return false;
}

static void DestroyLoadedImageEntry(PCFI_OBJECT Object){
    PLOADED_IMAGE_TRACKER TmpTracker = (PLOADED_IMAGE_TRACKER)MasterTracker.Peers.NextHeader;
    PLOADED_IMAGE_TRACKER Follower = &MasterTracker; 
    while(TmpTracker){
        if(TmpTracker->LoadedObject == Object){
            Follower->Peers.NextHeader = TmpTracker->Peers.NextHeader;
            
            LouKeFree(TmpTracker);
        }
        Follower = TmpTracker;
        TmpTracker = (PLOADED_IMAGE_TRACKER)TmpTracker->Peers.NextHeader;
    }
}

LOUSTATUS 
LouKeLoadCoffImageB(
    PVOID           Base,
    PCFI_OBJECT     CfiObject,
    BOOL            KernelObject
){
    LOUSTATUS           LoaderStatus;
    PCOFF_IMAGE_HEADER  CoffStdHeader;
    bool LouCoff = false;

    if((!Base) || (!CfiObject)){
        return STATUS_INVALID_PARAMETER;
    }

    MutexLock(&LITMutex);

    bool Loaded = LookForLoadedImageEntry(CfiObject);

    if(Loaded){
        LouPrint("Image Already Loaded\n");
        MutexUnlock(&LITMutex);
        MutexSynchronize(&CfiObject->LockOutTagOut);
        return STATUS_SUCCESS;
    }

    CreateLoadedImageEntry(CfiObject);

    CfiObject->CoffFile = (FILE*)Base;

    CoffStdHeader = CoffGetImageHeader((UINT8*)CfiObject->CoffFile);
    if(
        (memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)COFF_PE_SIGNATURE, sizeof(UINT32))) &&
        (memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)CFI_HEADER_LOUCOFF_SIGNATURE, sizeof(UINT32)))
    ){

        LouPrint("Error Loading Coff Image: File Is Not Coff Image:%s\n", (PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature);
        DestroyLoadedImageEntry(CfiObject);
        MutexUnlock(&LITMutex);
        while(1);
        return STATUS_INVALID_PARAMETER;
    }

    if(memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)CFI_HEADER_LOUCOFF_SIGNATURE, sizeof(UINT32))){
        LouCoff = true;
    }
    
    
    if( //TODO: Add EFI Byte Code
        (CoffStdHeader->StandardHeader.MachineType != CFI_MACHINE_TYPE_AMD64) &&
        (CoffStdHeader->StandardHeader.MachineType != CFI_MACHINE_TYPE_I386) 
    ){
        LouPrint("Error Loading Coff Image: Image Is Not Compatible With This Machine\n");
        DestroyLoadedImageEntry(CfiObject);
        MutexUnlock(&LITMutex);
        return STATUS_INVALID_PARAMETER;
    }
    
    CfiObject->AOA64 = (CoffStdHeader->OptionalHeader.PE64.Magic == CFI_OPTIONAL_HEADER_PE3264_MAGIC) ? 0 : 1;
    if(LouCoff){
        if(CfiObject->AOA64){
            KernelObject = (CoffStdHeader->OptionalHeader.PE32.Subsystem == CFI_SUBSYSTEM_LOUSINE_KERNEL_OBJECT); 

        }else{
            KernelObject = (CoffStdHeader->OptionalHeader.PE64.Subsystem == CFI_SUBSYSTEM_LOUSINE_KERNEL_OBJECT); 
        }
    }
 
    CfiObject->KernelObject = KernelObject;

    if((CoffStdHeader->OptionalHeader.PE64.Magic != CFI_OPTIONAL_HEADER_PE32_MAGIC) && CfiObject->AOA64){
        LouPrint("Error Loading Coff Image: Could Not Find Compatible Low Level Loader\n");
        DestroyLoadedImageEntry(CfiObject);
        MutexUnlock(&LITMutex);
        return STATUS_INVALID_PARAMETER;
    }

    CfiObject->ImageHeader = CoffStdHeader;

    if(!CfiObject->AOA64){
        LoaderStatus = LouKeLoadCoffImageA64(CfiObject);
    }else {
        LoaderStatus = LouKeLoadCoffImageA32(CfiObject);
    }

    //TODO: add KULA Parser

    if(LoaderStatus != STATUS_SUCCESS){
        DestroyLoadedImageEntry(CfiObject);
    }
    MutexUnlock(&LITMutex);
    return LoaderStatus;
}

LOUSTATUS
LouKeLoadCoffImageExA_ns(
    string          FileNameAndPath,
    PCFI_OBJECT     CfiObject,
    BOOL            KernelObject
){
    bool LouCoff = false;
    LOUSTATUS LoaderStatus;
    PCOFF_IMAGE_HEADER  CoffStdHeader;

    CfiObject->CoffFile = fopen(FileNameAndPath, KERNEL_GENERIC_MEMORY);

    if(!CfiObject->CoffFile){
        LouPrint("Error Loading Coff Image: Image Does Not Exist\n");
        DestroyLoadedImageEntry(CfiObject);
        MutexUnlock(&LITMutex);
        return STATUS_NO_SUCH_FILE;
    }


    CoffStdHeader = CoffGetImageHeader((UINT8*)CfiObject->CoffFile);
    if(
        (memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)COFF_PE_SIGNATURE, sizeof(UINT32))) &&
        (memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)CFI_HEADER_LOUCOFF_SIGNATURE, sizeof(UINT32)))
    ){

        LouPrint("Error Loading Coff Image: File Is Not Coff Image:%s\n", (PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature);
        DestroyLoadedImageEntry(CfiObject);
        MutexUnlock(&LITMutex);
        while(1);
        return STATUS_INVALID_PARAMETER;
    }

    if( //TODO: Add EFI Byte Code
        (CoffStdHeader->StandardHeader.MachineType != CFI_MACHINE_TYPE_AMD64) &&
        (CoffStdHeader->StandardHeader.MachineType != CFI_MACHINE_TYPE_I386) 
    ){
        LouPrint("Error Loading Coff Image: Image Is Not Compatible With This Machine\n");
        DestroyLoadedImageEntry(CfiObject);
        MutexUnlock(&LITMutex);
        return STATUS_INVALID_PARAMETER;
    }

    CfiObject->AOA64 = (CoffStdHeader->OptionalHeader.PE64.Magic == CFI_OPTIONAL_HEADER_PE3264_MAGIC) ? 0 : 1;
    if(LouCoff){
        if(CfiObject->AOA64){
            KernelObject = (CoffStdHeader->OptionalHeader.PE32.Subsystem == CFI_SUBSYSTEM_LOUSINE_KERNEL_OBJECT); 

        }else{
            KernelObject = (CoffStdHeader->OptionalHeader.PE64.Subsystem == CFI_SUBSYSTEM_LOUSINE_KERNEL_OBJECT); 
        }
    }
    CfiObject->KernelObject = KernelObject;

    if((CoffStdHeader->OptionalHeader.PE64.Magic != CFI_OPTIONAL_HEADER_PE32_MAGIC) && CfiObject->AOA64){
        LouPrint("Error Loading Coff Image: Could Not Find Compatible Low Level Loader\n");
        DestroyLoadedImageEntry(CfiObject);
        MutexUnlock(&LITMutex);
        return STATUS_INVALID_PARAMETER;
    }

    CfiObject->ImageHeader = CoffStdHeader;

    if(!CfiObject->AOA64){
        LoaderStatus = LouKeLoadCoffImageA64(CfiObject);
    }else {
        LoaderStatus = LouKeLoadCoffImageA32(CfiObject);
    }

    //todo add kula parser

    return LoaderStatus;
}

LOUSTATUS
LouKeLoadCoffImageExA(
    string          FileNameAndPath,
    PCFI_OBJECT     CfiObject,
    BOOL            KernelObject
){
    LOUSTATUS           LoaderStatus;

    if(!FileNameAndPath){
        return STATUS_INVALID_PARAMETER;
    }

    MutexLock(&LITMutex);

    bool Loaded = LookForLoadedImageEntry(CfiObject);

    if(Loaded){
        LouPrint("Image Already Loaded\n");
        MutexUnlock(&LITMutex);
        MutexSynchronize(&CfiObject->LockOutTagOut);
        return STATUS_SUCCESS;
    }

    CreateLoadedImageEntry(CfiObject);

    LoaderStatus = LouKeLoadCoffImageExA_ns(FileNameAndPath, CfiObject, KernelObject);
    
    //size_t ImageSize = CoffStdHeader->
    //LouPrint("Image Size Is:%h\n", ImageSize);

    fclose(CfiObject->CoffFile);
    MutexUnlock(&LITMutex);
    return LoaderStatus;
}


LOUSTATUS 
LouKeLoadCoffImageA(
    string          Path,
    string          FileName,      
    PCFI_OBJECT     CfiObject,
    BOOL            KernelObject
){
    string FullPath = 0x00;
    if(!FileName){
        return STATUS_INVALID_PARAMETER;
    }

    if(Path){
        FullPath = LouKeAddFileToPath(Path, FileName);        

    }else{
        LouPrint("LouKeLoadCoffImageA64() ERROR No Path\n");
        while(1);
    }
    return LouKeLoadCoffImageExA(FullPath, CfiObject, KernelObject);
}
