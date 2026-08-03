
zlib:
	x86_64-w64-mingw32-gcc -O3 -shared -static-libgcc -DZLIB_DLL *.c -o zlib.dll -Wl,--out-implib,libzlib.a


clean:	
	rm -rf libzlib.a
	rm -rf zlib.dll