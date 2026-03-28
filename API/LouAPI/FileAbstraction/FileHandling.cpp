//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <LouDDK.h>


LOUAPI FSStruct* GetDriveFss(uint8_t DriveNumber);
LOUAPI FSStruct* GetSystemDiskFss();
LOUAPI uint8_t GetDriveNumberByFss(FSStruct* Fs);
LOUAPI PLOUSINE_KERNEL_MOUNTED_FILESYSTEMS GetMountedFileSystemTable();
LOUAPI size_t GetMountedFileSystemTableMembers();
//static spinlock_t FOpenLock;

LOUAPI
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

LOUAPI
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
    LouPrint("Unable To Open File:%s\n", FileName);
    return 0x00;
}

LOUAPI
void fclose(FILE* File){
    LouKeFreeFileData(File);
}

LOUAPI 
SIZE 
fsize(
    FILE* File
){
    return LouKeGetAllocationSize((PVOID)File);
}