#ifndef _PRIVATE_LOCALE
#define _PRIVATE_LOCALE

#include "ntdll.h"

#ifndef _NLS_CODEPAGE_FILE_HEADER_FORMAT
#define _NLS_CODEPAGE_FILE_HEADER_FORMAT
typedef struct _NLS_FILE_HEADER{
    WORD    Cp2UniOffset;
    WORD    CodePage;
    WORD    MaxCharecterSize;
    BYTE    DefaultChar[2];
    WORD    UniDefaultChar;
    WORD    TransDefaultChar;
    WORD    TransUniDeafaultChar;
    BYTE    LeadByte[12];    
}NLS_FILE_HEADER, * PNLS_FILE_HEADER;
#endif

typedef enum{
    NLS_SECTION_SHORTKEY = 9,
    NLS_SECTION_CASEMAP = 10,
    NLS_SECTION_CODEPAGE = 11,
    NLS_SECTION_NORMALIZE = 12,
}NLS_SECTION_TYPE;

typedef struct _NLS_NORMALIZATION_TABLE{
    WCHAR       Name[13];
    USHORT      Checksum[3];
    USHORT      Version[4];
    USHORT      Form;
    USHORT      LengthFactor;
    USHORT      Reserved1;
    USHORT      DecompSize;
    USHORT      CompSize;
    USHORT      Reserved2;
    USHORT      Classes;
    USHORT      PropsLevel1;
    USHORT      PropsLevel2;
    USHORT      DecompHash;
    USHORT      DecompMap;
    USHORT      DecomSeq;
    USHORT      CompHash;
    USHORT      CompSeq;
}NLS_NORMALIZATION_TABLE, * PNLS_NORMALIZATION_TABLE;

typedef struct _LOCALE_NLS_HEADER{
    UINT        Ctypes;
    UINT        Reserved1;
    UINT        Reserved2;
    UINT        Reserved3;
    UINT        Locales;
    UINT        Charmaps;
    UINT        Geoids;
    UINT        Scripts;
}LOCALE_NLS_HEADER, * PLOCALE_NLS_HEADER;

static inline WCHAR CaseMapAscii(WCHAR Charecter){
    if((Charecter >= 'a') && (Charecter <= 'z')){
        Charecter -= 'a' - 'A';
    }
    return Charecter;
}

static inline int GetUtf16(
    LPWSTR  Source, 
    UINT    SourceLength,
    UINT*   Charecter
){
    if(IS_HIGH_SURROGATE(Source[0])){
        if(SourceLength <= 1){
            return 0;
        }
        if(!IS_LOW_SURROGATE(Source[1])){
            return 0;
        }
        *Charecter = 0x10000 + ((Source[0] & 0x03FF) << 10) + (Source[1] & 0x03FF);
        return 2;
    }
    if(IS_LOW_SURROGATE(Source[0])){
        return 0;
    }
    *Charecter = Source[0];
    return 1;
}

static inline void PutUtf16(
    LPWSTR      Destination,
    UINT        Charecter
){
    if(Charecter >= 0x10000){
        Charecter -= 0x10000;
        Destination[0] = 0xD800 | (Charecter >> 10);
        Destination[1] = 0xDC00 | (Charecter & 0x03FF);
        return;
    }
    Destination[0] = (WCHAR)Charecter;
}

static inline UINT DecodeUtf16Char(
    unsigned char   Charecter, 
    string*         Str,
    string          StrEnd
){

    static unsigned char Utf8Length[128] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
        0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,  
    };

    static const unsigned char Utf8Mask[4] = {
        0x7F, 0x1F, 0x0F, 0x07
    };

    UINT Length = Utf8Length[Charecter - 0x80];
    UINT Result = Charecter & Utf8Mask[Length];
    string End = *Str + Length;

    if(End > StrEnd){
        *Str = End;
        return (UINT)~0;
    }

    switch(Length){
        case 3:
            if((Charecter = End[-3] ^ 0x80) >= 0x40){
                break;
            }
            Result = (Result << 6) | Charecter;
            (*Str)++;
            if(Result < 0x10){
                break;
            }
        case 2:
            if((Charecter = End[-2] ^ 0x80) >= 0x40){
                break;
            }
            Result = (Result << 6) | Charecter;
            if(Result >= 0x110000 >> 6){
                break;
            }
            (*Str)++;
            if(Result < 0x20){
                break;
            }
            if(Result >= 0xD800 >> 6 && Result <= 0xDFFF >> 6){
                break;
            }
        case 1:
            if((Charecter = End[-1] ^ 0x80) >= 0x40){
                break;
            }
            Result = (Result << 6) | Charecter;
            (*Str)++;
            if(Result < 0x80){
                break;
            }
            return Result;
    }

    return (UINT)~0;
}

static inline void InitializeCodePageTable(
    PUSHORT Pointer

){

}

#endif