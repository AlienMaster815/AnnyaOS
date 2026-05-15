#ifndef _KERNEL_UNICODE_H
#define _KERNEL_UNICODE_H

#define UTFCHAR_FLAG_CHARECTER      (1 << 0)
#define UTFCHAR_FLAG_LOWERCASE      (1 << 1)
#define UTFCHAR_FLAG_NUMBER         (1 << 2)
#define UTFCHAR_FLAG_HEXNUMBER      (1 << 3)

typedef struct _UTF_CHAR_MAP{
    UINT32      Sibling;
    UINT8       CharecterFlags;
}UTF_CHAR_MAP, * PUTF_CHAR_MAP;

typedef struct _UTF_CHAR_MAP_TRACKER{
    ListHeader      Peers;
    PUTF_CHAR_MAP   CharMap;
    SIZE            MapBase;
    SIZE            MapSize;
}UTF_CHAR_MAP_TRACKER, * PUTF_CHAR_MAP_TRACKER;

PUTF_CHAR_MAP 
LouKeGetUnicodeMap(
    UINT32 Charecter
);

#endif