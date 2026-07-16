#include "../ApicInternals.h"

DRIVER_EXPORT 
LOUSTATUS 
ApicHalGetLocalApicIdRegister(
    UINT32* IdOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicIdRegister(
        ApicDeviceObject,
        IdOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicVersionRegister(
    UINT32*     VersionOut,
    UINT32*     MaxLvtOut,
    BOOLEAN*    SupportsEoiSuppresionOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicVersionRegister(
        ApicDeviceObject,
        VersionOut,
        MaxLvtOut,
        SupportsEoiSuppresionOut
    );
}

DRIVER_EXPORT
LOUSTATUS
ApicHalGetLocalApicLvtTimerRegister(
    APIC_TIMER_MODE*    TimerModeOut, 
    BOOLEAN*            MaskedOut, 
    BOOLEAN*            InterruptPendingOut, 
    UINT8*              VectorOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicLvtTimerRegister(
        ApicDeviceObject,
        TimerModeOut,
        MaskedOut,
        InterruptPendingOut,
        VectorOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicLvtCmciRegister(
    BOOLEAN*                MaskedOut, 
    BOOLEAN*                InterruptPendingOut, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeOut, 
    UINT8*                  VectorOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicLvtCmciRegister(
        ApicDeviceObject,
        MaskedOut,
        InterruptPendingOut,
        DeliveryModeOut,
        VectorOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicLvtLint0Register(
    BOOLEAN*                MaskedOut, 
    APIC_TRIGGER_MODE*      TriggerModeOut, 
    BOOLEAN*                IrrSetOut, 
    APIC_IN_PIN_POLARITY*   InPinPolarityOut, 
    BOOLEAN*                InterruptPendingOut, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeOut, 
    UINT8*                  VectorOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicLvtLint0Register(
        ApicDeviceObject,
        MaskedOut,
        TriggerModeOut,
        IrrSetOut,
        InPinPolarityOut,
        InterruptPendingOut,
        DeliveryModeOut,
        VectorOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicLvtLint1Register(
    BOOLEAN*                MaskedOut, 
    APIC_TRIGGER_MODE*      TriggerModeOut, 
    BOOLEAN*                IrrSetOut, 
    APIC_IN_PIN_POLARITY*   InPinPolarityOut, 
    BOOLEAN*                InterruptPendingOut, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeOut, 
    UINT8*                  VectorOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicLvtLint1Register(
        ApicDeviceObject,
        MaskedOut,
        TriggerModeOut,
        IrrSetOut,
        InPinPolarityOut,
        InterruptPendingOut,
        DeliveryModeOut,
        VectorOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicLvtErrorRegister(
    BOOLEAN*                MaskedOut, 
    BOOLEAN*                InterruptPendingOut, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeOut, 
    UINT8*                  VectorOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicLvtErrorRegister(
        ApicDeviceObject,
        MaskedOut,
        InterruptPendingOut,
        DeliveryModeOut,
        VectorOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicLvtPerformanceMonitoringCountersRegister(
    BOOLEAN*                MaskedOut, 
    BOOLEAN*                InterruptPendingOut, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeOut, 
    UINT8*                  VectorOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicLvtPerformanceMonitoringCountersRegister(
        ApicDeviceObject,
        MaskedOut,
        InterruptPendingOut,
        DeliveryModeOut,
        VectorOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicLvtThermalSensorRegister(
    BOOLEAN*                MaskedOut, 
    BOOLEAN*                InterruptPendingOut, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeOut, 
    UINT8*                  VectorOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicLvtThermalSensorRegister(
        ApicDeviceObject,
        MaskedOut,
        InterruptPendingOut,
        DeliveryModeOut,
        VectorOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicLogicalDestinationRegister(
    UINT32*             IdOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicLogicalDestinationRegister(
        ApicDeviceObject,
        IdOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicDestinationFormatRegister(
    UINT32*             DfrModelOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicDestinationFormatRegister(
        ApicDeviceObject,
        DfrModelOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicArbitrationPriorityRegister(
    UINT32*             ClassOut, 
    UINT32*             SubClassOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicArbitrationPriorityRegister(
        ApicDeviceObject,
        ClassOut,
        SubClassOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicTaskPriorityRegister(
    UINT32*             ClassOut, 
    UINT32*             SubClassOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicTaskPriorityRegister(
        ApicDeviceObject,
        ClassOut,
        SubClassOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicProcessorPriorityRegister(
    UINT32*             ClassOut, 
    UINT32*             SubClassOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicProcessorPriorityRegister(
        ApicDeviceObject,
        ClassOut,
        SubClassOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicSpuriousInterruptVectorRegister(
    BOOLEAN*            EoiBroadcastSuppresedOut, 
    BOOLEAN*            FocusProcessorCheckingEnabledOut, 
    BOOLEAN*            ApicSoftwareEnabledOut, 
    UINT8*              SpuriousInterruptVectorOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicSpuriousInterruptVectorRegister(
        ApicDeviceObject,
        EoiBroadcastSuppresedOut,
        FocusProcessorCheckingEnabledOut,
        ApicSoftwareEnabledOut,
        SpuriousInterruptVectorOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicIdRegister(
    UINT32*             IdIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicIdRegister(
        ApicDeviceObject,
        IdIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicLvtTimerRegister(
    APIC_TIMER_MODE*    TimerModeIn, 
    BOOLEAN*            MaskedIn, 
    UINT8*              VectorIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicLvtTimerRegister(
        ApicDeviceObject,
        TimerModeIn,
        MaskedIn,
        VectorIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicLvtCmciRegister(
    BOOLEAN*                MaskedIn, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeIn, 
    UINT8*                  VectorIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicLvtCmciRegister(
        ApicDeviceObject,
        MaskedIn,
        DeliveryModeIn,
        VectorIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicLvtLint0Register(
    BOOLEAN*                MaskedIn, 
    APIC_TRIGGER_MODE*      TriggerModeIn, 
    APIC_IN_PIN_POLARITY*   InPinPolarityIn, 
    UINT8*                  VectorIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicLvtLint0Register(
        ApicDeviceObject,
        MaskedIn,
        TriggerModeIn,
        InPinPolarityIn,
        VectorIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicLvtLint1Register(
    BOOLEAN*                MaskedIn, 
    APIC_TRIGGER_MODE*      TriggerModeIn, 
    APIC_IN_PIN_POLARITY*   InPinPolarityIn, 
    UINT8*                  VectorIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicLvtLint1Register(
        ApicDeviceObject,
        MaskedIn,
        TriggerModeIn,
        InPinPolarityIn,
        VectorIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicLvtErrorRegister(
    BOOLEAN*                MaskedIn, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeIn, 
    UINT8*                  VectorIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicLvtErrorRegister(
        ApicDeviceObject,
        MaskedIn,
        DeliveryModeIn,
        VectorIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicLvtPerformanceMonitoringCountersRegister(
    BOOLEAN*                MaskedIn, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeIn, 
    UINT8*                  VectorIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicLvtPerformanceMonitoringCountersRegister(
        ApicDeviceObject,
        MaskedIn,
        DeliveryModeIn,
        VectorIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicLvtThermalSensorRegister(
    BOOLEAN*                MaskedIn, 
    APIC_LVT_DELIVERY_MODE* DeliveryModeIn, 
    UINT8*                  VectorIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicLvtThermalSensorRegister(
        ApicDeviceObject,
        MaskedIn,
        DeliveryModeIn,
        VectorIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicInterruptCommandRegister(
    UINT32                      DestinationField, 
    APIC_DESTINATION_SHORTHAND  Shorthand, 
    APIC_TRIGGER_MODE           TriggerMode, 
    APIC_LEVEL                  Level, 
    APIC_DESTINATION_MODE       DestinationMode, 
    APIC_ICR_DELIVERY_MODE      DeliveryMode, 
    UINT8                       Vector
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicInterruptCommandRegister(
        ApicDeviceObject,
        DestinationField,
        Shorthand,
        TriggerMode,
        Level,
        DestinationMode,
        DeliveryMode,
        Vector
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicLogicalDestinationRegister(
    UINT32*             IdIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicLogicalDestinationRegister(
        ApicDeviceObject,
        IdIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicDestinationFormatRegister(
    UINT32*             DfrModelIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicDestinationFormatRegister(
        ApicDeviceObject,
        DfrModelIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicTaskPriorityRegister(    
    UINT32*             ClassIn, 
    UINT32*             SubClassIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicTaskPriorityRegister(
        ApicDeviceObject,
        ClassIn,
        SubClassIn
    );
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicSpuriousInterruptVectorRegister(
    BOOLEAN*            EoiBroadcastSuppresedIn, 
    BOOLEAN*            FocusProcessorCheckingEnabledIn, 
    BOOLEAN*            ApicSoftwareEnabledIn, 
    UINT8*              SpuriousInterruptVectorIn
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicSpuriousInterruptVectorRegister(
        ApicDeviceObject,
        EoiBroadcastSuppresedIn,
        FocusProcessorCheckingEnabledIn,
        ApicSoftwareEnabledIn,
        SpuriousInterruptVectorIn
    );
}


DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicDivideConfigurationRegister(
    APIC_TIMER_DIVIDE_CONFIG* DivideConfigOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicDivideConfigurationRegister(ApicDeviceObject, DivideConfigOut);
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicDivideConfigurationRegister(
    APIC_TIMER_DIVIDE_CONFIG DivideConfig
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicDivideConfigurationRegister(ApicDeviceObject, DivideConfig);
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicTimerInitialCount(
    UINT32* InitialCountOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicTimerInitialCount(ApicDeviceObject, InitialCountOut);
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalSetLocalApicTimerInitialCount(
    UINT32 InitialCount
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalSetApicTimerInitialCount(ApicDeviceObject, InitialCount);
}

DRIVER_EXPORT
LOUSTATUS 
ApicHalGetLocalApicTimerCurrentCount(
    UINT32*             CurrentCountOut
){
    ULONG ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[ProcessorNumber].ApicDeviceObject;
    return ApicHalGetApicTimerCurrentCount(ApicDeviceObject, CurrentCountOut);
}