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

LOUSTATUS Utf32CharToUtf8Char(
    UINT32 LongChar,
    UINT8* Utf8Char,
    UINT8* OutByteCount
){
    if((!Utf8Char) || (!OutByteCount)){
        return STATUS_INVALID_PARAMETER;
    }
    if(((LongChar >= 0xD800) && (LongChar <= 0xDFFF)) || (LongChar > 0x10FFFF)){
        return STATUS_INVALID_PARAMETER;
    }
    if(LongChar <= 0x7F){
        Utf8Char[0] = (UINT8)LongChar;
        *OutByteCount = 1;
    }
    else if(LongChar <= 0x7FF){
        Utf8Char[0] = (UINT8)(0xC0 | (LongChar >> 6));
        Utf8Char[1] = (UINT8)(0x80 | (LongChar & 0x3F));
        *OutByteCount = 2;
    }else if(LongChar <= 0xFFFF){
        Utf8Char[0] = (UINT8)(0xE0 | (LongChar >> 12));
        Utf8Char[1] = (UINT8)(0x80 | ((LongChar >> 6) & 0x3F));
        Utf8Char[2] = (UINT8)(0x80 | (LongChar & 0x3F));
        *OutByteCount = 3;
    }else{
        Utf8Char[0] = (UINT8)(0xF0 | (LongChar >> 18));
        Utf8Char[1] = (UINT8)(0x80 | ((LongChar >> 12) & 0x3F));
        Utf8Char[2] = (UINT8)(0x80 | ((LongChar >> 6) & 0x3F));
        Utf8Char[3] = (UINT8)(0x80 | (LongChar & 0x3F));
        *OutByteCount = 4;
    }
    return STATUS_SUCCESS;
}
