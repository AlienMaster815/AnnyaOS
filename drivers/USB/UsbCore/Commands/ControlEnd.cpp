#include "../UsbCore.h"

LOUSTATUS _UsbCoreDeviceRequestSetAddressEnd(
    PUSB_TRANSFER_OBJECT    TransferObject
){
    PUSB_HCD_OBJECT HcdObject = TransferObject->UsbDevice->Hcd;
    LOUSTATUS Status = UsbCoreFenceTransferObject(TransferObject);
    if(Status != STATUS_SUCCESS){        
        UsbCoreFreeUsbControlTransfer(TransferObject);
        return Status;
    }
    Status = HcdObject->Operations->GetTransferStatus(TransferObject);
    UsbCoreFreeUsbControlTransfer(TransferObject);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS 
UsbCoreDeviceRequestSetAddressEnd(
    PUSB_TRANSFER_OBJECT    TransferObject
){
    if(!TransferObject){
        return STATUS_INVALID_PARAMETER;
    }
    return _UsbCoreDeviceRequestSetAddressEnd(TransferObject);
}