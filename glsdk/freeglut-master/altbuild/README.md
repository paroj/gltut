Simple build files for freeglut
===============================
This directory includes a number of simple ways to build freeglut, without
relying on extra tools.

The official build system used by freeglut is cmake, with the current minimum
cmake version required being set to 3.1. Installing and using cmake 3.1 or later
to generate build files might be difficult or inconvenient in some cases.
Installing modern versions of cmake on very old UNIX systems might be difficult
or impossible. And finding the exact cmake version which still supports
generating project files for a certain old IDE, dropped from current cmake, can
be annoying.

None of the files in this directory are officially supported! Some of them might
be completely unmaintained, broken, or out of date. Please report any issues,
but be warned that you may have to fix them yourself.

The simple build files in this directory do not build the demo programs, and do
not provide the same flexibility of build options as the official cmake build.
Most of them just build a default configuration of freeglut as a static library
and that's it.

Configuration
-------------
Before using any of these build files, first you'll need to select one of the
`config.h.*` files provided, copy it to the project root directory with the name
`config.h`. The following config files are available:

  - config.h.unix: Modern UNIX with X11 (GNU/Linux, FreeBSD, etc).
  - config.h.msvc6: Windows build with MS Visual C/C++ 6.0.
  - config.h.irix5: IRIX 5.x build with the SGI compiler.
  - config.h.irix6: IRIX 6.x build with the SGI compiler.
  - config.h.sol26: Solaris 2.6 build with the SUN compiler.

You can edit the `config.h` file to remove unnecessary dependencies (and their
corresponding features). For example, some old X servers do not have the XRandR
extension, or you may not wish to install libXrandr, in which case you should
disable it by deleting the `#define HAVE_X11_EXTENSIONS_XRANDR_H` line, or
changing `define` to `undef`.

Simple UNIX Makefile
--------------------
This should build freeglut on many different UNIX systems with their native
make utility.

  - Copy `Makefile` to the project root directory.
  - Copy the appropriate `config.h.*` file to the project root directory renamed
    to `config.h`.
  - `make` to build.
  - `make install` to install. Change the `PREFIX` variable at the top of the
    `Makefile` to change the installation prefix.

You can also attempt to build a simple statically linked demo program, by typing
`make demo`. But be warned that you might need to modify the `demo_libs`
variable at the top of the `Makefile` to adjust for whatever options are
selected in the `config.h` you used to build freeglut.

MS Visual Studio 6.0 project
----------------------------
Project files for building freeglut on 32bit windows, using MSVC6.

  - Copy `config.h.msvc6` to the project root directory renamed to `config.h`.
  - Open the `freeglut.dsw` "workspace" file with visual studio 6.
  - Select build all from the build menu.

The MSVC6 project builds freeglut as both a static library and a DLL, and also
builds a simple statically linked demo program.
