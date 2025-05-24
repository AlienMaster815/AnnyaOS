#include <LouDDK.h>


KERNEL_IMPORT FSStruct* GetDriveFss(uint8_t DriveNumber);
KERNEL_IMPORT FSStruct* GetSystemDiskFss();
KERNEL_IMPORT uint8_t GetDriveNumberByFss(FSStruct* Fs);
KERNEL_IMPORT PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS GetMountedFileSystemTable();
KERNEL_IMPORT size_t GetMountedFileSystemTableMembers();
//static spinlock_t FOpenLock;

LOUDDK_API_ENTRY
bool fseek(string FileName){
      
    PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS MountedSystems = GetMountedFileSystemTable();

    size_t FileSystemsToCheck = GetMountedFileSystemTableMembers();
    char DriveString[2] = {
        0, '\0',
    };
    bool Result = false;

    for(size_t i = 0 ; i < FileSystemsToCheck; i++){
        //the first real filesystem starts after the ancor

        DriveString[0] = MountedSystems->FileSystem->DriveID;
                
        //Checks the Firs Charecter of the string for the drive letter
        if(strncmp(DriveString, FileName, 1) == 0){
            //Appends the string + 2 for Drive Letter And ':' to get to /FilePath

            string FilePath = (string)(uintptr_t)FileName + 2;
            if(MountedSystems->FileSystem->FileSystemOpen){
                Result = MountedSystems->FileSystem->FileSystemSeek(FilePath, MountedSystems->FileSystem);
            }else{
                LouPrint("Error Reading From Mounted Disk");
                while(1);
            }
            if(Result){
                return Result;
            }
            //otherwise the filesystem didnt find the file 
            //and if the filesystem is a system disc C
            //there is likely more than one filesystem linked
            //because the system disks are linked to one letter 
            //well loop back
        }
        if(MountedSystems->List.NextHeader){
            MountedSystems = (PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS)MountedSystems->List.NextHeader;
        }
    }

    return false;
}

LOUDDK_API_ENTRY
FILE* fopen(string FileName, uint64_t PageFlags){
    
    PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS MountedSystems = GetMountedFileSystemTable();

    size_t FileSystemsToCheck = GetMountedFileSystemTableMembers();
    char DriveString[2] = {
        0, '\0',
    };
    FILE* Result = 0x00;

    for(size_t i = 0 ; i < FileSystemsToCheck; i++){
        //the first real filesystem starts after the ancor

        DriveString[0] = MountedSystems->FileSystem->DriveID;
                
        //Checks the Firs Charecter of the string for the drive letter
        if(strncmp(DriveString, FileName, 1) == 0){
            //Appends the string + 2 for Drive Letter And ':' to get to /FilePath

            string FilePath = (string)(uintptr_t)FileName + 2;
            if(MountedSystems->FileSystem->FileSystemOpen){
                Result = MountedSystems->FileSystem->FileSystemOpen(FilePath, MountedSystems->FileSystem, PageFlags | UNCACHEABLE_PAGE);
            }else{
                LouPrint("Error Reading From Mounted Disk");
                while(1);
            }
            if(Result){
                return Result;
            }
            //otherwise the filesystem didnt find the file 
            //and if the filesystem is a system disc C
            //there is likely more than one filesystem linked
            //because the system disks are linked to one letter 
            //well loop back
        }
        if(MountedSystems->List.NextHeader){
            MountedSystems = (PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS)MountedSystems->List.NextHeader;
        }
    }

    return 0x00;
}

LOUDDK_API_ENTRY
void fclose(FILE* File){
    LouKeFreeFileData(File);
}