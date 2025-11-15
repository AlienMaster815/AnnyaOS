ENTRY(LouLoaderSetup)
OUTPUT_FORMAT("elf64-x86-64")

PHDRS {
    text   PT_LOAD FLAGS(RX);
    data   PT_LOAD FLAGS(RW);
}

SECTIONS
{
    . = 0x200000;

    .boot : {
        KEEP(*(.multiboot_header))
        *(.boot*)
    } :text

    .text : {
        *(.text*)
    } :text

    .rodata : {
        *(.rodata*)
    } :text

    .data : {
        *(.data*)
    } :data

    .bss : {
        *(.bss*)
        *(COMMON)
    } :data

}
