#ifndef _CIRTUALBOX_GUEST_H
#define _CIRTUALBOX_GUEST_H

/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */


#include "VBoxVideo.h"

typedef struct _VBVA_BUFFER_CONTEXT{
    uint32_t        BufferOffset;
    uint32_t        BufferLength;
    bool            BufferOverflow;
    PVBVA_RECORD    Record;
    PVBVA_BUFFER    VbvaBuffer;
}VBVA_BUFFER_CONTEXT, * PVBVA_BUFFER_CONTEXT;

LOUSTATUS HgsmiReportFlagsLocation(POOL Context, uint32_t Location);
LOUSTATUS HgsmiSendCapabilityInfo(POOL Context, uint32_t Capabilities);
LOUSTATUS HgsmiTestQueryConfiguration(POOL Context);
LOUSTATUS HgsmiQueryConfiguration(POOL Context, uint32_t Index, uint32_t* Result);
LOUSTATUS HgsmiUpdatePointerShape(POOL Context, uint32_t Flags, uint32_t HotX, uint32_t HotY, uint32_t Width, uint32_t Height, uint8_t* Pixels, uint32_t Length);
LOUSTATUS HgsmiCursorPosition(POOL Context, bool ReportPosition, uint32_t X, uint32_t Y, uint32_t* Xhost, uint32_t YHost);
bool      VbvaEnable(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context, PVBVA_BUFFER  VbvaBuffer, int32_t Screen);
void      VbvaDisable(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context, int32_t Screen);
bool      VbvaBufferBeginUpdate(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context);
void      VbvaBufferEndUpdate(PVBVA_BUFFER_CONTEXT VbvaContext);
bool      VbvaWrite(PVBVA_BUFFER_CONTEXT BufferContext, POOL Context, void* Pixels, uint32_t Length);
void      VbvaSetupBufferContext(PVBVA_BUFFER_CONTEXT VbvaContext, uint32_t BudderOffset, uint32_t BufferLength);
void      HgsmiProccessDisplayInformation(POOL Context, uint32_t Display, int32_t OriginX, int32_t OriginY, uint32_t StartOffset, uint32_t Pitch, uint32_t Width, uint32_t Height, uint16_t Bpp, uint16_t Flags);
LOUSTATUS HgsmiUpdateInputMappings(POOL Context, int32_t OriginX, int32_t OriginY, uint32_t Width, uint32_t Height);
LOUSTATUS HgsmiGetModeHints(POOL Context, uint32_t Screens, PVBVA_MODE_HINT Hints);

#endif