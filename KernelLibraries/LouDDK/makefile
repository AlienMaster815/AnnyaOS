# Compiler and Tools
CC = x86_64-w64-mingw32-gcc
AR = x86_64-w64-mingw32-ar

# Source and Target
CFILE = LouDDKCrtc.c
LIB_FILE = ../LouDDKCrtc.lib  # Output directory is set to the parent directory
OBJ_FILE = LouDDKCrtc.o     # Intermediate object file

INCLUDES = -I../../include

# Additional Libraries
LIBRARIES = -L../../../KernelLibraries -llouoskrnl.lib

# Default Rule
all: $(LIB_FILE)

# Compile C file into object file
$(OBJ_FILE): $(CFILE)
	@echo "Compiling $(CFILE) into $(OBJ_FILE)..."
	$(CC) -c $(CFILE) -Wno-return-type -o $(OBJ_FILE) $(INCLUDES) $(LIBRARIES)

# Build .lib file from object file
$(LIB_FILE): $(OBJ_FILE)
	@echo "Creating static library $(LIB_FILE) from $(OBJ_FILE)..."
	$(AR) rcs $(LIB_FILE) $(OBJ_FILE)

# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(LIB_FILE) $(OBJ_FILE)
