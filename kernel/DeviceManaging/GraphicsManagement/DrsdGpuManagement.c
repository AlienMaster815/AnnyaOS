#include <LouAPI.h>


static uint8_t GpuDevicesCount = 0x00; 

typedef struct _DrsdGpuKeyData{
    ListHeader              Neighbors;
    PDEVICE_DIRECTORY_TABLE Table;
}DrsdGpuManagmentData, * PDrsdGpuManagmentData;

static DrsdGpuManagmentData gpus = {0};

static bool LegacyGraphics = false;

static void InitializeModernGraphicsDevice(void* Device){

    PDRSD_DEVICE DrsdDevice = (PDRSD_DEVICE)Device;
    PDRSD_CONNECTOR DrsdConnector = DrsdDevice->Connectors;

    while(DrsdConnector){
        LouPrint("Initializing Connector:%h\n", DrsdConnector);

        DrsdConnector->Callbacks->ConnectorFillModes(
            DrsdConnector, 
            DrsdDevice->ModeConfiguration.MaximumWidth, 
            DrsdDevice->ModeConfiguration.MaximumHeight
        );

        DrsdConnector = (PDRSD_CONNECTOR)DrsdConnector->Peers.NextHeader;
    }

    LouPrint("InitializeModernGraphicsDevice() STATUS_SUCCESS\n");
    while(1);
}

LOUSTATUS LouRegisterDrsdGraphicsDevice(
    PDEVICE_DIRECTORY_TABLE Table
){
    PDrsdGpuManagmentData Tmp = &gpus;
    if((uint64_t)Table->PDEV == 0xFFFFFFFFFFFFFFFF){
        LegacyGraphics = true;
    }

    for(uint8_t i = 0 ; i < GpuDevicesCount; i++){
        if(((uint64_t)Tmp->Table->PDEV == 0xFFFFFFFFFFFFFFFF) || (i == 0)){
            LouKeFree(Tmp->Table);
            Tmp->Table = Table; 
            LegacyGraphics = false;
            return STATUS_SUCCESS;
        }
        if(Tmp->Neighbors.NextHeader){
            Tmp = (PDrsdGpuManagmentData)Tmp->Neighbors.NextHeader;
        }else{
            Tmp->Neighbors.NextHeader = (PListHeader)LouKeMallocEx(sizeof(DrsdGpuManagmentData), GET_ALIGNMENT(DrsdGpuManagmentData), WRITEABLE_PAGE | PRESENT_PAGE);
            Tmp = (PDrsdGpuManagmentData)Tmp->Neighbors.NextHeader;
        }
    }
    if(!LegacyGraphics){
        InitializeModernGraphicsDevice(Table->KeyData);
    }
    GpuDevicesCount++;
    Tmp->Table = Table;
    return STATUS_SUCCESS;
}

uint8_t LouKeDeviceManagerGetGpuCount(){
    return GpuDevicesCount;
}

PDrsdVRamObject LouKeDeviceManagerGetFBDEV(uint8_t Gpu){
    if(LegacyGraphics){
        if(Gpu >= GpuDevicesCount){
            return 0x00;
        }
        PDrsdGpuManagmentData Tmp = &gpus;
        for(uint8_t i = 0 ; i < Gpu; i++){
            Tmp = (PDrsdGpuManagmentData)Tmp->Neighbors.NextHeader;
        }
        return Tmp->Table->KeyData;
    }


    return 0x00;
}
