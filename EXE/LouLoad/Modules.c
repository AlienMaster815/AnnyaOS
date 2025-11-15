#include <LouLoad.h>
#include <LoaderPrivate.h>

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
    struct multiboot_tag_module* mod = (struct multiboot_tag_module*)Module;
    EnforceLoaderMemoryMap(mod->mod_start, mod->mod_end - mod->mod_start);
    Counter++;
}

