#include <LouAPI.h>

static const uint16_t FixedHuffmanLengths[288] = {
    /* 0-143: 8-bit codes (0b00110000 - 0b10111111) */
    [0 ... 143] = 8,
    /* 144-255: 9-bit codes (0b110010000 - 0b111111111) */
    [144 ... 255] = 9,
    /* 256-279: 7-bit codes (0b0000000 - 0b0010111) */
    [256 ... 279] = 7,
    /* 280-287: 8-bit codes (0b11000000 - 0b11000111) */
    [280 ... 287] = 8
};

static const uint16_t FixedHuffmanCodes[288] = {
    /* Codes 0-143 (8-bit) */
    [0 ... 143] = 0b00110000, 
    /* Codes 144-255 (9-bit) */
    [144 ... 255] = 0b110010000, 
    /* Codes 256-279 (7-bit) */
    [256 ... 279] = 0b0000000,  
    /* Codes 280-287 (8-bit) */
    [280 ... 287] = 0b11000000 
};

static const uint16_t LengthTableS[29] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 
                35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258};

static uint16_t LengthTable[29];

static const uint8_t ExtraBitsS[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 
             3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};

static uint8_t ExtraBits[29];

static const uint16_t DistanceTableS[31] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 
                257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};

static uint16_t DistanceTable[31];

static const uint8_t DistExtraBitsS[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 
               7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};

static uint8_t DistExtraBits[30];

static const uint8_t CodeLengthsOrderS[19] = { 
    16, 17, 18,  0,  8,  7,  9,  6, 10,  5, 11,  4, 12,  3, 13,  2, 14,  1, 15 
};

static uint8_t CodeLengthsOrder[19];

static uint8_t CodeLengths[19];

static HUFFMAN_TREE TreeData[3];

static mutex_t FixedHuffmanMutext;

static uint8_t LitLenCodeLengths[288];
static uint8_t DistCodeLengths[32];


LOUSTATUS LouKeZlibUnpackFixedHuffman(
    PZLIB_STREAM Stream, 
    size_t* OutputPosition, 
    uint8_t* OutputStream
){
    //I Know this looks rough but im 
    //trying to save my stack
    MutexLock(&FixedHuffmanMutext);
    memcpy(LengthTable, LengthTableS, 29);
    memcpy(ExtraBits, ExtraBitsS, 29);
    memcpy(DistanceTable, DistanceTableS, 31);
    memcpy(DistExtraBits, DistExtraBitsS, 30);
    uint64_t HuffmanBits = 0;
    int Symbol = 0;
    size_t i = 0;
    int LengthIndex = 0;
    int Length = 0;
    int DistanceCode = 0;
    int Distance = 0;
    while(1){
        HuffmanBits = 0;//LouKeZlibReadBits(Stream, 9);
        Symbol = -1;

        for(i = 0 ; i < 288; i++){
            if(HuffmanBits == (FixedHuffmanCodes[i] & ((1 << FixedHuffmanLengths[i]) - 1))){
                Symbol = i;
                break;
            }
        }

        if(Symbol == -1){
            return STATUS_UNSUCCESSFUL;
        }

        if(Symbol == 256){
            break; //ENDOF Block
        }else if(Symbol < 256){//literal byte
            OutputStream[*OutputPosition] = (uint8_t)Symbol;
            (*OutputPosition)++;
        }else{

            LengthIndex = Symbol - 257;
            Length = LengthTable[LengthIndex];
            if(ExtraBits[LengthIndex] > 0){
                Length += 0;//LouKeZlibReadBits(Stream, ExtraBits[LengthIndex]);
            }

            DistanceCode = 0;//LouKeZlibReadBits(Stream, 5);
            if(DistanceCode > 29){
                goto _ZLIB_HUFFMAN_FIXED_UNPACK_FAILED;
            }

            Distance = DistanceTable[DistanceCode];
            if(DistExtraBits[DistanceCode] > 0){
                Distance += 0;//LouKeZlibReadBits(Stream, DistExtraBits[DistanceCode]);
            }

            for(i = 0; i < Length; i++){
                OutputStream[*OutputPosition] = OutputStream[*OutputPosition - Distance];
                (*OutputPosition)++;
            }

        }

    }

    MutexUnlock(&FixedHuffmanMutext);
    return STATUS_SUCCESS;

    _ZLIB_HUFFMAN_FIXED_UNPACK_FAILED:
    MutexUnlock(&FixedHuffmanMutext);
    return STATUS_UNSUCCESSFUL;
}

#define CODE_LENGTH_TREE    0
#define LITLEN_TREE         1
#define DIST_TREE           2

static uint16_t HuffmanDecode(PZLIB_STREAM Stream, PHUFFMAN_TREE Tree){
    uint16_t Code = 0;

    for(uint16_t BitsRead = 0; BitsRead < 15; BitsRead++){
        uint16_t Bits = LouKeZlibReadBits(Stream, 1, ZLIB_LE);
        Code = (Code << 1) | Bits;
        
        //LouPrint("BitsRead:%d, Bit:%h, Code:%h\n", BitsRead + 1, Bits, Code);

        for(uint16_t Index = 0; Index < Tree->CodeCount; Index++){
            if ((Tree->Entries[Index].Code == Code) && (Tree->Entries[Index].Length == (BitsRead + 1))) {
                //LouPrint("Matched Symbol: %h\n", Tree->Entries[Index].Symbol);
                return Tree->Entries[Index].Symbol;
            }
        }   
    }
    return 0xFFFF; // Invalid symbol
}


static LOUSTATUS BuildHuffmanTree(PHUFFMAN_TREE Tree, const uint8_t* CodeLengths, uint16_t NumSymbols) {
    if (!Tree || !CodeLengths) {
        return STATUS_INVALID_PARAMETER;
    }

    uint16_t Count[15 + 1] = {0};
    uint16_t NextCode[15 + 1] = {0};

    for (uint16_t i = 0; i < NumSymbols; i++) {
        if (CodeLengths[i] > 0) {
            Count[CodeLengths[i]]++;
        }
    }

    uint16_t Code = 0;
    for (uint16_t Bits = 1; Bits <= 15; Bits++) {
        Code = (Code + Count[Bits - 1]) << 1;
        NextCode[Bits] = Code;
    }

    Tree->CodeCount = 0;
    for (uint16_t i = 0; i < NumSymbols; i++) {
        uint8_t Length = CodeLengths[i];
        if (Length > 0) {
            Tree->Entries[Tree->CodeCount].Symbol = i;
            Tree->Entries[Tree->CodeCount].Code = NextCode[Length];
            Tree->Entries[Tree->CodeCount].Length = Length;
            LouPrint("Symbol:%d :: Code:%h :: Length:%d\n", i, NextCode[Length], Length);
            NextCode[Length]++;
            Tree->CodeCount++;
        }
    }

    return STATUS_SUCCESS;
}


LOUSTATUS LouKeZlibUnpackDynamicHuffman(
    PZLIB_STREAM Stream, 
    size_t* OutputPosition, 
    uint8_t* OutputStream
){
    MutexLock(&FixedHuffmanMutext);
    memcpy(CodeLengthsOrder, CodeLengthsOrderS, 19);
    memset(CodeLengths, 0, 19);
    memset(CodeLengths, 0, 19);
    memset(LitLenCodeLengths, 0 , 288);
    memset(DistCodeLengths, 0 , 32);
    memcpy(LengthTable, LengthTableS, 29);
    memcpy(ExtraBits, ExtraBitsS, 29);
    memcpy(DistanceTable, DistanceTableS, 31);
    memcpy(DistExtraBits, DistExtraBitsS, 30);


    uint16_t i = 0;
    uint8_t RepeatCount = 0;
    uint8_t LastValue = 0;
    uint16_t Length = 0;
    uint16_t LengthIndex = 0;
    uint8_t j = 0;
    uint16_t DistanceCode = 0;
    uint16_t Distance = 0;

    for(i = 0; i < 3; i++){
        memset(&TreeData[i], 0, sizeof(HUFFMAN_TREE));
    }

    LouKeZlibSetStreamIndex(Stream, 4, 0);
    uint16_t HLIT  = (uint16_t)(LouKeZlibReadBits(Stream, 5, ZLIB_LE) + 257);
    uint16_t HDIST = (uint16_t)(LouKeZlibReadBits(Stream, 5, ZLIB_LE) + 1);
    uint16_t HCLEN = (uint16_t)(LouKeZlibReadBits(Stream, 4, ZLIB_LE) + 4);
    uint16_t Symbol = 0;
    
    LouPrint("HLIT :%d\n",   HLIT);
    LouPrint("HDIST:%d\n",  HDIST);
    LouPrint("HCLEN:%d\n",  HCLEN);
    LouPrint("Here\n");
    while(1);

    for(i = 0; i < HCLEN; i++){
        CodeLengths[CodeLengthsOrder[i]] = LouKeZlibReadBits(Stream, 3, ZLIB_LE);
    }

    if(BuildHuffmanTree(&TreeData[CODE_LENGTH_TREE], CodeLengths, 19) != STATUS_SUCCESS){
        goto _ZLIB_HUFFMAN_DYNAMIC_UNPACK_FAILED;
    }

    i = 0;

    while(i < (HLIT + HDIST)){
        Symbol = HuffmanDecode(Stream, &TreeData[CODE_LENGTH_TREE]);
    
        //LouPrint("Symbol i:%d :: %h\n",i, Symbol);

        if(Symbol <= 15){
            if(i < HLIT){
                LitLenCodeLengths[i++] = Symbol;
            } else {
                DistCodeLengths[i++ - HLIT] = Symbol;
            }
        } else if(Symbol == 16) {
            RepeatCount = LouKeZlibReadBits(Stream, 2, ZLIB_LE) + 3;
            LastValue = (i == 0) ? 0 : LitLenCodeLengths[i - 1];
            for(j = 0; j < RepeatCount && i < (HLIT + HDIST); j++){
                if(i < HLIT){
                    LitLenCodeLengths[i++] = LastValue;
                } else {
                    DistCodeLengths[i++ - HLIT] = LastValue;
                }
            }
        } else if(Symbol == 17) {
            RepeatCount = LouKeZlibReadBits(Stream, 3, ZLIB_LE) + 3;
            for(j = 0; j < RepeatCount && i < (HLIT + HDIST); j++){
                if(i < HLIT){
                    LitLenCodeLengths[i++] = 0;
                } else {
                    DistCodeLengths[i++ - HLIT] = 0;
                }
            }
        } else if(Symbol == 18) {
            RepeatCount = LouKeZlibReadBits(Stream, 7, ZLIB_LE) + 11;
            for(j = 0; j < RepeatCount && i < (HLIT + HDIST); j++){
                if(i < HLIT){
                    LitLenCodeLengths[i++] = 0;
                } else {
                    DistCodeLengths[i++ - HLIT] = 0;
                }
            }           
        }
    }

    BuildHuffmanTree(&TreeData[LITLEN_TREE],LitLenCodeLengths, HLIT);

    if(
        (BuildHuffmanTree(&TreeData[LITLEN_TREE],LitLenCodeLengths, HLIT) != STATUS_SUCCESS) ||
        (BuildHuffmanTree(&TreeData[DIST_TREE], DistCodeLengths, HDIST) != STATUS_SUCCESS)
    ){
        goto _ZLIB_HUFFMAN_DYNAMIC_UNPACK_FAILED;
    }
 
    while(1) {
        uint16_t Symbol = HuffmanDecode(Stream, &TreeData[LITLEN_TREE]);
        if(Symbol == 256){
            break;
        } else if(Symbol < 256){
            OutputStream[*OutputPosition] = (uint8_t)Symbol;
            (*OutputPosition)++;
        } else {
            LengthIndex = Symbol - 257;
            Length = LengthTable[LengthIndex];
            if(ExtraBits[LengthIndex] > 0){
                Length += LouKeZlibReadBits(Stream, ExtraBits[LengthIndex], ZLIB_LE);
            }

            DistanceCode = HuffmanDecode(Stream, &TreeData[DIST_TREE]);

            if(DistanceCode > 29){
                goto _ZLIB_HUFFMAN_DYNAMIC_UNPACK_FAILED;
            }

            Distance = DistanceTable[DistanceCode];
            if(DistanceTable[DistanceCode] > 0 ){
                Distance += LouKeZlibReadBits(Stream, DistExtraBits[DistanceCode], ZLIB_LE);
            }

            for(j = 0 ; j < Length; j++){
                OutputStream[*OutputPosition] = OutputStream[*OutputPosition - Distance];
                (*OutputPosition)++;
            }
        } 
    }

    LouPrint("Status Success\n");
    MutexUnlock(&FixedHuffmanMutext);
    return STATUS_SUCCESS;

    
    _ZLIB_HUFFMAN_DYNAMIC_UNPACK_FAILED:
    LouPrint("Status UnSuccessFull\n");
    MutexUnlock(&FixedHuffmanMutext);
    return STATUS_UNSUCCESSFUL;
}