#include "Ps2Mouse.h"



static void LouKePs2MouseIrqHandler(PPS2_DEVICE_OBJECT Ps2Device){ 
    if(!(LouKeHalPs2CheckControllerStatus() & (0x20))){
        return;
    }
    PPS2_MOUSE_PRIVATE_DATA Private = (PPS2_MOUSE_PRIVATE_DATA)Ps2Device->DriverPrivateData;
    LouKeHalPs2ReadDeviceBuffer(Ps2Device, &Private->Data[Private->Offset], 1);

    Private->Offset = (Private->Offset + 1) % 3;
    
    if(!Private->Offset){
        UINT8* Data = Private->Data;
        UINT8 State = Data[0];
        UINT8 Dx = Data[1];
        UINT8 Dy = Data[2];

        INT64 X = (INT64)Dx - ((State << 4) & 0x100);
        INT64 Y = (INT64)Dy - ((State << 3) & 0x100);

        LouKeMouseUpdateInput(
            Private->MouseMessage,
            X, -Y,
            State & (1 << 1), State & (1)
        );

    }

}


DRIVER_EXPORT
LOUSTATUS
LouKeHalInitializePs2Mouse(
    PPS2_DEVICE_OBJECT Ps2Device
){
    LouPrint("LouKeHalInitializePs2Mouse()\n");

    Ps2Device->DriverPrivateData = (PVOID)LouKeMallocType(PS2_MOUSE_PRIVATE_DATA, KERNEL_GENERIC_MEMORY);
    PPS2_MOUSE_PRIVATE_DATA Private = (PPS2_MOUSE_PRIVATE_DATA)Ps2Device->DriverPrivateData;

    Private->Scaling = MOUSE_COMMAND_SET_SCALLING_1_1;
    Private->Resolution = MOUSE_RESOLUTION_1_COUNT_MM;
    LouKeHalPs2InstallInterruptHandler(Ps2Device, (void(*)(uint64_t))LouKePs2MouseIrqHandler);
    UINT8 Command;
    Command = Private->Scaling;
    UINT8 Responce;
    LouKeHalPs2CommandPs2Device(Ps2Device, &Command, 1, &Responce, 1);

    Command = MOUSE_COMMAND_SET_RESOLUTION;
    LouKeHalPs2CommandPs2Device(Ps2Device, &Command, 1, &Responce, 1);

    Command = Private->Resolution;
    LouKeHalPs2CommandPs2Device(Ps2Device, &Command, 1, &Responce, 1);

    Command = MOUSE_COMMAND_ENABLE_SCANNING;
    LOUSTATUS Status = LouKeHalPs2CommandPs2Device(Ps2Device, &Command, 1, &Responce, 1);
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Starting Scanning\n");
    }

    LouKeHalPs2EnableInterrupt(Ps2Device);    

    Private->MouseMessage = LouKeMouseAllocateMessageDevice();

    LouPrint("LouKeHalInitializePs2Mouse() STATUS_SUCCESS\n");
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