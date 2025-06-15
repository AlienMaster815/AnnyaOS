#include <LouDDK.h>
#include <Hal.h>
#include <bootloader/grub/multiboot2.h>

KERNEL_IMPORT void StartDebugger();

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

static struct multiboot_tag_framebuffer_common* BootGraphics = 0x00;

LOUDDK_API_ENTRY
void LouKeDeferBootGraphics(
	struct multiboot_tag_framebuffer_common* BootGraphicsDefer
){
	BootGraphics = BootGraphicsDefer;
}

LOUDDK_API_ENTRY
void InitializeBootGraphics(){
	if(!BootGraphics){
		return;
	}
	uint16_t Width = BootGraphics->framebuffer_width;
	uint16_t Height = BootGraphics->framebuffer_height;
	uint16_t Bpp = BootGraphics->framebuffer_bpp;
	size_t FrameBufferSize = Bpp;
	FrameBufferSize /= 8;
	FrameBufferSize *= Width * Height;


	PFrameBufferModeDefinition SupportedModes = (PFrameBufferModeDefinition)LouKeMallocEx(sizeof(FrameBufferModeDefinition), GET_ALIGNMENT(FrameBufferModeDefinition), WRITEABLE_PAGE | PRESENT_PAGE);
	uintptr_t FramebufferAddress = BootGraphics->framebuffer_addr;
    SupportedModes->Width = Width;
    SupportedModes->Height = Height;
    SupportedModes->Bpp = Bpp;
    SupportedModes->Pitch = (Width * (Bpp / 8));
    SupportedModes->FrameBufferType = RGB_DRSD_FRAMEBUFFER;

	PDrsdStandardFrameworkObject DrsdFrameWork = (PDrsdStandardFrameworkObject)LouKeMallocEx(sizeof(DrsdStandardFrameworkObject), GET_ALIGNMENT(FrameBufferModeDefinition), WRITEABLE_PAGE | PRESENT_PAGE);
    DrsdFrameWork->RgbPutPixel = GenericVideoProtocolPutPixelEx;
    DrsdFrameWork->VRamSize = Width * Height * (Bpp / 8);
        
	DrsdFrameWork->BlitCopy = GenericVideoProtocolBlitCopy;

	uintptr_t VMemFramebuffer = (uintptr_t)LouVMalloc(ROUND_UP64(Width * Height * (Bpp / 8), KILOBYTE_PAGE));

	LouKeMapContinuousMemoryBlock(FramebufferAddress, VMemFramebuffer, ROUND_UP64(Width * Height * (Bpp / 8), KILOBYTE_PAGE), WRITEABLE_PAGE | PRESENT_PAGE);
	DrsdFrameWork->SecondaryFrameBuffer = (uintptr_t)LouKeMallocEx(ROUND_UP64(Width * Height * (Bpp / 8), KILOBYTE_PAGE), KILOBYTE_PAGE, WRITEABLE_PAGE | PRESENT_PAGE);

    LouKeRegisterFrameBufferDevice(
		(void*)0xFFFFFFFFFFFFFFFF,
		VMemFramebuffer,
        DrsdFrameWork->SecondaryFrameBuffer, 
        0x00,
        (Width * Height * (Bpp / 8)),
        Width, Height,
        Bpp, 
        RGB_DRSD_FRAMEBUFFER,
        SupportedModes,
        DrsdFrameWork
    );
	LouKeDrsdPciResetScreen((P_PCI_DEVICE_OBJECT)0xFFFFFFFFFFFFFFFF);
	StartDebugger();
}