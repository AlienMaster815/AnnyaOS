# --- Configuration ---
CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -IInclude -ICompiler
LDFLAGS = 
TARGET  = LKRCompiler
SRC     = $(shell find Compiler -name "*.c")
OBJ     = $(patsubst %.c, build/%.o, $(SRC))

# --- Build Rules ---
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Cleanup ---
clean:
	rm -rf build $(TARGET)


#TODO: Fix Termination Bug