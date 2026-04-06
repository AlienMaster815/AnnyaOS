//Copyright GPL-2 Tyler Grenier (2026)
#include "../BootVid.h"

UINT32 BootRenderGetPixel(
    INT32 x, INT32 y
);

static void DrawBezier(int x0, int y0, int x1, int y1, int x2, int y2, UINT32 Color) {
    int prevX = x0, prevY = y0;
    const int segments = 10; 
    for (int i = 1; i <= segments; i++) {
        float t = (float)i / segments;
        float xa = x0 + t * (x1 - x0);
        float ya = y0 + t * (y1 - y0);
        float xb = x1 + t * (x2 - x1);
        float yb = y1 + t * (y2 - y1);
        int x = (int)(xa + t * (xb - xa));
        int y = (int)(ya + t * (yb - ya));
        BootRenderDrawLineEx(prevX, prevY, x, y, Color);        
        prevX = x;
        prevY = y;
    }
}

void TtfDrawGlyphEx(
    PTTF_OBJECT         TtfObject,
    PTTFOBJ_GLYPH_DATA  GlyphData,
    int                 x,
    int                 y,
    int                 Height,
    UINT32              Color
) {
    int StartIdx = 0;
    float Scale = (float)Height / (float)TtfObject->UnitsPerEm;
    int Width = (int)((float)Height * GlyphData->Aspect);

    for (int c = 0; c < GlyphData->ContourCount; c++) {
        int EndIdx = GlyphData->EndPoints[c];
        
        int FirstX = x + (int)(GlyphData->XCoordinates[StartIdx] * Scale + 0.5f);
        int FirstY = (y + Height) - (int)(GlyphData->YCoordinates[StartIdx] * Scale + 0.5f);
        
        int PrevX = FirstX;
        int PrevY = FirstY;

        for (int i = StartIdx + 1; i <= EndIdx; i++) {
            int CurrX = x + (int)(GlyphData->XCoordinates[i] * Scale + 0.5f);
            int CurrY = (y + Height) - (int)(GlyphData->YCoordinates[i] * Scale + 0.5f);

            if (GlyphData->Flags[i] & TTF_ON_CURVE) {
                BootRenderDrawLineEx(PrevX, PrevY, CurrX, CurrY, Color);
                PrevX = CurrX; 
                PrevY = CurrY;
            } 
            else {
                int NextIdx = (i == EndIdx) ? StartIdx : i + 1;
                int NextX = x + (int)(GlyphData->XCoordinates[NextIdx] * Scale + 0.5f);
                int NextY = (y + Height) - (int)(GlyphData->YCoordinates[NextIdx] * Scale + 0.5f);

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
    TtfFillGlyph(x, y, Width, Height);

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


    TtfDrawGlyphEx(TtfObject, TtfObject->AsciiGlyphData['A'], 10, 10, 18, SET_RGB(0, 255, 0));
    TtfDrawGlyphEx(TtfObject, TtfObject->AsciiGlyphData['a'], 36, 10, 18, SET_RGB(0, 255, 0));

    BootRenderSyncScreen();

}