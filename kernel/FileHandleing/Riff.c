#include "Riff.h"

PRIFF_OBJECT LouKeOpenRiffFile(LOUSTR PathAndFile){
    PRIFF_OBJECT RiffObject = LouKeMallocType(RIFF_OBJECT, KERNEL_GENERIC_MEMORY);
    FILE* RiffFile = fopen(PathAndFile, KERNEL_GENERIC_MEMORY);

    if(memcmp((UINT8*)RiffFile, "RIFF", 4)){
        LouPrint("LouKeOpenRiffFile():File Is Not Riff\n");
        fclose(RiffFile);
        return 0x00;
    }

    RiffObject->Riff = (PRIFF_CHUNK)(UINT8*)RiffFile;

    if(!memcmp(&RiffObject->Riff->ChunkData[0], "WAVE", 4)){
        RiffObject->FileType = WAVE_FILE;
        RiffObject->WaveFile.Fmt = (PRIFF_CHUNK)&RiffObject->Riff->ChunkData[4];
        RiffObject->WaveFile.Data = (PRIFF_CHUNK)&RiffObject->WaveFile.Fmt->ChunkData[RiffObject->WaveFile.Fmt->ChunkSize];
    }else{
        LouPrint("LouKeOpenRiffFile():WARNING:Unkown RIFF File Type\n");
        RiffObject->FileType = UNKOWN_FILE;
    }

    return RiffObject;
}

void PrintRiffID(UINT8* Address){
    for(size_t i = 0; i < 4; i++){
        LouPrint("%c", Address[i]);
    }
    LouPrint("\n");
}

LOUSTATUS LouKePlayWaveFile(PRIFF_OBJECT RiffObject){

    if(!RiffObject){
        LouPrint("LouKePlayWaveFile():Riff Object Is NULL\n");
        return STATUS_INVALID_PARAMETER;
    }
    else if(RiffObject->FileType != WAVE_FILE){
        LouPrint("LouKePlayWaveFile():File Is Not WAVE Type\n");
        return STATUS_INVALID_PARAMETER;
    }


    


    return STATUS_SUCCESS;
}
