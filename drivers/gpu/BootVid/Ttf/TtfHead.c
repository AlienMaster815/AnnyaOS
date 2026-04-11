#include "../BootVid.h"

LOUSTATUS 
TtfParseHeadData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
){
    PTTF_HEAD_TABLE HeadTable = (PTTF_HEAD_TABLE)((UINTPTR)File + Directory->Offset);
    INT16 XMin = TtfReadUint16(HeadTable->XMin);;
    INT16 YMin = TtfReadUint16(HeadTable->YMin);;
    TtfObject->UsesLongLocaTableFormat =  TtfReadUint16(HeadTable->IndexToLocFormat) ? true : false;
    TtfObject->UnitsPerEm = TtfReadUint16(HeadTable->UnitsPerEm);
    TtfObject->ShiftY = (YMin < 0) ? ABS(YMin) : 0;
    TtfObject->ShiftX = (XMin < 0) ? ABS(XMin) : 0;
    return STATUS_SUCCESS;
}