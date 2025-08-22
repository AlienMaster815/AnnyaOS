ENTRY(start)
OUTPUT_FORMAT("elf64-x86-64")

SECTIONS
{

    . = 0x01000000;

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
    
    .data : { __ImageBase = .; *(.data) }

    /* .bss section for uninitialized data */
    .bss : {
        *(.bss)/* Your uninitialized data sections go here */
    }

    .JitlDirectory : {
        *(.JitlDirectory)
    }

    .Ahci : {
        *(.Data)
        *(.Code)
    }

    .User : 
    {
        *(.User)  /* User-mode stub code */
    }

}
