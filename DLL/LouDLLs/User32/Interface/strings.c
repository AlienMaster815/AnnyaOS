#include <ft2build.h>
#include FT_FREETYPE_H

__declspec(dllimport)
void*
LouGlobalUserMallocEx(size_t Size, uint64_t Alignment);

__declspec(dllimport)
void* AnnyaGetLibraryFunctionN(string ModuleName,string FunctionName);

static FT_Error (*FT_Init_FreeTypel)(FT_Library* Lib);
static FT_Error (*FT_New_Facel)(FT_Library library, const char* filepathname, FT_Long face_index, FT_Face* aface );

#define LouGlobalUserMallocType(Type) (Type*)LouGlobalUserMallocEx(sizeof(Type), GET_ALIGNMENT(Type))

typedef struct _FONT_FACE_TRACKER{
    ListHeader  Peers;
    string      FontPath;
    FT_Face     Font;
}FONT_FACE_TRACKER, * PFONT_FACE_TRACKER;

static FONT_FACE_TRACKER Fonts = {0};

static FT_Library FtInitLib = 0x00;

void InitializeFreeType(){
    FT_Init_FreeTypel = AnnyaGetLibraryFunctionN("LIBFREETYPE.DLL", "FT_Init_FreeType");

    FT_Error err = FT_Init_FreeTypel(&FtInitLib);
    FT_New_Facel = AnnyaGetLibraryFunctionN("LIBFREETYPE.DLL", "FT_New_Face");

    if (err) {
        LouPrint("FT_Init_FreeType() failed: %u\n", err);
        while(1);
    }
}

PVOID AnnyaGetFont(string FontPath){
    PFONT_FACE_TRACKER Tmp = &Fonts;
    while(Tmp->Peers.NextHeader){
        if(!strcmp(Tmp->FontPath, FontPath)){
            return (PVOID)Tmp->Font;
        }
        Tmp = (PFONT_FACE_TRACKER)Tmp->Peers.NextHeader;
    }
    

    FT_New_Facel(FtInitLib, FontPath, 0, &Tmp->Font); 
    return (PVOID)Tmp->Font;
}

typedef struct _FLOATING_STRING_DIMENTION{
    UINT32 SpaceWidth;
    UINT32 SpaceHeight;
    UINT32 Width;
    UINT32 Height;
}FLOATING_STRING_DIMENTION, * PFLOATING_STRING_DIMENTION;
  

static void GetFloatingStringDimention(string Str, PFLOATING_STRING_DIMENTION StrDimentionStruct){

    UINT32 CharWidth = StrDimentionStruct->Width;
    UINT32 CharHeight = StrDimentionStruct->Height;
    UINT32 TotalLength = 0;
    UINT32 TotalHeight = 1;
    UINT32 TLength = 0;
    SIZE Index = 0;
    while(Str[Index] != '\0'){
        switch(Str[Index]){
            case '\n':{
                TLength = 0;
                TotalHeight++;
                break;
            }
            default:
                TLength++;
                if(TLength > TotalLength){
                    TotalLength = TLength;
                }
                break;
        }
        Index++;
    }

    StrDimentionStruct->Width = TotalLength * (CharWidth + StrDimentionStruct->SpaceWidth);
    StrDimentionStruct->Height = TotalHeight * (CharHeight + StrDimentionStruct->SpaceHeight);
}

static FT_Bitmap* GetCharecterBitmap(
    PVOID FaceHandle, 
    char Charecter, 
    UINT32 CharWidth, 
    UINT32 CharHeight
){
    FT_Face Face = (FT_Face)FaceHandle;
    FT_Set_Pixel_Sizes(Face, 0, CharHeight);
    FT_UInt Index = FT_Get_Char_Index(Face, (FT_ULong)Charecter);
    if (!Index) {
        return 0x00;
    }
    if (FT_Load_Glyph(Face, Index, FT_LOAD_RENDER)) {
        return 0x00;
    }
    return &Face->glyph->bitmap;
}

PDRSD_CLIP CreateClipFromStringEx(
    string      Str, 
    PVOID       FaceHandle, 
    SIZE        CharecterWidth, 
    SIZE        CharecterHeight, 
    SIZE        SpaceWidth,
    SIZE        SpaceHeight,
    PDRSD_CLIP  BackgroundClip, 
    INT64      BackX, 
    INT64      BackY
){
    FLOATING_STRING_DIMENTION Dimentions = {0};
    Dimentions.Width = CharecterWidth;
    Dimentions.Height = CharecterHeight;
    GetFloatingStringDimention(Str, &Dimentions);
    //PDRSD_CLIP Result = LouDrsdCreateClip(BackgroundClip->ChainOwner->PlaneID, 0,0, Dimentions.Width, Dimentions.Height, 0, 0, 0, 255);

    
    while(1);
    return 0x00;
}

PDRSD_CLIP CreateClipFromString(
    string Str, 
    PVOID FaceHandle, 
    SIZE CharecterWidth, 
    SIZE CharecterHeight, 
    PDRSD_CLIP BackgroundClip, 
    INT64 BackX, 
    INT64 BackY
){
    return CreateClipFromStringEx(
        Str, 
        FaceHandle, 
        CharecterWidth, 
        CharecterHeight, 
        CharecterWidth,
        2,//adjust height diferential later 
        BackgroundClip, 
        BackX, 
        BackY
    );
}