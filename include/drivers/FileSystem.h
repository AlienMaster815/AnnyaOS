#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef char LOUSINE_KERNEL_DRIVE_ID;
typedef uint8_t LOUSINE_KERNEL_STORAGE_DEVICE_ID;

typedef enum _SYSTEM_IDENTIFIER_TYPE{
    VOLUME_IDENTIFER        = 0,
    VOLUME_SERIAL_NUMBER    = 1,
}SYSTEM_IDENTIFIER_TYPE;



typedef struct _LOUSINE_KERNEL_FILESYSTEM{
    LOUSINE_KERNEL_DRIVE_ID                     DriveID;
    uint8_t                                     PortID;
    bool                                        SystemDisk;
    struct _LOUSINE_KERNEL_FILESYSTEM*          (*FileSystemScan)(uint8_t PortNumber);
    LOUSTATUS                                   (*FileSystemFormatDisk)(LOUSINE_KERNEL_STORAGE_DEVICE_ID DriveNumber, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    FILE*                                       (*FileSystemOpen)(string FilePath, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem, uint64_t PageFlags);
    bool                                        (*FileSystemSeek)(string FilePath, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    void                                        (*FileSystemClose)(string FilePath, FILE* File, struct _LOUSINE_KERNEL_FILESYSTEM* LouKeFileSystem);
    LOUSTATUS                                   (*FileSystemGetVsi)(struct _LOUSINE_KERNEL_FILESYSTEM*, UINT64* OutVsi);
    LOUSTATUS                                   (*FileSystemGetVid)(struct _LOUSINE_KERNEL_FILESYSTEM*, LOUSTR* OutVsi);
    uint64_t                                    FileAllocationTableSector;
}LOUSINE_KERNEL_FILESYSTEM, * PLOUSINE_KERNEL_FILESYSTEM;

typedef struct _LOUSINE_KERNEL_MOUNTED_FILESYSTEMS{
    ListHeader                  List;
    PLOUSINE_KERNEL_FILESYSTEM  FileSystem;
}LOUSINE_KERNEL_MOUNTED_FILESYSTEMS, * PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS;

#define ISO     0x01
#define FAT_SYS 0x02

typedef struct _FSStruct{
    bool SystemDisk;
    uint8_t FSType;
    uint32_t FSNum;
    uintptr_t ExtendedFilesystemParameters;
} FSStruct, *PFSStruct;
typedef struct _ISO_STRUCT{
    uint64_t PathTableSize;
}ISO_STRUCT, *PISO_STRUCT;

#ifndef _USER_MODE_CODE_
#ifndef _KERNEL_MODULE_
void FileSystemSetup();
#endif
#endif
#ifdef __cplusplus
}
#endif
#endif