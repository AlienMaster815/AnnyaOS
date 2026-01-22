#include <LouDDK.h>
#include "../../../LouAPI/Processes/ProcessPrivate.h"

//LouKeLoadCoffImageB

LOUDDK_API_ENTRY
SIZE LouKePmGetProcessCount();

LOUDDK_API_ENTRY uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

typedef struct _COFF_PRIVATE_DATA{
    CFI_OBJECT      CfiObject;
}COFF_PRIVATE_DATA, * PCOFF_PRIVATE_DATA;

typedef struct _SECTION_OBJECT{
    ListHeader                  Peers;
    bool                        Coff;
    ACCESS_MASK                 AccessMask;
    POBJECT_ATTRIBUTES          Attribute;
    PLARGE_INTEGER              MaxSize;
    ULONG                       SectionPageProtection;
    ULONG                       AllocationAttributes;
    HANDLE                      FileHandle;
    PMEM_EXTENDED_PARAMETER     ExtendedParameters;
    ULONG                       ExtendedParameterCount;
    PVOID                       SectionVBase;
    PVOID                       SectionPBase;
    SIZE                        SectionSize;
    SIZE                        SectionAlignment;
    PVOID                       SectionPrivateData;
    PVOID                       InitializedDataCopy;
    UINT64                      FrameFlags;
    BOOL                        Cow;
    BOOL                        Bss;
    BOOL                        Private;
}SECTION_OBJECT, * PSECTION_OBJECT;

typedef struct _PML4_LIST {
    ListHeader  Peers;
    UINT64*     Pml4;
}PML4_LIST, * PPML4_LIST;

static PML4_LIST Pml4MasterList = {0};
static mutex_t Pml4MasterLock = {0};

static SECTION_OBJECT   MasterSectionList = {0};
static mutex_t          SectionListLock = {0};
static 
PSECTION_OBJECT 
AllocateSectionObject(
    PVOID   SectionPrivateData
){  
    PSECTION_OBJECT TmpSection = &MasterSectionList;
    MutexLock(&SectionListLock);
    while(TmpSection->Peers.NextHeader){
        TmpSection = (PSECTION_OBJECT)TmpSection->Peers.NextHeader;
    }    
    TmpSection->Peers.NextHeader = (PListHeader)LouGeneralAllocateMemoryEx(sizeof(SECTION_OBJECT), GET_ALIGNMENT(SECTION_OBJECT));
    TmpSection = (PSECTION_OBJECT)TmpSection->Peers.NextHeader;
    TmpSection->SectionPrivateData = SectionPrivateData;
    MutexUnlock(&SectionListLock);
    return  TmpSection;
}    

static PSECTION_OBJECT VAddressToSectionObject(PVOID VAddress){
    PSECTION_OBJECT TmpSection = &MasterSectionList;
    MutexLock(&SectionListLock);
    while(TmpSection->Peers.NextHeader){
        TmpSection = (PSECTION_OBJECT)TmpSection->Peers.NextHeader;
        if(TmpSection->SectionVBase == VAddress){
            MutexUnlock(&SectionListLock);
            return TmpSection;
        }
    }    
    MutexUnlock(&SectionListLock);
    return 0x00;
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeVmmCreateSharedSectionEx(
    PVOID           PBase,
    PVOID           VBase,
    SIZE            Size,
    UINT64          FrameFlags,
    UINT64          NtFlags
){

    PSECTION_OBJECT SectionObject = AllocateSectionObject(0x00);

    SectionObject->SectionVBase = VBase;
    SectionObject->SectionPBase = PBase;
    SectionObject->SectionSize = Size;
    SectionObject->SectionPageProtection = NtFlags;
    SectionObject->FrameFlags = FrameFlags;

    PPML4_LIST TmpList = &Pml4MasterList;
    MutexLock(&Pml4MasterLock);
    while(TmpList->Peers.NextHeader){
        TmpList = (PPML4_LIST)TmpList->Peers.NextHeader;
        LouKeMapContinuousMemoryBlockEx((UINT64)PBase, (UINT64)VBase, Size, SectionObject->FrameFlags, TmpList->Pml4);
    }
    MutexUnlock(&Pml4MasterLock);

    return STATUS_SUCCESS;

}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeVmmCreateSharedSection(
    PVOID           PBase,
    PVOID           VBase,
    SIZE            Size,
    UINT64          FrameFlags
){  
    return LouKeVmmCreateSharedSectionEx(
        PBase,
        VBase, 
        Size,
        FrameFlags,
        LouPageFlagsToNtPageFlags(FrameFlags, false, false)
    );
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeCreateDeviceSection(
    PVOID   PBase,
    PVOID   VBase,
    SIZE    Size,
    UINT64  PageFlags
){
    return LouKeVmmCreateSharedSectionEx(
        PBase, 
        VBase,
        Size,
        NtPageFlagsToLouPageFlags(PageFlags, false, false),
        PageFlags
    );
}

LOUDDK_API_ENTRY
ULONG LouPageFlagsToNtPageFlags(UINT64 PageFlags, BOOL PageFault, BOOL NxExists){
    ULONG Result = 0;

    if(PageFlags & WRITEABLE_PAGE){
        Result = PAGE_READWRITE;
    }else{
        Result = PAGE_READONLY;
    }   

    if(PageFlags & UNCACHEABLE_PAGE){
        Result |= PAGE_NOCACHE;
    }
        
    Result = ((PageFlags & NOEXEC_PAGE) ? (Result << 4) : Result);
    
    return Result;
}

LOUDDK_API_ENTRY
UINT64 NtPageFlagsToLouPageFlags(ULONG PageFlags, BOOL PageFault, BOOL NxExists){ //todo Take Parameter for NX
    UINT64 Result = 0;
    UNUSED bool ExecuteBit = false;
    if((PageFlags & 0xFF) > 0xF){
        PageFlags >>= 4;
        ExecuteBit = true;
    }

    if(PageFlags & PAGE_WRITECOPY){
        if(PageFault){
            Result |= WRITEABLE_PAGE | PRESENT_PAGE;
        }else{
            Result |= PRESENT_PAGE;
        }
    }
    else if(PageFlags & PAGE_READWRITE){ //TODO Handle WriteCopy
        Result |= WRITEABLE_PAGE | PRESENT_PAGE;
    }else{
        Result |= PRESENT_PAGE;
    }  

    if((ExecuteBit) && (NxExists)){
        PageFlags <<= 4;
        Result |= NOEXEC_PAGE;
    }
    
    if(PageFlags & SEC_NOCACHE){
        Result |= CACHE_DISABLED_PAGE;
    }

    return Result;
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeVmmCreateSectionEx(
    PHANDLE                 OutSectionHandle,
    ACCESS_MASK             DesiredAccess,
    POBJECT_ATTRIBUTES      ObjectAttributes,
    PLARGE_INTEGER          MaximumSize,
    ULONG                   SectionPageProtection,
    ULONG                   AllocationAttributes,
    HANDLE                  FileHandle,
    PMEM_EXTENDED_PARAMETER ExtendedParameters,
    ULONG                   ExtendedParameterCount
){
    if(!OutSectionHandle){
        return STATUS_INVALID_PARAMETER;
    }

    if(FileHandle){

        FILE_TYPE FileType = LouKeGetFileType(FileHandle);


        switch(FileType){
            case COFF_FILE_TYPE:{
                PVOID PrivateData = LouGeneralAllocateMemoryEx(sizeof(COFF_PRIVATE_DATA), GET_ALIGNMENT(COFF_PRIVATE_DATA));
                PSECTION_OBJECT NewSection = AllocateSectionObject(PrivateData);
                NewSection->Coff = true;
                LouKeLoadCoffImageB(
                    (UINT8*)FileHandle,
                    (PCFI_OBJECT)PrivateData,
                    false
                );
                *OutSectionHandle = (HANDLE)NewSection;
                return STATUS_SUCCESS;
            }
            default:{
                LouPrint("LouKeVmmCreateSectionEx():FileHandle\n");
                while(1);
            }
        }
    }

    

    return STATUS_UNSUCCESSFUL;
}

KERNEL_IMPORT
LOUSTATUS LouKeGetVAddressPageInformation(
    UINT64  VAddress, 
    UINT8   Level,
    UINT64* FrameBase, 
    UINT64* FrameMember
);

void LouKeVmmCloneSectionToPml(UINT64* Pml4){
    LouPrint("LouKeVmmCloneSectionToPml()\n");
    PSECTION_OBJECT TmpSection = &MasterSectionList;
    MutexLock(&SectionListLock);
    while(TmpSection->Peers.NextHeader){
        TmpSection = (PSECTION_OBJECT)TmpSection->Peers.NextHeader;
        if(!TmpSection->Private){
            LouKeMapContinuousMemoryBlockEx((UINT64)TmpSection->SectionPBase, (UINT64)TmpSection->SectionVBase, TmpSection->SectionSize, TmpSection->FrameFlags, (UINT64*)((UINT64)Pml4 - GetKSpaceBase()));
        }
        //LouPrint("%h:%h:%h:%bc:%d\n", TmpSection->SectionVBase, TmpSection->SectionPBase, TmpSection->SectionSize, TmpSection->FrameFlags, (((UINT64)FrameMember - (UINT64)FrameBase) / 8));
    }    
    MutexUnlock(&SectionListLock);
    LouPrint("LouKeVmmCloneSectionToPml() DONE\n");
}

void LouKeSendPml4ToSections(UINT64* Pml4){
    PPML4_LIST TmpList = &Pml4MasterList;
    MutexLock(&Pml4MasterLock);
    while(TmpList->Peers.NextHeader){
        TmpList = (PPML4_LIST)TmpList->Peers.NextHeader;
    }
    TmpList->Peers.NextHeader = (PListHeader)LouKeMallocType(PML4_LIST, KERNEL_GENERIC_MEMORY);
    TmpList = (PPML4_LIST)TmpList->Peers.NextHeader;
    TmpList->Pml4 = Pml4;
    MutexUnlock(&Pml4MasterLock);
}

LOUSTATUS LouKeProcessCreateEntryThread(PHPROCESS Process, PVOID Entry);

LOUDDK_API_ENTRY
LOUSTATUS LouKeSectionInitNewProcess(
    PHPROCESS   Process,
    HANDLE      Section
){
    if((!Process) || (!Section)){
        return STATUS_INVALID_PARAMETER;
    }
    UNUSED PSECTION_OBJECT SectionData = (PSECTION_OBJECT)Section;
    if(SectionData->Coff){
        PCOFF_PRIVATE_DATA CfiData = (PCOFF_PRIVATE_DATA)SectionData->SectionPrivateData; 

        CfiData->CfiObject.CoffCommitSection((HANDLE)&CfiData->CfiObject, ((PGENERIC_PROCESS_DATA)Process)->PMLTree);

    }else {
        LouPrint("LouKeSectionInitNewProcess() : NON COFF\n");
        while(1);
    }

    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeVmmCreatePrivateSectionEx(
    PVOID   VirtualAddress,
    size_t  Size,
    UINT64  Alignment,
    UINT64  FrameFlags,
    ULONG   NtFlags,
    BOOL    Cow,
    BOOL    Bss
){
    PSECTION_OBJECT NewPrivateSection = AllocateSectionObject(0x00);

    NewPrivateSection->Private                  = true;
    NewPrivateSection->Cow                      = Cow;
    NewPrivateSection->Bss                      = Bss;

    if((!Bss) && (!Cow)){
        NewPrivateSection->InitializedDataCopy = LouKeMallocEx(Size, Alignment, KERNEL_GENERIC_MEMORY);
        memcpy(NewPrivateSection->InitializedDataCopy, VirtualAddress, Size); 
    }

    if(Cow){
        RequestPhysicalAddress((UINT64)VirtualAddress, (UINT64*)&NewPrivateSection->SectionPBase);
    }

    NewPrivateSection->SectionVBase             = VirtualAddress;
    NewPrivateSection->SectionSize              = Size;
    NewPrivateSection->SectionPageProtection    = NtFlags;
    NewPrivateSection->FrameFlags               = FrameFlags;
    NewPrivateSection->SectionAlignment         = Alignment;

    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeVmmCreatePrivateSection(
    PVOID   VirtualAddress,
    size_t  Size,
    UINT64  Alignment,
    UINT64  FrameFlags,
    BOOL    Cow,
    BOOL    Bss
){
    return LouKeVmmCreatePrivateSectionEx(
        VirtualAddress,
        Size, 
        Alignment,
        FrameFlags,
        LouPageFlagsToNtPageFlags(FrameFlags, false, false),
        Cow,
        Bss
    );
}

LOUDDK_API_ENTRY
void LouKeVmmCommitPrivateSectionVAddress(PVOID VAddress, UINT64 Pml4){

    PSECTION_OBJECT CommitSection = VAddressToSectionObject(VAddress);

    if(CommitSection->Bss){
        PVOID Section = LouAllocatePhysical64UpEx(CommitSection->SectionSize, CommitSection->SectionAlignment);
        memset((UINT8*)((UINTPTR)Section + GetKSpaceBase()), 0, CommitSection->SectionSize);
        LouKeMemoryBarrier();
        LouKeMapContinuousMemoryBlockEx((UINT64)Section, (UINT64)VAddress, CommitSection->SectionSize, CommitSection->FrameFlags, (UINT64*)((UINT64)Pml4 - GetKSpaceBase()));
        return;
    }

    if(CommitSection->Cow){
        LouKeMemoryBarrier();
        LouKeMapContinuousMemoryBlockEx((UINT64)CommitSection->SectionPBase, (UINT64)VAddress, CommitSection->SectionSize, CommitSection->FrameFlags & ~(WRITEABLE_PAGE), (UINT64*)((UINT64)Pml4 - GetKSpaceBase()));
        return;
    }
    
    PVOID Section = LouAllocatePhysical64UpEx(CommitSection->SectionSize, CommitSection->SectionAlignment);
    memcpy((UINT8*)((UINTPTR)Section + GetKSpaceBase()), CommitSection->InitializedDataCopy, CommitSection->SectionSize);
    LouKeMemoryBarrier();
    LouKeMapContinuousMemoryBlockEx((UINT64)Section, (UINT64)VAddress, CommitSection->SectionSize, CommitSection->FrameFlags, (UINT64*)((UINT64)Pml4 - GetKSpaceBase()));
}