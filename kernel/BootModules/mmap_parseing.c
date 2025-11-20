#include <LouAPI.h>
#include <bootloader/grub/multiboot2.h>

void SendMapToAllocation(struct master_multiboot_mmap_entry* mmap);

static uint64_t mlimit;

uint64_t GetRamSize() {
    return mlimit;
}



void ParseMemoryMap(struct multiboot_tag* MBOOT) {

    struct master_multiboot_mmap_entry* mmap = (struct master_multiboot_mmap_entry*)MBOOT;

    //parse version 0
    if (mmap->entry_version == 0) {
        SendMapToAllocation(mmap);
    }
}