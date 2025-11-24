#include <LouLoad.h>
#include <LoaderPrivate.h>

LOUSINE_LOADER_INFO KernelLoaderInfo = {0};


bool LoaderRequestMemory(
    void*   Address,
    size_t  size
);

void* ReserveKernelMemory(struct multiboot_tag* KernelTag){

    struct multiboot_tag_module* KernelMod = (struct multiboot_tag_module*)KernelTag; 
    PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader((UINT8*)(UINT64)KernelMod->mod_start);
    UINT64 ImageBase, ImageSize, ImageAlignment;
    BOOL MemoryReserved = false;
    ImageBase = ImageHeader->OptionalHeader.PE64.ImageBase;
    ImageSize = ImageHeader->OptionalHeader.PE64.SizeOfImage;
    ImageSize = ROUND_UP64(ImageSize, 2 * MEGABYTE);
    ImageAlignment = ImageHeader->OptionalHeader.PE64.SectionAlignment;

    MemoryReserved = LoaderRequestMemory((void*)ImageBase, ImageSize);
    if(!MemoryReserved){
        ImageBase = (UINT64)LoaderAllocateMemoryEx((size_t)ImageSize, ImageAlignment);
    }


    return (void*)ImageBase;
}

PCOFF_IMAGE_HEADER UnpackKernelImage(
    struct multiboot_tag* KernelTag,
    void** ImageBase
){
    UINT64 KSpaceBase = GetKSpaceBase();
    void* ImageVBase = (void*)((UINT64)*ImageBase + KSpaceBase);
    struct multiboot_tag_module* KernelMod = (struct multiboot_tag_module*)KernelTag; 
    PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader((UINT8*)(UINT64)KernelMod->mod_start);
    LoaderMapKernelMemoryBlock((UINT64)*ImageBase, (UINT64)ImageVBase, ImageHeader->OptionalHeader.PE64.SizeOfImage, 0b11);   
    *ImageBase = ImageVBase;
    EnforceLoaderMemoryMap((UINT64)ImageVBase, ImageHeader->OptionalHeader.PE64.SizeOfImage);


    memcpy(ImageVBase, (void*)(UINTPTR)KernelMod->mod_start, ImageHeader->OptionalHeader.PE64.SizeOfHeaders);
    KernelLoaderInfo.KernelBase = (UINT64)ImageVBase;
    KernelLoaderInfo.KernelLimit = (UINT64)ImageHeader->OptionalHeader.PE64.SizeOfImage;

    size_t SectionCount = ImageHeader->StandardHeader.NumberOfSections;
    
    for(size_t i = 0; i < SectionCount; i++){
        if(ImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress){
            memcpy(
                (void*)(ImageVBase + (UINT64)ImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress),
                (void*)((UINT64)KernelMod->mod_start + (UINT64)ImageHeader->OptionalHeader.PE64.SectionTables[i].PointerToRawData),
                ImageHeader->OptionalHeader.PE64.SectionTables[i].SizeOfRawData
            );
        }
    }

    return (PCOFF_IMAGE_HEADER)((UINT64)ImageVBase + ((UINT64)ImageHeader - (UINT64)KernelMod->mod_start));
}

void RelocateKernelImage(
    PCOFF_IMAGE_HEADER  KernelImage,
    UINT64              NewBase
){
    PCOFF_IMAGE_HEADER PeImageHeader = KernelImage;
    UINT64 RelocAddress = PeImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].VirtualAddress;
    if(!RelocAddress){
        return;
    }
    UINT64 PreferedBase = PeImageHeader->OptionalHeader.PE64.ImageBase;
    UNUSED UINT64 BaseDelta;
    UNUSED BOOL AddressDrop = false;

    RelocAddress += NewBase;

    if(NewBase < PreferedBase){
        AddressDrop = true;
        BaseDelta = PreferedBase - NewBase;
    }else{
        BaseDelta = NewBase - PreferedBase;
    }

    size_t Offset = 0;
    size_t RelocSize = PeImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].Size;
    
    while(Offset < RelocSize){
        PCFI_BASE_RELOCATION_BLOCK TmpReloc = (PCFI_BASE_RELOCATION_BLOCK)(UINT8*)(RelocAddress + Offset);
        size_t EntryCount = ((TmpReloc->BlockSize - sizeof(UINT64)) / sizeof(UINT16)); 
        for(size_t i = 0 ; i < EntryCount; i++){            
            switch(TmpReloc->RelocationEntires[i].Type){
                case CFI_BASE_RELOCATION_TYPE_BASED_DIR64:{
                    UINT64* Target = (UINT64*)(UINT8*)(((UINT64)TmpReloc->PageRVA + (UINT64)TmpReloc->RelocationEntires[i].Offset) + NewBase);
                    if(AddressDrop){
                        *Target -= BaseDelta;
                    }else{
                        *Target += BaseDelta;
                    }
                    break;
                }
                default:
                    continue;
            }
        }
        Offset += TmpReloc->BlockSize;
    }   

}

void ConfigureConfigurationStructure(
    PCOFF_IMAGE_HEADER KernelImage
){
    PCOFF_IMAGE_DATA_DIRECTORY  LoadConfigTable = &KernelImage->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_LOAD_CONFIG_TABLE];

    if(!LoadConfigTable->VirtualAddress){
        return;
    }

    PCFI_LOAD_CONFIGURATION_LAYOUT LoadConfigurationLayout = (PCFI_LOAD_CONFIGURATION_LAYOUT)(UINT8*)((UINTPTR)KernelImage + (UINTPTR)LoadConfigTable->VirtualAddress);

    LoadConfigurationLayout->LoadConfigurationLayout64.SecurityCookie = (((UINTPTR)LoadConfigurationLayout->LoadConfigurationLayout64.SecurityCookie - (UINTPTR)KernelImage->OptionalHeader.PE64.ImageBase) + (UINTPTR)KernelImage);

    *(UINT64*)LoadConfigurationLayout->LoadConfigurationLayout64.SecurityCookie = 81503;

}

void EnableKernelMemoryProtecion(
    PCOFF_IMAGE_HEADER  KernelImage,
    UINT64              KernelBase
){
    UNUSED UINT64 KernelPhysicalAddress = KernelBase - GetKSpaceBase();
    size_t SectionCount = KernelImage->StandardHeader.NumberOfSections;

    for(size_t i = 0 ; i < SectionCount; i++){
        UNUSED UINT64 PageFlags;
        UINT32 SectionCharacteristics = KernelImage->OptionalHeader.PE64.SectionTables[i].Characteristics;
        size_t VirtualSize = (size_t)KernelImage->OptionalHeader.PE64.SectionTables[i].VirtualSize;
        VirtualSize = ROUND_UP64(VirtualSize, 2 * MEGABYTE);

        if(SectionCharacteristics & CFI_SCN_CNT_CODE){
            PageFlags = 0b1; //present page
        }else if(
            SectionCharacteristics & CFI_SCN_CNT_INITIALIZED_DATA || 
            SectionCharacteristics & CFI_SCN_CNT_UNINITIALIZED_DATA 
        ){
            PageFlags = 0b11; //present Writable
        }
        else{
            PageFlags = 0b1; //present page
        }

        LoaderMapKernelMemoryBlock(
            KernelPhysicalAddress + (UINT64)KernelImage->OptionalHeader.PE64.SectionTables[i].VirtualAddress,
            KernelBase + (UINT64)KernelImage->OptionalHeader.PE64.SectionTables[i].VirtualAddress,
            VirtualSize,
            PageFlags
        );
        
    }

}

extern void AdjdustStackAndJump(UINT64, UINT64 , UINT64);

PLOUSINE_LOADER_INFO RebaseKernelLoaderInformation(){
    PLOUSINE_LOADER_INFO KernelLoaderInfoCopy = (PLOUSINE_LOADER_INFO)((UINT64)&KernelLoaderInfo + GetKSpaceBase());
    KernelLoaderInfoCopy->MultibootInfo += GetKSpaceBase();   
    UINT64 Stack = KernelLoaderInfoCopy->BootStack - (16 * KILOBYTE);
    EnforceLoaderMemoryMap(Stack, 16 * KILOBYTE);
    EnforceLoaderMemoryMap(Stack + GetKSpaceBase(), 16 * KILOBYTE);
    KernelLoaderInfoCopy->BootStack += GetKSpaceBase();
    KernelLoaderInfoCopy->KernelTag += GetKSpaceBase();
    KernelLoaderInfoCopy->RegistryTag += GetKSpaceBase();
    KernelLoaderInfoCopy->KernelVm.vLargePageClusters = KernelLoaderInfoCopy->KernelVm.LargePageClusters + GetKSpaceBase();
    KernelLoaderInfoCopy->RatPartition.RamMap += GetKSpaceBase();
    KernelLoaderInfoCopy->RatPartition.BootPartition += GetKSpaceBase();
    if(KernelLoaderInfoCopy->FirmwareInfo.EfiTable)KernelLoaderInfoCopy->FirmwareInfo.EfiTable += GetKSpaceBase();
    if(KernelLoaderInfoCopy->FirmwareInfo.Smbios)KernelLoaderInfoCopy->FirmwareInfo.Smbios += GetKSpaceBase();
    if(KernelLoaderInfoCopy->FirmwareInfo.Rsdp)KernelLoaderInfoCopy->FirmwareInfo.Rsdp += GetKSpaceBase();
    if(KernelLoaderInfoCopy->FirmwareInfo.Rsdp2)KernelLoaderInfoCopy->FirmwareInfo.Rsdp2 += GetKSpaceBase();
    if(KernelLoaderInfoCopy->FirmwareInfo.Vbe)KernelLoaderInfoCopy->FirmwareInfo.Vbe += GetKSpaceBase();
    if(KernelLoaderInfoCopy->FirmwareInfo.Apm)KernelLoaderInfoCopy->FirmwareInfo.Apm += GetKSpaceBase();
    if(KernelLoaderInfoCopy->FirmwareInfo.Framebuffer)KernelLoaderInfoCopy->FirmwareInfo.Framebuffer += GetKSpaceBase();
    if(KernelLoaderInfoCopy->FirmwareInfo.EfiMap)KernelLoaderInfoCopy->FirmwareInfo.EfiMap += GetKSpaceBase();
    
    return KernelLoaderInfoCopy;
}

extern void LouLoaderStart(
    UINT64 MBoot,
    UINT64 BootStack
){
    struct multiboot_tag* mboot = (struct multiboot_tag*)(uintptr_t)(MBoot + 8);

    KernelLoaderInfo.MultibootInfo = (UINT64)(UINT8*)mboot;
    KernelLoaderInfo.BootStack = BootStack;
    KernelLoaderInfo.RatPartition.BootPartition = GetMemoryTrackerAddress();

    SetKSpaceBase(KERNEL_SPACE_DEFAULT_BASE);

    InitializeLoaderMultibootInformation(mboot);
    
    void* KernelBase = ReserveKernelMemory((struct multiboot_tag*)KernelLoaderInfo.KernelTag);
    
    PCOFF_IMAGE_HEADER LousineImage = UnpackKernelImage((struct multiboot_tag*)KernelLoaderInfo.KernelTag, &KernelBase);


    RelocateKernelImage(
        LousineImage, 
        (UINT64)KernelBase
    );

    UNUSED PLOUSINE_LOADER_INFO KernelLoaderInfoCopy = RebaseKernelLoaderInformation();

    EnableKernelMemoryProtecion(
        LousineImage,
        (UINT64)KernelBase
    );

    AdjdustStackAndJump(
        GetKSpaceBase(), 
        (UINT64)(LousineImage->OptionalHeader.PE64.AddressOfEntryPoint + (UINT64)KernelBase),
        (UINT64)KernelLoaderInfoCopy
    );

    while(1);
}