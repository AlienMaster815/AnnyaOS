INCLUDES = -I../../../include
TARGET = BOOTVID.SYS
SRC = 	BootVidMain.c \
		BootRender.c \
		Terminal.c \
		Ttf/OpenType.c \
		Ttf/TtfCmap.c \
		Ttf/TtfGlyph.c \
		Ttf/TtfLoca.c \
		Ttf/TtfHead.c \
		Ttf/TtfHmtx.c \
		Bitmap/Allocation.c \
		Bitmap/Drawing.c \
		Bitmap/Render.c


CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -mconsole --entry=BootVidEntry -fno-builtin -Wno-multichar

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../KernelLibraries -llouoskrnl $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
