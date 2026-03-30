#include "DrsdCore.h"


DRIVER_EXPORT
void 
DrsdMmInitialize(
    PDRSD_MM    Mm, 
    UINT64      Start, 
    UINT64      Size
){

    Mm->ColorAdjust = 0x00;
    Mm->IntervalTree = 0x00;    
    Mm->HolesSize = 0x00;    
    Mm->HolesAddress = 0x00;    

    Mm->HeadNode.Flags = 0;
    Mm->HeadNode.Mm = Mm;
    Mm->HeadNode.Start = Start + Size;
    Mm->HeadNode.Size = -Size;

    //TODO: Add Hole

    Mm->ScanActive = 0;
}
