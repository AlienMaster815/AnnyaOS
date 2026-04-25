#include "LouDll.h"


LOUDLL_API
LOUSTATUS
LouCreateProcessA(
    LOUSTR      ProcessName,
    LOUSTR      FilePath,
    HPROCESS    ParrentProcess,
    ACCESS_MASK AccessMask,
    HPROCESS*   OutProcess     
){
    LOUSTATUS Status;
    HANDLE NewProcess;
    if(!FilePath || !OutProcess){
        return STATUS_INVALID_PARAMETER;
    }
    FILE* ProcessFile = LouOpenFileExA(FilePath, AccessMask);
    if(!ProcessFile){
        return STATUS_NO_SUCH_FILE;
    }
    Status = LouCreateSectionEx(
        &NewProcess,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        ProcessFile,
        0x00,
        0x00
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    //TODO: 
    //Create Access Token And Register It 
    //Create Process Object Return New Handle

    return STATUS_SUCCESS;
}