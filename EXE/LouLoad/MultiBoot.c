#include <LouLoad.h>
#include <LoaderPrivate.h>

typedef struct _EFI_MEMORY_DESCRIPTOR{
    UINT32      Type;
    UINT32      Padding;
    UINT64      PhysicalStart;
    UINT64      VirtualStart;
    UINT64      NumberOfPages;
    UINT64      Attribute;
}EFI_MEMORY_DESCRIPTOR, * PEFI_MEMORY_DESCRIPTOR;


extern LOUSINE_LOADER_INFO KernelLoaderInfo;

static UINT8 Counter = 0;

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

void LoaderReserveEfiTable(uint64_t Address) {
    struct multiboot_tag_efi64* TableHeader = (struct multiboot_tag_efi64*)Address;
	EnforceLoaderMemoryMap((uint64_t)(uintptr_t)TableHeader->pointer, TableHeader->size);
}

void InitializeEfiMap(
    struct multiboot_tag* EfiMap
){
    EfiMap = (struct multiboot_tag*)((UINT64)EfiMap + GetKSpaceBase());
	struct multiboot_tag_efi_mmap* Map = (struct multiboot_tag_efi_mmap*)EfiMap;

    static EFI_MEMORY_DESCRIPTOR* Desc;

    for(uint64_t i = 16; i < (Map->size); i += Map->descr_size){
			
		Desc = (EFI_MEMORY_DESCRIPTOR*)((UINT64)EfiMap + i);
		switch(Desc->Type){
			case(0):
			case(3):
			case(4):
			case(5):
			case(6):
			case(8):
			case(9):
			case(10):
			case(11):
			case(12):
			case(13):
			case(14):
				EnforceLoaderMemoryMap(Desc->PhysicalStart, 4096 * Desc->NumberOfPages);
				EnforceLoaderMemoryMap(Desc->VirtualStart, 4096 * Desc->NumberOfPages);
			default: continue;
		}
	}
}

void ReserveVbeMemory(struct multiboot_tag* MBOOT){
    struct multiboot_tag_vbe* vbe_tag = (struct multiboot_tag_vbe*)MBOOT;
    EnforceLoaderMemoryMap(vbe_tag->vbe_mode_info.framebuffer, ROUND_UP64(640 * 480 * (32 / 8), 4 * KILOBYTE));
}

void 
InitializeLoaderMultibootInformation(
    struct multiboot_tag* MBoot
){
    struct multiboot_tag* Tmp = MBoot;
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
            LoaderReserveEfiTable((UINT64)MBoot);
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
            ReserveVbeMemory(MBoot);
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

    MBoot = Tmp;
    LoaderCreateKernelSpace();

    while (MBoot->type != 0) {
        switch (MBoot->type) {
        case(MULTIBOOT_TAG_TYPE_EFI_MMAP):{
            InitializeEfiMap(MBoot);
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