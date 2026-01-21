freeglut
========

![GNU/Linux (X11) build status](https://github.com/freeglut/freeglut/actions/workflows/build_gnulinux_x11.yml/badge.svg)
![FreeBSD (X11) build status](https://github.com/freeglut/freeglut/actions/workflows/build_freebsd_x11.yml/badge.svg)
![Windows (MSVC) build status](https://github.com/freeglut/freeglut/actions/workflows/build_win_msvc.yml/badge.svg)
![Windows (MSVC 6.0) build status](https://github.com/freeglut/freeglut/actions/workflows/build_win_msvc6.yml/badge.svg)
![Windows (MinGW) build status](https://github.com/freeglut/freeglut/actions/workflows/build_win_mingw.yml/badge.svg)
![MacOS X (X11) build status](https://github.com/freeglut/freeglut/actions/workflows/build_macosx_x11.yml/badge.svg)
![MacOS X (Cocoa) build status](https://github.com/freeglut/freeglut/actions/workflows/build_macosx_cocoa.yml/badge.svg)

OVERVIEW
--------

Freeglut, the Free OpenGL Utility Toolkit, is meant to be a free alternative to
Mark Kilgard's GLUT library. Freeglut is free software, distributed under an
MIT/X11 style license. You are free to use, modify, and redistribute freeglut
with or without modifications (see COPYING for details).

In short, freeglut can be used by OpenGL programs to perform those tasks which
would normally require platform-specific code. Tasks like creating a window,
creating an OpenGL context and binding it to the window, and processing input
events. Freeglut provides a concise and elegant API to handle those tasks, in a
platform-independent manner, keeping the application simple and portable.

One of the main goals of freeglut, is maximum compatibility. Freeglut is both
source and binary-compatible with the original GLUT, and can be used as a
drop-in replacement for it. We take great care to maintain a stable API and ABI,
and to introduce any new features and improvements in a way which does not
compromise compatibility.

Freeglut can be used with a wide range of OpenGL implementations, from the very
early OpenGL 1.0 on SGI computers, to the very latest modern OpenGL versions on
current GPUs. It can be used to create a classic OpenGL context, or a versioned
core profile or compatibility context. Freeglut can also be used with OpenGL ES,
on desktop or mobile devices.


PORTS
-----

Currently supported platforms:
 - UNIX systems with X11 or Wayland (such as GNU/Linux, FreeBSD, IRIX, etc)
 - MS Windows
 - macOS with XQuartz (no native Cocoa support yet)
 - Android (NDK)
 - BlackBerry
 - Nintendo GameCube and Wii

Consult the platform-specific readme files for details on the level of support
and build instructions.


INSTALLATION
------------

Freeglut relies on cmake (minimum 3.1.0) to generate build files for all the
different supported platforms and toolchains.

See [`README.cmake`](README.cmake) as a starting point, as well as the other `README`
files for further info.

For those cases where using cmake is inconvenient, we also provide a set of
unofficial, unsupported, possibly unmaintained, but potentially useful,
alternative build files. See [`altbuild/README.md`](altbuild/README.md) for details.


CONTRIBUTING
------------

Patches and pull requests for bugfixes and new features are certainly welcome.
Please send patches to the freeglut-developer mailing list (see CONTACT below).

Feel free to report any bugs you encounter, using the github *issues* system.

Older bug reports and feature requests are still reachable on:
  - https://sourceforge.net/p/freeglut/bugs/
  - https://sourceforge.net/p/freeglut/feature-requests/

But you are encouraged to use github issues for new ones.

Alternatively you can also send bug reports and feature requests to the
freeglut-developer mailing list if you prefer. Extended discussions about new
features and design issues for large contributions, are best suited to the
mailing list.


CONTACT
-------

FreeGLUT website: http://freeglut.sourceforge.net

FreeGLUT mailing lists:
 - developer: https://lists.sourceforge.net/lists/listinfo/freeglut-developer
 - bugs: https://lists.sourceforge.net/lists/listinfo/freeglut-bugs
 - announce: https://lists.sourceforge.net/lists/listinfo/freeglut-announce

  You need to subscribe before posting to any of our mailing lists. Make sure
  to avoid selecting "daily digest mode" if you intend to post, so that you can
  reply properly to specific messages. Also, please do not top-post, and try to
  send properly formatted emails (text, hard-wrapped at 72 columns, no binary or
  large attachments).
