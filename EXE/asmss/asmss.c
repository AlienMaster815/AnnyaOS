//Copyright GPL-2 Tyler Grenier (2025 - 2026)
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

LOUSTATUS AnnyaSmssProcessStartup(HANDLE Peb){

    LouPrint("ASMSS: Hello User Mode\n");

    //LouExitDosMode();

    //HPROCESS WindowManager;

    LouCreateProcessA(
        AWM_PROCESS_NAME,
        "C:/ANNYA/SYSTEM64/AWM.EXE",
        0x00,
        ACCESS_MASK_GENERIC_ALL,
        PROCESS_PRIORITY_HIGH,
        0x00
    );

    //TODO: Check object manager to make sure its safe to continue

    LouPrint("Session Manager Successfully Initialized\n");
    while(1);
}