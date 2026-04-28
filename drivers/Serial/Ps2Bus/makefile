#//Copyright GPL-2 Tyler Grenier (2024 - 2026)
# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -fno-builtin -mabi=ms -mno-red-zone

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