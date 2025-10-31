#include "Coff.h"



static mutex_t LITMutex = {0}; 
static LOADED_IMAGE_TRACKER MasterTracker = {0};

static PCFI_OBJECT CreateLoadedImageEntry(
    string          LoadedObjectName
){
    PLOADED_IMAGE_TRACKER TmpTracker = &MasterTracker;
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PLOADED_IMAGE_TRACKER)TmpTracker->Peers.NextHeader;
    }
    TmpTracker->Peers.NextHeader = (PListHeader)LouKeMallocType(LOADED_IMAGE_TRACKER, KERNEL_GENERIC_MEMORY);
    TmpTracker = (PLOADED_IMAGE_TRACKER)TmpTracker->Peers.NextHeader;
    TmpTracker->LoadedObjectName = LoadedObjectName;
    LouKeAcquireReference(&TmpTracker->LoadedObject.Reference);
    return &TmpTracker->LoadedObject;
}

static PCFI_OBJECT LookForLoadedImageEntry(string ImageName){
    PLOADED_IMAGE_TRACKER TmpTracker = (PLOADED_IMAGE_TRACKER)MasterTracker.Peers.NextHeader;
    while(TmpTracker){
        if(!strcmp(TmpTracker->LoadedObjectName, ImageName)){
            return &TmpTracker->LoadedObject;
        }
        TmpTracker = (PLOADED_IMAGE_TRACKER)TmpTracker->Peers.NextHeader;
    }
    return 0x00;
}

static void DestroyLoadedImageEntry(PCFI_OBJECT Object){
    PLOADED_IMAGE_TRACKER TmpTracker = (PLOADED_IMAGE_TRACKER)MasterTracker.Peers.NextHeader;
    PLOADED_IMAGE_TRACKER Follower = &MasterTracker; 
    while(TmpTracker){
        if(&TmpTracker->LoadedObject == Object){
            Follower->Peers.NextHeader = TmpTracker->Peers.NextHeader;
            
            LouKeFree(TmpTracker);
        }
        Follower = TmpTracker;
        TmpTracker = (PLOADED_IMAGE_TRACKER)TmpTracker->Peers.NextHeader;
    }
}

LOUSTATUS
LouKeLoadCoffImageExA_ns(
    string          FileNameAndPath,
    PCFI_OBJECT     CfiObject
){
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
    if(memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)COFF_PE_SIGNATURE, sizeof(UINT32))){
        LouPrint("Error Loading Coff Image: File Is Not Coff Image\n");
        DestroyLoadedImageEntry(CfiObject);
        MutexUnlock(&LITMutex);
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

    return LoaderStatus;
}

LOUSTATUS
LouKeLoadCoffImageExA(
    string          FileNameAndPath,
    PCFI_OBJECT*    LoadedObjectCheck
){
    LOUSTATUS           LoaderStatus;
    PCFI_OBJECT         CfiObject;

    if((!LoadedObjectCheck) || (!FileNameAndPath)){
        return STATUS_INVALID_PARAMETER;
    }

    MutexLock(&LITMutex);

    *LoadedObjectCheck = LookForLoadedImageEntry(FileNameAndPath);

    if(*LoadedObjectCheck){
        LouPrint("Image Already Loaded\n");
        MutexUnlock(&LITMutex);
        MutexSynchronize(&(*LoadedObjectCheck)->LockOutTagOut);
        return STATUS_SUCCESS;
    }

    CfiObject = CreateLoadedImageEntry(FileNameAndPath);

    LoaderStatus = LouKeLoadCoffImageExA_ns(FileNameAndPath, CfiObject);
    
    //size_t ImageSize = CoffStdHeader->
    //LouPrint("Image Size Is:%h\n", ImageSize);

    if(LoaderStatus == STATUS_SUCCESS){
        *LoadedObjectCheck = CfiObject;
    }else{
        *LoadedObjectCheck = 0x00;
        DestroyLoadedImageEntry(CfiObject);
    }
    fclose(CfiObject->CoffFile);
    MutexUnlock(&LITMutex);
    return LoaderStatus;
}


LOUSTATUS 
LouKeLoadCoffImageA(
    string          Path,
    string          FileName,      
    PCFI_OBJECT*    CfiObject
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
    return LouKeLoadCoffImageExA(FullPath, CfiObject);
}
