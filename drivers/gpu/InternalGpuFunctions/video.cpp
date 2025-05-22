#include "VBox/VBoxVGA.h"
#include <Hal.h>
#include <bootloader/grub/multiboot2.h>

void InitializeAmdGpu(P_PCI_DEVICE_OBJECT PDEV);
KERNEL_IMPORT void StartDebugger();
void InitializeVgaDevice(
	P_PCI_DEVICE_OBJECT PDEV
);

bool IsVGA(uint8_t bus,uint8_t slot,uint8_t function) {

	PCI_DEVICE_OBJECT VGADev;

	VGADev.bus = bus;
	VGADev.slot = slot;
	VGADev.func = function;

	if(( LouKePciReadHeaderType(&VGADev) == 0)
	&&	((LouKePciReadClass(&VGADev) == 0 && LouKePciReadSubClass(&VGADev) == 1) ||
		(LouKePciReadClass(&VGADev) == 0x03 && LouKePciReadSubClass(&VGADev) == 0x00))
		){
		InitializeVgaDevice(
			&VGADev
		);
		return true;
	}

	return false;
}


LOUSTATUS VBoxPciProbe(P_PCI_DEVICE_OBJECT PDEV);
LOUSTATUS InitializeGenericVgaDriver(P_PCI_DEVICE_OBJECT PDEV);
LOUSTATUS InitVMWareSVGA(P_PCI_DEVICE_OBJECT PDEV);

// Function to initialize the VGA device
void InitializeVgaDevice(P_PCI_DEVICE_OBJECT PDEV) {	
	
	LouPrint("Found A Video Controller\n");

	uint16_t VendorID = PciGetVendorID(PDEV->Group, PDEV->bus, PDEV->slot);
	uint16_t DeviceID = PciGetDeviceID(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func);

	PDEV->VendorID = VendorID;
	PDEV->DeviceID = DeviceID;

	if(VendorID == 0x80EE){
		PreVBoxVGAInit(PDEV);
		InitializeVirtualBoxVgaAdapter(PDEV);
		return;
	}
	if(VendorID == 0x15AD){
		InitVMWareSVGA(PDEV);
	}
	
}

LOUDDK_API_ENTRY
LOUSTATUS AmdGpuInit(P_PCI_DEVICE_OBJECT PDEV);

LOUSTATUS InitializeStandardVga(
    P_PCI_DEVICE_OBJECT PDEV, 
    PPCI_COMMON_CONFIG PciConfig
);

LOUDDK_API_ENTRY
LOUSTATUS SetupInitialVideoDevices(){
	LouPrint("Setting Up Video Devices\n");
	PCI_COMMON_CONFIG Config = {0};
	Config.Header.VendorID = ANY_PCI_ID;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = 0x03;
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	uint8_t NumberOfPciDevices = 0;


	UNUSED PPCI_DEVICE_GROUP* VideoDevices = LouKeOpenPciDeviceGroup(&Config);

	if(VideoDevices){
		NumberOfPciDevices = LouKeGetPciCountByType(&Config);
		for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
			P_PCI_DEVICE_OBJECT PDEV = VideoDevices[i]->PDEV;
			UNUSED PPCI_COMMON_CONFIG PConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;

			switch(PConfig->Header.VendorID){
				case 0x80EE:
					PreVBoxVGAInit(PDEV);
					InitializeVirtualBoxVgaAdapter(PDEV);
					continue;
				case 0x15AD:
					InitVMWareSVGA(PDEV);
					continue;
				default:
					continue;
			}
		}
		LouKeClosePciDeviceGroup(VideoDevices);
		VideoDevices = 0x00;
	}

	return STATUS_SUCCESS;
}

static struct multiboot_tag_vbe VBE_INFO;

LOUDDK_API_ENTRY
void SetBootVbe(struct multiboot_tag_vbe VbeInfo){
	VBE_INFO = VbeInfo;
}

void GenericVideoProtocolPutPixelEx(
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

void GenericVideoProtocolBlitCopy(void* Destination, void* Source, uint64_t Size){
    memcpy(Destination, Source, Size);
}

LOUDDK_API_ENTRY
void GenericVideoProtocolInitialize(){

	PFrameBufferModeDefinition SupportedModes = (PFrameBufferModeDefinition)LouKeMallocEx(sizeof(FrameBufferModeDefinition), GET_ALIGNMENT(FrameBufferModeDefinition), WRITEABLE_PAGE | PRESENT_PAGE);
	uintptr_t FramebufferAddress = VBE_INFO.vbe_mode_info.framebuffer;
    SupportedModes->Width = 640;
    SupportedModes->Height = 480;
    SupportedModes->Bpp = 32;
    SupportedModes->Pitch = (640 * (32 / 8));
    SupportedModes->FrameBufferType = RGB_DRSD_FRAMEBUFFER;

	PDrsdStandardFrameworkObject DrsdFrameWork = (PDrsdStandardFrameworkObject)LouKeMallocEx(sizeof(DrsdStandardFrameworkObject), GET_ALIGNMENT(FrameBufferModeDefinition), WRITEABLE_PAGE | PRESENT_PAGE);
    DrsdFrameWork->RgbPutPixel = GenericVideoProtocolPutPixelEx;
    DrsdFrameWork->VRamSize = 640 * 480 * (32 / 8);
        
	DrsdFrameWork->BlitCopy = GenericVideoProtocolBlitCopy;

	uintptr_t VMemFramebuffer = (uintptr_t)LouVMalloc(ROUND_UP64(640 * 480 * (32 / 8), KILOBYTE_PAGE));

	LouKeMapContinuousMemoryBlock(FramebufferAddress, VMemFramebuffer, ROUND_UP64(640 * 480 * (32 / 8), KILOBYTE_PAGE), WRITEABLE_PAGE | PRESENT_PAGE);
	DrsdFrameWork->SecondaryFrameBuffer = (uintptr_t)LouKeMallocEx(ROUND_UP64(640 * 480 * (32 / 8), KILOBYTE_PAGE), KILOBYTE_PAGE, WRITEABLE_PAGE | PRESENT_PAGE);

    LouKeRegisterFrameBufferDevice(
		(void*)0x01,
		VMemFramebuffer,
        DrsdFrameWork->SecondaryFrameBuffer, 
        0x00,
        (640 * 480 * 4),
        640, 480,
        32, 
        RGB_DRSD_FRAMEBUFFER,
        SupportedModes,
        DrsdFrameWork
    );

	LouKeDrsdPciResetScreen(0x00);
	StartDebugger();
}