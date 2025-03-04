//#include <drivers/display/vga.h>
#include <LouAPI.h>
#include <bootloader/grub/multiboot2.h>

#define VGA_RGB_FRAMEBUFFER 0xFF



extern struct multiboot_tag_vbe VBE_INFO;
CharMapping* GetCharecterMap(char Charecter);

volatile PWINDHANDLE 
GetWindowHandleByNumber(
    uint16_t HandleNumber
);

uint16_t GetAmmountOfOpenWindows();

static Char* VgaBuffer = (Char*)0xb8000;

static uint8_t color;



void clear_row(size_t row) {
    Char empty;
    empty.character = ' ';
    empty.color = color;

    for (size_t col = 0; col < NUM_COLS; col++) {
        VgaBuffer[col + NUM_COLS * row] = empty;
    }
}


void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

bool LouUpdateTextWindow(volatile PWINDHANDLE WindowHandle, TEXT_WINDOW_EVENT Update);


bool DrawWindow(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    volatile PWINDHANDLE WindHandle
);

void VgaPutCharecterRgb(char Character, volatile PWINDHANDLE Handle, uint8_t r, uint8_t g, uint8_t b) {
    static uint16_t xz, yz;

    if(Handle->Cursor.y > (Handle->Charecteristics.Dimentions.height + 64)){
            
        LouUpdateTextWindow(Handle, TEXT_WINDOW_RESIZE);
        
    }

    if (Character == '\n') {
        Handle->Cursor.x = 0;
        if ((Handle->Cursor.y + 64) > Handle->Charecteristics.Dimentions.height) {
                LouUpdateTextWindow(Handle, TEXT_WINDOW_BUFFER_OVERFLOW);
            }else{
            Handle->Cursor.y += 17;
        }
        return;
    } else if (Character == ' ') {
        Handle->Cursor.x += 8;
        return;
    }

    CharMapping* Map = GetCharecterMap(Character);

    if (Map == 0x00) {
        return;
    }

    if ((Handle->Cursor.x + Map->width + 17) > Handle->Charecteristics.Dimentions.width) {
        VgaPutCharecterRgb('\n', Handle , 0, 0, 0);
    }
    static uint16_t x;
    static uint16_t y;

    x = Handle->Charecteristics.Dimentions.x + Handle->Cursor.x;
    y = Handle->Charecteristics.Dimentions.y + Handle->Cursor.y;

    for (yz = 0; yz < 16; yz++) {
        wchar_t Ybyte = Map->pixels[yz];
        for (xz = 0; xz < 16; xz++) {
            if ((Ybyte >> (15 - xz)) & 0x01) {
                if(Handle->InnerWindowData){
                    for(uint8_t i = 0; i < GetAmmountOfOpenWindows();i++){
                        volatile PWINDHANDLE TempHandle = GetWindowHandleByNumber(i);
                        if(Handle == TempHandle){
                            uint8_t* PIXEL_DATA = (uint8_t*)&Handle->InnerWindowData[(Handle->Cursor.x + xz) + GetScreenBufferWidth() * (Handle->Cursor.y + yz)];
                            PIXEL_DATA[0] = b;
                            PIXEL_DATA[1] = g;
                            PIXEL_DATA[2] = r;
                        
                        }
                    }
                }

                LouKeDrsdPutPixelMirrored(x + xz, y + yz, r, g, b);
            }
        }
    }

    Handle->Cursor.x += Map->width;
}

//static spinlock_t VgaPutCharecterRgbButtonsLock;

static spinlock_t PrintStringToWindowLock;

void PrintStringToWindow(
    string Str, 
    volatile PWINDHANDLE Handle, 
    uint8_t r , 
    uint8_t g, 
    uint8_t b
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PrintStringToWindowLock, &Irql);
    for(size_t i = 0 ; i < strlen(Str); i++){
        VgaPutCharecterRgb(Str[i], Handle, r,g,b);
    }
    LouKeReleaseSpinLock(&PrintStringToWindowLock, &Irql);
}




void* GetFrameBufferAddress(
    PDrsdVRamObject FBDEV,
    uint16_t x, uint16_t y
){

    // Calculate the offset in the framebuffer
    uint32_t bytes_per_pixel = FBDEV->FrameBuffer.Bpp / 8;
    uint8_t* framebuffer;
    if(FBDEV->FrameBuffer.SecondaryFrameBufferBase){
        framebuffer = (uint8_t*)(uintptr_t)FBDEV->FrameBuffer.SecondaryFrameBufferBase;
    }else{
        framebuffer = (uint8_t*)(uintptr_t)FBDEV->FrameBuffer.FramebufferBase;
    }
    // Ensure x and y are within the screen bounds
    if (x >= FBDEV->FrameBuffer.Width || y >= FBDEV->FrameBuffer.Height) {
        return false; // Out of bounds, do nothing
    }

    //Calculate the position in the framebuffer
    uint32_t pixel_offset = (y * FBDEV->FrameBuffer.Pitch) + (x * bytes_per_pixel);

    return(void*)&framebuffer[pixel_offset];
}

#ifdef __x86_64__
    #include <limits.h>
#endif

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <drivers/display/vga.h>

#define EGA_TEXT_BUFFER ((volatile uint16_t*)0xB8000)
#define EGA_WIDTH 80
#define EGA_HEIGHT 25
#define EGA_COLOR 0x02  // Green on black

// Global cursor position for EGA text buffer
static int ega_x = 0;
static int ega_y = 0;

// Helper function to clear a specific line in the EGA text buffer
void ClearEgaLine(uint64_t line) {
    for (uint64_t x = 0; x < EGA_WIDTH; x++) {
        EGA_TEXT_BUFFER[line * EGA_WIDTH + x] = (EGA_COLOR << 8) | ' ';
    }
}

// Helper function to scroll the screen up by one line
void EgaScrollUp() {
    for (uint64_t y = 1; y < EGA_HEIGHT; y++) {
        for (uint64_t x = 0; x < EGA_WIDTH; x++) {
            EGA_TEXT_BUFFER[(y - 1) * EGA_WIDTH + x] = EGA_TEXT_BUFFER[y * EGA_WIDTH + x];
        }
    }
    ClearEgaLine(EGA_HEIGHT - 1);  // Clear the last line after scrolling
    ega_y = EGA_HEIGHT - 1;        // Reset cursor to the last line
    ega_x = 0;                     // Start at the beginning of the new line
}

// Helper function to write a character at the current EGA cursor position with scrolling
void EgaPutCharacter(char c) {
    if (c == '\n') {
        ega_x = 0;
        if (++ega_y >= EGA_HEIGHT) {
            EgaScrollUp();  // Scroll if we've reached the last line
        }
    } else {
        EGA_TEXT_BUFFER[ega_y * EGA_WIDTH + ega_x] = (EGA_COLOR << 8) | c;
        if (++ega_x >= EGA_WIDTH) {
            ega_x = 0;
            if (++ega_y >= EGA_HEIGHT) {
                EgaScrollUp();  // Scroll if we've reached the last line
            }
        }
    }
}

void print_binary64(uint64_t number);
void print_binary32(uint32_t number);
void print_binary16(uint16_t number);
void print_binary8(uint8_t number);
void intToString(uint64_t num, char* str);
//void uintToLittleEndianHexString(uint64_t number, char* hexString);
void uintToHexString(uint64_t number, char* hexString);

static spinlock_t EGALock;
static spinlock_t EGAPanicLock;

int LouPrintEGA(char* format, va_list args) {
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&EGALock, &Irql);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {  // Integer (decimal)
                    int64_t num = va_arg(args, int64_t);
                    char str[21];
                    intToString(num, str);  // Convert integer to string
                    for (char* p = str; *p != '\0'; ++p) {
                        EgaPutCharacter(*p);
                    }
                    break;
                }
                case 's': {  // String
                    char* text = va_arg(args, char*);
                    while (*text) {
                        EgaPutCharacter(*text++);
                    }
                    break;
                }
                case 'x': {  // Hexadecimal
                    uint64_t hex_num = va_arg(args, uint64_t);
                    char hex_str[17];
                    uintToHexString(hex_num, hex_str);
                    for (char* p = hex_str; *p != '\0'; ++p) {
                        EgaPutCharacter(*p);
                    }
                    break;
                }
                case 'y': {  // Set Y coordinate (EGA doesn't support this directly, placeholder)
                    uint64_t Y = va_arg(args, uint64_t);
                    ega_y = Y < EGA_HEIGHT ? Y : ega_y;  // Limit Y to screen height
                    break;
                }
                case 'c': {  // Single character
                    char c = (char)va_arg(args, int);
                    EgaPutCharacter(c);
                    break;
                }
                case 'h': {  // Hexadecimal (full 64-bit)
                    uint64_t num = va_arg(args, uint64_t);
                    char hex_str[17];
                    uintToHexString(num, hex_str);
                    for (char* p = hex_str; *p != '\0'; ++p) {
                        EgaPutCharacter(*p);
                    }
                    break;
                }
                case 'b': {  // Binary
                    format++;
                    uint64_t num = va_arg(args, uint64_t);
                    switch (*format) {
                        case 'l': {
                            print_binary64(num);  // Implement print_binary64 for 64-bit
                            break;
                        }
                        case 'i': {
                            print_binary32((uint32_t)num);  // 32-bit binary
                            break;
                        }
                        case 's': {
                            print_binary16((uint16_t)num);  // 16-bit binary
                            break;
                        }
                        case 'c': {
                            print_binary8((uint8_t)num);  // 8-bit binary
                            break;
                        }
                        default: {
                            format--;
                            break;
                        }
                    }
                    break;
                }
                case 'f': {  // Floating-point (long double, double, and float)
                    format++;
                    char str[21];
                    switch (*format) {
                        case 'l': {
                            long double num = va_arg(args, long double);
                            long_double_to_string(str, num);  // Convert to string
                            for (char* p = str; *p != '\0'; ++p) {
                                EgaPutCharacter(*p);
                            }
                            break;
                        }
                        case 'd': {
                            double num = va_arg(args, double);
                            double_to_string(str, num);  // Convert to string
                            for (char* p = str; *p != '\0'; ++p) {
                                EgaPutCharacter(*p);
                            }
                            break;
                        }
                        default: {  // Default float handling
                            format--;
                            float num = (float)va_arg(args, double);
                            float_to_string(str, num);  // Convert to string
                            for (char* p = str; *p != '\0'; ++p) {
                                EgaPutCharacter(*p);
                            }
                            break;
                        }
                    }
                    break;
                }
                default: {  // Unrecognized format, print literal '%'
                    EgaPutCharacter('%');
                    EgaPutCharacter(*format);
                    break;
                }
            }
            format++;
        } else {
            EgaPutCharacter(*format++);  // Print literal characters
        }
    }
    va_end(args);
    LouKeReleaseSpinLock(&EGALock, &Irql);
    return 0;
}



int LouPanicEGA(char* format, va_list args) {
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&EGAPanicLock, &Irql);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {  // Integer (decimal)
                    int64_t num = va_arg(args, int64_t);
                    char str[21];
                    intToString(num, str);  // Convert integer to string
                    for (char* p = str; *p != '\0'; ++p) {
                        EgaPutCharacter(*p);
                    }
                    break;
                }
                case 's': {  // String
                    char* text = va_arg(args, char*);
                    while (*text) {
                        EgaPutCharacter(*text++);
                    }
                    break;
                }
                case 'x': {  // Hexadecimal
                    uint64_t hex_num = va_arg(args, uint64_t);
                    char hex_str[17];
                    uintToHexString(hex_num, hex_str);
                    for (char* p = hex_str; *p != '\0'; ++p) {
                        EgaPutCharacter(*p);
                    }
                    break;
                }
                case 'y': {  // Set Y coordinate (EGA doesn't support this directly, placeholder)
                    uint64_t Y = va_arg(args, uint64_t);
                    ega_y = Y < EGA_HEIGHT ? Y : ega_y;  // Limit Y to screen height
                    break;
                }
                case 'c': {  // Single character
                    char c = (char)va_arg(args, int);
                    EgaPutCharacter(c);
                    break;
                }
                case 'h': {  // Hexadecimal (full 64-bit)
                    uint64_t num = va_arg(args, uint64_t);
                    char hex_str[17];
                    uintToHexString(num, hex_str);
                    for (char* p = hex_str; *p != '\0'; ++p) {
                        EgaPutCharacter(*p);
                    }
                    break;
                }
                case 'b': {  // Binary
                    format++;
                    uint64_t num = va_arg(args, uint64_t);
                    switch (*format) {
                        case 'l': {
                            print_binary64(num);  // Implement print_binary64 for 64-bit
                            break;
                        }
                        case 'i': {
                            print_binary32((uint32_t)num);  // 32-bit binary
                            break;
                        }
                        case 's': {
                            print_binary16((uint16_t)num);  // 16-bit binary
                            break;
                        }
                        case 'c': {
                            print_binary8((uint8_t)num);  // 8-bit binary
                            break;
                        }
                        default: {
                            format--;
                            break;
                        }
                    }
                    break;
                }
                case 'f': {  // Floating-point (long double, double, and float)
                    format++;
                    char str[21];
                    switch (*format) {
                        case 'l': {
                            long double num = va_arg(args, long double);
                            long_double_to_string(str, num);  // Convert to string
                            for (char* p = str; *p != '\0'; ++p) {
                                EgaPutCharacter(*p);
                            }
                            break;
                        }
                        case 'd': {
                            double num = va_arg(args, double);
                            double_to_string(str, num);  // Convert to string
                            for (char* p = str; *p != '\0'; ++p) {
                                EgaPutCharacter(*p);
                            }
                            break;
                        }
                        default: {  // Default float handling
                            format--;
                            float num = (float)va_arg(args, double);
                            float_to_string(str, num);  // Convert to string
                            for (char* p = str; *p != '\0'; ++p) {
                                EgaPutCharacter(*p);
                            }
                            break;
                        }
                    }
                    break;
                }
                default: {  // Unrecognized format, print literal '%'
                    EgaPutCharacter('%');
                    EgaPutCharacter(*format);
                    break;
                }
            }
            format++;
        } else {
            EgaPutCharacter(*format++);  // Print literal characters
        }
    }
    va_end(args);
    LouKeReleaseSpinLock(&EGAPanicLock, &Irql);
    return 0;
}
