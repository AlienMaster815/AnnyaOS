#include <LouAPI.h>
#include <bootloader/grub/multiboot2.h>

struct multiboot_tag_framebuffer* FramebufferInformation;

void DRSD_OVERIDE_EGA();
void LouKeDeferBootGraphics(
	struct multiboot_tag_framebuffer_common* BootGraphicsDefer
);

void InitializeFrameBuffer(
    struct multiboot_tag_framebuffer* Frambuffer
){
    //LouPrint("Parseing Framebuffer\n");
    FramebufferInformation = Frambuffer;

    struct multiboot_tag_framebuffer_common* Common = &FramebufferInformation->common;

    if(Common->framebuffer_type == 2){
        DRSD_OVERIDE_EGA();        
    }

    if(Common->framebuffer_type == 1){
        LouKeDeferBootGraphics(Common);
    }

}