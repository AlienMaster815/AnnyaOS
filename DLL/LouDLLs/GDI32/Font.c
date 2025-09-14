#include "Gdi32.h"

GDI32_API
HANDLE 
AddFontMemResourceEx(
    PVOID   FileView,
    DWORD   Size,
    PVOID   Reserved,
    DWORD*  FontCount
){



    return 0x00;
}

GDI32_API
int 
AddFontResourceExA(
    LPCSTR  Name,
    DWORD   Fl,
    PVOID   Res
){

    return 0x00;
}   

GDI32_API
int 
AddFontResourceA(
    LPCSTR UnamedParam1
){
    return AddFontResourceExA(UnamedParam1, 0, 0);
}


GDI32_API
int 
AddFontResourceExW(
    LPCWSTR Name,
    DWORD   Fl,
    PVOID   Res
){

}


GDI32_API
int
AddFontResourceW(
    LPCWSTR Name
){
   return  AddFontResourceExW(Name, 0, 0);
}

GDI32_API
HFONT
CreateFontA(
    int     Height,
    int     Width,
    int     Escapement,
    int     Orientation,
    int     Weight,
    DWORD   Italic,
    DWORD   Underline,
    DWORD   Strikeout,
    DWORD   CharSet,
    DWORD   OutPrecision,
    DWORD   ClipPrecision,
    DWORD   Quality,
    DWORD   PitchAndFamily,
    LPCSTR  FaceName
){



    return 0x00;
}


GDI32_API
HFONT
CreateFontW(
    int     Height,
    int     Width,
    int     Escapement,
    int     Orientation,
    int     Weight,
    DWORD   Italic,
    DWORD   Underline,
    DWORD   Strikeout,
    DWORD   CharSet,
    DWORD   OutPrecision,
    DWORD   ClipPrecision,
    DWORD   Quality,
    DWORD   PitchAndFamily,
    LPCWSTR FaceName
){



    return 0x00;
}



GDI32_API
HFONT
CreateFontIndirectA(
    PLOGFONTA LogFont
){



    return 0x00;
}

GDI32_API
HFONT 
CreateFontIndirectW(
    PLOGFONTW LogFont
){



    return 0x00;
}

GDI32_API
HFONT
CreateFontIndirectExA(
    ENUMLOGFONTEXDVA FontLog
){



    return 0x00;
}

GDI32_API
HFONT
CreateFontIndirectExW(
    ENUMLOGFONTEXDVW FontLog
){



    return 0x00;
}

GDI32_API
HDC
CreateMetaFileA(
    LPCSTR  File
){



    return 0x00;
}

GDI32_API
HDC
CreateMetaFileW(
    LPCWSTR File
){



    return 0x00;
}

GDI32_API
BOOL
CreateScalableFontResourceA(
    DWORD   Hidden,
    LPCSTR  Font,
    LPCSTR  File,
    LPCSTR  Path
){



    return false;
}

GDI32_API
BOOL
CreateScalableFontResourceW(
    DWORD       Hidden,
    LPCWSTR     Font,
    LPCWSTR     File,
    LPCWSTR     Path
){



    return false;
}


