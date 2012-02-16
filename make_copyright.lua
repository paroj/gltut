--The current directory should be the base SDK directory.

require "lfs"
require "ufs"

dofile("file_copyright_info.lua")

local alwaysIgnorePattern =
{
	"rapidxml.*%.hpp$",
}

local function CopywriteFile(filename)

	for i, ignore in ipairs(alwaysIgnorePattern) do
		if(filename:match(ignore)) then
			return
		end
	end

	local hInFile = io.open(filename, "rt");
	local fileData = hInFile:read("*a");
	hInFile:close();

	local hOutFile = io.open(filename, "wt");
	if(filename:match("%.c$") or filename:match("%.h$")) then
		hOutFile:write("/** ", copywriteText, " **/\n");
		hOutFile:write("/** ", licenseText, " **/\n");
	elseif(filename:match("%.cpp$") or filename:match("%.hpp$")) then
		hOutFile:write("//", copywriteText, "\n");
		hOutFile:write("//", licenseText, "\n");
	else
		--???
	end
	hOutFile:write("\n\n", fileData);
	hOutFile:close();
end

local searchPathsToMarkup =
{
	"Test",
	"framework",
}

local acceptedExtensions = {"cpp", "c", "h", "hpp"}

local function CopywriteDirectory(testPath)
	local pathBase = ufs.path(testPath);
	for file in lfs.dir(testPath) do
		for i, testExt in ipairs(acceptedExtensions) do
			if(file:match("%." .. testExt .. "$")) then
				CopywriteFile(tostring(pathBase / file));
				break;
			end
		end
	end
end

local baseDir = ...;
baseDir = baseDir or ".";
local pathBaseDir = ufs.path(baseDir)

for i, testPath in ipairs(searchPathsToMarkup) do
	testPath = tostring(pathBaseDir / testPath)
	local mode = lfs.attributes(testPath, "mode");
	if(mode == "directory") then
		CopywriteDirectory(testPath)
	elseif(mode == "file") then
		CopywriteFile(testPath);
	else
		print(testPath, "Is a:", mode);
	end
end

local dirPatterns =
{
	"^Tut %d%d",
}

for testPath in lfs.dir(baseDir) do
	local mode = lfs.attributes(testPath, "mode");
	if(mode == "directory") then
		for i, pattern in ipairs(dirPatterns) do
			if(testPath:match(pattern)) then
				CopywriteDirectory(tostring(pathBaseDir / testPath))
			end
		end
	end
end



