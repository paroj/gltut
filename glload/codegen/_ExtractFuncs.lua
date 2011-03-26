--[[The exported function, ExtractFuncs, takes an input file. It returns
a table that contains these things:

- properties: A table of property values. It is a map between property name and values. The value can either be "*" or an array of possible string values that the property can take.
- passthru: A string that is the pass-through data that should be put infront of the function definition header.
- functions: An array of functions. Each function is a table with:
-- name:
-- any of the properties defined in the properties table. This will have values culled from the list of possibles, except if the property was defined as "*", in which case it will be any string.
-- params: An array of parameters, in the order that they are defined as. Each param is a table with:
--- name: the name of the parameter.
--- type: The basic type. Something in the type-map.
--- input: True if it is an input variable, valse otherwise.
--- array: True if it is a pointer; false otehrwise.
--- other: A string containing the other data. Kept for backwards compatibility.
]]

require("_line");

local function StoreParamOptions(param, paramData)
	local testPattern = "(%S*)%s+(.*)";
	
	local glType, rest = string.match(paramData, testPattern);
	
	param.type = glType;
	
	local input;
	input, rest = string.match(rest, testPattern);
	
	if(input == "in") then
		param.input = true;
	else
		param.input = false;
	end
	
	local oldRest = rest;
	
	local arrayKind;
	arrayKind, rest = string.match(rest, testPattern);
	
	if(not arrayKind) then
		param.kind = oldRest;
	else
		param.kind = arrayKind;
	end
	
	if(rest and #rest ~= 0) then
		param.other = rest;
	end
end


local function CreateFunc(strFuncName, strParams)
	local func = {};
	func.name = strFuncName;
	func.params = {};
	func.AddParam = AddParamToFunc;


	--Parse the parameters, in order, into paramList.
	local currParamString = strParams;
	while((currParamString ~= nil) and (#currParamString ~= 0)) do
		local strCurrParam;
		strCurrParam, currParamString = string.match(currParamString, "([%w_]+)(,?%s?.*)");

		local paramData = {};
		paramData.name = strCurrParam;
		table.insert(func.params, paramData);
	end
	
	return func;
end

--If the pattern matches, then the function will be called on that match data.
local jumpTable = {
	{pattern = "^required%-props:$", func = function(state, matchArray)
		state.frontMatter = true;
	end},

	--Passthrough data.
	{pattern = "passthru: (.*)", func = function(state, matchArray)
		if(state.frontMatter) then
			table.insert(state.funcData.passthru, matchArray[1]);
		end
	end},
	
	--Front matter
	{pattern = "(%S*):%s*(.*)", func = function(state, matchArray)
		if(state.frontMatter) then
			local paramData = {};
			state.funcData.properties[matchArray[1]] = paramData;
			for term in string.gmatch(matchArray[2], "%S*") do
				if(#term ~= 0) then
					table.insert(paramData, term);
				end
			end
		end
	end},
	
	--Function definition
	{pattern = "^([%w_]+)%((.*)%)", func = function(state, matchArray)
		state.frontMatter = false;
		state.currFunc = CreateFunc(matchArray[1], matchArray[2]);
		table.insert(state.funcData.functions, state.currFunc);
	end},

	--Parameter Properties
	{pattern = "^\tparam%s+(%S*)%s+(.*)", func = function(state, matchArray)
		local bFound = false;
		
		for count = 1, #state.currFunc.params, 1 do
			if(state.currFunc.params[count].name == matchArray[1]) then
				StoreParamOptions(state.currFunc.params[count], matchArray[2]);
				bFound = true;
				break;
			end
		end
		
		if(not bFound) then
			print(string.format("The func \"%s\" does not have parameter \"%s\".",
				state.currFunc.name, matchArray[1]));
			return true;
		end;
	end},
	
	--Non-param Properties
	{pattern = "^\t(%S*)%s+(%S*)", func = function(state, matchArray)
		state.currFunc[matchArray[1]] = matchArray[2];
	end},
}

function ExtractFuncs(hFile)
	local funcData = {};
	funcData.properties = {};
	funcData.passthru = {};
	funcData.functions = {};
	
	local state = {};
	state.funcData = funcData;
	
	for currLine in hFile:lines() do
		local outLine = CullLine(currLine);
		
		if(outLine) then
			for i, proc in ipairs(jumpTable) do
				local parseArray = {string.match(outLine, proc.pattern);}
				if(parseArray[1]) then
					local bRet = proc.func(state, parseArray);
					if(bRet) then
						print("Bad line: " .. outLine);
					end
				end
			end
		end
	end
	
	return state.funcData;
end

