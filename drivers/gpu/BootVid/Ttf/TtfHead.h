#ifndef _TTF_HEAD_H
#define _TTF_HEAD_H

#include "../BootVid.h"

LOUSTATUS 
TtfParseHeadData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
);

#endif