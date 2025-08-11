#include "../Awm.h"

extern HWND BackgroundWindow;
extern bool MirrorAllScreens;

void AwmInitializeWindowClipsToWindowTracker(
    PWINDOW_HANDLE Parrent, 
    PWINDOW_HANDLE Child
);

static void AddChildToParentWindow(
    PWINDOW_HANDLE Parrent,
    PWINDOW_HANDLE Child
){  
    MutexLock(&Parrent->ChildTrackerMutex);
    PCHILD_WINDOW_TRACKER Tmp = &Parrent->Children;
    while(Tmp->Peers.NextHeader){
        Tmp = (PCHILD_WINDOW_TRACKER)Tmp->Peers.NextHeader;
    }
    Tmp->Peers.NextHeader = (PListHeader)LouGlobalUserMallocType(CHILD_WINDOW_TRACKER);
    Tmp = (PCHILD_WINDOW_TRACKER)Tmp->Peers.NextHeader;
    Tmp->Child = Child;
    MutexUnlock(&Parrent->ChildTrackerMutex);
} 

static PDRSD_CLIP FindClipOwnerFromWindowClips(PDRSD_CLIP* ClipArray, SIZE ArraySize, INT64 X, INT64 Y, INT64 Width, INT64 Height){
    for(size_t i = 0 ; i < ArraySize; i++){
        if(
            (ClipArray[i]->X <= X) && (ClipArray[i]->Y <= Y) &&
            ((ClipArray[i]->X + ClipArray[i]->Width) >= (X + Width)) && ((ClipArray[i]->Y + ClipArray[i]->Height) >= (Y + Height))
        ){
            return ClipArray[i];
        }
    }
    return 0x00;
}

static PWINDOW_HANDLE FindWindowOwnerOfLocation(PWINDOW_HANDLE WindowDirectory, INT64 X, INT64 Y, INT64 Width, INT64 Height){
    PWINDOW_HANDLE Best = WindowDirectory;
    PCHILD_WINDOW_TRACKER Tmp = &WindowDirectory->Children;
    while(Tmp->Peers.NextHeader){
        Tmp = (PCHILD_WINDOW_TRACKER)Tmp->Peers.NextHeader;
        PDRSD_CLIP Clip = FindClipOwnerFromWindowClips(Tmp->Child->MainWindow, Tmp->Child->PlaneCount, X, Y, Width, Height);
        if(Clip){
            Best = FindWindowOwnerOfLocation(
                Tmp->Child, 
                X, 
                Y, 
                Width, 
                Height
            );
        }
    }
    return Best;
}

static void GetWindowFromLocation(INT64 X, INT64 Y, INT64 Width, INT64 Height, PWINDOW_HANDLE* WindowOut){
    PWINDOW_HANDLE Window = FindWindowOwnerOfLocation(BackgroundWindow, X, Y, Width, Height);
    if(WindowOut){
       *WindowOut = Window;
    }
}

void AwmInitializeWindowToTracker(
    PWINDOW_HANDLE Parrent,
    PWINDOW_HANDLE Child
){
    if(!Parrent){
        Parrent = (PWINDOW_HANDLE)BackgroundWindow;
    }
    AddChildToParentWindow(Parrent, Child);
    if((!Child->Mirrored) && (!MirrorAllScreens)){
        AwmInitializeWindowClipsToWindowTracker(Parrent, Child);
    }
}

void AwmUpdateLocationArea(
    INT64 X, INT64 Y,
    INT64 Width, INT64 Height
){
    PWINDOW_HANDLE Window;
    PDRSD_CLIP Clip;
    GetWindowFromLocation(X, Y, Width, Height, &Window);
    //
    AwmRedrawArea(Window, X, Y, Width, Height);

}