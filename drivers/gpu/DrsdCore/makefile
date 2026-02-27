INCLUDES = -I../../../include
TARGET = DRSDCORE.SYS
SRC = DrsdCore.cpp \
		DrsdConnector.cpp \
		DrsdCache.cpp \
		DrsdModes.cpp \
		DrsdModeObjects.cpp 


CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -mconsole --entry=DrsdCoreSubsystemEntry

# Tool and Flags
DLLTOOL = x86_64-w64-mingw32-dlltool

# Source and Target
DEF_FILE = DrsdCore.def
LIB_FILE = drsdcore.lib  # Output directory is set to the parent directory


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
