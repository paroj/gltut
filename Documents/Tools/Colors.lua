
module(..., package.seeall);


local g_colorTable =
{
	lightSource = {"yellow"},
	surface = {"lightblue"},
}

function clrDirect(colorName, bIsBW)
	local clrValue = g_colorTable[colorName];
	
	if(clrValue) then
		if(bIsBW and clrValue[2]) then
			return clrValue[2];
		else
			return clrValue[1];
		end
	else
		return nil, "No Color value named " .. colorName;
	end
end

function clr(...)
	return assert(clrDirect(...));
end
