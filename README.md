# OpenGL Tutorials

This is a series of tutorials on using OpenGL to do graphical rendering.
The code for each tutorial is found in the `Tut*` directories. The code
alone is not enough information to understand what is going on. The actual
documentation is available in several forms.

The HTML form of the documentation can be found on: https://paroj.github.io/gltut/

The [License.txt](License.txt) file contains the licensing information for the materials distributed in these tutorials.

In case you prefer Java to C++, Giuseppe Barbieri [created a Java port here](https://github.com/elect86/modern-jogl-examples).

## Building the project
- Be warned, this repo does contain a number of files that are larger than GitHub's reccommended 50MB
- premake4 and glsdk are already included in this particular fork, so you do not need to download them yourself
- From the main directory, run `premake4 --file=./glsdk/premake4.lua <target>` where `<target>` is either `vs2010` or `gmake`
- Build the solution (if using VS) or run `make` (if using GNU) for all items in the glsdk directory (this builds the library we use)
- Now, again from the main directory, run premake (this time you do not need to specify the target file) `premake4 <target>` using the same target as last time
- Now you can either build the entire solution (VS) or run `make` (GNU; may be `make all`, uncertain as I used Virtual Studios for this)

## Rebuilding the HTML Documentation

- `apt-get install lua-filesystem libxerces2-java libsaxon-java docbook-xsl`
- run `lua CopyWebsite.lua`

## Rebuilding the PDF Documentation

- install the packages needed for HTML
- `apt-get install fop libfop-java libjeuclid-fop-java`
- add the line `find_jars jeuclid-core jeuclid-fop` to `/usr/bin/fop`
- run `lua Documents/Build/BuildComputerFO.lua`
