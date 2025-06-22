#include <LouAPI.h>


static uint8_t GpuDevicesCount = 0x00; 

typedef struct _DrsdGpuKeyData{
    ListHeader              Neighbors;
    PDEVICE_DIRECTORY_TABLE Table;
}DrsdGpuManagmentData, * PDrsdGpuManagmentData;

static DrsdGpuManagmentData gpus = {0};

static bool LegacyGraphics = false;

static int32_t DrsdPlaneInitBase = 0x00; 

void FillOutInitializationMode(PDRSD_CONNECTOR Connector, PDRSD_PLANE_STATE State, PDRSD_CRTC Crtc){
    //DRSD_MODE_TYPE_PREFERED
    PDRSD_DISPLAY_MODE DisplayMode = (PDRSD_DISPLAY_MODE)Connector->ProbedModes.NextHeader;
    PDRSD_DEVICE Device = Connector->Device;

    while(DisplayMode->Peers.NextHeader){
        if(DisplayMode->ModeType & DRSD_MODE_TYPE_PREFERED){
            break;
        }
        DisplayMode = (PDRSD_DISPLAY_MODE)DisplayMode->Peers.NextHeader;
    }
    //TODO: check for the actuall wandted mode from the registry

    LouPrint("DisplayMode Width : %d\n", DisplayMode->HorizontalDisplay);
    LouPrint("DisplayMode Height: %d\n", DisplayMode->VirticalDisplay);

    State->SourceX = State->SourceX ? State->SourceX : DrsdPlaneInitBase; 
    State->SourceY = State->SourceY ? State->SourceY : 0;
    State->Width = DisplayMode->HorizontalDisplay;
    State->Height = DisplayMode->VirticalDisplay;
    State->FrameBuffer = LouKeMallocType(DRSD_FRAME_BUFFER, KERNEL_GENERIC_MEMORY);
    State->FrameBuffer->Device = Device;
    State->FrameBuffer->Width = State->Width;
    State->FrameBuffer->Height = State->Height;
    size_t i;
    for(i = 0; i < State->FormatCount; i++){
        if(strncmp(DRSD_COLOR_FORMAT_XRGB8888, (string)&State->Formats[i] ,4) == 0){
            State->FrameBuffer->Bpp = 32;
            State->FrameBuffer->Pitch = 4 * State->Width;
            State->FrameBuffer->FramebufferSize = State->FrameBuffer->Pitch * State->FrameBuffer->Height;
            State->FormatUsed = DRSD_COLOR_FORMAT_XRGB8888;
            break;
        }
    }
    if(i == State->FormatCount){
        return;// no available mode
    }
    //State->FrameBuffer->

    //use double buffering for now
    uint64_t TmpDmaOffset = 0;
    State->FrameBuffer->FramebufferBase = (uint64_t)LouKeGenricAllocateDmaPool(Device->VramPool, State->FrameBuffer->FramebufferSize * 3, &TmpDmaOffset); 
    State->FrameBuffer->SecondaryFrameBufferBase = State->FrameBuffer->FramebufferBase + State->FrameBuffer->FramebufferSize;
    State->FrameBuffer->TrimaryFrameBufferBase = State->FrameBuffer->FramebufferBase + (State->FrameBuffer->FramebufferSize * 2);
    State->FrameBuffer->Offset = TmpDmaOffset;
    State->Crtc = Crtc;

    memset((void*)State->FrameBuffer->FramebufferBase, 0, State->FrameBuffer->FramebufferSize);

    while(1);
    Crtc->CrtcState->NeedsModeset = true;
    Crtc->CrtcState->Enable = true;
    Crtc->CrtcState->DisplayMode = *DisplayMode;

    DrsdPlaneInitBase += DisplayMode->HorizontalDisplay;
}

static void InitializeModernGraphicsDevice(void* Device){

    PDRSD_DEVICE DrsdDevice = (PDRSD_DEVICE)Device;
    PDRSD_CONNECTOR DrsdConnector = DrsdDevice->Connectors;
    PDRSD_CRTC DrsdCrtc = DrsdDevice->Crtcs;
    PDRSD_PLANE DrsdPlane = DrsdDevice->Planes;
    while(DrsdConnector){
        LouPrint("Initializing Connector:%h\n", DrsdConnector);

        while(DrsdPlane->Peers.NextHeader){
            if(DrsdPlane->PlaneType == PRIMARY_PLANE){
                break;
            }
            DrsdPlane = (PDRSD_PLANE)DrsdPlane->Peers.NextHeader;
        }

        DrsdConnector->ProbeModeCount = DrsdConnector->Callbacks->ConnectorFillModes(
            DrsdConnector, 
            DrsdDevice->ModeConfiguration.MaximumWidth, 
            DrsdDevice->ModeConfiguration.MaximumHeight
        );

        DrsdPlane->PlaneState->Formats = DrsdPlane->Formats;
        DrsdPlane->PlaneState->FormatCount = DrsdPlane->FormatCount;
        
        FillOutInitializationMode(DrsdConnector, DrsdPlane->PlaneState, DrsdCrtc);

        DrsdPlane->FrameBuffer = DrsdPlane->PlaneState->FrameBuffer;


        if(DrsdPlane->AssistCallbacks->AtomicUpdate){
            DrsdPlane->AssistCallbacks->AtomicUpdate(DrsdPlane, DrsdPlane->PlaneState);
        }

        LouKeDrsdClearScreen(DrsdPlane);

        DrsdConnector = (PDRSD_CONNECTOR)DrsdConnector->Peers.NextHeader;
        DrsdCrtc = (PDRSD_CRTC)DrsdCrtc->Peers.NextHeader;
        DrsdPlane = (PDRSD_PLANE)DrsdPlane->Peers.NextHeader;
    }

    LouPrint("InitializeModernGraphicsDevice() STATUS_SUCCESS\n");
    
}

LOUSTATUS LouRegisterDrsdGraphicsDevice(
    PDEVICE_DIRECTORY_TABLE Table
){
    PDrsdGpuManagmentData Tmp = &gpus;
    if((uint64_t)Table->PDEV == 0xFFFFFFFFFFFFFFFF){
        LegacyGraphics = true;
    }
    
    for(uint8_t i = 0 ; i < GpuDevicesCount; i++){
        if(((uint64_t)Tmp->Table->PDEV == 0xFFFFFFFFFFFFFFFF) && (GpuDevicesCount == 1)){
            LouKeFree(Tmp->Table);
            Tmp->Table = Table; 
            LegacyGraphics = false;
            break;
        }
        if(Tmp->Neighbors.NextHeader){
            Tmp = (PDrsdGpuManagmentData)Tmp->Neighbors.NextHeader;
        }else{
            Tmp->Neighbors.NextHeader = (PListHeader)LouKeMallocEx(sizeof(DrsdGpuManagmentData), GET_ALIGNMENT(DrsdGpuManagmentData), WRITEABLE_PAGE | PRESENT_PAGE);
            Tmp = (PDrsdGpuManagmentData)Tmp->Neighbors.NextHeader;
        }
    }
    if(!LegacyGraphics){
        InitializeModernGraphicsDevice(Table->KeyData);
    }
    GpuDevicesCount++;
    Tmp->Table = Table;
    return STATUS_SUCCESS;
}

