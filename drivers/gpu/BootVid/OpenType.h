//Copyright GPL-2 Tyler Grenier (2026)
#ifndef _MINI_OPEN_TYPE_H
#define _MINI_OPEN_TYPE_H

#include "BootVid.h"

//TTF Required Tables
#define TTF_CHARECTER_TO_GLYPH_MAPPING  'cmap'
#define TTF_GLYPH_DATA                  'glyf'
#define TTF_FONT_HEADER                 'head'
#define TTF_HORIZONTAL_HEADER           'hhea'
#define TTF_HORIZONTAL_METRICS          'hmtx'
#define TTF_INDEX_TO_LOCATION           'loca'
#define TTF_MAXIMUM_PROFILE             'maxp'
#define TTF_NAMING                      'name'
#define TTF_POST_SCRIPT                 'post'
//end

//TTF Optional Tables
#define TTF_CONTROL_VALUE               'cvt\0'
#define TTF_FONT_PROGRAM                'fpgm'
#define TTF_HORIZONTAL_DEVICE_METRICS   'hdmx'
#define TTF_KERNING                     'kern'
#define TTF_OS2                         'OS/2'
#define TTF_CONTROL_VALUE_PROGRAM       'prep'
//end

typedef struct PACKED _TTF_OFFSET_SUBTABLE{
    UINT32  ScalerType;
    UINT16  TableCount;
    UINT16  SearchRange;
    UINT16  EntrySelector;
    UINT16  RangeShift;
}TTF_OFFSET_SUBTABLE, * PTTF_OFFSET_SUBTABLE;

typedef struct PACKED _TTF_TABLE_DIRECTORY{
    UINT32  Tag;
    UINT32  Checksum;
    UINT32  Offset;
    UINT32  Length;
}TTF_TABLE_DIRECTORY, * PTTF_TABLE_DIRECTORY;

typedef struct _TTFOBJ_OFFSET_SUBTABLE{
    UINT32  ScalerType;
    UINT16  TableCount;
    UINT16  SearchRange;
    UINT16  EntrySelector;
    UINT16  RangeShift;
}TTFOBJ_OFFSET_SUBTABLE, * PTTFOBJ_OFFSET_SUBTABLE;

typedef struct _TTFOBJ_TABLE_DIRECTORY{
    UINT32  Tag;
    UINT32  Checksum;
    UINT32  Offset;
    UINT32  Length;
    PVOID   Data;
}TTFOBJ_TABLE_DIRECTORY, * PTTFOBJ_TABLE_DIRECTORY;

typedef struct _TTF_OBJECT{
    TTFOBJ_OFFSET_SUBTABLE     OffsetSubTable;
    PTTFOBJ_TABLE_DIRECTORY    TableDirectories;
}TTF_OBJECT, * PTTF_OBJECT; 

UINT8       TtfReadUint8(PVOID Data);
UINT16      TtfReadUint16(PVOID Data);
UINT32      TtfReadUint32(PVOID Data);
UINT64      TtfReadUint64(PVOID Data);
int         TtfMemCmp(PVOID Data, PVOID Check, size_t Size);
LOUSTATUS   TtfInitializeFile(PVOID TtfStream);

#endif