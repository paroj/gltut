--[[
These are conversion helper functions. All of the strings they return
have *no* \n terminators.

Certain variable names have a certain expected type. These will be used
consistently:

- func: Expects to be a function entry from LoadLuaSpec.
- enum: Expects to be an enum entry from LoadLuaSpec.
- enumTable: The table from LoadLuaSpec that maps from enum name to enumerator.
- typemap: Expects to be the typemap list from LoadLuaSpec.
- specData: Expects to be the table returned by LoadLuaSpec.
- funcPrefix: the prefix string to add to all functions.
- enumPrefix: the prefix string (no '_'. We add that) to add to all enumerators.
]]


Make = {};

local bIsKindPtr ={
	value = false,
	array = true,
	reference = true,
};

function Make.GetParameterListStr(func, typemap)
	local strParamList = "";
	for i, param in ipairs(func.params) do
		local paramType = typemap[param.type] or param.type;

		if(bIsKindPtr[param.kind]) then
			if(param.input) then
				--Input arrays are ALWAYS const.
				strParamList = strParamList .. "const ";
			end
			strParamList = strParamList .. string.format("%s *%s",
				paramType, param.name);
		else
			strParamList = strParamList .. string.format("%s %s",
				paramType, param.name);
		end

		if(i ~= #func.params) then
			strParamList = strParamList .. ", ";
		end
	end
	
	return strParamList;
end

function Make.GetFuncTypedefNameStr(func, funcPrefix)
	return string.upper(string.format("PFN%s%sPROC",
		funcPrefix, func.name));
end

function Make.GetFuncPtrNameStr(func, funcPrefix)
	return funcPrefix .. func.name;
end

function Make.GetCoreFuncPtrNameStr(func, funcPrefix)
	return string.format("__%se%s", funcPrefix, func.name);
end

function Make.GetFuncDef(func, funcPrefix, typemap)
	local strDefFormat = "%s (GLE_FUNCPTR * %s)(%s);";

	local funcTypedefName = Make.GetFuncTypedefNameStr(func, funcPrefix);
	local strParamList = Make.GetParameterListStr(func, typemap);
	
	return string.format(strDefFormat, typemap[func["return"]] or func["return"],
		funcTypedefName, strParamList);
end

function Make.GetFuncTypedef(func, funcPrefix, typemap)
	return "typedef " .. Make.GetFuncDef(func, funcPrefix, typemap);
end

function Make.GetFuncPtr(func, funcPrefix, typemap)
	local strTypedefFormat = "%s %s;";

	local funcTypedefName = Make.GetFuncTypedefNameStr(func, funcPrefix);
	local funcPtrName = Make.GetFuncPtrNameStr(func, funcPrefix);
	
	return string.format(strTypedefFormat, funcTypedefName, funcPtrName);
end

function Make.GetCoreFuncPtr(func, funcPrefix, typemap)
	local strTypedefFormat = "%s %s;";

	local funcTypedefName = Make.GetFuncTypedefNameStr(func, funcPrefix);
	local funcPtrName = Make.GetCoreFuncPtrNameStr(func, funcPrefix);
	
	return string.format(strTypedefFormat, funcTypedefName, funcPtrName);
end

function Make.GetFuncExternPtr(func, funcPrefix, typemap)
	return "extern " .. Make.GetFuncPtr(func, funcPrefix, typemap);
end

function Make.GetCoreFuncExternPtr(func, funcPrefix, typemap)
	return "extern " .. Make.GetCoreFuncPtr(func, funcPrefix, typemap);
end

function Make.GetCoreFuncPtrDefine(func, funcPrefix)
	return string.format("#define %s %s",
		Make.GetFuncPtrNameStr(func, funcPrefix),
		Make.GetCoreFuncPtrNameStr(func, funcPrefix));
end


local function GetEnumValue(enum, enumTable)
	if(enum.copy) then
		return GetEnumValue(enumTable[enum.value], enumTable), enum.value;
	else
		return enum.value;
	end
end

function Make.GetEnumerator(enum, enumTable, enumPrefix)
	local enumValue, copiedFrom = GetEnumValue(enum, enumTable);
	if(copiedFrom) then
		return string.format("#define %s_%s %s /* %s_%s */",
			enumPrefix, enum.name, enumValue, enumPrefix, copiedFrom);
	else
		return string.format("#define %s_%s %s",
			enumPrefix, enum.name, enumValue);
	end
end

function Make.GetExtensionVarName(extName, funcPrefix)
	return string.format("%sext_%s", funcPrefix, extName);
end

function Make.GetExtensionVar(extName, funcPrefix)
	return "int " .. Make.GetExtensionVarName(extName, funcPrefix) .. " = 0;";
end

function Make.GetExtensionVarExtern(extName, funcPrefix)
	return "extern int " .. Make.GetExtensionVarName(extName, funcPrefix) .. ";";
end

local loaderFuncDefFormat = "int %seIntLoad_%s()";

function Make.GetExtLoaderFuncDef(extName, funcPrefix)
	return string.format(loaderFuncDefFormat, funcPrefix, extName);
end

function Make.GetExtLoaderFuncPrototype(extName, funcPrefix)
	return Make.GetExtLoaderFuncDef(extName, funcPrefix) .. ";";
end

local profileCoreLoaderMap = {
	["core"] = "";
	["compatibility"] = "_Comp";
};

function Make.GetCoreLoaderFuncName(version, profile, funcPrefix)
	local major, minor = string.match(version, "(%d+)%.(%d+)");
	
	return string.format("%seIntLoad_Version_%s_%s%s", funcPrefix, major,
		minor, profileCoreLoaderMap[profile]);
end

function Make.GetCoreLoaderFuncDef(version, profile, funcPrefix)
	local major, minor = string.match(version, "(%d+)%.(%d+)");
	
	return string.format("int %s()",
		Make.GetCoreLoaderFuncName(version, profile, funcPrefix));
end

function Make.GetCoreLoaderFuncPrototype(version, profile, funcPrefix)
	return Make.GetCoreLoaderFuncDef(version, profile, funcPrefix) .. ";";
end

function Make.GetMapTableName(funcPrefix)
	return funcPrefix .. "eIntExtensionMap";
end

function Make.GetMapTableExtern(funcPrefix)
	return string.format("extern StrToExtMap %s[];", Make.GetMapTableName(funcPrefix));
end

function Make.GetMapTableDef(funcPrefix)
	return string.format("StrToExtMap %s[]", Make.GetMapTableName(funcPrefix));
end

function Make.GetMapTableSizeName(funcPrefix)
	return funcPrefix .. "eIntExtensionMapSize";
end

function Make.GetMapTableSizeExtern(funcPrefix)
	return string.format("extern int %s;", Make.GetMapTableSizeName(funcPrefix));
end

function Make.GetMapTableSizeDef(iSize, funcPrefix)
	return string.format("int %s = %i;", Make.GetMapTableSizeName(funcPrefix),
		iSize);
end

function Make.GetClearFunctionName(funcPrefix)
	return funcPrefix .. "eIntClear";
end

function Make.GetClearFunctionDecl(funcPrefix)
	return string.format("void %s();", Make.GetClearFunctionName(funcPrefix));
end

function Make.GetCoreStructType(funcPrefix)
	return string.upper(funcPrefix) .. "eStandardCoreStruct";
end

function Make.GetCoreStructVarName(funcPrefix)
	return funcPrefix .. "e_CoreStruct";
end

function Make.GetCoreStructMemberName(func, funcPrefix)
	return string.format("%seVar%s", funcPrefix, func.name);
end

function Make.GetCoreInitFuncName(funcPrefix)
	return funcPrefix .. "eIntCoreInit";
end

function Make.GetBaseLoaderFuncName(funcPrefix)
	return funcPrefix .. "eIntLoadBaseFuncs";
end

--Returns a list of core functions, including core extension funcs.
function Make.FetchAllCoreFunctions(specData)
	--Get all core functions.
	local funcList = {};
	for coreName, data in pairs(specData.coredefs) do
		for i, func in ipairs(data.funcs) do
			table.insert(funcList, func);
		end
	end
	
	--Get core extension functions.
	for extName, data in pairs(specData.extdefs) do
		if(specData.coreexts[extName]) then
			for i, func in ipairs(data.funcs) do
				table.insert(funcList, func);
			end
		end
	end
	
	return funcList;
end


