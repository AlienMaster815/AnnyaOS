#include <LouDDK.h>

static bool IsFileCoffFile(FILE File){
    PCOFF_IMAGE_HEADER  CoffStdHeader;
    if(memcmp((UINT8*)File, "MZ", 2)){
        return false;
    }
    CoffStdHeader = CoffGetImageHeader((UINT8*)File);
    if(
        (memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)COFF_PE_SIGNATURE, sizeof(UINT32))) &&
        (memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)CFI_HEADER_LOUCOFF_SIGNATURE, sizeof(UINT32)))
    ){
        return false;
    }
    return true;
}

LOUDDK_API_ENTRY FILE_TYPE LouKeGetFileType(FILE File){

    if(IsFileCoffFile(File)){
        return COFF_FILE_TYPE;
    }


    return UNKOWN_FILE_TYPE;
}