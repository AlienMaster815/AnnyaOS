#include <LouAPI.h>


void PrintStringToWindow(
    string Str, 
    volatile PWINDHANDLE Handle, 
    uint8_t r , 
    uint8_t g, 
    uint8_t b
);

void PlaceFloatingString(
    string FloatingString,
    uint16_t x, uint16_t y,
    uint16_t ScalingX, uint16_t ScalingY,
    uint8_t r, uint8_t g, uint8_t b,
    ...
);

static spinlock_t ButtonLock;
static spinlock_t ButtonUpdateLock;

void DrawButton(
    volatile PBUTTONHANDLE ButtonHandle
){

    //ButtonRectangleShape
    DrawRectangle(
        ButtonHandle->CurrentX, 
        ButtonHandle->CurrentY, 
        ButtonHandle->CurrentWidth, 
        ButtonHandle->CurrentHeight,
        ButtonHandle->ButtonColor.r,
        ButtonHandle->ButtonColor.g,
        ButtonHandle->ButtonColor.b
    );
    if(ButtonHandle->Charecteristics.IsButton3D){
        if(ButtonHandle->Charecteristics.Inverted3D){
            Draw3DBorder(
                ButtonHandle->CurrentX, 
                ButtonHandle->CurrentY, 
                ButtonHandle->CurrentWidth, 
                ButtonHandle->CurrentHeight,
                ButtonHandle->AftHighLight.r,
                ButtonHandle->AftHighLight.g,
                ButtonHandle->AftHighLight.b,
                ButtonHandle->ForwardHighLite.r,
                ButtonHandle->ForwardHighLite.g,
                ButtonHandle->ForwardHighLite.b
            );
        }else {
            Draw3DBorder(
                ButtonHandle->CurrentX, 
                ButtonHandle->CurrentY, 
                ButtonHandle->CurrentWidth, 
                ButtonHandle->CurrentHeight,
                ButtonHandle->ForwardHighLite.r,
                ButtonHandle->ForwardHighLite.g,
                ButtonHandle->ForwardHighLite.b,
                ButtonHandle->AftHighLight.r,
                ButtonHandle->AftHighLight.g,
                ButtonHandle->AftHighLight.b
            );
        }
    }

    PlaceFloatingString(
        ButtonHandle->Charecteristics.ButtonText,
        ButtonHandle->CurrentX + 3, ButtonHandle->CurrentY + ((ButtonHandle->CurrentHeight / 2) - 5),
        ButtonHandle->XScaleing, ButtonHandle->YScaleing,
        ButtonHandle->ButtonTextColor.r,
        ButtonHandle->ButtonTextColor.g,
        ButtonHandle->ButtonTextColor.b
    );  

    LouKeDrsdSyncScreens();
}



void LouUpdateButton(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    volatile PBUTTONHANDLE HBUTTON
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&ButtonUpdateLock, &Irql);

    //fill out the basic information
    HBUTTON->CurrentX = x;
    HBUTTON->CurrentY = y;
    HBUTTON->CurrentWidth = Width;
    HBUTTON->CurrentHeight = Height;

    DrawButton(HBUTTON);
    LouKeReleaseSpinLock(&ButtonUpdateLock, &Irql);
}



volatile PBUTTONHANDLE LouCreateButton(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    uintptr_t ParentWindow,
    uint64_t CharecteristicAligned
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&ButtonLock, &Irql);

    PBUTTON_CHARECTERISTICS Charecteristics = (volatile PBUTTON_CHARECTERISTICS)(uint8_t*)CharecteristicAligned;
    volatile PBUTTONHANDLE HBUTTON = LouKeMalloc(sizeof(BUTTONHANDLE), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
    uint64_t* StringLoaction = (uint64_t*)CharecteristicAligned;
    //uint64_t* IsInverted = (volatile uint64_t*)CharecteristicAligned + 16;
    //volatile uint64_t* Is3d = (volatile uint64_t*)CharecteristicAligned + 24;
    //fill out the basic information
    HBUTTON->CurrentX = x;
    HBUTTON->CurrentY = y;
    HBUTTON->CurrentWidth = Width;
    HBUTTON->CurrentHeight = Height;

    //fill out colors
    HBUTTON->Letters.r = 0;
    HBUTTON->Letters.g = 0;
    HBUTTON->Letters.b = 0;

    HBUTTON->ButtonColor.r = 198;
    HBUTTON->ButtonColor.g = 198;
    HBUTTON->ButtonColor.b = 198;

    HBUTTON->ForwardHighLite.r = 255; 
    HBUTTON->ForwardHighLite.g = 255; 
    HBUTTON->ForwardHighLite.b = 255;

    HBUTTON->AftHighLight.r = 64; 
    HBUTTON->AftHighLight.g = 64; 
    HBUTTON->AftHighLight.b = 64; 

    //Fill Out Affinitys
    HBUTTON->ParentWindow = ParentWindow;
    HBUTTON->ChildWindow = 0x00;
    HBUTTON->NumberOfChildWindows = 0x00;
    //Fill Out Charecteristics
    HBUTTON->Charecteristics.Type       = Charecteristics->Type;
    HBUTTON->Charecteristics.ButtonName = Charecteristics->ButtonName;
    HBUTTON->Charecteristics.ButtonText = (string)*StringLoaction;
    StringLoaction += 2;
    HBUTTON->Charecteristics.IsButton3D = *StringLoaction;
    StringLoaction++;
    HBUTTON->Charecteristics.Inverted3D = *StringLoaction;

    HBUTTON->XScaleing = 1;
    HBUTTON->YScaleing = 1;

    DrawButton(HBUTTON);
    LouKeReleaseSpinLock(&ButtonLock, &Irql);

    return HBUTTON;
}