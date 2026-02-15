#include <LouAPI.h>

DllModuleEntry LoadUserDllModule(uintptr_t Start, string ExecutablePath);

DllModuleEntry LouKeLoadUserModule(string ModuleNameAndPath, uintptr_t* BaseOfImage){

    FILE* ModuleHandle = fopen(ModuleNameAndPath, KERNEL_GENERIC_MEMORY);
    
    
    if(!ModuleHandle){
        LouPrint("Could Not Load Module:%s\n", ModuleNameAndPath);
        while(1);
        return 0x00;
    }

    return LoadUserDllModule((uintptr_t)ModuleHandle, ModuleNameAndPath); 
}


typedef struct _DRIVER_MODULE_HANDLES{
    ListHeader          Neighbors;
    string              Paths;
    DRIVER_MODULE_ENTRY ModuleEntry;
    CFI_OBJECT          CfiObject;
    void*               DriverObject;
}DRIVER_MODULE_HANDLES, * PDRIVER_MODULE_HANDLES;

static DRIVER_MODULE_HANDLES DriverHandles = {0};
static size_t DriveHandlesCount = 0;

LOUSTATUS 
LouKeLoadCoffImageB(
    PVOID           Base,
    PCFI_OBJECT     CfiObject,
    BOOL            KernelObject
);

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
            TmpHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocType(DRIVER_MODULE_HANDLES,  KERNEL_GENERIC_MEMORY);
            TmpHandle = (PDRIVER_MODULE_HANDLES)TmpHandle->Neighbors.NextHeader;
        }
    }

    string NewMod = (string)LouKeMallocArray(char, strlen(ModuleNameAndPath) + 1, KERNEL_GENERIC_MEMORY);
    strncpy(NewMod, ModuleNameAndPath, strlen(ModuleNameAndPath));

    LouKeLoadCoffImageExA(NewMod, &TmpHandle->CfiObject, true);

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
    LouKeLoadCoffImageB((PVOID)Base, &TmpHandle->CfiObject, true);
    Entry = (DRIVER_MODULE_ENTRY)TmpHandle->CfiObject.Entry;
    TmpHandle->ModuleEntry = Entry;
    TmpHandle->DriverObject = LouKeMalloc(DriverObjectSize, WRITEABLE_PAGE | PRESENT_PAGE);
    *DriverObject = TmpHandle->DriverObject;
    DriveHandlesCount++;
    return (DRIVER_MODULE_ENTRY)Entry;
}

HANDLE LouKeLoadLibraryA(string LibraryName){
    LouPrint("LouKeLoadLibraryA()\n");
    while(1);
}