//x86_64-w64-mingw32-gcc -shared -o ntdll.dll ntdll.c -nostdlib -nodefaultlibs -I../../../Include -I../../../Include -L../../../UserLibraries -lLouDll

#define NTDLL_API __declspec(dllexport)

#include <Annya.h>


NTDLL_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

//NtDll Functions

NTDLL_API
uint64_t A_SHAFinal(){LouPrint("A_SHAFinal()\n");while(1);return 0;}

NTDLL_API
void A_SHAInit(){LouPrint("A_SHAInit()\n");while(1);}

NTDLL_API
void A_SHAUpdate(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void AlpcAdjustCompletionListConcurrencyCount(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcFreeCompletionListMessage(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcGetCompletionListLastMessageInformation(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcGetCompletionListMessageAttributes(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcGetHeaderSize(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcGetMessageAttribute(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcGetMessageFromCompletionList(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcGetOutstandingCompletionListMessageCount(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcInitializeMessageAttribute(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcMaxAllowedMessageLength(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcRegisterCompletionList(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcRegisterCompletionListWorkerThread(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcRundownCompletionList(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcUnregisterCompletionList(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void AlpcUnregisterCompletionListWorkerThread(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void ApiSetQueryApiSetPresence(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void ApiSetQueryApiSetPresenceEx(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrAllocateCaptureBuffer(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrAllocateMessagePointer(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrCaptureMessageBuffer(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrCaptureMessageMultiUnicodeStringsInPlace(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrCaptureMessageString(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrCaptureTimeout(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrClientCallServer(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrClientConnectToServer(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrFreeCaptureBuffer(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrGetProcessId(){
    
}

NTDLL_API
void CsrIdentifyAlertableThread(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrSetPriorityClass(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void CsrVerifyRegion(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgBreakPoint(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgPrint(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void DbgPrintEx(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgPrintReturnControlC(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgPrompt(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgQueryDebugFilterState(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgSetDebugFilterState(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void DbgUiConnectToDbg(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgUiContinue(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void DbgUiConvertStateChangeStructure(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgUiConvertStateChangeStructureEx(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgUiDebugActiveProcess(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void DbgUiGetThreadDebugObject(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgUiIssueRemoteBreakin(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void DbgUiRemoteBreakin(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgUiSetThreadDebugObject(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgUiStopDebugging(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgUiWaitStateChange(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void DbgUserBreakPoint(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwCheckCoverage(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwCreateTraceInstanceId(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwDeliverDataBlock(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEnumerateProcessRegGuids(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventActivityIdControl(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventEnabled(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventProviderEnabled(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventRegister(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventSetInformation(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventUnregister(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwEventWrite(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventWriteEndScenario(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventWriteEx(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventWriteFull(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventWriteNoRegistration(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventWriteStartScenario(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventWriteString(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwEventWriteTransfer(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwGetTraceEnableFlags(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwGetTraceEnableLevel(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwGetTraceLoggerHandle(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwLogTraceEvent(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API
void EtwNotificationRegister(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwNotificationUnregister(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwProcessPrivateLoggerRequest(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwRegisterSecurityProvider(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwRegisterTraceGuidsA(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwRegisterTraceGuidsW(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwReplyNotification(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwSendNotification(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwSetMark(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwTraceEventInstance(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwTraceMessage(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwTraceMessageVa(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwUnregisterTraceGuids(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwWriteUMSecurityEvent(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwpCreateEtwThread(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EtwpGetCpuSpeed(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EvtIntReportAuthzEventAndSourceAsync(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void EvtIntReportEventAndSourceAsync(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API 
void ExpInterlockedPopEntrySListEnd(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API void ExpInterlockedPopEntrySListFault(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API void ExpInterlockedPopEntrySListResume(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API void KiRaiseUserExceptionDispatcher(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API void KiUserApcDispatcher(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API void KiUserCallbackDispatcher(){LouPrint("Hello NT DLL\n"); while(1);}

NTDLL_API void KiUserExceptionDispatcher() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void KiUserInvertedFunctionTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrAccessResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrAddDllDirectory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrAddLoadAsDataTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrAddRefDll() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrAppxHandleIntegrityFailure() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrCallEnclave() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrControlFlowGuardEnforced() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrCreateEnclave() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrDeleteEnclave() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrDisableThreadCalloutsForDll() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrEnumResources() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrEnumerateLoadedModules() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrFastFailInLoaderCallout() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrFindEntryForAddress() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrFindResourceDirectory_U() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrFindResourceEx_U() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrFindResource_U() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrFlushAlternateResourceModules() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrGetDllDirectory() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrGetDllFullName() {LouPrint("Hello nt Dll\n"); while(1);;}
NTDLL_API void LdrGetDllHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetDllHandleByMapping() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetDllHandleByName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetDllHandleEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetDllPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetFailureData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetFileNameFromLoadAsDataTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetKnownDllSectionHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetProcedureAddress() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetProcedureAddressEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrGetProcedureAddressForCaller() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrHotPatchNotify() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrInitShimEngineDynamic() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrInitializeEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrInitializeThunk() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrIsModuleSxsRedirected() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrLoadAlternateResourceModule() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrLoadAlternateResourceModuleEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrLoadDll() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrLoadEnclaveModule() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrLockLoaderLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrOpenImageFileOptionsKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrProcessInitializationComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrProcessRelocationBlock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrProcessRelocationBlockEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrQueryImageFileExecutionOptions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrQueryImageFileExecutionOptionsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrQueryImageFileKeyOption() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrQueryModuleServiceTags() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrQueryOptionalDelayLoadedAPI() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrQueryProcessModuleInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrRegisterDllNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrRemoveDllDirectory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrRemoveLoadAsDataTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrResFindResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrResFindResourceDirectory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrResGetRCConfig() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrResRelease() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrResSearchResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrResolveDelayLoadedAPI() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrResolveDelayLoadsFromDll() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrRscIsTypeExist() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrSetAppCompatDllRedirectionCallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrSetDefaultDllDirectories() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrSetDllDirectory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrSetDllManifestProber() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrSetImplicitPathOptions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrSetMUICacheType() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrShutdownProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrShutdownThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrStandardizeSystemPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrSystemDllInitBlock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrUnloadAlternateResourceModule() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrUnloadAlternateResourceModuleEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrUnloadDll() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrUnlockLoaderLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrUnregisterDllNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrUpdatePackageSearchPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrVerifyImageMatchesChecksum() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrVerifyImageMatchesChecksumEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrpResGetMappingSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void LdrpResGetResourceDirectory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void MD4Final() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void MD4Init() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void MD4Update() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void MD5Final() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void MD5Init() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void MD5Update() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void MicrosoftTelemetryAssertTriggeredUM() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NlsAnsiCodePage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NlsMbCodePageTag() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NlsMbOemCodePageTag() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAcceptConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAccessCheck() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAccessCheckAndAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAccessCheckByType() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAccessCheckByTypeAndAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAccessCheckByTypeResultList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAccessCheckByTypeResultListAndAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAccessCheckByTypeResultListAndAuditAlarmByHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAcquireCrossVmMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAcquireProcessActivityReference() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAddAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAddAtomEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAddBootEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAddDriverEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAdjustGroupsToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAdjustPrivilegesToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAdjustTokenClaimsAndDeviceGroups() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlertMultipleThreadByThreadId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlertResumeThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlertThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlertThreadByThreadId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlertThreadByThreadIdEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAllocateLocallyUniqueId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAllocateReserveObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAllocateUserPhysicalPages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAllocateUserPhysicalPagesEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAllocateUuids() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAllocateVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAllocateVirtualMemoryEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcAcceptConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcCancelMessage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcConnectPortEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcCreatePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcCreatePortSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcCreateResourceReserve() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcCreateSectionView() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcCreateSecurityContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcDeletePortSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcDeleteResourceReserve() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcDeleteSectionView() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcDeleteSecurityContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcDisconnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcImpersonateClientContainerOfPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcImpersonateClientOfPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcOpenSenderProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcOpenSenderThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcQueryInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcQueryInformationMessage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcRevokeSecurityContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcSendWaitReceivePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAlpcSetInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtApphelpCacheControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAreMappedFilesTheSame() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAssignProcessToJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtAssociateWaitCompletionPacket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCallEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCallbackReturn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCancelIoFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCancelIoFileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCancelSynchronousIoFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCancelTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCancelTimer2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCancelWaitCompletionPacket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtChangeProcessState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtChangeThreadState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtClearEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtClose() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCloseObjectAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCommitComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCommitEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCommitRegistryTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCommitTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCompactKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCompareObjects() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCompareSigningLevels() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCompareTokens() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCompleteConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCompressKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtContinue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtContinueEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtConvertBetweenAuxiliaryCounterAndPerformanceCounter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCopyFileChunk() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateCpuPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateCrossVmEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateCrossVmMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateDebugObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateDirectoryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateDirectoryObjectEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateIRTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateIoRing() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateJobSet() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateKeyTransacted() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateKeyedEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateLowBoxToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateMailslotFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateNamedPipeFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreatePagingFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreatePartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreatePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreatePrivateNamespace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateProcessEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateProcessStateChange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateProfileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateRegistryTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateSectionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateSemaphore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateSymbolicLinkObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateThreadEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateThreadStateChange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateTimer2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateTokenEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateUserProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateWaitCompletionPacket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateWaitablePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateWnfStateName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtCreateWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDebugActiveProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDebugContinue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDelayExecution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteBootEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteDriverEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteObjectAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeletePrivateNamespace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeleteWnfStateName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDeviceIoControlFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDirectGraphicsCall() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDisableLastKnownGood() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDisplayString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDrawText() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDuplicateObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtDuplicateToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtEnableLastKnownGood() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtEnumerateBootEntries() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtEnumerateDriverEntries() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtEnumerateKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtEnumerateSystemEnvironmentValuesEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtEnumerateTransactionObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtEnumerateValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtExtendSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFilterBootOption() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFilterToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFilterTokenEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFindAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFlushBuffersFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFlushBuffersFileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFlushInstallUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFlushInstructionCache() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFlushKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFlushProcessWriteBuffers() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFlushVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFlushWriteBuffer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFreeUserPhysicalPages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFreeVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFreezeRegistry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFreezeTransactions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtFsControlFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetCachedSigningLevel() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetCompleteWnfStateSubscription() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetContextThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetCurrentProcessorNumber() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetCurrentProcessorNumberEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetDevicePowerState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetMUIRegistryInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetNextProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetNextThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetNlsSectionPtr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetNotificationResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetTickCount() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtGetWriteWatch() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtImpersonateAnonymousToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtImpersonateClientOfPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtImpersonateThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtInitializeEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtInitializeNlsFiles() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtInitializeRegistry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtInitiatePowerAction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtIsProcessInJob() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtIsSystemResumeAutomatic() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtIsUILanguageComitted() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtListenPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLoadDriver() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLoadEnclaveData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLoadKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLoadKey2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLoadKey3() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLoadKeyEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLockFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLockProductActivationKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLockRegistryKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtLockVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtMakePermanentObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtMakeTemporaryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtManageHotPatch() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtManagePartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtMapCMFModule() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtMapUserPhysicalPages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtMapUserPhysicalPagesScatter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtMapViewOfSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtMapViewOfSectionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtModifyBootEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtModifyDriverEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtNotifyChangeDirectoryFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtNotifyChangeDirectoryFileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtNotifyChangeKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtNotifyChangeMultipleKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtNotifyChangeSession() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenCpuPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenDirectoryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenKeyEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenKeyTransacted() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenKeyTransactedEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenKeyedEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenObjectAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenPrivateNamespace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenProcessToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenProcessTokenEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenRegistryTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenSemaphore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenSession() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenSymbolicLinkObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenThreadToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenThreadTokenEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtOpenTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPlugPlayControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPowerInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPrePrepareComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPrePrepareEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPrepareComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPrepareEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPrivilegeCheck() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPrivilegeObjectAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPrivilegedServiceAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPropagationComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPropagationFailed() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtProtectVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPssCaptureVaSpaceBulk() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtPulseEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryAttributesFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryAuxiliaryCounterFrequency() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryBootEntryOrder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryBootOptions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryDebugFilterState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryDefaultLocale() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryDefaultUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryDirectoryFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryDirectoryFileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryDirectoryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryDriverEntryOrder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryEaFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryFullAttributesFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationByName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationCpuPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInformationWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryInstallUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryIntervalProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryIoRingCapabilities() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryLicenseValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryMultipleValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryOpenSubKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryOpenSubKeysEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryPerformanceCounter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryPortInformationProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryQuotaInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySecurityAttributesToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySecurityPolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySemaphore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySymbolicLinkObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySystemEnvironmentValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySystemEnvironmentValueEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySystemInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySystemInformationEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQuerySystemTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryTimerResolution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryVolumeInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueryWnfStateNameInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueueApcThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueueApcThreadEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtQueueApcThreadEx2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRaiseException() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRaiseHardError() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReadFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReadFileScatter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReadOnlyEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReadRequestData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReadVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReadVirtualMemoryEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRecoverEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRecoverResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRecoverTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRegisterProtocolAddressInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRegisterThreadTerminatePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReleaseKeyedEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReleaseMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReleaseSemaphore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReleaseWorkerFactoryWorker() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRemoveIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRemoveIoCompletionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRemoveProcessDebug() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRenameKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRenameTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReplaceKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReplacePartitionUnit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReplyPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReplyWaitReceivePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReplyWaitReceivePortEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtReplyWaitReplyPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRequestPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRequestWaitReplyPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtResetEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtResetWriteWatch() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRestoreKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtResumeProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtResumeThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRevertContainerImpersonation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRollbackComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRollbackEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRollbackRegistryTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRollbackTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtRollforwardTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSaveKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSaveKeyEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSaveMergedKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSecureConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSerializeBoot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetBootEntryOrder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetBootOptions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetCachedSigningLevel() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetCachedSigningLevel2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetContextThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetDebugFilterState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetDefaultHardErrorPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetDefaultLocale() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetDefaultUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetDriverEntryOrder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetEaFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetEventBoostPriority() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetEventEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetHighEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetHighWaitLowEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetIRTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationCpuPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationDebugObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationIoRing() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationSymbolicLink() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetInformationWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetIntervalProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetIoCompletionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetLdtEntries() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetLowEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetLowWaitHighEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetQuotaInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetSecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetSystemEnvironmentValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetSystemEnvironmentValueEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetSystemInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetSystemPowerState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetSystemTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetThreadExecutionState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetTimer2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetTimerEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetTimerResolution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetUuidSeed() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetVolumeInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSetWnfProcessNotificationEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtShutdownSystem() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtShutdownWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSignalAndWaitForSingleObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSinglePhaseReject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtStartProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtStopProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSubmitIoRing() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSubscribeWnfStateChange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSuspendProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSuspendThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtSystemDebugControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtTerminateEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtTerminateJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtTerminateProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtTerminateThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtTestAlert() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtThawRegistry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtThawTransactions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtTraceControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtTraceEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtTranslateFilePath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUmsThreadYield() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnloadDriver() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnloadKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnloadKey2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnloadKeyEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnlockFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnlockVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnmapViewOfSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnmapViewOfSectionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUnsubscribeWnfStateChange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtUpdateWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtVdmControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitForAlertByThreadId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitForDebugEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitForKeyedEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitForMultipleObjects() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitForMultipleObjects32() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitForSingleObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitForWorkViaWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitHighEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWaitLowEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWorkerFactoryWorkerReady() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWriteFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWriteFileGather() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWriteRequestData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtWriteVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtYieldExecution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtdllDefWindowProc_A() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtdllDefWindowProc_W() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtdllDialogWndProc_A() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void NtdllDialogWndProc_W() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PfxFindPrefix() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PfxInitialize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PfxInsertPrefix() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PfxRemovePrefix() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PssNtCaptureSnapshot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PssNtDuplicateSnapshot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PssNtFreeRemoteSnapshot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PssNtFreeSnapshot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PssNtFreeWalkMarker() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PssNtQuerySnapshot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PssNtValidateDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void PssNtWalkSnapshot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAbortRXact() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAbsoluteToSelfRelativeSD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAcquirePebLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAcquirePrivilege() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAcquireReleaseSRWLockExclusive() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAcquireResourceExclusive() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAcquireResourceShared() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAcquireSRWLockExclusive() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAcquireSRWLockShared() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlActivateActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlActivateActivationContextEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlActivateActivationContextUnsafeFast() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAccessAllowedAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAccessAllowedAceEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAccessAllowedObjectAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAccessDeniedAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAccessDeniedAceEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAccessDeniedObjectAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAccessFilterAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddActionToRXact() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAtomToAtomTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAttributeActionToRXact() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAuditAccessAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAuditAccessAceEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddAuditAccessObjectAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddCompoundAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddFunctionTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddGrowableFunctionTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddIntegrityLabelToBoundaryDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddMandatoryAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddProcessTrustLabelAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddRefActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddRefMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddResourceAttributeAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddSIDToBoundaryDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddScopedPolicyIDAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddVectoredContinueHandler() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddVectoredExceptionHandler() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAddressInSectionTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAdjustPrivilege() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAllocateActivationContextStack() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAllocateAndInitializeSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAllocateAndInitializeSidEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAllocateHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAllocateHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAllocateMemoryBlockLookaside() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAllocateMemoryZone() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAllocateWnfSerializationGroup() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAnsiCharToUnicodeChar() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAnsiStringToUnicodeSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAnsiStringToUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAppendAsciizToString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAppendPathElement() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAppendStringToString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAppendUnicodeStringToString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAppendUnicodeToString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlApplicationVerifierStop() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlApplyRXact() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlApplyRXactNoFlush() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAppxIsFileOwnedByTrustedInstaller() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAreAllAccessesGranted() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAreAnyAccessesGranted() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAreBitsClear() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAreBitsClearEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAreBitsSet() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAreLongPathsEnabled() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAssert() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAvlInsertNodeEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlAvlRemoveNode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlBarrier() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlBarrierForDelete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCallEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCallEnclaveReturn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCancelTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCanonicalizeDomainName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCapabilityCheck() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCapabilityCheckForSingleSessionSku() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCaptureContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCaptureContext2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCaptureStackBackTrace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCharToInteger() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckBootStatusIntegrity() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckForOrphanedCriticalSections() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckPortableOperatingSystem() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckRegistryKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckSandboxedToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckSystemBootStatusIntegrity() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckTokenCapability() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckTokenMembership() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCheckTokenMembershipEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCleanUpTEBLangLists() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlClearAllBits() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlClearAllBitsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlClearBit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlClearBitEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlClearBits() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlClearBitsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlClearThreadWorkOnBehalfTicket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCloneMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCloneUserProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCmDecodeMemIoResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCmEncodeMemIoResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCommitDebugInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCommitMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompactHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompareAltitudes() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompareExchangePointerMapping() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompareExchangePropertyStore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompareMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompareMemoryUlong() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompareString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompareUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompareUnicodeStrings() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompleteProcessCloning() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCompressBuffer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlComputeCrc32() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlComputeImportTableHash() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlComputePrivatizedDllName_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConnectToSm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConsoleMultiByteToUnicodeN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConstructCrossVmEventPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConstructCrossVmMutexPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlContractHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConvertDeviceFamilyInfoToString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConvertExclusiveToShared() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConvertHostPerfCounterToPerfCounter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConvertLCIDToString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConvertSRWLockExclusiveToShared() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConvertSharedToExclusive() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConvertSidToUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlConvertToAutoInheritSecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyBitMap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyExtendedContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyLuid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyLuidAndAttributesArray() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyMappedMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyMemoryNonTemporal() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyMemoryStreamTo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyOutOfProcessMemoryStreamTo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopySecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopySid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopySidAndAttributesArray() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCopyUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCrc32() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCrc64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateAcl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateAndSetSD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateAtomTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateBootStatusDataFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateBoundaryDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateEnvironment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateEnvironmentEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateHashTableEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateMemoryBlockLookaside() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateMemoryZone() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateProcessParameters() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateProcessParametersEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateProcessParametersWithTemplate() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateProcessReflection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateQueryDebugBuffer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateRegistryKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateServiceSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateSystemVolumeInformationFolder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateTagHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateTimerQueue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUmsCompletionList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUmsThreadContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUnicodeStringFromAsciiz() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUserFiberShadowStack() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUserProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUserProcessEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUserSecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUserStack() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateUserThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCreateVirtualAccountSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCultureNameToLCID() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCustomCPToUnicodeN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlCutoverTimeToSystemTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeCommitDebugInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeNormalizeProcessParams() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeactivateActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeactivateActivationContextUnsafeFast() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDebugPrintTimes() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDecodePointer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDecodeRemotePointer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDecodeSystemPointer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDecompressBuffer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDecompressBufferEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDecompressFragment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDefaultNpAcl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDelayExecution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDelete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteAtomFromAtomTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteBarrier() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteBoundaryDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteElementGenericTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteElementGenericTableAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteElementGenericTableAvlEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteFunctionTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteGrowableFunctionTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteNoSplay() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteRegistryValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteSecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteTimerQueue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteTimerQueueEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteUmsCompletionList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeleteUmsThreadContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDequeueUmsCompletionListItems() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeregisterSecureMemoryCacheCallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeregisterWait() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeregisterWaitEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDeriveCapabilitySidsFromName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDestroyAtomTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDestroyEnvironment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDestroyHandleTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDestroyHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDestroyMemoryBlockLookaside() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDestroyMemoryZone() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDestroyProcessParameters() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDestroyQueryDebugBuffer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDetectHeapLeaks() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDetermineDosPathNameType_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDisableThreadProfiling() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDisownModuleHeapAllocation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDllShutdownInProgress() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDnsHostNameToComputerName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDoesFileExists_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDoesNameContainWildCards() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosApplyFileIsolationRedirection_Ustr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosLongPathNameToNtPathName_U_WithStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosLongPathNameToRelativeNtPathName_U_WithStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosPathNameToNtPathName_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosPathNameToNtPathName_U_WithStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosPathNameToRelativeNtPathName_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosPathNameToRelativeNtPathName_U_WithStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosSearchPath_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDosSearchPath_Ustr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDowncaseUnicodeChar() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDowncaseUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDrainNonVolatileFlush() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDumpResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlDuplicateUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEmptyAtomTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnableEarlyCriticalSectionEventCreation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnableThreadProfiling() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnclaveCallDispatch() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnclaveCallDispatchReturn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEncodePointer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEncodeRemotePointer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEncodeSystemPointer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEndEnumerationHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEndStrongEnumerationHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEndWeakEnumerationHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnterCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnterUmsSchedulingMode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnumProcessHeaps() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnumerateEntryHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnumerateGenericTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnumerateGenericTableAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnumerateGenericTableLikeADirectory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnumerateGenericTableWithoutSplaying() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEnumerateGenericTableWithoutSplayingAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEqualComputerName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEqualDomainName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEqualLuid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEqualPrefixSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEqualSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEqualString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEqualUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEqualWnfChangeStamps() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEraseUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEthernetAddressToStringA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEthernetAddressToStringW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEthernetStringToAddressA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlEthernetStringToAddressW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExecuteUmsThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExitUserProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExitUserThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExpandEnvironmentStrings() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExpandEnvironmentStrings_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExpandHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExtendCorrelationVector() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExtendMemoryBlockLookaside() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExtendMemoryZone() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlExtractBitMap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFillMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFillMemoryNonTemporal() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFillNonVolatileMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFinalReleaseOutOfProcessMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindAceByType() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindActivationContextSectionGuid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindActivationContextSectionString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindCharInUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindClearBits() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindClearBitsAndSet() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindClearBitsAndSetEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindClearBitsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindClearRuns() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindClosestEncodableLength() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindExportedRoutineByName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindLastBackwardRunClear() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindLeastSignificantBit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindLongestRunClear() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindMessage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindMostSignificantBit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindNextForwardRunClear() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindSetBits() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindSetBitsAndClear() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindSetBitsAndClearEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindSetBitsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFindUnicodeSubstring() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFirstEntrySList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFirstFreeAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlsAlloc() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlsAllocEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlsFree() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlsGetValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlsGetValue2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlsSetValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlushHeaps() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlushNonVolatileMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlushNonVolatileMemoryRanges() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFlushSecureMemoryCache() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFormatCurrentUserKeyPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFormatMessage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFormatMessageEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeActivationContextStack() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeAnsiString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeMemoryBlockLookaside() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeNonVolatileToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeOemString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeThreadActivationContextStack() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeUTF8String() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeUserFiberShadowStack() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlFreeUserStack() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGUIDFromString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGenerate8dot3Name() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetAce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetAcesBufferSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetActiveActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetActiveConsoleId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetAppContainerNamedObjectPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetAppContainerParent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetAppContainerSidType() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCallersAddress() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCompressionWorkSpaceSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetConsoleSessionForegroundProcessId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetControlSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCriticalSectionRecursionCount() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCurrentDirectory_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCurrentPeb() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCurrentProcessorNumber() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCurrentProcessorNumberEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCurrentServiceSessionId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCurrentThreadPrimaryGroup() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCurrentTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetCurrentUmsThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetDaclSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetDeviceFamilyInfoEnum() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetElementGenericTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetElementGenericTableAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetEnabledExtendedFeatures() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetExePath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetExtendedContextLength() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetExtendedContextLength2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetExtendedFeaturesMask() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetFeatureToggleConfiguration() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetFeatureTogglesChangeToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetFileMUIPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetFrame() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetFullPathName_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetFullPathName_UEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetFullPathName_UstrEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetFunctionTableListHead() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetGroupSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetImageFileMachines() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetIntegerAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetInterruptTimePrecise() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetLastNtStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetLastWin32Error() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetLengthWithoutLastFullDosOrNtPathElement() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetLengthWithoutTrailingPathSeperators() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetLocaleFileMappingAddress() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetLongestNtPathLength() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetMultiTimePrecise() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetNativeSystemInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetNextEntryHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetNextUmsListItem() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetNonVolatileToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetNtGlobalFlags() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetNtProductType() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetNtSystemRoot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetNtVersionNumbers() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetOwnerSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetParentLocaleName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetPersistedStateLocation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetProcessHeaps() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetProcessPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetProductInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetReturnAddressHijackTarget() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSaclSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSearchPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSecurityDescriptorRMControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSessionProperties() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSetBootStatusData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSuiteMask() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSystemBootStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSystemBootStatusEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSystemGlobalData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSystemPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSystemTimeAndBias() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetSystemTimePrecise() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetThreadErrorMode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetThreadLangIdByIndex() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetThreadPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetThreadWorkOnBehalfTicket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetTokenNamedObjectPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetUILanguageInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetUmsCompletionListEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetUnloadEventTrace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetUnloadEventTraceEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetUserInfoHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetUserPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGetVersion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGrowFunctionTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlGuardCheckLongJumpTarget() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlHashUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlHeapTrkInitialize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIdentifierAuthoritySid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIdnToAscii() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIdnToNameprepUnicode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIdnToUnicode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlImageDirectoryEntryToData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlImageNtHeader() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlImageNtHeaderEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlImageRvaToSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlImageRvaToVa() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlImpersonateSelf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlImpersonateSelfEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIncrementCorrelationVector() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitAnsiString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitAnsiStringEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitBarrier() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitCodePageTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitEnumerationHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitNlsTables() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitOutOfProcessMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitStringEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitStrongEnumerationHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitUTF8String() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitUTF8StringEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitUnicodeStringEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitWeakEnumerationHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeAtomPackage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeBitMap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeBitMapEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeConditionVariable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeCorrelationVector() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeCriticalSectionAndSpinCount() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeCriticalSectionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeExtendedContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeExtendedContext2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeGenericTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeGenericTableAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeHandleTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeNtUserPfn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeRXact() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeSListHead() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeSRWLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInitializeSidEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInsertElementGenericTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInsertElementGenericTableAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInsertElementGenericTableFull() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInsertElementGenericTableFullAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInsertEntryHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInstallFunctionTableCallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInt64ToUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIntegerToChar() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIntegerToUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInterlockedClearBitRun() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInterlockedClearBitRunEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInterlockedFlushSList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInterlockedPopEntrySList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInterlockedPushEntrySList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInterlockedPushListSList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInterlockedPushListSListEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlInterlockedSetBitRun() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIoDecodeMemIoResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIoEncodeMemIoResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv4AddressToStringA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv4AddressToStringExA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv4AddressToStringExW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv4AddressToStringW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv4StringToAddressA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv4StringToAddressExA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv4StringToAddressExW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv4StringToAddressW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv6AddressToStringA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv6AddressToStringExA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv6AddressToStringExW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv6AddressToStringW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv6StringToAddressA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv6StringToAddressExA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv6StringToAddressExW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIpv6StringToAddressW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsActivationContextActive() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsApiSetImplemented() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsCapabilitySid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsCloudFilesPlaceholder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsCriticalSectionLocked() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsCriticalSectionLockedByThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsCurrentProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsCurrentThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsCurrentThreadAttachExempt() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsDosDeviceName_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsEcCode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsElevatedRid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsEnclaveFeaturePresent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsFeatureEnabledForEnterprise() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsGenericTableEmpty() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsGenericTableEmptyAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsMultiSessionSku() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsMultiUsersInSessionSku() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsNameInExpression() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsNameInUnUpcasedExpression() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsNameLegalDOS8Dot3() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsNonEmptyDirectoryReparsePointAllowed() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsNormalizedString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsPackageSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsParentOfChildAppContainer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsPartialPlaceholder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsPartialPlaceholderFileHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsPartialPlaceholderFileInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsProcessorFeaturePresent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsStateSeparationEnabled() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsTextUnicode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsThreadWithinLoaderCallout() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsUntrustedObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsValidHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsValidIndexHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsValidLocaleName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsValidProcessTrustLabelSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlIsZeroMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlKnownExceptionFilter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLCIDToCultureName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLargeIntegerToChar() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLcidToLocaleName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLeaveCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLengthCurrentClearRunBackwardEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLengthCurrentClearRunForwardEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLengthRequiredSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLengthSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLengthSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLengthSidAsUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLoadString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLocalTimeToSystemTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLocaleNameToLcid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLocateExtendedFeature() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLocateExtendedFeature2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLocateLegacyContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLockBootStatusData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLockCurrentThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLockHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLockMemoryBlockLookaside() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLockMemoryStreamRegion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLockMemoryZone() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLockModuleSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLogStackBackTrace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLogUnexpectedCodepath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupAtomInAtomTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupElementGenericTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupElementGenericTableAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupElementGenericTableFull() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupElementGenericTableFullAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupEntryHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupFirstMatchingElementGenericTableAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupFunctionEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlLookupFunctionTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMakeSelfRelativeSD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMapGenericMask() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMapSecurityErrorToNtStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMoveMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMultiAppendUnicodeStringBuffer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMultiByteToUnicodeN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMultiByteToUnicodeSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMultipleAllocateHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlMultipleFreeHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNewInstanceSecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNewSecurityGrantedAccess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNewSecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNewSecurityObjectEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNewSecurityObjectWithMultipleInheritance() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNormalizeProcessParams() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNormalizeSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNormalizeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNotifyFeatureToggleUsage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNotifyFeatureUsage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNtPathNameToDosPathName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNtStatusToDosError() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNtStatusToDosErrorNoTeb() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNtdllName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberGenericTableElements() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberGenericTableElementsAvl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberOfClearBits() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberOfClearBitsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberOfClearBitsInRange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberOfSetBits() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberOfSetBitsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberOfSetBitsInRange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlNumberOfSetBitsUlongPtr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlOemStringToUnicodeSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlOemStringToUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlOemToUnicodeN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlOpenCrossProcessEmulatorWorkConnection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlOpenCurrentUser() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlOsDeploymentState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlOverwriteFeatureConfigurationBuffer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlOwnerAcesPresent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlPcToFileHeader() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlPinAtomInAtomTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlPopFrame() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlPrefixString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlPrefixUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlPrepareForProcessCloning() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlProcessFlsData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlProtectHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlPublishWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlPushFrame() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryActivationContextApplicationSettings() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryAllFeatureConfigurations() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryAllInternalFeatureConfigurations() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryAtomInAtomTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryCriticalSectionOwner() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryDepthSList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryDynamicTimeZoneInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryElevationFlags() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryEnvironmentVariable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryEnvironmentVariable_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryFeatureConfiguration() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryFeatureConfigurationChangeStamp() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryFeatureUsageNotificationSubscriptions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryHeapInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryImageMitigationPolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryInformationAcl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryInformationActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryInformationActiveActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryInterfaceMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryInternalFeatureConfiguration() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryModuleInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryPackageClaims() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryPackageIdentity() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryPackageIdentityEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryPerformanceCounter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryPerformanceFrequency() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryPointerMapping() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryProcessBackTraceInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryProcessDebugInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryProcessHeapInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryProcessLockInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryProcessPlaceholderCompatibilityMode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryPropertyStore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryProtectedPolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryRegistryValueWithFallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryRegistryValues() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryRegistryValuesEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryResourcePolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQuerySecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryTagHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryThreadPlaceholderCompatibilityMode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryThreadProfiling() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryTimeZoneInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryTokenHostIdAsUlong64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryUmsThreadInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryUnbiasedInterruptTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryValidationRunlevel() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryWnfMetaNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueryWnfStateDataWithExplicitScope() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueueApcWow64Thread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlQueueWorkItem() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRaiseCustomSystemEventTrigger() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRaiseException() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRaiseExceptionForReturnAddressHijack() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRaiseNoncontinuableException() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRaiseStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRandom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRandomEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRbInsertNodeEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRbRemoveNode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRcuAllocate() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRcuFree() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRcuReadLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRcuReadUnlock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRcuSynchronize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReAllocateHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReadMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReadOutOfProcessMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReadThreadProfilingData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRealPredecessor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRealSuccessor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRegisterFeatureConfigurationChangeNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRegisterForWnfMetaNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRegisterSecureMemoryCacheCallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRegisterThreadWithCsrss() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRegisterWait() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleaseActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleaseMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleasePath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleasePebLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleasePrivilege() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleaseRelativeName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleaseResource() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleaseSRWLockExclusive() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReleaseSRWLockShared() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRemoteCall() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRemoveEntryHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRemovePointerMapping() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRemovePrivileges() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRemovePropertyStore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRemoveVectoredContinueHandler() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRemoveVectoredExceptionHandler() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReplaceSidInSd() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReplaceSystemDirectoryInPath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReportException() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReportExceptionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReportSilentProcessExit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlReportSqmEscalation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlResetMemoryBlockLookaside() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlResetMemoryZone() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlResetNtUserPfn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlResetRtlTranslations() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRestoreBootStatusDefaults() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRestoreContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRestoreLastWin32Error() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRestoreSystemBootStatusDefaults() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRestoreThreadPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRetrieveNtUserPfn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRevertMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRunDecodeUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRunEncodeUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRunOnceBeginInitialize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRunOnceComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRunOnceExecuteOnce() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlRunOnceInitialize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSecondsSince1970ToTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSecondsSince1980ToTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSeekMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSelfRelativeToAbsoluteSD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSelfRelativeToAbsoluteSD2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSendMsgToSm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetAllBits() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetAllBitsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetAttributesSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetBit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetBitEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetBits() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetBitsEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetControlSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetCriticalSectionSpinCount() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetCurrentDirectory_U() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetCurrentEnvironment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetCurrentTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetDaclSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetDynamicTimeZoneInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetEnvironmentStrings() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetEnvironmentVar() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetEnvironmentVariable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetExtendedFeaturesMask() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetFeatureConfigurations() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetGroupSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetHeapInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetImageMitigationPolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetInformationAcl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetIoCompletionCallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetLastWin32Error() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetLastWin32ErrorAndNtStatusFromNtStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetMemoryStreamSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetOwnerSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetPortableOperatingSystem() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetProcessDebugInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetProcessIsCritical() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetProcessPlaceholderCompatibilityMode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetProcessPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetProtectedPolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetProxiedProcessId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetSaclSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetSearchPathMode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetSecurityDescriptorRMControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetSecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetSecurityObjectEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetSystemBootStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetSystemBootStatusEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetThreadErrorMode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetThreadIsCritical() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetThreadPlaceholderCompatibilityMode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetThreadPoolStartFunc() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetThreadPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetThreadPreferredUILanguages2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetThreadSubProcessTag() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetThreadWorkOnBehalfTicket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetTimeZoneInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetUmsThreadInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetUnhandledExceptionFilter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetUserFlagsHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSetUserValueHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSidDominates() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSidDominatesForTrust() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSidEqualLevel() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSidHashInitialize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSidHashLookup() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSidIsHigherLevel() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSizeHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSleepConditionVariableCS() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSleepConditionVariableSRW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSplay() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlStartRXact() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlStatMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlStringFromGUID() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlStringFromGUIDEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlStronglyEnumerateEntryHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSubAuthorityCountSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSubAuthoritySid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSubscribeForFeatureUsageNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSubscribeWnfStateChangeNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSubtreePredecessor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSubtreeSuccessor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSwitchedVVI() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlSystemTimeToLocalTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTestAndPublishWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTestBit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTestBitEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTestProtectedAccess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTimeFieldsToTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTimeToElapsedTimeFields() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTimeToSecondsSince1970() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTimeToSecondsSince1980() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTimeToTimeFields() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTlsAlloc() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTlsFree() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTlsSetValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTraceDatabaseAdd() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTraceDatabaseCreate() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTraceDatabaseDestroy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTraceDatabaseEnumerate() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTraceDatabaseFind() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTraceDatabaseLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTraceDatabaseUnlock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTraceDatabaseValidate() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTryAcquirePebLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTryAcquireSRWLockExclusive() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTryAcquireSRWLockShared() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTryConvertSRWLockSharedToExclusiveOrRelease() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlTryEnterCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUTF8StringToUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUTF8ToUnicodeN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUdiv128() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUmsThreadYield() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnhandledExceptionFilter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnhandledExceptionFilter2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeStringToAnsiSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeStringToAnsiString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeStringToCountedOemString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeStringToInteger() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeStringToOemSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeStringToOemString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeStringToUTF8String() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeToCustomCPN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeToMultiByteN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeToMultiByteSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeToOemN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnicodeToUTF8N() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUniform() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnlockBootStatusData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnlockCurrentThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnlockHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnlockMemoryBlockLookaside() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnlockMemoryStreamRegion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnlockMemoryZone() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnlockModuleSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnregisterFeatureConfigurationChangeNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnsubscribeFromFeatureUsageNotifications() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnsubscribeWnfNotificationWaitForCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnsubscribeWnfNotificationWithCompletionCallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnsubscribeWnfStateChangeNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnwind() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUnwindEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpcaseUnicodeChar() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpcaseUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpcaseUnicodeStringToAnsiString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpcaseUnicodeStringToCountedOemString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpcaseUnicodeStringToOemString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpcaseUnicodeToCustomCPN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpcaseUnicodeToMultiByteN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpcaseUnicodeToOemN() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpdateClonedCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpdateClonedSRWLock() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpdateTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpperChar() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUpperString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUserFiberStart() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlUserThreadStart() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidAcl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidProcessProtection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidRelativeSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidSecurityDescriptor() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidSid() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidateCorrelationVector() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidateHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidateProcessHeaps() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidateUnicodeString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlValidateUserCallTarget() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlVerifyVersionInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlVirtualUnwind() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlVirtualUnwind2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWaitForWnfMetaNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWaitOnAddress() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWakeAddressAll() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWakeAddressAllNoFence() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWakeAddressSingle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWakeAddressSingleNoFence() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWakeAllConditionVariable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWakeConditionVariable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWalkFrameChain() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWalkHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWeaklyEnumerateEntryHashTable() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWerpReportException() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWnfDllUnloadCallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64CallFunction64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64ChangeProcessState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64ChangeThreadState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64EnableFsRedirection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64EnableFsRedirectionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetCpuAreaEnabledFeatures() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetCpuAreaInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetCurrentCpuArea() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetCurrentMachine() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetEquivalentMachineCHPE() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetProcessMachines() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetSharedInfoProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetThreadContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64GetThreadSelectorEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64IsWowGuestMachineSupported() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64LogMessageInEventLogger() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64PopAllCrossProcessWorkFromWorkList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64PopCrossProcessWorkFromFreeList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64PushCrossProcessWorkOntoFreeList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64PushCrossProcessWorkOntoWorkList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64RequestCrossProcessHeavyFlush() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64SetThreadContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64SuspendProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWow64SuspendThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWriteMemoryStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWriteNonVolatileMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlWriteRegistryValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlXRestore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlXSave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlZeroHeap() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlZeroMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlZombifyActivationContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpApplyLengthFunction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpCheckDynamicTimeZoneInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpCleanupRegistryKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpConvertAbsoluteToRelativeSecurityAttribute() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpConvertCultureNamesToLCIDs() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpConvertLCIDsToCultureNames() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpConvertRelativeToAbsoluteSecurityAttribute() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpCreateProcessRegistryInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpEnsureBufferSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpFreezeTimeBias() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpGetDeviceFamilyInfoEnum() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpGetLCIDFromLangInfoNode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpGetNameFromLangInfoNode() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpGetSystemDefaultUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpGetUserOrMachineUILanguage4NLS() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpInitializeLangRegistryInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpIsQualifiedLanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpLoadMachineUIByPolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpLoadUserUIByPolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpMergeSecurityAttributeInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpMuiFreeLangRegistryInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpMuiRegCreateRegistryInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpMuiRegFreeRegistryInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpMuiRegLoadRegistryInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpNotOwnerCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpNtCreateKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpNtEnumerateSubKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpNtMakeTemporaryKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpNtOpenKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpNtQueryValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpNtSetValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpQueryDefaultUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpQueryProcessDebugInformationFromWow64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpQueryProcessDebugInformationRemote() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpRefreshCachedUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpScpCfgNtdllExports() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpSetInstallLanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpSetPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpSetUserPreferredUILanguages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpTimeFieldsToTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpTimeToTimeFields() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpUnWaitCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpVerifyAndCommitUILanguageSettings() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpWaitForCriticalSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpWow64CtxFromAmd64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpWow64GetContextOnAmd64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlpWow64SetContextOnAmd64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlxAnsiStringToUnicodeSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlxOemStringToUnicodeSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlxUnicodeStringToAnsiSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void RtlxUnicodeStringToOemSize() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void SbExecuteProcedure() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void SbSelectProcedure() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ShipAssert() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ShipAssertGetBufferInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ShipAssertMsgA() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ShipAssertMsgW() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocAlpcCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocAlpcCompletionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocCleanupGroup() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocJobNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocPool() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocWait() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAllocWork() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAlpcRegisterCompletionList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpAlpcUnregisterCompletionList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackDetectedUnrecoverableError() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackIndependent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackLeaveCriticalSectionOnCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackMayRunLong() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackReleaseMutexOnCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackReleaseSemaphoreOnCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackSendAlpcMessageOnCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackSendPendingAlpcMessage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackSetEventOnCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCallbackUnloadDllOnCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCancelAsyncIoOperation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCaptureCaller() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpCheckTerminateWorker() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpDbgDumpHeapUsage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpDbgSetLogRoutine() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpDisablePoolCallbackChecks() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpDisassociateCallback() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpIsTimerSet() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpPostWork() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpQueryPoolStackInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleaseAlpcCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleaseCleanupGroup() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleaseCleanupGroupMembers() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleaseIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleaseJobNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleasePool() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleaseTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleaseWait() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpReleaseWork() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetDefaultPoolMaxThreads() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetDefaultPoolStackInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetPoolMaxThreads() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetPoolMaxThreadsSoftLimit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetPoolMinThreads() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetPoolStackInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetPoolThreadBasePriority() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetPoolThreadCpuSets() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetPoolWorkerThreadIdleTimeout() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetTimerEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetWait() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSetWaitEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpSimpleTryPost() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpStartAsyncIoOperation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpTimerOutstandingCallbackCount() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpTrimPools() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpWaitForAlpcCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpWaitForIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpWaitForJobNotification() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpWaitForTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpWaitForWait() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpWaitForWork() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpWorkOnBehalfClearTicket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void TpWorkOnBehalfSetTicket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void VerSetConditionMask() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WerReportExceptionWorker() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WerReportSQMEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmAddToAverageDWORD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmAddToStream() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmAddToStreamEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCheckEscalationAddToStreamEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCheckEscalationSetDWORD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCheckEscalationSetDWORD64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCheckEscalationSetString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCommonDatapointDelete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCommonDatapointSetDWORD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCommonDatapointSetDWORD64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCommonDatapointSetStreamEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmCommonDatapointSetString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmEndSession() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmEventEnabled() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmEventWrite() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmGetEscalationRuleStatus() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmGetInstrumentationProperty() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmIncrementDWORD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmIsOptedIn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmIsOptedInEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmIsSessionDisabled() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmSetDWORD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmSetDWORD64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmSetEscalationInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmSetIfMaxDWORD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmSetIfMinDWORD() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmSetString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmStartSession() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmStartSessionForPartner() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void WinSqmStartSqmOptinListener() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAcceptConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAccessCheck() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAccessCheckAndAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAccessCheckByType() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAccessCheckByTypeAndAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAccessCheckByTypeResultList() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAccessCheckByTypeResultListAndAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAccessCheckByTypeResultListAndAuditAlarmByHandle() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAcquireCrossVmMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAcquireProcessActivityReference() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAddAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAddAtomEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAddBootEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAddDriverEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAdjustGroupsToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAdjustPrivilegesToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAdjustTokenClaimsAndDeviceGroups() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlertMultipleThreadByThreadId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlertResumeThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlertThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlertThreadByThreadId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlertThreadByThreadIdEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAllocateLocallyUniqueId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAllocateReserveObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAllocateUserPhysicalPages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAllocateUserPhysicalPagesEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAllocateUuids() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAllocateVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAllocateVirtualMemoryEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcAcceptConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcCancelMessage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcConnectPortEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcCreatePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcCreatePortSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcCreateResourceReserve() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcCreateSectionView() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcCreateSecurityContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcDeletePortSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcDeleteResourceReserve() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcDeleteSectionView() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcDeleteSecurityContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcDisconnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcImpersonateClientContainerOfPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcImpersonateClientOfPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcOpenSenderProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcOpenSenderThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcQueryInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcQueryInformationMessage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcRevokeSecurityContext() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcSendWaitReceivePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAlpcSetInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwApphelpCacheControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAreMappedFilesTheSame() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAssignProcessToJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwAssociateWaitCompletionPacket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCallEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCallbackReturn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCancelIoFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCancelIoFileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCancelSynchronousIoFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCancelTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCancelTimer2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCancelWaitCompletionPacket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwChangeProcessState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwChangeThreadState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwClearEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwClose() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCloseObjectAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCommitComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCommitEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCommitRegistryTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCommitTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCompactKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCompareObjects() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCompareSigningLevels() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCompareTokens() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCompleteConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCompressKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwContinue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwContinueEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwConvertBetweenAuxiliaryCounterAndPerformanceCounter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCopyFileChunk() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateCpuPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateCrossVmEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateCrossVmMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateDebugObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateDirectoryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateDirectoryObjectEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateIRTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateIoRing() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateJobSet() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateKeyTransacted() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateKeyedEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateLowBoxToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateMailslotFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateNamedPipeFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreatePagingFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreatePartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreatePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreatePrivateNamespace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateProcessEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateProcessStateChange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateProfileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateRegistryTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateSectionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateSemaphore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateSymbolicLinkObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateThreadEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateThreadStateChange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateTimer2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateTokenEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateUserProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateWaitCompletionPacket() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateWaitablePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateWnfStateName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwCreateWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDebugActiveProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDebugContinue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDelayExecution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteBootEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteDriverEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteObjectAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeletePrivateNamespace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeleteWnfStateName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDeviceIoControlFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDirectGraphicsCall() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDisableLastKnownGood() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDisplayString() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDrawText() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDuplicateObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwDuplicateToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwEnableLastKnownGood() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwEnumerateBootEntries() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwEnumerateDriverEntries() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwEnumerateKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwEnumerateSystemEnvironmentValuesEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwEnumerateTransactionObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwEnumerateValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwExtendSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFilterBootOption() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFilterToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFilterTokenEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFindAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFlushBuffersFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFlushBuffersFileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFlushInstallUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFlushInstructionCache() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFlushKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFlushProcessWriteBuffers() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFlushVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFlushWriteBuffer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFreeUserPhysicalPages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFreeVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFreezeRegistry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFreezeTransactions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwFsControlFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetCachedSigningLevel() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetCompleteWnfStateSubscription() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetContextThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetCurrentProcessorNumber() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetCurrentProcessorNumberEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetDevicePowerState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetMUIRegistryInfo() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetNextProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetNextThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetNlsSectionPtr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetNotificationResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwGetWriteWatch() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwImpersonateAnonymousToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwImpersonateClientOfPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwImpersonateThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwInitializeEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwInitializeNlsFiles() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwInitializeRegistry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwInitiatePowerAction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwIsProcessInJob() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwIsSystemResumeAutomatic() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwIsUILanguageComitted() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwListenPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLoadDriver() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLoadEnclaveData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLoadKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLoadKey2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLoadKey3() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLoadKeyEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLockFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLockProductActivationKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLockRegistryKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwLockVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwMakePermanentObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwMakeTemporaryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwManageHotPatch() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwManagePartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwMapCMFModule() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwMapUserPhysicalPages() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwMapUserPhysicalPagesScatter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwMapViewOfSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwMapViewOfSectionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwModifyBootEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwModifyDriverEntry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwNotifyChangeDirectoryFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwNotifyChangeDirectoryFileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwNotifyChangeKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwNotifyChangeMultipleKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwNotifyChangeSession() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenCpuPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenDirectoryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenKeyEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenKeyTransacted() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenKeyTransactedEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenKeyedEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenObjectAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenPrivateNamespace() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenProcessToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenProcessTokenEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenRegistryTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenSemaphore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenSession() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenSymbolicLinkObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenThreadToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenThreadTokenEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwOpenTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPlugPlayControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPowerInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPrePrepareComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPrePrepareEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPrepareComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPrepareEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPrivilegeCheck() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPrivilegeObjectAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPrivilegedServiceAuditAlarm() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPropagationComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPropagationFailed() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwProtectVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPssCaptureVaSpaceBulk() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwPulseEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryAttributesFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryAuxiliaryCounterFrequency() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryBootEntryOrder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryBootOptions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryDebugFilterState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryDefaultLocale() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryDefaultUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryDirectoryFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryDirectoryFileEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryDirectoryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryDriverEntryOrder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryEaFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryFullAttributesFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationAtom() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationByName() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationCpuPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInformationWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryInstallUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryIntervalProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryIoRingCapabilities() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryLicenseValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryMultipleValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryOpenSubKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryOpenSubKeysEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryPerformanceCounter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryPortInformationProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryQuotaInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySecurityAttributesToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySecurityPolicy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySemaphore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySymbolicLinkObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySystemEnvironmentValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySystemEnvironmentValueEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySystemInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySystemInformationEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQuerySystemTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryTimerResolution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryVolumeInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueryWnfStateNameInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueueApcThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueueApcThreadEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwQueueApcThreadEx2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRaiseException() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRaiseHardError() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReadFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReadFileScatter() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReadOnlyEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReadRequestData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReadVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReadVirtualMemoryEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRecoverEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRecoverResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRecoverTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRegisterProtocolAddressInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRegisterThreadTerminatePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReleaseKeyedEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReleaseMutant() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReleaseSemaphore() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReleaseWorkerFactoryWorker() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRemoveIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRemoveIoCompletionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRemoveProcessDebug() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRenameKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRenameTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReplaceKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReplacePartitionUnit() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReplyPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReplyWaitReceivePort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReplyWaitReceivePortEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwReplyWaitReplyPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRequestPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRequestWaitReplyPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwResetEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwResetWriteWatch() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRestoreKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwResumeProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwResumeThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRevertContainerImpersonation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRollbackComplete() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRollbackEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRollbackRegistryTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRollbackTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwRollforwardTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSaveKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSaveKeyEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSaveMergedKeys() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSecureConnectPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSerializeBoot() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetBootEntryOrder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetBootOptions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetCachedSigningLevel() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetCachedSigningLevel2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetContextThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetDebugFilterState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetDefaultHardErrorPort() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetDefaultLocale() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetDefaultUILanguage() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetDriverEntryOrder() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetEaFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetEventBoostPriority() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetEventEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetHighEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetHighWaitLowEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetIRTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationCpuPartition() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationDebugObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationEnlistment() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationIoRing() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationResourceManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationSymbolicLink() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationToken() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationTransaction() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationTransactionManager() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetInformationWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetIntervalProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetIoCompletion() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetIoCompletionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetLdtEntries() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetLowEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetLowWaitHighEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetQuotaInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetSecurityObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetSystemEnvironmentValue() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetSystemEnvironmentValueEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetSystemInformation() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetSystemPowerState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetSystemTime() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetThreadExecutionState() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetTimer() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetTimer2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetTimerEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetTimerResolution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetUuidSeed() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetValueKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetVolumeInformationFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSetWnfProcessNotificationEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwShutdownSystem() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwShutdownWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSignalAndWaitForSingleObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSinglePhaseReject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwStartProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwStopProfile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSubmitIoRing() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSubscribeWnfStateChange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSuspendProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSuspendThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwSystemDebugControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwTerminateEnclave() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwTerminateJobObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwTerminateProcess() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwTerminateThread() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwTestAlert() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwThawRegistry() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwThawTransactions() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwTraceControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwTraceEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwTranslateFilePath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUmsThreadYield() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnloadDriver() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnloadKey() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnloadKey2() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnloadKeyEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnlockFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnlockVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnmapViewOfSection() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnmapViewOfSectionEx() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUnsubscribeWnfStateChange() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwUpdateWnfStateData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwVdmControl() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitForAlertByThreadId() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitForDebugEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitForKeyedEvent() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitForMultipleObjects() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitForMultipleObjects32() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitForSingleObject() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitForWorkViaWorkerFactory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitHighEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWaitLowEventPair() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWorkerFactoryWorkerReady() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWriteFile() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWriteFileGather() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWriteRequestData() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwWriteVirtualMemory() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void ZwYieldExecution() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void __C_specific_handler() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void __chkstk() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void __isascii() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void __iscsym() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void __iscsymf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void __misaligned_access() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void __toascii() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _atoi64() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _errnoNT() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _fltused() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _i64toa() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _i64toa_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _i64tow() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _i64tow_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _itoa() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _itoa_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _itow() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _itow_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _lfind() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _local_unwind() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ltoa() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ltoa_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ltow() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ltow_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _makepath_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _memccpy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _memicmp() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _setjmp() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _setjmpex() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _snprintf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _snprintf_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _snscanf_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _snwprintf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _snwprintf_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _snwscanf_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _splitpath() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _splitpath_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _strcmpi() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _stricmp() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _strlwr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _strlwr_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _strnicmp() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _strnset_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _strset_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _strupr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _strupr_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _swprintf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ui64toa() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ui64toa_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ui64tow() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ui64tow_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ultoa() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ultoa_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ultow() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _ultow_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _vscprintf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _vscwprintf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _vsnprintf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _vsnprintf_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _vsnwprintf() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _vsnwprintf_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void _vswprintf_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcscat() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcscat_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcschr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcscmp() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcscpy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcscpy_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcscspn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcslen() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsncat() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsncat_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsncmp() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsncpy() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsncpy_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsnlen() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcspbrk() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsrchr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsspn() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcsstr() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcstok_s() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcstol() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcstombs() {LouPrint("Hello nt Dll\n"); while(1);}
NTDLL_API void wcstoul() {LouPrint("Hello nt Dll\n"); while(1);}