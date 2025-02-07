#include <LouDDK.h>


KERNEL_IMPORT FSStruct* GetDriveFss(uint8_t DriveNumber);
KERNEL_IMPORT FSStruct* GetSystemDiskFss();
KERNEL_IMPORT uint8_t GetDriveNumberByFss(FSStruct* Fs);

//static spinlock_t FOpenLock;

LOUDDK_API_ENTRY
FILE* fopen(string FileName){

    

    return 0x00;
}

KERNEL_IMPORT
uint64_t GetAllocationBlockSize(uint64_t Address);

LOUDDK_API_ENTRY
size_t FFileSize(FILE* File){
    return GetAllocationBlockSize((uint64_t)File);
}