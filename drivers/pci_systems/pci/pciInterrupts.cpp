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

#define IOAPIC_DELIVERY_MODE_FIXED    0x0
#define IOAPIC_DEST_MODE_PHYSICAL     0x0
#define IOAPIC_POLARITY_ACTIVE_LOW    0x1
#define IOAPIC_TRIGGER_MODE_LEVEL     0x1

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
LOUDDK_API_ENTRY
uint8_t LouKeHalPciAllocateInterrupt(
    P_PCI_DEVICE_OBJECT PDEV, 
    void(*Handler)(uint64_t), 
    bool NeedFlotationSave, 
    uintptr_t OverideData,
    uint8_t UsingInterrupt,
    uint64_t Flags
){
    if(Flags){
        //TODO: Set flags for MSI/MSIX
        

    }
    //no flags uses intx    
    //ioapic_configure_irq(
    //    PDEV->InterruptLine,                       
    //    UsingInterrupt,
    //    0,
    //    IOAPIC_DELIVERY_MODE_FIXED,
    //    IOAPIC_DEST_MODE_PHYSICAL,
    //    IOAPIC_POLARITY_ACTIVE_LOW,
    //    IOAPIC_TRIGGER_MODE_LEVEL
    //);
    LouKeHalPciEnableInterrupts(PDEV);
    ioapic_unmask_irq(PDEV->InterruptLine);
    //_INTERRUPT_ALLOCATED:
    //RegisterInterruptHandler(Handler, UsingInterrupt, false, (uint64_t)OverideData);
    return UsingInterrupt;
}