#include <LouAPI.h>
#include <stdint.h>


// Read a byte from an I/O port
uint8_t inb(uint64_t port64) {
    uint8_t data;
    uint16_t port = (uint16_t)port64;

    __asm__ __volatile__("inb %w1, %b0"
                         : "=a"(data)
                         : "Nd"(port));
    return data;
}

// Write a byte to an I/O port
void outb(uint64_t port64, uint8_t data) {
    uint16_t port = (uint16_t)port64;

    __asm__ __volatile__("outb %b0, %w1"
                         :
                         : "a"(data), "Nd"(port));
}

// Read a word from an I/O port
uint16_t inw(uint64_t port64) {
    uint16_t data;
    uint16_t port = (uint16_t)port64;

    __asm__ __volatile__("inw %w1, %w0"
                         : "=a"(data)
                         : "Nd"(port));
    return data;
}

// Write a word to an I/O port
void outw(uint64_t port64, uint16_t data) {
    uint16_t port = (uint16_t)port64;
    __asm__ __volatile__("outw %w0, %w1"
                         :
                         : "a"(data), "Nd"(port));
}

// Read a double-word from an I/O port
uint32_t inl(uint64_t port64) {
    uint16_t port = (uint16_t)port64;
    uint32_t data;
    __asm__ __volatile__("inl %w1, %0"
                         : "=a"(data)
                         : "Nd"(port));
    return data;
}

// Write a double-word to an I/O port
void outl(uint64_t port64, uint32_t data) {
    uint16_t port = (uint16_t)port64;
    __asm__ __volatile__("outl %0, %w1"
                         :
                         : "a"(data), "Nd"(port));
}

// Slow write of a byte to an I/O port
void outbSlow(uint64_t port64, uint8_t data) {
    uint16_t port = (uint16_t)port64;
    __asm__ __volatile__("outb %b0, %w1\n\t"
                         "jmp 1f\n\t"
                         "1: jmp 1f\n\t"
                         "1:"
                         :
                         : "a"(data), "Nd"(port));
}

uint64_t read_msr(uint32_t msr_id) {
    uint32_t low, high;
    __asm__ __volatile__("rdmsr"
                         : "=a"(low), "=d"(high)
                         : "c"(msr_id));
    return ((uint64_t)high << 32) | low;
}

void write_msr(uint32_t msr, uint64_t value) {
    uint32_t low = (uint32_t)(value & 0xFFFFFFFF);
    uint32_t high = (uint32_t)(value >> 32);
    __asm__ __volatile__("wrmsr"
                         :
                         : "c"(msr), "a"(low), "d"(high));
}

void insw(uint16_t port, void *buf, unsigned long count) {
    __asm__ __volatile__("cld; rep; insw"
                         : "+D"(buf), "+c"(count)
                         : "d"(port)
                         : "memory");
}

void outsw(uint16_t port, const void *buf, unsigned long count) {
    __asm__ __volatile__("cld; rep; outsw"
                         : "+S"(buf), "+c"(count)
                         : "d"(port)
                         : "memory");
}

extern uint64_t LouKeMachineLevelReadRegisterUlong(uint64_t AddressOfRegister);
extern uint64_t LouKeMachineLevelWriteRegisterUlong(uint64_t AddressOfRegister,uint64_t Data);


unsigned long LouKeReadRegisterUlong(void* Register){
    unsigned long RESULT = 0;
    RESULT = (unsigned long)LouKeMachineLevelReadRegisterUlong((uint64_t)(uint8_t*)Register);
    return RESULT;
}

void LouKeWriteRegisterUlong(void* Register, unsigned long Data){
    LouKeMachineLevelWriteRegisterUlong((uint64_t)(uint8_t*)Register,(uint64_t)Data);
}