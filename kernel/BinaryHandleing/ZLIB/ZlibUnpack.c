#include <LouAPI.h>


LOUSTATUS LouKeZlibUnpackStream(uint8_t* OutputStream, size_t* OutputStreamSize, uint8_t* InputStream, size_t InputLength){
    UNUSED size_t AllocatedOutputSize = *OutputStreamSize;
    UNUSED size_t OutputPosition = 0;
    UNUSED uint8_t BlockType = 0;
    UNUSED bool FinalBlock = false;
    LOUSTATUS Status = STATUS_SUCCESS;
    if((!OutputStream) || (!InputStream) || (!OutputStreamSize) || (InputLength < 6)){
        return STATUS_INVALID_PARAMETER;
    }

    ZLIB_STREAM DataStream = {InputStream, InputLength, 0};
    LouKeZlibSetStreamIndex(&DataStream, 3, 0); //hufman information starts at byte 3

    do {
        FinalBlock = (LouKeZlibReadBits(&DataStream, 1, ZLIB_LE)) ? 1  : 0;
        BlockType = (uint8_t)LouKeZlibReadBits(&DataStream, 2, ZLIB_LE);

        switch (BlockType){
            case 0:
                LouPrint("Data Is Not Packed\n");
                while(1);
                //Status = ZlibHandleDataConstruction(&DataStream, &OutputPosition, OutputStream);
                break;
            case 1:
                LouPrint("Data Uses Fixed Huffman\n");
                while(1);
                //Status = LouKeZlibUnpackFixedHuffman(&DataStream, &OutputPosition, OutputStream);
                break;
            case 2:
                Status = LouKeZlibUnpackDynamicHuffman(&DataStream, &OutputPosition, OutputStream);
                break;
            default:
                LouPrint("STATUS_UNSUCCESSFUL\n");
                while(1);
                return STATUS_UNSUCCESSFUL;   
        }
    
        if(Status != STATUS_SUCCESS){
            return Status;
        }
    
    } while (!FinalBlock);    
    *OutputStreamSize = OutputPosition;
    return STATUS_SUCCESS;
}