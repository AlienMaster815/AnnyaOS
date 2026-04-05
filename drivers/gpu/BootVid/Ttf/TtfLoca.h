#ifndef _TTF_LOCA_H
#define _TTF_LOCA_H 

LOUSTATUS 
TtfParseLocaData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
);

#endif