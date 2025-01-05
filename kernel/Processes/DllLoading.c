#include <LouAPI.h>


DllModuleEntry LoadUserDllModule(uintptr_t Start, string ExecutablePath);

DllModuleEntry LouKeLoadUserModule(string ModuleNameAndPath){
    FILE* ModuleHandle = fopen(ModuleNameAndPath);
    return LoadUserDllModule((uintptr_t)ModuleHandle, ModuleNameAndPath); 
}