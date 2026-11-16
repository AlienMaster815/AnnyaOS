#include "../UsbCore.h"

LOUSTATUS _UsbCoreDeviceRequestSetAddressStart(
    PUSB_TRANSFER_OBJECT*   OutObject,
    PUSB_DEVICE_OBJECT      UsbDevice,
    UINT8                   Address
){
    LOUSTATUS Status = UsbCoreAllocateUsbControlTransfer(
        OutObject,
        UsbDevice,
        &UsbDevice->DefaultControlPipe,
        USB_TRANSFER_FLAG_NO_DATA,
        0,
        0
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    PUSB_TRANSFER_OBJECT NewTransfer = *OutObject;
    UINT8* Setup = (UINT8*)NewTransfer->SetupData;
    
    //Request Type
    Setup[0] = 0x00;
    
    //Request
    Setup[1] = USB_DEVREQ_REQUEST_SET_ADDRESS; 
    
    //value
    Setup[2] = Address;
    Setup[3]  = 0x00;
    
    //index
    Setup[4]  = 0x00;
    Setup[5]  = 0x00;
    
    //length
    Setup[6]  = 0x00;
    Setup[7]  = 0x00;

    UsbCoreCommitUsbTransferToCommandEngine(NewTransfer, 2000);

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
UsbCoreDeviceRequestSetAddressStart(
    PUSB_TRANSFER_OBJECT*   OutObject,
    PUSB_DEVICE_OBJECT      UsbDevice,
    UINT8                   Address
){
    if((!OutObject) || (!UsbDevice) || (!Address)){
        return STATUS_INVALID_PARAMETER;
    }
    return _UsbCoreDeviceRequestSetAddressStart(OutObject, UsbDevice, Address);
}