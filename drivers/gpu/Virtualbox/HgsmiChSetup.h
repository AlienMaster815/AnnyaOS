#ifndef _HGSMI_CH_SETUP_H
#define _HGSMI_CH_SETUP_H

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

#define HGSMI_CC_HOST_FLAGS_LOCATION 		0
#define HGSMIHOSTFLAGS_COMMANDS_PENDING    	0x01u
#define HGSMIHOSTFLAGS_IRQ                 	0x02u
#define HGSMIHOSTFLAGS_VSYNC               	0x10u
#define HGSMIHOSTFLAGS_HOTPLUG             	0x20u
#define HGSMIHOSTFLAGS_CURSOR_CAPABILITIES 	0x40u

typedef struct PACKED _HGSMI_BUFFER_LOCATION {
	uint32_t BufferLocation;
	uint32_t BufferLength;
} HGSMI_BUFFER_LOCATION, * PHGSMI_BUFFER_LOCATION;

typedef struct PACKED _HGSMI_HOST_FLAGS {
	uint32_t    HostFlags;
	uint32_t    Reserved[3];
}HGSMI_HOST_FLAGS, * PHGSMI_HOST_FLAGS;

#endif