#include <LouAPI.h>

typedef struct _NETFRAME_DEVICE_MANAGER_DEVICE{
    ListHeader              Neighbors;
    PDEVICE_DIRECTORY_TABLE Device;
}NETFRAME_DEVICE_MANAGER_DEVICE, * PNETFRAME_DEVICE_MANAGER_DEVICE;

static NETFRAME_DEVICE_MANAGER_DEVICE NetFrameDeviceTable = {0};
static size_t                          NetFrameDeviceCount = 0;

void LouKeNetFrameActivateNetworkDevice(PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER NetFrameDriver);

LOUSTATUS LouRegisterNetFrameDevice(PDEVICE_DIRECTORY_TABLE NetFrameDevice){
    LouPrint("Registering NetFrame Device\n");
    PNETFRAME_DEVICE_MANAGER_DEVICE TmpDevice = &NetFrameDeviceTable;
    for(size_t i = 0 ; i < NetFrameDeviceCount; i++){
        if(!TmpDevice->Neighbors.NextHeader){
            TmpDevice->Neighbors.NextHeader = (PListHeader)LouKeMallocEx(sizeof(NETFRAME_DEVICE_MANAGER_DEVICE), GET_ALIGNMENT(NETFRAME_DEVICE_MANAGER_DEVICE), KERNEL_GENERIC_MEMORY);
        }
        TmpDevice = (PNETFRAME_DEVICE_MANAGER_DEVICE)TmpDevice->Neighbors.NextHeader;
    }

    TmpDevice->Device = NetFrameDevice;

    LouPrint("NetFrame Device Registration Successfull :: Activating Device\n");

    LouKeNetFrameActivateNetworkDevice((PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER)NetFrameDevice->KeyData);

    return STATUS_SUCCESS;
}