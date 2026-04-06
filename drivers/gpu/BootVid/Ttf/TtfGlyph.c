//Copyright GPL-2 Tyler Grenier (2026)
#include "../BootVid.h"

static
void DrawBezier(int x0, int y0, int x1, int y1, int x2, int y2, UINT32 Color) {
    int prevX = x0, prevY = y0;
    for (int i = 1; i <= 10; i++) {
        float t = i / 10.0f;
        int x = (1-t)*(1-t)*x0 + 2*(1-t)*t*x1 + t*t*x2;
        int y = (1-t)*(1-t)*y0 + 2*(1-t)*t*y1 + t*t*y2;
        BootRenderDrawLineEx(prevX, prevY, x, y, Color);
        prevX = x; prevY = y;
    }
}

void TtfDrawGlyphEx(
    PTTF_OBJECT         TtfObject,
    PTTFOBJ_GLYPH_DATA  GlyphData,
    int                 x,
    int                 y,
    int                 Height,
    UINT32              Color
){
    int StartIdx = 0;
    int Width = (int)(((float)Height) * GlyphData->Aspect);

    for (int c = 0; c < GlyphData->ContourCount; c++) {
        int EndIdx = GlyphData->EndPoints[c];
        int FirstX = x + TtfGetPixelX(GlyphData->XCoordinates[StartIdx], Width, TtfObject->UnitsPerEm);
        int FirstY = (y + Height) - TtfGetPixelX(GlyphData->YCoordinates[StartIdx], Height, TtfObject->UnitsPerEm);        
        int PrevX = FirstX;
        int PrevY = FirstY;
        for (int i = StartIdx + 1; i <= EndIdx; i++) {
            int CurrX = x + TtfGetPixelX(GlyphData->XCoordinates[i], Width, TtfObject->UnitsPerEm);
            int CurrY = (y + Height) - TtfGetPixelX(GlyphData->YCoordinates[i], Height, TtfObject->UnitsPerEm);
            if (GlyphData->Flags[i] & TTF_ON_CURVE) {
                BootRenderDrawLineEx(PrevX, PrevY, CurrX, CurrY, Color);
                PrevX = CurrX;
                PrevY = CurrY;
            } 
            else {
                int NextIdx = (i == EndIdx) ? StartIdx : i + 1;
                int NextX = x + TtfGetPixelX(GlyphData->XCoordinates[NextIdx], Width, TtfObject->UnitsPerEm);
                int NextY = (y + Height) - TtfGetPixelX(GlyphData->YCoordinates[NextIdx], Height, TtfObject->UnitsPerEm);
                if (!(GlyphData->Flags[NextIdx] & TTF_ON_CURVE)) {
                    int MidX = (CurrX + NextX) / 2;
                    int MidY = (CurrY + NextY) / 2;
                    DrawBezier(PrevX, PrevY, CurrX, CurrY, MidX, MidY, Color);
                    PrevX = MidX;
                    PrevY = MidY;
                } 
                else {
                    DrawBezier(PrevX, PrevY, CurrX, CurrY, NextX, NextY, Color);
                    PrevX = NextX;
                    PrevY = NextY;
                    i++;
                }
            }
        }
        if (PrevX != FirstX || PrevY != FirstY) {
            BootRenderDrawLineEx(PrevX, PrevY, FirstX, FirstY, Color);
        }
        StartIdx = EndIdx + 1; 
    }
}


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

    GlyphData->Aspect = (float)((INT16)TtfReadUint16(GlyphDescription->XMax) - (INT16)TtfReadUint16(GlyphDescription->XMin)) / (float)TtfObject->UnitsPerEm;

    GlyphData->VectorCount  = TtfReadUint16(EndPoints[Countours - 1]) + 1;
    GlyphData->ContourCount = Countours;
    GlyphData->EndPoints    = LouKeMallocArray(UINT16, Countours, KERNEL_GENERIC_MEMORY); 

    for(size_t i = 0 ; i < Countours; i++){
        GlyphData->EndPoints[i] = TtfReadUint16(EndPoints[i]);
    }

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
    
    return STATUS_SUCCESS;
}

LOUSTATUS 
TtfParseGlyphData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
){
    LouPrint("TtfParseGlyphData()\n");
    
    
    for(size_t i = 0; i < 127; i++){
        SIZE Offset = TtfObject->AsciiGlyphOffsets[i];
        if(Offset == UINT32_MAX){
            continue;
        }
        PTTF_GLYPH_DESCRIPTION GlyphDescription = (PTTF_GLYPH_DESCRIPTION)(((UINTPTR)Directory->Offset + (UINTPTR)File) + (UINTPTR)Offset);    
        TtfObject->AsciiGlyphData[i] = LouKeMallocType(TTFOBJ_GLYPH_DATA, KERNEL_GENERIC_MEMORY);
        TtfUnpackGlyphObject(
            GlyphDescription,
            TtfObject->AsciiGlyphData[i],
            TtfObject
        );
    }

}