#include "UsbCore.h"

LOUSTATUS UsbCoreCreateDefaultInEndpoint(PUSB_PIPE_OBJECT Pipe);
LOUSTATUS UsbCoreCreateDefaultOutEndpoint(PUSB_PIPE_OBJECT Pipe);

LOUSTATUS UsbCoreCreateDefaultPipe(PUSB_DEVICE_OBJECT UsbDevice){
    LOUSTATUS Status;
    Status = UsbCoreCreateDefaultInEndpoint(&UsbDevice->DefaultControlPipe);    
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return UsbCoreCreateDefaultOutEndpoint(&UsbDevice->DefaultControlPipe);    
}