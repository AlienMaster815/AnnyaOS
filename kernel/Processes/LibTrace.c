#include <LouAPI.h>

typedef struct _LOUSINE_LIB_TRACE_OBJ{
    ListHeader      Peers;
    PCHAR           ModID;
    UINT64          LibraryBase;
    UINT64          LibrarySize;
}LOUSINE_LIB_TRACE_OBJ, * PLOUSINE_LIB_TRACE_OBJ; 

static LOUSINE_LIB_TRACE_OBJ MasterLibTrace = {0};
static mutex_t LibTraceListLock = {0};

void LouKeLibTraceInitializeLibrarary(
    UINT64      LibraryBase,
    UINT64      LibrarySize,
    PCHAR       ModID
){
    PLOUSINE_LIB_TRACE_OBJ TmpObject = &MasterLibTrace;
    MutexLock(&LibTraceListLock);
    while(TmpObject->Peers.NextHeader){
        TmpObject = (PLOUSINE_LIB_TRACE_OBJ)TmpObject->Peers.NextHeader;
    }

    TmpObject->Peers.NextHeader = (PListHeader)LouKeMallocType(LOUSINE_LIB_TRACE_OBJ, KERNEL_GENERIC_MEMORY);
    MutexUnlock(&LibTraceListLock);
    
    TmpObject = (PLOUSINE_LIB_TRACE_OBJ)TmpObject->Peers.NextHeader;
    TmpObject->LibraryBase = LibraryBase;
    TmpObject->LibrarySize = LibrarySize;
    TmpObject->ModID = ModID;
}


void LouKeLibTraceCheckPanic(
    UINT64 Instruction
){
    PLOUSINE_LIB_TRACE_OBJ TmpObject = &MasterLibTrace;
    while(TmpObject->Peers.NextHeader){
        TmpObject = (PLOUSINE_LIB_TRACE_OBJ)TmpObject->Peers.NextHeader;
        if(RangeInterferes(
            TmpObject->LibraryBase,
            TmpObject->LibrarySize,
            Instruction,
            1
        )){
            
            LouPrint("%s Module Caused Fault At Module Mapped Offset:%h\n", TmpObject->ModID, Instruction - TmpObject->LibraryBase);
            return;
        }
    }   
    LouPrint("Kernel Or Runaway Instruction Caused Fault\n");
}