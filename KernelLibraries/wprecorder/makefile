# Compiler and Tools
CC = x86_64-w64-mingw32-g++
AR = x86_64-w64-mingw32-ar

# Source and Target
CFILE = wprecorder.cpp
LIB_FILE = ../wprecorder.lib  # Output directory is set to the parent directory
OBJ_FILE = wprecorder.o       # Intermediate object file
DEF_FILE = wprecorder.def     # Define exports

INCLUDES = -I../../include

# Default Rule
all: $(LIB_FILE)

# Compile C file into object file
$(OBJ_FILE): $(CFILE)
	$(CC) -c $(CFILE) -Wno-write-strings -Wno-return-type -o $(OBJ_FILE) -L../../KernelLibraries -llouoskrnl $(INCLUDES)

# Build .lib file from object file and .def file
$(LIB_FILE): $(OBJ_FILE) $(DEF_FILE)
	$(AR) rcs $(LIB_FILE) $(OBJ_FILE)

# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(LIB_FILE) $(OBJ_FILE)
