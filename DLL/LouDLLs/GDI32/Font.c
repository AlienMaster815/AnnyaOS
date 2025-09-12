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

