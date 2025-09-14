#include "Gdi32.h"

GDI32_API
BOOL 
CancelDc(
    HDC Hdc
){



    return false;
}

GDI32_API
HDC
CreateCompatibleDC(
    HDC Hdc
){

    
    
    return 0x00;
}

GDI32_API
HDC
CreateDCA(
    LPCSTR       Driver,
    LPCSTR       Device,
    LPCSTR       Port,
    PDEVICEMODEA Dm 
){



    return 0x00;
}


GDI32_API
HDC
CreateDCW(
    LPCWSTR       Driver,
    LPCWSTR       Device,
    LPCWSTR       Port,
    PDEVICEMODEW  Dm 
){



    return 0x00;
}

GDI32_API
HBITMAP
CreateDIBitmap(
    HDC                     Hdc,
    BITMAP_INFO_HEADER      BitmapInfoHeader,
    DWORD                   Init,
    PVOID                   Bits,
    PBITMAP_INFO            Bmi,
    UINT32                  Usage  
){


    return 0x00;
}

GDI32_API
BOOL
DeleteDC(
    HDC Hdc
){



    return true;
}

