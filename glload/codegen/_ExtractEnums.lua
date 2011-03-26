--[[
The exported function, ExtractEnums, returns the enum data as follows:

An array of enumerators, ordered as in enumext.spec. Each enumerator is a table that contains
these fields:

- name: String containing the name of the enumerator.
- value: String number containing the value of the enumerator, or the name of an enumerator to copy from.
- copy: True if the value is an enumerator to copy from; false if it's a number.
- version: String in A.B format contining the core version for this enumerator.
- deprecated: String in A.B format for the version where the enumerator was deprecated.
- removed: String in A.B format when the enumerator was removed from GL.
- extension: An array of extension names.
]]

require("_line");

--GLOBAL: Bad form, I know, but it's the easiest way to do this.
local clipPattern = nil;


local function AddExtToEnum(enumEntry, extName)
	if(enumEntry.extensions == nil) then enumEntry.extensions = {}; end;
	
	if(clipPattern) then
		local newExtName = string.match(extName, clipPattern);
		if(newExtName) then extName = newExtName; end;
	end
	
	table.insert(enumEntry.extensions, extName);
end

local function FetchEnum(currState, enumName)
	if(clipPattern) then
		local newEnumName = string.match(enumName, clipPattern);
		if(newEnumName) then enumName = newEnumName; end;
	end
	
	if(currState.enumMap[enumName] == nil) then
		currState.enumMap[enumName] = {};
		table.insert(currState.enumArray, currState.enumMap[enumName]);
	end

	local enumEntry = currState.enumMap[enumName];
	enumEntry.name = enumName;
	
	if(currState.extDef.version) then
		enumEntry.version = currState.extDef.version;
	else
		AddExtToEnum(enumEntry, currState.extDef.extName);
	end
	
	if(enumEntry.deprecated == nil) then enumEntry.deprecated = currState.extDef.deprecated; end
	if(enumEntry.removed == nil) then enumEntry.removed = currState.extDef.removed; end
	
	currState.enumMap[enumName] = enumEntry;
	
	return enumEntry;
end

--We process each line with this table. For the line, we match it with the given pattern.
--If the pattern matches, then we call the associated function. If no patterns match, we skip it.
--The first parameter to the functions is the current data for our enumerators.
--The second parameter is the array of matches from the pattern test.
local procTable =
{
	{["pattern"] = "passthru:%s+(.+)", ["func"] = function(currState, matchArray)
end},

--This pattern is hit when we reach a new extension.
--This function sets it to be the current extension.
	{["pattern"] = "(%S+)%s*enum:", ["func"] = function(currState, matchArray)
		currState.extDef = {};
		local bHasVersion = false;
		
		local baseExtName = string.match(matchArray[1], "(.*)_DEPRECATED$");
		local testExtName = matchArray[1];
		
		if(baseExtName) then testExtName = baseExtName; end;

		local versionNum = string.match(testExtName, "^VERSION_(.*)");
		if(versionNum) then
			currState.extDef.version = string.format("%s.%s", string.match(versionNum, "(.*)_(.*)"));
			bHasVersion = true;
		end
		
		if(baseExtName) then
			currState.extDef.deprecated = "3.0";
			currState.extDef.removed = "3.1";
			if(not bHasVersion) then
				currState.extDef.extName = baseExtName;
			end
		else
			if(not bHasVersion) then
				currState.extDef.extName = testExtName;
			end
		end
	end},

--This pattern is hit when we reach an enumeration definition by hexadecimal value.
	{["pattern"] = "(%S+)%s*=%s*(0x%x+)", ["func"] = function(currState, matchArray)
		local enumEntry = FetchEnum(currState, matchArray[1]);
		
		enumEntry.value = matchArray[2];
		enumEntry.copy = false;
	end},

--This pattern is hit when we reach an enumeration definition by decimal value.
	{["pattern"] = "(%S+)%s*=%s*(%d+)", ["func"] = function(currState, matchArray)
		local enumEntry = FetchEnum(currState, matchArray[1]);
		
		enumEntry.value = matchArray[2];
		enumEntry.copy = false;
	end},

--This pattern is hit when we reach an enumeration copy (copy the value from another enum).
	{["pattern"] = "(%S+)%s*=%s*%S-_(%S+)", ["func"] = function(currState, matchArray)
		local enumEntry = FetchEnum(currState, matchArray[1]);
		
		enumEntry.value = matchArray[2];
		enumEntry.copy = true;
	end},

--This pattern is hit when we are saying that the given enum (param #2) is being used in
--this context, so we should add the current context as extensions or core.
--If the current context is an extension, then it's possible that
--the thing using it is a core version.
	{["pattern"] = "use (%S+)%s*(%S+)", ["func"] = function(currState, matchArray)
		local enumEntry = FetchEnum(currState, matchArray[2]);
end},
};

function ExtractEnums(hInFile, clipPrefix)
	
	local state = {};
	state.enumArray = {};
	state.enumMap = {};
	state.FetchEnum = FetchEnum;
	
	if(clipPrefix) then
		clipPattern = string.format("^%s_(.*)", clipPrefix);
	else
		clipPattern = nil;
	end


	for strCurrLine in hInFile:lines() do
		local strOutLine = CullLine(strCurrLine);
		if(strOutLine) then
			for i, proc in ipairs(procTable) do
				local test = {string.match(strOutLine, proc.pattern)};
				if(#test ~= 0) then
					proc.func(state, test);
					break;
				end;
			end
		end
	end
	
	return state.enumArray;
end



