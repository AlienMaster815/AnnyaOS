#include "Ps2Bus.h"

static spinlock_t Ps2Lock = {0};
static mutex_t Ps2Mutex = {0};

LOU_BUS_OBJECT Ps2BusObjects = {0};

static PS2_DEVICE_OBJECT Ps2Devices[TOTAL_PS2_PORTS] = {0};

LOUSTATUS Ps2InitializeBus(PLOU_BUS BussClass, PLOU_BUS_OBJECT Object){
    LouPrint("PS2IO.SYS:Ps2InitializeBus()\n");
    Object->BusPrivateData = (PVOID)Ps2Devices;



    LouPrint("PS2IO.SYS:Ps2InitializeBus() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS Ps2DeInitializeBus(PLOU_BUS BussClass, PLOU_BUS_OBJECT Object){
    LouPrint("PS2IO.SYS:Ps2DeInitializeBus()\n");



    LouPrint("PS2IO.SYS:Ps2DeInitializeBus() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOU_BUS Ps2Bus = {
    .BusName = "8042 PS/2",
    .BusObjects = &Ps2BusObjects,
    .InitializeBus = Ps2InitializeBus,
    .DeInitializeBus = Ps2DeInitializeBus,
};

LOUDDK_API_ENTRY
NTSTATUS
DriverEntry(
    PDRIVER_OBJECT DrvObject, 
    PUNICODE_STRING RegEntry
){
    LouPrint("PS2IO.SYS:DriverEntry()\n");

    LouKeCreateBusClass(
        &Ps2Bus
    );

    LouPrint("PS2IO.SYS:DriverEntry() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}