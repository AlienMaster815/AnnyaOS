#include <LouDDK.h>

static uint32_t* WmiTraceMessageVaHandlerStackTrace = 0;
static uint64_t* WmiTraceMessageVaHandlerStackTraceContext = 0;

void NtTransitionLayerInitMessageTraceStack(){
    WmiTraceMessageVaHandlerStackTrace = (uint32_t*)LouKeMallocArray(uint32_t, 64, KERNEL_GENERIC_MEMORY);
    WmiTraceMessageVaHandlerStackTraceContext = (uint64_t*)LouKeMallocArray(uint64_t, 64, KERNEL_GENERIC_MEMORY);
}

extern "C" uint64_t GetGSValue(uint64_t Offset);

LOUDDK_API_ENTRY
NTSTATUS 
WmiTraceMessageVa(
   TRACEHANDLE LoggerHandle,
   ULONG       MessageFlags,
   LPCGUID     MessageGuid,
   USHORT      MessageNumber,
   va_list     MessageArgList
){

    LouPrint("WmiTraceMessageVa()\n");
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS 
WmiTraceMessage(
   TRACEHANDLE LoggerHandle,
   ULONG       MessageFlags,
   LPCGUID     MessageGuid,
   USHORT      MessageNumber,
   ...
){
    NTSTATUS Status;
    va_list args;
    va_start(args, MessageNumber);
    Status = WmiTraceMessageVa(
        LoggerHandle,
        MessageFlags,
        MessageGuid,
        MessageNumber, 
        args
    );
    va_end(args);
    return Status;
}


LOUDDK_API_ENTRY
NTSTATUS 
WmiQueryTraceInformation(
   TRACE_INFORMATION_CLASS TraceInformationClass,
   PVOID                   TraceInformation,
   ULONG                   TraceInformationLength,
   PULONG                  RequiredLength,
   PVOID                   Buffer
){
    LouPrint("WmiQueryTraceInformation\n");
    return STATUS_SUCCESS;
}