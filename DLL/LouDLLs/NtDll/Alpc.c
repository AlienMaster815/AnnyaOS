#include "ntdll.h"

int64_t LouAlpcSetInformation(
    uint64_t PortHandle, 
    uint64_t size,       
    uint64_t ConcurrencyCount,
    uint64_t AlpcCompletionCurrencyCount
){
    uint64_t KulaPacket[5] = {0};
    KulaPacket[1] = PortHandle;
    KulaPacket[2] = size;
    KulaPacket[3] = ConcurrencyCount;
    KulaPacket[4] = AlpcCompletionCurrencyCount;
    while(KulaPacket[0] != 1){
        LouCALL(LouAlpcSetInformationCall, (uint64_t)&KulaPacket, LOUCALL_WIN64_EMU);
    }
    return KulaPacket[1];
}

int64_t NtLowLouAplcSetInformation();

NTDLL_API 
int64_t AlpcAdjustCompletionListConcurrencyCount(){
    return NtLowLouAplcSetInformation(); 
}

NTDLL_API
void AlpcFreeCompletionListMessage(

){
    LouPrint("Hello NT DLL\n"); while(1);
}

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