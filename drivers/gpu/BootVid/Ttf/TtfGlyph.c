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
    GlyphData->ContourCount = Countours;
    GlyphData->EndPoints    = LouKeMallocArray(UINT16, Countours, KERNEL_GENERIC_MEMORY); 
    GlyphData->XMin = GlyphDescription->XMin;
    GlyphData->XMax = GlyphDescription->XMax;

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

static
LOUSTATUS 
GlpyCountVectors(
    int X, 
    int Y, 
    PVOID Context
){
    SIZE* Foo = (SIZE*)Context;
    *Foo = *Foo + 2; //im not doing += cause i had issues in the past with referenceing increments
    return STATUS_SUCCESS;
}

typedef struct _GET_VECTOR_STRUCT{
    SIZE        Count;
    SIZE        CurrentOut;
    INT16       ShiftX;
    INT16       ShiftY;
    INT16*      VectorOut;
    INT16*      ReorganizorStack;
}GET_VECTOR_STRUCT, * PGET_VECTOR_STRUCT;

static 
LOUSTATUS 
GlpyhGetVectors(
    int X, 
    int Y, 
    PVOID Context
){
    PGET_VECTOR_STRUCT Gvs = (PGET_VECTOR_STRUCT)Context;
    Gvs->VectorOut[Gvs->CurrentOut + 0] = X + Gvs->ShiftX;
    Gvs->VectorOut[Gvs->CurrentOut + 1] = Y - Gvs->ShiftY;
    Gvs->CurrentOut += 2;
}

static
void
GlyphSortTopBottom(PGET_VECTOR_STRUCT Gvs){    
    memcpy(Gvs->ReorganizorStack, Gvs->VectorOut, Gvs->Count * sizeof(UINT16));
    memset(Gvs->VectorOut, 0, Gvs->Count * sizeof(UINT16));

    SIZE YCount = Gvs->Count / 2;
    Gvs->CurrentOut = 0;

    UINT16 TmpY;
    UINT16 TmpX;
    SIZE i;
    for(SIZE i = 0 ; i < YCount; i++){
        TmpY = Gvs->ReorganizorStack[i * 2 + 1];
        TmpX = Gvs->ReorganizorStack[i * 2];
        SIZE j = 0;
        for(; j < i; j++){
            if(TmpY > Gvs->VectorOut[j * 2 + 1]){
                memcpy(&Gvs->VectorOut[(j + 1) * 2], &Gvs->VectorOut[j * 2], (i - j) * (sizeof(UINT16) * 2));
                break;
            }
        }
        Gvs->VectorOut[j * 2]       = TmpX;
        Gvs->VectorOut[j * 2 + 1]   = TmpY;
        Gvs->CurrentOut++;
    }
    Gvs->CurrentOut *= 2;
    memset(Gvs->ReorganizorStack, 0, Gvs->Count * sizeof(UINT16));
}



static
void
GlyphSortLeftRigt(
    PGET_VECTOR_STRUCT Gvs
){
    memcpy(Gvs->ReorganizorStack, Gvs->VectorOut, Gvs->Count * sizeof(UINT16));
    memset(Gvs->VectorOut, 0, Gvs->Count * sizeof(UINT16));

    SIZE YCount = Gvs->Count / 2;
    Gvs->CurrentOut = 0;

    UINT16 TmpY;
    UINT16 TmpX;
    SIZE i;
    SIZE BaseY = Gvs->ReorganizorStack[1];
    SIZE BaseVector = 0;
    for(SIZE i = 0 ; i < YCount; i++){
        TmpY = Gvs->ReorganizorStack[i * 2 + 1];
        TmpX = Gvs->ReorganizorStack[i * 2];

        if(TmpY != BaseY){
            BaseY = TmpY;
            BaseVector = i;
        }
        SIZE j;
        for(j = BaseVector; j < i; j++){
            if(TmpX < Gvs->VectorOut[j * 2]){
                memcpy(&Gvs->VectorOut[(j + 1) * 2], &Gvs->VectorOut[j * 2], (i - j) * (sizeof(UINT16) * 2));
                break;
            }
        }
        Gvs->VectorOut[j * 2]       = TmpX;
        Gvs->VectorOut[j * 2 + 1]   = TmpY;
        Gvs->CurrentOut++;
    }
    Gvs->CurrentOut *= 2;
    memset(Gvs->ReorganizorStack, 0, Gvs->Count * sizeof(UINT16));
}

static 
UINT16
GlyphGetYCount(
    PGET_VECTOR_STRUCT Gvs
){
    SIZE TotalYCount = Gvs->Count / 2;
    UINT16 CurrentY = Gvs->VectorOut[1];
    UINT16 Result = 0;
    for(SIZE i = 0 ; i < TotalYCount; i++){ 
        Result++;
        for(;(i < TotalYCount) && (Gvs->VectorOut[i * 2 + 1] == CurrentY); i++){
        
        }
        CurrentY = Gvs->VectorOut[i * 2 + 1];
    }
    return Result;
}

static LOUSTATUS GlyphLineToVectors(
    int x1, int y1, int x2, int y2, 
    LOUSTATUS (*Somthing)(int, int, PVOID), PVOID Context
) {
    if (y1 == y2){
        return STATUS_SUCCESS;
    } 

    if (y1 > y2) {
        int tx = x1; x1 = x2; x2 = tx;
        int ty = y1; y1 = y2; y2 = ty;
    }

    float dx = (float)(x2 - x1) / (float)(y2 - y1);
    float currentX = (float)x1;

    for (int y = y1; y < y2; y++) {
        LOUSTATUS Status = Somthing((int)(currentX + 0.5f), y, Context);
        if (Status != STATUS_SUCCESS) return Status;
        currentX += dx;
    }
    return STATUS_SUCCESS;
}

static LOUSTATUS GlyphBezierToVectors(
    int x0, int y0, int x1, int y1, int x2, int y2, 
    LOUSTATUS (*Somthing)(int, int, PVOID), PVOID Context
) {
    int prevX = x0, prevY = y0;
    const int segments = 10; 
    for (int i = 1; i <= segments; i++) {
        float t = (float)i / segments;
        float invT = 1.0f - t;
        
        int x = (int)(invT * invT * x0 + 2 * invT * t * x1 + t * t * x2 + 0.5f);
        int y = (int)(invT * invT * y0 + 2 * invT * t * y1 + t * t * y2 + 0.5f);
        
        LOUSTATUS Status = GlyphLineToVectors(prevX, prevY, x, y, Somthing, Context);
        if (Status != STATUS_SUCCESS) return Status;
        
        prevX = x;
        prevY = y;
    }
    return STATUS_SUCCESS;
}



static LOUSTATUS GlpyhDoSomthing(
    PTTF_OBJECT TtfObject, PTTFOBJ_GLYPH_DATA GlyphData,
    int x, int y, int Height,
    LOUSTATUS (*Somthing)(int, int, PVOID), PVOID Context
) {
    if (!Somthing) return STATUS_INVALID_PARAMETER;

    float Scale = (float)Height / (float)TtfObject->UnitsPerEm;
    int StartIdx = 0;

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
                GlyphLineToVectors(PrevX, PrevY, CurrX, CurrY, Somthing, Context);
                PrevX = CurrX; PrevY = CurrY;
            } else {
                int NextIdx = (i == EndIdx) ? StartIdx : i + 1;
                int NextX = x + (int)(GlyphData->XCoordinates[NextIdx] * Scale + 0.5f);
                int NextY = (y + Height) - (int)(GlyphData->YCoordinates[NextIdx] * Scale + 0.5f);

                if (!(GlyphData->Flags[NextIdx] & TTF_ON_CURVE)) {
                    int MidX = (CurrX + NextX) / 2;
                    int MidY = (CurrY + NextY) / 2;
                    GlyphBezierToVectors(PrevX, PrevY, CurrX, CurrY, MidX, MidY, Somthing, Context);
                    PrevX = MidX; PrevY = MidY;
                } else {
                    GlyphBezierToVectors(PrevX, PrevY, CurrX, CurrY, NextX, NextY, Somthing, Context);
                    PrevX = NextX; PrevY = NextY;
                    i++;
                }
            }
        }
        GlyphLineToVectors(PrevX, PrevY, FirstX, FirstY, Somthing, Context);
        StartIdx = EndIdx + 1;
    }
    return STATUS_SUCCESS;
}

void GlyphScanlineFill(PGET_VECTOR_STRUCT Gvs, PBOOTVID_BITMAP Map) {
    SIZE TotalPoints = Gvs->Count / 2;
    for (SIZE i = 0; i < (TotalPoints & ~1); i += 2) {
        UINT16 x1 = Gvs->VectorOut[i * 2];
        UINT16 y1 = Gvs->VectorOut[i * 2 + 1];
        UINT16 x2 = Gvs->VectorOut[(i + 1) * 2];
        UINT16 y2 = Gvs->VectorOut[(i + 1) * 2 + 1];

        if (y1 == y2) {
            for (UINT16 x = x1; x <= x2; x++) {
                BootVidBitmapPutPixelEx(Map, x, y1, SET_RGB(0, 255, 0));
            }
        } else {
            i--; 
        }
    }
}


void BootRenderGlyph(PTTF_OBJECT TtfObject, PTTFOBJ_GLYPH_DATA GlyphData, SIZE Height) {
    GET_VECTOR_STRUCT Gvs = {0};   
    
    Gvs.ShiftX = (INT16)(((float)TtfObject->ShiftX / TtfObject->UnitsPerEm) * (float)Height + 0.0f);
    Gvs.ShiftY = (INT16)(((float)TtfObject->ShiftY / TtfObject->UnitsPerEm) * (float)Height + 0.5f);

    Height -= Gvs.ShiftY; //scale height down so negative minimal also fits

    Gvs.ShiftX = (INT16)(((float)TtfObject->ShiftX / TtfObject->UnitsPerEm) * (float)Height + 0.0f);
    Gvs.ShiftY = (INT16)(((float)TtfObject->ShiftY / TtfObject->UnitsPerEm) * (float)Height + 0.5f);

    Height += Gvs.ShiftY; //scale back up within original height

    GlpyhDoSomthing(TtfObject, GlyphData, 0, 0, Height, GlpyCountVectors, &Gvs.Count);
    
    Gvs.VectorOut = LouKeMallocArray(UINT16, Gvs.Count + 2, KERNEL_GENERIC_MEMORY);
    if (!Gvs.VectorOut) return;

    GlpyhDoSomthing(TtfObject, GlyphData, 0, 0, Height, GlpyhGetVectors, &Gvs);

    SIZE TotalPoints = Gvs.Count / 2;
    for (SIZE i = 0; i < TotalPoints - 1; i++) {
        for (SIZE j = 0; j < TotalPoints - i - 1; j++) {
            if (Gvs.VectorOut[j*2+1] > Gvs.VectorOut[(j+1)*2+1] || 
               (Gvs.VectorOut[j*2+1] == Gvs.VectorOut[(j+1)*2+1] && Gvs.VectorOut[j*2] > Gvs.VectorOut[(j+1)*2])) {
                UINT16 tx = Gvs.VectorOut[j*2];
                Gvs.VectorOut[j*2] = Gvs.VectorOut[(j+1)*2];
                Gvs.VectorOut[(j+1)*2] = tx;
                UINT16 ty = Gvs.VectorOut[j*2+1];
                Gvs.VectorOut[j*2+1] = Gvs.VectorOut[(j+1)*2+1];
                Gvs.VectorOut[(j+1)*2+1] = ty;
            }
        }
    }
    PBOOTVID_BITMAP NewMap;
    float Scale = (float)Height / (float)TtfObject->UnitsPerEm;

    BootVidCreateBitmap(&NewMap, Height, Height); //create a cube and trim after

    GlyphData->Bitmap = (PVOID)NewMap;

    GlyphScanlineFill(&Gvs, NewMap);

    BootVidTrimBitmap(NewMap, 0);
    LouKeFree(Gvs.VectorOut);
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
            TtfObject->AsciiGlyphData[i] = 0x00;
            continue;
        }
        PTTF_GLYPH_DESCRIPTION GlyphDescription = (PTTF_GLYPH_DESCRIPTION)(((UINTPTR)Directory->Offset + (UINTPTR)File) + (UINTPTR)Offset);    
        TtfObject->AsciiGlyphData[i] = LouKeMallocType(TTFOBJ_GLYPH_DATA, KERNEL_GENERIC_MEMORY);
        TtfUnpackGlyphObject(
            GlyphDescription,
            TtfObject->AsciiGlyphData[i],
            TtfObject
        );
        BootRenderGlyph(
            TtfObject,
            TtfObject->AsciiGlyphData[i],
            14
        );
    }

}

void 
TtfCloseGlyphData(
    PTTF_OBJECT TtfObject
){
    for(size_t i = 0 ; i < 127; i++){
        if(!TtfObject->AsciiGlyphData[i]){
            continue;
        }
        BootVidDestroyBitmap(TtfObject->AsciiGlyphData[i]->Bitmap);
        LouKeFree(TtfObject->AsciiGlyphData[i]->YCoordinates);
        LouKeFree(TtfObject->AsciiGlyphData[i]->XCoordinates);
        LouKeFree(TtfObject->AsciiGlyphData[i]->Flags);
        LouKeFree(TtfObject->AsciiGlyphData[i]->EndPoints);
    }
}