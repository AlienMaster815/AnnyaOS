#ifndef _BINARYS_H
#define _BINARYS_H
#ifndef __cplusplus
#include <LouAPI.h>

typedef char* FUNCTION_NAME;
#ifndef _KERNEL_MODULE_
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


#endif
#else
#include <LouDDK.h>
typedef char* FUNCTION_NAME;
#ifndef _KERNEL_MODULE_
extern "C" uint64_t GetSysBinaryChunk(uint64_t Address, uint32_t ChunkSize);
extern "C" void ReleaseSysBinaryChunk(uint64_t Address, uint32_t ChunkSize);
KERNEL_IMPORT wchar_t* LookForUTF16LEBuffer(wchar_t* BufferOfSearch, wchar_t* UTF16LEString, size_t BufferSize, size_t StringSize);



#endif
#endif


#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif

//Network Byte Order

#define U16_TO_NETWORK_BYTE_ORDER(x) ConvertBeToLeU16((x))
#define U32_TO_NETWORK_BYTE_ORDER(x) ConvertBeToLeU32((x))
#define U64_TO_NETWORK_BYTE_ORDER(x) ConvertBeToLeU64((x))

//ISO646 Standard
LOUSTATUS ISO646StandardAlphaNumericToAsciiAlphaNumeric(string Destiantion, uint8_t* Source, size_t BytesToConvert);

//ZLIB

#define LOU_ZLIB_CMF_GET_COMPRESION_METHOD(x)     (x) & (0xF)
#define LOU_ZLIB_CMF_GET_COMPRESION_INFO  (x)    ((x) >> 4) & (0x0F)
#define LOU_ZLIB_COMPRESION_METHOD_DEFLATE         8 //uo to 32K
#define LOU_ZLIB_COMPRESION_METHOD_RESERVED       15
#define LOU_ZLIB_COMPRESION_32K_WINDOW             7
#define LOU_ZLIB_FLAG_GET_FCHECK(x)              (X & 0xF)
#define LOU_ZLIB_FLAG_GET_FDICT(x)               (x >> 4) & 0x0F
#define LOU_ZLIB_IS_DICTIONARY_PRESENT           (1 << 5)
#define LOU_ZLIB_FLAG_GET_FLEVEL(x)              (x >> 6) & 0x02
#define LOU_ZLIB_FASTEST_LEVEL_COMPRESION       0
#define LOU_ZLIB_FAST_LEVEL_COMPRESION          1
#define LOU_ZLIB_DEFAULT_LEVEL_COMPRESION       2
#define LOU_ZLIB_MAXIMUM_COMPRESION             3

#define ADLER32_MOD 65521 

static inline uint32_t ComputeAdler32(const uint8_t *data, size_t length) {
    uint32_t A = 1, B = 0;
    for (size_t i = 0; i < length; i++) {
        A = (A + data[i]) % ADLER32_MOD;
        B = (B + A) % ADLER32_MOD;
    }
    return (B << 16) | A;
}

static inline bool ValidateAdler32(const uint8_t *data, size_t length, uint32_t expectedChecksum) {
    return (ComputeAdler32(data, length) == expectedChecksum) ? 1 : 0;
}

uint32_t LouKeGetZlibUnCompressedSize(uint8_t* ZlibData, size_t ZlibSize);

typedef struct _ZLIB_STREAM{
    uint8_t*    Input;
    size_t      InputLength;
    size_t      InputPosition;
    uint32_t    BitBuffer;
    int         BitIndex;
}ZLIB_STREAM, HUFFMAN_STREAM, * PZLIB_STREAM, * PHUFFMAN_STREAM;

uint32_t LouKeZlibReadBits(PZLIB_STREAM Stream, int Count, uint8_t DataTypeNibble);

LOUSTATUS LouKeZlibUnpackDynamicHuffman(
    PZLIB_STREAM Stream, 
    size_t* OutputPosition, 
    uint8_t* OutputStream
);

LOUSTATUS LouKeZlibUnpackFixedHuffman(
    PZLIB_STREAM Stream, 
    size_t* OutputPosition, 
    uint8_t* OutputStream
);

typedef struct _HUFFMAN_ENTRY{
    uint16_t Symbol;
    uint16_t Code;
    uint8_t  Length;
}HUFFMAN_ENTRY, * PHUFFMAN_ENTRY;

typedef struct _HUFFMAN_TREE{
    HUFFMAN_ENTRY   Entries[288];
    uint16_t        CodeCount;
}HUFFMAN_TREE, * PHUFFMAN_TREE;

LOUSTATUS LouKeZlibUnpackStream(uint8_t* OutputStream, size_t* OutputStreamSize, uint8_t* InputStream, size_t InputLength);

void LouKeZlibSetStreamIndex(PZLIB_STREAM Stream, size_t StartOffset, uint8_t BitIndex);

#define ZLIB_LE     0
#define ZLIB_LE_BF  1
#define ZLIB_BE     2
#define ZLIB_BE_BF  3

#define ZLIB_U8  0 << 2
#define ZLIB_U16 1 << 2
#define ZLIB_U32 2 << 2


uint32_t LouKeZlibReadHuffmanBits(PHUFFMAN_STREAM Stream, int Count, uint8_t DataTypeNibble);
void LouKeZlibSetHuffmanStreamIndex(PHUFFMAN_STREAM Stream, size_t StartOffset, uint8_t BitIndex);

static inline void LouKeZlibSyncStreamWithHuffmanData(
    PZLIB_STREAM ZlibStream, 
    PHUFFMAN_STREAM HuffmanStream
){
    memcpy(HuffmanStream, ZlibStream, sizeof(HUFFMAN_STREAM));
}



#ifdef __cplusplus
}
#endif
#endif