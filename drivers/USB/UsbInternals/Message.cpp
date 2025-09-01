#include <LouDDK.h>
#include <Hal.h>
#include <usb.h>
#include "Hcd.h"

void LouKeUsbEnableEnpoint(
    PUSB_DEVICE                 UsbDevice,
    PUSB_HOST_ENDPOINT          Ep,
    BOOL                        ResetEp
){
    UNUSED INTEGER EpNumber = LouKeUsbGetEndpointNumber(&Ep->EndpointDescriptor);
    UNUSED INTEGER Out = LouKeUsbEndpointDirOut(&Ep->EndpointDescriptor);
    UNUSED INTEGER Xfer = LouKeUsbEndpointXferControl(&Ep->EndpointDescriptor);

    if(ResetEp){
        LouKeUsbHcdResetEndpoint(UsbDevice, Ep);
    } 

    if((Out) || (Xfer)){
        UsbDevice->OutputEndpoint[EpNumber] = Ep;
    }
    if((!Out) || (Xfer)){
        UsbDevice->InputEndpoint[EpNumber] = Ep;
    }
    Ep->Enabled = 1;
}