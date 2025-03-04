#include <LouAPI.h>


static uint8_t GpuDevicesCount = 0x00; 

typedef struct _DrsdGpuKeyData{
    ListHeader              Neighbors;
    PDEVICE_DIRECTORY_TABLE Table;
}DrsdGpuManagmentData, * PDrsdGpuManagmentData;

static DrsdGpuManagmentData gpus = {0};

LOUSTATUS LouRegisterDrsdGraphicsDevice(
    PDEVICE_DIRECTORY_TABLE Table
){
    PDrsdGpuManagmentData Tmp = &gpus;

    for(uint8_t i = 0 ; i < GpuDevicesCount; i++){
        if(Tmp->Neighbors.NextHeader){
            Tmp = (PDrsdGpuManagmentData)Tmp->Neighbors.NextHeader;
        }else{
            Tmp->Neighbors.NextHeader = (PListHeader)LouMallocEx(sizeof(DrsdGpuManagmentData), GET_ALIGNMENT(DrsdGpuManagmentData));
            Tmp = (PDrsdGpuManagmentData)Tmp->Neighbors.NextHeader;
        }
    }
    GpuDevicesCount++;
    Tmp->Table = Table;
    return STATUS_SUCCESS;
}

uint8_t LouKeDeviceManagerGetGpuCount(){
    return GpuDevicesCount;
}

PDrsdVRamObject LouKeDeviceManagerGetFBDEV(uint8_t Gpu){
    if(Gpu >= GpuDevicesCount){
        return 0x00;
    }
    PDrsdGpuManagmentData Tmp = &gpus;
    for(uint8_t i = 0 ; i < Gpu; i++){
        Tmp = (PDrsdGpuManagmentData)Tmp->Neighbors.NextHeader;
    }
    return Tmp->Table->KeyData;
}