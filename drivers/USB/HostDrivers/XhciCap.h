/* SPDX-License-Identifier: GPL-2.0 */

/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

#define _KERNEL_MODULE_
#ifndef _XHCI_CAPABILITIES_H
#define _XHCI_CAPABILITIES_H

#define XHCI_HC_VERSION(Port)                   (((Port) >> 16) & 0xFFFF)
#define XHCI_HCS_SLOTS(Port)                    ((Port) & 0xFF)
#define XHCI_HCS_MAX_SLOTS                      0xFF
#define XHCI_HCS_MAX_INTERRUPTERS(Port)         (((Port) >> 8) & 0x07FF)
#define XHCI_HCS_MAX_PORTS(Port)                (((Port) >> 24) & 0x7F)
#define XHCI_HCS_IST(Port)                      ((Port) & 0x0F)
#define XHCI_ERST_MAX(Port)                     (((Port) >> 4) & 0x0F)
#define XHCI_MAX_SCRATCHPAD(Port)               ((((Port) >> 16) & 0x03E0) | (((Port) >> 27) & 0x1F))

#define XHCI_HCS_U1_LATENCY(Port)               ((Port) & 0xFF)
#define XHCI_HCS_U2_LATENCY(Port)               (((Port) >> 16) & 0xFFFF)

#define XHCI_HCC_64_BIT_SUPPORT(Port)           ((Port) & (1))
#define XHCI_HCC_BANDWIDTH_NEGOTIATION(Port)    ((Port) & (1 << 1))
#define XHCI_HCC_64_BYTE_CONTEXT(Port)          ((Port) & (1 << 2))
#define XHCI_HCC_PORT_POWER_SWITCHES(Port)      ((Port) & (1 << 3))
#define XHCI_HCS_INDICATOR(Port)                ((Port) & (1 << 4))
#define XHCI_HCC_LIGHT_RESET(Port)              ((Port) & (1 << 5))
#define XHCI_HCC_LATENCY_TOLERENCE(Port)        ((Port) & (1 << 6))
#define XHCI_HCC_NO_SECONDARY_STEAM_ID(Port)    ((Port) & (1 << 7))
#define XHCI_HCC_STOPED_SHORT_PCACKET(Port)     ((Port) & (1 << 9))
#define XHCI_HCC_CONTIGUOUS_FRAME_ID(Port)      ((Port) & (1 << 11))
#define XHCI_HCC_PRIMART_STREAM_ARRAYS(Port)    (1 << ((((Port) >> 12) & 0x0F) + 1))

#define XHCI_CONTEXT_SIZE(Hcc)                  (XHCI_HCC_64_BYTE_CONTEXT(Hcc) ? 64 : 32)
#define XHCI_DBOFF_MASK                         (0xFFFFFFFC)
#define XHCI_RTSOFF_MASK                        (-0x1F)

#define XHCI_HCC_U3C(Port)                      ((Port) & (1)) 
#define XHCI_HCC_CMC(Port)                      ((Port) & (1 << 1)) 
#define XHCI_HCC_FSC(Port)                      ((Port) & (1 << 2)) 
#define XHCI_HCC_CTC(Port)                      ((Port) & (1 << 3)) 
#define XHCI_HCC_LEC(Port)                      ((Port) & (1 << 4)) 
#define XHCI_HCC_CIC(Port)                      ((Port) & (1 << 5)) 
#define XHCI_HCC_ETC(Port)                      ((Port) & (1 << 6)) 
#define XHCI_HCC_ETC_TSC(Port)                  ((Port) & (1 << 7)) 
#define XHCI_HCC_GSC(Port)                      ((Port) & (1 << 8)) 
#define XHCI_HCC_VTC(Port)                      ((Port) & (1 << 9)) 

#endif