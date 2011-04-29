--[[ The function, MakeExtHeaderFile, will create a header file containing the enums, extension
test values, and the list of function pointers.

It takes these parameters:
- the name of the output file. Without the path.
- the specData, as formatted by LoadLuaSpec.
- the prefix (without the underscore) to prepend to enumerators.
- the prefix to prepend to functions.
- a string representing the target GL version to export. If nil, gets everything.
- a boolean. If true, means that this should output only the core stuff.
- an array of strings to write to the front of the header file.
]]

require "_util"
require "_makeHelpers"

local function ProcessCoreVersion(hFile, core, specData, enumPrefix, funcPrefix,
									version, targetVersion, bIsCore)
	WriteFormatted(hFile, GetSectionHeading(string.format("Version: %s", version)));
	hFile:write("\n");
	
	local bDidWrite = false;
	for i, enum in ipairs(core.enums) do
		local bShouldWrite = true;
		if(bIsCore) then
			if(enum.removed and (tonumber(enum.removed) <= tonumber(targetVersion))) then
				bShouldWrite = false;
			end
		end
		
		--We'll write it as an extension
		if(enum.extension) then
			bShouldWrite = false;
			--TODO: Make this write something saying that it comes from the extension.
		end
		
		if(bShouldWrite) then
			hFile:write(Make.GetEnumerator(enum, specData.enumtable, enumPrefix));
			hFile:write("\n");
			bDidWrite = true;
		end
	end
	
	--Collate the functions we want to write.
	local funcs = {};
	for i, func in ipairs(core.funcs) do
		local bShouldWrite = true;
		if(bIsCore) then
			if(func.deprecated and
					(tonumber(func.deprecated) <= tonumber(targetVersion))) then
				bShouldWrite = false;
			end
		end
		
		--Exts don't start with "VERSION"; don't write extension
		--functions here. Write them in the extension
		if(func.category and not string.match(func.category, "^VERSION")) then
			bShouldWrite = false;
		end
		
		if(bShouldWrite) then
			table.insert(funcs, func);
		end
	end
	
	if(bDidWrite and #funcs ~= 0) then
		hFile:write("\n\n");
	end
	
	local bWroteAnything = bDidWrite;
	bDidWrite = false;
	
	--Write the typedefs.
	for i, func in ipairs(funcs) do
		bDidWrite = true;
		hFile:write(Make.GetFuncTypedef(func, funcPrefix, specData.typemap));
		hFile:write("\n");
	end
	
	if(bDidWrite) then
		hFile:write("\n");
	end
	
	--Write the function pointers.
	for i, func in ipairs(funcs) do
		bDidWrite = true;
		hFile:write(Make.GetCoreFuncExternPtr(func, funcPrefix, specData.typemap));
		hFile:write("\n");
		hFile:write(Make.GetCoreFuncPtrDefine(func, funcPrefix, specData.typemap));
		hFile:write("\n");
	end

	bWroteAnything = bDidWrite or bWroteAnything;

	if(bWroteAnything) then
		hFile:write("\n\n");
	end
end

local function ProcessExtension(hFile, ext, extName, specData, enumPrefix, funcPrefix)
	WriteFormatted(hFile, GetSectionHeading(string.format("Extension: %s_%s",
		enumPrefix, extName)));
	hFile:write("\n");
	
	--Write the enumerators.
	local bDidWrite = false;
	for i, enum in ipairs(ext.enums) do
		bDidWrite = true;
		hFile:write(Make.GetEnumerator(enum, specData.enumtable, enumPrefix));
		hFile:write("\n");
	end

	if(bDidWrite and #ext.funcs ~= 0) then
		hFile:write("\n\n");
	end
	
	local bWroteAnything = bDidWrite;
	bDidWrite = false;

	--Write the typedefs.
	local extDefine = nil;
	if(#ext.funcs > 0) then
	    --Write the #ifdef for the function pointers, so that they are only
	    --available if something hasn't defined over them.
	    extDefine = string.format("%s_%s", enumPrefix, extName);
	    hFile:write(string.format("#ifndef %s\n#define %s 1\n\n",
	        extDefine, extDefine));
	end
	for i, func in ipairs(ext.funcs) do
		bDidWrite = true;
		hFile:write(Make.GetFuncTypedef(func, funcPrefix, specData.typemap));
		hFile:write("\n");
	end
	
	if(bDidWrite) then
		hFile:write("\n");
	end
	
	--Write the function pointers.
	for i, func in ipairs(ext.funcs) do
		bDidWrite = true;
		
		if(specData.coreexts[extName]) then
			hFile:write(Make.GetCoreFuncExternPtr(func, funcPrefix, specData.typemap));
			hFile:write("\n");
			hFile:write(Make.GetCoreFuncPtrDefine(func, funcPrefix, specData.typemap));
		else
			hFile:write(Make.GetFuncExternPtr(func, funcPrefix, specData.typemap));
		end
		hFile:write("\n");
	end
	
	if(extDefine) then
	    hFile:write(string.format("#endif /*%s*/", extDefine));
	end
	
	bWroteAnything = bDidWrite or bWroteAnything;

	if(bWroteAnything) then
		hFile:write("\n\n");
	end
end

function MakeExtHeaderFile(outFilename, specData, enumPrefix, funcPrefix,
							targetVersion, bIsCore, preceedData)
	local hFile = io.open(GetIncludePath() .. outFilename .. ".h", "w");
	if(not hFile) then
		print("Could not open the output file\"" .. GetIncludePath() .. outFilename .. "\".\n");
		return;
	end
	
	local defineName = string.upper(outFilename) .. "_H";
	
	hFile:write(GetFileIncludeGuardStart(defineName));
	hFile:write("\n");
	
	if(preceedData) then
		for i, preceed in ipairs(preceedData) do
			hFile:write(preceed);
			hFile:write("\n");
		end
	end
	
	--Write the passthru data.
	for i, passthru in ipairs(specData.funcData.passthru) do
		hFile:write(passthru);
		hFile:write("\n");
	end
	hFile:write("\n");

	hFile:write(GetExternCStart());
	hFile:write("\n");
	
	--Write all of the extension query variables.
	for i, extName in ipairs(specData.extensions) do
		hFile:write(Make.GetExtensionVarExtern(extName, funcPrefix));
		hFile:write("\n");
	end

	hFile:write("\n\n");

	--Process all of the cores, up to and including targetVersion.
	local coreVersions = dofile(GetDataFilePath() .. "listOfCoreVersions.lua");
	if(not targetVersion) then targetVersion = coreVersions[#coreVersions]; end;
	
	for i, version in ipairs(coreVersions) do
		if(tonumber(version) > tonumber(targetVersion)) then
			break;
		end

		if(specData.coredefs[version]) then
			ProcessCoreVersion(hFile, specData.coredefs[version], specData,
				enumPrefix, funcPrefix, version, targetVersion, bIsCore);
		end
	end
	
	hFile:write("\n\n");

	--Process all of the extensions.
	for extName, ext in sortPairs(specData.extdefs, CompLess) do
		ProcessExtension(hFile, ext, extName, specData, enumPrefix, funcPrefix);
	end
	
	
	hFile:write(GetExternCEnd());
	hFile:write("\n");
	
	if(preceedData and preceedData.footer) then
		for i, footer in ipairs(preceedData.footer) do
			hFile:write(footer);
			hFile:write("\n");
		end
	end
	
	hFile:write(GetFileIncludeGuardEnd(defineName));
	
	hFile:close();
end

