# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs -O3

# Paths
INCLUDES = -I../../../include -I ../../3rdParty/zlib
LDFLAGS = -L../../../UserLibraries 
LIBS = -lLouDll -lntdll -luser32 -lmsvcrt -lKERNEL32

# Source and Target
SRC = Codecs.c \
		Png.c

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
