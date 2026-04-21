INCLUDES = -I../../include
TARGET = DRSDCORE.SYS
SRC = DrsdCore.c \
		DrsdAtomic.c \
		DrsdAtomicHelper.c \
		DrsdAtomicStateHelpers.c \
		DrsdAtomicUapi.c \
		DrsdBridge.c \
		DrsdBridgeHelper.c \
		DrsdConnector.c \
		DrsdCache.c \
		DrsdModes.c \
		DrsdModeConfig.c \
		DrsdModesetLock.c \
		DrsdEld.c \
		DrsdEdid.c \
		DrsdDraw.c \
		DrsdFormatHelper.c \
		DrsdModeObject.c \
		DrsdColorOp.c \
		DrsdWriteback.c \
		DrsdCrtc.c \
		DrsdGxeVRamHelper.c \
		DrsdGxeTtmHelper.c \
		DrsdGxe.c \
		DrsdMm.c \
		DrsdProperty.c \
		DrsdUapi.c \
		DrsdCrtcHelper.c \
		DrsdPlane.c \
		DrsdVBlank.c \
		DrsdRect.c \
		DrsdGxeFrameBufferHelper.c \
		Ttm/TtmRangeManager.c \
		Ttm/TtmDevice.c \
		Ttm/TtmPool.c \
		Ttm/TtmTt.c \
		Ttm/TtmResource.c 


CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -mconsole --entry=DrsdCoreSubsystemEntry -fno-builtin -Wno-multichar

# Tool and Flags
DLLTOOL = x86_64-w64-mingw32-dlltool

# Source and Target
DEF_FILE = DrsdCore.def
LIB_FILE = drsdcore.lib  # Output directory is set to the parent directory


# Build rule
all: $(TARGET) $(LIB_FILE)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../KernelLibraries -llouoskrnl $(INCLUDES)

# Build Rule
$(LIB_FILE): $(DEF_FILE)
	@echo "Generating $(LIB_FILE) from $(DEF_FILE)..."
	$(DLLTOOL) --input-def $(DEF_FILE) --output-lib $(LIB_FILE)

# Clean rule
clean:
	rm -f $(TARGET)
	rm -f $(LIB_FILE)