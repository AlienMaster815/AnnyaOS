# Compiler and flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64 -O3 -mabi=ms -mno-red-zone -fno-stack-protector -nostdlib -nodefaultlibs -fno-builtin
LDFLAGS = \
    -Wl,--entry=AnnyaExplorerProcessStartup \
    -Wl,--subsystem,console \
    -Wl,--dynamicbase \
    -Wl,--high-entropy-va \
    -L../../UserLibraries
INCLUDES = -I../../include
LIBS = -lLouDll -luser32

# Source and target
SRC = Explorer.c
TARGET = Explorer.exe

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) $(LIBS) $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)