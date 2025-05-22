#include <LouACPI.h>

void LouKeInitializeFixedAcpiDescriptionTable(void* TableBase){
    //LouPrint("Initializing Fixed ACPI Description Table\n");
    UNUSED PFIXED_ACPI_DESCRIPTION_TABLE Fadt = (PFIXED_ACPI_DESCRIPTION_TABLE)TableBase;
            
    //get the table pointers
    uint64_t FirmwareControlAddress = 0;
    uint64_t DifferentialSystemsAdddress = 0;
    if((LouKeAcpiGetVersion() > 1) && (Fadt->XFirmwareControl)){
        FirmwareControlAddress = Fadt->XFirmwareControl;
    }else {
        FirmwareControlAddress = Fadt->FacsTablePhyPointer;
    }
    if((LouKeAcpiGetVersion() > 1) && (Fadt->XDsdtPhyAddress)){
        DifferentialSystemsAdddress = Fadt->XDsdtPhyAddress;
    }else {
        DifferentialSystemsAdddress = Fadt->DsdtTablePhyPointer;
    }

    //log tables and initialize them
    if(FirmwareControlAddress){
        LouKeInitializeLouACPITable((void*)FirmwareControlAddress);
    }
    if(DifferentialSystemsAdddress){
        LouKeInitializeLouACPITable((void*)DifferentialSystemsAdddress);
    }
}

LOUSTATUS LouACPIInfoQueryCheckFADT(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput){
    //if id is out of range just retrun to avoid overhead
     if((OutputID < FADT_TABLE_DATA_START) || (OutputID > FADT_TABLE_DATA_END)){
         return STATUS_INVALID_PARAMETER;
     }
     LOU_ACPI_TABLE_POINTER_UNION LouAcpiTable = {0};
     LouAcpiTable.Fadt = LouKeAcpiGetFadtTable();
     if(!LouAcpiTable.Fadt){
         return STATUS_NO_SUCH_DEVICE;
     }
     switch(OutputID){
         case PREFERED_POWER_MODE_PROFILE_INFO:{
             InfoOutput->InfoData.Fadt.PreferedPowerMode = LouAcpiTable.Fadt->PreferedPowerMode;
             break;
         }
         case SCI_8259_PIC_INT_INFO:{
             InfoOutput->InfoData.Fadt.Sci8259PicInt = LouAcpiTable.Fadt->Sci8259PicInt;
             break;
         }
         case SMI_COMMAND_PORT:{
             InfoOutput->InfoData.Fadt.SmiCommandPort.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->SmiCommandPort;
             InfoOutput->InfoData.Fadt.SmiCommandPort.eXtendedDevice = false;
             break;
         }
         case ACPI_ENABLE:{
             InfoOutput->InfoData.Fadt.AcpiEnable = LouAcpiTable.Fadt->AcpiEnable;
             break;
         }
         case ACPI_DISABLE:{
             InfoOutput->InfoData.Fadt.AcpiDisable = LouAcpiTable.Fadt->AcpiDisable;
             break;
         }
         case S4BIOS_REQUEST_VALUE:{
             InfoOutput->InfoData.Fadt.S4BiosRequestValue = LouAcpiTable.Fadt->S4BiosRequestValue;
             break;
         }
         case PROCESSOR_STATE_CONTROL_VALUE:{
             InfoOutput->InfoData.Fadt.ProcessorStateControlValue = LouAcpiTable.Fadt->ProcessorStateControlValue;
             break;
         } 
         case PM1A_EVENT_REGISTER_BLOCK_ADDRESS:{
             if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm1AEventRegisterBlock)){
                 InfoOutput->InfoData.Fadt.Pm1AEventRegister.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->XPm1AEventRegisterBlock;
                 InfoOutput->InfoData.Fadt.Pm1AEventRegister.eXtendedDevice = true;
             }else{
                 InfoOutput->InfoData.Fadt.Pm1AEventRegister.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->Pm1AEventRegisterBlockAddress;
                 InfoOutput->InfoData.Fadt.Pm1AEventRegister.eXtendedDevice = false;       
             }
             break;
         }
         case PM1B_EVENT_REGISTER_BLOCK_ADDRESS:{
             if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm1BEventRegisterBlock)){
                 InfoOutput->InfoData.Fadt.Pm1BEventRegister.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->XPm1BEventRegisterBlock;
                 InfoOutput->InfoData.Fadt.Pm1BEventRegister.eXtendedDevice = true;
             }else{
                 InfoOutput->InfoData.Fadt.Pm1BEventRegister.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->Pm1BEventRegisterBlockAddress;
                 InfoOutput->InfoData.Fadt.Pm1BEventRegister.eXtendedDevice = false;       
             }
             break;
         }
         case PM1A_CONTROL_REGISTER_BLOCK_ADDRESS:{
             if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm1AControlRegisterBlock)){
                 InfoOutput->InfoData.Fadt.Pm1AEventRegister.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->XPm1AControlRegisterBlock;
                 InfoOutput->InfoData.Fadt.Pm1AEventRegister.eXtendedDevice = true;
             }else{
                 InfoOutput->InfoData.Fadt.Pm1AControlRegister.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->Pm1AControlRegisterBlockAddress;
                 InfoOutput->InfoData.Fadt.Pm1AControlRegister.eXtendedDevice = false;       
             }
             break;
         }
         case PM1B_CONTROL_REGISTER_BLOCK_ADDRESS: {
             if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm1BControlRegisterBlock)) {  // <-- should be B not A
                 InfoOutput->InfoData.Fadt.Pm1BControlRegister.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->XPm1BControlRegisterBlock;
                 InfoOutput->InfoData.Fadt.Pm1BControlRegister.eXtendedDevice = true;
             } else {
                 InfoOutput->InfoData.Fadt.Pm1BControlRegister.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->Pm1BControlRegisterBlockAddress;
                 InfoOutput->InfoData.Fadt.Pm1BControlRegister.eXtendedDevice = false;
             }
             break;
         }        
         case PM2_CONTROL_REGISTER_BLOCK_ADDRESS:{
             if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm2ControlRegisterBlock)){
                 InfoOutput->InfoData.Fadt.Pm2ControlRegister.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->XPm2ControlRegisterBlock;
                 InfoOutput->InfoData.Fadt.Pm2ControlRegister.eXtendedDevice = true;
             }else{
                 InfoOutput->InfoData.Fadt.Pm2ControlRegister.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->Pm2ControlRegisterBlockAddress;
                 InfoOutput->InfoData.Fadt.Pm2ControlRegister.eXtendedDevice = false;       
             }
             break;
         }
         case PM_TIMER_CONTROL_REGISTER_BLOCK:{
             if(NonZeroGasValue(&LouAcpiTable.Fadt->XPmTimerRegisterBlock)){
                 InfoOutput->InfoData.Fadt.PmTimerControlRegister.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->XPmTimerRegisterBlock;
                 InfoOutput->InfoData.Fadt.PmTimerControlRegister.eXtendedDevice = true;
             }else{
                 InfoOutput->InfoData.Fadt.PmTimerControlRegister.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->PmTimerControlRegisterBlock;
                 InfoOutput->InfoData.Fadt.PmTimerControlRegister.eXtendedDevice = false;       
             }
             break;
         }
         case GENERAL_PURPOSE_EVENT_BLOCK0:{
             if(NonZeroGasValue(&LouAcpiTable.Fadt->XGeneralPurposeEvent0)){
                 InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock0.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->XGeneralPurposeEvent0;
                 InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock0.eXtendedDevice = true;
             }else{
                 InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock0.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->GeneralPurposeEventBlock0;
                 InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock0.eXtendedDevice = false;       
             }
             break;
         }
         case GENERAL_PURPOSE_EVENT_BLOCK1:{
             if(NonZeroGasValue(&LouAcpiTable.Fadt->XGeneralPurposeEvent1)){
                 InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock1.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->XGeneralPurposeEvent1;
                 InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock1.eXtendedDevice = true;
             }else{
                 InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock1.HwDeviceData.StandardDevice = LouAcpiTable.Fadt->GeneralPurposeEventBlock1;
                 InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock1.eXtendedDevice = false;       
             }
             break;
         }
         case PM1_EVENT_LENGTH:{
             InfoOutput->InfoData.Fadt.Pm1EventLength = LouAcpiTable.Fadt->Pm1EventLength;
             break;
         }
         case PM1_CONTROL_LENGTH:{
             InfoOutput->InfoData.Fadt.Pm2ControlLength = LouAcpiTable.Fadt->Pm2ControlLength;
             break;
         }
         case PM2_CONTROL_LENGTH:{
             InfoOutput->InfoData.Fadt.Pm2ControlLength = LouAcpiTable.Fadt->Pm2ControlLength;
             break;
         }
         case PM_TIMER_LENGTH:{
             InfoOutput->InfoData.Fadt.PmTimerLength = LouAcpiTable.Fadt->PmTimerLength;
             break;
         }
         case GENERAL_PURPOSE_EVENT_BLOCK0_LENGTH:{
             InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock0Length = LouAcpiTable.Fadt->GeneralPurposeEventBlock0Length;
             break;
         }
         case GENERAL_PURPOSE_EVENT_BLOCK1_LENGTH:{
             InfoOutput->InfoData.Fadt.GeneralPurposeEventBlock1Length = LouAcpiTable.Fadt->GeneralPurposeEventBlock1Length;
             break;
         }
         case GENERAL_PURPOSE_EVENT_BASE:{
             InfoOutput->InfoData.Fadt.GeneralPurposeEventBase = LouAcpiTable.Fadt->GeneralPurposeEventBase;
             break;
         }
         case CST_COUNT:{
             InfoOutput->InfoData.Fadt.CstCount = LouAcpiTable.Fadt->CstCount;
             break;
         }
         case PM_LEVEL_2_LATENCY:{
             InfoOutput->InfoData.Fadt.PmLevel2Latency = LouAcpiTable.Fadt->PmLevel2Latency;
             break;
         }
         case PM_LEVEL_3_LATENCY:{
             InfoOutput->InfoData.Fadt.PmLevel3Latency = LouAcpiTable.Fadt->PmLevel3Latency;
             break;
         }
         case FADT_FLUSH_SIZE:{
             InfoOutput->InfoData.Fadt.FlushSize = LouAcpiTable.Fadt->FlushSize;
             break;
         }
         case FADT_FLUSH_STRIDE:{
             InfoOutput->InfoData.Fadt.FlushStride = LouAcpiTable.Fadt->FlushStride;
             break;
         }
         case FADT_DUTY_OFFSET:{
             InfoOutput->InfoData.Fadt.DutyOffset = LouAcpiTable.Fadt->DutyOffset;
             break;
         }
         case FADT_DUTY_WIDTH:{
             InfoOutput->InfoData.Fadt.DutyWidth = LouAcpiTable.Fadt->DutyWidth;
             break;
         }
         case FADT_DAY_ALARM:{
             InfoOutput->InfoData.Fadt.DayAlarm = LouAcpiTable.Fadt->DayAlarm;
             break;
         }
         case FADT_MONTH_ALARM:{
             InfoOutput->InfoData.Fadt.MonthAlarm = LouAcpiTable.Fadt->MonthAlarm;
             break;
         }
         case FADT_CENTURY:{
             InfoOutput->InfoData.Fadt.Century = LouAcpiTable.Fadt->Century;
             break;
         }
         case FADT_IAPC_BOOT_ARCH:{
             InfoOutput->InfoData.Fadt.IAPCBootArch = LouAcpiTable.Fadt->IAPCBootArch;
             break;
         }
         case FADT_FEATURE_FLAGS:{
             InfoOutput->InfoData.Fadt.FeatureFlags = LouAcpiTable.Fadt->FeatureFlags;
             break;
         }
         case FADT_RESET_REGISTER:{
             InfoOutput->InfoData.Fadt.ResetRegister.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->ResetRegister;
             InfoOutput->InfoData.Fadt.ResetRegister.eXtendedDevice = true;
             break;
         }
         case FADT_RESET_VALUE:{
             InfoOutput->InfoData.Fadt.ResetValue = LouAcpiTable.Fadt->ResetValue;
             break;
         }
         case FADT_ARM_BOOT_ARCH:{
             InfoOutput->InfoData.Fadt.ArmBootArch = LouAcpiTable.Fadt->ArmBootArch;
             break;
         }
         case FADT_MINOR_VERSION:{
             InfoOutput->InfoData.Fadt.FadtMinorVersion = LouAcpiTable.Fadt->FadtMinorVersion;
             break;
         }
         case FADT_SLEEP_STATUS_REGISTER : {
             InfoOutput->InfoData.Fadt.SleepStatusRegister.HwDeviceData.eXtendedDevice = LouAcpiTable.Fadt->SleepStatusRegister;
             InfoOutput->InfoData.Fadt.SleepStatusRegister.eXtendedDevice = true;
             break;
         }
         case FADT_HYPERVISOR_VENDOR_ID:{
             InfoOutput->InfoData.Fadt.HypervisorVendorIdentity = LouAcpiTable.Fadt->HypervisorVendorIdentity;
             break;
         }
         default:
             return STATUS_INVALID_PARAMETER;
     }
     return STATUS_SUCCESS;
 }

LOUSTATUS LouACPIInfoSetCheckFADT(LOU_ACPI_INFORMATION_ID InputID ,PLOU_ACPI_INFORMATION InfoInput){
    //if id is out of range just retrun to avoid overhead
    if((InputID <= FADT_TABLE_DATA_START) || (InputID >= FADT_TABLE_DATA_END)){
        return STATUS_INVALID_PARAMETER;
    }
    LOU_ACPI_TABLE_POINTER_UNION LouAcpiTable = {0};
    LouAcpiTable.Fadt = LouKeAcpiGetFadtTable();
    if(!LouAcpiTable.Fadt){
        return STATUS_NO_SUCH_DEVICE;
    }
    switch(InputID){
        case PREFERED_POWER_MODE_PROFILE_INFO:{
            LouAcpiTable.Fadt->PreferedPowerMode = InfoInput->InfoData.Fadt.PreferedPowerMode;
            break;
        }
        case SCI_8259_PIC_INT_INFO:{
            LouAcpiTable.Fadt->Sci8259PicInt = InfoInput->InfoData.Fadt.Sci8259PicInt;
            break;
        }
        case SMI_COMMAND_PORT:{
            LouAcpiTable.Fadt->SmiCommandPort = InfoInput->InfoData.Fadt.SmiCommandPort.HwDeviceData.StandardDevice;
            break;
        }
        case ACPI_ENABLE:{
            LouAcpiTable.Fadt->AcpiEnable = InfoInput->InfoData.Fadt.AcpiEnable;
            break;
        }
        case ACPI_DISABLE:{
            LouAcpiTable.Fadt->AcpiDisable = InfoInput->InfoData.Fadt.AcpiDisable;
            break;
        }
        case S4BIOS_REQUEST_VALUE:{
            LouAcpiTable.Fadt->S4BiosRequestValue = InfoInput->InfoData.Fadt.S4BiosRequestValue;
            break;
        }
        case PROCESSOR_STATE_CONTROL_VALUE:{
            LouAcpiTable.Fadt->ProcessorStateControlValue = InfoInput->InfoData.Fadt.ProcessorStateControlValue;
            break;
        } 
        case PM1A_EVENT_REGISTER_BLOCK_ADDRESS:{
            if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm1AEventRegisterBlock)){
                LouAcpiTable.Fadt->XPm1AEventRegisterBlock = InfoInput->InfoData.Fadt.Pm1AEventRegister.HwDeviceData.eXtendedDevice;
            }else{
                LouAcpiTable.Fadt->Pm1AEventRegisterBlockAddress = InfoInput->InfoData.Fadt.Pm1AEventRegister.HwDeviceData.StandardDevice;
            }
            break;
        }
        case PM1B_EVENT_REGISTER_BLOCK_ADDRESS:{
            if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm1BEventRegisterBlock)){
                LouAcpiTable.Fadt->XPm1BEventRegisterBlock = InfoInput->InfoData.Fadt.Pm1BEventRegister.HwDeviceData.eXtendedDevice;
            }else{
                LouAcpiTable.Fadt->Pm1BEventRegisterBlockAddress = InfoInput->InfoData.Fadt.Pm1BEventRegister.HwDeviceData.StandardDevice;
            }
            break;
        }
        case PM1A_CONTROL_REGISTER_BLOCK_ADDRESS:{
            if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm1AControlRegisterBlock)){
                LouAcpiTable.Fadt->XPm1AControlRegisterBlock = InfoInput->InfoData.Fadt.Pm1AEventRegister.HwDeviceData.eXtendedDevice;
            }else{
                LouAcpiTable.Fadt->Pm1AControlRegisterBlockAddress = InfoInput->InfoData.Fadt.Pm1AControlRegister.HwDeviceData.StandardDevice;
            }
            break;
        }
        case PM1B_CONTROL_REGISTER_BLOCK_ADDRESS: {
            if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm1BControlRegisterBlock)) {  // <-- should be B not A
                LouAcpiTable.Fadt->XPm1BControlRegisterBlock = InfoInput->InfoData.Fadt.Pm1BControlRegister.HwDeviceData.eXtendedDevice;
            } else {
                LouAcpiTable.Fadt->Pm1BControlRegisterBlockAddress = InfoInput->InfoData.Fadt.Pm1BControlRegister.HwDeviceData.StandardDevice;
            }
            break;
        }        
        case PM2_CONTROL_REGISTER_BLOCK_ADDRESS:{
            if(NonZeroGasValue(&LouAcpiTable.Fadt->XPm2ControlRegisterBlock)){
                LouAcpiTable.Fadt->XPm2ControlRegisterBlock = InfoInput->InfoData.Fadt.Pm2ControlRegister.HwDeviceData.eXtendedDevice;
            }else{
                LouAcpiTable.Fadt->Pm2ControlRegisterBlockAddress = InfoInput->InfoData.Fadt.Pm2ControlRegister.HwDeviceData.StandardDevice;
            }
            break;
        }
        case PM_TIMER_CONTROL_REGISTER_BLOCK:{
            if(NonZeroGasValue(&LouAcpiTable.Fadt->XPmTimerRegisterBlock)){
                LouAcpiTable.Fadt->XPmTimerRegisterBlock = InfoInput->InfoData.Fadt.PmTimerControlRegister.HwDeviceData.eXtendedDevice;
            }else{
                LouAcpiTable.Fadt->PmTimerControlRegisterBlock = InfoInput->InfoData.Fadt.PmTimerControlRegister.HwDeviceData.StandardDevice;
            }
            break;
        }
        case GENERAL_PURPOSE_EVENT_BLOCK0:{
            if(NonZeroGasValue(&LouAcpiTable.Fadt->XGeneralPurposeEvent0)){
                LouAcpiTable.Fadt->XGeneralPurposeEvent0 = InfoInput->InfoData.Fadt.GeneralPurposeEventBlock0.HwDeviceData.eXtendedDevice;
            }else{
                LouAcpiTable.Fadt->GeneralPurposeEventBlock0 = InfoInput->InfoData.Fadt.GeneralPurposeEventBlock0.HwDeviceData.StandardDevice;
            }
            break;
        }
        case GENERAL_PURPOSE_EVENT_BLOCK1:{
            if(NonZeroGasValue(&LouAcpiTable.Fadt->XGeneralPurposeEvent1)){
                LouAcpiTable.Fadt->XGeneralPurposeEvent1 = InfoInput->InfoData.Fadt.GeneralPurposeEventBlock1.HwDeviceData.eXtendedDevice;
            }else{
                LouAcpiTable.Fadt->GeneralPurposeEventBlock1 = InfoInput->InfoData.Fadt.GeneralPurposeEventBlock1.HwDeviceData.StandardDevice;
            }
            break;
        }
        case PM1_EVENT_LENGTH:{
            LouAcpiTable.Fadt->Pm1EventLength = InfoInput->InfoData.Fadt.Pm1EventLength;
            break;
        }
        case PM1_CONTROL_LENGTH:{
            LouAcpiTable.Fadt->Pm2ControlLength = InfoInput->InfoData.Fadt.Pm2ControlLength;
            break;
        }
        case PM2_CONTROL_LENGTH:{
            LouAcpiTable.Fadt->Pm2ControlLength = InfoInput->InfoData.Fadt.Pm2ControlLength;
            break;
        }
        case PM_TIMER_LENGTH:{
            LouAcpiTable.Fadt->PmTimerLength = InfoInput->InfoData.Fadt.PmTimerLength;
            break;
        }
        case GENERAL_PURPOSE_EVENT_BLOCK0_LENGTH:{
            LouAcpiTable.Fadt->GeneralPurposeEventBlock0Length = InfoInput->InfoData.Fadt.GeneralPurposeEventBlock0Length;
            break;
        }
        case GENERAL_PURPOSE_EVENT_BLOCK1_LENGTH:{
            LouAcpiTable.Fadt->GeneralPurposeEventBlock1Length = InfoInput->InfoData.Fadt.GeneralPurposeEventBlock1Length;
            break;
        }
        case GENERAL_PURPOSE_EVENT_BASE:{
            LouAcpiTable.Fadt->GeneralPurposeEventBase = InfoInput->InfoData.Fadt.GeneralPurposeEventBase;
            break;
        }
        case CST_COUNT:{
            LouAcpiTable.Fadt->CstCount = InfoInput->InfoData.Fadt.CstCount;
            break;
        }
        case PM_LEVEL_2_LATENCY:{
            LouAcpiTable.Fadt->PmLevel2Latency = InfoInput->InfoData.Fadt.PmLevel2Latency;
            break;
        }
        case PM_LEVEL_3_LATENCY:{
            LouAcpiTable.Fadt->PmLevel3Latency = InfoInput->InfoData.Fadt.PmLevel3Latency;
            break;
        }
        case FADT_FLUSH_SIZE:{
            LouAcpiTable.Fadt->FlushSize = InfoInput->InfoData.Fadt.FlushSize;
            break;
        }
        case FADT_FLUSH_STRIDE:{
            LouAcpiTable.Fadt->FlushStride = InfoInput->InfoData.Fadt.FlushStride;
            break;
        }
        case FADT_DUTY_OFFSET:{
            LouAcpiTable.Fadt->DutyOffset = InfoInput->InfoData.Fadt.DutyOffset;
            break;
        }
        case FADT_DUTY_WIDTH:{
            LouAcpiTable.Fadt->DutyWidth = InfoInput->InfoData.Fadt.DutyWidth;
            break;
        }
        case FADT_DAY_ALARM:{
            LouAcpiTable.Fadt->DayAlarm = InfoInput->InfoData.Fadt.DayAlarm;
            break;
        }
        case FADT_MONTH_ALARM:{
            LouAcpiTable.Fadt->MonthAlarm = InfoInput->InfoData.Fadt.MonthAlarm;
            break;
        }
        case FADT_CENTURY:{
            LouAcpiTable.Fadt->Century = InfoInput->InfoData.Fadt.Century;
            break;
        }
        case FADT_IAPC_BOOT_ARCH:{
            LouAcpiTable.Fadt->IAPCBootArch = InfoInput->InfoData.Fadt.IAPCBootArch;
            break;
        }
        case FADT_FEATURE_FLAGS:{
            LouAcpiTable.Fadt->FeatureFlags = InfoInput->InfoData.Fadt.FeatureFlags;
            break;
        }
        case FADT_RESET_REGISTER:{
            LouAcpiTable.Fadt->ResetRegister = InfoInput->InfoData.Fadt.ResetRegister.HwDeviceData.eXtendedDevice;
            break;
        }
        case FADT_RESET_VALUE:{
            LouAcpiTable.Fadt->ResetValue = InfoInput->InfoData.Fadt.ResetValue;
            break;
        }
        case FADT_ARM_BOOT_ARCH:{
            LouAcpiTable.Fadt->ArmBootArch = InfoInput->InfoData.Fadt.ArmBootArch;
            break;
        }
        case FADT_MINOR_VERSION:{
            LouAcpiTable.Fadt->FadtMinorVersion = InfoInput->InfoData.Fadt.FadtMinorVersion;
            break;
        }
        case FADT_SLEEP_STATUS_REGISTER : {
            LouAcpiTable.Fadt->SleepStatusRegister = InfoInput->InfoData.Fadt.SleepStatusRegister.HwDeviceData.eXtendedDevice;
            break;
        }
        case FADT_HYPERVISOR_VENDOR_ID:{
            LouAcpiTable.Fadt->HypervisorVendorIdentity = InfoInput->InfoData.Fadt.HypervisorVendorIdentity;
            break;
        }
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}
