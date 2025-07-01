#include "LouDll.h"

#define LOUDLL_API __declspec(dllexport)

LOUDLL_API
PDRSD_CLIP LouDrsdCreateClip(
    void* Plane, 
    size_t X, size_t Y, 
    size_t Width, size_t Height, 
    uint8_t R, uint8_t G, uint8_t B, uint8_t A
){

    uint64_t KulaPacket[11] = {0};
    KulaPacket[2] = (uint64_t)Plane;
    KulaPacket[3] = (uint64_t)X;
    KulaPacket[4] = (uint64_t)Y;
    KulaPacket[5] = (uint64_t)Width;
    KulaPacket[6] = (uint64_t)Height;
    KulaPacket[7] = (uint64_t)R;
    KulaPacket[8] = (uint64_t)G;
    KulaPacket[9] = (uint64_t)B;
    KulaPacket[10] = (uint64_t)A;
    while(!KulaPacket[0]){
        LouCALL(LOUDRSDCREATECLIP, (uint64_t)&KulaPacket[0], 0);
    }
    return (PDRSD_CLIP)KulaPacket[1];
}

LOUDLL_API
void* LouDrsdGetPlaneInformation(size_t* CountHandle){
    uint64_t KulaPacket[3] = {0};
    KulaPacket[2] = (uint64_t)CountHandle;
    while(!KulaPacket[0]){
        LouCALL(LOUDRSDGETPLANEINFO, (uint64_t)&KulaPacket[0], 0);
    }
    return (void*)KulaPacket[1];
}

LOUDLL_API
void 
LouDrsdSyncScreen(void* Chain){
    uint64_t KulaPacket[2] = {0};
    KulaPacket[1] = (uint64_t)Chain;
    while(!KulaPacket[0]){
        LouCALL(LOUDRSDSYNCSCREEN, (uint64_t)&KulaPacket[0], 0);
    }
}

LOUDLL_API
void 
LouUpdateClipState(void* Clip){
    uint64_t KulaPacket[2] = {0};
    KulaPacket[1] = (uint64_t)Clip;
    while(!KulaPacket[0]){
        LouCALL(LOUUPDTATECLIP, (uint64_t)&KulaPacket[0], 0);
    }
}

LOUDLL_API
void 
LouUpdateShadowClipState(
    void* Clip
){
    uint64_t KulaPacket[2] = {0};
    KulaPacket[1] = (uint64_t)Clip;
    while(!KulaPacket[0]){
        LouCALL(LOUDPDATESHADOWCLIP, (uint64_t)&KulaPacket[0], 0);
    }
}

LOUDLL_API
void LouUpdateClipSubState(
    void* Clip,
    size_t X, size_t Y, 
    size_t Width, size_t Height
){
    uint64_t KulaPacket[6] = {0};
    KulaPacket[1] = (uint64_t)Clip;
    KulaPacket[2] = (uint64_t)X;
    KulaPacket[3] = (uint64_t)Y;
    KulaPacket[4] = (uint64_t)Width;
    KulaPacket[5] = (uint64_t)Height;

    while(!KulaPacket[0]){
        LouCALL(LOUDRSDUPDATECLIPSUBSTATE, (uint64_t)&KulaPacket[0], 0);
    }
}


LOUDLL_API
void LouUpdateShadowClipSubState(
    void* Clip,
    void* Shadow,
    size_t X, size_t Y, 
    size_t Width, size_t Height
){
    uint64_t KulaPacket[6] = {0};
    KulaPacket[1] = (uint64_t)Clip;
    KulaPacket[2] = (uint64_t)X;
    KulaPacket[3] = (uint64_t)Y;
    KulaPacket[4] = (uint64_t)Width;
    KulaPacket[5] = (uint64_t)Height;

    while(!KulaPacket[0]){
        LouCALL(LOUDRSDUPDATESHADOWCLIPSUBSTATE, (uint64_t)&KulaPacket[0], 0);
    }
}