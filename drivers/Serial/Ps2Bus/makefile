# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings

# Paths
INCLUDES = -I../../../include


# Source and target
SRC = Ps2.cpp
TARGET = PS2IO.SYS

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)