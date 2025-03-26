# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs -ffreestanding -Wno-builtin-declaration-mismatch

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll -lKERNEL32 -lkernelbase

# Source and Target
SRC = MSVCRT.c \
      MsvcLock.c \
	  Allocation.c

TARGET = msvcrt.dll

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)


# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
