#include "asmss.h"

NTSTATUS AnnyaSmssNtProcessStartup(HANDLE Peb){

    LouExitDosMode();

    LouPrint("ASMSS: Hello User Mode\n");    
        
    while(1);
}