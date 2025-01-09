# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll

# Source and Target
SRC = VCRUNTIME140.c
TARGET = VCRUNTIME140.dll

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Clean Rule
clean:
	rm -f $(TARGET)
