#include "DrsdCore.h"

static 
LOUSTATUS
DrsdModeCreateStandardProperties(
    PDRSD_DEVICE    Device
){
    LOUSTATUS Status;
    //PDRSD_PROPERTY Property;

    Status = DrsdConnectorCreateStandardProperties(Device);
    if(Status != STATUS_SUCCESS){
        return Status;
    }


    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
LOUSTATUS 
DrsdModeConfigInit(
    PDRSD_DEVICE Device
){
    LOUSTATUS Status;
    LouPrint("DrsdModeConfigInit\n");

    LouKeLouQInitializeWork(&Device->ModeConfig.ConnectorFreeWork, DrsdConnectorFreeWorkFunction, &Device->ModeConfig.ConnectorFreeWork);

    Status = DrsdModeCreateStandardProperties(Device);
    if(Status != STATUS_SUCCESS){
        LouPrint("DrsdModeConfigInit:ERROR Unable To Create Standard Properties\n");
        return Status;
    }



    while(1);
    return STATUS_SUCCESS;
}