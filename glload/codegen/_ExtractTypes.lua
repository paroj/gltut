--[[ This function takes a handle to a .tm file, and returns a table. The keys for the table are
the GL-generic types, and the values are the actual C++ types for them.
]]

require("_line");

function ExtractTypes(hInFile)
	local typemapPattern = "^(%S-),.-,.-,%s-(%S.-),";
	
	local typeMap = {};

	for strCurrLine in hInFile:lines() do
		local strOutLine = CullLine(strCurrLine);
		
		if(strOutLine) then
			local glType, realType = string.match(strOutLine, typemapPattern);
			if(glType and realType) then
				if(typeMap[glType]) then
					print("typemap duplicate: " .. strOutLine);
				else
					typeMap[glType] = realType;
				end
			else
				print("bad typemap line: " .. strOutLine);
			end
		end
	end
	
	return typeMap;
end
