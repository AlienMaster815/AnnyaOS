//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <LouDDK.h>
#include <Hal.h>
#include <bootloader/grub/multiboot2.h>

LOUAPI void StartDebugger();

static struct multiboot_tag_vbe VBE_INFO;

LOUAPI
void SetBootVbe(struct multiboot_tag_vbe VbeInfo){
	VBE_INFO = VbeInfo;
}


static struct multiboot_tag_framebuffer_common* BootGraphics = 0x00;

LOUAPI
void LouKeDeferBootGraphics(
	struct multiboot_tag_framebuffer_common* BootGraphicsDefer
){
	BootGraphics = BootGraphicsDefer;
}

LOUAPI 
LOUSTATUS
LouKeDrsdInitializeBootDevice(
    PDRSD_DEVICE Device
);

KERNEL_EXPORT 
LOUSTATUS 
LouKeGetBootFrameBuffer(
	struct multiboot_tag_framebuffer_common** pBootGraphics
){
	if(!pBootGraphics){
		return STATUS_INVALID_PARAMETER;
	}

	if(!BootGraphics){
		return STATUS_NO_SUCH_DEVICE;
	}

	*pBootGraphics = BootGraphics;

	return STATUS_SUCCESS;
}
