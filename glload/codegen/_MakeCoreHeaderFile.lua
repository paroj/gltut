--[[
The function MakeCoreHeaderFile will generate the core source file.

This file will contain all of the core function pointers (including core extensions) in a big struct. It also exposes a function that will set these function pointers from the default version of OpenGL.

The function is called "void [funcPrefix]eIntCoreInit();"

This exists to fix the "core function" problem. Windows, for examples, defines all of the 1.1 entrypoints as regular functions. Thus, calling wglGetProcAddress will not retrieve those functions. We must instead get pointers to those functions manually. They get put into this struct.

The above function will fill in the pointers that standard GL provides, while NULL-ing out things that aren't statically defined.

You MUST include a file that has all of the typedefs before including this file.
]]

require "_makeHelpers"
require "_util"

function MakeCoreHeaderFile(outFilename, specData, funcPrefix)
	local hFile = io.open(GetSourcePath() .. outFilename .. ".h", "w");
	if(not hFile) then
		print("Could not open the output file\"" .. GetSourcePath() .. outFilename .. "\".\n");
		return;
	end
	
	local defineName = string.upper(outFilename) .. "_H";

	hFile:write(GetFileIncludeGuardStart(defineName));
	hFile:write("\n");
	
	hFile:write(GetExternCStart());
	hFile:write("\n");
	
	hFile:write("\n");

	--Collect all of the appropriate functions.
	local funcList = Make.FetchAllCoreFunctions(specData);
	
	hFile:write(string.format("typedef struct %s_s\n", Make.GetCoreStructType(funcPrefix)));
	hFile:write("{\n");
	
	--Write out the struct values.
	for i, func in ipairs(funcList) do
		hFile:write(string.format("\tvoid *%s;\n",
			Make.GetCoreStructMemberName(func, funcPrefix)
		));
	end

	WriteForm(hFile, "}%s;\n", Make.GetCoreStructType(funcPrefix));
	hFile:write("\n");
	
	--Write the extern of the struct definition.
	hFile:write(string.format("extern %s %s;\n", Make.GetCoreStructType(funcPrefix),
		Make.GetCoreStructVarName(funcPrefix)));

	hFile:write("\n");
	
	WriteFormatted(hFile, "void %s();\n", Make.GetCoreInitFuncName(funcPrefix));
		
	hFile:write("\n");

	hFile:write(GetExternCEnd());
	hFile:write("\n");

	hFile:write(GetFileIncludeGuardEnd(defineName));
	hFile:write("\n");
	
	hFile:close();
end
