#include <LouAPI.h>
#include <bootloader/grub/multiboot2.h>

void SendMapToAllocation(struct master_multiboot_mmap_entry* mmap);

static uint64_t mlimit;

KERNEL_EXPORT
uint64_t LouKeGetRamSize() {
    return mlimit;
}

void SetRamSize(UINT64 Size){
    mlimit = Size;
}

void ParseMemoryMap(struct multiboot_tag* MBOOT) {

    struct master_multiboot_mmap_entry* mmap = (struct master_multiboot_mmap_entry*)MBOOT;

    //parse version 0
    if (mmap->entry_version == 0) {
        SendMapToAllocation(mmap);
    }
}