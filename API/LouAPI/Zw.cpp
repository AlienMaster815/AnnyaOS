#include <LouDDK.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwAllocateLocallyUniqueId(
    PLUID Luid
){
    LouPrint("LouKeZwAllocateLocallyUniqueId()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwDeviceIoControlFile(
    HANDLE              FileHandle, 
    HANDLE              Event, 
    PIO_APC_ROUTINE     ApcRoutine, 
    PVOID               ApcContext, 
    PIO_STATUS_BLOCK    IoStatusBlock, 
    ULONG               IoControlCode, 
    PVOID               InputBuffer, 
    ULONG               InputBufferLength, 
    PVOID               OutputBuffer, 
    ULONG               OutputBufferLength
){
    LouPrint("LouKeZwDeviceIoControlFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwOpenProcess(
    PHANDLE             ProcessHandle, 
    ACCESS_MASK         DesiredAccess, 
    POBJECT_ATTRIBUTES  ObjectAttributes, 
    PCLIENT_ID          ClientId
){
    LouPrint("LouKeZwOpenProcess()\n");
    while(1);
    return STATUS_SUCCESS;
}


KERNEL_EXPORT 
LOUSTATUS 
LouKeZwPowerInformation(
    POWER_INFORMATION_LEVEL InformationLevel, 
    PVOID                   InputBuffer, 
    ULONG                   InputBufferLength, 
    PVOID                   OutputBuffer, 
    ULONG                   OutputBufferLength
){
    LouPrint("LouKeZwPowerInformation()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQueryVolumeInformationFile(
    HANDLE                  FileHandle, 
    PIO_STATUS_BLOCK        IoStatusBlock, 
    PVOID                   FsInformation, 
    ULONG                   Length, 
    FS_INFORMATION_CLASS    FsInformationClass
){
    LouPrint("LouKeZwQueryVolumeInformationFile()\n");
    while(1);
    return STATUS_SUCCESS; 
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwSetInformationThread(
    HANDLE          ThreadHandle, 
    THREADINFOCLASS ThreadInformationClass, 
    PVOID           ThreadInformation, 
    ULONG           ThreadInformationLength
){
    LouPrint("LouKeZwSetInformationThread()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwTerminateProcess(
    HANDLE      ProcessHandle, 
    LOUSTATUS   ExitStatus
){
    LouPrint("LouKeZwTerminateProcess()\n");
    while(1);
    return STATUS_SUCCESS;
}


KERNEL_EXPORT 
LOUSTATUS 
LouKeZwAllocateVirtualMemory(
    HANDLE ProcessHandle, 
    PVOID* BaseAddress, 
    ULONG_PTR ZeroBits, 
    PSIZE_T RegionSize, 
    ULONG AllocationType, 
    ULONG Protect
){
    LouPrint("LouKeZwAllocateVirtualMemory()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwCreateEvent(
    PHANDLE EventHandle, 
    ACCESS_MASK DesiredAccess, 
    POBJECT_ATTRIBUTES ObjectAttributes, 
    EVENT_TYPE EventType, 
    BOOLEAN InitialState
){
    LouPrint("LouKeZwCreateEvent()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwDeleteFile(
    POBJECT_ATTRIBUTES ObjectAttributes
){
    LouPrint("LouKeZwDeleteFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwDuplicateObject(
    HANDLE SourceProcessHandle, 
    HANDLE SourceHandle, 
    HANDLE TargetProcessHandle, 
    PHANDLE TargetHandle, 
    ACCESS_MASK DesiredAccess, 
    ULONG HandleAttributes, 
    ULONG Options
){
    LouPrint("LouKeZwDuplicateObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwDuplicateToken(
    HANDLE ExistingTokenHandle, 
    ACCESS_MASK DesiredAccess, 
    POBJECT_ATTRIBUTES ObjectAttributes, 
    BOOLEAN EffectiveOnly, 
    TOKEN_TYPE TokenType, 
    PHANDLE NewTokenHandle
){
    LouPrint("LouKeZwDuplicateToken()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwFlushBuffersFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock
){
    LouPrint("LouKeZwFlushBuffersFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwFlushBuffersFileEx(
    HANDLE FileHandle, 
    ULONG FLags, 
    PVOID Parameters, 
    ULONG ParametersSize, 
    PIO_STATUS_BLOCK IoStatusBlock
){
    LouPrint("LouKeZwFlushBuffersFileEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwFlushVirtualMemory(
    HANDLE ProcessHandle, 
    PVOID* BaseAddress, 
    PSIZE_T RegionSize,
    PIO_STATUS_BLOCK IoStatus
){
    LouPrint("LouKeZwFlushVirtualMemory()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwFreeVirtualMemory(
    HANDLE ProcessHandle, 
    PVOID* BaseAddress, 
    PSIZE_T RegionSize, 
    ULONG FreeType
){
    LouPrint("LouKeZwFreeVirtualMemory()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwFsControlFile(
    HANDLE FileHandle, 
    HANDLE Event, 
    PIO_APC_ROUTINE ApcRoutine, 
    PVOID ApcContext, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    ULONG FsControlCode, 
    PVOID InputBuffer, 
    ULONG InputBufferLength, 
    PVOID OutputBuffer, 
    ULONG OutputBufferLength
){
    LouPrint("LouKeZwFsControlFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwLockFile(
    HANDLE FileHandle, 
    HANDLE Event,
    PIO_APC_ROUTINE ApcRoutine, 
    PVOID ApcContext, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PLARGE_INTEGER ByteOffset, 
    PLARGE_INTEGER Length, 
    ULONG Key, 
    BOOLEAN FailImmediately, 
    BOOLEAN ExclusiveLock
){
    LouPrint("LouKeZwLockFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwNotifyChangeKey(
    HANDLE KeyHandle, 
    HANDLE Event, 
    PIO_APC_ROUTINE ApcRoutine, 
    PVOID ApcContext, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    ULONG CompletionFilter, 
    BOOLEAN WatchTree, 
    PVOID Buffer, 
    ULONG BufferSize, 
    BOOLEAN Asynchronous
){
    LouPrint("LouKeZwNotifyChangeKey()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwOpenDirectoryObject(
    PHANDLE DirectoryHandle, 
    ACCESS_MASK DesiredAccess, 
    POBJECT_ATTRIBUTES ObjectAttributes
){
    LouPrint("LouKeZwOpenDirectoryObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwOpenProcessTokenEx(
    HANDLE ProcessHandle, 
    ACCESS_MASK DesiredAccess, 
    ULONG HandleAttributes, 
    PHANDLE TokenHandle
){
    LouPrint("LouKeZwOpenProcessTokenEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwOpenThreadTokenEx(
    HANDLE ThreadHandle, 
    ACCESS_MASK DesiredAccess, 
    BOOLEAN OpenAsSelf, 
    ULONG HandleAttributes, 
    PHANDLE TokenHandle
){
    LouPrint("LouKeZwOpenThreadTokenEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQueryDirectoryFile(
    HANDLE FileHandle, 
    HANDLE Event, 
    PIO_APC_ROUTINE ApcRoutine, 
    PVOID ApcContext, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID FileInformation, 
    ULONG Length, 
    FILE_INFORMATION_CLASS FileInformationClass, 
    BOOLEAN ReturnSingleEntry, 
    PUNICODE_STRING FileName, 
    BOOLEAN RestartScan
){
    LouPrint("LouKeZwQueryDirectoryFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQueryDirectoryFileEx(
    HANDLE FileHandle, 
    HANDLE Event, 
    PIO_APC_ROUTINE ApcRoutine, 
    PVOID ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID FileInformation, 
    ULONG Length, 
    FILE_INFORMATION_CLASS FileInformationClass, 
    ULONG QueryFlags, 
    PUNICODE_STRING FileName
){
    LouPrint("LouKeZwQueryDirectoryFileEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQueryEaFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID Buffer, 
    ULONG Length, 
    BOOLEAN ReturnSingleEntry, 
    PVOID EaList, 
    ULONG EaListLength, 
    PULONG EaIndex, 
    BOOLEAN RestartScan
){
    LouPrint("LouKeZwQueryEaFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQueryInformationToken(
    HANDLE TokenHandle, 
    TOKEN_INFORMATION_CLASS TokenInformationClass, 
    PVOID TokenInformation, 
    ULONG TokenInformationLength, 
    PULONG ReturnLength
){
    LouPrint("LouKeZwQueryInformationToken()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQueryObject(
    HANDLE Handle, 
    OBJECT_INFORMATION_CLASS ObjectInformationClass, 
    PVOID ObjectInformation, 
    ULONG ObjectInformationLength, 
    PULONG ReturnLength
){
    LouPrint("LouKeZwQueryObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQueryQuotaInformationFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID Buffer, 
    ULONG Length, 
    BOOLEAN ReturnSingleEntry, 
    PVOID SidList, 
    ULONG SidListLength, 
    PSID StartSid, 
    BOOLEAN RestartScan
){
    LouPrint("LouKeZwQueryQuotaInformationFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQuerySecurityObject(
    HANDLE Handle, 
    SECURITY_INFORMATION SecurityInformation, 
    PSECURITY_DESCRIPTOR SecurityDescriptor, 
    ULONG Length, 
    PULONG LengthNeeded
){
    LouPrint("LouKeZwQuerySecurityObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwQueryVirtualMemory(
    HANDLE ProcessHandle, 
    PVOID BaseAddress, 
    MEMORY_INFORMATION_CLASS MemoryInformationClass, 
    PVOID MemoryInformation, 
    SIZE_T MemoryInformationLength, 
    PSIZE_T ReturnLength
){
    LouPrint("LouKeZwQueryVirtualMemory()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwSetEaFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID Buffer, 
    ULONG Length
){
    LouPrint("LouKeZwSetEaFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwSetEvent(
    HANDLE EventHandle, 
    PLONG PreviousState
){
    LouPrint("LouKeZwSetEvent()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwSetInformationToken(
    HANDLE TokenHandle, 
    TOKEN_INFORMATION_CLASS TokenInformationClass, 
    PVOID TokenInformation,
    ULONG TokenInformationLength
){
    LouPrint("LouKeZwSetInformationToken()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwSetInformationVirtualMemory(
    HANDLE ProcessHandle, 
    VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass, 
    ULONG_PTR NumberOfEntries, 
    PMEMORY_RANGE_ENTRY VirtualAddresses, 
    PVOID VmInformation, 
    ULONG VmInformationLength
){
    LouPrint("LouKeZwSetInformationVirtualMemory()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwSetQuotaInformationFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID Buffer, 
    ULONG Length
){
    LouPrint("LouKeZwSetQuotaInformationFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwSetSecurityObject(
    HANDLE Handle, 
    SECURITY_INFORMATION SecurityInformation, 
    PSECURITY_DESCRIPTOR SecurityDescriptor
){
    LouPrint("LouKeZwSetSecurityObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwSetVolumeInformationFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID FsInformation, 
    ULONG Length, 
    FS_INFORMATION_CLASS FsInformationClass
){
    LouPrint("LouKeZwSetVolumeInformationFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwUnlockFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PLARGE_INTEGER ByteOffset, 
    PLARGE_INTEGER Length, 
    ULONG Key
){
    LouPrint("LouKeZwUnlockFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeZwWaitForSingleObject(
    HANDLE Handle, 
    BOOLEAN Alertable, 
    PLARGE_INTEGER Timeout
){
    LouPrint("LouKeZwWaitForSingleObject()\n");
    while(1);
    return STATUS_SUCCESS;
}