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