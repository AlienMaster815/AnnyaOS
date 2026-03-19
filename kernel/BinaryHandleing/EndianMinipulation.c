#include <LouAPI.h>

//static inline
//wchar_t LittleEndianTransfer(wchar_t LittleEndianWord){
//    wchar_t Result = (wchar_t)((LittleEndianWord & (wchar_t)0xFF) << (wchar_t)8);
//    Result |= (wchar_t)((LittleEndianWord >> 8) & (wchar_t)0xFF); 
//    return Result;
//}


KERNEL_EXPORT
LOUSTATUS 
LouKeSwapEndianess(
    void* InStreamTmp, 
    void* OutStreamTmp, 
    size_t StreamSize
){
    uint8_t* InStream = (uint8_t*)InStreamTmp; 
    uint8_t* OutStream = (uint8_t*)OutStreamTmp;

    if(RangeInterferes(
        (UINT64)InStreamTmp,
        (UINT64)OutStreamTmp,
        StreamSize,
        StreamSize
    )){
        return STATUS_INVALID_PARAMETER;
    }

    for(size_t i = 0 ; i < StreamSize; i++){
        OutStream[(StreamSize - 1) - i] = InStream[i]; 
    }
    return STATUS_SUCCESS;
}



wchar_t* LookForUTF16LEBuffer(wchar_t* BufferOfSearch ,wchar_t* UTF16LEString, size_t BufferSize, size_t StringSize){

    if ((!BufferOfSearch) || (!UTF16LEString) || (BufferSize > StringSize)) {
        return 0x00; // Invalid input or string size larger than buffer
    }

    bool FoundBuffer = true;

    for(size_t i = 0; i < StringSize; i++){

        for(size_t j = 0 ; j < BufferSize; j++){
            wchar_t UTF16String = UTF16LEString[i + j];
            wchar_t Buffer = BufferOfSearch[j];

            if(UTF16String != Buffer){
                FoundBuffer = false;
                break;
            }
            if(FoundBuffer != true){
                return &UTF16LEString[i + j];
            }

        }

    }
  
    return 0x00; // No match found
}