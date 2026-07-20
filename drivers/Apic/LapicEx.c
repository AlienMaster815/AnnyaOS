#include "ApicInternals.h"
#include "X1ApicInternals.h"
#include "X2ApicInternals.h"

LOUSTATUS 
ApicHalGetApicIdRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicIdRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicVersionRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicVersionRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicTaskPriorityRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicTaskPriorityRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicArbitrationPriorityRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into X1 Apic Only Function:ApicHalGetApicArbitrationPriorityRegisterEx()\n", ApicDeviceObject);
            return STATUS_NOT_SUPPORTED;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicArbitrationPriorityRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicProcessorPriorityRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicProcessorPriorityRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }    
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicRemoteReadRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into X1 Apic Only Function:ApicHalGetApicRemoteReadRegisterEx()\n", ApicDeviceObject);
            return STATUS_NOT_SUPPORTED;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicRemoteReadRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLogicalDestinationRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLogicalDestinationRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicDestinationFormatRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into X1 Apic Only Function:ApicHalGetApicDestinationFormatRegisterEx()\n", ApicDeviceObject);
            return STATUS_NOT_SUPPORTED;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicDestinationFormatRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicSpuriousInterruptVectorRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicSpuriousInterruptVectorRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS ApicHalGetApicInServiceRegisterX32Ex(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicInServiceRegisterX32Ex()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS ApicHalGetApicTriggerModeRegisterX32Ex(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicTriggerModeRegisterX32Ex()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS ApicHalGetApicInterruptRequestRegisterX32Ex(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicInterruptRequestRegisterX32Ex()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicErrorStatusRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicErrorStatusRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtCmciRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtCmciRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicInterruptCommandRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicInterruptCommandRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtTimerRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtTimerRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtThermalSensorRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtThermalSensorRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtPerformanceMonitoringCountersRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtPerformanceMonitoringCountersRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtLint0RegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtLint0RegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtLint1RegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtLint1RegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicLvtErrorRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicLvtErrorRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicInitialCountRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicInitialCountRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicCurrentCountRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicCurrentCountRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
ApicHalGetApicDivideConfigurationRegisterEx(
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
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicDivideConfigurationRegisterEx()\n", ApicDeviceObject);
        default:
            *Out = 0;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalSetApicIdRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicIdRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into Function With Depreciated Apic Feature:ApicHalSetApicIdRegisterEx()\n", ApicDeviceObject);
            return STATUS_NOT_SUPPORTED;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicIdRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalSetApicTaskPriorityRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
      if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicTaskPriorityRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicTaskPriorityRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicTaskPriorityRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicEndOfInterruptRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
      if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicEndOfInterruptRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicEndOfInterruptRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicEndOfInterruptRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}


LOUSTATUS 
ApicHalSetApicLogicalDestinationRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
      if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicLogicalDestinationRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into Function With Depreciated Apic Feature:ApicHalSetApicLogicalDestinationRegisterEx()\n", ApicDeviceObject);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicLogicalDestinationRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicDestinationFormatRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
      if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicDestinationFormatRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:X2 Apic Device:%h Input Into Function With Depreciated Apic Feature:ApicHalSetApicDestinationFormatRegisterEx()\n", ApicDeviceObject);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicDestinationFormatRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicSpuriousInterruptVectorRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
      if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicSpuriousInterruptVectorRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicSpuriousInterruptVectorRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicDestinationFormatRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicErrorStatusRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
      if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicErrorStatusRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicErrorStatusRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicErrorStatusRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicLvtCmciRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicLvtCmciRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicLvtCmciRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicLvtCmciRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicInterruptCommandRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT64              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicInterruptCommandRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicInterruptCommandRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicInterruptCommandRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicLvtTimerRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicLvtTimerRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicLvtTimerRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicLvtTimerRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicLvtThermalSensorRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicLvtThermalSensorRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicLvtThermalSensorRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicLvtThermalSensorRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicLvtPerformanceMonitoringCountersRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicLvtPerformanceMonitoringCountersRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicLvtPerformanceMonitoringCountersRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicLvtLint0RegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicLvtLint0Register(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicLvtLint0Register(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicLvtLint0RegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicLvtLint1RegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicLvtLint1Register(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicLvtLint1Register(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicLvtLint1RegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}


LOUSTATUS 
ApicHalSetApicLvtErrorRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicLvtErrorRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicLvtErrorRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicLvtErrorRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicInitialCountRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicInitialCountRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicInitialCountRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicInitialCountRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

LOUSTATUS 
ApicHalSetApicDivideConfigurationRegisterEx(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32              Value
){
    if(!ApicDeviceObject){
        return STATUS_INVALID_PARAMETER;
    }
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX1ApicDivideConfigurationRegister(ApicDeviceObject->X1ApicObject.ApicBase, Value);
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            ApicHalSetX2ApicDivideConfigurationRegister(Value);
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalSetApicDivideConfigurationRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;  
}

