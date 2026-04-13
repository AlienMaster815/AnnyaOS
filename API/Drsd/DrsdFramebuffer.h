#ifndef _DRSD_FRAMEBUFFER_INTERNAL_H
#define _DRSD_FRAMEBUFFER_INTERNAL_H

#include "DrsdCore.h"

static inline void DrsdFrameBufferGet(PDRSD_FRAME_BUFFER Fb){
    DrsdModeObjectGet(&Fb->Base);
}

static inline void DrsdFrameBufferPut(PDRSD_FRAME_BUFFER Fb){
    DrsdModeObjectPut(&Fb->Base);
}

static inline void DrsdFramebufferAssign(PDRSD_FRAME_BUFFER* p, PDRSD_FRAME_BUFFER FrameBuffer){
    if(FrameBuffer){
        DrsdFrameBufferGet(FrameBuffer);
    }
    if(*p){
        DrsdFrameBufferPut(FrameBuffer);
    }
    *p = FrameBuffer;
}

#endif