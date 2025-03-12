# Tool and Flags
DLLTOOL = x86_64-w64-mingw32-dlltool

# Source and Target
DEF_FILE = KERNEL32.def
LIB_FILE = ../KERNEL32.lib  # Output directory is set to the parent directory

# Default Rule
all: $(LIB_FILE)

# Build Rule
$(LIB_FILE): $(DEF_FILE)
	@echo "Generating $(LIB_FILE) from $(DEF_FILE)..."
	$(DLLTOOL) --input-def $(DEF_FILE) --output-lib $(LIB_FILE)

# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(LIB_FILE)
