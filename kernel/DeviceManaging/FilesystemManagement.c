#include <LouAPI.h>

LOUSTATUS Iso9660DriverEntry();
uint8_t LouKeGetNumberOfStorageDevices();
LOUSTATUS FatDriverEntry();
LOUSTATUS LouKeFmMountDrive(
    PLOUSINE_KERNEL_FILESYSTEM LouKeFileSystem
);
typedef struct _LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE{
    ListHeader                   List;
    PDEVICE_DIRECTORY_TABLE      FileSystem;
}LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE, * PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE;

static LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE FileSystemTable;
static size_t FileSystemTableMembers = 0;

static LOUSINE_KERNEL_MOUNTED_FILESYSTEMS   MountedFileSystemTable;
static size_t                               MountedFileSystemTableMembers;

LOUSTATUS LouRegisterFileSystemDevice(PDEVICE_DIRECTORY_TABLE NewFileSystem){
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE Tmp = &FileSystemTable;
    for(size_t i = 0 ; i < FileSystemTableMembers; i++){
        if(Tmp->List.NextHeader){
            Tmp = (PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE)Tmp->List.NextHeader;
        }else{
            Tmp->List.NextHeader = (PListHeader)LouKeMallocType(LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE,  KERNEL_GENERIC_MEMORY);
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

typedef struct _DRIVE_ID_TABLE{
    LOUSINE_KERNEL_DRIVE_ID     DriveID;
    bool                        DriveTaken;
}DRIVE_ID_TABLE, * PDRIVE_ID_TABLE;

static DRIVE_ID_TABLE DriveIdTable[25] = {
    {'A', false},
    {'B', false},
    {'D', false},
    {'E', false},
    {'F', false},
    {'G', false},
    {'H', false},
    {'I', false},
    {'J', false},
    {'K', false},
    {'L', false},
    {'M', false},
    {'N', false},
    {'O', false},
    {'P', false},
    {'Q', false},
    {'R', false},
    {'S', false},
    {'T', false},
    {'U', false},
    {'V', false},
    {'W', false},
    {'X', false},
    {'Y', false},
    {'Z', false},
};

void InitializeFileSystemManager(){
    
    Iso9660DriverEntry(); 
    //FatDriverEntry();      
    uint8_t PortCount = LouKeGetNumberOfStorageDevices();
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE Tmp = &FileSystemTable;
    for(size_t FileSystemIndex = 0 ; FileSystemIndex < FileSystemTableMembers; FileSystemIndex++){
        PLOUSINE_KERNEL_FILESYSTEM FileSystemHandle = Tmp->FileSystem->KeyData;
        if(!FileSystemHandle->FileSystemScan)continue;
        for(uint8_t i = 0 ; i < PortCount; i ++){
            LouPrint("Scanning Port:%d\n", i);
            PLOUSINE_KERNEL_FILESYSTEM NewMountedFileSystem = FileSystemHandle->FileSystemScan(i);
            if(NewMountedFileSystem){
                PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS TmpMfs = &MountedFileSystemTable;
                for(size_t j = 0 ; j < MountedFileSystemTableMembers; j++){
                    if(TmpMfs->List.NextHeader){
                        TmpMfs = (PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS)TmpMfs->List.NextHeader;
                    }
                }
                TmpMfs->List.NextHeader = (PListHeader)LouKeMallocType(LOUSINE_KERNEL_MOUNTED_FILESYSTEMS, KERNEL_GENERIC_MEMORY);
                TmpMfs->FileSystem = NewMountedFileSystem;
                if(NewMountedFileSystem->FileSystemSeek){
                    //Seek Kernel Image tto identify if its a system disk
                    bool KernelImage = NewMountedFileSystem->FileSystemSeek("/ANNYA/SYSTEM64/LOUOSKRN.EXE", NewMountedFileSystem);
                    if(KernelImage){
                        LouPrint("Storage Device Is A System Disk\n");
                        NewMountedFileSystem->SystemDisk = true;
                        NewMountedFileSystem->DriveID = 'C';
                        MountedFileSystemTableMembers++;
                        LouKeFmMountDrive(NewMountedFileSystem);
                        continue;
                    }
                }
                for(uint8_t Drive = 0; Drive < 25; Drive++){
                    if(DriveIdTable[Drive].DriveTaken){
                        DriveIdTable[Drive].DriveTaken = true;
                        NewMountedFileSystem->DriveID = DriveIdTable[Drive].DriveID;
                    }
                }
                MountedFileSystemTableMembers++;
                LouKeFmMountDrive(NewMountedFileSystem);
            }
        }  
        if(Tmp->List.NextHeader){
            Tmp = (PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE)Tmp->List.NextHeader;
        }
    }
}

PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS GetMountedFileSystemTable(){
    return &MountedFileSystemTable;
}

size_t GetMountedFileSystemTableMembers(){
    return MountedFileSystemTableMembers;
}