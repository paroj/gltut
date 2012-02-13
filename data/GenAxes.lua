require "XmlWriter"
require "vmath"

local function GenStringFromArray(theArray, bAsInt)
	local array = {" "}
	for i, vector in ipairs(theArray) do
		local elements = vector;
		if(bAsInt) then
			elements = {};
			for i, value in ipairs(vector) do
				elements[#elements + 1] = string.format("%i", value);
			end
		end
		
		array[#array + 1] = "        " .. table.concat(vector, " ");
	end
	
	return table.concat(array, "\n");
end

local positions =
{
	vmath.vec3(0.0, 0.0, 0.0),
	vmath.vec3(0.5, 0.0, 0.0),

	vmath.vec3(0.0, 0.0, 0.0),
	vmath.vec3(0.0, 0.5, 0.0),

	vmath.vec3(0.0, 0.0, 0.0),
	vmath.vec3(0.0, 0.0, 0.5),
};

local colors = 
{
	vmath.vec4(1.0, 0.0, 0.0, 1.0),
	vmath.vec4(1.0, 0.0, 0.0, 1.0),
	
	vmath.vec4(0.0, 1.0, 0.0, 1.0),
	vmath.vec4(0.0, 1.0, 0.0, 1.0),
	
	vmath.vec4(0.0, 0.0, 1.0, 1.0),
	vmath.vec4(0.0, 0.0, 1.0, 1.0),
};

do
	local writer = XmlWriter.XmlWriter("UnitAxes.xml");
	writer:AddPI("oxygen", [[RNGSchema="../Documents/meshFormat.rnc" type="compact"]]);
	writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");
		writer:PushElement("attribute");
			writer:AddAttribute("index", "0");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(positions));
		writer:PopElement();
		writer:PushElement("attribute");
			writer:AddAttribute("index", "1");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "4");
			writer:AddText(GenStringFromArray(colors));
		writer:PopElement();
		writer:PushElement("arrays");
			writer:AddAttribute("cmd", "lines");
			writer:AddAttribute("start", "0");
			writer:AddAttribute("count", "6");
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end

