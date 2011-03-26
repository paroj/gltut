--[[The funciton ExtractExts takes a file handle to an enumext.spec file. It returns an array of extension names.
]]

require "_line"

local function IsExtension(heading)
	if(string.match(heading, "^VERSION.*")) then return false; end;
	
	if(string.match(heading, "DEPRECATED$")) then return false; end;

	return true;
end

function ExtractExts(hInFile, clipPrefix)
	local ret = {};
	local headingPattern = "^(%S+)%s*enum:";
	
	local clipPattern = nil;
	if(clipPrefix) then
		clipPattern = string.format("^%s_(.*)", clipPrefix);
	end

	for strCurrLine in hInFile:lines() do
		local strOutLine = CullLine(strCurrLine);
		if(strOutLine) then
			local heading = string.match(strOutLine, headingPattern);
			if(heading) then
				if(IsExtension(heading)) then
					if(clipPattern) then
						local newHeading = string.match(heading, clipPattern);
						if(newHeading) then heading = newHeading; end;
					end
					
					table.insert(ret, heading);
				end
			end
		end
	end

	return ret;
end
