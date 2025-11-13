ENTRY(LouLoaderSetup)
OUTPUT_FORMAT("elf64-x86-64")

SECTIONS
{

    . = 0x200000;

    .boot :
    {
        KEEP(*(.multiboot_header))
        *(.boot)
        *(.bootdata)
    }
    .text :
    {
        *(.text)
    }
     .data : {
        *(.data)/* Your initialized data sections go here */
    }
    
    /* .bss section for uninitialized data */
    .bss : {
        *(.bss)/* Your uninitialized data sections go here */
    }
}
