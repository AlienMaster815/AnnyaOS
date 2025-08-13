# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings

# Paths
INCLUDES = -I../../../include


# Source and target
PIIX_SRC = PIIX.cpp
PIIX_TARGET = PIIX.SYS

# Build rule
all: $(PIIX_TARGET)

$(PIIX_TARGET): $(PIIX_SRC)
	$(CC) $(CFLAGS) -o $(PIIX_TARGET) $(PIIX_SRC) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES)

# Clean rule
clean:
	rm -f $(PIIX_TARGET)
