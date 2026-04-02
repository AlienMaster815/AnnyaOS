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

//CMAP Spec Meta Data
typedef struct PACKED _TTF_CMAP_SUBTABLE{
    UINT16  PlatformID;
    UINT16  PlatformSpecID;
    UINT32  Offset;
}TTF_CMAP_SUBTABLE, * PTTF_CMAP_SUBTABLE;

typedef struct PACKED _TTF_CMAP_INDEX{
    UINT16  Version;
    UINT16  SubTableCount;
}TTF_CMAP_INDEX, * PTTF_CMAP_INDEX;

typedef struct PACKED _TTF_CMAP_FORMAT0{
    UINT16      Format;     //0
    UINT16      Length;     //262
    UINT16      Language;   //Macintosh only
    UINT8       GlyphArrayIndex[256];
}TTF_CMAP_FORMAT0, * PTTF_CMAP_FORMAT0;

typedef struct PACKED _TTF_CMAP_FORMAT2{
    UINT16      Format;     //0
    UINT16      Length;     //262
    UINT16      Language;   //Macintosh only
    UINT16      SubHeaderKeys[256];
    UINT16      VariableData[];
}TTF_CMAP_FORMAT2, * PTTF_CMAP_FORMAT2;

typedef struct PACKED _TTF_CMAP_FORMAT4{
    UINT16      Format;     //0
    UINT16      Length;     //262
    UINT16      Language;   //Macintosh only
    UINT16      SegCountX2;
    UINT16      SearchRange;
    UINT16      EntrySelector;
    UINT16      RangeShift;
    #define     TTF_CMAP_FORMAT4_END_CODE_PTR(x, y)          ((UINT16*)LouKeCastToUnalignedPointer(&(x)->VariableData[y]))
    #define     TTF_CMAP_FORMAT4_START_CODE_PTR(x, y)        ((UINT16*)LouKeCastToUnalignedPointer(&(x)->VariableData[(TtfReadUint16((x)->SegCountX2) / 2)     + 1 + (y)]))
    #define     TTF_CMAP_FORMAT4_ID_DELTA_PTR(x, y)          ((UINT16*)LouKeCastToUnalignedPointer(&(x)->VariableData[(TtfReadUint16((x)->SegCountX2) / 2) * 2 + 1 + (y)]))
    #define     TTF_CMAP_FORMAT4_ID_RANGE_OFFSET_PTR(x, y)   ((UINT16*)LouKeCastToUnalignedPointer(&(x)->VariableData[(TtfReadUint16((x)->SegCountX2) / 2) * 3 + 1 + (y)]))
    UINT16      VariableData[];
}TTF_CMAP_FORMAT4, * PTTF_CMAP_FORMAT4;


typedef struct PACKED _TTF_CMAP_FORMAT_HEADER{
    UINT16      Format;
    UINT16      Length;
    UINT16      Language;//Macintosh only
}TTF_CMAP_FORMAT_HEADER, * PTTF_CMAP_FORMAT_HEADER;

//end

//CMAP Bootvid Meta Data
typedef struct _TTFOBJ_CMAP_INDEX{
    UINT16  Version;
    UINT16  SubTableCount;
}TTFOBJ_CMAP_INDEX, * PTTFOBJ_CMAP_INDEX;

typedef struct _TTFOBJ_CMAP_SUBTABLE{
    UINT16  PlatformID;
    UINT16  PlatformSpecID;
    UINT32  Offset;
}TTFOBJ_CMAP_SUBTABLE, * PTTFOBJ_CMAP_SUBTABLE;

typedef struct _TTF_OBJECT_CMAP_META_DATA{
    TTFOBJ_CMAP_INDEX       Index;
    PTTFOBJ_CMAP_SUBTABLE   SubTables;
    UINT16                  AsciiSpace[127];
    UINT16                  RussianSpace[256];
}TTF_OBJECT_CMAP_META_DATA, * PTTF_OBJECT_CMAP_META_DATA;

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
    TTFOBJ_OFFSET_SUBTABLE      OffsetSubTable;
    PTTFOBJ_TABLE_DIRECTORY     TableDirectories;
    TTF_OBJECT_CMAP_META_DATA   CmapMetaData;
}TTF_OBJECT, * PTTF_OBJECT; 

UINT8       TtfReadUint8(UINT8 Data);
UINT16      TtfReadUint16(UINT16 Data);
UINT32      TtfReadUint32(UINT32 Data);
UINT64      TtfReadUint64(UINT64 Data);
int         TtfMemCmp(PVOID Data, PVOID Check, size_t Size);
LOUSTATUS   TtfInitializeFile(PVOID TtfStream);

#endif