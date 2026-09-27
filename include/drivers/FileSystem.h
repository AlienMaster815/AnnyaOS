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

struct _BLOCK_DEVICE_OBJECT;
struct _LOUSINE_KERNEL_FILESYSTEM;

typedef struct _LOUSINE_KERNEL_MOUNTED_FILESYSTEM{
    ListHeader                          Peers;
    ListHeader                          gPeers;
    struct _LOUSINE_KERNEL_FILESYSTEM*  FileSystem;
    LOUSINE_KERNEL_DRIVE_ID             DriveID;
    bool                                SystemDisk;
    struct _BLOCK_DEVICE_OBJECT*        BlockDevice;
    UINT64                              BlockOffset;
}LOUSINE_KERNEL_MOUNTED_FILESYSTEM, * PLOUSINE_KERNEL_MOUNTED_FILESYSTEM;

typedef struct _LOUSINE_KERNEL_FILESYSTEM{
    LOUSTATUS   (*FileSystemScan)(struct _BLOCK_DEVICE_OBJECT* BlockDevice, PLOUSINE_KERNEL_MOUNTED_FILESYSTEM* OutFilesystem);
    LOUSTATUS   (*FileSystemFormatDisk)(struct _BLOCK_DEVICE_OBJECT* BlockDevice, PLOUSINE_KERNEL_MOUNTED_FILESYSTEM* LouKeFileSystem);
    LOUSTATUS   (*FileSystemOpen)(string FilePath, PLOUSINE_KERNEL_MOUNTED_FILESYSTEM LouKeFileSystem, FILE** OutFile);
    LOUSTATUS   (*FileSystemSeek)(string FilePath, PLOUSINE_KERNEL_MOUNTED_FILESYSTEM LouKeFileSystem);
    void        (*FileSystemClose)(string FilePath, FILE* File, PLOUSINE_KERNEL_MOUNTED_FILESYSTEM LouKeFileSystem);
    LOUSTATUS   (*FileSystemGetVsi)(PLOUSINE_KERNEL_MOUNTED_FILESYSTEM LouKeFileSystem, UINT64* OutVsi);
    LOUSTATUS   (*FileSystemGetVid)(PLOUSINE_KERNEL_MOUNTED_FILESYSTEM LouKeFileSystem, LOUSTR* OutVsi);
}LOUSINE_KERNEL_FILESYSTEM, * PLOUSINE_KERNEL_FILESYSTEM;

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


KERNEL_EXPORT LOUSTATUS LouKeAllocateLousineKernelFilesystem(PLOUSINE_KERNEL_FILESYSTEM* OutFilesystem);
KERNEL_EXPORT LOUSTATUS LouKeRegisterFileSystem(PLOUSINE_KERNEL_FILESYSTEM NewFileSystem);
KERNEL_EXPORT LOUSTATUS LouKeUnRegisterFileSystem(PLOUSINE_KERNEL_FILESYSTEM FileSystem);

#ifndef _USER_MODE_CODE_
#ifndef _KERNEL_MODULE_
void FileSystemSetup();
#endif
#endif
#ifdef __cplusplus
}
#endif
#endif