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
	UNUSED uint16_t Width = BootGraphics->framebuffer_width;
	UNUSED uint16_t Height = BootGraphics->framebuffer_height;
	UNUSED uint16_t Bpp = BootGraphics->framebuffer_bpp;
	
	PDRSD_DEVICE Device = LouKeMallocType(DRSD_DEVICE, KERNEL_GENERIC_MEMORY);
	PDRSD_PLANE Plane = LouKeMallocType(DRSD_PLANE, KERNEL_GENERIC_MEMORY);
	Plane->PlaneState = LouKeMallocType(DRSD_PLANE_STATE, KERNEL_GENERIC_MEMORY);
	Plane->FrameBuffer = LouKeMallocType(DRSD_FRAME_BUFFER, KERNEL_GENERIC_MEMORY);
	Plane->PlaneState->SourceX = 0;
	Plane->PlaneState->SourceY = 0;
	Plane->PlaneState->Width = Width;
	Plane->PlaneState->Height = Height;
	Plane->PlaneState->FormatUsed = DRSD_COLOR_FORMAT_XRGB8888;
	Plane->FrameBuffer->Height = Height;
	Plane->FrameBuffer->Width = Width;
	Plane->FrameBuffer->Bpp = Bpp;
	Plane->FrameBuffer->Pitch = (Width * (Bpp / 8));;
	Plane->FrameBuffer->FramebufferSize = Width * Height * (Bpp / 8);
	Plane->FrameBuffer->FramebufferBase = (uintptr_t)LouVMallocEx(ROUND_UP64(Width * Height * (Bpp / 8), MEGABYTE_PAGE), MEGABYTE_PAGE);
	LouKeMapContinuousMemoryBlock(BootGraphics->framebuffer_addr, Plane->FrameBuffer->FramebufferBase, ROUND_UP64(Width * Height * (Bpp / 8), MEGABYTE_PAGE), KERNEL_DMA_MEMORY);

	DrsdInitializeGenericPlane(Device, Plane, 0, 0,0, 0, 0, PRIMARY_PLANE, "BOOTVID.SYS");

	LouKeDrsdClearScreen(Plane);

	//LouKeDrsdClearScreen

	LouPrint("Hello World\n");

	while(1);
}