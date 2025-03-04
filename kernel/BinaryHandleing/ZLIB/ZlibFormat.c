#include <LouAPI.h>

uint32_t LouKeGetZlibUnCompressedSize(uint8_t* ZlibData, size_t ZlibSize) {
    if (!ZlibData || ZlibSize < 6) {
        return 0;
    }

    uint8_t CMF = ZlibData[0];
    uint8_t FLG = ZlibData[1];

    // Fix overflow issue
    if (((CMF << 8) | FLG) % 31 != 0) { 
        return 0;
    }

    size_t Pos = 2; 
    uint32_t TotalUncompressedSize = 0;

    while (Pos < ZlibSize) {
        if (Pos + 1 >= ZlibSize) return 0;
        uint8_t BlockHeader = ZlibData[Pos++];
        uint8_t BFINAL = BlockHeader & 1;
        uint8_t BTYPE = (BlockHeader >> 1) & 3;

        if (BTYPE == 0) {
            if (Pos + 4 > ZlibSize) {
                return 0;
            }
            
            uint16_t BlockLength = ZlibData[Pos] | (ZlibData[Pos + 1] << 8);
            uint16_t BlockLengthInv = ZlibData[Pos + 2] | (ZlibData[Pos + 3] << 8);

            if ((BlockLength ^ BlockLengthInv) != 0xFFFF) {
                return 0;
            }

            Pos += 4;
            TotalUncompressedSize += BlockLength;
            Pos += BlockLength;
        }
        else if (BTYPE == 1 || BTYPE == 2) { 
            return 0xFFFFFFFF;
        }
        else {
            return 0;
        }

        if (BFINAL) return TotalUncompressedSize;
    }

    return TotalUncompressedSize;
}

static void LouKeZlibFlipBits(uint32_t* Bits) {
    uint32_t Result = 0;
    for(uint8_t i = 0; i < 32; i++) {
        Result |= ((*Bits >> i) & 0x01) << (31 - i);
    }
    *Bits = Result;
}

uint32_t LouKeZlibReadBits(PZLIB_STREAM Stream, int Count, uint8_t DataTypeNibble) {
    
    uint32_t Result = 0;
    uint8_t i = 0;
    if((Count + Stream->BitIndex) >= 31){  
        for(; i < (31 - Stream->BitIndex); i++){
            Stream->BitBuffer & (1 << (Stream->BitIndex + i)) ? Result |= (1 << i) : 0;//false do nothing
        }
        Stream->BitBuffer = 0;
        Stream->BitIndex = 0;
        for(uint8_t j = 0; j < 4; j++){
            Stream->BitBuffer |= (Stream->Input[j + Stream->InputPosition] << (j * 8));
        }
        Stream->InputPosition += 4;
    }

    for(; i < Count; i++, Stream->BitIndex++){
        Stream->BitBuffer & (1 << Stream->BitIndex) ? Result |= (1 << i) : 0; //false do nothing
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



void LouKeZlibSetStreamIndex(PZLIB_STREAM Stream, size_t StartOffset, uint8_t BitIndex) {
    if(StartOffset > 0){
        StartOffset -= 1;
    }
    Stream->BitBuffer = 0;
    Stream->BitIndex = BitIndex;
    Stream->InputPosition = StartOffset + 4;
    for(uint8_t i = 0; i < 4; i++){
        Stream->BitBuffer |= (Stream->Input[i + StartOffset] << (i * 8));
    }
}

