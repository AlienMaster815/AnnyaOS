SOURCE   = wcsext.c
OBJ      = $(SOURCE:.c=.o)
COMPILER = gcc
FLAGS    = -I ../Include -Wall -Wextra -fPIC -fvisibility=hidden -DBUILDING_DLL -Wno-unused-parameter -Wno-unused-private-field
LD       = ld
OUTPUT   = ../Wwc.so

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    LDFLAGS  = -shared -soname $(OUTPUT)
    CRTI     := $(shell $(COMPILER) -print-file-name=crti.o)
    CRTBEGIN := $(shell $(COMPILER) -print-file-name=crtbeginS.o)
    CRTEND   := $(shell $(COMPILER) -print-file-name=crtendS.o)
    CRTN     := $(shell $(COMPILER) -print-file-name=crtn.o)
    LIBGCC_D := $(dir $(shell $(COMPILER) -print-libgcc-file-name))
    
    PRE_OBJS  = $(CRTI) $(CRTBEGIN)
    POST_OBJS = $(CRTEND) $(CRTN)
    LIBS      = -L$(LIBGCC_D) -lstdc++ -lm -lgcc_s -lc
endif

ifeq ($(UNAME_S),Darwin)
    LDFLAGS   = -dylib -install_name @rpath/$(OUTPUT)
    SYSROOT  := $(shell xcrun --show-sdk-path)
    
    PRE_OBJS  =
    POST_OBJS =
    LIBS      = -L$(SYSROOT)/usr/lib -lc++ -lSystem
endif

.PHONY: all clean

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(PRE_OBJS) $^ $(LIBS) $(POST_OBJS)

%.o: %.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUTPUT)
