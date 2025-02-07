#include <LouAPI.h>

LOUSTATUS Iso9660DriverEntry();
uint8_t LouKeGetNumberOfStorageDevices();



typedef struct _LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE{
    ListHeader                   List;
    PDEVICE_DIRECTORY_TABLE      FileSystem;
}LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE, * PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE;

static LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE FileSystemTable;
static size_t FileSystemTableMembers = 0;

typedef struct _LOUSINE_KERNEL_MOUNTED_FILESYSTEMS{
    ListHeader                  List;
    PLOUSINE_KERNEL_FILESYSTEM  FileSystem;
}LOUSINE_KERNEL_MOUNTED_FILESYSTEMS, * PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS;

static LOUSINE_KERNEL_MOUNTED_FILESYSTEMS   MountedFileSystemTable;
static size_t                               MountedFileSystemTableMembers;

LOUSTATUS LouRegisterFileSystemDevice(PDEVICE_DIRECTORY_TABLE NewFileSystem){
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE Tmp = &FileSystemTable;
    for(size_t i = 0 ; i < FileSystemTableMembers; i++){
        if(Tmp->List.NextHeader){
            Tmp = (PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE)Tmp->List.NextHeader;
        }else{
            Tmp->List.NextHeader = (PListHeader)LouMalloc(sizeof(LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE));
            Tmp = (PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE)Tmp->List.NextHeader;
        }
    }
    Tmp->FileSystem = NewFileSystem;
    FileSystemTableMembers++;
    return STATUS_SUCCESS;
}


LOUSTATUS LouUnRegisterFileSystemDevice(PDEVICE_INFORMATION_TABLE FileSystem){
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE Tmp = &FileSystemTable;
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE Tmp2 = &FileSystemTable;
    for(size_t i = 0 ; i < FileSystemTableMembers; i++){
        if(Tmp->List.NextHeader){
            Tmp = (PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE)Tmp->List.NextHeader;
        }
        if(Tmp->FileSystem == FileSystem){
            for(size_t j = 0 ; j < i; j++){
                if(Tmp->List.NextHeader){
                    Tmp2 = (PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE)Tmp2->List.NextHeader;
                }       
            }
            Tmp2->List.NextHeader = Tmp->List.NextHeader; 
            LouFree((RAMADD)Tmp);
            FileSystemTableMembers--;
            return STATUS_SUCCESS;
        }
    }
    return STATUS_UNSUCCESSFUL;
}



void InitializeFileSystemManager(){
    Iso9660DriverEntry();       
    uint8_t PortCount = LouKeGetNumberOfStorageDevices();
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE Tmp = &FileSystemTable;
    for(size_t FileSystemIndex = 0 ; FileSystemIndex < FileSystemTableMembers; FileSystemIndex++){
        PLOUSINE_KERNEL_FILESYSTEM FileSystemHandle = Tmp->FileSystem->KeyData;
        if(!FileSystemHandle->FileSystemScan)continue;
        for(uint8_t i = 0 ; i < PortCount; i ++){
            PLOUSINE_KERNEL_FILESYSTEM NewMountedFileSystem = FileSystemHandle->FileSystemScan(i);
            if(NewMountedFileSystem){
                PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS TmpMfs = &MountedFileSystemTable;
                for(size_t j = 0 ; j < MountedFileSystemTableMembers; j++){
                    if(TmpMfs->List.NextHeader){
                        TmpMfs = (PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS)TmpMfs->List.NextHeader;
                    }
                }
                TmpMfs->List.NextHeader = (PListHeader)LouMalloc(sizeof(LOUSINE_KERNEL_MOUNTED_FILESYSTEMS));
                TmpMfs = (PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS)TmpMfs->List.NextHeader;
                TmpMfs->FileSystem = NewMountedFileSystem;
                if(NewMountedFileSystem->FileSystemOpen){
                    FILE* KernelImage = NewMountedFileSystem->FileSystemOpen("/ANNYA/SYSTEM64/LOUOSKRN.EXE", NewMountedFileSystem);
                    if(KernelImage){
                        LouPrint("Storage Device Is A System Disk\n");
                        NewMountedFileSystem->SystemDisk = true;
                    }
                }
            }
        }  
        if(Tmp->List.NextHeader){
            Tmp = (PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE)Tmp->List.NextHeader;
        }
    }
}