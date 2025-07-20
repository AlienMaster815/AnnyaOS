GCC = gcc
SRC = UsrSrc
GLB_SRC = Src
OP_SRC = Src/Opcodes
INC = Include
BIN = bin
TARGET = LkrsUser.sh

CFLAGS = -I$(INC) -O2 #-Wall -Wextra
LDFLAGS =

OBJS := $(patsubst $(SRC)/%.c,$(BIN)/%.o,$(wildcard $(SRC)/*.c))
OBJS += $(patsubst $(GLB_SRC)/%.c,$(BIN)/%.o,$(wildcard $(GLB_SRC)/*.c))
OBJS += $(patsubst $(OP_SRC)/%.c,$(BIN)/%.o,$(wildcard $(OP_SRC)/*.c))

.PHONY: BuildHostCompiler CleanHostCompiler

BuildHostCompiler: $(TARGET)

$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(BIN)
	$(GCC) $(CFLAGS) -c -o $@ $<

$(BIN)/%.o: $(GLB_SRC)/%.c
	@mkdir -p $(BIN)
	$(GCC) $(CFLAGS) -c -o $@ $<

$(BIN)/%.o: $(OP_SRC)/%.c
	@mkdir -p $(BIN)
	$(GCC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(GCC) -o $@ $(OBJS) $(LDFLAGS)

CleanHostCompiler:
	rm -rf $(BIN) $(TARGET)