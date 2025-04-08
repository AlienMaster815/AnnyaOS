#include <LouDDK.h>

LOUDDK_API_ENTRY
void LouKeNetFrameActivateNetworkDevice(PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER NetFrameDriver){
    if(!NetFrameDriver){
        return;
    }
    if(NetFrameDriver->HardwareActivate){
        NetFrameDriver->HardwareActivate(NetFrameDriver);
    }
}