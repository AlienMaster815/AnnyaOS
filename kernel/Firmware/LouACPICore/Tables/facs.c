#include <LouACPI.h>

void LouKeAcpiInitializeFacs(void* TableBase){
    


}

LOUSTATUS LouACPIInfoQueryCheckFACS(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput){
    if((OutputID <= FACS_TABLE_DATA_START) || (OutputID >= FACS_TABLE_DATA_END)){
        return STATUS_INVALID_PARAMETER;
    }
    LOU_ACPI_TABLE_POINTER_UNION LouAcpiTable = {0};
    LouAcpiTable.Facs = LouKeAcpiGetFacsTable();
    switch(OutputID){
        case FACS_HARDWARE_SIGNATURE:{
            InfoOutput->InfoData.Facs.HardwareSignature = LouAcpiTable.Facs->HardwareSignature;
            break;
        }
        case FACS_FIRMWARE_WAKING_VECTOR:{
            if(LouAcpiTable.Facs->XFirmwareWakingVector){
                InfoOutput->InfoData.Facs.FirmwareWakingVector = LouAcpiTable.Facs->XFirmwareWakingVector;
            }else {
                InfoOutput->InfoData.Facs.FirmwareWakingVector = (uint64_t)LouAcpiTable.Facs->FirmwareWakingVector;
            }
            break;
        }
        case FACS_GLOBAL_LOCK:{
            InfoOutput->InfoData.Facs.GlobalLock = LouAcpiTable.Facs->GlobalLock;
            break;
        }
        case FACS_FLAGS:{
            InfoOutput->InfoData.Facs.FeatureFlags = LouAcpiTable.Facs->FeatureFlags;
            break;
        }
        case FACS_VERSION:{
            InfoOutput->InfoData.Facs.Version = LouAcpiTable.Facs->Version;
            break;
        }
        case FACS_OSPM_FLAGS:{
            InfoOutput->InfoData.Facs.OspmFlags = LouAcpiTable.Facs->OspmFlags;
            break;
        }
        default:
            return STATUS_NO_SUCH_DEVICE;
    }
    return STATUS_SUCCESS;
}


LOUSTATUS LouACPIInfoSetCheckFACS(LOU_ACPI_INFORMATION_ID InputID, PLOU_ACPI_INFORMATION InfoInput){
    if((InputID <= FACS_TABLE_DATA_START) || (InputID >= FACS_TABLE_DATA_END)){
        return STATUS_INVALID_PARAMETER;
    }
    LOU_ACPI_TABLE_POINTER_UNION LouAcpiTable = {0};
    LouAcpiTable.Facs = LouKeAcpiGetFacsTable();
    switch(InputID){
        case FACS_HARDWARE_SIGNATURE:{
            LouAcpiTable.Facs->HardwareSignature = InfoInput->InfoData.Facs.HardwareSignature;
            break;
        }
        case FACS_FIRMWARE_WAKING_VECTOR:{
            if(LouAcpiTable.Facs->XFirmwareWakingVector){
                LouAcpiTable.Facs->XFirmwareWakingVector = InfoInput->InfoData.Facs.FirmwareWakingVector;
            }else {
                LouAcpiTable.Facs->FirmwareWakingVector = (uint32_t)InfoInput->InfoData.Facs.FirmwareWakingVector;
            }
            break;
        }
        case FACS_GLOBAL_LOCK:{
            LouAcpiTable.Facs->GlobalLock = InfoInput->InfoData.Facs.GlobalLock;
            break;
        }
        case FACS_FLAGS:{
            LouAcpiTable.Facs->FeatureFlags = InfoInput->InfoData.Facs.FeatureFlags;
            break;
        }
        case FACS_VERSION:{
            LouAcpiTable.Facs->Version = InfoInput->InfoData.Facs.Version;
            break;
        }
        case FACS_OSPM_FLAGS:{
            LouAcpiTable.Facs->OspmFlags = InfoInput->InfoData.Facs.OspmFlags;
            break;
        }
        default:
            return STATUS_NO_SUCH_DEVICE;
    }
    return STATUS_SUCCESS;
}

