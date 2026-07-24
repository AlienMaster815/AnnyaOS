//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "Mf2Kbd.h"

static LOUSTATUS LouKeMf2KbdIrqHandler(UINT64 Data){
    UINT8 Ps2Data;
    PPS2_DEVICE_OBJECT Ps2Device = (PPS2_DEVICE_OBJECT)(UINT8*)Data;
    LouKeHalPs2ReadDeviceBuffer(Ps2Device, &Ps2Data, 1);



    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS
LouKeHalInitializeMf2Ps2Keyboard(
    PPS2_DEVICE_OBJECT Ps2Device
){
    LouPrint("LouKeHalInitializeMf2Ps2Keyboard()\n");

    LouKeHalPs2InstallInterruptHandler(Ps2Device, (OPAQUE_PTR)LouKeMf2KbdIrqHandler, LirRoutine, (UINT64)Ps2Device);
    UINT8 Command;
    UINT8 Responce;
    Command = KBD_COMMAND_ENABLE_SCANNING;
    LOUSTATUS Status = LouKeHalPs2CommandPs2Device(Ps2Device, &Command, 1, &Responce, 1);
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Starting Scanning\n");
    }
    
    LouKeHalPs2EnableInterrupt(Ps2Device);

    LouPrint("LouKeHalInitializeMf2Ps2Keyboard() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS
DriverEntry(
    PDRIVER_OBJECT DrvObject, 
    PUNICODE_STRING RegEntry
){


    return STATUS_SUCCESS;
}