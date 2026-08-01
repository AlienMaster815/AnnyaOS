#//Copyright GPL-2 Tyler Grenier (2026)
INCLUDES = -I../../../include
TARGET = SCSICORE.SYS
SRC = 	ScsiCore.c \
		Cdb.c \
		Cdb6.c \
		Cdb10.c \
		Cdb12.c \
		Cdb16.c \
		CdbVar.c \
		Ssdd.c \
		ScsiCommands.c

CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -mconsole --entry=ScsiCoreEntry -fno-builtin -Wno-multichar -mabi=ms -mno-red-zone

# Tool and Flags
DLLTOOL = x86_64-w64-mingw32-dlltool

# Source and Target
DEF_FILE = Scsi.def
LIB_FILE = Scsi.lib  # Output directory is set to the parent directory


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