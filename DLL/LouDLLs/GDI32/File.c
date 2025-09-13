#include "Gdi32.h"


GDI32_API
HMETAFILE
CloseMetaFile(
    HDC Hdc
){



    return 0x00;
}

GDI32_API
HENHMETAFILE 
CloseEnhMetaFile(
    HDC Hdc
){



    return 0x00;
}

GDI32_API
HENHMETAFILE
CopyEnhMetaFileA(
    HENHMETAFILE    Enh,
    LPCSTR          FileName
){

    

    return 0x00;
}

GDI32_API
HMETAFILE
CopyMetaFileA(
    HMETAFILE   File,
    LPCSTR      FileName
){  



    return 0x00;
}


GDI32_API
HENHMETAFILE
CopyEnhMetaFileW(
    HENHMETAFILE    File,
    LPCWSTR         FileName
){


    return 0x00;
}


GDI32_API
HMETAFILE
CopyMetaFileW(
    HMETAFILE   File,
    LPCWSTR     FileName
){


    return 0x00;
}

GDI32_API
HDC 
CreateEnhMetaFileA(
    HDC         Hdc,
    LPCSTR      FileName,
    PRECT       Rect,
    LPCSTR      Description
){



    return 0x00;
}

GDI32_API
HDC 
CreateEnhMetaFileW(
    HDC         Hdc,
    LPCWSTR     FileName,
    PRECT       Rect,
    LPCWSTR     Description
){

    

    return 0x00;
}

GDI32_API
BOOL
DeleteEnhMEtaFile(
    HENHMETAFILE    Hmf
){



    return false;
}

GDI32_API
BOOL
DeleteMetaFile(
    HMETAFILE   Hmf
){

    

    return false;
}

