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
#include <Hal.h>
#include <drivers/VBoxError.h>

static void ValidateOrSetPositionHints(
    PVIRTUALBOX_PRIVATE_DATA VBox
){
    PVBVA_MODE_HINT ModeHintI;
    PVBVA_MODE_HINT ModeHintJ;
    bool ValidData = true;
    uint16_t CurrentX = 0;

    for(size_t i = 0 ; i < VBox->CrtcCount; i++){
        for(size_t j = 0 ; j < i; j++){
            ModeHintI = &VBox->LastModeHints[i];
            ModeHintJ = &VBox->LastModeHints[j];

            if ((ModeHintI->Enabled) && (ModeHintJ->Enabled)) {
                if (
                    (ModeHintI->Dx >= 0xFFFF) || 
                    (ModeHintI->Dy >= 0xFFFF) ||
                    (ModeHintJ->Dx >= 0xFFFF) || 
                    (ModeHintJ->Dy >= 0xFFFF) || 
                    (ModeHintI->Dx < ((ModeHintJ->Dx + (ModeHintJ->Cx & 0x8FFF)) && 
                                    (ModeHintI->Dx + (ModeHintI->Cx & 0x8FFF) > ModeHintJ->Dx))) ||
                    (ModeHintI->Dy < ((ModeHintJ->Dy + (ModeHintJ->Cy & 0x8FFF)) && 
                                    (ModeHintI->Dy + (ModeHintI->Cy & 0x8FFF) > ModeHintJ->Dy)))
                ) {
                    ValidData = false;
                }
            }   
        }
    }
    if(!ValidData){
        for(size_t i = 0 ; i < VBox->CrtcCount; i++){
            if(VBox->LastModeHints[i].Enabled){
                VBox->LastModeHints[i].Dx = CurrentX;
                VBox->LastModeHints[i].Dy = 0;
                CurrentX += VBox->LastModeHints[i].Cx & 0x8FFFF;
            }
        }
    }
    LouPrint("ValidateOrSetPositionHints() STATUS_SUCCESS\n");
}

void VirtualboxUpdateModeHints(PVIRTUALBOX_PRIVATE_DATA VBox){
    PDRSD_DEVICE Device = &VBox->DrsdDevice;
    LOUSTATUS Status;
    PVIRTUALBOX_CONNECTOR Connector = (PVIRTUALBOX_CONNECTOR)Device->Connectors;
    bool Disconnected;
    uint16_t Flags;
    uint32_t CrtcID;
    PVBVA_MODE_HINT ModeHint;

    Status = HgsmiGetModeHints(
        VBox->GuestPool,
        VBox->CrtcCount,
        VBox->LastModeHints
    );
    if(Status != STATUS_SUCCESS){
        return;
    }

    ValidateOrSetPositionHints(VBox);

    MutexLock(&Device->ModeConfiguration.ConnectionMutex);

    while(Connector){
        LouPrint("Initializing Connector:%h Mode Hints\n", Connector);
        CrtcID = Connector->VBOXCrtc->CrtcId;
        ModeHint = &VBox->LastModeHints[CrtcID];

        if(ModeHint->Magic != VBVA_MODE_HINT_MAGIC){
            LouPrint("ERROR:VBOX_VIDEO: VirtualboxUpdateModeHints() Invalid Mode Hint\n");
            Connector = (PVIRTUALBOX_CONNECTOR)Connector->Base.Peers.NextHeader;
            continue;
        }

        Disconnected = ModeHint->Enabled ? 0 : 1;
        Connector->ModeHint.Width = ModeHint->Cx;
        Connector->ModeHint.Height = ModeHint->Cy;
        Connector->ModeHint.X = ModeHint->Dx;
        Connector->ModeHint.Y = ModeHint->Dy;
        Connector->ModeHint.Disconnected = Disconnected;

        if(Connector->VBOXCrtc->Disconnected == Disconnected){
            LouPrint("Initializing Connector:%h Mode Hints SUCCESS\n", Connector);
            Connector = (PVIRTUALBOX_CONNECTOR)Connector->Base.Peers.NextHeader;
            continue;
        }

        if(Disconnected){
            Flags = VBVA_SCREEN_F_ACTIVE | VBVA_SCREEN_F_DISABLED;
        }else {
            Flags = VBVA_SCREEN_F_ACTIVE | VBVA_SCREEN_F_BLANK;
        }

        LouPrint("VBOX_VIDEO:HERE\n");
        while(1);

        Connector->VBOXCrtc->Disconnected = Disconnected;

        LouPrint("Initializing Connector:%h Mode Hints SUCCESS\n", Connector);
        Connector = (PVIRTUALBOX_CONNECTOR)Connector->Base.Peers.NextHeader;
    }

    MutexUnlock(&Device->ModeConfiguration.ConnectionMutex);

}

void VirtualboxInterruptHandler(uint64_t VBoxPrivate){

    LouPrint("VirtualboxInterruptHandler()\n");
    while(1);
}

LOUSTATUS InitializeVirtualboxInterrupts(PVIRTUALBOX_PRIVATE_DATA VBox){
    P_PCI_DEVICE_OBJECT PDEV = VBox->PDEV;

    VirtualboxUpdateModeHints(VBox);


    RegisterInterruptHandler(VirtualboxInterruptHandler, LouKePciGetInterruptLine(PDEV), false, (uint64_t)VBox);

    LouPrint("InitializeVirtualboxInterrupts() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}