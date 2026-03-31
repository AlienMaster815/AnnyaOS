#include <LouAPI.h>

LOUSTATUS 
Utf32CharToUtf16Char(
    UINT32      LongChar,
    UINT16*     ShortChar,
    BOOLEAN*    OutSurgate
){
    if((!ShortChar) || (!OutSurgate)){
        return STATUS_INVALID_PARAMETER;
    }

    if(((LongChar >= 0xD800) && (LongChar <= 0xDFFF)) || (LongChar > 0x10FFFF)){
        return STATUS_INVALID_PARAMETER;
    }
    
    if(LongChar > 0xFFFF){
        LongChar -= 0x10000;
        ShortChar[0] = (UINT16)((LongChar >> 10) + 0xD800);
        ShortChar[1] = (UINT16)((LongChar & 0x3FF) + 0xDC00);
        *OutSurgate = true;
    }else{
        //UINT16 compatible
        ShortChar[0] = (UINT16)LongChar;
        *OutSurgate = false;
    }
    return STATUS_SUCCESS;
}