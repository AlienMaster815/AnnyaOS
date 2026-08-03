CC = x86_64-w64-mingw32-gcc
CFLAGS = -O3 -shared -static-libgcc -I./include -DFT2_BUILD_LIBRARY -D"FT_CONFIG_OPTION_DISABLE_ZLIB" -D"FT_CONFIG_OPTION_DISABLE_LZW"

SRCS = src/base/ftbase.c src/base/ftinit.c src/base/ftsystem.c src/base/ftdebug.c \
       src/base/ftbbox.c src/base/ftbdf.c src/base/ftbitmap.c src/base/ftcid.c \
       src/base/ftfstype.c src/base/ftgasp.c src/base/ftglyph.c src/base/ftgxval.c \
       src/base/ftmm.c src/base/ftotval.c src/base/ftpatent.c \
       src/base/ftpfr.c src/base/ftstroke.c src/base/ftsynth.c src/base/fttype1.c \
       src/base/ftwinfnt.c src/gzip/ftgzip.c src/lzw/ftlzw.c \
       src/autofit/autofit.c src/truetype/truetype.c src/cff/cff.c src/cid/type1cid.c \
       src/pfr/pfr.c src/type42/type42.c src/winfonts/winfnt.c src/pcf/pcf.c src/bdf/bdf.c \
       src/sfnt/sfnt.c src/psaux/psaux.c src/psnames/psnames.c src/pshinter/pshinter.c \
       src/smooth/smooth.c src/raster/raster.c src/sdf/sdf.c src/svg/svg.c src/type1/type1.c

FreeType:
	$(CC) $(CFLAGS) $(SRCS) -o freetype.dll -Wl,--out-implib,libfreetype.a

# Clean rule
clean:
	rm -f freetype.dll libfreetype.a
