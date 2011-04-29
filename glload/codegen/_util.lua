
--Works like the regular pairs, but returns the key/value pairs in a key-sorted order.
--sortFunc is the function used to compare them.
function sortPairs(theTable, sortFunc)
	local keyTable = {};
	
	for key, value in pairs(theTable) do
		table.insert(keyTable, key);
	end
	
	table.sort(keyTable, sortFunc);
	
	local currIndex = 1;
	local lenTable = #keyTable;
	
	return function()
		local currKey = keyTable[currIndex];
		currIndex = currIndex + 1;
		return currKey, theTable[currKey];
	end
end

--Works like ipairs, but returns the list as through it were in a sorted order.
--It even returns the "wrong" indices.
--sortFunc is the function used to compare them.
function isortPairs(theTable, sortFunc)
	local tempTable = {};
	
	for i, value in ipairs(theTable) do
		table.insert(tempTable, value);
	end
	
	table.sort(tempTable, sortFunc);
	
	local currIndex = 1;
	local lenTable = #tempTable;
	
	return function()
		local tempIndex = currIndex;
		currIndex = currIndex + 1;
		return tempIndex, theTable[tempIndex];
	end
end

--ipairs in reverse order.
function ripairs(theTable)
	local currIndex = #theTable;

	return function()
		local tempIndex = currIndex;
		currIndex = currIndex - 1;
		if(currIndex < 0) then return nil, nil; end;
		return tempIndex, theTable[tempIndex];
	end
end

--Standard lessthan compare function. For use with the above.
function CompLess(key1, key2)
	return key1 < key2;
end

--A combined printf and hFile:write.
function WriteFormatted(hFile, strFormat, ...)
	hFile:write(string.format(strFormat, ...));
end

function WriteForm(hFile, strFormat, ...)
	hFile:write(string.format(strFormat, ...));
end

function GetIncludePath()
	return "../include/glload/";
end

function GetSourcePath()
	return "../source/";
end

function GetSpecFilePath()
	return "glspecs/";
end

function GetDataFilePath()
	return "data/";
end

--This returns the starting part of a header's includeguard. Takes the name of the define.
function GetFileIncludeGuardStart(defineName)
	return string.format([[
#ifndef %s
#define %s

]], defineName, defineName);
end

--This returns the ending part of a header's includeguard. Takes the name of the define.
function GetFileIncludeGuardEnd(defineName)
	return string.format([[
#endif //%s

]], defineName);
end

--Retrieves the beginning of the extern C block
function GetExternCStart()
	return [[
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

]]
end

--Retrieves the end of the extern C block.
function GetExternCEnd()
	return [[
#ifdef __cplusplus
}
#endif //__cplusplus

]]
end

--Retrieves a string for a C-style heading. Takes the name of the heading.
function GetSectionHeading(headingName)
	return string.format(
[[/******************************
* %s
******************************/
]], headingName);
end

