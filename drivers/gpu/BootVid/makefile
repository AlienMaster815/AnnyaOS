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
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -mconsole --entry=BootVidEntry -fno-builtin -Wno-multichar -mabi=ms -mno-red-zone

# Tool and Flags
DLLTOOL = x86_64-w64-mingw32-dlltool

# Source and Target
DEF_FILE = BootVid.def
LIB_FILE = BootVid.lib  # Output directory is set to the parent directory


# Build rule
all: $(TARGET) $(LIB_FILE)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../KernelLibraries -llouoskrnl $(INCLUDES)

# Build Rule
$(LIB_FILE): $(DEF_FILE)
	@echo "Generating $(LIB_FILE) from $(DEF_FILE)..."
	$(DLLTOOL) --input-def $(DEF_FILE) --output-lib $(LIB_FILE)

# Clean rule
clean:
	rm -f $(TARGET)
	rm -f $(LIB_FILE)