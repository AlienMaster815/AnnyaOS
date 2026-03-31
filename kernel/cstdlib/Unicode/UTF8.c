#include <LouAPI.h>

//TODO Utf8StrCmp and Utf8StrCmpSafe

LOUSTATUS 
Utf8CharLength(
    CHAR    Char, 
    SIZE*   Count
){
    if(!Count){
        return STATUS_INVALID_PARAMETER;
    }
    if(!(Char & (1 << 7))){
        *Count = 1;
    }else if((Char & 0xE0) == 0xC0){
        *Count = 2;
    }else if((Char & 0xF0) == 0xE0){
        *Count = 3;
    }else if((Char & 0xF8) == 0xF0){
        *Count = 4;
    }else{
        return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS
Utf8CharToUtf32Char(
    string      CharIndex, 
    UINT32*     Out
){
    if(!Out){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status;
    SIZE CharLength = 0;
    UINT32 Result = 0;
    Status = Utf8CharLength(CharIndex[0], &CharLength);

    if(Status != STATUS_SUCCESS){
        return Status;
    }

    switch(CharLength){
        case 1:
            Result = (UINT32)CharIndex[0];
            break;
        case 2:
            Result =  ((UINT32)CharIndex[0] & 0x1F) << 6;
            Result |= ((UINT32)CharIndex[1] & 0x3F);
            break;
        case 3:
            Result =  ((UINT32)CharIndex[0] & 0x0F) << 12;
            Result |= ((UINT32)CharIndex[1] & 0x3F) << 6;
            Result |= ((UINT32)CharIndex[2] & 0x3F);
            break;
        case 4:
            Result =  ((UINT32)CharIndex[0] & 0x07) << 18;
            Result |= ((UINT32)CharIndex[1] & 0x3F) << 12;
            Result |= ((UINT32)CharIndex[2] & 0x3F) << 6;
            Result |= ((UINT32)CharIndex[3] & 0x3F);
            break;
        default:
            return STATUS_INVALID_PARAMETER;
    }
    *Out = Result;
    return STATUS_SUCCESS;
}

LOUSTATUS 
Utf8StrLen(
    string  RawString, 
    SIZE*   Length
){
    if((!RawString) || (!Length)){
        return STATUS_INVALID_PARAMETER;
    }

    SIZE TmpLength = 0;
    SIZE Utf8Index = 0;
    SIZE Inc = 0;
    UINT32 TmpChar;
    LOUSTATUS Status;

    while(1){
        Status = Utf8CharToUtf32Char(&RawString[Utf8Index], &TmpChar);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        if(!TmpChar){
            break;
        }
        Status = Utf8CharLength(RawString[Utf8Index], &Inc);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Utf8Index += Inc;
        TmpLength++;
    }

    *Length = TmpLength;

    return STATUS_SUCCESS;
}

LOUSTATUS 
Utf8StrToUtf32Str(
    UINT32* Destination, 
    string  RawString
){
    if((!Destination) || (!RawString)){
        return STATUS_INVALID_PARAMETER;
    }
    SIZE Utf32Index = 0;
    SIZE Utf8Index = 0;
    SIZE Inc = 0;
    UINT32 TmpChar;
    LOUSTATUS Status;
    while(1){
        Status = Utf8CharToUtf32Char(&RawString[Utf8Index], &TmpChar);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Destination[Utf32Index] = TmpChar;
        if(!TmpChar){
            break;
        }
        Status = Utf8CharLength(RawString[Utf8Index], &Inc);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Utf8Index += Inc;
        Utf32Index++;
    }    
    return STATUS_SUCCESS;
}

LOUSTATUS 
Utf8StrToUtf32StrSafe(
    UINT32* Destination, 
    string  RawString,
    SIZE    Length
){
    if((!Destination) || (!RawString)){
        return STATUS_INVALID_PARAMETER;
    }
    SIZE Utf32Index = 0;
    SIZE Utf8Index = 0;
    SIZE Inc = 0;
    UINT32 TmpChar;
    LOUSTATUS Status;
    while(Utf32Index < Length){
        Status = Utf8CharToUtf32Char(&RawString[Utf8Index], &TmpChar);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Destination[Utf32Index] = TmpChar;
        if(!TmpChar){
            break;
        }
        Status = Utf8CharLength(RawString[Utf8Index], &Inc);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Utf8Index += Inc;
        Utf32Index++;
    }    
    if(Utf32Index < Length){
        Destination[Utf32Index] = 0;
    }
    else if(Utf32Index > 0){
        Destination[Utf32Index - 1] = 0;
        if(TmpChar){
            return STATUS_INSUFFICIENT_RESOURCES;
        }
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
Utf8StrToUtf16Str(
    UINT16* Destination, 
    string  RawString
){
    if((!Destination) || (!RawString)){
        return STATUS_INVALID_PARAMETER;
    }
    SIZE Utf16Index = 0;
    SIZE Utf8Index = 0;
    SIZE Inc = 0;
    UINT32 TmpChar;
    LOUSTATUS Status;
    BOOLEAN Surgate;
    while(1){
        Status = Utf8CharToUtf32Char(&RawString[Utf8Index], &TmpChar);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Status = Utf32CharToUtf16Char(TmpChar, &Destination[Utf16Index], &Surgate);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        if(!TmpChar){
            break;
        }
        Status = Utf8CharLength(RawString[Utf8Index], &Inc);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Utf8Index += Inc;
        Surgate ? Utf16Index += 2 : Utf16Index++;
    }    
    return STATUS_SUCCESS;
}

LOUSTATUS 
Utf8StrToUtf16StrSafe(
    UINT16* Destination, 
    string  RawString,
    SIZE    Length
){
    if((!Destination) || (!RawString)){
        return STATUS_INVALID_PARAMETER;
    }
    SIZE Utf16Index = 0;
    SIZE Utf8Index = 0;
    SIZE Inc = 0;
    UINT32 TmpChar;
    LOUSTATUS Status;
    BOOLEAN Surgate;
    UINT16 Tmp[2] = {0};
    while(1){
        Status = Utf8CharToUtf32Char(&RawString[Utf8Index], &TmpChar);
        if(Status != STATUS_SUCCESS){
            return Status;
        }

        Status = Utf32CharToUtf16Char(TmpChar, Tmp, &Surgate);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        if((Utf16Index + (Surgate ? 2 : 1)) < Length){
            memcpy(&Destination[Utf16Index], Tmp, (Surgate ? 2 : 1) * sizeof(UINT16));
        }else if((Utf16Index + 1) < Length){
            memset(&Destination[Utf16Index + 1], 0, sizeof(UINT16));
            return STATUS_INSUFFICIENT_RESOURCES;
        }else{
            memset(&Destination[Utf16Index], 0, sizeof(UINT16));
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        if(!TmpChar){
            return STATUS_SUCCESS;  
        }
        Status = Utf8CharLength(RawString[Utf8Index], &Inc);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Utf8Index += Inc;
        Surgate ? Utf16Index += 2 : Utf16Index++;
    }    
}