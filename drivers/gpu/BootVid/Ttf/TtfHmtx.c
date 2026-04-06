#include "../BootVid.h"

LOUSTATUS 
TtfParseHmtxData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
){

    TtfDrawGlyphEx(TtfObject, TtfObject->AsciiGlyphData['A'], 10, 10, 128, SET_RGB(0, 255, 0));

    //UINT8* Flags;
    BootRenderSyncScreen();

    return STATUS_SUCCESS;
}
