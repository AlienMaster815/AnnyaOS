//Copyright GPL-2 Tyler Grenier (2026)
#include "../BootVid.h"

static 
LOUSTATUS
TtfUnpackGlyphObject(
    PTTF_GLYPH_DESCRIPTION  GlyphDescription,
    PTTFOBJ_GLYPH_DATA      GlyphData,
    PTTF_OBJECT             TtfObject
){

    UINT16* EndPoints = (UINT16*)(UINT8*)((UINTPTR)GlyphDescription + sizeof(TTF_GLYPH_DESCRIPTION));
    UINT32  Countours = TtfReadUint16(GlyphDescription->ContourCount);
    UINT16  InstructionLength = TtfReadUint16(EndPoints[Countours]);
    UINT8*  RawFlags = (UINT8*)(((UINTPTR)&EndPoints[Countours]) + (UINTPTR)InstructionLength + (UINTPTR)2);

    GlyphData->VectorCount  = TtfReadUint16(EndPoints[Countours - 1]) + 1;
    GlyphData->Flags        = LouKeMallocArray(UINT8, GlyphData->VectorCount, KERNEL_GENERIC_MEMORY);
    GlyphData->XCoordinates = LouKeMallocArray(INT16, GlyphData->VectorCount, KERNEL_GENERIC_MEMORY);
    GlyphData->YCoordinates = LouKeMallocArray(INT16, GlyphData->VectorCount, KERNEL_GENERIC_MEMORY);
    SIZE    Index = 0;
    UINT8*  CurrentByte = RawFlags;
    UINT8   TmpFlag;
    UINT8   RepeatCount;
    INT16   CurrentX = 0;
    INT16   CurrentY = 0;
    while(Index < GlyphData->VectorCount){
        TmpFlag = *CurrentByte++;
        GlyphData->Flags[Index++] = TmpFlag;
        if(TmpFlag & (1 << 3)){
            RepeatCount = *CurrentByte++;
            for(UINT8 Repeat = 0; Repeat < RepeatCount; Repeat++){
                GlyphData->Flags[Index++] = TmpFlag;
            }
        }
    }

    for(size_t i = 0 ; i < GlyphData->VectorCount; i++){
        TmpFlag = GlyphData->Flags[i];
        INT16 DeltaX = 0;
        if(TmpFlag & (1 << 1)){
            DeltaX = (INT16)(*CurrentByte++);
            if(!(TmpFlag & (1 << 4))){
                DeltaX = -DeltaX;
            } 
        }else{
            if(TmpFlag & (1 << 4)){
                DeltaX = 0;
            }else{
                DeltaX = (INT16)TtfReadUint16(*(UINT16*)CurrentByte);
                CurrentByte += 2;
            }
        }
        CurrentX += DeltaX;
        GlyphData->XCoordinates[i] = CurrentX; 
    }

    for(size_t i = 0 ; i < GlyphData->VectorCount; i++){
        //LouPrint("Flags[%d]:%bc\n", i, GlyphData->Flags[i]);
        TmpFlag = GlyphData->Flags[i];
        INT16 DeltaY = 0;
        if(TmpFlag & (1 << 2)){
            DeltaY = (INT16)(*CurrentByte++);
            if(!(TmpFlag & (1 << 5))){
                DeltaY = -DeltaY;
            } 
        }else{
            if(TmpFlag & (1 << 5)){
                DeltaY = 0;
            }else{
                DeltaY = (INT16)TtfReadUint16(*(UINT16*)CurrentByte);
                CurrentByte += 2;
            }
        }
        CurrentY += DeltaY;
        GlyphData->YCoordinates[i] = CurrentY; 
    }
    
    BOOLEAN LastPoint = false;

    for(size_t i = 0 ; i < 2; i++){
    
        LouPrint("Flag  :%bc\n", GlyphData->Flags[i]);
        LouPrint("XPoint:%d\n", GlyphData->XCoordinates[i]);
        LouPrint("YPoint:%d\n", GlyphData->YCoordinates[i]);
        int x = TtfGetPixelX(GlyphData->XCoordinates[i], 16, TtfObject->UnitsPerEm) + 10;
        int y = TtfGetPixelY(GlyphData->YCoordinates[i], 16, TtfObject->UnitsPerEm) + 10;

        if(LastPoint && (GlyphData->Flags[i] & TTF_ON_CURVE)){

        }
        
        if(GlyphData->Flags[i] & TTF_ON_CURVE){
            LastPoint = true;
        }else{
            LastPoint = false;
        }

        //BootRenderPutPixel(x, y, 0, 255, 0);
    
    }

    BootRenderDrawLine(
        30, 30,
        50, 50,
        0, 255, 0
    );

    BootRenderSyncScreen();
    //UINT8* Flags;

    return STATUS_SUCCESS;
}

LOUSTATUS 
TtfParseGlyphData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
){
    LouPrint("TtfParseGlyphData()\n");
    
    
    //for(size_t i = 0; i < 127; i++){
        SIZE Offset = TtfObject->AsciiGlyphOffsets['A'];
        if(Offset == UINT32_MAX){
            //continue;
        }
        PTTF_GLYPH_DESCRIPTION GlyphDescription = (PTTF_GLYPH_DESCRIPTION)(((UINTPTR)Directory->Offset + (UINTPTR)File) + (UINTPTR)Offset);    
        TtfObject->AsciiGlyphData['A'] = LouKeMallocType(TTFOBJ_GLYPH_DATA, KERNEL_GENERIC_MEMORY);
        TtfUnpackGlyphObject(
            GlyphDescription,
            TtfObject->AsciiGlyphData['A'],
            TtfObject
        );
    //}


}