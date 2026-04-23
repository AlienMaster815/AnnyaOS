//Copyright GPL-2 Tyler Grenier (2026)
#ifndef _TTF_CMAP_H
#define _TTF_CMAP_H

#include "../BootVid.h"

LOUSTATUS 
TtfParseCmapData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             Object
);

void 
TtfCloseCmapData(
    PTTF_OBJECT TtfObject
);

#endif