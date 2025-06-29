# Compiler and flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -O3

# Paths
LDFLAGS = -L../../UserLibraries
INCLUDES = -I../../include
LIBS = -lLouDll -luser32 -l/PreCompiledHeaders/ExeCrtc -lKERNEL32

# Source and target
SRC = AnnyaExp.c
TARGET = AnnyaExp.exe

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS) $(LIBS) $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
