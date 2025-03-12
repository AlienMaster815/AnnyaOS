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



#ifdef __cplusplus
}
#endif
#endif