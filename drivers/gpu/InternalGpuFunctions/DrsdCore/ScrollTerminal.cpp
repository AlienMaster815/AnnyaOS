#include "DrsdCore.h"

LOUDDK_API_ENTRY void LouKeDrsdSyncScreen(PDRSD_CLIP_CHAIN Chain);

static bool UsingDosTerminal = true;

typedef struct _TERMAINAL_PLANE {
    ListHeader          Peers;
    PDRSD_CLIP          DosClip;
    size_t              CursorX;
    size_t              CursorY;
    uint32_t            TerminalBackground;
    uint32_t            TerminalForeground;
} TERMAINAL_PLANE, *PTERMAINAL_PLANE;

typedef struct _LOUOS_DOS_TERMINAL {
    TERMAINAL_PLANE     TerminalPlane;
    uint32_t            DefaultBackground;
    uint32_t            DefaultForeground;
} LOUOS_DOS_TERMINAL, *PLOUOS_DOS_TERMINAL;

static LOUOS_DOS_TERMINAL LouOsDosTerminalScreen = {
    .TerminalPlane = {0},
    .DefaultBackground = DRSD_CORE_TRANSLATE_COLOR(0, 0 , 0, 255),
    .DefaultForeground = DRSD_CORE_TRANSLATE_COLOR(0, 128, 0, 255),
};

void ScrollClipDestroyed(PDRSD_CLIP Clip) {
    PTERMAINAL_PLANE Plane = (PTERMAINAL_PLANE)LouOsDosTerminalScreen.TerminalPlane.Peers.NextHeader;
    PTERMAINAL_PLANE Prev = &LouOsDosTerminalScreen.TerminalPlane;
    while (Plane) {
        if (Plane->DosClip == Clip) {
            Prev->Peers.NextHeader = Plane->Peers.NextHeader;
            LouKeFree(Plane);
            LouPrint("Clip:%h : Successfully Destroyed From Terminal\n", Clip);
            return;
        }
        Prev = Plane;
        Plane = (PTERMAINAL_PLANE)Plane->Peers.NextHeader;
    }
}

void ScrollTerminalClipChange(PDRSD_CLIP Clip, DRSD_CLIP_UPDATE_REASON UpdateReason, void* UpdateData) {
    if (UpdateReason == CLIP_DESTROYED) {
        ScrollClipDestroyed(Clip);
    }
}


void LouKeCreateScrollTerminal(PDRSD_CLIP Clip) {
    if (!UsingDosTerminal) return;

    PTERMAINAL_PLANE TerminalPlane = &LouOsDosTerminalScreen.TerminalPlane;
    while (TerminalPlane->Peers.NextHeader) {
        TerminalPlane = (PTERMAINAL_PLANE)TerminalPlane->Peers.NextHeader;
    }
    TerminalPlane->Peers.NextHeader = (PListHeader)LouKeMallocType(TERMAINAL_PLANE, KERNEL_GENERIC_MEMORY);
    TerminalPlane = (PTERMAINAL_PLANE)TerminalPlane->Peers.NextHeader;
    TerminalPlane->DosClip = Clip;
    TerminalPlane->TerminalBackground = LouOsDosTerminalScreen.DefaultBackground;
    TerminalPlane->TerminalForeground = LouOsDosTerminalScreen.DefaultForeground;

    Clip->SignalClipChange = ScrollTerminalClipChange;

    LouKeDrsdUpdateClipColor(Clip, LouOsDosTerminalScreen.DefaultBackground);
    LouKeUpdateClipState(Clip);
    LouKeDrsdSyncScreen(Clip->ChainOwner);

    LouPrint("Hello LouOS DOS\n");
}

KERNEL_IMPORT CharMapping* GetCharecterMap(char Character);

void LouOsDosScrollDown(PDRSD_CLIP Clip, size_t Pixels) {
    size_t Width = Clip->Width;
    size_t Height = Clip->Height;
    for (size_t y = 0; y < Height - Pixels; y++) {
        for (size_t x = 0; x < Width; x++) {
            Clip->WindowBuffer[x + (y * Width)] = Clip->WindowBuffer[x + ((y + Pixels) * Width)];
        }
    }
    for (size_t y = Height - Pixels; y < Height; y++) {
        for (size_t x = 0; x < Width; x++) {
            Clip->WindowBuffer[x + (y * Width)] = 0;
        }
    }
}

void _LouKeOsDosPrintCharacter(char Character, PTERMAINAL_PLANE Plane, uint32_t Color) {
    if (Character == '\n') {
        Plane->CursorX = 0;
        if ((Plane->CursorY + 2) * 17 >= Plane->DosClip->Height) {
            LouOsDosScrollDown(Plane->DosClip, 17);
        } else {
            Plane->CursorY++;
        }
        return;
    } else if (Character == ' ') {
        Plane->CursorX++;
        return;
    }

    CharMapping* Map = GetCharecterMap(Character);
    if (!Map) return;

    if ((Plane->CursorX + 1) * 8 + Map->width > Plane->DosClip->Width) {
        _LouKeOsDosPrintCharacter('\n', Plane, Color);
    }

    int64_t x = Plane->CursorX * 8;
    int64_t y = Plane->CursorY * 17;

    for (int64_t yz = 0; yz < 16; yz++) {
        wchar_t Ybyte = Map->pixels[yz];
        for (int64_t xz = 0; xz < 16; xz++) {
            if ((Ybyte >> (15 - xz)) & 0x01) {
                LouKeDrsdClipPutPixel(Plane->DosClip, x + xz, y + yz, Color);
            }
        }
    }

    Plane->CursorX++;
}

void LouKeOsDosPrintCharecter(char Character) {
    if (!UsingDosTerminal) return;

    PTERMAINAL_PLANE Plane = (PTERMAINAL_PLANE)LouOsDosTerminalScreen.TerminalPlane.Peers.NextHeader;
    while (Plane) {
        _LouKeOsDosPrintCharacter(Character, Plane, Plane->TerminalForeground);
        Plane = (PTERMAINAL_PLANE)Plane->Peers.NextHeader;
    }
}

void LouKeOsDosUpdateMapping() {
    if (!UsingDosTerminal) return;
    PTERMAINAL_PLANE Plane = (PTERMAINAL_PLANE)LouOsDosTerminalScreen.TerminalPlane.Peers.NextHeader;
    while (Plane) {
        LouKeUpdateClipState(Plane->DosClip);
        LouKeDrsdSyncScreen(Plane->DosClip->ChainOwner);
        Plane = (PTERMAINAL_PLANE)Plane->Peers.NextHeader;
    }
}

LOUDDK_API_ENTRY
void 
LouKeExitDosMode(){
    PTERMAINAL_PLANE Plane = (PTERMAINAL_PLANE)LouOsDosTerminalScreen.TerminalPlane.Peers.NextHeader;

    while (Plane) {
        ScrollClipDestroyed(Plane->DosClip);
        LouKeDestroyClip(Plane->DosClip);
        Plane = (PTERMAINAL_PLANE)Plane->Peers.NextHeader;
    }
    UsingDosTerminal = false;
    LouKeMemoryBarrier();
}