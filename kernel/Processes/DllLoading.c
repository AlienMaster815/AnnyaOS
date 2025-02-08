#include <LouAPI.h>


DllModuleEntry LoadUserDllModule(uintptr_t Start, string ExecutablePath);

DllModuleEntry LouKeLoadUserModule(string ModuleNameAndPath){
    FILE* ModuleHandle = fopen(ModuleNameAndPath);
    if(!ModuleHandle){
        return 0x00;
    }
    return LoadUserDllModule((uintptr_t)ModuleHandle, ModuleNameAndPath); 
}

PHANDLE LoadKernelModule(uintptr_t Start, string ExecutablePath);

DRIVER_MODULE_ENTRY LouKeLoadKernelModule(string ModuleNameAndPath){
    FILE* ModuleHandle = fopen(ModuleNameAndPath);
    if(!ModuleHandle){
        return 0x00;
    }
    return (DRIVER_MODULE_ENTRY)LoadKernelModule((uintptr_t)ModuleHandle, ModuleNameAndPath);
}

