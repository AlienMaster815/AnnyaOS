//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <LouDDK.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeOpenProcess(
    PHANDLE             ProcessHandle, 
    ACCESS_MASK         DesiredAccess, 
    POBJECT_ATTRIBUTES  ObjectAttributes, 
    PCLIENT_ID          ClientId
){
    LouPrint("LouKeOpenProcess()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKePcreateProcessNotifyRoutine(
    HANDLE  ParentId, 
    HANDLE  ProcessId,
    BOOLEAN Create
){
    LouPrint("LouKePcreateProcessNotifyRoutine()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKePcreateThreadNotifyRoutine(
    HANDLE  ProcessId, 
    HANDLE  ThreadId, 
    BOOLEAN Create
){
    LouPrint("LouKePcreateThreadNotifyRoutine()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePgetLocationString(
    PVOID       Context, 
    PZZWSTR*    LocationStrings
){
    LouPrint("LouKePgetLocationString()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKePcreateProcessNotifyRoutineEx(
    PEPROCESS               Process, 
    HANDLE                  ProcessId, 
    PPS_CREATE_NOTIFY_INFO  CreateInfo
){
    LouPrint("LouKePcreateProcessNotifyRoutineEx()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsAllocSiloContextSlot(
    ULONG_PTR   Reserved, 
    ULONG*      ReturnedContextSlot
){
    LouPrint("LouKePsAllocSiloContextSlot()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
PESILO 
LouKePsAttachSiloToCurrentThread(
    PESILO Silo
){
    LouPrint("LouKePsAttachSiloToCurrentThread()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsCreateSiloContext(
    PESILO                          Silo, 
    ULONG                           Size, 
    POOL_TYPE                       PoolType, 
    SILO_CONTEXT_CLEANUP_CALLBACK   ContextCleanupCallback, 
    PVOID*                          ReturnedSiloContext
){
    LouPrint("LouKePsCreateSiloContext()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKePsDereferenceSiloContext(
    PVOID SiloContext
){
    LouPrint("LouKePsDereferenceSiloContext()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKePsDetachSiloFromCurrentThread(
    PESILO PreviousSilo
){
    LouPrint("LouKePsDetachSiloFromCurrentThread()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsFreeSiloContextSlot(
    ULONG ContextSlot
){
    LouPrint("LouKePsFreeSiloContextSlot()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
HANDLE 
LouKePsGetCurrentProcessId(){
    LouPrint("LouKePsGetCurrentProcessId()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT
PESILO 
LouKePsGetCurrentServerSilo(){
    LouPrint("LouKePsGetCurrentServerSilo()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PESILO 
LouKePsGetCurrentSilo(){
    LouPrint("LouKePsGetCurrentSilo()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PETHREAD 
LouKePsGetCurrentThread(){
    LouPrint("LouKePsGetCurrentThread()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
HANDLE 
LouKePsGetCurrentThreadId(){
    LouPrint("LouKePsGetCurrentThreadId()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PVOID 
LouKePsGetCurrentThreadTeb(){
    LouPrint("LouKePsGetCurrentThreadTeb()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PESILO 
LouKePsGetEffectiveServerSilo(
    PESILO Silo
){
    LouPrint("LouKePsGetEffectiveServerSilo()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PESILO 
LouKePsGetHostSilo(){
    LouPrint("LouKePsGetHostSilo()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsGetJobServerSilo(
    PEJOB   Job, 
    PESILO* ServerSilo
){
    LouPrint("LouKePsGetJobServerSilo()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsGetJobSilo(
    PEJOB Job, 
    PESILO* Silo
){
    LouPrint("LouKePsGetJobSilo()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
PESILO 
LouKePsGetParentSilo(
    PEJOB Job
){
    LouPrint("LouKePsGetParentSilo()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsGetPermanentSiloContext(
    PESILO Silo, 
    ULONG ContextSlot, 
    PVOID* ReturnedSiloContext
){
    LouPrint("LouKePsGetPermanentSiloContext()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LONGLONG 
LouKePsGetProcessCreateTimeQuadPart(
    PEPROCESS Process
){
    LouPrint("LouKePsGetProcessCreateTimeQuadPart()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsGetProcessExitStatus(
    PEPROCESS Process
){
    LouPrint("LouKePsGetProcessExitStatus()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
HANDLE 
LouKePsGetProcessId(
    PEPROCESS Process
){
    LouPrint("LouKePsGetProcessId()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
ULONGLONG 
LouKePsGetProcessStartKey(
    PEPROCESS Process
){
    LouPrint("LouKePsGetProcessStartKey()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
ULONG 
LouKePsGetServerSiloActiveConsoleId(
    PESILO Silo
){
    LouPrint("LouKePsGetServerSiloActiveConsoleId()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
GUID* 
LouKePsGetSiloContainerId(
    PESILO Silo
){
    LouPrint("LouKePsGetSiloContainerId()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsGetSiloContext(
    PESILO  Silo, 
    ULONG   ContextSlot, 
    PVOID*  ReturnedSiloContext
){
    LouPrint("LouKePsGetSiloContext()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
ULONG 
LouKePsGetSiloMonitorContextSlot(
    PSILO_MONITOR Monitor
){
    LouPrint("LouKePsGetSiloMonitorContextSlot()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LONGLONG 
LouKePsGetThreadCreateTime(
    PETHREAD Thread
){
    LouPrint("LouKePsGetThreadCreateTime()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsGetThreadExitStatus(
    PETHREAD Thread
){
    LouPrint("LouKePsGetThreadExitStatus()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
HANDLE 
LouKePsGetThreadId(
    PETHREAD Thread
){
    LouPrint("LouKePsGetThreadId()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
HANDLE 
LouKePsGetThreadProcessId(
    PETHREAD Thread
){
    LouPrint("LouKePsGetThreadProcessId()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PESILO 
LouKePsGetThreadServerSilo(
    PETHREAD Thread
){
    LouPrint("LouKePsGetThreadServerSilo()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT
LOUSTATUS 
LouKePsInsertPermanentSiloContext(
    PESILO  Silo, 
    ULONG   ContextSlot, 
    PVOID   SiloContext
){
    LouPrint("LouKePsInsertPermanentSiloContext()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsInsertSiloContext(
    PESILO Silo,
    ULONG ContextSlot, 
    PVOID SiloContext
){
    LouPrint("LouKePsInsertSiloContext()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
BOOLEAN 
LouKePsIsHostSilo(
    PESILO Silo
){
    LouPrint("LouKePsIsHostSilo()\n");
    while(1);
    return false;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsMakeSiloContextPermanent(
    PESILO Silo, 
    ULONG ContextSlot
){
    LouPrint("LouKePsMakeSiloContextPermanent()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKePsReferenceSiloContext(
    PVOID SiloContext
){
    LouPrint("LouKePsReferenceSiloContext()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsRemoveCreateThreadNotifyRoutine(
    PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine
){
    LouPrint("LouKePsRemoveCreateThreadNotifyRoutine()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsRemoveLoadImageNotifyRoutine(
    PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine
){
    LouPrint("LouKePsRemoveLoadImageNotifyRoutine()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsRemoveSiloContext(
    PESILO  Silo, 
    ULONG   ContextSlot, 
    PVOID*  RemovedSiloContext
){
    LouPrint("LouKePsRemoveSiloContext()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsReplaceSiloContext(
    PESILO  Silo, 
    ULONG   ContextSlot, 
    PVOID   NewSiloContext, 
    PVOID*  OldSiloContext
){
    LouPrint("LouKePsReplaceSiloContext()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsSetCreateProcessNotifyRoutine(
    PCREATE_PROCESS_NOTIFY_ROUTINE  NotifyRoutine, 
    BOOLEAN                         Remove
){
    LouPrint("LouKePsSetCreateProcessNotifyRoutine()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsSetCreateProcessNotifyRoutineEx(
    PCREATE_PROCESS_NOTIFY_ROUTINE_EX   NotifyRoutine, 
    BOOLEAN                             Remove
){
    LouPrint("LouKePsSetCreateProcessNotifyRoutineEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsSetCreateProcessNotifyRoutineEx2(
    PSCREATEPROCESSNOTIFYTYPE   NotifyType, 
    PVOID                       NotifyInformation, 
    BOOLEAN                     Remove
){
    LouPrint("LouKePsSetCreateProcessNotifyRoutineEx2()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsSetCreateThreadNotifyRoutine(
    PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine
){
    LouPrint("LouKePsSetCreateThreadNotifyRoutine()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsSetCreateThreadNotifyRoutineEx(
    PSCREATETHREADNOTIFYTYPE    NotifyType, 
    PVOID                       NotifyInformation
){
    LouPrint("LouKePsSetCreateThreadNotifyRoutineEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsSetLoadImageNotifyRoutine(
    PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine
){
    LouPrint("LouKePsSetLoadImageNotifyRoutine()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsSetLoadImageNotifyRoutineEx(
    PLOAD_IMAGE_NOTIFY_ROUTINE  NotifyRoutine, 
    ULONG_PTR                   Flags
){
    LouPrint("LouKePsSetLoadImageNotifyRoutineEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePsStartSiloMonitor(
    PSILO_MONITOR Monitor
){
    LouPrint("LouKePsStartSiloMonitor()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKePsTerminateServerSilo(
    PESILO      ServerSilo, 
    LOUSTATUS   ExitStatus
){
    LouPrint("LouKePsTerminateServerSilo()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKePsUnregisterSiloMonitor(
    PSILO_MONITOR Monitor
){
    LouPrint("LouKePsUnregisterSiloMonitor()\n");
    while(1);
}

KERNEL_EXPORT 
BOOLEAN 
LouKePsIsSystemThread(
    PETHREAD Thread
){
    LouPrint("LouKePsIsSystemThread(\n");
    while(1);
    return false;
}
