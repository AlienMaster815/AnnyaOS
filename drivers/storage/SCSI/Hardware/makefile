# Compiler and flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings

LIBS = -L../../../PCI -lPCI

# Paths
INCLUDES = -I../../../../include


# Source and target
SRC = LsiLogic.c
TARGET = LSI_SCSI.SYS

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)
