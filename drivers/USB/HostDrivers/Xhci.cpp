#include "Xhci.h"

LOUSTATUS XhciResetHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("XHCI.SYS:XhciResetHcdDevice()\n");
    while(1);
    LouPrint("XHCI.SYS:XhciResetHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStartHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("XHCI.SYS:XhciStartHcdDevice()\n");
    while(1);
    LouPrint("XHCI.SYS:XhciStartHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStopHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("XHCI.SYS:XhciStopHcdDevice()\n");
    while(1);
    LouPrint("XHCI.SYS:XhciStopHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS XhciHcdCreateEndpoint(PUSB_HCD_OBJECT Hcd, PUSB_ENDPOINT_OBJECT NewEndpoint){
    LouPrint("XHCI.SYS:XhciHcdCreateEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciHcdDestroyEndpoint(PUSB_ENDPOINT_OBJECT Endpoint){
    LouPrint("XHCI.SYS:XhciHcdDestroyEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

RHPORT_STATUS XhciGetHcdRhPortStatus(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("XHCI.SYS:XhciGetHcdRhPortStatus()\n");
    while(1);
    return RHPORT_STATUS_NEEDS_RESET;
}

LOUSTATUS XhciResetRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("XHCI.SYS:XhciResetRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStartRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("XHCI.SYS:XhciStartRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStopRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("XHCI.SYS:XhciStopRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciPrepTransfer(PUSB_TRANSFER_DATA Transfer){
    LouPrint("XHCI.SYS:XhciPrepTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciCommitTransfer(PUSB_TRANSFER_DATA Transfer){
    LouPrint("XHCI.SYS:XhciCommitTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}
