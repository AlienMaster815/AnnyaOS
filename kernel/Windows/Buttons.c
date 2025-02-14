#include <LouAPI.h>


void PrintStringToWindow(
    string Str, 
    PWINDHANDLE Handle, 
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
    PBUTTONHANDLE ButtonHandle
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
    PBUTTONHANDLE HBUTTON
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



PBUTTONHANDLE LouCreateButton(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    uintptr_t ParentWindow,
    PBUTTON_CHARECTERISTICS Charecteristics
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&ButtonLock, &Irql);

    PBUTTONHANDLE HBUTTON = LouKeMalloc(sizeof(BUTTONHANDLE), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);

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
    HBUTTON->Charecteristics.ButtonText = Charecteristics->ButtonText;
    HBUTTON->Charecteristics.IsButton3D = Charecteristics->IsButton3D;
    HBUTTON->Charecteristics.Inverted3D = Charecteristics->Inverted3D;

    HBUTTON->XScaleing = 1;
    HBUTTON->YScaleing = 1;

    DrawButton(HBUTTON);
    LouKeReleaseSpinLock(&ButtonLock, &Irql);

    return HBUTTON;
}