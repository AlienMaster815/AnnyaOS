#ifndef _VIRTUALBOX_VBE_H
#define _VIRTUALBOX_VBE_H

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

//guest host communication

#define VIRTUALBOX_VBE_DISPI_BANK_ADDRESS           0xA0000
#define VIRTUALBOX_VBE_DISPI_BANK_SIZE              64
#define VIRTUALBOX_VBE_DISPI_MAX_XRESOLUTION        16384
#define VIRTUALBOX_VBE_DISPI_MAX_YRESOLUTION        16384
#define VIRTUALBOX_VBE_DISPI_MAX_BITS_PER_PIXEL     32
#define VIRTUALBOX_VBE_DISPI_IO_INDEX_PORT          0x01CE
#define VIRTUALBOX_VBE_DISPI_IO_DATA_PORT           0x01CF
#define VIRTUALBOX_VBE_DISPI_DAC_WRITE_INDEX_PORT   0x03C8
#define VIRTUALBOX_VBE_DISPI_DAC_IO_DATA_PORT       0x03C9
#define VIRTUALBOX_VBE_DISPI_INDEX_ID               0
#define VIRTUALBOX_VBE_DISPI_INDEX_XRESOLUTION      1
#define VIRTUALBOX_VBE_DISPI_INDEX_YRESOLUTION      2
#define VIRTUALBOX_VBE_DISPI_INDEX_BPP              3
#define VIRTUALBOX_VBE_DISPI_INDEX_ENABLE           4
#define VIRTUALBOX_VBE_DISPI_INDEX_BANK             5
#define VIRTUALBOX_VBE_DISPI_INDEX_VIRTUAL_WIDTH    6
#define VIRTUALBOX_VBE_DISPI_INDEX_VIRTUAL_HEIGHT   7
#define VIRTUALBOX_VBE_DISPI_INDEX_X_OFFSET         8
#define VIRTUALBOX_VBE_DISPI_INDEX_Y_OFFSET         9
#define VIRTUALBOX_VBE_DISPI_INDEX_VBOX_VIDEO       10
#define VIRTUALBOX_VBE_DISPI_INDEX_FB_BASE_HI       11
#define VIRTUALBOX_VBE_DISPI_ID0                    0xB0C0
#define VIRTUALBOX_VBE_DISPI_ID1                    0xB0C1
#define VIRTUALBOX_VBE_DISPI_ID2                    0xB0C2
#define VIRTUALBOX_VBE_DISPI_ID3                    0xB0C3
#define VIRTUALBOX_VBE_DISPI_ID4                    0xB0C4
#define VIRTUALBOX_VBE_DISPI_ID_VBOX_VIDEO          0xBE00
#define VIRTUALBOX_VBE_DISPI_ID_HGSMI               0xBE01
#define VIRTUALBOX_VBE_DISPI_ID_ANYX                0xBE02
#define VIRTUALBOX_VBE_DISPI_DISABLED               0
#define VIRTUALBOX_VBE_DISPI_ENABLED                1
#define VIRTUALBOX_VBE_DISPI_GET_CAPS               2
#define VIRTUALBOX_VBE_DISPI_8BIT_DAC               0x20
#define VIRTUALBOX_VGA_HGSMI_HOST                   0x03B0
#define VIRTUALBOX_VGA_HGSMI_GUEST                  0x03D0

#endif