#include <LouLoad.h>
#include <LoaderPrivate.h>

extern LOUSINE_LOADER_INFO KernelLoaderInfo;


void 
InitializeLoaderMultibootInformation(
    struct multiboot_tag* MBoot
){

    while (MBoot->type != 0) {
        // Check if tag is memory map tag
        EnforceLoaderMemoryMap((uint64_t)MBoot, MBoot->size);
        switch (MBoot->type) {
        case(MULTIBOOT_TAG_TYPE_MMAP):{
            ParseRamMap(MBoot);
            KernelLoaderInfo.RatPartition.RamMap = (UINT64)(UINT8*)MBoot;
            break;
        }
        case(MULTIBOOT_TAG_TYPE_EFI64):{
            KernelLoaderInfo.FirmwareInfo.EfiTable = (UINT64)MBoot;          
            break;  
        }
        case(MULTIBOOT_TAG_TYPE_SMBIOS):{
            KernelLoaderInfo.FirmwareInfo.Smbios = (UINT64)MBoot;
            break;
        }
        case(MULTIBOOT_TAG_TYPE_ACPI_OLD):{
            KernelLoaderInfo.FirmwareInfo.Rsdp = (UINT64)MBoot;
            break;  
        }
        case(MULTIBOOT_TAG_TYPE_ACPI_NEW):{
            KernelLoaderInfo.FirmwareInfo.Rsdp2 = (UINT64)MBoot;
            break;
        }
        case(MULTIBOOT_TAG_TYPE_VBE):{
            KernelLoaderInfo.FirmwareInfo.Vbe = (UINT64)MBoot;
            break;
        }
        case(MULTIBOOT_TAG_TYPE_APM):{
            KernelLoaderInfo.FirmwareInfo.Apm = (UINT64)MBoot;
            break;
        }
        case(MULTIBOOT_TAG_TYPE_FRAMEBUFFER):{
            KernelLoaderInfo.FirmwareInfo.Framebuffer = (UINT64)MBoot;  
            break;
        }
        case(MULTIBOOT_TAG_TYPE_EFI_MMAP):{
            KernelLoaderInfo.FirmwareInfo.EfiMap = (UINT64)MBoot;
            break;
        }

        case(MULTIBOOT_TAG_TYPE_MODULE):{
            InitializeModuleForLoading(MBoot);
            break;
        }

        default:
            break;
        }

        if (MBoot->size % 8 == 0){
            MBoot = (struct multiboot_tag*)((uint8_t*)MBoot + MBoot->size);
        }
        else{
            MBoot = (struct multiboot_tag*)((uint8_t*)MBoot + ROUND_UP64(MBoot->size, 8));
        }
    }

    


}