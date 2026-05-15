#include <LouAPI.h>
#include "Unicode.h"

UINT32 LouKeUtf32ToUpper(UINT32 C){
    PUTF_CHAR_MAP Map = LouKeGetUnicodeMap(C);
    if(!Map){
        return C;
    }
    else if(Map->CharecterFlags & UTFCHAR_FLAG_LOWERCASE && Map->Sibling){
        return Map->Sibling;
    }   
    return C;
}

LONG 
LouKeMultUtfStrCmp_s(
    UINT8*  Raw1,
    UINT8*  Raw2,
    SIZE    El1,
    SIZE    El2,
    SIZE    Length
){

    

    return 0x00;
}

LONG 
LouKeMultUtfStrCmp(
    UINT8*  Raw1,
    UINT8*  Raw2,
    SIZE    El1,
    SIZE    El2
){



    return 0x00;
}