#include "LouLoadPrivate.h"

PVOID memcpy(PVOID Dest, PCVOID Src, SIZE Size){
    PUINT8  Destination = (PUINT8)Dest;
    PUINT8  Source = (PUINT8)Src; 
    if(!Destination || !Source || !Size){
        return 0x00;
    }
    for(SIZE i = 0 ; i < Size; i++){
        Destination[i] = Source[i];
    }
    return Destination;
}

PVOID memset(PVOID Dest, int Val, SIZE Size){
    if(!Dest){
        return 0x00;
    }
    PUINT8 Destination = (PUINT8)Dest;
    UINT8 Value = (UINT8)Val;
    for(SIZE i = 0; i < Size; i++){
        Destination[i] = Value;
    }
    return Destination;
}

PVOID memmove(PVOID Dest, PCVOID Src, SIZE Size){
    PUINT8 Destination = (PUINT8)Dest;
    PUINT8 Source = (PUINT8)Src;
    if((UINTPTR)Source > (UINTPTR)Destination){
        for(SIZE i = 0; i < Size; i++){
            Destination[i] = Source[i];
        }
    }else if((UINTPTR)Source < (UINTPTR)Destination){
        for(SIZE i = Size; i > 0; i--){
            Destination[i - 1] = Source[i - 1];
        }
    }
    return Destination;
}

//memcmp from ACPICA see /AnnyaOS/kernel/Firmware/ACPICA/utilities/utclib.c 
int memcmp(void *VBuffer1, void *VBuffer2, UINT64 Count){ 
    char *Buffer1 = (char *) VBuffer1; 
    char *Buffer2 = (char *) VBuffer2; 
    for ( ; Count-- && (*Buffer1 == *Buffer2); Buffer1++, Buffer2++) { } 
    return ((Count == 0xFFFFFFFFFFFFFFFF) ? 0 : ((unsigned char) *Buffer1 - (unsigned char) *Buffer2)); 
} 