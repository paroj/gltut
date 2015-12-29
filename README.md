# OpenGL Tutorials

This is a series of tutorials on using OpenGL to do graphical rendering.
The code for each tutorial is found in the `Tut*` directories. The code
alone is not enough information to understand what is going on. The actual
documentation is available in several forms.

The HTML form of the documentation can be found on: https://paroj.github.io/gltut/

The [License.txt](License.txt) file contains the licensing information for the materials distributed in these tutorials.


## Rebuilding the HTML Documentation

- `apt-get install lua-filesystem libxerces2-java libsaxon-java docbook-xsl`
- run `lua CopyWebsite.lua`

## Rebuilding the PDF Documentation

- install the packages needed for HTML
- `apt-get install fop libfop-java libjeuclid-fop-java`
- add the line `find_jars jeuclid-core jeuclid-fop` to `/usr/bin/fop`
- run `lua Documents/Build/BuildComputerFO.lua`
