#ifndef _KERNEL_OBJECTS_H
#define _KERNEL_OBJECTS_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

#define GetObjectItemOffset(Object, Item) ((SIZE)&((Object*)0x00)->Item)

typedef struct _IDENTIFICATION_RANGE{
    INTEGER     RangeStart;
    INTEGER     Entries;
    mutex_t     RangeLock;
    struct{
        INTEGER RangeID;
        PVOID   Object;
        BOOL    RangeAllocated;
    }Identities[];
}IDENTIFICATION_RANGE, * PIDENTIFICATION_RANGE;

#define LouKeDestroyIdentificationRange(x) LouKeFree(x)

PIDENTIFICATION_RANGE
LouKeCreateIdentificationRange(
    INTEGER RangeStart,
    INTEGER RangeEnd
);

void LouKeReleaseIdFromRange(
    PIDENTIFICATION_RANGE IdRange,
    INTEGER Id
);

INTEGER 
LouKeAcquireIdFromRange(
    PIDENTIFICATION_RANGE   IdRange,
    PVOID                   Object
);



typedef struct _KERNEL_REFERENCE{
    mutex_t     IncrementLock;
    mutex_t     RaceLock;
    atomic_t    ReferenceCounter;
    //TODO: Add variables as needed
}KERNEL_REFERENCE, * PKERNEL_REFERENCE;

static inline bool LouKeAcquireReference(PKERNEL_REFERENCE KRef){
    if(MutexIsLocked(&KRef->IncrementLock)){
        return false;
    }
    MutexLock(&KRef->RaceLock);
    UINT32 Tmp = (UINT32)LouKeGetAtomic(&KRef->ReferenceCounter);
    Tmp++;
    LouKeSetAtomic(&KRef->ReferenceCounter,Tmp);
    MutexUnlock(&KRef->RaceLock);
    return true;
}

static inline void LouKeReleaseReference(PKERNEL_REFERENCE KRef){
    MutexLock(&KRef->RaceLock);
    UINT32 Tmp = (UINT32)LouKeGetAtomic(&KRef->ReferenceCounter);
    Tmp--;
    LouKeSetAtomic(&KRef->ReferenceCounter,Tmp);
    MutexUnlock(&KRef->RaceLock);
}

static inline UINT32 LouKeGetReferenceCount(PKERNEL_REFERENCE KRef){
    MutexLock(&KRef->RaceLock);
    UINT32 Tmp = (UINT32)LouKeGetAtomic(&KRef->ReferenceCounter);
    MutexUnlock(&KRef->RaceLock);
    return Tmp;
}

LOUSTATUS 
LouKeReadRegistryValue(
    LPWSTR  Key,
    PVOID   Data,
    size_t  Count
);

PVOID 
LouKeOpenRegistryHandle(
    LPWSTR  Key,
    PVOID   RootHandle
);

LOUSTATUS LouKeRegGetAndCombineStringPath(  
    PVOID   RootKey,
    LPWSTR  PathKey,
    LPWSTR  ExeKey,
    string* OutString
);   


void LouKeDumpRegData(
    PVOID RegHandle
);

PVOID GetRegHiveOffsetHandle(PVOID Key);

size_t LouKeGetRegistryKeySize(PVOID Key);

LOUSTATUS LouKeReadRegistryWcsValue(PVOID Key, LPWSTR String);

LOUSTATUS LouKeReadRegistryByteValue(
    PVOID Key, 
    BYTE* Data
);

LOUSTATUS LouKeReadRegistryWordValue(
    PVOID Key, 
    WORD* Data
);

LOUSTATUS LouKeReadRegistryDWordValue(
    PVOID Key, 
    DWORD* Data
);

LOUSTATUS LouKeReadRegistryQWordValue(
    PVOID Key, 
    QWORD* Data
);

#ifndef _OBJECT_ATTRIBUTES_DEF
#define _OBJECT_ATTRIBUTES_DEF
typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES* POBJECT_ATTRIBUTES;
#endif

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
);

typedef LOUSTATUS (*LOUSINE_OBJECT_CONSTRUCTOR)(PVOID Object, PVOID ConstructParams);
typedef LOUSTATUS (*LOUSINE_OBJECT_DECONSTRUCTOR)(PVOID Object);

LOUSTATUS LouKeCreateFastObjectClass(
    LOUSTR  ClassName,
    SIZE    ObjectCount,
    SIZE    ObjectSize,
    SIZE    ObjectAlignment,
    SIZE    Flags,
    SIZE    PageFlags
);

LOUSTATUS LouKeCreateFastObjectClassEx(
    LOUSTR                          ClassName,
    SIZE                            ObjectCount,
    SIZE                            ObjectSize,
    SIZE                            ObjectAlignment,
    SIZE                            Flags,
    SIZE                            PageFlags,
    LOUSINE_OBJECT_CONSTRUCTOR      Constructor,
    LOUSINE_OBJECT_DECONSTRUCTOR    DeConstructor
);

PVOID LouKeAllocateFastObject(
    LOUSTR  ObjectLookup
);

PVOID LouKeAllocateFastObjectEx(
    LOUSTR  ObjectLookup,
    PVOID   ConstructData
);
void LouKeFreeFastObject(LOUSTR ObjectLookup, PVOID Address);

LOUSTATUS LouKeRegisterObjectToObjectManager(
    PVOID                   ObjectPointer,
    SIZE                    ObjectSize,
    LOUSTR                  ObjectName,
    int                     MaxHandles,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
);

LOUSTATUS LouKeRegisterFileToObjectManager(
    FILE*                   File,
    LOUSTR                  FileName,
    int                     MaxHandles,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
);

LOUSTATUS LouKeGetObjectHeaderByName(
    LOUSTR  ObjectName,
    PVOID*  ObjectHeader
);

LOUSTATUS LouKeAcquireHandleForObject(
    PHANDLE     OutHandle,
    PVOID       Object, 
    ACCESS_MASK RequestedAccess
);

LOUSTATUS LouKeZwAcquireHandleForObjectEx(
    PHANDLE     OutHandle,
    PVOID       Object
);

LOUSTATUS LouKeZwAcquireHandleForObject(
    PHANDLE     OutHandle,
    PVOID       Object
);

#ifdef __cplusplus
}
#endif

#endif