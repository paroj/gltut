--[[This file exposes a function that will write a Lua-based spec file. It takes a destination
file and table of 3 files:

-glspec: the gl.spec file.
-enumext: the enumext.spec file.
-gltm: the gl.tm file.

The destination file is a lua file that, when "dofile" is run on it, returns the table. The table
is formatted as follows:

- extensions: A table formatted as in ExtractExts.
- enumerations: A table formatted as in ExtractEnums.
- typemap: A table formatted as in ExtractTypes.
- funcData: A table formatted as in ExtractFuncs.
]]

require "_ExtractExts"
require "_ExtractEnums"
require "_ExtractTypes"
require "_ExtractFuncs"
require "_TableWriter"
require "_util"


function ExtractSpecsToFile(outFilename, inputFiles, clipPrefix)
	local extractedData = {};
	
	local hFile = io.open(GetSpecFilePath() .. inputFiles.enumext, "r");
	if(not hFile) then
		print(string.format("Could not open enumext file: '%s'", inputFiles.enumext));
		return;
	end
	extractedData.extensions = ExtractExts(hFile, clipPrefix);
	hFile:close();

	hFile = io.open(GetSpecFilePath() .. inputFiles.enumext, "r");
	if(not hFile) then
		print(string.format("Could not open enumext file: '%s'", inputFiles.enumext));
		return;
	end
	extractedData.enumerations = ExtractEnums(hFile, clipPrefix);
	hFile:close();

	hFile = io.open(GetSpecFilePath() .. inputFiles.gltm, "r");
	if(not hFile) then
		print(string.format("Could not open gltm file: '%s'", inputFiles.gltm));
		return;
	end
	extractedData.typemap = ExtractTypes(hFile);
	hFile:close();

	hFile = io.open(GetSpecFilePath() .. inputFiles.glspec, "r");
	if(not hFile) then
		print(string.format("Could not open glspec file: '%s'", inputFiles.glspec));
		return;
	end
	extractedData.funcData = ExtractFuncs(hFile);
	hFile:close();
	
	hFile = io.open(GetSpecFilePath() .. outFilename, "w");
	if(not hFile) then
		print(string.format("Could not open the output file: '%s'", outFilename));
		return;
	end
	hFile:write("return ");
	WriteTable(hFile, extractedData);
	hFile:write(";\n");
	hFile:close();
end


