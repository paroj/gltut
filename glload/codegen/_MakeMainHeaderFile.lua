--[[
MakeMainHeaderFile will generate the internal header file that GLE uses to load 
the extension functions for this spec data. This header exposes the following:

== Mapping table and size ==

The mapping table structure is defined in "gll_util.h". This variable is an array of these structs, one per extension. The entry structure contains a string name of the extension, a pointer to an int that represents the extension variable, and a function pointer (possibly NULL) to the function loader for that extension.

The function loader is a function that takes no parameters and returns an integer. The return value is GL_TRUE if all of the function pointers are loaded, and GL_FALSE otherwise.

Naturally, there will also be a size variable exposed.

== Extension clear function ==

This function, "[funcPrefix]eIntClear()" will clear all of the extension variables.

== Version/profile entrypoints ==

The parameter, "VersionFunc" should be an interator function that returns 2 parameters: a string containing the version to generate, and a string containing the profile. This is either "core" or "compatibility". For each value returned, there will be one function prototype generated.

The functions are defined as follows:

int [funcPrefix]eIntLoad_Version_[major]_[minor][profile]();

== Base entrypoints and data ==

If you provide this function with a "baseData" field, then it will generate an additional file called <filename>_base.h. This additional file will contain a number of OpenGL enumerators and function pointers. This file will also have a function called: "[funcPrefix]eIntLoad_BaseFuncs". That function will load only the function pointers for the base functions.

The baseData field should be structured like:

* enums: a list of enumerator names.
* funcs: a list of function names.
* bFuncsAreCore: true if the names in funcs are core functions. False if extension functions.
* preceedData: a list of strings to write at the beginning of the file.
* enumPrefix: the prefix for enumerator names.
]]

require "_makeHelpers"
require "_util"

local function WriteExtFuncLoaderPrototype(hFile, extName, funcPrefix)
	hFile:write(Make.GetExtLoaderFuncPrototype(extName, funcPrefix));
	hFile:write("\n");
end

local function WriteCoreLoaderPrototype(hFile, version, profile, funcPrefix)
	hFile:write(Make.GetCoreLoaderFuncPrototype(version, profile, funcPrefix));
	hFile:write("\n");
end

local function WriteBaseDataValues(hFile, specData, funcPrefix, baseData)
	for i, enumName in ipairs(baseData.enums) do
		hFile:write(Make.GetEnumerator(
			specData.enumtable[enumName], specData.enumTable, baseData.enumPrefix));
		hFile:write("\n");
	end
	
	hFile:write("\n");
	
	for i, funcName in ipairs(baseData.funcs) do
		--find the function.
		local func = nil;
		for i, funcTest in ipairs(specData.funcData.functions) do
			if(funcTest.name == funcName) then
				func = funcTest;
				break;
			end
		end
		
		if(func) then
			if(baseData.bFuncsAreCore) then
				WriteForm(hFile, "%s\n%s\n%s\n",
					Make.GetFuncTypedef(func, funcPrefix, specData.typemap),
					Make.GetCoreFuncExternPtr(func, funcPrefix, specData.typemap),
					Make.GetCoreFuncPtrDefine(func, funcPrefix, specData.typemap));
			else
				WriteForm(hFile, "%s\n%s\n",
					Make.GetFuncTypedef(func, funcPrefix, specData.typemap),
					Make.GetFuncExternPtr(func, funcPrefix, specData.typemap));
			end
		end
	end
end

function MakeMainHeaderFile(outFilename, specData, funcPrefix, VersionFunc, baseData)
	local hFile = io.open(GetSourcePath() .. outFilename .. ".h", "w");
	if(not hFile) then
		print("Could not open the output file\"" .. GetSourcePath() .. outFilename .. "\".\n");
		return;
	end
	
	local defineName = string.upper(outFilename) .. "_H";
	
	hFile:write(GetFileIncludeGuardStart(defineName));
	hFile:write("\n");

	hFile:write("#include \"gll_util.h\"\n");
	hFile:write("\n");

	hFile:write(GetExternCStart());
	hFile:write("\n");
	
	hFile:write("\n");
	
	--Write the extension mapping table.
	hFile:write(Make.GetMapTableExtern(funcPrefix));
	hFile:write("\n");
	hFile:write(Make.GetMapTableSizeExtern(funcPrefix));
	hFile:write("\n");

	hFile:write("\n");
	
	--Write the clear function.
	hFile:write(Make.GetClearFunctionDecl(funcPrefix));
	hFile:write("\n");

	hFile:write("\n");

	--Write the version-based loading funcs.
	if(VersionFunc) then
		for version, profile in VersionFunc do
			WriteCoreLoaderPrototype(hFile, version, profile, funcPrefix);
		end
	end

	hFile:write("\n");
	
	--Write the baseData, if there.
	if(baseData) then
    	local hFile = io.open(GetSourcePath() .. outFilename .. "_base.h", "w");
	    local defineName = string.upper(outFilename) .. "_BASE_H";
	
	    hFile:write(GetFileIncludeGuardStart(defineName));
	    hFile:write("\n");
	    
	    hFile:write(GetExternCStart());
	    hFile:write("\n");

		if(baseData.preceedData) then
			for i, preceed in ipairs(baseData.preceedData) do
				hFile:write(preceed);
				hFile:write("\n");
			end
		end
		
		for i, passthru in ipairs(specData.funcData.passthru) do
			hFile:write(passthru);
			hFile:write("\n");
		end
		hFile:write("\n");
	
		WriteBaseDataValues(hFile, specData, funcPrefix, baseData);
		hFile:write("\n");
		WriteForm(hFile, "void %s();\n", Make.GetBaseLoaderFuncName(funcPrefix));
		hFile:write("\n");

		if(baseData.preceedData and baseData.preceedData.footer) then
			for i, footer in ipairs(baseData.preceedData.footer) do
				hFile:write(footer);
				hFile:write("\n");
			end
		end
	    hFile:write("\n");
	    hFile:write(GetExternCEnd());
	    hFile:write("\n");
    	hFile:write(GetFileIncludeGuardEnd(defineName));
	    hFile:write("\n");

		hFile:close();
	end
	
	hFile:write(GetExternCEnd());
	hFile:write("\n");
	
	if(baseData and baseData.funcs) then
	end

	
	hFile:write(GetFileIncludeGuardEnd(defineName));

	hFile:close();
end

