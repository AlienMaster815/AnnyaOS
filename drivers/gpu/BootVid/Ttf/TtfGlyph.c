//Copyright GPL-2 Tyler Grenier (2026)
#include "../BootVid.h"

//void 
//TtfSortEdgesTopTown(
//    UINT16* OutSort,
//    UINT16* Vector,
//    SIZE    VectorSize
//    SIZE    VectorCount
//){
//
//}


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

float BootRenderAbsolute(float x);

UNUSED
static 
LOUSTATUS GlyphLineDoSomthing(
    int x1, int y1,
    int x2, int y2,
    LOUSTATUS (*Somthing)(int, int, PVOID),
    PVOID       Context
){
    LOUSTATUS Status;
    if (x1 == x2 && y1 == y2) {
        Status = Somthing(x1, y1, Context);
        return Status;
    }

    int dx = BootRenderAbsolute(x2 - x1);
    int dy = -BootRenderAbsolute(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;

    while (1) {
        if (x1 == x2 && y1 == y2) break;
        Status = Somthing(x1, y1, Context);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        int e2 = 2 * err;
        if (e2 >= dy) { 
            err += dy; 
            x1 += sx; 
        }
        if (e2 <= dx) { 
            err += dx; 
            y1 += sy; 
        }
    }
    return STATUS_SUCCESS;
}

static LOUSTATUS GlyphBezierDoSomthing(
    int x0, int y0, 
    int x1, int y1, 
    int x2, int y2, 
    LOUSTATUS (*Somthing)(int, int, PVOID),
    PVOID       Context
) {
    LOUSTATUS Status;
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
        Status = GlyphLineDoSomthing(prevX, prevY, x, y, Somthing, Context);        
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        prevX = x;
        prevY = y;
    }
    return STATUS_SUCCESS;
}

UNUSED 
static 
LOUSTATUS
GlpyhDoSomthing(
    PTTF_OBJECT         TtfObject,
    PTTFOBJ_GLYPH_DATA  GlyphData,
    int                 x,
    int                 y,
    int                 Height,
    LOUSTATUS           (*Somthing)(int, int, PVOID),
    PVOID               Context
){
    if(!Somthing){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status;

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
                Status = GlyphLineDoSomthing(PrevX, PrevY, CurrX, CurrY, Somthing, Context);
                if(Status != STATUS_SUCCESS){
                    return Status;
                }
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
                    Status = GlyphBezierDoSomthing(PrevX, PrevY, CurrX, CurrY, MidX, MidY, Somthing, Context);
                    if(Status != STATUS_SUCCESS){
                        return Status;
                    }
                    PrevX = MidX; 
                    PrevY = MidY;
                } 
                else {
                    Status = GlyphBezierDoSomthing(PrevX, PrevY, CurrX, CurrY, NextX, NextY, Somthing, Context);
                    if(Status != STATUS_SUCCESS){
                        return Status;
                    }
                    PrevX = NextX; 
                    PrevY = NextY;
                    i++;
                }
            }
        }        
        if (PrevX != FirstX || PrevY != FirstY) {
            Status = GlyphLineDoSomthing(PrevX, PrevY, FirstX, FirstY, Somthing, Context);
            if(Status != STATUS_SUCCESS){
                return Status;
            }
        }
        StartIdx = EndIdx + 1;
    }
}

LOUSTATUS 
TtfGetVectorEdgeCount(
    PTTFOBJ_GLYPH_DATA  GlyphData,             
    SIZE*               VectorCount,
    SIZE*               EdgeCount
){
    if((!GlyphData) || (!VectorCount) || (!EdgeCount)){
        return STATUS_INVALID_PARAMETER;
    }



    return STATUS_SUCCESS;
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
    UINT16*     VectorOut;
    UINT16*     ReorganizorStack;
}GET_VECTOR_STRUCT, * PGET_VECTOR_STRUCT;

static 
LOUSTATUS 
GlpyhGetVectors(
    int X, 
    int Y, 
    PVOID Context
){
    PGET_VECTOR_STRUCT Gvs = (PGET_VECTOR_STRUCT)Context;
    Gvs->VectorOut[Gvs->CurrentOut + 0] = X;
    Gvs->VectorOut[Gvs->CurrentOut + 1] = Y;
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

static 
UINT16
GlyphGetXCount(
    PGET_VECTOR_STRUCT Gvs
){

}

void 
GlyphScanlineFill(
    PGET_VECTOR_STRUCT Gvs
){  

    SIZE YCount = GlyphGetYCount(Gvs);
    SIZE CurrentY;
    UINT16 CurrentYLine = Gvs->VectorOut[1];
    SIZE Index = 0;
    SIZE Next = 0;
    for(SIZE YLine = 0 ; YLine < YCount; YLine++){
        CurrentY = Gvs->VectorOut[Index * 2 + 1];
        BOOLEAN Inside = true;
        while(Gvs->VectorOut[Index * 2 + 1] == CurrentY){
            Next = Index;
            if((Gvs->VectorOut[(Next + 1) * 2] == (Gvs->VectorOut[Next * 2] + 1))){
                while((Gvs->VectorOut[Next * 2 + 1] == CurrentY) && (Gvs->VectorOut[(Next + 1) * 2] == (Gvs->VectorOut[Next * 2] + 1))){
                    BootRenderPutPixel(Gvs->VectorOut[Next * 2], Gvs->VectorOut[Next * 2 + 1], 0,255,0);
                    Next++;
                }
                Inside = false;
                goto _GOTO_NEXT_VERTECES;
            }else{
                Next++;
            }
            if(Gvs->VectorOut[Next * 2 + 1] != CurrentY){
                goto _GOTO_NEXT_VERTECES;
            }else if(Gvs->VectorOut[(Next + 1) * 2 + 1] != CurrentY){
                BootRenderDrawLine(Gvs->VectorOut[Index * 2], Gvs->VectorOut[Index * 2 + 1],Gvs->VectorOut[Next * 2], Gvs->VectorOut[Next * 2 + 1], 0,255,0);
                goto _GOTO_NEXT_VERTECES;
            }
            

            if(Inside){
                BootRenderDrawLine(Gvs->VectorOut[Index * 2], Gvs->VectorOut[Index * 2 + 1],Gvs->VectorOut[Next * 2], Gvs->VectorOut[Next * 2 + 1], 0,255,0);
                Inside = false;
            }else{
                Inside = true;
            }
            
            _GOTO_NEXT_VERTECES:
            if(Index == Next) {
                Index++;
            }
            else{
                Index = Next;
            }
        }
        //LouPrint("X:%d : Y:%d\n", Gvs->VectorOut[i * 2], Gvs->VectorOut[i * 2 + 1]);
    }

}

void BootRenderGlyph(
    PTTF_OBJECT         TtfObject,
    PTTFOBJ_GLYPH_DATA  GlyphData,
    SIZE                Height
){
    GET_VECTOR_STRUCT Gvs = {0};   

    GlpyhDoSomthing(
        TtfObject,
        GlyphData,
        0, 0,
        Height,
        GlpyCountVectors,
        &Gvs.Count
    );

    Gvs.VectorOut           = LouKeMallocArray(UINT16, Gvs.Count + 2, KERNEL_GENERIC_MEMORY);
    Gvs.ReorganizorStack    = LouKeMallocArray(UINT16, Gvs.Count + 2, KERNEL_GENERIC_MEMORY);

    GlpyhDoSomthing(
        TtfObject,
        GlyphData,
        0, 0,
        Height,
        GlpyhGetVectors,
        &Gvs
    );

    GlyphSortTopBottom(&Gvs);

    GlyphSortLeftRigt(&Gvs);
    
    GlyphScanlineFill(&Gvs);

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


    //TtfDrawGlyphEx(TtfObject, TtfObject->AsciiGlyphData['A'], 10, 10, 18, SET_RGB(0, 255, 0));
    //TtfDrawGlyphEx(TtfObject, TtfObject->AsciiGlyphData['a'], 36, 10, 18, SET_RGB(0, 255, 0));

    //BootRenderSyncScreen();

    BootRenderGlyph(
        TtfObject,
        TtfObject->AsciiGlyphData['A'],
        64
    );

    BootRenderSyncScreen();

}