#include "LouDll.h"

LOUDLL_API
LOUSTATUS 
LouCreateProcessEx2(
    PHPROCESS                       HandleOut,                       
    string                          ProcessName,
    HPROCESS                        ParentProcess,  
    UINT8                           Priority,                 
    HANDLE                          Section,
    HANDLE                          AccessToken,
    PLOUSINE_CREATE_PROCESS_PARAMS  Params 
){
    UINT64 KulaPacket[9] = {0, 0, (UINT64)HandleOut, (UINT64)ProcessName, (UINT64)ParentProcess, (UINT64)Priority, (UINT64)Section, (UINT64)AccessToken, (UINT64)Params};

    while(KulaPacket[0] != 1){
        LouCALL(LOUCREATEPROCESS, (UINT64)&KulaPacket[0], 0);
    }
    return (LOUSTATUS)KulaPacket[1];
}



LOUDLL_API
LOUSTATUS
LouCreateProcessA(
    LOUSTR      ProcessName,
    LOUSTR      FilePath,
    HPROCESS    ParrentProcess,
    ACCESS_MASK RequestedAccess,
    UINT8       Priority,
    PHPROCESS   OutProcess     
){

    LOUSTATUS Status;
    HANDLE NewProcessSection;
    if(!FilePath){
        return STATUS_INVALID_PARAMETER;
    }
    FILE* ProcessFile = LouOpenFileExA(FilePath, RequestedAccess);
    if(!ProcessFile){
        return STATUS_NO_SUCH_FILE;
    }

    Status = LouCreateSectionEx(
        &NewProcessSection,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        ProcessFile,
        0x00,
        0x00
    );

    LouCloseFileA(
        ProcessFile
    );

    if(Status != STATUS_SUCCESS){
        return Status;
    }

    HANDLE NewTokenHandle;
    LouCreateAccessToken(
        &NewTokenHandle,
        RequestedAccess,
        0x00
    );

    Status = LouCreateProcessEx2(
        OutProcess,
        ProcessName,
        0x00,
        Priority,
        NewProcessSection,
        NewTokenHandle,
        0
    );
    if(Status != STATUS_SUCCESS){
        //TODO: Destroy Section
        LouPrint("LouCreateProcessA()\n");
        return Status;
    }
    return STATUS_SUCCESS;
}