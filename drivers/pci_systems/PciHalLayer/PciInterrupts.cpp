#include <LouDDK.h>
#include <Hal.h>

KERNEL_IMPORT uint16_t GetNPROC();
KERNEL_IMPORT uint8_t GetTotalHardwareInterrupts();

uint64_t* AdvancedInterruptRouterData;
int NumberOfInterruptHandlers = 0;
int HandlersPerCore = 0;



int GetSupportedMsiVectors(P_PCI_DEVICE_OBJECT PDEV,uint64_t Flags) {


    uint8_t CapabilitiesPtr = LouKeReadPciUint8(PDEV, 0x34); 

    if(Flags & PCI_IRQ_MSIX){
        while (CapabilitiesPtr != 0) {
            uint8_t CapId = LouKeReadPciUint8(PDEV, CapabilitiesPtr);  // Read Capability ID
            if (CapId == 0x11) {  // MSI-X Capability ID
                uint16_t MsixControl = LouKeReadPciUint16(PDEV, CapabilitiesPtr + 2);  // MSI-X Control register
                uint16_t table_size = (MsixControl & 0x07FF) + 1;  // Bits 10-0 hold the number of entries (table size)
                return table_size;  // Return number of MSI-X vectors supported
            }
            CapabilitiesPtr = LouKeReadPciUint8(PDEV, CapabilitiesPtr + 1);  // Next capability
        }
    }
    if(Flags & PCI_IRQ_MSIX){
        while (CapabilitiesPtr != 0) {
            uint8_t CapId = LouKeReadPciUint8(PDEV, CapabilitiesPtr); 
            if (CapId == 0x05) { 
                uint16_t MsiControl = LouKeReadPciUint16(PDEV, CapabilitiesPtr + 2); 
                uint8_t multiple_message_capable = (MsiControl >> 1) & 0x07;
                return (1 << multiple_message_capable); 
            }
            CapabilitiesPtr = LouKeReadPciUint8(PDEV, CapabilitiesPtr + 1);
        }
    }
    return 0;
}



LOUDDK_API_ENTRY
int LouKeHalMallocPciIrqVectors(
    P_PCI_DEVICE_OBJECT PDEV, 
    int RequestedVectors, 
    uint64_t Flags
){
    return 0;
}

LOUDDK_API_ENTRY 
LOUSTATUS LouKeMallocAdvancedKernelInterruptHandleing(){
    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY
void AdvancedInterruptRouter(uint64_t InterruptNumber, uint64_t Args){

}