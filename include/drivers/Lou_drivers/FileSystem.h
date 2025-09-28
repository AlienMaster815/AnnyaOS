#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

typedef char LOUSINE_KERNEL_DRIVE_ID;
typedef uint8_t LOUSINE_KERNEL_STORAGE_DEVICE_ID;

typedef struct _FILESYSTEM_DIRECTORY_QUERY{
    size_t          Entries;
    struct{
        string      ObjectName;
        bool        File;
        //if(File == true){
            size_t  StartSector;
            size_t  SectorCount;
        //}
    }Entities[];
}FILESYSTEM_DIRECTORY_QUERY, * PFILESYSTEM_DIRECTORY_QUERY;

typedef struct _LOUSINE_KERNEL_FILESYSTEM{
    LOUSINE_KERNEL_DRIVE_ID                     DriveID;
    uint8_t                                     PortID;
    bool                                        SystemDisk;
    struct _LOUSINE_KERNEL_FILESYSTEM*          (*FileSystemScan)(uint8_t PortNumber);
    LOUSTATUS                                   (*FileSystemFormatDisk)(LOUSINE_KERNEL_STORAGE_DEVICE_ID DriveNumber, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    FILE*                                       (*FileSystemOpen)(string FilePath, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem, uint64_t PageFlags);
    PFILESYSTEM_DIRECTORY_QUERY                 (*FileSystemDirectoryQuery)(string DirPath, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    bool                                        (*FileSystemSeek)(string FilePath, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    void                                        (*FileSystemClose)(string FilePath, FILE* File, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    uint64_t                                    FileAllocationTableSector;
}LOUSINE_KERNEL_FILESYSTEM, * PLOUSINE_KERNEL_FILESYSTEM;

typedef struct _LOUSINE_KERNEL_MOUNTED_FILESYSTEMS{
    ListHeader                  List;
    PLOUSINE_KERNEL_FILESYSTEM  FileSystem;
}LOUSINE_KERNEL_MOUNTED_FILESYSTEMS, * PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS;


#define ISO 0x01
#define FAT_SYS 0x02


typedef struct _FSStruct{
    bool SystemDisk;
    uint8_t FSType;
    uint32_t FSNum;
    uintptr_t ExtendedFilesystemParameters;
} FSStruct, *PFSStruct;


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
