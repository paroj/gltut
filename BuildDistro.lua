--[[
Must manually generate the following first:
* Documents/web, generated with Oxygen template

May also generate the following:
* Documents/tutorials.pdf, generated with Oxygen template
* Documents/kindleTutorials.pdf, generated with Oxygen template
]]--

require "lfs"

local destDir, hgChangelist, versionNum = ...

--local test = {...}
--print(#test, ...)
assert(#({...}) == 3, "Not enough commandline parameters.");

lfs.mkdir(destDir);


-------------------------------------------
-- Use the other Lua script to copy the HTML to the destination.
local CopyWebsite = assert(loadfile("CopyWebsite.lua"));
CopyWebsite(destDir .. "html\\");


--------------------------------------------
-- Copy other files.
os.execute(string.format([[copy "documents\TutorialsPrint.pdf" "%s\"]], destDir));
os.execute(string.format([[copy "documents\TutorialsKindle.pdf" "%s\"]], destDir));
os.execute(string.format([[copy "documents\TutorialsComp.pdf" "%s\"]], destDir));

------------------------------------------
-- Use Mercurial to get a version in the destination directory.
local clone = [[hg archive -r "%s" "%s\"]];
clone = clone:format(hgChangelist, destDir);

print(clone);
os.execute(clone);

-------------------------------------------
-- Generate the ancillary files

--Readme.txt
local readme = io.open(destDir .. "readme.txt", "wt");
readme:write(string.format(
[===[
OpenGL Tutorials, version %s

This is a series of tutorials on using OpenGL to do graphical rendering.
The code for each tutorial is found in the "Tut *" directories. The code
alone is not enough information to understand what is going on. The actual
documentation is available in several forms.

The HTML form of the documentation can be found by openning the "index.html"
file. There are 3 PDF forms of the documentation. TutorialsComp.pdf is a PDF
that uses very thin margins; it is useful for display on computers (or
tablets). TutorialsPrint.pdf is a PDF designed for printing.
TutorialsKindle.pdf is a PDF that is sized specifically for the screen of the
Kindle 2.

The source of the documentation is found in the Documents directory. This
source documentation is in the DocBook 5 format. All other formats were
generated automatically from these source files.
]===], versionNum))
readme:close()

--Version.txt
local version = io.open(destDir .. "version.txt", "wt");
version:write(string.format(
[===[
OpenGL Tutorials.

Version %s
]===]
, versionNum))
version:close();

--Index.html
local index_html = io.open(destDir .. "index.html", "wt");
index_html:write(
[===[
<html>
<body>
<h1>OpenGL Tutorials</h1>
<p><a href="html/index.html">HTML Tutorials</a></p>
</body>
</html>
]===]
)
index_html:close();








