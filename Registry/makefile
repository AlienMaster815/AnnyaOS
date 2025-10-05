# --- Configuration ---
CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -IInclude
LDFLAGS = 
TARGET  = LKRCompiler
SRC     = 	Compiler.c \
			LKRLIB/wcsext.c \
			LKRLIB/Nodes.c \
			LKRLIB/LkrFile.c \
			LKRLIB/LkrLexer.c			
OBJ     = $(SRC:.c=.o)

# --- Build Rules ---
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Cleanup ---
clean:
	rm -f $(OBJ) $(TARGET)
