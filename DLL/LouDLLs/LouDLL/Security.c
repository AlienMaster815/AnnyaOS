//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "LouDll.h"

LOUDLL_API
LOUSTATUS 
LouCreateAccessToken(
    PHANDLE                 OutTokenHandle, 
    ACCESS_MASK             RequestedAccess,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
){
    UINT64 KulaPacket[6] = {0, 0, (UINT64)OutTokenHandle, (UINT64)RequestedAccess, (UINT64)SecurityDescriptor};
    while(!KulaPacket[0]){
        LouCALL(LOUCREATEACCESSTOKEN, (UINT64)&KulaPacket[0], 0);
    }
    return (LOUSTATUS)KulaPacket[1];
}

LOUDLL_API
void LouAccessCheckAndAuditAlarm(){
    LouPrint("LouAccessCheckAndAuditAlarm()\n");
    while(1);
}

LOUDLL_API
void LouAccessCheckByType(){
    LouPrint("LouAccessCheckByType()\n");
    while(1);
}

LOUDLL_API
void LouAccessCheckByTypeAndAuditAlarm(){
    LouPrint("LouAccessCheckByTypeAndAuditAlarm()\n");
    while(1);
}

LOUDLL_API
void LouAccessCheckByTypeResultList(){
    LouPrint("LouAccessCheckByTypeResultList()\n");
    while(1);
}

LOUDLL_API
void LouAccessCheckByTypeResultListAndAuditAlarm(){
    LouPrint("LouAccessCheckByTypeResultListAndAuditAlarm()\n");
    while(1);
}

LOUDLL_API
void LouAccessCheckByTypeResultListAndAuditAlarmByHandle(){
    LouPrint("LouAccessCheckByTypeResultListAndAuditAlarmByHandle()\n");
    while(1);
}

LOUDLL_API
void LouAcquireCMFViewOwnership(){
    LouPrint("LouAcquireCMFViewOwnership()\n");
    while(1);
}