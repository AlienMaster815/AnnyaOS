#include <LouAPI.h>

DllModuleEntry LoadUserDllModule(uintptr_t Start, string ExecutablePath);

DllModuleEntry LouKeLoadUserModule(string ModuleNameAndPath){
    FILE* ModuleHandle = fopen(ModuleNameAndPath);

    if(!ModuleHandle){
        return 0x00;
    }
    return LoadUserDllModule((uintptr_t)ModuleHandle, ModuleNameAndPath); 
}


typedef struct _DRIVER_MODULE_HANDLES{
    ListHeader          Neighbors;
    string              Paths;
    DRIVER_MODULE_ENTRY ModuleEntry;
    void* DriverObject;
}DRIVER_MODULE_HANDLES, * PDRIVER_MODULE_HANDLES;

static DRIVER_MODULE_HANDLES DriverHandles = {0};
static size_t DriveHandlesCount = 0;

PHANDLE LoadKernelModule(uintptr_t Start, string ExecutablePath);

DRIVER_MODULE_ENTRY LouKeLoadKernelModule(string ModuleNameAndPath, void** DriverObject, size_t DriverObjectSize){
    PDRIVER_MODULE_HANDLES TmpHandle = &DriverHandles;
    
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
            TmpHandle->Neighbors.NextHeader = (PListHeader)LouMalloc(sizeof(DRIVER_MODULE_HANDLES));
            TmpHandle = (PDRIVER_MODULE_HANDLES)TmpHandle->Neighbors.NextHeader;
        }
    }

    DRIVER_MODULE_ENTRY Entry;
    FILE* ModuleHandle = fopen(ModuleNameAndPath);
    if(!ModuleHandle){
        return 0x00;
    }

    TmpHandle->Paths = ModuleNameAndPath;
    Entry = (DRIVER_MODULE_ENTRY)LoadKernelModule((uintptr_t)ModuleHandle, ModuleNameAndPath);
    TmpHandle->ModuleEntry = Entry;
    TmpHandle->DriverObject = LouMalloc(DriverObjectSize);
    *DriverObject = TmpHandle->DriverObject;
    DriveHandlesCount++;
    return (DRIVER_MODULE_ENTRY)Entry;
}

