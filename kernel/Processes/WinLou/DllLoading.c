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
            TmpHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocType(DRIVER_MODULE_HANDLES,  KERNEL_GENERIC_MEMORY);
            TmpHandle = (PDRIVER_MODULE_HANDLES)TmpHandle->Neighbors.NextHeader;
        }
    }

    DRIVER_MODULE_ENTRY Entry;
    FILE* ModuleHandle = fopen(ModuleNameAndPath, KERNEL_GENERIC_MEMORY);
    if(!ModuleHandle){
        return 0x00;
    }

    string NewMod = (string)LouKeMallocArray(char, strlen(ModuleNameAndPath), KERNEL_GENERIC_MEMORY);
    strncpy(NewMod, ModuleNameAndPath, strlen(ModuleNameAndPath));

    TmpHandle->Paths = NewMod;
    Entry = (DRIVER_MODULE_ENTRY)LoadKernelModule((uintptr_t)ModuleHandle, ModuleNameAndPath);
    TmpHandle->ModuleEntry = Entry;
    TmpHandle->DriverObject = LouKeMalloc(DriverObjectSize, WRITEABLE_PAGE | PRESENT_PAGE);
    *DriverObject = TmpHandle->DriverObject;
    DriveHandlesCount++;
    return (DRIVER_MODULE_ENTRY)Entry;
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
    Entry = (DRIVER_MODULE_ENTRY)LoadKernelModule((uintptr_t)Base, 0x00);
    TmpHandle->ModuleEntry = Entry;
    TmpHandle->DriverObject = LouKeMalloc(DriverObjectSize, WRITEABLE_PAGE | PRESENT_PAGE);
    *DriverObject = TmpHandle->DriverObject;
    DriveHandlesCount++;
    return (DRIVER_MODULE_ENTRY)Entry;
}

typedef struct _LIBRARY_HANDLES{
    ListHeader                      Neighbors;
    string                          Paths;
    string                          LibraryName;
    DllModuleEntry                  LibraryEntry;
    HANDLE                          LibraryHandle;
    uintptr_t                       ImageBase;
    PPE32_PROCESS_EXECUTION_DATA    ProcessInformation;
}LIBRARY_HANDLES, * PLIBRARY_HANDLES;

static LIBRARY_HANDLES  LibHandles = {0};
static size_t           LibHandlesCount = 0;
// static mutex_t          LoadLibMutex;


typedef struct _ATTACH_THREAD_DATA{
    bool   (*DllEntry)(uint64_t, uint64_t, uint64_t);
    uint64_t DllHandle;
    uint64_t DllCallReason;
    uint64_t DllReserved;
    mutex_t  Lock;
}ATTACH_THREAD_DATA, * PATTACH_THREAD_DATA;

uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

extern uint64_t GetRBP();
extern void SetTEB();
uintptr_t LouKeCreateUserStackThreadWin(void (*Function)(), PVOID FunctionParameters, size_t StackSize, uint64_t TEBPointer);



HANDLE LouKeLoadLibraryA(string LibraryName){

    LouPrint("Loading Library:%s\n", LibraryName);
    bool IsLibraryAPath = false; 
    if(LibraryName[1] == ':'){
        IsLibraryAPath = true;
    } 

    PLIBRARY_HANDLES TmpLibHandle = &LibHandles;

    for(size_t i = 0; i < LibHandlesCount; i++){
        if(IsLibraryAPath && TmpLibHandle->Paths){
            if(strcmp(LibraryName, TmpLibHandle->Paths) == 0){
                return TmpLibHandle->LibraryHandle;
            }
        }else if((!IsLibraryAPath) && TmpLibHandle->LibraryName){
            if(strcmp(LibraryName, TmpLibHandle->LibraryName) == 0){
                return TmpLibHandle->LibraryHandle;
            }
        }

        if(!TmpLibHandle->Neighbors.NextHeader){
            TmpLibHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocType(LIBRARY_HANDLES, KERNEL_GENERIC_MEMORY);
        }
        TmpLibHandle = (PLIBRARY_HANDLES)TmpLibHandle->Neighbors.NextHeader;
    }

    if(IsLibraryAPath){
        string NewMod = (string)LouKeMallocArray(char, strlen(LibraryName), KERNEL_GENERIC_MEMORY);
        strncpy(NewMod, LibraryName, strlen(LibraryName));
        TmpLibHandle->Paths = NewMod;
        TmpLibHandle->LibraryEntry = LouKeLoadUserModule(LibraryName, &TmpLibHandle->ImageBase);
        //TODO: Apend the string for the Lib name


    }
    else{
        TmpLibHandle->LibraryName = LibraryName;
        // TODO: look at the registry and the program
        // Directory for finding the best compatible
        // Dll
        LouPrint("File Is Not Path\n");
        while(1);
    }
    //TODO: Look at the registery and 
    //find the reciprical of the above

    TmpLibHandle->LibraryHandle = (HANDLE)LouKeMallocType(atomic_t,  USER_GENERIC_MEMORY);

    //LouPrint("TmpLibHandle->LibraryEntry:%h\n", TmpLibHandle->LibraryEntry);
    //TODO: Manage Processes Loading the DLL
    TmpLibHandle->ProcessInformation = InitializeProcessData(TmpLibHandle->ImageBase, TmpLibHandle->Paths);

    if(TmpLibHandle->LibraryEntry){
        PWIN_TEB Teb = (PWIN_TEB)LouKeMallocType(WIN_TEB, USER_GENERIC_MEMORY);
    
        UNUSED PATTACH_THREAD_DATA DllAttachProcessData = (PATTACH_THREAD_DATA)LouKeMallocType(ATTACH_THREAD_DATA , USER_GENERIC_MEMORY);
        DllAttachProcessData->DllEntry = (bool(*)(uint64_t, uint64_t, uint64_t))TmpLibHandle->LibraryEntry;
        DllAttachProcessData->DllHandle = (uint64_t)TmpLibHandle->LibraryHandle;
        DllAttachProcessData->DllCallReason = (uint64_t)DLL_PROCESS_ATTACH;
        DllAttachProcessData->DllReserved = 0;
        MutexLock(&DllAttachProcessData->Lock);
        UNUSED uint64_t AttachLing = LouKeLinkerGetAddress("LouDll.dll", "AnnyaAttachDllToProcess");
        LouKeCreateUserStackThreadWin((void(*))AttachLing, DllAttachProcessData, 16 * KILOBYTE, (uint64_t)(uint8_t*)Teb);
        MutexSynchronize(&DllAttachProcessData->Lock);
    }
    LibHandlesCount++;
    return TmpLibHandle->LibraryHandle;
}