#include <kernel/ports.h>
#include <kernel/pic.h>
#include <kernel/interrupts.h>

#ifdef __i386__
LOUSTATUS InitializeStartupInterruptHandleing();
void SetInterruptFlags();
#endif

bool GetAPICStatus();

void PIC_sendEOI(unsigned char irq){
 
    if (!GetAPICStatus()) {
        outb(0x20, 0x20);

        if (irq >= 8)
            outb(0x20, 0xA0);

        PIC_remap(0x20, 0x28);
        Mask_All_Programable_Interrupts();
        IRQ_Pic_clear_mask(0);
        IRQ_Pic_clear_mask(1);
    }
}


void PIC_remap(int offset1, int offset2){
    if (!GetAPICStatus()) {
        unsigned char a1, a2;

        a1 = inb(PIC1_DATA);                        // save masks
        a2 = inb(PIC2_DATA);

        outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
        outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
        outb(PIC1_DATA, offset1);                   // ICW2: Master PIC vector offset
        outb(PIC2_DATA, offset2);                   // ICW2: Slave PIC vector offset
        outb(PIC1_DATA, 4);                         // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
        outb(PIC2_DATA, 2);                         // ICW3: tell Slave PIC its cascade identity (0000 0010)

        outb(PIC1_DATA, ICW4_8086);                 // ICW4: have the PICs use 8086 mode (and not 8080 mode)
        outb(PIC2_DATA, ICW4_8086);

        outb(PIC1_DATA, a1);   // restore saved masks.
        outb(PIC2_DATA, a2);
    }
}

void IRQ_Pic_set_mask(unsigned char IRQline) {
    if(!GetAPICStatus()) {
        uint16_t port;
        uint8_t value;

        if (IRQline < 8) {
            port = PIC1_DATA;
        }
        else {
            port = PIC2_DATA;
            IRQline -= 8;
        }
        value = inb(port) | (1 << IRQline);
        outb(port, value);
    }
}
 
void IRQ_Pic_clear_mask(unsigned char IRQline) {
    if (!GetAPICStatus()) {
        uint16_t port;
        uint8_t value;

        if (IRQline < 8) {
            port = PIC1_DATA;
        }
        else {
            port = PIC2_DATA;
            IRQline -= 8;
        }
        value = inb(port) & ~(1 << IRQline);
        outb(port, value);
    }
}

/* Helper func */
static uint16_t __pic_get_irq_reg(int ocw3){
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_CMD, ocw3);
    outb(PIC2_CMD, ocw3);
    return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr(void){
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr(void){
    return __pic_get_irq_reg(PIC_READ_ISR);
}

void Mask_All_Programable_Interrupts(){
    if (!GetAPICStatus()) {
        for (uint8_t i = 0; i < 16; i++)
            IRQ_Pic_set_mask(i);
    }
}


// Function to disable the PIC
void disable_pic() {

    PIC_remap(0x40, 0x40 + 0x08);

    // Mask all interrupts on both PICs
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

}