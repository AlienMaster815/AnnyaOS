#include <LouAPI.h>

DRIVER_MODULE_ENTRY LouKeLoadBootKernelModule(uintptr_t Base, void** DriverObject, size_t DriverObjectSize);
void* LouKeGetBootDevice(size_t Index);

void StartupConfigureExportTable(PVOID Table);
void StartupConfigureImportTable(PVOID Table);

void LouKeInitializeKernelRuntimeEnviornment(){

    StartupConfigureExportTable(KernelLoaderInfo.KernelExportTable);

    size_t StrLen = wcslen(L"KERNEL_DEFAULT_CONFIG\\Subsystems\\0x");
    size_t TotalLen = wcslen(L"KERNEL_DEFAULT_CONFIG\\Subsystems\\0x                ");
    LPWSTR SearchBuffer = LouKeMallocArray(WCHAR, TotalLen + 1, KERNEL_GENERIC_MEMORY);
    WORD LoadOrder;
    wcscpy(SearchBuffer, L"KERNEL_DEFAULT_CONFIG\\Subsystems\\0x");

    for(size_t i = 0 ; i < UINT64_MAX; i++){
        memset(&SearchBuffer[StrLen], 0, sizeof(WCHAR) * (TotalLen - StrLen));
        _ui64tow(i, &SearchBuffer[StrLen], 16);
        PVOID Key = LouKeOpenRegistryHandle(
            SearchBuffer,
            0x00
        );
        if(!Key){
            break;
        }
        
        Key = LouKeOpenRegistryHandle(
            L"LoadOrder",
            Key
        );

        if(!Key){
            continue;
        }

        LouKeReadRegistryWordValue(Key, &LoadOrder);
        
        if(!LoadOrder){
            continue;
        }

        void* DriverBase = LouKeGetBootDevice(LoadOrder);    
        void (*Driver)() = (void(*)())LouKeLoadBootKernelModule((uintptr_t)DriverBase, 0, 0x00);
        if(Driver){
            Driver();
        }
    }

    LouKeFree(SearchBuffer);

    StartupConfigureImportTable(KernelLoaderInfo.KernelImportTable);

}