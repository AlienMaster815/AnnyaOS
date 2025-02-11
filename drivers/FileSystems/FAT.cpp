#include <LouDDK.h>
#include <Hal.h>
// Updateing Systems As Needed

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
PLOUSINE_KERNEL_FILESYSTEM FatFileSystemScan(uint8_t PortID){
    LouPrint("Searching For Fat FileSystem\n");
    
    

    while(1);
    return 0x00;
}

LOUDDK_API_ENTRY
LOUSTATUS FatDriverEntry(){
    PLOUSINE_KERNEL_FILESYSTEM FatFileSystem = (PLOUSINE_KERNEL_FILESYSTEM)LouMalloc(sizeof(LOUSINE_KERNEL_FILESYSTEM));

    FatFileSystem->FileSystemScan = FatFileSystemScan;

    return LouKeRegisterDevice(
        0x00, 
        FILESYSTEM_DEVICE_T,
        "HKEY_LOCAL_MACHINE:/ANNYA/SYSTEM64/DRIVERS/FAT.SYS",
        (void*)FatFileSystem,
        (void*)FatFileSystem
    );
}