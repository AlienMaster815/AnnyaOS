#include <LouAPI.h>

LOUSTATUS Iso9660DriverEntry();
uint8_t LouKeGetNumberOfStorageDevices();
LOUSTATUS FatDriverEntry();


typedef struct _LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE{
    ListHeader                  Peers;
    ListHeader                  Mfs;
    LOUSINE_KERNEL_FILESYSTEM   FileSystem;
}LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE, * PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE;

static mutex_t      FileSystemsLock = {0};
static ListHeader   FileSystems = {0};
static SIZE         FileSystemsLoaded = 0;

KERNEL_EXPORT LOUSTATUS LouKeAllocateLousineKernelFilesystem(PLOUSINE_KERNEL_FILESYSTEM* OutFilesystem){
    if(!OutFilesystem){
        return STATUS_INVALID_PARAMETER;
    }
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE NewTable = LouKeMallocType(LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE, KERNEL_GENERIC_MEMORY);
    if(!NewTable){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *OutFilesystem = &NewTable->FileSystem; 
    return STATUS_SUCCESS;
}

KERNEL_EXPORT LOUSTATUS LouKeRegisterFileSystem(PLOUSINE_KERNEL_FILESYSTEM NewFileSystem){
    if(!NewFileSystem){
        return STATUS_INVALID_PARAMETER;
    }
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE NewFileSystemTable = CONTAINER_OF(NewFileSystem, LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE, FileSystem);
    MutexLock(&FileSystemsLock);
    LouKeListAddTail(&NewFileSystemTable->Peers, &FileSystems);
    FileSystemsLoaded++;
    MutexUnlock(&FileSystemsLock);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT LOUSTATUS LouKeUnRegisterFileSystem(PLOUSINE_KERNEL_FILESYSTEM FileSystem){
    if(!FileSystem){
        return STATUS_INVALID_PARAMETER;
    }
    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE FileSystemTable = CONTAINER_OF(FileSystem, LOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE, FileSystem);

    MutexLock(&FileSystemsLock);
    LouKeListDeleteItem(&FileSystemTable->Peers);
    FileSystemsLoaded--;
    MutexUnlock(&FileSystemsLock);
    LouKeFree(FileSystemTable);
    return STATUS_SUCCESS;
}

typedef struct _DRIVE_ID_TABLE{
    LOUSINE_KERNEL_DRIVE_ID     DriveID;
    bool                        DriveTaken;
}DRIVE_ID_TABLE, * PDRIVE_ID_TABLE;

UNUSED static DRIVE_ID_TABLE DriveIdTable[25] = {
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
    
    PVOID SystemIdHandle = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\SystemDrive\\SYSTEM_IDENTIFIER_TYPE", 0x00);
    PVOID IdHandle = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\SystemDrive\\SYSTEM_IDENTIFIER", 0x00);
    UINT8 RawByteId;
    LouKeReadRegistryByteValue(SystemIdHandle, &RawByteId);
    SYSTEM_IDENTIFIER_TYPE SystemIdType = (SYSTEM_IDENTIFIER_TYPE)RawByteId;

    PVOID IdData = 0;
    switch(SystemIdType){
        case VOLUME_IDENTIFER:{
            IdData = (PVOID)LouKeMallocArray(CHAR, LouKeGetRegistryKeySize(IdHandle) + 1, KERNEL_GENERIC_MEMORY);
            LouKeReadRegistryCsValue(IdHandle, (LOUSTR)IdData);
            break;
        }
        case VOLUME_SERIAL_NUMBER:{
            LouKeReadRegistryQWordValue(IdHandle, (UINT64*)&IdData);
            break;
        }
        default:
            break;
    }

    Iso9660DriverEntry(); 
    //FatDriverEntry();      

    PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE TmpTable;
    PListHeader BlockDevices = BlkDevGetBlockDevices();
    PBLOCK_DEVICE_OBJECT TmpBlockDevice;
    ForEachListEntry(TmpBlockDevice, BlockDevices, Peers){
        BlkDevApiAcquireDeviceReference(TmpBlockDevice);
        if(!BlkdevApiGetBlockSize(TmpBlockDevice)){
            goto _PUT_BLKDEV;
        }
        ForEachListEntry(TmpTable, &FileSystems, Peers){
            PLOUSINE_KERNEL_FILESYSTEM TmpFileSystem = &TmpTable->FileSystem;
            PLOUSINE_KERNEL_MOUNTED_FILESYSTEM MountedFileSystem;
            LOUSTATUS Status;
            if(!TmpFileSystem->FileSystemScan){
                goto _NEXT_FILESYSTEM;
            }
            Status = TmpFileSystem->FileSystemScan(TmpBlockDevice, &MountedFileSystem);
            if(Status != STATUS_SUCCESS){
                goto _NEXT_FILESYSTEM;
            }

            LouPrint("InitializeFileSystemManager()\n");
            while(1);

        _NEXT_FILESYSTEM:
        }

    _PUT_BLKDEV:
        BlkDevApiReleaseDeviceReference(TmpBlockDevice);
    }
    BlkDevPutBlockDevices();

    /*uint8_t PortCount = LouKeGetNumberOfStorageDevices();
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
                switch(SystemIdType){

                    case VOLUME_IDENTIFER:{
                        if(NewMountedFileSystem->FileSystemGetVid){
                            LOUSTR VidString = 0;
                            LOUSTATUS Status = NewMountedFileSystem->FileSystemGetVid(NewMountedFileSystem, &VidString);
                            BOOLEAN IsSystemDrive = false;
                            if(Status == STATUS_SUCCESS){
                                if(!strcmp(VidString, (LOUSTR)IdData)){
                                    IsSystemDrive = true;
                                }
                                LouKeFree(VidString);
                            }
                            if(IsSystemDrive){
                                LouPrint("Storage Device Is A System Disk\n");
                                NewMountedFileSystem->SystemDisk = true;
                                NewMountedFileSystem->DriveID = 'C';
                                MountedFileSystemTableMembers++;
                                continue;
                            }
                        }
                        break;
                    }
                    case VOLUME_SERIAL_NUMBER:{
                        if(NewMountedFileSystem->FileSystemGetVsi){
                            UINT64 VsnQuad = 0;
                            LOUSTATUS Status = NewMountedFileSystem->FileSystemGetVsi(NewMountedFileSystem, &VsnQuad);
                            if(Status == STATUS_SUCCESS){
                                if(!memcmp(&VsnQuad, &IdData, sizeof(UINT64))){
                                    LouPrint("Storage Device Is A System Disk\n");
                                    NewMountedFileSystem->SystemDisk = true;
                                    NewMountedFileSystem->DriveID = 'C';
                                    MountedFileSystemTableMembers++;
                                    continue;
                                }
                            }
                            break;
                        }
                    }
                    default:
                        break;
                }
                for(uint8_t Drive = 0; Drive < 25; Drive++){
                    if(DriveIdTable[Drive].DriveTaken){
                        DriveIdTable[Drive].DriveTaken = true;
                        NewMountedFileSystem->DriveID = DriveIdTable[Drive].DriveID;
                    }
                }
                MountedFileSystemTableMembers++;
            }
        }  
        if(Tmp->List.NextHeader){
            Tmp = (PLOUSINE_KERNEL_DEVICE_MANAGER_FILE_SYSTEM_TABLE)Tmp->List.NextHeader;
        }
    }
    switch(SystemIdType){
        case VOLUME_IDENTIFER:{
            LouKeFree(IdData);
        }
        default:
            break;
    }*/
}
