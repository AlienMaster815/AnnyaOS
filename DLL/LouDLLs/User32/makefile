# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs -O3 -flto

# Paths
INCLUDES = -I../../../include -I../../3rdParty/FreeType/include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll -lntdll -lKERNEL32

# Source and Target
SRC = User32.c \
		Interface/strings.c \
		Interface/Awm.c \
		Interface/Geometry.c \
		Interface/WindowCreation/WinCreation.c \
		Interface/WindowCreation/Styles.c \
		Interface/WinModifications/WinModification.c \
		Interface/PlaneGeometrics/PlaneInitialization.c \
		Interface/PlaneGeometrics/PlanePaint.c 

TARGET = user32.dll

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Clean Rule
clean:
	rm -f $(TARGET)
