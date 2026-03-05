#ifndef _BINARYS_H
#define _BINARYS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>
#include <kernel/loustatus.h>
#include <string.h>  

typedef char* FUNCTION_NAME;

static inline
uint16_t ConvertBeToLeU16(uint16_t Foo){
    uint16_t Tmp1, Tmp2;
    Tmp1 = Foo & 0xFF;
    Tmp2 = Foo >> 8;
    return (Tmp1 << 8) | Tmp2;
}

static inline
uint32_t ConvertBeToLeU32(uint32_t Foo) {
    uint32_t Tmp1, Tmp2, Tmp3, Tmp4;
    Tmp1 = Foo & 0xFF;
    Tmp2 = (Foo >> 8) & 0xFF;
    Tmp3 = (Foo >> 16) & 0xFF;
    Tmp4 = (Foo >> 24) & 0xFF;    
    return (Tmp1 << 24) | (Tmp2 << 16) | (Tmp3 << 8) | Tmp4;
}

static inline
uint64_t ConvertBeToLeU64(uint64_t Foo) {
    uint64_t Tmp1, Tmp2, Tmp3, Tmp4, Tmp5, Tmp6, Tmp7, Tmp8;
    Tmp1 = Foo & 0xFF;
    Tmp2 = (Foo >> 8) & 0xFF;
    Tmp3 = (Foo >> 16) & 0xFF;
    Tmp4 = (Foo >> 24) & 0xFF;
    Tmp5 = (Foo >> 32) & 0xFF;
    Tmp6 = (Foo >> 40) & 0xFF;
    Tmp7 = (Foo >> 48) & 0xFF;
    Tmp8 = (Foo >> 56) & 0xFF;
    return (Tmp1 << 56) | (Tmp2 << 48) | (Tmp3 << 40) | (Tmp4 << 32) | (Tmp5 << 24) | (Tmp6 << 16) | (Tmp7 << 8)  | Tmp8;
}

#define U16_TO_NETWORK_BYTE_ORDER(x) ConvertBeToLeU16((x))
#define U32_TO_NETWORK_BYTE_ORDER(x) ConvertBeToLeU32((x))
#define U64_TO_NETWORK_BYTE_ORDER(x) ConvertBeToLeU64((x))


#ifndef _USER_MODE_CODE_
uint64_t* ProbeBinary64Bit(uint64_t Address, uint64_t Buffer);
uint32_t* ProbeBinary32Bit(uint64_t Address, uint64_t Buffer);
uint16_t* ProbeBinary16Bit(uint64_t Address, uint64_t Buffer);
uint8_t* ProbeBinary8Bit(uint64_t Address, uint64_t Buffer);

int64_t* ProbeBinary64BitSigned(uint64_t Address, uint64_t Buffer);
int32_t* ProbeBinary32BitSinged(uint64_t Address, uint64_t Buffer);
int16_t* ProbeBinary16BitSigned(uint64_t Address, uint64_t Buffer);
int8_t* ProbeBinary8BitSigned(uint64_t Address, uint64_t Buffer);
uint64_t GetSysBinaryChunk(uint64_t Address, uint32_t ChunkSize);
void ReleaseSysBinaryChunk(uint64_t Address, uint32_t ChunkSize);
wchar_t* LookForUTF16LEBuffer(wchar_t* BufferOfSearch, wchar_t* UTF16LEString, size_t BufferSize,size_t StringSize);

LOUSTATUS ISO646StandardAlphaNumericToAsciiAlphaNumeric(string Destiantion, uint8_t* Source, size_t BytesToConvert);

#endif

#ifdef __cplusplus
}
#endif
#endif
