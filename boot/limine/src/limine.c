#include "limine.h"
#include "cstdlib.h"
#include "loader.h"

LIMINE_REQUEST_START uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

LIMINE_REQUEST uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);

LIMINE_REQUEST_END uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

static LOADER_INFORMATION LoaderInformation = {0};

static void HaltAndCatchFile() {
    for (;;) {
        asm ("hlt");
    }
}

static volatile FORCE_ALIGNMENT(4096) UINT64 L3Tables[512] = {0};
static volatile FORCE_ALIGNMENT(4096) UINT64 L2Tables[512] = {0};


void kmain() {

    if(LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false){
        HaltAndCatchFile();
    }

    L3Tables[0] = (UINT64)LimineGetPhysicalAddress((PVOID)&L2Tables[0]) | 0b11;

    for(SIZE i = 0 ; i < 512; i++){
        L2Tables[i] = ((MEGABYTE_PAGE * i) | ((1 << 7) | 0b11));
    }

    UINT64* L4Tables = (UINT64*)LimineGetVirtualAddress(GetPageBase());

    L4Tables[0] = (UINT64)LimineGetPhysicalAddress((PVOID)&L3Tables[0]) | 0b11;

    LouKeReloadCR3();

    PLOADER_RAT_MBR_CHUNK RatMbr = LoaderSetUpRatMbr();
    if(!RatMbr){
        asm("INT $0");
    }
    LoaderInformation.RatMbr = RatMbr;

    BOOLEAN LockedAndLoaded = LoaderInitializeLoaderInformation(&LoaderInformation);
    
    if(!LockedAndLoaded){
        asm("INT $0");
    }

    HaltAndCatchFile();
}