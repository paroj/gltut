--[[
The function, LoadLuaSpec exposed here will load a spec.lua file. It takes a filename
pointing to a spec.lua file.

This function will also add some features to the object before returning it.

The format will be as defined in ConvertAllSpecFilesToLua, except for the following:

- extdefs: This is a table of extensions, indexed by extension name.
	Each entry contains:
-- enums: An array of enumerators. These enumerators are the entries in the main enum array.
-- funcs: An array of functions. These functions are the entries in the main funcData array.
- coredefs: This is a table of core versions, indexed by version name string
	"1.1" is the first.
-- enums: An array of enumerators. These enumerators are the entries in the main enum array.
-- funcs: An array of functions. These functions are the entries in the main funcData array.
- enumtable: A table of enumerators, indexed by their names.
- coreexts: A table of core extensions, indexed by extension name. The value of these entries are:
-- name: The core extension's name.
-- version: the version that extension became core in. The version is a string.


All enumerators and functions are found in one of these two lists. Some of them are in both.

Other changes are:
- All functions that would have the 1.0 version have it changed to 1.1. This makes the data match the enums.
- The "void" type in the typemap maps to "void".
- Fixes for certain extensions. Certain extensions are non-core, but the enums and functions
	have no suffixes as if they were core.
]]

local listOfCoreVersions = dofile("data/listOfCoreVersions.lua");

local listOfNonCoreFixes = 
{
	"ARB_sample_shading",
	"ARB_draw_buffers_blend",
	"ARB_texture_cube_map_array",
};

local listOfExtensionsToRemove =
{
    "SGIX_video_source",
    "SGIX_dmbuffer",
    "SGIX_hyperpipe",
};

function LoadLuaSpec(luaFilename)
	local specData = dofile(luaFilename);

	specData.extdefs = {};
	specData.coredefs = {};
	specData.enumtable = {};
	local extdefs = specData.extdefs;
	local coredefs = specData.coredefs;
	local enumtable = specData.enumtable;
	
	--HACK! Change 1.0 version in functions to 1.1, to match enums.
	for i, func in ipairs(specData.funcData.functions) do
		if(func.version == "1.0") then func.version = "1.1"; end;
	end
	
	--HACK! Change "void" in the typemap to map to "void".
	specData.typemap.void = "void";
	
	--HACK! Add suffixes to functions and enums for these extensions.
	for i, extName in ipairs(listOfNonCoreFixes) do
		for j, func in ipairs(specData.funcData.functions) do
			if(func.category == extName) then
				func.name = func.name .. "ARB";
			end
		end
		for j, enum in ipairs(specData.enumerations) do
			if(enum.extensions) then
				for k, enumExt in ipairs(enum.extensions) do
					if(enumExt == extName) then
						enum.name = enum.name .. "_ARB";
					end
				end
			end
		end
	end
	
	--HACK! Remove certain offensive extensions.
	local toRemove = {}
	for i, ext in ipairs(specData.extensions) do
	    for j, test in ipairs(listOfExtensionsToRemove) do
	        if(ext == test) then
	            table.insert(toRemove, 1, i);
	            break;
	        end
	    end
	end
	
	for i, index in ipairs(toRemove) do
	    table.remove(specData.extensions, index);
	end
	
	toRemove = {}
	for i, enum in ipairs(specData.enumerations) do
		if(enum.extensions) then
		    for j, enumExt in ipairs(enum.extensions) do
		        local bBreak = false;
	            for k, test in ipairs(listOfExtensionsToRemove) do
	                if(enumExt == test) then
	                    table.insert(toRemove, 1, i);
	                    bBreak = true;
	                    break;
	                end
	            end
	            if(bBreak) then break; end
		    end
		end
	end
	
	for i, index in ipairs(toRemove) do
	    table.remove(specData.enumerations, index);
	end
	
	toRemove = {}
    for i, func in ipairs(specData.funcData.functions) do
	    for j, test in ipairs(listOfExtensionsToRemove) do
	        if(ext == func.category) then
	            table.insert(toRemove, 1, i);
	            break;
	        end
	    end
    end

	for i, index in ipairs(toRemove) do
	    table.remove(specData.funcData.functions, index);
	end
	
	
	
	
	local function GetCore(version)
		if(not coredefs[version]) then
			local coredef = {};
			coredefs[version] = coredef;
			coredef.enums = {};
			coredef.funcs = {};
		end
		
		return coredefs[version];
	end
	
	local function GetExt(extName)
		if(not extdefs[extName]) then
			local extdef = {};
			extdefs[extName] = extdef;
			extdef.enums = {};
			extdef.funcs = {};
		end
		
		return extdefs[extName];
	end

	--Add all extensions to the extdefs.
	for	i, extName in ipairs(specData.extensions) do
		GetExt(extName);
	end
	
	for i, enum in ipairs(specData.enumerations) do
		enumtable[enum.name] = enum;
		
		if(enum.extensions) then
			for k, extName in ipairs(enum.extensions) do
				table.insert(GetExt(extName).enums, enum);
			end
		end
		
		if(enum.version) then
			table.insert(GetCore(enum.version).enums, enum);
		end
	end

	for i, func in ipairs(specData.funcData.functions) do
		--This is here to make sure that the category is an actual extension,
		--not a verison number.
		if(extdefs[func.category]) then
			table.insert(GetExt(func.category).funcs, func);
		end
	
		if(func.version) then
			if(not func.category or string.match(func.category, "^VERSION")) then
				local versionVal = string.gsub(func.category, "VERSION_(%d+)_(%d+).*", "%1%.%2");
				--HACK!
				if(versionVal == "1.0") then versionVal = "1.1" end;
				table.insert(GetCore(versionVal).funcs, func);
			end
		end
	end
	
	specData.coreexts = dofile(GetDataFilePath() .. "coreExtList.lua");

	return specData;
end

