#include <LouDDK.h>


KERNEL_EXPORT 
LOUSTATUS 
LouKeAllocateVirtualMemory(
    HANDLE      ProcessHandle, 
    PVOID       BaseAddress, 
    ULONG_PTR   ZeroBits, 
    PSIZE_T     RegionSize, 
    ULONG       AllocationType, 
    ULONG Protect
){
    LouPrint("LouKeAllocateVirtualMemory()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeClose(
    HANDLE Handle
){
    LouPrint("LouKeClose()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeCopyFileChunk(
    HANDLE              SourceHandle, 
    HANDLE              DestHandle, 
    HANDLE              Event, 
    PIO_STATUS_BLOCK    IoStatusBlock, 
    ULONG               Length, 
    PLARGE_INTEGER      SourceOffset, 
    PLARGE_INTEGER      DestOffset, 
    PULONG              SourceKey, 
    PULONG              DestKey, 
    ULONG               Flags
){
    LouPrint("LouKeCopyFileChunk()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeCreateFile(
    PHANDLE             FileHandle, 
    ACCESS_MASK         DesiredAccess, 
    POBJECT_ATTRIBUTES  ObjectAttributes, 
    PIO_STATUS_BLOCK    IoStatusBlock, 
    PLARGE_INTEGER      AllocationSize, 
    ULONG               FileAttributes, 
    ULONG               ShareAccess, 
    ULONG               CreateDisposition, 
    ULONG               CreateOptions, 
    PVOID               EaBuffer,
    ULONG               EaLength
){
    LouPrint("LouKeCreateFile()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeCreateSection(
    PHANDLE             SectionHandle, 
    ACCESS_MASK         DesiredAccess, 
    POBJECT_ATTRIBUTES  ObjectAttributes, 
    PLARGE_INTEGER      MaximumSize, 
    ULONG               SectionPageProtection, 
    ULONG               AllocationAttributes, 
    HANDLE              FileHandle
){
    LouPrint("LouKeCreateSection()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeDeviceIoControlFile(
    HANDLE FileHandle, 
    HANDLE Event, 
    PIO_APC_ROUTINE ApcRoutine, 
    PVOID ApcContext, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    ULONG IoControlCode, 
    PVOID InputBuffer, 
    ULONG InputBufferLength, 
    PVOID OutputBuffer, 
    ULONG OutputBufferLength
){
    LouPrint("LouKeDeviceIoControlFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeDuplicateToken(
    HANDLE              ExistingTokenHandle, 
    ACCESS_MASK         DesiredAccess, 
    POBJECT_ATTRIBUTES  ObjectAttributes, 
    BOOLEAN             EffectiveOnly, 
    TOKEN_TYPE          TokenType, 
    PHANDLE             NewTokenHandle
){  
    LouPrint("LouKeDuplicateToken()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeFlushBuffersFileEx(
    HANDLE              FileHandle, 
    ULONG               Flags, 
    PVOID               Parameters, 
    ULONG               ParametersSize, 
    PIO_STATUS_BLOCK    IoStatusBlock
){
    LouPrint("LouKeFlushBuffersFileEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeFreeVirtualMemory(
    HANDLE      ProcessHandle, 
    PVOID*      BaseAddress, 
    PSIZE_T     RegionSize, 
    ULONG       FreeType
){
    LouPrint("LouKeFreeVirtualMemory()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeFsControlFile(
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
    LouPrint("LouKeFsControlFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeLockFile(
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
    LouPrint("LouKeLockFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeOpenFile(
    PHANDLE FileHandle, 
    ACCESS_MASK DesiredAccess, 
    POBJECT_ATTRIBUTES ObjectAttributes,
    PIO_STATUS_BLOCK IoStatusBlock, 
    ULONG ShareAccess, 
    ULONG OpenOptions
){
    LouPrint("LouKeOpenFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeOpenProcessToken(
    HANDLE ProcessHandle, 
    ACCESS_MASK DesiredAccess, 
    PHANDLE TokenHandle
){
    LouPrint("LouKeOpenProcessToken()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeOpenProcessTokenEx(
    HANDLE          ProcessHandle, 
    ACCESS_MASK     DesiredAccess, 
    ULONG           HandleAttributes, 
    PHANDLE         TokenHandle
){
    LouPrint("LouKeOpenProcessTokenEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeOpenThreadToken(
    HANDLE ThreadHandle, 
    ACCESS_MASK DesiredAccess, 
    BOOLEAN OpenAsSelf, 
    PHANDLE TokenHandle
){
    LouPrint("LouKeOpenThreadToken()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeOpenThreadTokenEx(
    HANDLE ThreadHandle, 
    ACCESS_MASK DesiredAccess, 
    BOOLEAN OpenAsSelf, 
    ULONG HandleAttributes, 
    PHANDLE TokenHandle
){
    LouPrint("LouKeOpenThreadTokenEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePrivilegeCheck(
    HANDLE ClientToken, 
    PPRIVILEGE_SET RequiredPrivileges, 
    PBOOLEAN Result
){
    LouPrint("LouKePrivilegeCheck()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueryDirectoryFile(
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
    LouPrint("LouKeQueryDirectoryFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueryDirectoryFileEx(
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
    LouPrint("LouKeQueryDirectoryFileEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueryInformationFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID FileInformation, 
    ULONG Length, 
    FILE_INFORMATION_CLASS FileInformationClass
){
    LouPrint("LouKeQueryInformationFile()\n");
    while(1);
    return STATUS_SUCCESS;
}


KERNEL_EXPORT 
LOUSTATUS 
LouKeQueryInformationToken(
    HANDLE TokenHandle, 
    TOKEN_INFORMATION_CLASS 
    TokenInformationClass,
    PVOID TokenInformation, 
    ULONG TokenInformationLength, 
    PULONG ReturnLength
){
    LouPrint("LouKeQueryInformationToken()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueryObject(
    HANDLE Handle, 
    OBJECT_INFORMATION_CLASS ObjectInformationClass, 
    PVOID ObjectInformation, 
    ULONG ObjectInformationLength, 
    PULONG ReturnLength
){
    LouPrint("LouKeQueryObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueryQuotaInformationFile(
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
    LouPrint("LouKeQueryQuotaInformationFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQuerySecurityObject(
    HANDLE Handle, 
    SECURITY_INFORMATION SecurityInformation, 
    PSECURITY_DESCRIPTOR SecurityDescriptor, 
    ULONG Length, 
    PULONG LengthNeeded
){
    LouPrint("LouKeQuerySecurityObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueryVirtualMemory(
    HANDLE  ProcessHandle, 
    PVOID   BaseAddress, 
    MEMORY_INFORMATION_CLASS MemoryInformationClass, 
    PVOID MemoryInformation, 
    SIZE_T MemoryInformationLength, 
    PSIZE_T ReturnLength
){
    LouPrint("LouKeQueryVirtualMemory()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueryVolumeInformationFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID FsInformation, 
    ULONG Length, 
    FS_INFORMATION_CLASS FsInformationClass
){
    LouPrint("LouKeQueryVolumeInformationFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeReadFile(
    HANDLE FileHandle, 
    HANDLE Event, 
    PIO_APC_ROUTINE ApcRoutine, 
    PVOID ApcContext, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID Buffer, 
    ULONG Length, 
    PLARGE_INTEGER ByteOffset, 
    PULONG Key
){
    LouPrint("LouKeReadFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeSetInformationFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID FileInformation, 
    ULONG Length, 
    FILE_INFORMATION_CLASS FileInformationClass
){
    LouPrint("LouKeSetInformationFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeSetInformationThread(
    HANDLE ThreadHandle, 
    THREADINFOCLASS ThreadInformationClass, 
    PVOID ThreadInformation, 
    ULONG ThreadInformationLength
){
    LouPrint("LouKeSetInformationThread()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeSetInformationToken(
    HANDLE TokenHandle, 
    TOKEN_INFORMATION_CLASS TokenInformationClass, 
    PVOID TokenInformation, 
    ULONG TokenInformationLength
){
    LouPrint("LouKeSetInformationToken()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeSetQuotaInformationFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID Buffer, 
    ULONG Length
){  
    LouPrint("LouKeSetQuotaInformationFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeSetSecurityObject(
    HANDLE Handle, 
    SECURITY_INFORMATION SecurityInformation, 
    PSECURITY_DESCRIPTOR SecurityDescriptor
){
    LouPrint("LouKeSetSecurityObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeUnlockFile(
    HANDLE FileHandle, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PLARGE_INTEGER ByteOffset, 
    PLARGE_INTEGER Length, 
    ULONG Key
){
    LouPrint("LouKeUnlockFile()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeWriteFile(
    HANDLE FileHandle, 
    HANDLE Event, 
    PIO_APC_ROUTINE ApcRoutine, 
    PVOID ApcContext, 
    PIO_STATUS_BLOCK IoStatusBlock, 
    PVOID Buffer, 
    ULONG Length, 
    PLARGE_INTEGER ByteOffset, 
    PULONG Key
){
    LouPrint("LouKeWriteFile()\n");
    while(1);
    return STATUS_SUCCESS;
}
