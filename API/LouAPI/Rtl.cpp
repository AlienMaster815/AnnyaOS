#include <LouDDK.h>


KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlCharToInteger(
    PCSZ    String, 
    ULONG   Base, 
    PULONG  Value
){
    LouPrint("LouKeRtlCharToInteger()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LONG 
LouKeRtlCompareString(
    const STRING*   String1, 
    const STRING*   String2,
    BOOLEAN         CaseInSensitive
){

    LouPrint("LouKeRtlCompareString()\n");
    while(1);
    return 0x00;

}

KERNEL_EXPORT 
VOID 
LouKeRtlCopyString(
    PSTRING         DestinationString, 
    const STRING*   SourceString
){

    LouPrint("LouKeRtlCopyString()\n");
    while(1);

}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlEqualString(
    const STRING*   String1, 
    const STRING*   String2, 
    BOOLEAN         CaseInSensitive
){

    LouPrint("LouKeRtlEqualString()\n");
    while(1);
    return false;

}

KERNEL_EXPORT 
ULONG64 
LouKeRtlGetEnabledExtendedFeatures(
    ULONG64 FeatureMask
){

    LouPrint("LouKeRtlGetEnabledExtendedFeatures()\n");
    while(1);
    return 0x00;

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlGetPersistedStateLocation(
    PCWSTR                  SourceID, 
    PCWSTR                  CustomValue, 
    PCWSTR                  DefaultPath, 
    STATE_LOCATION_TYPE     StateLocationType, 
    PWCHAR                  TargetPath, 
    ULONG                   BufferLengthIn, 
    PULONG                  BufferLengthOut
){

    LouPrint("LouKeRtlGetPersistedStateLocation()\n");
    while(1);
    return STATUS_SUCCESS;

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIncrementCorrelationVector(
    PCORRELATION_VECTOR CorrelationVector
){

    LouPrint("LouKeRtlIncrementCorrelationVector()\n");
    while(1);
    return STATUS_SUCCESS;
    
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInitializeCorrelationVector(
    PCORRELATION_VECTOR CorrelationVector, 
    int                 Version, 
    const GUID*         Guid
){

    LouPrint("LouKeRtlInitializeCorrelationVector()\n");
    while(1);
    return STATUS_SUCCESS;
    
}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlIsStateSeparationEnabled(){

    LouPrint("LouKeRtlIsStateSeparationEnabled()\n");
    while(1);
    return false;

}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlIsZeroMemory(
    PVOID   Buffer, 
    SIZE_T  Length
){

    LouPrint("LouKeRtlIsZeroMemory()\n");
    while(1);
    return false;
    
}

KERNEL_EXPORT 
VOID 
LouKeRtlMapGenericMask(
    PACCESS_MASK            AccessMask, 
    const GENERIC_MAPPING*  GenericMapping
){

    LouPrint("LouKeRtlMapGenericMask()\n");
    while(1);

}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlNormalizeSecurityDescriptor(
    PSECURITY_DESCRIPTOR*   SecurityDescriptor, 
    ULONG                   SecurityDescriptorLength, 
    PSECURITY_DESCRIPTOR*   NewSecurityDescriptor, 
    PULONG                  NewSecurityDescriptorLength, 
    BOOLEAN CheckOnly
){

    LouPrint("LouKeRtlNormalizeSecurityDescriptor()\n");
    while(1);
    return false;

}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlPrefixUnicodeString(
    PCUNICODE_STRING    String1, 
    PCUNICODE_STRING    String2, 
    BOOLEAN             CaseInSensitive
){

    LouPrint("LouKeRtlPrefixUnicodeString()\n");
    while(1);
    return false;

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlQueryRegistryValueWithFallback(
    HANDLE          PrimaryHandle, 
    HANDLE          FallbackHandle, 
    PUNICODE_STRING ValueName, 
    ULONG           ValueLength, 
    PULONG          ValueType, 
    PVOID           ValueData, 
    PULONG          ResultLength
){

    LouPrint("LouKeRtlQueryRegistryValueWithFallback()\n");
    while(1);
    return STATUS_SUCCESS;
    
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlRaiseCustomSystemEventTrigger(
    PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG TriggerConfig
){

    LouPrint("LouKeRtlRaiseCustomSystemEventTrigger()\n");
    while(1);
    return STATUS_SUCCESS;
    
}

KERNEL_EXPORT 
VOID 
LouKeRtlRunOnceInitialize(
    PRTL_RUN_ONCE RunOnce
){

    LouPrint("LouKeRtlRunOnceInitialize()\n");
    while(1);

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUpcaseUnicodeString(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    BOOLEAN             AllocateDestinationString
){

    LouPrint("LouKeRtlUpcaseUnicodeString()\n");
    while(1);
    return STATUS_SUCCESS;

}

KERNEL_EXPORT 
CHAR 
LouKeRtlUpperChar(
    CHAR Character
){

    LouPrint("LouKeRtlUpperChar()\n");
    while(1);
    return 0x00;

}

KERNEL_EXPORT 
VOID 
LouKeRtlUpperString(
    PSTRING DestinationString, 
    const STRING* SourceString
){

    LouPrint("LouKeRtlUpperString()\n");
    while(1);

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlValidateCorrelationVector(
    PCORRELATION_VECTOR Vector
){

    LouPrint("LouKeRtlValidateCorrelationVector()\n");
    while(1);
    return STATUS_SUCCESS;

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlVolumeDeviceToDosName(
    PVOID           VolumeDeviceObject, 
    PUNICODE_STRING DosName
){

    LouPrint("LouKeRtlVolumeDeviceToDosName()\n");
    while(1);
    return STATUS_SUCCESS;

}
