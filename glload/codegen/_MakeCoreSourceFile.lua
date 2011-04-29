--[[
The function MakeCoreSourceFile will generate the core source file.

The file will implement the function exposed by MakeCoreHeaderFile.

Because the implementation of this is platform-specific, there must be a way to determine which versions are available in the core gl.h file. To do this, you provide a special parameter: platformDef.

The platformDef parameter is an array of platform definitions. Each entry in the array has the following:

* define: the string name of the #define that is used to control this.
* statements: a list of strings, each of which is a statement. These should be added towards the top of the file; they must include the standard gl.h.
* versions: a list of versions (in string form) that the included files define.
]]

require "_makeHelpers"
require "_util"


function MakeCoreSourceFile(outFilename, specData, funcPrefix, platformDef)
	local hFile = io.open(GetSourcePath() .. outFilename .. ".c", "w");
	if(not hFile) then
		print("Could not open the output file\"" .. GetSourcePath() .. outFilename .. ".c\".\n");
		return;
	end
	
	hFile:write([[#include <stdlib.h>
#include <string.h>
]]);

	hFile:write("\n");

	--Collect all of the appropriate functions.
	local funcList = Make.FetchAllCoreFunctions(specData);

	--Include the header file.
	hFile:write("#include \"" .. outFilename .. ".h\"\n");
	
	--Define the struct variable.
	hFile:write(string.format("%s %s;\n", Make.GetCoreStructType(funcPrefix),
		Make.GetCoreStructVarName(funcPrefix)));

	--Now, write the platform-specific statements.
	for i, platform in ipairs(platformDef) do
		if(platform.statements and #platform.statements ~= 0) then
			WriteFormatted(hFile, "#ifdef %s\n", platform.define);
			for j, statement in ipairs(platform.statements) do
				hFile:write(statement);
				hFile:write("\n");
			end
			WriteFormatted(hFile, "#endif //%s\n", platform.define);
		end
	end
	
	--Write the implementation of the function.
	hFile:write("\n");
	
	WriteFormatted(hFile, "void %s()\n", Make.GetCoreInitFuncName(funcPrefix));
	hFile:write("{\n");
	
	-- Pre-platform-specific.
	WriteFormatted(hFile, [[
	memset(&%s, 0, sizeof(%s));
]], Make.GetCoreStructVarName(funcPrefix), Make.GetCoreStructType(funcPrefix));
	
	-- Write platform-specifics: retrieving the function pointers.
	for i, platform in ipairs(platformDef) do
		if(platform.versions and #platform.versions ~= 0) then
			WriteFormatted(hFile, "#ifdef %s\n", platform.define);
			for j, strVersion in ipairs(platform.versions) do
				local testVersion = string.gsub(strVersion, "(%d+)%.(%d+)", "VERSION_%1_%2");
				local testVersionDep = testVersion .. "_DEPRECATED";
				for k, func in ipairs(funcList) do
					if((func.category == testVersion) or (func.category == testVersionDep)) then
						WriteFormatted(hFile, "\t%s.%s = (void*)%s;\n",
							Make.GetCoreStructVarName(funcPrefix),
							Make.GetCoreStructMemberName(func, funcPrefix),
							Make.GetFuncPtrNameStr(func, funcPrefix)
						)
					end
				end
			end
			WriteFormatted(hFile, "#endif //%s\n", platform.define);
		end
	end
	
	hFile:write("}\n");
	hFile:write("\n");

	hFile:close();
end
