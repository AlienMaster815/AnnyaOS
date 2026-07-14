#include "ApicInternals.h"
#include "X1ApicInternals.h"
#include "X2ApicInternals.h"

LOUSTATUS 
ApicHalGetApicIdRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject, 
    UINT32*             Out
){
    APIC_OBJECT_TYPE ObjectType;
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicIdRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicIdRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicIdRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicVersionRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicVersionRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicVersionRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicVersionRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicTaskPriorityRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicTaskPriorityRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicTaskPriorityRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicTaskPriorityRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicArbitrationPriorityRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicArbitrationPriorityRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into X1 Apic Only Function:ApicHalGetApicArbitrationPriorityRegister()\n", ApicDeviceObject);
            return STATUS_NOT_SUPPORTED;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicArbitrationPriorityRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicProcessorPriorityRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicProcessorPriorityRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicProcessorPriorityRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicProcessorPriorityRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }    
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicRemoteReadRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicRemoteReadRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into X1 Apic Only Function:ApicHalGetApicRemoteReadRegister()\n", ApicDeviceObject);
            return STATUS_NOT_SUPPORTED;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicRemoteReadRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLogicalDestinationRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicLogicalDestinationRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicLogicalDestinationRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLogicalDestinationRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicDestinationFormatRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicDestinationFormatRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into X1 Apic Only Function:ApicHalGetApicDestinationFormatRegister()\n", ApicDeviceObject);
            return STATUS_NOT_SUPPORTED;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicDestinationFormatRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicSpuriousInterruptVectorRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicSpuriousInterruptVectorRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS ApicHalGetApicInServiceRegisterX32(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    SIZE                Offset,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicInServiceRegisterX32(ApicDeviceObject->X1ApicObject.ApicBase, Offset);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicInServiceRegisterX32(Offset);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicInServiceRegisterX32()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS ApicHalGetApicTriggerModeRegisterX32(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    SIZE                Offset,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicTriggerModeRegisterX32(ApicDeviceObject->X1ApicObject.ApicBase, Offset);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicTriggerModeRegisterX32(Offset);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicTriggerModeRegisterX32()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS ApicHalGetApicInterruptRequestRegisterX32(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    SIZE                Offset,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicInterruptRequestRegisterX32(ApicDeviceObject->X1ApicObject.ApicBase, Offset);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicInterruptRequestRegisterX32(Offset);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicInterruptRequestRegisterX32()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicErrorStatusRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicErrorStatusRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicErrorStatusRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicErrorStatusRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtCmciRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicLvtCmciRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicLvtCmciRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtCmciRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicInterruptCommandRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT64*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicInterruptCommandRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicInterruptCommandRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicInterruptCommandRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtTimerRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicLvtTimerRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicLvtTimerRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtTimerRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtThermalSensorRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicLvtThermalSensorRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicLvtThermalSensorRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtThermalSensorRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtPerformanceMonitoringCountersRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtPerformanceMonitoringCountersRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtLint0Register(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicLvtLint0Register(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicLvtLint0Register();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtLint0Register()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtLint1Register(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicLvtLint1Register(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicLvtLint1Register();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtLint1Register()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtErrorRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicLvtErrorRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicLvtErrorRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtErrorRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicInitialCountRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicInitialCountRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicInitialCountRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicInitialCountRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicCurrentCountRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicCurrentCountRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicCurrentCountRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicCurrentCountRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicDivideConfigurationRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             Out
){
    if((!ApicDeviceObject) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX1ApicDivideConfigurationRegister(ApicDeviceObject->X1ApicObject.ApicBase);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            *Out = ApicHalGetX2ApicDivideConfigurationRegister();
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicDivideConfigurationRegister()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}