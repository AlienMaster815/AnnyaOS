#include <LouLoad.h>
#include <bootloader/grub/multiboot2.h>

void 
EnforceLoaderMemoryMap(
    UINT64  Address,
    UINT64  size
);

void 
InitializeLoaderMultibootInformation(
    struct multiboot_tag* MBoot
){
    UNUSED struct multiboot_tag* MBootStack = MBoot;
    
    while (MBoot->type != 0) {
        // Check if tag is memory map tag
    //    EnforceLoaderMemoryMap((uint64_t)MBoot, MBoot->size);
    //    switch (MBoot->type) {

        

    //    default:
    //        break;
    //    }

        if (MBoot->size % 8 == 0){
            MBoot = (struct multiboot_tag*)((uint8_t*)MBoot + MBoot->size);
        }
        else{
            MBoot = (struct multiboot_tag*)((uint8_t*)MBoot + ROUND_UP64(MBoot->size, 8));
        }
    }

    //MBoot = MBootStack;


    //MBoot = MBootStack;


    //MBoot = MBootStack;

}