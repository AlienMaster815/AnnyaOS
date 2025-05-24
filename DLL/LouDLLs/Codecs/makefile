# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll -lntdll -luser32 -lmsvcrt

# Source and Target
SRC = Codecs.c 
TARGET = codecs.dll

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)


# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
