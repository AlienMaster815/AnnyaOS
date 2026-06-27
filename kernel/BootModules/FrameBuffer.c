#include <LouAPI.h>

static SIZE gFramebuffers = 0;
static PLOADER_FB_MEMORY_MAP gFbMaps;

void InitializeFrameBuffer(
    PLOADER_FB_MEMORY_MAP   FbMaps,
    SIZE                    Framebuffers
){
    gFramebuffers = Framebuffers;
    gFbMaps = FbMaps;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeGetBootFrameBuffer(
	PLOADER_FB_MEMORY_MAP*  pBootGraphics,
    SIZE*                   FbCount 
){
	if(!pBootGraphics || !FbCount){
		return STATUS_INVALID_PARAMETER;
	}

	if(!gFbMaps || !gFramebuffers){
		return STATUS_NO_SUCH_DEVICE;
	}

	*pBootGraphics = gFbMaps;
    *FbCount = gFramebuffers;
	return STATUS_SUCCESS;
}
