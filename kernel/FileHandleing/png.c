#include <LouAPI.h>

PPNG_FILE_HANDLE LouKeOpenPngImage(string Path){
    
    FILE* RawPng = fopen(Path); 
    if(!RawPng){
        return 0x00;
    }
    uint8_t* Buffer = (uint8_t*)RawPng;
    if((Buffer[0] != 0x89)  ||
       (Buffer[1] != 'P')   ||
       (Buffer[2] != 'N')   ||
       (Buffer[3] != 'G')   
    ){
        LouPrint("ERROR: File Is Not A PNG Image\n");
        //fclose(RawPng);
        return 0x00;
    }

    PPNG_FILE_HANDLE Result = (PPNG_FILE_HANDLE)LouKeMalloc(sizeof(PNG_FILE_HANDLE), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);

    Result->UnpackedBase = RawPng;



    return Result;
}