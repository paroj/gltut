How to build freeglut with CMake on Windows (MS Visual Studio)
--------------------------------------------------------------
Note: If you are using a recent version of Visual Studio (2017 or newer),
it may be simpler to use the built-in support for CMake (described in the
next section), rather than installing CMake separately as shown here.

1.  Download CMake (http://www.cmake.org/cmake/resources/software.html).
    Get one of the releases from the binary distribution section.
2.  Run the CMake installer, install wherever you like. 
3.  Launch CMake via Start > Program Files > CMake 2.8 > CMake (GUI)
    (note that the shortcut put by the installer on your desktop does NOT
    point to the CMake GUI program!)
4.  In the "Where is the source code" box, type or browse to the root
    directory of your freeglut source (so that's /freeglut, not
    /freeglut/src).
5.  In the "Where to build the binaries" box, type or browse to any
    folder you like - this will be where the Visual Studio solution will be
    generated. This folder does not have to exist yet.
6.  Hit the Configure button near the bottom of the window. 
7.  Pick your target compiler, make sure that its installed on your
    system of course!
8.  Answer Ok when asked if you want to create the build directory. 
9.  Wait for the configure process to finish. 
10. The screen will now have some configuration options on it, for
    instance specifying whether you want to build static and/or shared
    libraries (see below for a complete list). When you've selected your
    options, click the Configure button again.
11. The Generate button at the bottom will now be enabled. Click Generate.
12. The build files will now be generated in the location you picked. 

You can now navigate to the build directory you specified in step 5.
Open the freeglut.sln file that was generated in your build directory,
and compile as usual


How to build freeglut on Windows (Visual Studio 2017 or newer)
--------------------------------------------------------------
Starting from Visual Studio 2017, VS features built-in
support for CMake projects:
https://learn.microsoft.com/cpp/build/cmake-projects-in-visual-studio
This means that installing CMake separately is not needed.

1. Install the "Desktop development with C++" workload from
   the VS Installer, which includes CMake and MSVC by default.
2. Open the project folder from Visual Studio. At this point
   it will attempt to configure CMake automatically. Once it's done,
   click on "Open CMake Settings editor" or select
   "Manage Configurations..." from the build configuration drop-down to
   make further changes.
3. After adjusting the CMake options (or just using the default
   configuration), click on "Build > Build All". By default, this will
   generate output in the "out" subdirectory of your project. A list of
   available options is given below.


How to build freeglut on UNIX
-----------------------------
- Make sure you have cmake installed. Examples:
  - Debian/Ubuntu: apt-get install cmake
  - Fedora: yum install cmake
  - FreeBSD: cd /usr/ports/devel/cmake && make install
  Or directly from their website:
  http://www.cmake.org/cmake/resources/software.html
- Make sure you have the basics for compiling code, such as C compiler
  (e.g., GCC) and the make package.
- Also make sure you have packages installed that provide the relevant
  header files for opengl (e.g., libgl1-mesa-dev on Debian/Ubuntu) and
  the chosen backend :
  - X11: x11 (e.g., libx11-dev, libxrandr-devel on Debian/Ubuntu) and
  XInput (libxi-dev / libXi-devel)
  - Wayland: wayland (e.g., libwayland-dev and libegl1-mesa-dev on
  Debian/Ubuntu) and xkbcommon (libxkbcommon-dev /libxkbcommon-devel)
- Run 'cmake .' (or 'cmake . -DFREEGLUT_WAYLAND=ON' for Wayland) in the
  freeglut directory to generate the makefile.
- Run 'make' to build, and 'make install' to install freeglut.
- If you wish to change any build options run 'ccmake .'


Breakdown of CMake configuration options
----------------------------------------
CMAKE_BUILD_TYPE            [Empty, Debug, Release] Can be overridden by
                            passing it as a make variable during build.
CMAKE_INSTALL_PREFIX        Installation prefix (e.g. /usr/local on UNIX)
FREEGLUT_BUILD_DEMOS        [ON, OFF] Controls whether the demos are
                            built or not.
FREEGLUT_BUILD_SHARED_LIBS  [ON, OFF] Build freeglut as a shared library
FREEGLUT_BUILD_STATIC_LIBS  [ON, OFF] Build freeglut as a static library
FREEGLUT_GLES               [ON, OFF] Link with GLEs libraries instead
                            of OpenGL
FREEGLUT_WAYLAND            [ON, OFF] Link with Wayland libraries instead
                            of X11
FREEGLUT_PRINT_ERRORS       [ON, OFF] Controls whether errors are
                            default handled or not when user does not
                            provide an error callback
FREEGLUT_PRINT_WARNINGS     [ON, OFF] Controls whether warnings are
                            default handled or not when user does not
                            provide an warning callback
FREEGLUT_REPLACE_GLUT       [ON, OFF] For non-Windows platforms,
                            freeglut is by default built as -lglut. if
                            off, built as -lfreeglut. On Windows,
                            libraries are always built as freeglut.
INSTALL_PDB                 [ON, OFF] MSVC only: controls whether debug
                            information files are included with the
                            install or not
