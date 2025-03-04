#include <LouDDK.h>
#include <Hal.h>
#include "VMWareSVGA.h"

KERNEL_IMPORT void StartDebugger();

typedef struct _VMW_PRIVATE{
    P_PCI_DEVICE_OBJECT PDEV;
    void* Context;
    mutex_t CmdBuffMutex;
    mutex_t BindingMutex;
    spinlock_t ResourceLock;
    spinlock_t HwLock;
    spinlock_t WaiterLock;
    spinlock_t CursorLock;
    PCI_COMMON_CONFIG PrivatePciConfig;
    uintptr_t IoStart;
    uintptr_t rMmIoStart;
    uint32_t rMmIoLimit;
    uintptr_t VRamStart;
    uint32_t VRamLimit;
    uintptr_t FifoBase;
    uint32_t FifoLimit;
    uint32_t FbWidth;
    uint32_t FbHeight;
    PULONG rMmIo;
    uint64_t UsedMemorySize;
    bool Assume16Bpp;
    uint32_t Capabilities;
    uint32_t Capabilities2;
}VMW_PRIVATE, * PVMW_PRIVATE;

static inline 
bool VmwIsSvgaV3(PVMW_PRIVATE VmwPrivate){
    if(VmwPrivate->PrivatePciConfig.Header.DeviceID == VMWSVGA_SVGA_III_ID){
        return true;
    }
    return false;
}

static inline 
void VmwWrite(
    PVMW_PRIVATE VmwPrivate,
    uint32_t Offset, uint32_t Value
){

    if(VmwIsSvgaV3(VmwPrivate)){
        ULONG UlValue = (ULONG)Value;
        PULONG MmioAddress = (PULONG)((uint64_t)VmwPrivate->rMmIo + (uint64_t)Offset);
        WRITE_REGISTER_ULONG(MmioAddress, UlValue);
    }
    else{
        LouKIRQL Irql;
        LouKeAcquireSpinLock(&VmwPrivate->HwLock, &Irql);
        outl((uint64_t)((uint64_t)VmwPrivate->IoStart + (uint64_t)SVGA_INDEX_PORT), Offset);
        outl((uint64_t)((uint64_t)VmwPrivate->IoStart + (uint64_t)SVGA_VALUE_PORT), Value);
        LouKeReleaseSpinLock(&VmwPrivate->HwLock, &Irql);
    }

}

static inline
uint32_t VmwRead(
    PVMW_PRIVATE VmwPrivate,
    uint32_t Offset
){
    uint32_t Result;
    if(VmwIsSvgaV3(VmwPrivate)){
        Result = (uint32_t)READ_REGISTER_ULONG((PULONG)((uint64_t)VmwPrivate->rMmIo + (uint64_t)Offset));
    }
    else{
        LouKIRQL Irql;
        LouKeAcquireSpinLock(&VmwPrivate->HwLock, &Irql);
        outl((uint64_t)((uint64_t)VmwPrivate->IoStart + (uint64_t)SVGA_INDEX_PORT), Offset);
        Result = inl((uint64_t)((uint64_t)VmwPrivate->IoStart + (uint64_t)SVGA_VALUE_PORT));
        LouKeReleaseSpinLock(&VmwPrivate->HwLock, &Irql);
    }
    return Result;
}

LOUSTATUS VMWDetectVersion(PVMW_PRIVATE VmwPrivate){
    UNUSED uint32_t SVGAID; 

    VmwWrite(VmwPrivate, SVGA_REG_ID, VmwIsSvgaV3(VmwPrivate) ? SVGA_ID_3 : SVGA_ID_2);
	SVGAID = VmwRead(VmwPrivate, SVGA_REG_ID);

    if((SVGAID == SVGA_ID_2) && (SVGAID == SVGA_ID_3)){
        DEBUG_TRAP;
        return STATUS_NOT_SUPPORTED;
    }

    return STATUS_SUCCESS;
}

LOUSTATUS VmwSetupPciResources(
    PVMW_PRIVATE VmwPrivate
){
    P_PCI_DEVICE_OBJECT PDEV = VmwPrivate->PDEV;
    PPCI_COMMON_CONFIG PciConfig = &VmwPrivate->PrivatePciConfig;
    LouKeHalPciSetMaster(PDEV);

    if(PciConfig->Header.DeviceID == VMWSVGA_SVGA_III_ID){
        VmwPrivate->rMmIoStart = (uintptr_t)LouKeHalGetPciVirtualBaseAddress(PciConfig, 0);
        VmwPrivate->rMmIoLimit = LouKeHalGetPciBaseAddressSize(PciConfig, 0);
        VmwPrivate->VRamStart = (uintptr_t)LouKeHalGetPciVirtualBaseAddress(PciConfig, 2);
        VmwPrivate->VRamLimit = LouKeHalGetPciBaseAddressSize(PciConfig, 2);
        
        if((!VmwPrivate->rMmIoStart) || 
         (!VmwPrivate->rMmIoLimit) || 
         (!VmwPrivate->VRamStart) || 
         (!VmwPrivate->VRamLimit)){
            DEBUG_TRAP;
            return STATUS_NO_SUCH_DEVICE;
        }
    }
    else if(PciConfig->Header.DeviceID == VMWSVGA_SVGA_II_ID){
        VmwPrivate->IoStart = (uintptr_t)LouKeHalGetPciVirtualBaseAddress(PciConfig, 0);
        VmwPrivate->VRamStart = (uintptr_t)LouKeHalGetPciVirtualBaseAddress(PciConfig, 1);
        VmwPrivate->VRamLimit = LouKeHalGetPciBaseAddressSize(PciConfig, 1);
        VmwPrivate->FifoBase = (uintptr_t)LouKeHalGetPciVirtualBaseAddress(PciConfig, 2);
        VmwPrivate->FifoLimit = LouKeHalGetPciBaseAddressSize(PciConfig, 2);

        if((!VmwPrivate->IoStart) || 
         (!VmwPrivate->VRamStart) || 
         (!VmwPrivate->VRamLimit) || 
         (!VmwPrivate->FifoBase) || 
         (!VmwPrivate->FifoLimit)){

            LouPrint("ERROR Getting PciRecources For VMWSVGA II\n");

            if(!VmwPrivate->IoStart){
                LouPrint("ERROR BAR:0\n");
            }
            if(!VmwPrivate->VRamStart){
                LouPrint("ERROR BAR:1 Address\n");
            }
            if(!VmwPrivate->VRamLimit){
                LouPrint("ERROR BAR:1 Size\n");
            }
            if(!VmwPrivate->FifoBase){
                LouPrint("ERROR BAR:2 Address\n");
            }
            if(!VmwPrivate->FifoLimit){
                LouPrint("ERROR BAR:2 Size\n");
            }

            while(1);
            DEBUG_TRAP;
            return STATUS_NO_SUCH_DEVICE;
        }
    }else{
        DEBUG_TRAP
        return STATUS_NO_SUCH_DEVICE;
    }

    return STATUS_SUCCESS;
}

LOUSTATUS VmwDmaSelectMode(
    PVMW_PRIVATE VmwPrivate
){

        
    return STATUS_SUCCESS;
}

LOUSTATUS VmwHostGetGustInformation(PVMW_PRIVATE VmwPrivate){



    return STATUS_SUCCESS;
}

LOUSTATUS VMWLoadDriver(PVMW_PRIVATE VmwPrivate){
    LOUSTATUS Status = STATUS_SUCCESS;

    Status = VmwSetupPciResources(VmwPrivate);
    if(!NT_SUCCESS(Status)){
        return Status;
    }

    Status = VMWDetectVersion(VmwPrivate);
    if(!NT_SUCCESS(Status)){
        return Status;
    }

    //queues can be done later
    VmwPrivate->UsedMemorySize = 0;
    VmwPrivate->Assume16Bpp = false;

    VmwPrivate->Capabilities = VmwRead(VmwPrivate, SVGA_REG_CAPABILITIES);
    if(VmwPrivate->Capabilities & SVGA_CAP_CAP2_REGISTER){
        VmwPrivate->Capabilities2 = VmwRead(VmwPrivate, SVGA_REG_CAP2);
    }

    VmwPrivate->VRamLimit = VmwRead(VmwPrivate, SVGA_REG_VRAM_SIZE);
    VmwPrivate->FifoLimit = VmwRead(VmwPrivate, SVGA_REG_MEM_SIZE);
    VmwPrivate->FbWidth   = VmwRead(VmwPrivate, SVGA_REG_MAX_WIDTH);
    VmwPrivate->FbHeight  = VmwRead(VmwPrivate, SVGA_REG_MAX_HEIGHT);

    return Status;
}

LOUSTATUS VmwSetMode(PVMW_PRIVATE VmwPrivate, uint32_t Width, uint32_t Height) {
    // Set the mode width, height, and bits per pixel
    VmwWrite(VmwPrivate, SVGA_REG_WIDTH, Width);
    VmwWrite(VmwPrivate, SVGA_REG_HEIGHT, Height);
    VmwWrite(VmwPrivate, SVGA_REG_BITS_PER_PIXEL, 32);

    // Store the framebuffer width and height in the private structure for later use
    VmwPrivate->FbWidth = Width;
    VmwPrivate->FbHeight = Height;

    // Enable the display
    VmwWrite(VmwPrivate, SVGA_REG_ENABLE, 1);

    return STATUS_SUCCESS;
}

void VmwBoxSvgaBlitCopy(void* Destination, void* Source, uint64_t Size){
    //TODO: Set up the 3d Acelleration
    memcpy(Destination, Source, Size);
}

void VmwPutPixelRgbEx(
    PDrsdVRamObject FBDEV,
    uint16_t x, 
    uint16_t y, 
    uint8_t r, uint8_t g, uint8_t b, uint8_t a
) {
    // Calculate bytes per pixel from the bits per pixel setting
    uint32_t bytes_per_pixel = FBDEV->FrameBuffer.Bpp / 8;
    uint8_t* framebuffer = (uint8_t*)(uintptr_t)FBDEV->FrameBuffer.SecondaryFrameBufferBase;

    // Ensure x and y are within the screen bounds
    if (x >= FBDEV->FrameBuffer.Width || y >= FBDEV->FrameBuffer.Height) {
        return; // Out of bounds, do nothing
    }

    // Calculate the position in the framebuffer using pitch
    uint32_t pixel_offset = (y * FBDEV->FrameBuffer.Pitch) + (x * bytes_per_pixel);

    // Set the pixel value based on the framebuffer format
    if (FBDEV->FrameBuffer.Bpp == 32) {
        // 32-bit color (RGBA)
        framebuffer[pixel_offset] = b;        // Blue
        framebuffer[pixel_offset + 1] = g;    // Green
        framebuffer[pixel_offset + 2] = r;    // Red
        framebuffer[pixel_offset + 3] = a;    // Alpha (or reserved)
    } else if (FBDEV->FrameBuffer.Bpp == 24) {
        // 24-bit color (RGB)
        framebuffer[pixel_offset] = b;        // Blue
        framebuffer[pixel_offset + 1] = g;    // Green
        framebuffer[pixel_offset + 2] = r;    // Red
    } else if (FBDEV->FrameBuffer.Bpp == 16) {
        // 16-bit color (5-6-5 RGB)
        uint16_t color = ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F);
        *((uint16_t*)(framebuffer + pixel_offset)) = color;
    }
}


LOUSTATUS InitVMWareSVGA(P_PCI_DEVICE_OBJECT PDEV){

    //DEBUG_TRAP;
    LouKeHalEnablePciDevice(PDEV);

    PVMW_PRIVATE VmwPrivate = (PVMW_PRIVATE)LouKeMallocEx(sizeof(VMW_PRIVATE), GET_ALIGNMENT(VMW_PRIVATE), WRITEABLE_PAGE | PRESENT_PAGE);
    
    LouKeHalGetPciConfiguration(PDEV, &VmwPrivate->PrivatePciConfig);
    
    VmwPrivate->PDEV = PDEV;
    VMWLoadDriver(VmwPrivate);

    VmwSetMode(VmwPrivate, 1920, 1080);


    PDEV->DeviceExtendedObject = (uintptr_t)VmwPrivate;

    PDrsdStandardFrameworkObject DrsdFrameWork = (PDrsdStandardFrameworkObject)LouKeMallocEx(sizeof(DrsdStandardFrameworkObject), GET_ALIGNMENT(DrsdStandardFrameworkObject), WRITEABLE_PAGE | PRESENT_PAGE);

    DrsdFrameWork->RgbPutPixel = VmwPutPixelRgbEx;
    DrsdFrameWork->SecondaryFrameBuffer = VmwPrivate->VRamStart + (1920 * 1080 * 4);
    DrsdFrameWork->BlitCopy = VmwBoxSvgaBlitCopy;

    LouKeRegisterFrameBufferDevice(
        (void*)PDEV, 
        VmwPrivate->VRamStart, 
        DrsdFrameWork->SecondaryFrameBuffer,
        0x00,
        (1920 * 1080 * 4), 
        1920, 1080,
        32, 
        RGB_DRSD_FRAMEBUFFER,
        0x00,
        DrsdFrameWork
    );

    LouKeDrsdPciResetScreen(PDEV);

    StartDebugger();

    LouPrint("Done Initializing VMWareSVGA Adapter\n");
    return STATUS_SUCCESS;
}