#include <LouACPI.h>
#include <acpi.h>

typedef struct _DEBUGGER_COMMUNICATIONS_DEVICE{
    ListHeader Peers;
    void (*PrintCharecter)(char Charecter);
}DEBUGGER_COMMUNICATIONS_DEVICE, * PDEBUGGER_COMMUNICATIONS_DEVICE;

static DEBUGGER_COMMUNICATIONS_DEVICE MainDebuggerList = {0};

#define SEND_CHARECTER_TO_VIRTUALBOX_DEBBUGGER(X) outb(0x0504, (X))

void VirtualboxDebuggerPrintCharecter(char Charecter){
    switch(Charecter){
        case '\n':{
            SEND_CHARECTER_TO_VIRTUALBOX_DEBBUGGER('\r');
            SEND_CHARECTER_TO_VIRTUALBOX_DEBBUGGER('\n');
            break;
        }
        default:{
            SEND_CHARECTER_TO_VIRTUALBOX_DEBBUGGER(Charecter);
            break;
        }
    }
}

void InitializeDebuggerComunications(){

    PFIXED_ACPI_DESCRIPTION_TABLE Fadt = LouKeAquireAcpiTable(FIXED_ACPI_DESCRIPTION);
    PDEBUGGER_COMMUNICATIONS_DEVICE Com;
    if(!Fadt){
        return;
    }

    if(memcmp(Fadt->FadtHeader.OemID, "VBOX  ", 6) == 0){
        Com = &MainDebuggerList;
        while(Com->Peers.NextHeader){
            Com = (PDEBUGGER_COMMUNICATIONS_DEVICE)Com->Peers.NextHeader;
        }
        Com->PrintCharecter = VirtualboxDebuggerPrintCharecter;
        Com->Peers.NextHeader = (PListHeader)LouKeMallocType(DEBUGGER_COMMUNICATIONS_DEVICE, KERNEL_GENERIC_MEMORY);
        ((PDEBUGGER_COMMUNICATIONS_DEVICE)Com->Peers.NextHeader)->Peers.LastHeader = (PListHeader)Com;
        LouPrint("HELLO VIRTUALBOX DEBUGGER\n");
    }
}

void LouKeDebuggerCommunicationsSendCharecter(char Charecter){
    PDEBUGGER_COMMUNICATIONS_DEVICE Com = &MainDebuggerList;
    while(Com){
        if (Com->PrintCharecter) {
            Com->PrintCharecter(Charecter);
        }
        if (!Com->Peers.NextHeader)
            break;
        Com = (PDEBUGGER_COMMUNICATIONS_DEVICE)Com->Peers.NextHeader;
    }
}

void LouKeThrowPc(){
    DEBUG_TRAP
}