#include "limine.h"
#include "cstdlib.h"
#include "loader.h"

LIMINE_REQUEST_START uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

LIMINE_REQUEST uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);

LIMINE_REQUEST_END uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

static LOADER_INFORMATION LoaderInformation = {0};

static void HaltAndCatchFile() {
    for (;;) {
        asm ("hlt");
    }
}

static volatile FORCE_ALIGNMENT(4096) UINT64 L3Tables[512] = {0};
static volatile FORCE_ALIGNMENT(4096) UINT64 L2Tables[512] = {0};

void MsvcAbiJump(UINT64 Info, UINT64 Jmp, UINT64 Stack);

void UnpackLoader(PCOFF_IMAGE_HEADER* ImageHeaderp, PVOID PhysicalAddress, PVOID CoffData){
    PCOFF_IMAGE_HEADER ImageHeader = *ImageHeaderp;

    memcpy(PhysicalAddress, CoffData, ImageHeader->OptionalHeader.PE64.SizeOfHeaders);
    SIZE SectionCount = ImageHeader->StandardHeader.NumberOfSections;

    for(SIZE i = 0; i < SectionCount; i++){
        if(ImageHeader->OptionalHeader.PE64.SectionTables[i].PointerToRawData){
            memcpy(
                (PVOID)((UINT64)PhysicalAddress + (UINT64)ImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress),
                (PVOID)((UINT64)CoffData + (UINT64)ImageHeader->OptionalHeader.PE64.SectionTables[i].PointerToRawData),
                ImageHeader->OptionalHeader.PE64.SectionTables[i].SizeOfRawData
            );
        }
    }    
    *ImageHeaderp = (PCOFF_IMAGE_HEADER)((UINT64)PhysicalAddress + ((UINT64)ImageHeader - (UINT64)CoffData));
}

BOOLEAN ApplyLoaderRelocation(
    PCOFF_IMAGE_HEADER  ImageHeader,
    PVOID               PhysicalAddress
){
    UINT64 RelocAddress = ImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].VirtualAddress;
    if(!RelocAddress){
        return true;
    }
    UINT64  PreferedBase = ImageHeader->OptionalHeader.PE64.ImageBase;
    UINT64  BaseDelta;
    BOOLEAN AddressDrop = false;

    RelocAddress += (UINT64)PhysicalAddress;

    if((UINT64)PhysicalAddress < PreferedBase){
        AddressDrop = true;
        BaseDelta = PreferedBase - (UINT64)PhysicalAddress;
    }else{
        BaseDelta = (UINT64)PhysicalAddress - PreferedBase;
    }

    SIZE Offset = 0;
    SIZE RelocSize = ImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].Size;
    while(Offset < RelocSize){
        PCFI_BASE_RELOCATION_BLOCK TmpReloc = (PCFI_BASE_RELOCATION_BLOCK)(UINT8*)(RelocAddress + Offset);
        SIZE EntryCount = ((TmpReloc->BlockSize - sizeof(UINT64)) / sizeof(UINT16));
        for(SIZE i = 0 ; i < EntryCount; i++){
            switch(TmpReloc->RelocationEntries[i].Type){
                case CFI_BASE_RELOCATION_TYPE_BASED_DIR64:{
                    UINT64* Target = (UINT64*)(UINT8*)(((UINT64)TmpReloc->PageRVA + (UINT64)TmpReloc->RelocationEntries[i].Offset) + PhysicalAddress); 
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
    return true;
}

void kmain() {
    
    //check revision
    if(LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false){
        HaltAndCatchFile();
    }

    //set up the first gig of data
    L3Tables[0] = (UINT64)LimineGetPhysicalAddress((UINTPTR)&L2Tables[0]) | 0b11;

    for(SIZE i = 0 ; i < 512; i++){
        L2Tables[i] = ((MEGABYTE_PAGE * i) | ((1 << 7) | 0b11));
    }

    UINT64* L4Tables = (UINT64*)LimineGetVirtualAddress(GetPageBase());

    L4Tables[0] = (UINT64)LimineGetPhysicalAddress((UINTPTR)&L3Tables[0]) | 0b11;
    //reload new tables
    LouKeReloadCR3();

    //set up RAT Mbr
    PLOADER_RAT_MBR_CHUNK RatMbr = LoaderSetUpRatMbr(&LoaderInformation);
    if(!RatMbr){
        DEBUG_TRAP;
        while(1);
    }
    LoaderInformation.RatMbr = RatMbr;

    BOOLEAN LockedAndLoaded = InitializeRatSubsystem(&LoaderInformation);
    if(!LockedAndLoaded){
        DEBUG_TRAP;
        while(1);
    }


    LockedAndLoaded = LoaderInitializeLoaderInformation(&LoaderInformation);
    if(!LockedAndLoaded){
        DEBUG_TRAP;
        while(1);
    }

    LoaderInformation.BootModulesCount = LoaderInformation.LoadedModulesCount - 2;
    LoaderInformation.BootModulesBase = (PLOADER_MEMORY_MAP)((UINTPTR)&LoaderInformation.LoadedModules[2] + KSpaceBase);

    LoaderInformation.LouLoadCoff = (PLOADER_MEMORY_MAP)((UINTPTR)&LoaderInformation.LoadedModules[0] + KSpaceBase);
    LoaderInformation.LousineCoff = (PLOADER_MEMORY_MAP)((UINTPTR)&LoaderInformation.LoadedModules[1] + KSpaceBase);

    //Locked and loaded we are ocsar mike
    PVOID LoaderBase = (PVOID)LoaderInformation.LoadedModules[0].Tracker.Base;
    PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader(LoaderBase);

    if(memcmp(&ImageHeader->StandardHeader.PeSignature, CFI_HEADER_LOUCOFF_SIGNATURE, 4)){
        DEBUG_TRAP;
        while(1);
    }

    if(ImageHeader->OptionalHeader.PE64.Subsystem != CFI_SUBSYSTEM_LOUSINE_LOADER_OBJECT){
        DEBUG_TRAP;
        while(1);
    }

    LoaderInformation.LoaderHandle = (KHANDLE)LoaderAllocateSpace(ImageHeader->OptionalHeader.PE64.SizeOfImage, ImageHeader->OptionalHeader.PE64.SectionAlignment);
    if(!LoaderInformation.LoaderHandle){
        DEBUG_TRAP;
        while(1);
    }

    UnpackLoader(&ImageHeader, LoaderInformation.LoaderHandle, LoaderBase);
    if(memcmp(&ImageHeader->StandardHeader.PeSignature, CFI_HEADER_LOUCOFF_SIGNATURE, 4)){
        DEBUG_TRAP;
        while(1);
    }

    if(ImageHeader->OptionalHeader.PE64.Subsystem != CFI_SUBSYSTEM_LOUSINE_LOADER_OBJECT){
        DEBUG_TRAP;
        while(1);
    }

    ApplyLoaderRelocation(ImageHeader, LoaderInformation.LoaderHandle);

    if(!ImageHeader->OptionalHeader.PE64.AddressOfEntryPoint){
        DEBUG_TRAP;
        while(1);
    }
    
    UINT64 LoaderEntry = (UINT64)(ImageHeader->OptionalHeader.PE64.AddressOfEntryPoint + (UINT64)LoaderInformation.LoaderHandle); 

    UINT64 LoaderStack = (UINT64)LoaderAllocateSpace(16 * KILOBYTE, 16);
    LoaderInformation.StackHandle = (KHANDLE)LoaderStack;

    for(SIZE i = 0 ; i < LoaderInformation.LoadedModulesCount; i++){
        LoaderInformation.LoadedModules[i].Tracker.Base = (UINT64)LimineGetPhysicalAddress((UINTPTR)LoaderInformation.LoadedModules[i].Tracker.Base);
    }

    MsvcAbiJump((UINT64)&LoaderInformation, LoaderEntry, LoaderStack + (16 * KILOBYTE));

    HaltAndCatchFile();
}