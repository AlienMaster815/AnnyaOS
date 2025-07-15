#include <LouDDK.h>
#include <Hal.h>
#include <bootloader/grub/multiboot2.h>

KERNEL_IMPORT void StartDebugger();

static struct multiboot_tag_vbe VBE_INFO;

LOUDDK_API_ENTRY
void SetBootVbe(struct multiboot_tag_vbe VbeInfo){
	VBE_INFO = VbeInfo;
}


static struct multiboot_tag_framebuffer_common* BootGraphics = 0x00;

LOUDDK_API_ENTRY
void LouKeDeferBootGraphics(
	struct multiboot_tag_framebuffer_common* BootGraphicsDefer
){
	BootGraphics = BootGraphicsDefer;
}

LOUDDK_API_ENTRY 
LOUSTATUS
LouKeDrsdInitializeBootDevice(
    PDRSD_DEVICE Device
);

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
	Plane->FrameBuffer->SecondaryFrameBufferBase = (uintptr_t)LouKeMallocEx(ROUND_UP64(Width * Height * (Bpp / 8), MEGABYTE_PAGE), MEGABYTE_PAGE, KERNEL_GENERIC_MEMORY);
	LouKeMapContinuousMemoryBlock(BootGraphics->framebuffer_addr, Plane->FrameBuffer->FramebufferBase, ROUND_UP64(Width * Height * (Bpp / 8), MEGABYTE_PAGE), KERNEL_DMA_MEMORY);


	//while(1){
		//BUGBUG	
	//}

	DrsdInitializeGenericPlane(Device, Plane, 0, 0,0, 0, 0, PRIMARY_PLANE, "BOOTVID.SYS");

	LouKeDrsdInitializeBootDevice(
    	Device
	);

}