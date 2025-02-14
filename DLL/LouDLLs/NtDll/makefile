# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll

# Source and Target
SRC = 	NtDll.c \
		Sha.c
		
TARGET = ntdll.dll

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
