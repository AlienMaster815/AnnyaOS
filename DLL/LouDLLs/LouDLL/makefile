# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs

# Paths
INCLUDES = -I../../../Include

# Source and Target
SRC = LouDll.c
TARGET = LouDll.dll

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES)

# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
