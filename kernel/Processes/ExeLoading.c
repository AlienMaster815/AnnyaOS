#include <LouAPI.h>

void* LoadPeExecutable(uintptr_t Start, string );

void* LouKeLoadPeExecutable(string ExecutablePath){
    FILE* ExeHandle = fopen(ExecutablePath);
    if(!ExeHandle){
        return 0x00;
    }
    return LoadPeExecutable((uintptr_t)ExeHandle, ExecutablePath); 
}
