#include <LouAPI.h>
#include "Unicode.h"

static UTF_CHAR_MAP AsciiCharecters[] = { 
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000020 : ' '
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000021 : '!'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000022 : '"'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000023 : '#'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000024 : '$'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000025 : '%'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000026 : '&'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000027 : '''
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000028 : '('
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000029 : ')'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000002A : '*'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000002B : '+'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000002C : ','
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000002D : '-'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000002E : '.'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000002F : '/'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000030 : '0'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000031 : '1'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000032 : '2'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000033 : '3'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000034 : '4'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000035 : '5'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000036 : '6'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000037 : '7'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000038 : '8'
    {0, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_NUMBER | UTFCHAR_FLAG_HEXNUMBER}, //0x00000039 : '9'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000003A : ':'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000003B : ';'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000003C : '<'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000003D : '='
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000003E : '>'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000003F : '?'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000040 : '@'
    {0x61, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000041 : 'A'
    {0x62, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000042 : 'B'
    {0x63, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000043 : 'C'
    {0x64, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000044 : 'D'
    {0x65, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000045 : 'E'
    {0x66, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000046 : 'F'
    {0x67, UTFCHAR_FLAG_CHARECTER},                                             //0x00000047 : 'G'
    {0x68, UTFCHAR_FLAG_CHARECTER},                                             //0x00000048 : 'H'
    {0x69, UTFCHAR_FLAG_CHARECTER},                                             //0x00000049 : 'I'
    {0x6A, UTFCHAR_FLAG_CHARECTER},                                             //0x0000004A : 'J'
    {0x6B, UTFCHAR_FLAG_CHARECTER},                                             //0x0000004B : 'K'
    {0x6C, UTFCHAR_FLAG_CHARECTER},                                             //0x0000004C : 'L'
    {0x6D, UTFCHAR_FLAG_CHARECTER},                                             //0x0000004D : 'M'
    {0x6E, UTFCHAR_FLAG_CHARECTER},                                             //0x0000004E : 'N'
    {0x6F, UTFCHAR_FLAG_CHARECTER},                                             //0x0000004F : 'O'
    {0x70, UTFCHAR_FLAG_CHARECTER},                                             //0x00000050 : 'P'
    {0x71, UTFCHAR_FLAG_CHARECTER},                                             //0x00000051 : 'Q'
    {0x72, UTFCHAR_FLAG_CHARECTER},                                             //0x00000052 : 'R'
    {0x73, UTFCHAR_FLAG_CHARECTER},                                             //0x00000053 : 'S'
    {0x74, UTFCHAR_FLAG_CHARECTER},                                             //0x00000054 : 'T'
    {0x75, UTFCHAR_FLAG_CHARECTER},                                             //0x00000055 : 'U'
    {0x76, UTFCHAR_FLAG_CHARECTER},                                             //0x00000056 : 'V'
    {0x77, UTFCHAR_FLAG_CHARECTER},                                             //0x00000057 : 'W'
    {0x78, UTFCHAR_FLAG_CHARECTER},                                             //0x00000058 : 'X'
    {0x79, UTFCHAR_FLAG_CHARECTER},                                             //0x00000059 : 'Y'
    {0x7A, UTFCHAR_FLAG_CHARECTER},                                             //0x0000005A : 'Z'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000005B : '['
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000005C : '\'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000005D : ']'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000005E : '^'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000005F : '_'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x00000060 : '`'
    {0x41, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000061 : 'a'
    {0x42, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000062 : 'b'
    {0x43, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000063 : 'c'
    {0x44, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000064 : 'd'
    {0x45, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000065 : 'e'
    {0x46, UTFCHAR_FLAG_CHARECTER | UTFCHAR_FLAG_HEXNUMBER},                    //0x00000066 : 'f'
    {0x47, UTFCHAR_FLAG_CHARECTER},                                             //0x00000067 : 'g'
    {0x48, UTFCHAR_FLAG_CHARECTER},                                             //0x00000068 : 'h'
    {0x49, UTFCHAR_FLAG_CHARECTER},                                             //0x00000069 : 'i'
    {0x4A, UTFCHAR_FLAG_CHARECTER},                                             //0x0000006A : 'j'
    {0x4B, UTFCHAR_FLAG_CHARECTER},                                             //0x0000006B : 'k'
    {0x4C, UTFCHAR_FLAG_CHARECTER},                                             //0x0000006C : 'l'
    {0x4D, UTFCHAR_FLAG_CHARECTER},                                             //0x0000006D : 'm'
    {0x4E, UTFCHAR_FLAG_CHARECTER},                                             //0x0000006E : 'n'
    {0x4F, UTFCHAR_FLAG_CHARECTER},                                             //0x0000006F : 'o'
    {0x50, UTFCHAR_FLAG_CHARECTER},                                             //0x00000070 : 'p'
    {0x51, UTFCHAR_FLAG_CHARECTER},                                             //0x00000071 : 'q'
    {0x52, UTFCHAR_FLAG_CHARECTER},                                             //0x00000072 : 'r'
    {0x53, UTFCHAR_FLAG_CHARECTER},                                             //0x00000073 : 's'
    {0x54, UTFCHAR_FLAG_CHARECTER},                                             //0x00000074 : 't'
    {0x55, UTFCHAR_FLAG_CHARECTER},                                             //0x00000075 : 'u'
    {0x56, UTFCHAR_FLAG_CHARECTER},                                             //0x00000076 : 'v'
    {0x57, UTFCHAR_FLAG_CHARECTER},                                             //0x00000077 : 'w'
    {0x58, UTFCHAR_FLAG_CHARECTER},                                             //0x00000078 : 'x'
    {0x59, UTFCHAR_FLAG_CHARECTER},                                             //0x00000079 : 'y'
    {0x5A, UTFCHAR_FLAG_CHARECTER},                                             //0x0000007A : 'z'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000007B : '{'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000007C : '|'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000007D : '}'
    {0, UTFCHAR_FLAG_CHARECTER},                                                //0x0000007E : '~'
};

static UTF_CHAR_MAP_TRACKER AsciiMap = {
    .CharMap = AsciiCharecters,
    .MapBase = 0x20,
    .MapSize = ARRAY_SIZE(AsciiCharecters),
};

static mutex_t UnicodeLock = {0};
static ListHeader UnicodeList = {
    .NextHeader = &AsciiMap.Peers,
};

PUTF_CHAR_MAP 
LouKeGetUnicodeMap(
    UINT32 Charecter
){
    PUTF_CHAR_MAP_TRACKER TmpTracker;
    PUTF_CHAR_MAP Result = 0x00;
    MutexLock(&UnicodeLock);
    ForEachListEntry(TmpTracker, &UnicodeList, Peers){
        if(RangeInterferes(Charecter, 1, TmpTracker->MapBase, TmpTracker->MapSize)){
            Result = &TmpTracker->CharMap[Charecter - TmpTracker->MapBase];
            goto _DONE;
        }
    }
    _DONE:
    MutexUnlock(&UnicodeLock);
    return Result;
}