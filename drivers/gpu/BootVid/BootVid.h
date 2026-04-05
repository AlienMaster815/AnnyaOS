//Copyright GPL-2 Tyler Grenier (2026)
#ifndef _BOOTVID_H
#define _BOOTVID_H

#define _KERNEL_MODULE_

#include <LouDDK.h>
#include <bootloader/grub/multiboot2.h>
#include "Ttf/OpenType.h"
#include "Ttf/TtfCmap.h"
#include "Ttf/TtfGlyph.h"
#include "Ttf/TtfHead.h"
#include "Ttf/TtfLoca.h"

typedef struct _BOOTVID_FRAMEBUFFER{
    ListHeader  Head;
    BOOLEAN     DrsdDevice;
    SIZE        FramebufferSize;
    UINT8*      RawData;
    UINT16      Width;
    UINT16      Height;
    UINT16      Pitch;
    UINT8       Bpp;
}BOOTVID_FRAMEBUFFER, * PBOOTVID_FRAMEBUFFER;

#define BLUE_MASK       (0xFF)
#define GREEN_MASK      (0xFF << 8)
#define RED_MASK        (0xFF << 16)
#define UNUSED_MASK     (0xFF << 24)

#define SET_RED(r)      ((r & 0xFF) << 16)
#define SET_GREEN(g)    ((g & 0xFF) << 8)
#define SET_BLUE(b)     ((b & 0xFF))

#define SET_RGB(r, g, b) (SET_RED(r) | SET_GREEN(g) | SET_BLUE(b))

KERNEL_EXPORT 
LOUSTATUS 
LouKeGetBootFrameBuffer(
	struct multiboot_tag_framebuffer_common** pBootGraphics
);

LOUSTATUS BootVidRegisterBootFrameBuffer(PBOOTVID_FRAMEBUFFER FrameBuffer);

void BootRenderPutPixelEx(INT32 x, INT32 y, UINT32 Rgb);
void BootRenderPutPixel(INT32 x, INT32 y, UINT8 R, UINT8 G, UINT8 B);
void BootRenderSyncScreen();

#endif