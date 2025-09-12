# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs -O3

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll -lntdll -luser32 #defaultlibs

# Source and Target
SRC = 	Gdi32.c \
		Brush.c \
		Path.c  \
		Bitmap.c \
		Font.c \
		Dc.c \
		Close.c \
		Combine.c \
		Copy.c

TARGET = GDI32.DLL

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)


# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)

#TODO: GDI_TODO 