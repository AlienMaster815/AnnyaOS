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

static uint32_t ISOGetLBA(uint8_t* DirectoryEntry){

    uint32_t LBA = 0;

    LBA |= DirectoryEntry[2];    
    LBA |= (DirectoryEntry[3] << 8);
    LBA |= (DirectoryEntry[4] << 16);
    LBA |= (DirectoryEntry[5] << 24);

    return LBA;
}

static uint32_t ISOGetDirecotrySize(uint8_t* DirectoryEntry){

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
    string Dir
    ){

    LOUSTATUS Status = LOUSTATUS_GOOD;
    uint64_t BufferSize = RootSize;

    uint16_t* Test = (uint16_t*)ReadDrive(
        DrvNum,
        RootLBA,
        1,
        &BufferSize,
        &Status
    );

    UNUSED uint8_t* FOO = (uint8_t*)(uint64_t)Test;
    
    string NewDir = GetNextDirectoryName(Dir);

    string SearchDirectory = NewDir;

    bool FinalRecurse = false;
    while(1){
        //LouPrint("String Length:%d\n", FOO[32]);
        //LouPrint("String Value :%s\n", &FOO[33]);

        if (FOO[32] == CurrenDirectoryStringLength(SearchDirectory) || FinalRecurse){
            if(strncmp((const char*)SearchDirectory, (const char*)&FOO[33], CurrenDirectoryStringLength(SearchDirectory)) == 0){

                if(FinalRecurse != true){
                   SearchDirectory = GetNextDirectoryName(SearchDirectory);
                }            
                RootLBA = ISOGetLBA(FOO);
                RootSize = ISOGetDirecotrySize(FOO);

                if(RootSize){
                    BufferSize = ((RootSize + 2047) / 2048) * 2048;
                }
                //LouPrint("BufferSize:%h\n", BufferSize);
                LouKeFree((RAMADD)Test);
                uint16_t* Test = (uint16_t*)ReadDrive(
                    DrvNum,
                    RootLBA,
                    1,
                    &BufferSize,
                    &Status
                );
                FOO = (uint8_t*)(uint64_t)Test;

                if((FinalRecurse) && (RootSize)){
                    FILE* Handle = (FILE*)LouMallocEx(RootSize, KILOBYTE_PAGE);
                    memcpy(Handle, FOO, RootSize);
                    //LouPrint("Done With Recursion: Found File : FileSize:%h\n", RootSize);
                    LouKeFree((RAMADD)Test);  //Free before exiting
                    return Handle;
                }
                else if(*(char*)(SearchDirectory + CurrenDirectoryStringLength(SearchDirectory)) == '.'){
                    FinalRecurse = true;
                }

            }
        }
        if(FOO[0] == 0){
            break;
        }
        else{
            FOO += FOO[0];   
        }
    }

    //LouPrint("Done With Recursion: Could Not Find File\n");
    LouKeFree((RAMADD)Test);  //Free before exiting
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

        if(Test == 0x00){
            //LouPrint("ISO FileSystem Has Not Been Found Due To Insufficent Resources\n");
            VD.Type = 0;
            VD.Identifier = 0x0000;
            VD.Version = 0;
            //LouPrint("VD Parsed\n");
            LouKeFree((RAMADD)Test);
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
            LouKeFree((RAMADD)Test);
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

        LouKeFree((RAMADD)Test);

        return VD;
}


LOUDDK_API_ENTRY
void Iso9660FileSystemClose(string FilePath, FILE* File, PLOUSINE_KERNEL_FILESYSTEM FilesystemHandle){

    LouKeFree((RAMADD)File);

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
        FilePath
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
        return Iso9660FileSystem;
    }
    return 0x00;
}

LOUDDK_API_ENTRY
LOUSTATUS Iso9660DriverEntry(){

    PLOUSINE_KERNEL_FILESYSTEM Iso9660FileSystem = (PLOUSINE_KERNEL_FILESYSTEM)LouMalloc(sizeof(LOUSINE_KERNEL_FILESYSTEM));

    Iso9660FileSystem->FileSystemScan = Iso9660FileSystemScan;
    Iso9660FileSystem->FileSystemClose = Iso9660FileSystemClose;
    Iso9660FileSystem->FileSystemOpen = Iso9660FileSystemOpen;

    return LouKeRegisterDevice(
        0x00, 
        FILESYSTEM_DEVICE_T,
        "HKEY_LOCAL_MACHINE:/ANNYA/SYSTEM64/DRIVERS/ISO9660.SYS",
        (void*)Iso9660FileSystem,
        (void*)Iso9660FileSystem
    );
}
