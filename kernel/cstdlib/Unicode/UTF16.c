#include <LouAPI.h>
#include "Unicode.h"

SIZE Utf16EncodedLength(
    UINT16* Charecter
){
    if(Charecter[0] >= 0xD800 && Charecter[0] <= 0xDBFF){
        return 2;
    }
    return 1;
}

UINT32 Utf16ToUint32(
    UINT16* Charecter
){
    if(Charecter[0] >= 0xD800 && Charecter[0] <= 0xDBFF){
        return ((((UINT32)Charecter[0]) - 0xD800) << 10) + ((UINT32)Charecter[1] - 0xDC00) + 0x10000; 
    }
    return (UINT32)Charecter[0];
}