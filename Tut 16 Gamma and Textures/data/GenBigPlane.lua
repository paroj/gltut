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
	vmath.vec3( 64.0, 0.0, -64.0),
	vmath.vec3( 64.0, 0.0,  64.0),
	vmath.vec3(-64.0, 0.0,  64.0),
	vmath.vec3(-64.0, 0.0, -64.0),

	vmath.vec3( 64.0, 0.0, -64.0),
	vmath.vec3( 64.0, 0.0,  64.0),
	vmath.vec3(-64.0, 0.0,  64.0),
	vmath.vec3(-64.0, 0.0, -64.0),
};

local texCoords =
{
	vmath.vec2(64.0, -64.0),
	vmath.vec2(64.0, 64.0),
	vmath.vec2(-64.0, 64.0),
	vmath.vec2(-64.0, -64.0),

	vmath.vec2(64.0, -64.0),
	vmath.vec2(64.0, 64.0),
	vmath.vec2(-64.0, 64.0),
	vmath.vec2(-64.0, -64.0),
};

local indices =
{
	vmath.vec3(0, 1, 2),
	vmath.vec3(2, 3, 0),

	vmath.vec3(4, 6, 5),
	vmath.vec3(6, 4, 7),
};

do
	local writer = XmlWriter.XmlWriter("BigPlane.xml");
	writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
	writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");
		writer:PushElement("attribute");
			writer:AddAttribute("index", "0");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(positions));
		writer:PopElement();
		writer:PushElement("attribute");
			writer:AddAttribute("index", "5");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "2");
			writer:AddText(GenStringFromArray(texCoords));
		writer:PopElement();
		writer:PushElement("vao");
			writer:AddAttribute("name", "flat");
			writer:PushElement("source"); writer:AddAttribute("attrib", "0"); writer:PopElement();
		writer:PopElement();
		writer:PushElement("vao");
			writer:AddAttribute("name", "tex");
			writer:PushElement("source"); writer:AddAttribute("attrib", "0"); writer:PopElement();
			writer:PushElement("source"); writer:AddAttribute("attrib", "5"); writer:PopElement();
		writer:PopElement();
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "triangles");
			writer:AddAttribute("type", "ushort");
			writer:AddText(GenStringFromArray(indices, true));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end

