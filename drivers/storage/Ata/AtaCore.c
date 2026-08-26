#include "AtaCore.h"

/*
TODO:
    * = multiple commands under a single ATA feature
    CFA ERASE SECTORS: 
        this command is used in advance of the CFA WRITE_SECTORS_WITHOUGHT_ERASE or
        a CFA WRITE MULTIPLE WITHOUGHT ERASE command to increase execution speed  
    CFA REQUEST EXTENDED ERROR CODES:
        define error commands and create logic for error handling : ATA-ATAPI.PDF Page 80
    CFA_TRANSLATE_SECTOR:
        create structure for the Translation Information : ATA-ATAPI.PDF Page 82
    CHECK_POWER_MODE:
        handle result data : ATA-ATAPI.PDF Page 90
    DEVICE CONFIGURATION * : 
        Check over them when finished with the basics 
    IDENTIFY DEVICE:
        read all the data and behavior, implement the data and behavior: ATA-ATAPI.PDF Page 117
*/


BOOLEAN DbgPrintEn = false;

LOUSTATUS AtaCoreScsiDeviceResetHcd(PSCSI_HOST_DEVICE_OBJECT Hcd){

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreScsiDeviceResetHcd()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreScsiDevicePowerOnHcd(PSCSI_HOST_DEVICE_OBJECT Hcd){

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreScsiDevicePowerOnHcd()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreScsiDevicePowerOffHcd(PSCSI_HOST_DEVICE_OBJECT Hcd){

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreScsiDevicePowerOffHcd()\n");
    while(1);
    return STATUS_NOT_SUPPORTED;
}

LOUSTATUS AtaCoreScsiDeviceStartHcd(PSCSI_HOST_DEVICE_OBJECT Hcd){

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreScsiDeviceStartHcd()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreScsiDeviceStopHcd(PSCSI_HOST_DEVICE_OBJECT Hcd){

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreScsiDeviceStopHcd()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreScsiDeviceSendScsiCommand(PSCSI_PORT_DEVICE_OBJECT ScsiPortDevice, PSCSI_COMMAND_PACKET ScsiCommandPacket){

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreScsiDeviceSendScsiCommand()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreScsiDevicePrepScsiCommand(PSCSI_PORT_DEVICE_OBJECT ScsiPortDevice, PSCSI_COMMAND_PACKET ScsiCommandPacket){

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreScsiDevicePrepScsiCommand()\n");
    while(1);
    return STATUS_SUCCESS;
}

static SCSI_HOST_DEVICE_CALLBACKS SatCalls = {
    .ScsiDeviceResetHcd = AtaCoreScsiDeviceResetHcd,
    .ScsiDevicePowerOnHcd = AtaCoreScsiDevicePowerOnHcd,
    .ScsiDevicePowerOffHcd = AtaCoreScsiDevicePowerOffHcd,
    .ScsiDeviceStartHcd = AtaCoreScsiDeviceStartHcd,
    .ScsiDeviceStopHcd = AtaCoreScsiDeviceStopHcd,
    .ScsiDeviceSendScsiCommand = AtaCoreScsiDeviceSendScsiCommand,
    .ScsiDevicePrepScsiCommand = AtaCoreScsiDevicePrepScsiCommand,
};

static SCSI_HOST_DEVICE_DRIVER_OBJECT ScsiAtaTranslateDriver = {
    .DriverName = "Scsi to Ata Translation Layer",
    .Callbacks = &SatCalls,
};

void AtaCoreDbgPrint(char* format, ...){
    if(DbgPrintEn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}

LOUSTATUS AtaCoreEntry(){
    HANDLE AtaDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\ATA_CORE_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(AtaDebugKey, &DbgValue);
    DbgPrintEn = DbgValue ? true : false;

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreEntry()\n");

    LOUSTATUS Status = ScsiCoreRegisterScsiHostDeviceDriver(
        &ScsiAtaTranslateDriver,
        sizeof(ATA_SATDEV_PRIVATE_DATA),
        GET_ALIGNMENT(ATA_SATDEV_PRIVATE_DATA)
    );
    if(Status != STATUS_SUCCESS){
        AtaCoreDbgPrint("ATACORE.SYS:AtaCoreEntry():Unable To Register SAT Driver\n");
        return Status;
    }

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreEntry():STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}