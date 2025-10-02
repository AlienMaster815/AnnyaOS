#include <LouAPI.h>

static uintptr_t BootRegistryBase = 0; 
static uintptr_t BootRegistryTop = 0; 



size_t GetBootDeviceCount();
void* LouKeGetBootDevice(size_t Index);

void InitializeBootRegistry(uintptr_t Base, uintptr_t Top){
    BootRegistryBase = Base;
    BootRegistryTop = Top;
}

string LouKeGetNextManifestDevice(string CurrentDevice);
string LouKeDoesManifestDeviceMatch(string CurrentDevice, void* Config);

size_t LouKeGetBootDeviceIndex(void* Config){
    size_t i = 0;
    string NextDevice = LouKeGetNextManifestDevice((string)BootRegistryBase);
    while(NextDevice){
        if(LouKeDoesManifestDeviceMatch(NextDevice, Config)){
            break;
        }
        NextDevice = LouKeGetNextManifestDevice(NextDevice);
        i++;
    }
    return i;
}