#include <LouDDK.h>
#include <Hal.h>
// Updateing Systems As Needed

typedef struct __attribute__((packed)) _FAT_12_AND_16_EXTENDED_BLOCK{
    uint8_t     Int0x13DriveNumber;
    uint8_t     Rsv1;
    uint8_t     FatBootSignature;
    uint32_t    VolumeIdentification;
    char        VolumeLabel[11];
    uint8_t     FsType[8]; //FAT12, 16, or FAT.
    uint8_t     Padding[448];
    uint16_t    BootSignature;
    uint8_t     NoMansLand[]; //by specification this needs to be 0 for the entire sector
}FAT_12_AND_16_EXTENDED_BLOCK, * PFAT_12_AND_16_EXTENDED_BLOCK;

typedef struct __attribute__((packed)) _FAT_32_EXTENDED_BLOCK{
    uint32_t    FatSize32;
    uint16_t    ExtendedFlags;
    uint16_t    FileSystemVersion;
    uint32_t    RootCluster;
    uint16_t    FileSystemInformation;
    uint16_t    BootSector;
    uint8_t     Reserved[12];
    uint8_t     Int0x13DriveNumber;
    uint8_t     Reserved2;
    uint8_t     FatBootSignature;
    uint32_t    VolumeIdentification;
    char        VolumeLabel[11];
    char        FileSystemType[8];
    uint8_t     Reserved3[420];
    uint16_t    BootSignature;
    uint8_t     NoMansLand[];
}FAT_32_EXTENDED_BLOCK, * PFAT_32_EXTENDED_BLOCK;

typedef struct __attribute__((packed)) _FAT_BIOS_PARAMETER_BLOCK{
    uint8_t     JumpBoot[3];
    char        OemName[8]; 
    uint16_t    BytesPerSector;
    uint8_t     SectorsPerCluster;
    uint16_t    ReservedSectorCount;
    uint8_t     FileAllocationTableCount;
    uint16_t    RootEntryCount;
    uint16_t    TotalSectors16;
    uint8_t     BiosParameterBlockMedia;
    uint16_t    FatSize16;
    uint16_t    SectorsPerTrack;
    uint16_t    HeadCount;
    uint32_t    HiddenSectors;
    uint32_t    TotalSectors;
    union {
        FAT_12_AND_16_EXTENDED_BLOCK    Fat12And16Extention;
        FAT_32_EXTENDED_BLOCK           Fat32Extention;   
    }Extension;
}FAT_BIOS_PARAMETER_BLOCK, * PFAT_BIOS_PARAMETER_BLOCK;

typedef uint8_t FINAL_VERDICT;
#define NOT_FAT     0
#define FAT12       1
#define FAT16       2
#define FAT32       3
#define FAT32_EXT   4

LOUDDK_API_ENTRY
void Fat12FileSystemClose(string FilePath, FILE* File, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    

}

LOUDDK_API_ENTRY
FILE* Fat12FileSystemOpen(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){



    return 0x00;
}

LOUDDK_API_ENTRY
bool Fat12FileSystemSeek(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    
    return false;
}


LOUDDK_API_ENTRY
void Fat16FileSystemClose(string FilePath, FILE* File, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    

}

LOUDDK_API_ENTRY
FILE* Fat16FileSystemOpen(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){



    return 0x00;
}

LOUDDK_API_ENTRY
bool Fat16FileSystemSeek(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    
    return false;
}


LOUDDK_API_ENTRY
void Fat32FileSystemClose(string FilePath, FILE* File, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    

}

LOUDDK_API_ENTRY
FILE* Fat32FileSystemOpen(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){



    return 0x00;
}

LOUDDK_API_ENTRY
bool Fat32FileSystemSeek(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    return false;
}

LOUDDK_API_ENTRY
void Fat32ExtFileSystemClose(string FilePath, FILE* File, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    

}

LOUDDK_API_ENTRY
FILE* Fat32ExtFileSystemOpen(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){



    return 0x00;
}

LOUDDK_API_ENTRY
bool Fat32ExtFileSystemSeek(string FilePath, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    return false;
}


LOUDDK_API_ENTRY
PLOUSINE_KERNEL_FILESYSTEM FatFileSystemScan(uint8_t PortID){
    LouPrint("Searching For Fat FileSystem\n");
    
    LOUSTATUS Status = STATUS_SUCCESS;
    uint64_t BufferSize = 512;
    FINAL_VERDICT FinalVerdict = NOT_FAT;
    PFAT_BIOS_PARAMETER_BLOCK PBPB = (PFAT_BIOS_PARAMETER_BLOCK)ReadDrive(
        PortID,
        0,
        1,
        &BufferSize,
        &Status
    );
    uint16_t* ValidVBR = (uint16_t*)((uintptr_t)PBPB + 510);

    if(*ValidVBR != 0xAA55){
        return 0x00;
    }
    //Ok so the world likes to complicate things
    //and microsoft has jumped on the band wagon
    //with it the "secification" for FAT is out
    //the window (No pun intended). the method
    //of detection is not follwed including in
    //the windows formatting tool distibuted by
    //windows acording to detection methods the
    //the mehod for distinguishing fat32 and 
    //fat < 32 systems dosent work because
    //the systems are now designed for backwards
    //compatibility for small disks
    //so I think i found a method 
    //do tell the difference but its dirty

    //step 1 follow the original calculation of
    //the sectors occupied by the root directory
    //and god forbid it follows it handle 
    //accordingly
    if(!PBPB->RootEntryCount){
        FinalVerdict = FAT32;
    }

    if(
        ((((PBPB->RootEntryCount * 32) + (PBPB->BytesPerSector - 1)) == 0) || (PBPB->BytesPerSector == 0)) 
    ){
        //avoids a db0
        FinalVerdict = NOT_FAT;
        return 0x00;
    }

    uint64_t RDS = ((PBPB->RootEntryCount * 32) + (PBPB->BytesPerSector - 1)) / PBPB->BytesPerSector;
    uint64_t Size;
    uint64_t Sectors;
    if(PBPB->FatSize16){
        Size = PBPB->FatSize16;
    }else{
        Size = PBPB->Extension.Fat32Extention.FatSize32;
    }

    if(PBPB->TotalSectors16){
        Sectors = PBPB->TotalSectors16;
    }else{
        Sectors = PBPB->TotalSectors;
    }

    uint64_t DataSectors = Sectors - (PBPB->ReservedSectorCount + (PBPB->FileAllocationTableCount * Size) + RDS);

    if((PBPB->SectorsPerCluster == 0) || (DataSectors == 0)){
        //avoids another db0
        return 0x00;
    }

    uint64_t CountOfClusters = DataSectors / PBPB->SectorsPerCluster;

    if(CountOfClusters < 4085){
        FinalVerdict = FAT12;
    }else if(CountOfClusters < 65525){
        FinalVerdict = FAT16;
    }else{
        FinalVerdict = FAT32;
    }
    
    //step 2 acording to all specificatiions the
    //38th byte of fat < 32 has a signature of 
    //0x28 or 0x29 but in FAT 32  byte 38 is the
    //(0xff << 8) of the sectors per fat value
    //this creates a good way to detect if the 
    //system is 32 or 32 <... for a last check
    if(((FinalVerdict == FAT16) || (FinalVerdict == FAT12)) && ((PBPB->Extension.Fat12And16Extention.FatBootSignature == 0x28) || (PBPB->Extension.Fat12And16Extention.FatBootSignature == 0x28))){
        FinalVerdict = FAT16;
    }else{
        FinalVerdict = FAT32;
    }

    ReleaseDriveHandle((void*)PBPB);

    switch(FinalVerdict){
    case FAT32:{
        PLOUSINE_KERNEL_FILESYSTEM NewFat32System = (PLOUSINE_KERNEL_FILESYSTEM)LouKeMallocEx(sizeof(LOUSINE_KERNEL_FILESYSTEM), GET_ALIGNMENT(LOUSINE_KERNEL_FILESYSTEM), WRITEABLE_PAGE | PRESENT_PAGE);
        NewFat32System->FileSystemOpen = Fat32FileSystemOpen;
        NewFat32System->FileSystemClose = Fat32FileSystemClose;
        NewFat32System->FileSystemSeek = Fat32FileSystemSeek;
        return NewFat32System;
    }
    case FAT12:{
        PLOUSINE_KERNEL_FILESYSTEM NewFat12System = (PLOUSINE_KERNEL_FILESYSTEM)LouKeMallocEx(sizeof(LOUSINE_KERNEL_FILESYSTEM), GET_ALIGNMENT(LOUSINE_KERNEL_FILESYSTEM), WRITEABLE_PAGE | PRESENT_PAGE);
        NewFat12System->FileSystemOpen = Fat12FileSystemOpen;
        NewFat12System->FileSystemClose = Fat12FileSystemClose;
        NewFat12System->FileSystemSeek = Fat12FileSystemSeek;
        return NewFat12System;
    }
    case FAT16:{
        PLOUSINE_KERNEL_FILESYSTEM NewFat16System = (PLOUSINE_KERNEL_FILESYSTEM)LouKeMallocEx(sizeof(LOUSINE_KERNEL_FILESYSTEM), GET_ALIGNMENT(LOUSINE_KERNEL_FILESYSTEM), WRITEABLE_PAGE | PRESENT_PAGE);
        NewFat16System->FileSystemOpen = Fat16FileSystemOpen;
        NewFat16System->FileSystemClose = Fat16FileSystemClose;
        NewFat16System->FileSystemSeek = Fat16FileSystemSeek;
        return NewFat16System;
    }
    case FAT32_EXT:{
        PLOUSINE_KERNEL_FILESYSTEM NewFat32ExtSystem = (PLOUSINE_KERNEL_FILESYSTEM)LouKeMallocEx(sizeof(LOUSINE_KERNEL_FILESYSTEM), GET_ALIGNMENT(LOUSINE_KERNEL_FILESYSTEM), WRITEABLE_PAGE | PRESENT_PAGE);
        NewFat32ExtSystem->FileSystemOpen = Fat32ExtFileSystemOpen;
        NewFat32ExtSystem->FileSystemClose = Fat32ExtFileSystemClose;
        NewFat32ExtSystem->FileSystemSeek = Fat32ExtFileSystemSeek;
        return NewFat32ExtSystem;
    }
    }
    //redundant return for for the fussy mingw
    return 0x00;
}

LOUDDK_API_ENTRY
LOUSTATUS FatDriverEntry(){
    PLOUSINE_KERNEL_FILESYSTEM FatFileSystem = (PLOUSINE_KERNEL_FILESYSTEM)LouKeMallocEx(sizeof(LOUSINE_KERNEL_FILESYSTEM), GET_ALIGNMENT(LOUSINE_KERNEL_FILESYSTEM), WRITEABLE_PAGE | PRESENT_PAGE);

    FatFileSystem->FileSystemScan = FatFileSystemScan;

    return LouKeRegisterDevice(
        0x00, 
        FILESYSTEM_DEVICE_T,
        "HKEY_LOCAL_MACHINE:/ANNYA/SYSTEM64/DRIVERS/FAT.SYS",
        (void*)FatFileSystem,
        (void*)FatFileSystem
    );
}