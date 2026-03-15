#include <LouDDK.h>

KERNEL_EXPORT 
BOOLEAN 
LouKeLheaSignalHandlerOverrideCallback( //export KULA as NTOSKRNL.EXE:WheaSignalHandlerOverrideCallback
    UINT_PTR    Context    
){
    LouPrint("LheaSignalHandlerOverrideCallback()\n");
    while(1);
    return false;
}

KERNEL_EXPORT 
PVOID 
LouKeLheaErrorRecordBuilderAddPacket(
    PLHEA_ERROR_RECORD      Record, 
    LHEA_ERROR_PACKET_V2    Packet, 
    UINT32                  MaxSectionCount
){
    LouPrint("LouKeLheaErrorRecordBuilderAddPacket()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PVOID 
LouKeLheaErrorRecordBuilderAddSection(
    PLHEA_ERROR_RECORD                          Record, 
    UINT32                                      MaxSectionCount, 
    UINT32                                      SectionLength, 
    LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS  Flags, 
    GUID                                        SectionType, 
    PVOID                                       DescriptorOut
){
    LouPrint("LouKeLheaErrorRecordBuilderAddSection()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
void 
LouKeLheaErrorRecordBuilderInit(
    PLHEA_ERROR_RECORD      Record, 
    UINT32                  RecordLength, 
    LHEA_ERROR_SEVERITY     Severity, 
    GUID                    Notify
){
    LouPrint("LouKeLheaErrorRecordBuilderInit()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeLheaRegisterErrorSourceOverride(
    LHEA_ERROR_SOURCE_OVERRIDE_SETTINGS     OverrideSettings, 
    PLHEA_ERROR_SOURCE_CONFIGURATION        OverrideConfig, 
    PLHEA_SIGNAL_HANDLER_OVERRIDE_CALLBACK  OverrideCallback
){

    LouPrint("LouKeLheaRegisterErrorSourceOverride()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
BOOLEAN 
LouKeLheaSignalHandlerOverride(
    LHEA_ERROR_SOURCE_TYPE  SourceType, 
    UINT_PTR                Context
){
    LouPrint("LouKeLheaSignalHandlerOverride()\n");
    while(1);
    return false;
}

KERNEL_EXPORT 
void 
LouKeLheaUnregisterErrorSourceOverride(
    LHEA_ERROR_SOURCE_TYPE      Type, 
    ULONG32                     OverrideErrorSourceId
){
    LouPrint("LouKeLheaUnregisterErrorSourceOverride()");
    while(1);
}