#include "limine.h"
#include "cstdlib.h"

LIMINE_REQUEST_START uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

LIMINE_REQUEST uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);

LIMINE_REQUEST struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0,
};

LIMINE_REQUEST struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST_ID,
    .revision = 0,
};

LIMINE_REQUEST_END uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

static void HaltAndCatchFile() {
    for (;;) {
        asm ("hlt");
    }
}

void kmain() {

    if(LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false){
        HaltAndCatchFile();
    }

    if(
        (framebuffer_request.response == 0x00) ||
        (framebuffer_request.response->framebuffer_count < 1)
    ){
        HaltAndCatchFile();
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    volatile uint32_t *fb_ptr = framebuffer->address;
    for (size_t y = 0; y < framebuffer->height; y++) {
        for (size_t x = 0; x < framebuffer->width; x++) {
            uint32_t nX = x * 255 / framebuffer->width;
            uint32_t nY = y * 255 / framebuffer->height;
            fb_ptr[y * (framebuffer->pitch / 4) + x] = (nY << 8) | nX;
        }
    }

    HaltAndCatchFile();
}