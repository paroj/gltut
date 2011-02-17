require "lfs"

local outputDir = ...;
outputDir = outputDir or "website\\";

if(not lfs.attributes(outputDir)) then
	--Delete the directory.
	lfs.rmdir(outputDir);
end

lfs.mkdir(outputDir);

local mainDir = "Documents\\";

--Generate the HTML files to the output directory.
local cwd = lfs.currentdir();
lfs.chdir(mainDir .. "Build\\");
local BuildWebsite = assert(loadfile("BuildWebsite.lua"));
BuildWebsite(cwd .. "\\" .. outputDir);
lfs.chdir(cwd);

--Copy the html files.
--[=[
local htmlDir = mainDir .. "web\\";
local command = string.format([[xcopy "%s*" "%s" /s /c /q /r /y]], htmlDir, outputDir);
print(command);
os.execute(command);
]=]

--Copy the .css file.
local cssFilename = "chunked.css";
command = string.format([[copy "%s%s" "%s" ]], mainDir, cssFilename, outputDir);
print(command);
os.execute(command);

local function DoesDirHavePattern(theDir, ...)
	local patterns = {...};
	for dir in lfs.dir(theDir) do
		for i, pattern in ipairs(patterns) do
			if(dir:match(pattern)) then return true end
		end
	end
	
	return false;
end

--Copy the images.
for dir in lfs.dir(mainDir) do
	local sourceDir = mainDir .. dir;
	if(lfs.attributes(sourceDir, "mode") == "directory" and dir ~= "." and dir ~= "..") then
		if(DoesDirHavePattern(sourceDir, "%.svg$", "%.png$")) then
			local destDir = outputDir .. dir;
			lfs.mkdir(destDir);
			
			command = string.format([[copy "%s\*.svg" "%s" ]], sourceDir, destDir);
			print(command);
			os.execute(command);
			
			command = string.format([[copy "%s\*.png" "%s" ]], sourceDir, destDir);
			print(command);
			os.execute(command);
		end
	end
end

--Copy the .css file to all directories in the destination.
for dir in lfs.dir(outputDir) do
	if(lfs.attributes(outputDir .. dir, "mode") == "directory" and dir ~= "." and dir ~= "..") then
		command = string.format([[copy "%s%s" "%s"]], mainDir, cssFilename, outputDir .. dir);
		print(command);
		os.execute(command);
	end
end


