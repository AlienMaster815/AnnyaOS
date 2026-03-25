#include <LouAPI.h>

LOUAPI uint16_t GetNPROC();

//static 
PSRCU_NODE_LIST_ITEM AllocateNewRcuNode(){
    //TODO Run this in a debuger to verify
    PSRCU_NODE_LIST_ITEM Result = 0x00;
    SIZE ProcCount = GetNPROC();
    return (PSRCU_NODE_LIST_ITEM)LouKeMallocEx(GetStructureSize(Result, SRcuItem.PerCpuRcuData, ProcCount), GET_ALIGNMENT(SRCU_NODE_LIST_ITEM), KERNEL_GENERIC_MEMORY);
}