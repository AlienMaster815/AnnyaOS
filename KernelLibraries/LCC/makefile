# Compiler and Tools
CC = x86_64-w64-mingw32-gcc
AR = x86_64-w64-mingw32-ar

# Source and Target
CFILE = LCC.c
LIB_FILE = ../LCC.lib  # Output directory is set to the parent directory
OBJ_FILE = LCC.o     # Intermediate object file

INCLUDES = -I../../include


# Default Rule
all: $(LIB_FILE)

# Compile C file into object file
$(OBJ_FILE): $(CFILE)
	$(CC) -c $(CFILE) -Wno-return-type -o $(OBJ_FILE) $(INCLUDES)

# Build .lib file from object file
$(LIB_FILE): $(OBJ_FILE)
	$(AR) rcs $(LIB_FILE) $(OBJ_FILE)

# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(LIB_FILE) $(OBJ_FILE)
