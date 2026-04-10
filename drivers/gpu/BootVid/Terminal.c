#include "BootVid.h"

static int BootVidPrintAsciiCharecter(CHAR AsciiCharecter){

}
    
static int BootVidPrintUnicodeCharecter(UINT32 Charecter){

}

static void BootVidEndofData(){

}

static LOUSINE_ECS_DRIVER BootVidEcsDriver = {
    .DriverName = "BOOTVIS-ECS",
    .ModuleName = "BOOTVID.SYS",
    .EcsOperations = {
        .PrintAsciiCharecter = BootVidPrintAsciiCharecter,
        .PrintUnicodeCharecter = BootVidPrintUnicodeCharecter,
        .EndofData = BootVidEndofData,
    },
};

LOUSTATUS 
BootVidInitializeTerminalDriver(){
    LOUSTATUS Status;
    
    Status = LouKeRegisterEcsDriver(&BootVidEcsDriver);

    return Status;
}