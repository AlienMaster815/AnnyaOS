#ifndef _HGSMI_CHANNELS_H
#define _HGSMI_CHANNELS_H

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

#define HGSMI_CH_RESERVED       0
#define HGSMI_CH_HGSMI          1
#define HGSMI_CH_VBVA           2
#define HGSMI_CH_SEAMLESS       3
#define HGSMI_CH_SEAMLESS2      4
#define HGSMI_CH_OPENGL         5

#define HGSMI_CH_STRING_FIRST   0x20
#define HGMSI_CH_STRING_LAST    0xFF

#endif