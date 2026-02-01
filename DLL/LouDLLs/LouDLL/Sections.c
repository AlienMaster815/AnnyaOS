#include "LouDll.h"
#include <LouCoff.h>


//LOUSTATUS 
//LouKeVmmCreateSectionEx(
//    PHANDLE                 OutSectionHandle,
//    ACCESS_MASK             DesiredAccess,
//    POBJECT_ATTRIBUTES      ObjectAttributes,
//    PLARGE_INTEGER          MaximumSize,
//    ULONG                   SectionPageProtection,
//    ULONG                   AllocationAttributes,
//    HANDLE                  FileHandle,
//    PMEM_EXTENDED_PARAMETER ExtendedParameters,
//    ULONG                   ExtendedParameterCount
//);

LOUDLL_API
LOUSTATUS 
LouCreateSectionEx(
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
    UINT64 KulaPacket[11] = {0};

    KulaPacket[1] = (UINT64)OutSectionHandle;
    KulaPacket[2] = (UINT64)DesiredAccess;
    KulaPacket[3] = (UINT64)ObjectAttributes;
    KulaPacket[4] = (UINT64)MaximumSize;
    KulaPacket[5] = (UINT64)SectionPageProtection;
    KulaPacket[6] = (UINT64)AllocationAttributes;
    KulaPacket[7] = (UINT64)FileHandle;
    KulaPacket[8] = (UINT64)ExtendedParameters;
    KulaPacket[9] = (UINT64)ExtendedParameterCount;
    while(!KulaPacket[0]){
        LouCALL(LOUCREATESECTIONEX, (uint64_t)&KulaPacket[0], 0);
    }
    return (LOUSTATUS)KulaPacket[10];
}