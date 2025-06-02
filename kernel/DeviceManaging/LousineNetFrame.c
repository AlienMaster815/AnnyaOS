#include <LouAPI.h>

typedef struct _LOU_NETFRAME_TRACK{
    ListHeader     Peers;
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HwDrv;
}LOU_NETFRAME_TRACK, * PLOU_NETFRAME_TRACK; 

static LOU_NETFRAME_TRACK NetFrameMasterTrack = { 0 };

LOUSTATUS LoukeRegisterNetFrameHardwareDriver(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver
){
    PLOU_NETFRAME_TRACK TmpTrack = &NetFrameMasterTrack;
    LOUSTATUS Status = STATUS_SUCCESS;
    while(TmpTrack && TmpTrack->Peers.NextHeader){
        TmpTrack = (PLOU_NETFRAME_TRACK)TmpTrack->Peers.NextHeader;
    }
    TmpTrack->HwDrv = HardwareDriver;
    Status = HardwareDriver->HardwareInitialize(HardwareDriver);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = HardwareDriver->HardwareReset(HardwareDriver);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    //TODO: Read Registry to determine if there is
    //a activation protocol eg safe mode or disabled
    //hardware
    HardwareDriver->HardwareActivate(HardwareDriver);
    TmpTrack->Peers.NextHeader = (PListHeader)LouKeMallocType(LOU_NETFRAME_TRACK, KERNEL_GENERIC_MEMORY);
    return STATUS_SUCCESS;
}