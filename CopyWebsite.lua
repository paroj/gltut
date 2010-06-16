require "lfs"

local outputDir = ...;
outputDir = outputDir or "website\\";

if(not lfs.attributes(outputDir)) then
	--Delete the directory.
	lfs.rmdir(outputDir);
end

lfs.mkdir(outputDir);

local mainDir = "Documents\\";

--Copy the html files.
local htmlDir = mainDir .. "web\\";
local command = string.format([[copy "%s*.html" "%s"]], htmlDir, outputDir);
print(command);
os.execute(command);

--Copy the .css file.
command = string.format([[copy "%schunked.css" "%s" ]], mainDir, outputDir);
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

