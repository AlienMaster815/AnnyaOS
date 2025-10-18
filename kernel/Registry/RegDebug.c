#include <LouAPI.h>
#include "Registry.h"

void LouKeDumpRegData(
    PVOID RegHandle
){
    LouPrint("Offset:%h\n", GetRegHiveOffsetHandle(RegHandle));
    LouPrint("Item Offset:%h\n", GET_ITEM_OFFSET(&((PCOMPILED_NODE_ENTRY)RegHandle)->Node));
    LouPrint("Item Opcode:%h\n", GET_ITEM_OPCODE(&((PCOMPILED_NODE_ENTRY)RegHandle)->Node));
}   