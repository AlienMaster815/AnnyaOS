#include "Mf2Kbd.h"

static void LouKeMf2KbdIrqHandler(PPS2_DEVICE_OBJECT Ps2Device){

    UINT8 Scan; 
    Ps2ReadDataRegister(&Scan);

    

}

DRIVER_EXPORT
LOUSTATUS
LouKeHalInitializeMf2Ps2Keyboard(
    PPS2_DEVICE_OBJECT Ps2Device
){
    LouPrint("LouKeHalInitializeMf2Ps2Keyboard()\n");

    LouKeHalPs2InstallInterruptHandler(Ps2Device, (void(*)(uint64_t))LouKeMf2KbdIrqHandler);
    UINT8 Command;
    UINT8 Responce;
    Command = KBD_COMMAND_ENABLE_SCANNING;
    LOUSTATUS Status = LouKeHalPs2CommandPs2Device(Ps2Device, &Command, 1, &Responce, 1);
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Starting Scanning\n");
    }
    LouKeHalPs2FlushBuffer();
    
    LouKeHalPs2EnableInterrupt(Ps2Device);    

    LouPrint("LouKeHalInitializeMf2Ps2Keyboard() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS
DriverEntry(
    PDRIVER_OBJECT DrvObject, 
    PUNICODE_STRING RegEntry
){


    return STATUS_SUCCESS;
}