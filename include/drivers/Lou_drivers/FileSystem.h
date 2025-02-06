#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

typedef char LOUSINE_KERNEL_DRIVE_ID;
typedef uint8_t LOUSINE_KERNEL_STORAGE_DEVICE_ID;



typedef struct _LOUSINE_KERNEL_FILESYSTEM{
    LOUSINE_KERNEL_DRIVE_ID                     DriveID;
    uint8_t                                     PortID;
    struct _LOUSINE_KERNEL_FILESYSTEM*          (*FileSystemScan)(LOUSINE_KERNEL_STORAGE_DEVICE_ID DriveNumber);
    LOUSTATUS                                   (*FileSystemFormatDisk)(LOUSINE_KERNEL_STORAGE_DEVICE_ID DriveNumber, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    void*                                       (*FileSystemOpen)(int16_t* FilePath, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    void                                        (*FileSystemClos)(int16_t* FilePath, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    uint64_t                                    FileAllocationTableSector;
}LOUSINE_KERNEL_FILESYSTEM, * PLOUSINE_KERNEL_FILESYSTEM;



#define ISO 0x01
#define FAT_SYS 0x02

#pragma pack(push, 1)
typedef struct _FSStruct{
    bool SystemDisk;
    uint8_t FSType;
    uint32_t FSNum;
    uintptr_t ExtendedFilesystemParameters;
} FSStruct, *PFSStruct;
#pragma pack(pop)

#ifdef __cplusplus


typedef struct _ISO_STRUCT{
    uint64_t PathTableSize;
}ISO_STRUCT, *PISO_STRUCT;

#include "FileSystems/fat.h"

#else

#ifndef _KERNEL_MODULE_
void FileSystemSetup();
#endif //kernel mod 

#endif

#endif
