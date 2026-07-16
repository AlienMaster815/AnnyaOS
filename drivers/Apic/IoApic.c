#include "ApicInternals.h"

#define IO_APIC_ID_OFFSET           0
#define IO_APIC_VERSION_OFFSET      1
#define IO_APIC_ARBITRATION_OFFSET  2
#define IO_APIC_IRQWINDOW_OFFSET(x) ((x * 2 + 0x10) + 1)

static UINT32 ReadIoApicRegister(
    PVOID ApicBase, 
    UINT8 Register
){
    UINT32 volatile* IoApic = (UINT32 volatile*)ApicBase;
    IoApic[0] = Register;
    return IoApic[4];
}

static void WriteIoApicRegister(
    PVOID   ApicBase, 
    UINT8   Register, 
    UINT32  Value
){
    UINT32 volatile* IoApic = (UINT32 volatile*)ApicBase;
    IoApic[0] = Register;
    IoApic[4] = Value;
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetIoApicIdRegisterFromObject(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             VersionOut
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    if(ApicDeviceObject->ApicObjectType != IO_APIC_OBJECT_TYPE){
        ApicHalDbgPrint("APIC.SYS:WARNING:Apic Device:%h Is Not An Io Apic In Io Apic Function:ApicHalGetIoApicIdRegisterFromObject()", ApicDeviceObject);
        return STATUS_INVALID_PARAMETER;
    }
    UINT32 Register = ReadIoApicRegister(ApicDeviceObject->IoApicObject.ApicBase, IO_APIC_ID_OFFSET);
    if(VersionOut){
        *VersionOut = ((Register >> 24) & 0x0F);
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS
ApicHalGetIoApicVersionRegisterFromObject(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Version,
    UINT32*             MaxRedirections
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    if(ApicDeviceObject->ApicObjectType != IO_APIC_OBJECT_TYPE){
        ApicHalDbgPrint("APIC.SYS:WARNING:Apic Device:%h Is Not An Io Apic In Io Apic Function:ApicHalGetIoApicVersionRegisterFromObject()", ApicDeviceObject);
        return STATUS_INVALID_PARAMETER;
    }
    UINT32 Register = ReadIoApicRegister(ApicDeviceObject->IoApicObject.ApicBase, IO_APIC_VERSION_OFFSET);
    if(Version){
        *Version = Register & 0xFF;
    }
    if(MaxRedirections){
        *MaxRedirections = (Register >> 16) & 0xFF;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetIoApicArbitrationIdRegisterFromObject(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Id
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    if(ApicDeviceObject->ApicObjectType != IO_APIC_OBJECT_TYPE){
        ApicHalDbgPrint("APIC.SYS:WARNING:Apic Device:%h Is Not An Io Apic In Io Apic Function:ApicHalGetIoApicArbitrationIdRegisterFromObject()", ApicDeviceObject);
        return STATUS_INVALID_PARAMETER;
    }
    UINT32 Register = ReadIoApicRegister(ApicDeviceObject->IoApicObject.ApicBase, IO_APIC_ARBITRATION_OFFSET);
    if(Id){
        *Id = (Register >> 24) & 0x0F;
    }
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetIoApicRedirectionEntryFromObjectEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject, 
    UINT64              Entry,
    UINT64*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    if(ApicDeviceObject->ApicObjectType != IO_APIC_OBJECT_TYPE){
        ApicHalDbgPrint("APIC.SYS:WARNING:Apic Device:%h Is Not An Io Apic In Io Apic Function:ApicHalGetIoApicRedirectionEntryFromObjectEx()", ApicDeviceObject);
        return STATUS_INVALID_PARAMETER;
    }  
    UINT8 Offset = IO_APIC_IRQWINDOW_OFFSET(Entry);
    *Out = (UINT64)ReadIoApicRegister(ApicDeviceObject->IoApicObject.ApicBase, Offset);
    *Out |= (UINT64)ReadIoApicRegister(ApicDeviceObject->IoApicObject.ApicBase, Offset + 1) << 32;
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetIoApicRedirectionEntryFromObject(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject, 
    UINT64                      Entry,
    UINT32*                     Destination,
    BOOLEAN*                    Masked,
    IO_APIC_TRIGGER_MODE*       TriggerMode,
    BOOLEAN*                    IrrSet,
    IO_APIC_PIN_POLARITY*       PinPolarity,
    BOOLEAN*                    InterruptPending,
    IO_APIC_DESTINATION_MODE*   DestinationMode,
    IO_APIC_DELIVERY_MODE*      DeliveryMode,
    UINT8*                      Vector
){
    UINT64 Register;
    LOUSTATUS Status = ApicHalGetIoApicRedirectionEntryFromObjectEx(ApicDeviceObject, Entry, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(Destination){
        *Destination = ((Register >> 56) & 0xFF);
    }
    if(Masked){
        *Masked = (Register & (1 << 16)) ? true : false;
    }
    if(TriggerMode){
        *TriggerMode = (IO_APIC_TRIGGER_MODE)((Register >> 15) & 0x01);
    }
    if(IrrSet){
        *IrrSet = (Register & (1 << 14)) ? true : false;
    }
    if(PinPolarity){
        *PinPolarity = (IO_APIC_PIN_POLARITY)((Register >> 13) & 0x01);
    }
    if(InterruptPending){
        *InterruptPending = (Register & (1 << 12)) ? true : false;
    }
    if(DestinationMode){
        *DestinationMode = (IO_APIC_DESTINATION_MODE)((Register >> 11) & 0x01);
    }
    if(DeliveryMode){
        *DeliveryMode = (IO_APIC_DESTINATION_MODE)((Register >> 8) & 0x07);
    }
    if(Vector){
        *Vector = Register & 0xFF;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetIoApicRedirectionEntryFromObjectEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject, 
    UINT64              Entry,
    UINT64              In
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    if(ApicDeviceObject->ApicObjectType != IO_APIC_OBJECT_TYPE){
        ApicHalDbgPrint("APIC.SYS:WARNING:Apic Device:%h Is Not An Io Apic In Io Apic Function:ApicHalSetIoApicRedirectionEntryFromObjectEx()", ApicDeviceObject);
        return STATUS_INVALID_PARAMETER;
    }  
    UINT8 Offset = IO_APIC_IRQWINDOW_OFFSET(Entry);
    WriteIoApicRegister(ApicDeviceObject->IoApicObject.ApicBase, Offset, In & UINT32_MAX);
    WriteIoApicRegister(ApicDeviceObject->IoApicObject.ApicBase, Offset + 1, (In >> 32) & UINT32_MAX);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetIoApicRedirectionEntryFromObject(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject, 
    UINT64                      Entry,
    UINT32*                     Destination,
    BOOLEAN*                    Masked,
    IO_APIC_TRIGGER_MODE*       TriggerMode,
    IO_APIC_PIN_POLARITY*       PinPolarity,
    IO_APIC_DESTINATION_MODE*   DestinationMode,
    IO_APIC_DELIVERY_MODE*      DeliveryMode,
    UINT8*                      Vector
){
    UINT64 Register;
    LOUSTATUS Status = ApicHalGetIoApicRedirectionEntryFromObjectEx(ApicDeviceObject, Entry, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(Destination){
        Register = (Register & ~(0xFFULL << 56)) | (((UINT64)*Destination & 0xFF) << 56);
    }
    if(Masked){
        Register &= ~(1 << 16);
        if(*Masked){
            Register |= (1 << 16);
        }
    }
    if(TriggerMode){
        Register = (Register & ~(1 << 15)) | (((UINT32)*TriggerMode & 0x01) << 15); 
    }
    if(PinPolarity){
        Register = (Register & ~(0x01 << 13)) | (((UINT32)*PinPolarity & 0x01) << 13);
    }
    if(DestinationMode){
        Register = (Register & ~(0x01 << 11)) | (((UINT32)*DestinationMode & 0x01) << 11);
    }
    if(DeliveryMode){
        Register = (Register & ~(0x07 << 8)) | (((UINT32)*DeliveryMode & 0x07) << 8);
    }
    if(Vector){
        Register = (Register & ~0xFF) | *Vector;
    }
    return ApicHalSetIoApicRedirectionEntryFromObjectEx(ApicDeviceObject, Entry, Register);
}