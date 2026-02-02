#include "asmss.h"

/*__declspec(dllimport)
LOUSTATUS 
LouCreateSectionEx(
    PHANDLE                 OutSectionHandle,
    ACCESS_MASK             DesiredAccess,
    POBJECT_ATTRIBUTES      ObjectAttributes,
    PLARGE_INTEGER          MaximumSize,
    ULONG                   SectionPageProtection,
    ULONG                   AllocationAttributes,
    HANDLE                  FileHandle,
    PMEM_EXTENDED_PARAMETER ExtendedParameters,
    ULONG                   ExtendedParameterCount
);*/

static HANDLE SessionManagerProcessHandle = 0x00;

NTSTATUS AnnyaSmssProcessStartup(HANDLE Peb){

    //LouExitDosMode();

    LouPrint("ASMSS: Hello User Mode\n");    

    LouOpenFileA("C:/ANNYA/SYSTEM64/INIT.EXE");

    while(1);
    
    FILE* SessionManagerBinary = 0x00;
    if(!SessionManagerBinary){
        return STATUS_UNSUCCESSFUL;
    }

    LouCreateSectionEx(
        &SessionManagerProcessHandle,
        0,0,0,0,0,
        SessionManagerBinary,
        0,0
    );

    

    LouPrint("Session Manager Successfully Initialized\n");
    while(1);
}