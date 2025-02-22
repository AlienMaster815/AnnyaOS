#include <LouAPI.h>

static void LouKeZlibFlipBits(uint32_t* Bits) {
    uint32_t Result = 0;
    for(uint8_t i = 0; i < 32; i++) {
        Result |= ((*Bits >> i) & 0x01) << (31 - i);
    }
    *Bits = Result;
}

uint32_t LouKeZlibReadHuffmanBits(PHUFFMAN_STREAM Stream, int Count, uint8_t DataTypeNibble) {
    
    uint32_t Result = 0;
    uint8_t i = 0;
    if((Count + Stream->BitIndex) >= 31){  
        for(; i < (31 - Stream->BitIndex); i++){
            Stream->BitBuffer & (1 << (31 - (Stream->BitIndex + i))) ? Result |= (1 << i) : 0;//false do nothing
        }
        Stream->BitBuffer = 0;
        Stream->BitIndex = 0;
        for(uint8_t j = 0; j < 4; j++){
            Stream->BitBuffer |= Stream->Input[j + Stream->InputPosition] << (j * 8);
        }
        Stream->InputPosition += 4;
    }

    for(; i < Count; i++, Stream->BitIndex++){
        Stream->BitBuffer & (1 << (31 - Stream->BitIndex)) ? Result |= (1 << i) : 0; //false do nothing
    }

    switch (DataTypeNibble) {
        case ZLIB_LE:
            return Result;
        case ZLIB_LE_BF | ZLIB_U32:
            LouKeZlibFlipBits(&Result);
            return Result;
        case ZLIB_LE_BF | ZLIB_U16:
            LouKeZlibFlipBits(&Result);
            Result >>= 16;
            return Result;
        case ZLIB_LE_BF | ZLIB_U8:
            LouKeZlibFlipBits(&Result);
            Result >>= 24;
            return Result;
        case ZLIB_BE:
            return U32_TO_NETWORK_BYTE_ORDER(Result);
        case ZLIB_BE_BF | ZLIB_U32:
            Result = U32_TO_NETWORK_BYTE_ORDER(Result);
            LouKeZlibFlipBits(&Result);
            return Result;
        case ZLIB_BE_BF | ZLIB_U16:
            Result = U32_TO_NETWORK_BYTE_ORDER(Result);
            LouKeZlibFlipBits(&Result);
            Result >>= 16;
            return Result;
        case ZLIB_BE_BF | ZLIB_U8:
            Result = U32_TO_NETWORK_BYTE_ORDER(Result);
            LouKeZlibFlipBits(&Result);
            Result >>= 24;
            return Result;
        default:
            return Result;
    }
}



void LouKeZlibSetHuffmanStreamIndex(PHUFFMAN_STREAM Stream, size_t StartOffset, uint8_t BitIndex) {
    Stream->BitBuffer = 0;
    Stream->BitIndex = BitIndex;
    Stream->InputPosition = StartOffset + 4;
    for(uint8_t i = 0; i < 4; i++){
        Stream->BitBuffer |= Stream->Input[i + StartOffset] << (i * 8);
    }
}

