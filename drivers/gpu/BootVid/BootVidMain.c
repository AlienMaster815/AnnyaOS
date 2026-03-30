#include "BootVid.h"

LOUAPI
LOUSTATUS
BootVidEntry(){
    LouPrint("BOOTVID.SYS:BootVidEntry()\n");

    

    LouPrint("BOOTVID.SYS:BootVidEntry():STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}