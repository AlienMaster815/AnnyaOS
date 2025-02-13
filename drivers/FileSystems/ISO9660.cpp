#include <LouDDK.h>
#include <Hal.h>

#define ROOT_DIRECTORY_START 156 - 7
#define ROOT_DIRECTORY_END 190 - 7
#define SIZE_OF_ROOT_DIRECTORY_ENTRY 34

#define LBA_LSB32 ROOT_DIRECTORY_START + 2
#define LBA_LSB_HI32 LBA_LSB32 + 1
#define LBA_MSB_LO32 LBA_LSB_HI32 + 1
#define LBA_MSB32 LBA_MSB_LO32 + 1

#define DL_LSB32 ROOT_DIRECTORY_START + 10
#define DL_LSB_HI32 DL_LSB32 + 1
#define DL_MSB_LO32 DL_LSB_HI32 + 1
#define DL_MSB DL_MSB_LO32 + 1

static bool IsIsoFileSystemEntryFileToken(string Entry, size_t EntrySize){
    //the iso Filesystem has two different entryies
    //it has a directory entry and a file entry the 
    //to determine the difference the files have a 
    //;1 at the end of the files string 
    // so add theentry size
    Entry += EntrySize;
    //Subtract two
    Entry -= 2;
    //compare for a ;1
    return (strncmp(Entry, ";1", 1) == 0);
}


static bool IsPathAFileToken(string Path){
    //The Losuine Kernel's Path system follows 
    //a c string style path it should be noted
    //that a file token is a path with and null
    //terminator or a dot terminator therfore
    //we 1st get the path length
    uint8_t PathLength = CurrentDirectoryStringLength(Path);
    //we then add the path length 
    //to get the Terminator charecter
    Path += PathLength;
    //then we comare the string to known
    //file tokens and return the results
    switch(Path[0]){
        case '.':
        case '\0':
            return true;
        default:
            return false;
    }
}

static bool IsIso9660ItemOfSearch(uint8_t* FOO, string SearchDirectory){
    bool SearchDirectoryIsFileToken = IsPathAFileToken(SearchDirectory);
    bool DirectoryEntryIsFileToken = IsIsoFileSystemEntryFileToken((string)&FOO[33], FOO[32]);
    //if the value in Directory length is less 
    //than what we are searching for thats a 
    //tale that its not the filesystem 
    if(CurrentDirectoryStringLength(SearchDirectory) > FOO[32])return false;
    //because iso filesystems have file tokens 
    //";1" the best way to handle is when
    //looking for a file make sure the search
    //and directory are tokens and compare
    //the entry length-2 (FOO[32] - 2)
    if(((SearchDirectoryIsFileToken) && (DirectoryEntryIsFileToken)) && (strncmp((string)&FOO[33], SearchDirectory ,FOO[32] - 2) == 0))return true;
    //other wise check for if both entries are
    //Directories the actual value of the entry
    //length is to be compared
    else if(((!SearchDirectoryIsFileToken) && (!DirectoryEntryIsFileToken)) && (strncmp((string)&FOO[33], SearchDirectory ,FOO[32]) == 0))return true;
    //if niether of these two scenarios this isnt
    //the Directory we are looking for
    //https://www.youtube.com/watch?v=ihyjXd2C-E8
    else return false;
}


uint32_t ISOGetLBA(uint8_t* DirectoryEntry){

    uint32_t LBA = 0;

    LBA |= DirectoryEntry[2];    
    LBA |= (DirectoryEntry[3] << 8);
    LBA |= (DirectoryEntry[4] << 16);
    LBA |= (DirectoryEntry[5] << 24);

    return LBA;
}

uint32_t ISOGetDirecotrySize(uint8_t* DirectoryEntry){

    uint32_t DATA_LEN = 0;

    DATA_LEN |= DirectoryEntry[10];
    DATA_LEN |= (DirectoryEntry[11] << 8);
    DATA_LEN |= (DirectoryEntry[12] << 16);
    DATA_LEN |= (DirectoryEntry[13] << 24);

    return DATA_LEN;
}

static FILE* ISOLouKeFindDirectory(
    uint32_t RootLBA,
    uint32_t RootSize, 
    uint8_t DrvNum, 
    string Dir,
    bool Seek
    ){

    UNUSED LOUSTATUS Status = LOUSTATUS_GOOD;
    UNUSED uint64_t BufferSize = RootSize;

    UNUSED uint16_t* Test = (uint16_t*)ReadDrive(
        DrvNum,
        RootLBA,
        1,
        &BufferSize,
        &Status
    );

    UNUSED uint8_t* FOO = (uint8_t*)(uint64_t)Test;
    
    UNUSED string NewDir = GetNextDirectoryName(Dir);

    UNUSED string SearchDirectory = NewDir;

    UNUSED bool FinalRecurse = false;
    while(1){
        if (IsIso9660ItemOfSearch(FOO, SearchDirectory)){
            
            //LouPrint("String Length:%d\n", FOO[32]);
            //LouPrint("String Value :%s\n", &FOO[33]);
            
            //First We are going to look at the LBA
            //to see where the Directory Exists in
            //memory
            RootLBA = ISOGetLBA(FOO);
            //Theen we are going to get the root 
            //size from the directory structure
            RootSize = ISOGetDirecotrySize(FOO);            
            //now if the root size is not 0
            //because some entries will be we
            //are going to round up the data 
            //to the nearest 2048 sector for
            //the sake of the drive 
            if(RootSize){
                BufferSize = ROUND_UP64(RootSize, 2048);
            }
            //now we can free the memory read
            //from the last sector to get ready
            //to allocate memory from the new
            //sector we are about to read
            ReleaseDriveHandle((RAMADD)Test);
            
            //before we read the Next sector 
            //we need to return if this is a
            //seek from the OS otherwise we
            //will just waste time reading if
            //we are just looking for a file
            //or Directory
            if(IsPathAFileToken(SearchDirectory) && Seek){
                return (FILE*)1;
            }

            //Now We Can read the next sector
            //now that we cleaned up the last 
            //sector
            uint16_t* Test = (uint16_t*)ReadDrive(
                DrvNum,
                RootLBA,
                1,
                &BufferSize,
                &Status
            );
            //now cast from Test to FOO and 
            //then get the next directory
            FOO = (uint8_t*)Test;
            if(IsPathAFileToken(SearchDirectory)){
                //if the end of the path
                //is reached then the file
                //is loaded and can be return
                FILE* LoadedFile = (FILE*)LouMallocEx(BufferSize, KILOBYTE_PAGE);
                memcpy(LoadedFile, FOO, BufferSize);
                ReleaseDriveHandle(FOO);
                return LoadedFile;
            }
            SearchDirectory = GetNextDirectoryName(SearchDirectory);

        }
        if(FOO[0] == 0){
            break;
        }
        else{
            FOO += FOO[0];   
        }
    }

    LouPrint("Done With Recursion: Could Not Find File\n");
    ReleaseDriveHandle((RAMADD)Test);  //Free before exiting
    return 0;
}

static VolumeDescriptor ReadVolumeDescriptor(uint8_t DrvNum,uint32_t sector = 0x10){
    
    VolumeDescriptor VD;

    LOUSTATUS Status = STATUS_SUCCESS;
    uint64_t BufferSize = 2048;

    uint16_t* Test = (uint16_t*)ReadDrive(
        DrvNum,
        sector,
        1,
        &BufferSize,
        &Status
        );

        if(!Test){
            //LouPrint("ISO FileSystem Has Not Been Found Due To Insufficent Resources\n");
            VD.Type = 0;
            VD.Identifier = 0x0000;
            VD.Version = 0;
            //LouPrint("VD Parsed\n");
            ReleaseDriveHandle((RAMADD)Test);
            return VD;
        }
        

        VD.Type = Test[0] & 0xFF;

        char foo[6];
        foo[0] = (char)(Test[0] >> 8);
        foo[1] = (char)(Test[1] & 0xFF);
        foo[2] = (char)(Test[1] >> 8);
        foo[3] = (char)(Test[2] & 0xFF);
        foo[4] = (char)(Test[2] >> 8);
        foo[5] = '\0';
        VD.Identifier = foo;
        VD.Version = Test[3] & 0xFF;



        //LouPrint("Type is: %d\n", VD.Type);
        //LouPrint("Identifier is: %s \n",VD.Identifier);
        //LouPrint("Version is: %d\n", VD.Version);


        if ((VD.Type != 1) || (strcmp(VD.Identifier, "CD001") != 0) || (VD.Version != 1)) {
            //LouPrint("ISO FileSystem Has Not Been Found\n");
            VD.Type = 0;
            VD.Identifier = 0x0000;
            VD.Version = 0;
            //LouPrint("VD Parsed\n");
            ReleaseDriveHandle((RAMADD)Test);
            return VD;
        }
            
        //If We are here we have successfully found an ISO Filesystem

        //LouPrint("ISO FileSystem Has Been Found Parseing ISO System Information\n");

        uint16_t i = 0, BufferSelector = 0;
        bool condition = false;

        //Parse Through The Rest Of The Data Buffer
        do{
            if (false == condition) {
                VD.Data[BufferSelector] = (uint8_t)(Test[i + 3] >> 8);
                condition = true;
                BufferSelector++;
                i++;
            }
            else {
                VD.Data[BufferSelector] = (uint8_t)(Test[i + 3] & 0xFF);
                BufferSelector++;
                condition = false; 
            }
        } while (i < ((2041 - 7) / 2));


        //LouPrint("VD Parsed\n");

        ReleaseDriveHandle((RAMADD)Test);

        return VD;
}


LOUDDK_API_ENTRY
void Iso9660FileSystemClose(string FilePath, FILE* File, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    ReleaseDriveHandle((RAMADD)File);

}

LOUDDK_API_ENTRY
FILE* Iso9660FileSystemOpen(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){
    UNUSED VolumeDescriptor VD = ReadVolumeDescriptor(FilesystemHandle->PortID);

    //:/Dir/dir/.../file
    //LouPrint("Opening File:%s\n", Path);

    uint64_t LBA = 0;
    uint64_t DATA_LEN = 0;
    LBA |= VD.Data[LBA_LSB32];    
    LBA |= (VD.Data[LBA_LSB_HI32] << 8);
    LBA |= (VD.Data[LBA_MSB_LO32] << 16);
    LBA |= (VD.Data[LBA_MSB32] << 24);

    DATA_LEN |= VD.Data[DL_LSB32];
    DATA_LEN |= (VD.Data[DL_LSB_HI32] << 8);
    DATA_LEN |= (VD.Data[DL_MSB_LO32] << 16);
    DATA_LEN |= (VD.Data[DL_MSB] << 24);        
            
    return ISOLouKeFindDirectory(
        LBA, 
        DATA_LEN, 
        FilesystemHandle->PortID, 
        FilePath,
        false
    );
}

LOUDDK_API_ENTRY
bool Iso9660FileSystemSeek(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){
    UNUSED VolumeDescriptor VD = ReadVolumeDescriptor(FilesystemHandle->PortID);

    //:/Dir/dir/.../file
    //LouPrint("Opening File:%s\n", Path);

    uint64_t LBA = 0;
    uint64_t DATA_LEN = 0;
    LBA |= VD.Data[LBA_LSB32];    
    LBA |= (VD.Data[LBA_LSB_HI32] << 8);
    LBA |= (VD.Data[LBA_MSB_LO32] << 16);
    LBA |= (VD.Data[LBA_MSB32] << 24);

    DATA_LEN |= VD.Data[DL_LSB32];
    DATA_LEN |= (VD.Data[DL_LSB_HI32] << 8);
    DATA_LEN |= (VD.Data[DL_MSB_LO32] << 16);
    DATA_LEN |= (VD.Data[DL_MSB] << 24);        
            
    return (bool)ISOLouKeFindDirectory(
        LBA, 
        DATA_LEN, 
        FilesystemHandle->PortID, 
        FilePath,
        true
    );
}

LOUDDK_API_ENTRY
PLOUSINE_KERNEL_FILESYSTEM Iso9660FileSystemScan(uint8_t PortID){
    VolumeDescriptor PVD = ReadVolumeDescriptor(PortID);
    //Create A File System Structure
    if((PVD.Type == ISO_PrimaryVolumeDescriptor) && (strncmp(PVD.Identifier, "CD001", 5) == 0) && (PVD.Version == 0x01)){
        PLOUSINE_KERNEL_FILESYSTEM Iso9660FileSystem = (PLOUSINE_KERNEL_FILESYSTEM)LouMalloc(sizeof(LOUSINE_KERNEL_FILESYSTEM));
        Iso9660FileSystem->PortID = PortID;
        Iso9660FileSystem->FileSystemScan = Iso9660FileSystemScan;
        Iso9660FileSystem->FileSystemClose = Iso9660FileSystemClose;
        Iso9660FileSystem->FileSystemOpen = Iso9660FileSystemOpen;
        Iso9660FileSystem->FileSystemSeek = Iso9660FileSystemSeek;
        return Iso9660FileSystem;
    }
    return 0x00;
}

LOUDDK_API_ENTRY
LOUSTATUS Iso9660DriverEntry(){

    PLOUSINE_KERNEL_FILESYSTEM Iso9660FileSystem = (PLOUSINE_KERNEL_FILESYSTEM)LouMalloc(sizeof(LOUSINE_KERNEL_FILESYSTEM));

    Iso9660FileSystem->FileSystemScan = Iso9660FileSystemScan;

    return LouKeRegisterDevice(
        0x00, 
        FILESYSTEM_DEVICE_T,
        "HKEY_LOCAL_MACHINE:/ANNYA/SYSTEM64/DRIVERS/ISO9660.SYS",
        (void*)Iso9660FileSystem,
        (void*)Iso9660FileSystem
    );
}
