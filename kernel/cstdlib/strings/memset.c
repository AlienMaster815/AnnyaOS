#include <kernel/memmory.h>


KERNEL_EXPORT void* memset(void* dest, int value, size_t count) {
    if (count == 0) return dest;

    unsigned char val = (unsigned char)value;
    void* temp_dest = dest;
    __asm__ volatile (
        "cld\n\t"
        "rep stosb"
        : "+D"(temp_dest), "+c"(count)
        : "a"(val)
        : "memory"
    );
    return dest;
}
