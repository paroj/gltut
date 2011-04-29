
-- This function will take the given line string and remove the comments from it.
-- It may return an empty line.
function CullLine(strLine)
	if(string.find(strLine, "passthru:%s.+")) then
		return strLine;
	end

	local iVal = string.find(strLine, "#", 1, true);
	
	if(iVal == nil) then
		return strLine;
	end
	
	local strCulled = string.sub(strLine, 1, iVal - 1);
	if(#strCulled == 0) then
		return nil;
	end
	
	return strCulled;
end