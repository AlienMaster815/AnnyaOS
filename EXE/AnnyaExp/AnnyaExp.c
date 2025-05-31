// Annya.exp.cpp : Defines the entry point for the application.
//x86_64-w64-mingw32-gcc -shared -o AnnyaExp.exe AnnyaExp.c -m64 -nostdlib -nodefaultlibs -L../../UserLibraries -lLouDll -luser32 -I../../Include


#include <Annya.h>


static HANDLE (*AnnyaOpenPngA)(string);

static volatile PWINDHANDLE TaskBarHandle = 0;
static PBUTTONHANDLE StartButton = 0;
static PBUTTONHANDLE ClockButton = 0;
static PBITMAP_HANDLE Background = 0;
//static HANDLE MyComputerPng = 0x00;
static uint16_t Width = 0;
static uint16_t Height = 0;

static char Time[25];
static uint8_t Hour = 0;
static uint8_t Minute = 0;

static uint64_t i = 0;

static TIME_T TimeStruct = {0};

//static HMODULE CODECShModule = 0;

static void UpdateClockTime(){
            if(TimeStruct.Hour > 12){
                if((TimeStruct.Hour - 12) < 10){
                    if(TimeStruct.Minute < 10){
                        _vsprintf(Time, 25, " %d:0%d PM", TimeStruct.Hour - 12, TimeStruct.Minute);
                    }else{
                        _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour - 12, TimeStruct.Minute);
                    }
                }else{
                    _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour - 12, TimeStruct.Minute);
                }
            }else if((TimeStruct.Hour != 0) && (TimeStruct.Hour < 10)){
                if(TimeStruct.Minute < 10){
                    _vsprintf(Time, 25, " %d:0%d PM", TimeStruct.Hour, TimeStruct.Minute);
                }else{
                    _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour, TimeStruct.Minute);
                }    
            }else if(TimeStruct.Hour == 0) {
                if(TimeStruct.Minute < 10){
                    _vsprintf(Time, 25, " %d:0%d PM", TimeStruct.Hour, TimeStruct.Minute);
                }else{
                    _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour, TimeStruct.Minute);
                }
            }else{
                if(TimeStruct.Minute < 10){
                    _vsprintf(Time, 25, " %d:0%d PM", TimeStruct.Hour, TimeStruct.Minute);
                }else{
                    _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour, TimeStruct.Minute);
                }
            }
            AnnyaUpdateButton(
                Width - 87, Height - 28, 
                87 - 2, 25,
                ClockButton
            );
            Minute = TimeStruct.Minute;
            Hour = TimeStruct.Hour;
}

DWORD ClockThread(PVOID Args){
    LouPrint("Creating Clock Thread\n");

    BUTTON_CHARECTERISTICS ButtonCharecteristics;
    ButtonCharecteristics.Type = PUSH_TEXT_BUTTON;
    ButtonCharecteristics.IsButton3D = true;
    ButtonCharecteristics.Inverted3D = true;
    
    ButtonCharecteristics.ButtonName = (uint64_t)"Clock";
    ButtonCharecteristics.ButtonText = (uint64_t)Time;

    GetRtcTimeData(&TimeStruct);    
    Minute = TimeStruct.Minute;
    Hour = TimeStruct.Hour;
    if(TimeStruct.Hour > 12){
        if((TimeStruct.Hour - 12) < 10){
            if(TimeStruct.Minute < 10){
                _vsprintf(Time, 25, " %d:0%d PM", TimeStruct.Hour - 12, TimeStruct.Minute);
            }else{
                _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour - 12, TimeStruct.Minute);
            }
        }else{
            if(TimeStruct.Minute < 10){
                _vsprintf(Time, 25, "%d:0%d PM", TimeStruct.Hour - 12, TimeStruct.Minute);
            }else{
                _vsprintf(Time, 25, "%d:%d PM", TimeStruct.Hour - 12, TimeStruct.Minute);
            }        }
    }else if((TimeStruct.Hour != 0) && (TimeStruct.Hour < 10)){
        if(TimeStruct.Minute < 10){
            _vsprintf(Time, 25, " %d:0%d PM", TimeStruct.Hour, TimeStruct.Minute);
        }else{
            _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour, TimeStruct.Minute);
        }    
    }else if(TimeStruct.Hour == 0) {
        if(TimeStruct.Minute < 10){
            _vsprintf(Time, 25, " %d:0%d PM", TimeStruct.Hour, TimeStruct.Minute);
        }else{
            _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour, TimeStruct.Minute);
        }
    }else{
        if(TimeStruct.Minute < 10){
            _vsprintf(Time, 25, " %d:0%d PM", TimeStruct.Hour, TimeStruct.Minute);
        }else{
            _vsprintf(Time, 25, " %d:%d PM", TimeStruct.Hour, TimeStruct.Minute);
        }
    }
    ClockButton = AnnyaCreateButton(
        Width - 87, Height - 28, 
        87 - 2, 25,
        (uintptr_t)TaskBarHandle,
        (uintptr_t)&ButtonCharecteristics
    );

    LouPrint("Clock Thread Created Entering Main Loop\n");
    
    while(1){
        GetRtcTimeData(&TimeStruct);    
        if((TimeStruct.Hour != Hour) || (TimeStruct.Minute != Minute)){
            UpdateClockTime();
        }
    }

    return 0;
}

void StartDesktop(){
    
    LouPrint("Hello UserMode Im Annya :) :: Starting Desktop\n");
    Background = AnnyaOpenBitmapImage("C:/ANNYA/PROFILES/DEFAULT/BG/ANNYA.BMP");

    DrawDesktopBackground((FILE*)Background, 0);

    LouPrint("Background Drawn : Creating Taskbar\n");

    WINDOW_CHARECTERISTICS TaskbarCharecteristics;
    TaskbarCharecteristics.Type = CANVAS_WINDOW;
    TaskbarCharecteristics.WindowName = "TaskBar";

    BUTTON_CHARECTERISTICS ButtonCharecteristics = {0};
    ButtonCharecteristics.Type = PUSH_TEXT_BUTTON;
    ButtonCharecteristics.IsButton3D = true;
    ButtonCharecteristics.Inverted3D = false;
    ButtonCharecteristics.ButtonName = (uint64_t)"StartButton";
    ButtonCharecteristics.ButtonText = (uint64_t)"Start";
    

    TaskBarHandle = AnnyaCreateCanvasBuffer(
        0 , AnnyaGetScreenBufferHeight() - 30, 
        AnnyaGetScreenBufferWidth() , 30,
        0x00,
        &TaskbarCharecteristics
    );

    AnnyaChangeCanvasBufferColor(
        TaskBarHandle,
        198,
        198,
        198,
        0
    );

    AnnyaCreateButton(
        0 + 2, Height - 28, 
        50 - 2, 25,
        (uintptr_t)TaskBarHandle,
        (uintptr_t)&ButtonCharecteristics
    );

    //MyComputerPng = AnnyaOpenPngA("C:/ANNYA/AOSMC.PNG");



    LouPrint("Desktop Drawn\n");

}

int WndProc(void* hwnd, uint32_t uMsg, void* WParam, void* LParam);


int WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     CommandLine,
    int       CmdShow 
){
    LouPrint("AnnyaExp Created With Instance:%h\n", hInstance);
    LouPrint("Loading CODECS.DLL\n");

    //CODECShModule = LoadLibraryA("C:/ANNYA/SYSTEM64/CODECS.DLL");

    //if(!CODECShModule){
    //    LouPrint("CODECS.DLL Could Not Be Found\n");
    //    while(1);
    //}

    //AnnyaOpenPngA = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaOpenPngA");

    Time[0] = '\0';
    
    Width = AnnyaGetScreenBufferWidth();
    Height = AnnyaGetScreenBufferHeight();

    StartDesktop();

    //LouPrint("Desktop created : Starting Clock Thread\n");
    PTHREAD PTClock = AnnyaCreateThread(ClockThread, 0x00);

    LouPrint("Clock Thread Running As Thread:%h\n", PTClock);

    LouPrint("Shell Initialization Complete\n");
    //ZlibTest();
    while(1){

    }
    return (int)-1;

}


int WndProc(void* hwnd, uint32_t uMsg, void* WParam, void* LParam){

}