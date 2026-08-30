# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -fno-builtin -mabi=ms -mno-red-zone

# Paths
INCLUDES = -I../../../../include


# Source and target
SRC = AtaGeneric.c
TARGET = ATA.SYS

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES) -L../../../PCI -lPCI -L.. -lAta

# Clean rule
clean:
	rm -f $(TARGET)

