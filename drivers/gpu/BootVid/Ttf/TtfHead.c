#include "../BootVid.h"

LOUSTATUS 
TtfParseHeadData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
){
    PTTF_HEAD_TABLE HeadTable = (PTTF_HEAD_TABLE)((UINTPTR)File + Directory->Offset);

    TtfObject->UsesLongLocaTableFormat =  TtfReadUint16(HeadTable->IndexToLocFormat) ? true : false;
    TtfObject->UnitsPerEm = TtfReadUint16(HeadTable->UnitsPerEm);

    return STATUS_SUCCESS;
}