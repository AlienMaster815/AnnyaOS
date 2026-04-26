#include <LouAPI.h>

typedef struct _DRIVER_MODULE_HANDLES{
    ListHeader          Neighbors;
    string              Paths;
    DRIVER_MODULE_ENTRY ModuleEntry;
    CFI_OBJECT          CfiObject;
    void*               DriverObject;
}DRIVER_MODULE_HANDLES, * PDRIVER_MODULE_HANDLES;

static DRIVER_MODULE_HANDLES DriverHandles = {0};
static size_t DriveHandlesCount = 0;

DRIVER_MODULE_ENTRY LouKeLoadKernelModule(string ModuleNameAndPath, void** DriverObject, size_t DriverObjectSize){ //TODO
    PDRIVER_MODULE_HANDLES TmpHandle = &DriverHandles;
    LOUSTATUS Status;
    for(size_t i = 0 ; i < DriveHandlesCount; i++){
        if(TmpHandle->Paths){
            if(strcmp(ModuleNameAndPath, TmpHandle->Paths) == 0){
                DriverObject = TmpHandle->DriverObject;
                return TmpHandle->ModuleEntry;
            }
        }
        if(TmpHandle->Neighbors.NextHeader){
            TmpHandle = (PDRIVER_MODULE_HANDLES)TmpHandle->Neighbors.NextHeader;
        }else{
            TmpHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocType(DRIVER_MODULE_HANDLES,  KERNEL_GENERIC_MEMORY);
            TmpHandle = (PDRIVER_MODULE_HANDLES)TmpHandle->Neighbors.NextHeader;
        }
    }

    string NewMod = (string)LouKeMallocArray(char, strlen(ModuleNameAndPath) + 1, KERNEL_GENERIC_MEMORY);
    strncpy(NewMod, ModuleNameAndPath, strlen(ModuleNameAndPath));

    Status = LouKeLoadCoffImageExA(NewMod, &TmpHandle->CfiObject, true);
    if(Status != STATUS_SUCCESS){
        LouKeFree(NewMod);
        return 0x00;
    }

    TmpHandle->Paths = NewMod;
    TmpHandle->ModuleEntry = TmpHandle->CfiObject.Entry;
    TmpHandle->DriverObject = LouKeMalloc(DriverObjectSize, WRITEABLE_PAGE | PRESENT_PAGE);
    *DriverObject = TmpHandle->DriverObject;
    DriveHandlesCount++;
    return (DRIVER_MODULE_ENTRY)TmpHandle->CfiObject.Entry;
}


DRIVER_MODULE_ENTRY LouKeLoadBootKernelModule(uintptr_t Base, void** DriverObject, size_t DriverObjectSize){
    if(!Base){
        return 0x00;
    }

    PDRIVER_MODULE_HANDLES TmpHandle = &DriverHandles;
    
    for(size_t i = 0 ; i < DriveHandlesCount; i++){
        if(TmpHandle->Paths){
            if(TmpHandle->Paths == (string)Base){
                DriverObject = TmpHandle->DriverObject;
                return TmpHandle->ModuleEntry;
            }
        }
        if(TmpHandle->Neighbors.NextHeader){
            TmpHandle = (PDRIVER_MODULE_HANDLES)TmpHandle->Neighbors.NextHeader;
        }else{
            TmpHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocType(DRIVER_MODULE_HANDLES,  KERNEL_GENERIC_MEMORY);
            TmpHandle = (PDRIVER_MODULE_HANDLES)TmpHandle->Neighbors.NextHeader;
        }
    }
    
    DRIVER_MODULE_ENTRY Entry;
    TmpHandle->Paths = (string)Base;
    LouKeLoadCoffImageBNs((PVOID)Base, &TmpHandle->CfiObject, true);
    Entry = (DRIVER_MODULE_ENTRY)TmpHandle->CfiObject.Entry;
    TmpHandle->ModuleEntry = Entry;
    if(DriverObject && DriverObjectSize){
        TmpHandle->DriverObject = LouKeMalloc(DriverObjectSize, WRITEABLE_PAGE | PRESENT_PAGE);
        *DriverObject = TmpHandle->DriverObject;
    }else if(DriverObject){
        *DriverObject = 0x00;
    }
    DriveHandlesCount++;
    return (DRIVER_MODULE_ENTRY)Entry;
}

HANDLE LouKeLoadLibraryA(string LibraryName){
    LouPrint("LouKeLoadLibraryA()\n");
    while(1);
}