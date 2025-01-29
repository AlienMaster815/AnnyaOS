# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs

# Paths
LDFLAGS = -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc
INCLUDES = -I../../../include


# Source and target
SRC = PcNet2Main.cpp
TARGET = PCNET2.SYS

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(LDFLAGS) $(SRC) $(LIBS) $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
