#include "VBoxVGA.h"
#include "VBoxAceleration/vbox_drv.h"
#include <bootloader/grub/multiboot2.h>
#include <Hal.h>

extern struct multiboot_tag_vbe VBE_INFO;

typedef struct _VBoxVideoControllerData{
    uint32_t VRamTotalSize;
}VBVCD, * PVBVCD;    

static PVBVCD VirtualboxVGAC = 0x00;

KERNEL_IMPORT void print_clear();

LOUDDK_API_ENTRY void VirtualBoxChangeResolution(
    uint16_t Width, uint16_t Height
){

    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_XRES);  // Select the X resolution register
    outw(VBE_DISPI_IOPORT_DATA, Width);                    // Set X resolution to 1024 pixels


    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_YRES);  // Select the Y resolution register
    outw(VBE_DISPI_IOPORT_DATA, Height);                    // Set Y resolution to 768 pixels

    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_BPP);  // Select the bits per pixel register
    outw(VBE_DISPI_IOPORT_DATA, 32);                    // Set color depth to 32 bits per pixel

    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_ENABLE);                      // Select the enable register
    outw(VBE_DISPI_IOPORT_DATA, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);    // Enable display with LFB
    
    //VBE_INFO.vbe_mode_info.height = Height;
    //VBE_INFO.vbe_mode_info.width = Width;
    //VBE_INFO.vbe_mode_info.bpp = 32;
    //VBE_INFO.vbe_mode_info.pitch = Width * (32 / 8);
    
}


LOUSTATUS VboxHwInit(struct vbox_private *vbox);

KERNEL_IMPORT void StartDebugger();

UNUSED static LINUX_PCI_DEVICE_ID VBoxDeviceIds[] = {
    {0x80EE, ANY_PCI_ID, ANY_PCI_ID, ANY_PCI_ID, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0} // Correctly initializing all fields to 0
};


void VBoxPutPixelRgbEx(
    PDrsdVRamObject FBDEV,
    uint16_t x, 
    uint16_t y, 
    uint8_t r, uint8_t g, uint8_t b, uint8_t a
){
    
    // Calculate the offset in the framebuffer
    uint32_t bytes_per_pixel = FBDEV->FrameBuffer.Bpp / 8;
    uint8_t* framebuffer = (uint8_t*)(uintptr_t)FBDEV->FrameBuffer.FramebufferBase;

    // Ensure x and y are within the screen bounds
    if (x >= FBDEV->FrameBuffer.Width || y >= FBDEV->FrameBuffer.Height) {
        return; // Out of bounds, do nothing
    }

    // Calculate the position in the framebuffer
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



void VBoxPutPixelRgbExBasicAcceleration(
    PDrsdVRamObject FBDEV,
    uint16_t x, 
    uint16_t y, 
    uint8_t r, uint8_t g, uint8_t b, uint8_t a
){
    
        // Calculate the offset in the framebuffer
    uint32_t bytes_per_pixel = FBDEV->FrameBuffer.Bpp / 8;
    uint8_t* framebuffer = (uint8_t*)(uintptr_t)FBDEV->FrameBuffer.SecondaryFrameBufferBase;

    // Ensure x and y are within the screen bounds
    if (x >= FBDEV->FrameBuffer.Width || y >= FBDEV->FrameBuffer.Height) {
        return; // Out of bounds, do nothing
    }

    // Calculate the position in the framebuffer
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

KERNEL_IMPORT
void LouKeDrsdPutPixelMirrored(
    uint16_t x, uint16_t y, 
    uint8_t r, uint8_t g, uint8_t b
);

void VirtualBoxSvgaBlitCopy(void* Destination, void* Source, uint64_t Size){
    //Virtualbox as far as i know does not support DMA 
    //unless 3D Acelleration however i don know enough
    //to make this assumption on all set ups so the 
    //internal kernel driver is just going to use a
    //CPU transfer and when i write the external modual
    //i will include all advanced features because ther
    //are some tricks up VBox's sleeve even impressive 
    //even for actuall SVGA video hardware
    memcpy(Destination, Source, Size);
}

void InitializeVirtualBoxVgaAdapter(P_PCI_DEVICE_OBJECT PDEV){

	LouPrint("Initializeng Virtualbox VGA Adapter\n");


    if(VirtualboxVGAC == 0x00){
        VirtualboxVGAC = (PVBVCD)LouMallocEx(sizeof(VBVCD), GET_ALIGNMENT(VBVCD));
    }

    PPCI_COMMON_CONFIG PciConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;

    VirtualboxVGAC->VRamTotalSize = inl(VBE_DISPI_IOPORT_DATA);

    VirtualBoxChangeResolution(1920, 1080);

    PFrameBufferModeDefinition SupportedModes = (PFrameBufferModeDefinition)LouKeMallocEx(sizeof(FrameBufferModeDefinition), GET_ALIGNMENT(FrameBufferModeDefinition), WRITEABLE_PAGE | PRESENT_PAGE);

    SupportedModes->Width = 1920;
    SupportedModes->Height = 1080;
    SupportedModes->Bpp = 32;
    SupportedModes->Pitch = (1920 * (32 / 8));
    SupportedModes->FrameBufferType = RGB_DRSD_FRAMEBUFFER;

    uint64_t FrameBufferAdress = (uint64_t)LouKeHalGetPciVirtualBaseAddress(PciConfig, 0);

    PDrsdStandardFrameworkObject DrsdFrameWork = (PDrsdStandardFrameworkObject)LouKeMallocEx(sizeof(DrsdStandardFrameworkObject), GET_ALIGNMENT(FrameBufferModeDefinition), WRITEABLE_PAGE | PRESENT_PAGE);
    DrsdFrameWork->RgbPutPixel = VBoxPutPixelRgbEx;
    DrsdFrameWork->VRamSize = VirtualboxVGAC->VRamTotalSize;
    
    if((1920 * 1080 * 4) * 2 <= VirtualboxVGAC->VRamTotalSize){
        DrsdFrameWork->SecondaryFrameBuffer = FrameBufferAdress + (1920 * 1080 * 4);
        DrsdFrameWork->BlitCopy = VirtualBoxSvgaBlitCopy;
        DrsdFrameWork->RgbPutPixel = VBoxPutPixelRgbExBasicAcceleration;
    }

    memset((void*)FrameBufferAdress, 0, DrsdFrameWork->VRamSize);

    LouKeRegisterFrameBufferDevice(
        (void*)PDEV, 
        FrameBufferAdress,
        DrsdFrameWork->SecondaryFrameBuffer, 
        0x00,
        (1920 * 1080 * 4),
        1920, 1080,
        32, 
        RGB_DRSD_FRAMEBUFFER,
        SupportedModes,
        DrsdFrameWork
    );

    LouKeDrsdPciResetScreen(PDEV);

    StartDebugger();

    LouPrint("Hello World\n");
    LouPrint("Total VRam:%h\n",VirtualboxVGAC->VRamTotalSize);

}
