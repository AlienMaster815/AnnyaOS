#include <LouAPI.h>

DllModuleEntry LoadUserDllModule(uintptr_t Start, string ExecutablePath);

DllModuleEntry LouKeLoadUserModule(string ModuleNameAndPath){

    FILE* ModuleHandle = fopen(ModuleNameAndPath);
    
    
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
            TmpHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocEx(sizeof(DRIVER_MODULE_HANDLES), GET_ALIGNMENT(DRIVER_MODULE_HANDLES), WRITEABLE_PAGE | PRESENT_PAGE);
            TmpHandle = (PDRIVER_MODULE_HANDLES)TmpHandle->Neighbors.NextHeader;
        }
    }

    DRIVER_MODULE_ENTRY Entry;
    FILE* ModuleHandle = fopen(ModuleNameAndPath);
    if(!ModuleHandle){
        return 0x00;
    }

    string NewMod = (string)LouKeMallocEx(strlen(ModuleNameAndPath), GET_ALIGNMENT(string), WRITEABLE_PAGE | PRESENT_PAGE);
    strncpy(NewMod, ModuleNameAndPath, strlen(ModuleNameAndPath));

    TmpHandle->Paths = NewMod;
    Entry = (DRIVER_MODULE_ENTRY)LoadKernelModule((uintptr_t)ModuleHandle, ModuleNameAndPath);
    TmpHandle->ModuleEntry = Entry;
    TmpHandle->DriverObject = LouKeMalloc(DriverObjectSize, WRITEABLE_PAGE | PRESENT_PAGE);
    *DriverObject = TmpHandle->DriverObject;
    DriveHandlesCount++;
    return (DRIVER_MODULE_ENTRY)Entry;
}

typedef struct _LIBRARY_HANDLES{
    ListHeader          Neighbors;
    string              Paths;
    string              LibraryName;
    DllModuleEntry      LibraryEntry;
    HANDLE              LibraryHandle;
}LIBRARY_HANDLES, * PLIBRARY_HANDLES;

static LIBRARY_HANDLES  LibHandles = {0};
static size_t           LibHandlesCount = 0;
// static mutex_t          LoadLibMutex;


typedef struct _ATTACH_THREAD_DATA{
    bool   (*DllEntry)(uint64_t, uint64_t, uint64_t);
    uint64_t DllHandle;
    uint64_t DllCallReason;
    uint64_t DllReserved;
    void   (*LockRelease)();
}ATTACH_THREAD_DATA, * PATTACH_THREAD_DATA;

uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

extern uint64_t GetRBP();
extern void SetTEB();
uintptr_t LouKeCreateUserStackThreadWin(void (*Function)(), PVOID FunctionParameters, size_t StackSize, uint64_t TEBPointer);

HANDLE LouKeLoadLibraryA(string LibraryName){

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
            TmpLibHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocEx(sizeof(LIBRARY_HANDLES), GET_ALIGNMENT(LIBRARY_HANDLES), WRITEABLE_PAGE | PRESENT_PAGE);
        }
        TmpLibHandle = (PLIBRARY_HANDLES)TmpLibHandle->Neighbors.NextHeader;
    }

    if(IsLibraryAPath){
        string NewMod = (string)LouKeMallocEx(strlen(LibraryName), GET_ALIGNMENT(string), WRITEABLE_PAGE | PRESENT_PAGE);
        strncpy(NewMod, LibraryName, strlen(LibraryName));
        TmpLibHandle->Paths = NewMod;
        TmpLibHandle->LibraryEntry = LouKeLoadUserModule(LibraryName);
        //TODO: Apend the string for the Lib name


    }
    else{
        TmpLibHandle->LibraryName = LibraryName;
        // TODO: look at the registry and the program
        // Directory for finding the best compatible
        // Dll
    }
    //TODO: Look at the registery and 
    //find the reciprical of the above

    TmpLibHandle->LibraryHandle = (HANDLE)LouKeMallocEx(sizeof(atomic_t), GET_ALIGNMENT(atomic_t), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);

    //LouPrint("TmpLibHandle->LibraryEntry:%h\n", TmpLibHandle->LibraryEntry);
    //TODO: Manage Processes Loading the DLL


    if(TmpLibHandle->LibraryEntry){
        PWIN_TEB Teb = (PWIN_TEB)LouKeMallocEx(sizeof(WIN_TEB), GET_ALIGNMENT(WIN_TEB), WRITEABLE_PAGE | USER_PAGE | PRESENT_PAGE);
    
        UNUSED PATTACH_THREAD_DATA DllAttachProcessData = (PATTACH_THREAD_DATA)LouKeMallocEx(sizeof(ATTACH_THREAD_DATA), GET_ALIGNMENT(ATTACH_THREAD_DATA) , USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
        DllAttachProcessData->DllEntry = (bool(*)(uint64_t, uint64_t, uint64_t))TmpLibHandle->LibraryEntry;
        DllAttachProcessData->DllHandle = (uint64_t)TmpLibHandle->LibraryHandle;
        DllAttachProcessData->DllCallReason = (uint64_t)DLL_PROCESS_ATTACH;
        DllAttachProcessData->DllReserved = 0;
        DllAttachProcessData->LockRelease = (void(*)())(uint8_t*)LouKeLinkerGetAddress("KERNEL32.dll", "ReleaseLoadLibraryALock");//ReleaseLoadLibraryALock

        UNUSED uint64_t AttachLing = LouKeLinkerGetAddress("LouDLL.dll", "AnnyaAttachDllToProcess");
        LouKeCreateUserStackThreadWin((void(*))AttachLing, DllAttachProcessData, 16 * KILOBYTE, (uint64_t)(uint8_t*)Teb);
    }
    LibHandlesCount++;
    return TmpLibHandle->LibraryHandle;
}