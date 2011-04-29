--[[
The function MakeMainSourceFile will generate the main source file. It will generate the definitions declared in the header.

It takes the parameters that MakeMainHeaderFile does, with the addition of enumPrefix, preceedData, and coreData.

preceedData is a list of strings to write after the initial includes.

The coreData can be nil or a table containing the following:

* file: the filename (no .h) of the core data header to load.

If there is no coreData, then the core loading functions will not try to get data from the core stuff.
]]

require "_makeHelpers"
require "_util"

-- Bad form, I know, but necessary.
local glob_HasCore = nil;

local function GetRemovedVersionList(specData)
	local depTable = {};
	
	for i, func in ipairs(specData.funcData.functions) do
		if(func.deprecated) then
			depTable[func.deprecated] = true;
		end
	end
	
	local ret = {};
	
	for version, bool in pairs(depTable) do
		table.insert(ret, version);
	end
	
	table.sort(ret, function(lhs, rhs) return tonumber(lhs) < tonumber(rhs) end);
	
	return ret;
end

local function WriteTestFunc(hFile)
	hFile:write([[
#include <stddef.h>	
	
static int TestPointer(const void *pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;
	
	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
	
	return 1;
}

]]);
end

local function GetExtLoaderName(extName, funcPrefix)
	return string.format("%seIntLoad_%s", funcPrefix, extName);
end

local function WriteExtVarClear(hFile, specData, funcPrefix)
	WriteFormatted(hFile, "void %s()\n", Make.GetClearFunctionName(funcPrefix));
	hFile:write("{\n");
	
	for i, extName in ipairs(specData.extensions) do
		WriteFormatted(hFile, "\t%s = 0;\n",
			Make.GetExtensionVarName(extName, funcPrefix));
	end
	
	hFile:write("}\n");
end

local function WriteFuncPointers(hFile, ext, extName, specData, enumPrefix, funcPrefix)
	if(#ext.funcs == 0) then return; end;
	
    local extDefine = string.format("%s_%s", enumPrefix, extName);
    hFile:write(string.format("#ifndef %s\n", extDefine));

	--Write the typedefs.
	for i, func in ipairs(ext.funcs) do
		hFile:write(Make.GetFuncTypedef(func, funcPrefix, specData.typemap));
		hFile:write("\n");
	end
	
	hFile:write("\n");
	
	--Write the function pointers.
	for i, func in ipairs(ext.funcs) do
		if(specData.coreexts[extName]) then
			hFile:write(Make.GetCoreFuncPtr(func, funcPrefix, specData.typemap));
		else
			hFile:write(Make.GetFuncPtr(func, funcPrefix, specData.typemap));
		end
		hFile:write("\n");
	end

    hFile:write(string.format("#endif /*%s*/\n", extDefine));
end

local function WriteFuncLoad(hFile, func, funcPrefix, bIsCoreExt)
	local funcPtrName = nil;
	
	if(bIsCoreExt) then
		funcPtrName = Make.GetCoreFuncPtrNameStr(func, funcPrefix);
	else
		funcPtrName = Make.GetFuncPtrNameStr(func, funcPrefix);
	end
	
	WriteForm(hFile, "\t%s = (%s)gleIntGetProcAddress(\"%s\");\n",
		funcPtrName,
		Make.GetFuncTypedefNameStr(func, funcPrefix),
		Make.GetFuncPtrNameStr(func, funcPrefix)
	);
	
	WriteForm(hFile, "\tif(!TestPointer((const void*)%s)) bIsLoaded = 0;\n", funcPtrName);
end

local function WriteLoaderFunc(hFile, ext, extName, specData, funcPrefix, enumPrefix)
	if(not ext.funcs or #ext.funcs == 0) then return; end;
	
	WriteForm(hFile, "static int %s()\n", GetExtLoaderName(extName, funcPrefix));
	hFile:write("{\n");
	
	hFile:write("\tint bIsLoaded = 1;\n");

	local bIsCoreExt = specData.coreexts[extName] ~= nil;
	
    local extDefine = string.format("%s_%s", enumPrefix, extName);
    hFile:write(string.format("#ifndef %s\n", extDefine));
	
	for i, func in ipairs(ext.funcs) do
		WriteFuncLoad(hFile, func, funcPrefix, bIsCoreExt)
	end
	
    hFile:write(string.format("#endif /*%s*/\n", extDefine));

	hFile:write("\treturn bIsLoaded;\n");
	
	hFile:write("}\n");
end

local function WriteMappingTable(hFile, specData, enumPrefix, funcPrefix)
	WriteForm(hFile, "StrToExtMap %s[] = {\n", Make.GetMapTableName(funcPrefix));
	
	local iNumEntries = 0;
	
	for extName, ext in sortPairs(specData.extdefs, CompLess) do
		local extLoadFuncName = "NULL";
		
		if(ext.funcs and #ext.funcs ~= 0) then
			extLoadFuncName = GetExtLoaderName(extName, funcPrefix);
		end
		
		WriteForm(hFile, "\t{\"%s_%s\", &%s, %s},\n",
			enumPrefix,
			extName,
			Make.GetExtensionVarName(extName, funcPrefix),
			extLoadFuncName
		);
		
		iNumEntries = iNumEntries + 1;
	end
	
	hFile:write("};\n\n");
	
	--Write the variable that stores the size of the mapping table.
	hFile:write(Make.GetMapTableSizeDef(iNumEntries, funcPrefix));
	hFile:write("\n");
end

local function GetStaticCoreRemovedSuffix(removedVersion)
	if(removedVersion) then
		return string.gsub(removedVersion, "(%d+)%.(%d+)", "_Version_%1_%2");
	else
		return "_Base";
	end
end

local function GetStaticCoreVersionSuffix(version)
	return string.gsub(version, "(%d+)%.(%d+)", "_%1_%2");
end

local function GetStaticCoreName(version, funcPrefix, removedVersion)
	return string.format("%seIntLoadCore%s%s", funcPrefix,
		GetStaticCoreVersionSuffix(version),
		GetStaticCoreRemovedSuffix(removedVersion));
end


local bHasCoreStruct = false;

local function WriteCoreFuncLoad(hFile, func, funcPrefix)
	local funcPtrName = nil;
	
	funcPtrName = Make.GetCoreFuncPtrNameStr(func, funcPrefix);
	
	WriteForm(hFile, "\t%s = (%s)gleIntGetProcAddress(\"%s\");\n",
		funcPtrName,
		Make.GetFuncTypedefNameStr(func, funcPrefix),
		Make.GetFuncPtrNameStr(func, funcPrefix)
	);
	
	WriteForm(hFile, "\tif(!TestPointer((const void*)%s))\n", funcPtrName);
	hFile:write("\t{\n");
	WriteForm(hFile, "\t\t%s = (%s)%s.%s;\n", funcPtrName,
		Make.GetFuncTypedefNameStr(func, funcPrefix),
		Make.GetCoreStructVarName(funcPrefix),
		Make.GetCoreStructMemberName(func, funcPrefix));
	WriteForm(hFile, "\t\tif(!%s) bIsLoaded = 0;\n", funcPtrName);
	hFile:write("\t}\n");
end

--If there is a nextVersion, then we should write functions
--that were deprecated <= that version. If there is no next
--version, then we should contain functions that are *not* deprecated ever.
local function CanWriteFunc(func, nextVersion)
	if(nextVersion) then
		--if(thingy) then print(func.name); end;
		if(func.deprecated and tonumber(func.deprecated) <= tonumber(nextVersion)) then
			return true;
		end
	else
		if(not func.deprecated) then
			return true;
		end
	end
	
	return false;
end

local function WriteStaticCoreLoaders(hFile, specData, enumPrefix, funcPrefix, removedVersion,
										nextVersion)
	for coreVersion, core in sortPairs(specData.coredefs, CompLess) do
		if(not removedVersion or (tonumber(removedVersion) > tonumber(coreVersion))) then
			WriteForm(hFile, "static int %s()\n",
				GetStaticCoreName(coreVersion, funcPrefix, removedVersion));
			hFile:write("{\n");
			
			local iVersion = tonumber(coreVersion);
			
			local theNextVersion = nil;
			local initValue = "1";
			if(nextVersion and iVersion < tonumber(nextVersion)) then
				initValue = GetStaticCoreName(coreVersion, funcPrefix, nextVersion) .. "()";
				theNextVersion = nextVersion;
			end

			WriteForm(hFile, "\tint bIsLoaded = %s;\n", initValue);

			local iRemovedVersion = nil;
			if(removedVersion) then iRemovedVersion = tonumber(removedVersion); end;
		
			if(not iRemovedVersion or (tonumber(coreVersion) <= iRemovedVersion)) then
				for i, func in ipairs(core.funcs) do
					if(CanWriteFunc(func, theNextVersion)) then
						WriteCoreFuncLoad(hFile, func, funcPrefix);
					end
				end
			end
			
			for extName, coreext in pairs(specData.coreexts) do
				if(coreVersion == coreext.version and specData.extdefs[extName]) then
					local bDidWrite = false;
					for i, func in ipairs(specData.extdefs[extName].funcs) do
						if(CanWriteFunc(func, theNextVersion)) then
							bDidWrite = true;
							WriteCoreFuncLoad(hFile, func, funcPrefix);
						end
					end
					
					--Set the extension variable for this core extension.
					if(bDidWrite) then
						WriteForm(hFile, "\t%s = 1;\n",
							Make.GetExtensionVarName(extName, funcPrefix));
					end
				end
			end
			
			hFile:write("\treturn bIsLoaded;\n");
			hFile:write("}\n");
			hFile:write("\n");
		end
	end
end

local function WriteCoreLoaderFunc(hFile, specData, funcPrefix, removedVersionList,
									version, profile)
	hFile:write(Make.GetCoreLoaderFuncDef(version, profile, funcPrefix));
	hFile:write("\n");
	hFile:write("{\n");
	
	hFile:write("\tint bIsLoaded = 1;\n");
	
	WriteForm(hFile, "\t%s();\n", Make.GetClearFunctionName(funcPrefix));
	WriteForm(hFile, "\t%s();\n", Make.GetCoreInitFuncName(funcPrefix));
	
	local lastVersion = removedVersionList[#removedVersionList];
	
	local iVersion = tonumber(version);
	for coreVersion, core in sortPairs(specData.coredefs, CompLess) do
		if(tonumber(coreVersion) <= iVersion) then
			local removedVersion = nil;
			if(profile == "core" and iVersion > 3.0 and tonumber(coreVersion) < tonumber(lastVersion)) then
				removedVersion = lastVersion;
			end
			
			WriteForm(hFile, "\tif(!%s()) bIsLoaded = 0;\n",
				GetStaticCoreName(coreVersion, funcPrefix, removedVersion));
		end
	end

	hFile:write("\n");
	hFile:write("\treturn bIsLoaded;\n");
	hFile:write("}\n");
end

local function WriteCoreFuncPtrs(hFile, specData, enumPrefix, funcPrefix)
	for coreVersion, core in sortPairs(specData.coredefs, CompLess) do
		for i, func in ipairs(core.funcs) do
			hFile:write(Make.GetFuncTypedef(func, funcPrefix, specData.typemap));
			hFile:write("\n");
			hFile:write(Make.GetCoreFuncPtr(func, funcPrefix, specData.typemap));
			hFile:write("\n");
		end
	end
	
	hFile:write("\n");
end

local function WriteBaseLoaders(hFile, specData, funcPrefix, baseData)
	WriteForm(hFile, "void %s()\n", Make.GetBaseLoaderFuncName(funcPrefix));
	hFile:write("{\n");
	hFile:write("\tint bIsLoaded = 1; //Unimportant here.\n");
	
	if(bHasCoreStruct) then
		WriteForm(hFile, "\t%s();\n", Make.GetCoreInitFuncName(funcPrefix));
	end

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
				WriteCoreFuncLoad(hFile, func, funcPrefix);
			else
				WriteFuncLoad(hFile, func, funcPrefix, false);
			end
		end
	end

	hFile:write("}\n");
end


function MakeMainSourceFile(outFilename, specData, enumPrefix, funcPrefix, VersionFunc,
							preceedData, baseData, coreData)
	if(coreData) then bHasCoreStruct = true; else bHasCoreStruct = false; end;
							
	local hFile = io.open(GetSourcePath() .. outFilename .. ".c", "w");
	if(not hFile) then
		print("Could not open the output file\"" .. GetSourcePath() .. outFilename .. ".c\".\n");
		return;
	end
	
	hFile:write([[#include <stdlib.h>
#include <string.h>
]]);
	WriteFormatted(hFile, "#include \"%s.h\"\n", outFilename);
	if(coreData) then
		WriteFormatted(hFile, "#include \"%s.h\"\n", coreData.file);
	end
	
	hFile:write("\n");
	
	--Write the preceeding data.
	if(preceedData) then
		for i, preceed in ipairs(preceedData) do
			hFile:write(preceed);
			hFile:write("\n");
		end
	end
	
	--Write a function to test function pointers.
	WriteTestFunc(hFile);
	
	--Write the passthru data.
	for i, passthru in ipairs(specData.funcData.passthru) do
		hFile:write(passthru);
		hFile:write("\n");
	end
	hFile:write("\n");

	hFile:write(dofile(GetDataFilePath() .. "getProcAddress.lua"));
	hFile:write("\n");
	
	--Write the extension variables.
	for i, extName in ipairs(specData.extensions) do
		hFile:write(Make.GetExtensionVar(extName, funcPrefix));
		hFile:write("\n");
	end

	hFile:write("\n\n");

	--Write the function that clears the extension variables.
	WriteExtVarClear(hFile, specData, funcPrefix);
	hFile:write("\n\n");
	
	--Write function pointers and the loading function for each extension.
	for extName, ext in sortPairs(specData.extdefs, CompLess) do
		WriteFuncPointers(hFile, ext, extName, specData, enumPrefix, funcPrefix);
		hFile:write("\n");
		WriteLoaderFunc(hFile, ext, extName, specData, funcPrefix, enumPrefix);
	end
	
	--Write the mapping table definition.
	WriteMappingTable(hFile, specData, enumPrefix, funcPrefix);
	
	hFile:write("\n");
	
	--Write the function pointer definitions for all core versions, whether removed or not.
	WriteCoreFuncPtrs(hFile, specData, enumPrefix, funcPrefix);
	
	--Write the core function loaders.
	if(VersionFunc) then
		local removedVersionList = GetRemovedVersionList(specData);
		
		for i, version in ripairs(removedVersionList) do
			WriteStaticCoreLoaders(hFile, specData, enumPrefix, funcPrefix, version,
				removedVersionList[i+1]);
		end

		WriteStaticCoreLoaders(hFile, specData, enumPrefix, funcPrefix, nil, removedVersionList[1]);

		--For each version/profile combo, write loaders for them.
		for version, profile in VersionFunc do
			WriteCoreLoaderFunc(hFile, specData, funcPrefix, removedVersionList, version, profile);
			hFile:write("\n");
		end
	end

	hFile:write("\n");
	
	--Write the base loaders, if any.
	if(baseData) then
		WriteBaseLoaders(hFile, specData, funcPrefix, baseData);
	end
	

	hFile:close();
end
