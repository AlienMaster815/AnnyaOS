/*
 * This is a clean-room reimplementation of the VirtualBox VBE/VMSVGA driver,
 * originally developed by Oracle Corporation and released under the MIT license.
 *
 * This implementation is based on independent research and observation of the
 * Linux kernel's `vboxvideo` driver and related specifications. No code was
 * directly copied or translated.
 *
 * All identifiers, register names, and behavior are derived from public
 * documentation or reverse-engineered from hardware behavior.
 *
 * Copyright (C) 2025 Tyler Grenier
 * Licensed under the GNU GPLv2
 */
 #define _KERNEL_MODULE_
 #include <LouDDK.h>
 #include "VirtualboxDriver.h"


UNUSED static uint32_t VbvaBufferAvailable(PVBVA_BUFFER Vbva){


    return 0;
}

UNUSED static void VbvaBufferPlaceDataAt(PVBVA_BUFFER_CONTEXT VbvaContext, void* Pointer, uint32_t Length, uint32_t Offset){

}

UNUSED static void VbvaBufferFlush(POOL* Context){

}

UNUSED static bool VbvaInformHost(PVBVA_BUFFER_CONTEXT VbvaContext, POOL* Context, int32_t Screen, bool Enable){

    return false;
}

bool VbvaEnable(PVBVA_BUFFER_CONTEXT VbvaContext, POOL* Context, PVBVA_BUFFER  VbvaBuffer, int32_t Screen){

    return false;
}

void VbvaDisable(PVBVA_BUFFER_CONTEXT VbvaContext, POOL* Context, int32_t Screen){

}

bool VbvaBufferBeginUpdate(PVBVA_BUFFER_CONTEXT VbvaContext, POOL* Context){

    return false;
}

void VbvaBufferEndUpdate(PVBVA_BUFFER_CONTEXT VbvaContext){

}

bool VbvaWrite(PVBVA_BUFFER_CONTEXT BufferContext, POOL* Context, void* Pixels, uint32_t Length){

    return false;
}

void VbvaSetupBufferContext(PVBVA_BUFFER_CONTEXT VbvaContext, uint32_t BudderOffset, uint32_t BufferLength){


}
