#ifndef _HGSMI_CH_SETUP_H
#define _HGSMI_CH_SETUP_H

/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */
/* Port Copyright (C) 2025-2026 Tyler Grenier */

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