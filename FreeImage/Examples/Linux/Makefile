CC = gcc
CPP = g++
COMPILERFLAGS = -O3
INCLUDE = -I../../Dist -I/usr/include/asm
VGALIBRARIES = -lfreeimage -lvga
GTKLIBRARIES = -lfreeimage -lgtk -lgdk
GTKINCLUDE = -I/usr/lib/glib/include
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)



all: default

default: linux-svgalib linux-gtk

linux-svgalib: linux-svgalib.c
	$(CC) $(CFLAGS) $< -o $@ $(VGALIBRARIES)
	strip $@

linux-gtk: linux-gtk.c
	$(CC) $(CFLAGS) $< -o $@ $(GTKLIBRARIES) $(GTKINCLUDE)
	strip $@

clean:
	rm -f core linux-svgalib linux-gtk
