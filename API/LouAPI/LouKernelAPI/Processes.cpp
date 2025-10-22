#include <LouDDK.h>

#define KERNEL_PROCESS_ID 1

static HANDLE SessionManagerHandle = 0x00;

typedef struct _LOUSINE_KERNEL_PROCESS{
    PWIN_PEB ProcessExecutionBlock;
    
}LOUSINE_KERNEL_PROCESS, * PLOUSINE_KERNEL_PROCESS;

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeCreateProcessEx(
    PHANDLE             ProcessHandle,
    ACCESS_MASK         DesiredAccess,
    POBJECT_ATTRIBUTES  ObjectAttributes,
    HANDLE              ParrentProcess,
    ULONG               Flags,
    HANDLE              SectionHandle,
    HANDLE              DebugPort,
    HANDLE              TokenHandle,
    ULONG               JobMemberLevel,
    BOOL                AnnyaOSProcess
){
    if((!ProcessHandle) && (!ParrentProcess)){
        return STATUS_INVALID_PARAMETER;
    }

    


    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
void 
LouKeCreateSystemManagerProcess(){

    HANDLE SectionHandle = LouKeLoadPeExecutable("C:/ANNYA/SYSTEM64/ASMSS.EXE");

    LouKeCreateProcessEx(
        &SessionManagerHandle,
        PROCESS_ALL_ACCESS,
        0x00,
        (HANDLE)KERNEL_PROCESS_ID,
        0,
        SectionHandle,
        0x00,
        0x00,
        0x00,
        true
    );

}


LOUDDK_API_ENTRY uint64_t UpdateProcessManager(uint64_t CpuCurrentState){



    return CpuCurrentState;
}

LOUDDK_API_ENTRY void InitializeProcessManager(){
    LouPrint("Initializing Process Manager\n");



}