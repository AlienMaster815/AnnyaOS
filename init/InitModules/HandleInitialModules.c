#include <LouAPI.h>

PHANDLE LoadKernelModule(uintptr_t Start, string ExecutablePath);
void InitializePreLoadedModule(uintptr_t Entry, uint8_t DriverNumber);

typedef struct __attribute__((packed)) _ModuleTrack{
    uintptr_t ModuleStart;
    uintptr_t ModuleEnd;
    bool BeingUsed;
    uintptr_t Entry;
}MoudleTrack, * PMoudleTrack;

static MoudleTrack Track[255];

#define PRE_LOADED_SYSTEM_FILES 1

static uint8_t StartupModules = 0;
void handle_module(
    uintptr_t ModuleStart,
    uintptr_t ModuleEnd
){

    EnforceSystemMemoryMap(ModuleStart, ModuleEnd - ModuleStart);



    Track[StartupModules].ModuleStart = ModuleStart;
    Track[StartupModules].ModuleEnd = ModuleEnd;


    StartupModules++;
}

void InitPreLoadedModules(){

}

bool PciScanBusCheck(P_PCI_DEVICE_OBJECT PDEV, uint8_t DriverNumber);

bool LouKeSeachPreLoadedSystemModules(P_PCI_DEVICE_OBJECT PDEV){
    LouPrint("Scanning External Modules\n");

    for(uint8_t i = 0 ; i < PRE_LOADED_SYSTEM_FILES; i++){
        if(PciScanBusCheck(PDEV, i)){
            return true;
        }
    }

    return false;
}