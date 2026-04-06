#ifndef _TTF_HMTX_H
#define _TTF_HMTX_H

#include "../BootVid.h"

LOUSTATUS 
TtfParseHmtxData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             Object
);

#endif