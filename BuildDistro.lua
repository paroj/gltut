--[[
Will automatically generate all files from the current sources.
Takes three parameters:
- The destination directory, as a relative directory. Will create it if it does not exist.
- The Mercurial revision number to archive to the destination directory.
- The version number of the tutorials.
]]--

require("ex")
require "ufs"
require "lfs"
require "_FindFileInPath"

local baseDir, hgChangelist, versionNum = ...

if(#({...}) ~= 3) then
	print("Not enough commandline parameters. You provided: " .. #({...}));
	print("Paramters:")
	print("\tDestination dir, relative to this path.")
	print("\tMercurial revision to archive.")
	print("\tVersion number of the SDK.")
	return
end

local buildDirname = "Tutorial " .. versionNum

lfs.mkdir(baseDir);
local pathDestDir = ufs.path(baseDir) / buildDirname;
local destDir = tostring(pathDestDir);
lfs.mkdir(destDir);

local pathCurrent = ufs.current_path();
local pathDest = pathCurrent / destDir;
local pathBase = pathCurrent / baseDir;

-------------------------------------------
-- Use the other Lua script to copy the HTML and PDFs to the destination.
local CopyWebsite = assert(loadfile("CopyWebsite.lua"));
CopyWebsite(destDir .. "\\html\\");

--Generate the PDF files.
local pdfOutDir = "..\\..\\" .. destDir .. "\\"
local cwd = lfs.currentdir();
lfs.chdir("Documents\\Build");
local BuildPrintBW = assert(loadfile("BuildPrintBWFO.lua"));
BuildPrintBW(pdfOutDir);
local BuildKindleFO = assert(loadfile("BuildKindleFO.lua"));
BuildKindleFO(pdfOutDir);
local BuildComputerFO = assert(loadfile("BuildComputerFO.lua"));
BuildComputerFO(pdfOutDir);
lfs.chdir(cwd);

------------------------------------------
-- Use Mercurial to get a version in the destination directory.
local clone = [[hg archive -r "%s" "%s"]];
clone = clone:format(hgChangelist, destDir);

print(clone);
os.execute(clone);

---------------------------------------------------------------
-- Install the dependencies.
local luaFilename = "lua.exe"
local pathLua = ufs.path(FindFileInPath(luaFilename))
local luaDepScriptName = "get_externals.lua"

ufs.current_path(pathDest);

local depProc = ex.spawn(tostring(pathLua),
	{args={luaDepScriptName}});
depProc:wait(depProc);

---------------------------------------------------------------
-- Apply Copyright Info
local luaCopyScriptName = "make_copyright.lua"

if(pathLua:empty()) then
	print("Could not find Lua. Since this is a Lua script, that's kinda confusing...");
	return;
end

ufs.current_path(pathCurrent);

local copyProc = ex.spawn(tostring(pathLua),
	{args={luaCopyScriptName, tostring(pathDest)}});
copyProc:wait(copyProc);

-------------------------------------------
-- Generate the ancillary files

--Readme.txt
local readme = io.open(destDir .. "\\readme.txt", "wt");
readme:write(string.format(
[===[
OpenGL Tutorials, version %s

This is a series of tutorials on using OpenGL to do graphical rendering.
The code for each tutorial is found in the "Tut *" directories. The code
alone is not enough information to understand what is going on. The actual
documentation is available in several forms.

The HTML form of the documentation can be found by opening the "index.html"
file. There are 3 PDF forms of the documentation. TutorialsComp.pdf is a PDF
that uses very thin margins; it is useful for display on computers (or
tablets). TutorialsPrintBW.pdf is a PDF designed for printing on a black-and-white
printer. TutorialsKindle.pdf is a PDF that is sized specifically for the screen
of the Kindle 2.

The License.txt file contains the licensing information for the materials distributed in these tutorials.
]===], versionNum))
readme:close()

--Version.txt
local version = io.open(destDir .. "\\version.txt", "wt");
version:write(string.format(
[===[
OpenGL Tutorials.

Version %s
]===]
, versionNum))
version:close();

--Index.html
local index_html = io.open(destDir .. "\\index.html", "wt");
index_html:write(
[===[
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<meta http-equiv="Content-Type" content="text/xhtml;charset=UTF-8"/>
	<meta HTTP-EQUIV="REFRESH" content="0; url=html/index.html"/>
</head>
<body>
</body>
]===]
)
index_html:close();

------------------------------------------------------------
-- Delete select files from the destination location.
local toDelete =
{
	--files
	--Distro building
	"BuildDistro.lua", "CopyWebsite.lua",
	"_FindFileInPath.lua", "file_copyright_info.lua", "make_copyright.lua",
	--Mercurial
	".hgignore", ".hgtags", ".hg_archival.txt",
	--directories
	"glimg\\Test", "glload\\Test", "glload\\codegen",
	"Documents", "Meshes",
}


for i, filename in ipairs(toDelete) do
	local pathFile = pathDest / filename;
	print("deleting:", pathFile);
	ufs.remove_all(pathFile);
end

------------------------------------------------------------
-- Create Zip archive of the distro.
local szFilename = "7z.exe"
local archiveName = buildDirname .. ".7z"
local pathSZ = ufs.path(FindFileInPath(szFilename))

if(pathSZ:empty()) then
	print("Could not find 7zip.");
	return;
end

ufs.current_path(pathBase);

local zipProc = ex.spawn(tostring(pathSZ),
	{args={"a", "-r", archiveName, buildDirname}});
zipProc:wait(zipProc);

------------------------------------------------------------
-- Destroy the directory.
ufs.remove_all(pathDest);









