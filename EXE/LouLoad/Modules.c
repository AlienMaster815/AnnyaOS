#include <LouLoad.h>
#include <bootloader/grub/multiboot2.h>

static UINT8 Counter = 0;

extern LOUSINE_LOADER_INFO KernelLoaderInfo;


void InitializeModuleForLoading(
    struct multiboot_tag* Module
){

    if(Counter < 2){
        if(Counter == 0){
            KernelLoaderInfo.KernelTag = (UINT64)Module;
        }
        else if(Counter == 1){
            KernelLoaderInfo.RegistryTag = (UINT64)Module;
        }
    }   
    
    Counter++;
}