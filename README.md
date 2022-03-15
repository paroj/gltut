# OpenGL Tutorials

This is a series of tutorials on using OpenGL to do graphical rendering.
The code for each tutorial is found in the `Tut*` directories. The code
alone is not enough information to understand what is going on. The actual
documentation is available in several forms.

The HTML form of the documentation can be found on: https://paroj.github.io/gltut/

The [License.txt](License.txt) file contains the licensing information for the materials distributed in these tutorials.

In case you prefer Java to C++, Giuseppe Barbieri [created a Java port here](https://github.com/elect86/modern-jogl-examples).

## Building the tutorials

- `apt-get install cmake`
- `mkdir build && cd build`
- `cmake ..`
- `cmake --build . --config Release`

## Rebuilding the HTML Documentation

- `apt-get install lua-filesystem xsltproc docbook-xsl`
- run `lua CopyWebsite.lua`

## Rebuilding the PDF Documentation

- install the packages needed for HTML
- `apt-get install fop libxerces2-java libsaxon-java libfop-java libjeuclid-fop-java`
- add the line `find_jars jeuclid-core jeuclid-fop` to `/usr/bin/fop`
- inside `Documents/Build` run `lua BuildComputerFO.lua`

## Known issues

### Exception in thread "main" java.lang.NoClassDefFoundError: org/w3c/dom/events/CustomEvent
Some versions of `fop` will not work correctly.
Installing `2.6` from here https://xmlgraphics.apache.org/fop/download.html fixes it.
