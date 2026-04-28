#ifndef _KERNEL_SECTIONS_H
#define _KERNEL_SECTIONS_H

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

#endif