--[[
This script downloads all of the external dependencies and unzips them to the proper directory. You will need to have 7z in your path to run this, as well as the LuaSocket, UFS, and EX Lua modules.
]]

local io = require("io")
local http = require("socket.http")
local ltn12 = require("ltn12")
require("ex")
require "ufs"
require "_FindFileInPath"


local externals =
{
	{
		"OpenGL SDK 0.4.2",		--The name of the component.
		"glsdk",				--The output directory to copy the component's data.
		"glsdk.7z",				--The filename that will be created in the download director.
		"glsdk_0.4.2",			--If the zip file has a base directory, then name it here. If it doesn't, then just use ""
		[==[https://downloads.sourceforge.net/project/glsdk/GLSDK%200.4.0/glsdk_0.4.2.7z?r=&ts=1329264406&use_mirror=iweb]==],
		
		--Files/ to delete, relative to the output directory of this component.
		{
			"docs",
			"examples",
			"glfw",
			"freeglut/VisualStudio2008",
			"freeglut/VisualStudio2008Static",
			"glm/bench",
			"glm/doc",
			"glm/test",
			"glm/util",
			"README.html",
		}
	},
}

local zipFullName = FindFileInPath("7z.exe");

if(zipFullName == nil) then
	return
end

local function RecursiveCopy(fromDir, toDir)
	print(tostring(fromDir), tostring(toDir));
	for entry in ufs.directory_iterator(fromDir) do
		local es = entry:status();
		local srcPath = entry:path();
		
		local pathDestName = toDir / srcPath:filename();
		if(ufs.is_regular_file(es)) then
			ufs.copy_file(srcPath, pathDestName, ufs.copy_option_overwrite_if_exists);
		end
		
		if(ufs.is_directory(es)) then
			local bDidCreate, ec = ufs.create_directory(pathDestName);
			RecursiveCopy(srcPath, pathDestName);
		end
	end
end

local decompressDir = ".\\extract";
ufs.create_directory(ufs.path(decompressDir));

for i, ext in ipairs(externals) do
	print("Downloading: " .. ext[1]);
	
	local compressFile = decompressDir .. "\\" .. ext[3];
	
	local hFile = assert(io.open(compressFile, "wb"));
	http.request {url = ext[5], sink = ltn12.sink.file(hFile)}
	
	local unzipDir = decompressDir .. "\\dir" .. i;
	ufs.create_directory(ufs.path(unzipDir));
	
	print("Extracting: " .. ext[1]);
	if(ext[3]:match("%.tar%.gz$")) then
		local proc = ex.spawn(zipFullName, {
			args={"x", "-y", "-o" .. decompressDir, compressFile},
			});
			
		local tarFile = compressFile:match("(.+)%.gz$");
		proc:wait(proc);

		proc = ex.spawn(zipFullName, {
			args={"x", "-y", "-o" .. unzipDir, tarFile},
			});
		proc:wait(proc);
	else
		proc = ex.spawn(zipFullName, {
			args={"x", "-y", "-o" .. unzipDir, compressFile},
			});
		proc:wait(proc);
	end
	
	print("Copying: " .. ext[1]);
	local pathSrc = ufs.path(unzipDir);
	if(#ext[4] ~= 0) then
		pathSrc = pathSrc / ext[4]
	end

	--Copy to final directory.
	local pathOut = ufs.path(".\\" .. ext[2]);
	ufs.create_directory(pathOut);
	RecursiveCopy(pathSrc, pathOut);
	
	--Remove extraneous files/directories
	if(ext[6]) then
		for i, filename in ipairs(ext[6]) do
			local pathFile = pathOut / filename;
			print("deleting:", pathFile);
			ufs.remove_all(pathFile);
		end
	end
end

ufs.remove_all(ufs.path(decompressDir));


