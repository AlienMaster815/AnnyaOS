#include <LouAPI.h>


static uint8_t PspHostSiloGlobals[832]; 


int64_t PsIsServerSilo(void* arg1) {
    // If the input pointer is not null, check the value at the offset 0x5d0
    if (arg1 != NULL) {
        bool result = *((uint8_t*)arg1 + 0x5d0) != 0;
        return result;
    }
    
    // If the input pointer is null, return true (1)
    return 1;
}

void* PsGetCurrentServerSiloGlobals() {
    // Retrieve the gsbase value (current processor's GS segment base address)
    uint64_t gsbase = __readgsqword(0);;
    
    // Check if the value at offset 0x1A0 is 0
    if (*(void**)((uintptr_t)gsbase + 0x1A0) == 0) {
        void* rax = *(void**)((uintptr_t)gsbase + 0x188);
        void* rcx = *(void**)((uintptr_t)rax + 0x658);
        
        if (rcx == (void*)-3) {
            rcx = *(void**)((uintptr_t)(*(void**)((uintptr_t)rax + 0x220)) + 0x870);
        } else if (rcx != NULL) {
            // Loop through until a server silo is found
            while (!PsIsServerSilo(rcx)) {
                rcx = *(void**)((uintptr_t)rcx + 0x508);
            }
        }
        
        // Return the silo's globals if one is found
        if (rcx != NULL) {
            return *(void**)((uintptr_t)rcx + 0x5D0);
        }
    }
    
    // If no server silo globals found, return PspHostSiloGlobals
    return &PspHostSiloGlobals;
}

//Process Manager


typedef struct  __attribute__((packed)) _CPUContext{
    // General-Purpose Registers    
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r8;

    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;

    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;

    uint64_t cs;
    uint64_t fq;
    uint64_t FaultStack;
    uint64_t ss;
} CPUContext;


static uint64_t ActiveWin32Binaries = 0;
static LOADED_WIN32_BINARY_OBJECT MasterBinObjList;
static spinlock_t LouKeCreateBinaryObjectLogLock;

PLOADED_WIN32_BINARY_OBJECT 
LouKeCreateBinaryObjectLog(
    string BinaryName
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(
        &LouKeCreateBinaryObjectLogLock,
        &Irql
    );

    PLOADED_WIN32_BINARY_OBJECT NewObject;
    
    if(!ActiveWin32Binaries){
        //if no active binaries exist use the master Object
        ActiveWin32Binaries++;
        LouKeReleaseSpinLock(
            &LouKeCreateBinaryObjectLogLock,
            &Irql
        );
        return &MasterBinObjList;
    }
    //Otherwise start going through the list
    PLOADED_WIN32_BINARY_OBJECT CurrentListEnd = 
   (PLOADED_WIN32_BINARY_OBJECT)LouKeGetListEnd(
        (PListHeader)&MasterBinObjList.Neighbors, 
        (size_t)      ActiveWin32Binaries
    );
    //Create A New Object
    NewObject = (PLOADED_WIN32_BINARY_OBJECT)LouMallocEx(sizeof(LOADED_WIN32_BINARY_OBJECT) ,1);
    CurrentListEnd->Neighbors.NextHeader = (PListHeader)NewObject;
    ActiveWin32Binaries++;
    LouKeReleaseSpinLock(
        &LouKeCreateBinaryObjectLogLock,
        &Irql
    );
    return NewObject;
}

LOUSTATUS 
LouKeDestroyBinaryObject(
    PLOADED_WIN32_BINARY_OBJECT BinaryObjectHandle
){
    return LouKeUnLinkMemberFromList(
        (PListHeader)&MasterBinObjList.Neighbors, 
        (PListHeader) BinaryObjectHandle, 
        (size_t)      ActiveWin32Binaries
    );
}


LOUSTATUS LouKeMallocBinarySectionLogs(
    PLOADED_WIN32_BINARY_OBJECT BinaryObject,
    size_t NumberOfLogs
){
    if(!BinaryObject){
        return STATUS_INVALID_PARAMETER;
    }

    BinaryObject->SectionCount = NumberOfLogs;
    BinaryObject->SectionObject = (PSECTION_HEADER)LouMallocEx((sizeof(SECTION_HEADER) * NumberOfLogs), 1); 
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeLogBinarySection(
    PLOADED_WIN32_BINARY_OBJECT BinaryObject,
    size_t SectionNumber,
    PSECTION_HEADER Header
){
    // Validate input pointers
    if ((BinaryObject == 0x00) || (BinaryObject->SectionObject == 0x00) || (Header == 0x00)) {
        return STATUS_INVALID_PARAMETER;
    }

    // Bounds check for SectionNumber
    if (SectionNumber >= BinaryObject->SectionCount) {
        return STATUS_INVALID_PARAMETER;
    }

    memcpy((void*)&BinaryObject->SectionObject[SectionNumber], Header, sizeof(SECTION_HEADER));
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeGetFaultBnaryHande(
    PPROCESS_EXCEPTION_DATA_PACKET DataPacket
){
    if(!DataPacket){
        return STATUS_INVALID_PARAMETER;
    }
    
    UNUSED CPUContext* FaultContext = DataPacket->OutData.FaultContext;
    PLOADED_WIN32_BINARY_OBJECT SlaveHandle = &MasterBinObjList;

    for(uint64_t i = 0;i < ActiveWin32Binaries ;i++){
        if(
            (FaultContext->rip >= SlaveHandle->VirtualLoadedAddress) && 
            (FaultContext->rip < (SlaveHandle->VirtualLoadedAddress + SlaveHandle->TotalUsedMemory)) 
        ){
            DataPacket->InData.ProcessOfFault = SlaveHandle;
            return STATUS_SUCCESS;
        }
        if(SlaveHandle->Neighbors.NextHeader){
            SlaveHandle = (PLOADED_WIN32_BINARY_OBJECT)SlaveHandle->Neighbors.NextHeader;
        }
    }
    DataPacket->InData.ProcessOfFault = 0x00;
    return STATUS_UNSUCCESSFUL;
}

static inline PBUTTON_BINARY_LOG CreateButtonLog(PLOADED_WIN32_BINARY_OBJECT BinaryBind){
    PBUTTON_BINARY_LOG TmpLog = &BinaryBind->ButtonLogs;
    
    for(size_t i = 0 ; i < BinaryBind->NumButtonLogs; i++){
        if(TmpLog->Neighbors.NextHeader){
            TmpLog = (PBUTTON_BINARY_LOG)TmpLog->Neighbors.NextHeader;
        }
    }   

    PBUTTON_BINARY_LOG NewLog = LouMalloc(sizeof(BUTTON_BINARY_LOG));
    TmpLog->Neighbors.NextHeader = (PListHeader)NewLog;
    return NewLog;
}

static inline void DestroyButtonLog(
    PLOADED_WIN32_BINARY_OBJECT BinaryBind,
    PBUTTON_BINARY_LOG          BinaryLog
){
    PBUTTON_BINARY_LOG TmpLog = &BinaryBind->ButtonLogs;
    for(uint64_t i = 0 ; i < BinaryBind->NumButtonLogs; i++){
        if(TmpLog->Neighbors.NextHeader){
            TmpLog = (PBUTTON_BINARY_LOG)TmpLog->Neighbors.NextHeader;
        }
        if(TmpLog == BinaryLog){
            PBUTTON_BINARY_LOG TmpLog2 = &BinaryBind->ButtonLogs;
            for(uint64_t j = 0 ; j < i; j++){
                if(TmpLog->Neighbors.NextHeader){
                    TmpLog2 = (PBUTTON_BINARY_LOG)TmpLog->Neighbors.NextHeader;
                }
            }
            TmpLog2->Neighbors.NextHeader = TmpLog->Neighbors.NextHeader;
            LouFree((RAMADD)TmpLog);
        }
    }
}

void LogButtonToProccess(
    PBUTTONHANDLE ButtonHandle, 
    PLOADED_WIN32_BINARY_OBJECT BinaryBind
){
    LouPrint("Registering Button:%h To Process:%h\n", ButtonHandle, BinaryBind);
    PBUTTON_BINARY_LOG ButtonLog = CreateButtonLog(BinaryBind);
    ButtonLog->ButtonHandle = ButtonHandle;
}

LOUSTATUS LouKeRegisterCallbackProcedure(
    void* CallbackHandler,
    PLOADED_WIN32_BINARY_OBJECT BinaryBind
){
    if((!BinaryBind) || (!CallbackHandler)){
        //Endof Systemcall
        return STATUS_INVALID_PARAMETER;
    }
    BinaryBind->WndProc = (int(*)(void*,uint32_t,void*,void*))CallbackHandler;
    //Endof SystemCall
    LouPrint("Added Callback Procedure:%h To Process:%h\n", CallbackHandler, BinaryBind);
    return  STATUS_SUCCESS;
}



//Endof Process Manager