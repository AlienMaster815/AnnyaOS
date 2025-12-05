#include <LouDDK.h>

//LouKeLoadCoffImageB

typedef struct _COFF_PRIVATE_DATA{
    CFI_OBJECT      CfiObject;
}COFF_PRIVATE_DATA, * PCOFF_PRIVATE_DATA;

typedef struct _SECTION_OBJECT{
    ListHeader                  Peers;
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
    PVOID                       SectionPrivateData;
    UINT64                      FrameFlags;
}SECTION_OBJECT, * PSECTION_OBJECT;

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

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeCreateDeviceSection(
    PVOID   PBase,
    PVOID   VBase,
    SIZE    Size,
    UINT64  PageFlags
){
    PSECTION_OBJECT SectionObject = AllocateSectionObject(0x00);

    SectionObject->SectionVBase = VBase;
    SectionObject->SectionPBase = PBase;
    SectionObject->SectionSize = Size;
    SectionObject->SectionPageProtection = PageFlags;
    SectionObject->FrameFlags = NtPageFlagsToLouPageFlags(PageFlags ,false, false);

    return STATUS_SUCCESS;
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
            Result = WRITEABLE_PAGE | PRESENT_PAGE;
        }else{
            Result = PRESENT_PAGE;
        }
    }
    else if(PageFlags & PAGE_READWRITE){ //TODO Handle WriteCopy
        Result = WRITEABLE_PAGE | PRESENT_PAGE;
    }else{
        Result = PRESENT_PAGE;
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
                LouKeLoadCoffImageB(
                    (UINT8*)FileHandle,
                    (PCFI_OBJECT)PrivateData,
                    false
                );
                *OutSectionHandle = (HANDLE)NewSection;
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
        UINT64 FrameBase;
        UINT64 FrameMember;
        LouKeGetVAddressPageInformation(
            (UINT64)TmpSection->SectionVBase,
            4, 
            &FrameBase,
            &FrameMember
        );
        Pml4[(((UINT64)FrameMember - (UINT64)FrameBase) / 8)] = *(UINT64*)FrameMember;   
        //LouPrint("%h:%h:%h:%bc:%d\n", TmpSection->SectionVBase, TmpSection->SectionPBase, TmpSection->SectionSize, TmpSection->FrameFlags, (((UINT64)FrameMember - (UINT64)FrameBase) / 8));
    }    
    MutexUnlock(&SectionListLock);
    LouPrint("LouKeVmmCloneSectionToPml() DONE\n");
}