#include <LouDDK.h>
#include <NtAPI.h>


uint8_t LouKeGetPciInterruptPin(P_PCI_DEVICE_OBJECT PDEV){

    uint8_t PIN = LouKeReadPciUint8(PDEV, 0x3D);
    return PIN;
}

uint8_t LouKeGetPciInterruptLine(P_PCI_DEVICE_OBJECT PDEV){

    uint8_t LINE = LouKeReadPciUint8(PDEV, 0x3C);
    return LINE;
}

void ioapic_configure_irq(
    uint8_t irq, 
    uint8_t vector, 
    uint8_t apic_id, 
    uint8_t delivery_mode, 
    uint8_t dest_mode, 
    uint8_t polarity, 
    uint8_t trigger_mode
);

KERNEL_IMPORT void ioapic_unmask_irq(uint8_t irq);
KERNEL_IMPORT void PIC_remap(int offset1, int offset2);

LOUDDK_API_ENTRY void LouKeHalPciEnableInterrupts(P_PCI_DEVICE_OBJECT PDEV);

KERNEL_IMPORT void IRQ_Pic_clear_mask(unsigned char IRQline);
KERNEL_IMPORT void Mask_All_Programable_Interrupts();

KERNEL_IMPORT uint8_t LouKeGetPciGsi(P_PCI_DEVICE_OBJECT PDEV);

LOUDDK_API_ENTRY
uint8_t LouKeHalPciAllocateInterrupt(
    P_PCI_DEVICE_OBJECT PDEV, 
    void(*Handler)(uint64_t), 
    bool NeedFlotationSave, 
    uintptr_t OverideData,
    uint64_t Flags
){
    if(Flags){
        //TODO: Set flags for MSI/MSIX
        

    }

    uint8_t INTxInterrupt = 0;//LouKeGetPciGsi(PDEV);

    LouPrint("PCI INTx Interrupt Is:%d\n", INTxInterrupt);

    while(1);
    //no flags uses intx
    RegisterInterruptHandler(Handler, 0x30 + PDEV->InterruptLine, false, (uint64_t)OverideData);
    InitializeIoApicIRQ(
        PDEV->InterruptLine,         
        0x30 + PDEV->InterruptLine,      
        0,        
        0,         
        1,         
        1,         
        0          
    );
    return PDEV->InterruptLine;
}