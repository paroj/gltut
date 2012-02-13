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
    --Frontside
	vmath.vec3(-0.5, -0.5,  0.5),
	vmath.vec3(-0.5,  0.5,  0.5),
	vmath.vec3(-0.5,  0.5, -0.5),
	vmath.vec3(-0.5, -0.5, -0.5),
	
	vmath.vec3(-0.5, -0.5, -0.5),
	vmath.vec3(-0.5,  0.5, -0.5),
	vmath.vec3( 0.5,  0.5, -0.5),
	vmath.vec3( 0.5, -0.5, -0.5),

	vmath.vec3( 0.5, -0.5, -0.5),
	vmath.vec3( 0.5,  0.5, -0.5),
	vmath.vec3( 0.5,  0.5,  0.5),
	vmath.vec3( 0.5, -0.5,  0.5),
	
	--Backside
	vmath.vec3(-0.5, -0.5,  0.5),
	vmath.vec3(-0.5,  0.5,  0.5),
	vmath.vec3(-0.5,  0.5, -0.5),
	vmath.vec3(-0.5, -0.5, -0.5),
	
	vmath.vec3(-0.5, -0.5, -0.5),
	vmath.vec3(-0.5,  0.5, -0.5),
	vmath.vec3( 0.5,  0.5, -0.5),
	vmath.vec3( 0.5, -0.5, -0.5),

	vmath.vec3( 0.5, -0.5, -0.5),
	vmath.vec3( 0.5,  0.5, -0.5),
	vmath.vec3( 0.5,  0.5,  0.5),
	vmath.vec3( 0.5, -0.5,  0.5),
};

local normals =
{
	--Frontside
	vmath.vec3( 1.0,  0.0,  0.0),
	vmath.vec3( 1.0,  0.0,  0.0),
	vmath.vec3( 1.0,  0.0,  0.0),
	vmath.vec3( 1.0,  0.0,  0.0),
	
	vmath.vec3( 0.0,  0.0,  1.0),
	vmath.vec3( 0.0,  0.0,  1.0),
	vmath.vec3( 0.0,  0.0,  1.0),
	vmath.vec3( 0.0,  0.0,  1.0),
	
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
	
	--Backside
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
	
	vmath.vec3( 0.0,  0.0, -1.0),
	vmath.vec3( 0.0,  0.0, -1.0),
	vmath.vec3( 0.0,  0.0, -1.0),
	vmath.vec3( 0.0,  0.0, -1.0),
	
	vmath.vec3( 1.0,  0.0,  0.0),
	vmath.vec3( 1.0,  0.0,  0.0),
	vmath.vec3( 1.0,  0.0,  0.0),
	vmath.vec3( 1.0,  0.0,  0.0),
}

local texCoords =
{
	--Frontside
	vmath.vec2(0.0, 0.0),
	vmath.vec2(0.0, 1.0),
	vmath.vec2(1.0, 1.0),
	vmath.vec2(1.0, 0.0),

	vmath.vec2(0.0, 0.0),
	vmath.vec2(0.0, 1.0),
	vmath.vec2(1.0, 1.0),
	vmath.vec2(1.0, 0.0),

	vmath.vec2(0.0, 0.0),
	vmath.vec2(0.0, 1.0),
	vmath.vec2(1.0, 1.0),
	vmath.vec2(1.0, 0.0),

	--Backside
	vmath.vec2(0.0, 0.0),
	vmath.vec2(0.0, 1.0),
	vmath.vec2(1.0, 1.0),
	vmath.vec2(1.0, 0.0),

	vmath.vec2(0.0, 0.0),
	vmath.vec2(0.0, 1.0),
	vmath.vec2(1.0, 1.0),
	vmath.vec2(1.0, 0.0),

	vmath.vec2(0.0, 0.0),
	vmath.vec2(0.0, 1.0),
	vmath.vec2(1.0, 1.0),
	vmath.vec2(1.0, 0.0),
}

local indices =
{
	--Frontside
	vmath.vec3(0, 1, 2),
	vmath.vec3(2, 3, 0),
	
	vmath.vec3(4, 5, 6),
	vmath.vec3(6, 7, 4),

	vmath.vec3(8, 9, 10),
	vmath.vec3(10, 11, 8),
	
	--Backside
	vmath.vec3(12, 15, 14),
	vmath.vec3(14, 13, 12),
	
	vmath.vec3(16, 19, 18),
	vmath.vec3(18, 17, 16),
	
	vmath.vec3(20, 23, 22),
	vmath.vec3(22, 21, 20),
};

local function WriteVAO(writer, name, ...)
	local attribs = {...}
	
	writer:PushElement("vao");
		writer:AddAttribute("name", name);
		for i, attrib in ipairs(attribs) do
			writer:PushElement("source");
			writer:AddAttribute("attrib", tostring(attrib));
			writer:PopElement();
		end
	writer:PopElement();
end

do
	local writer = XmlWriter.XmlWriter("UnitDiorama.xml");
	writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
	writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");
		writer:PushElement("attribute");
			writer:AddAttribute("index", "0");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(positions));
		writer:PopElement();
		writer:PushElement("attribute");
			writer:AddAttribute("index", "2");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(normals));
		writer:PopElement();
		writer:PushElement("attribute");
			writer:AddAttribute("index", "5");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "2");
			writer:AddText(GenStringFromArray(texCoords));
		writer:PopElement();
		WriteVAO(writer, "lit", 0, 2);
		WriteVAO(writer, "lit-tex", 0, 2, 5);
		WriteVAO(writer, "tex", 0, 5);
		WriteVAO(writer, "flat", 0);
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "triangles");
			writer:AddAttribute("type", "ushort");
			writer:AddText(GenStringFromArray(indices, true));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end
