#ifndef _TTF_CMAP_H
#define _TTF_CMAP_H

#include "BootVid.h"

LOUSTATUS 
TtfParseCmapData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory
);

#endif