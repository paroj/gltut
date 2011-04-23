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
	--Front
	vmath.vec3( 0.5,  0.5,  0.5),
	vmath.vec3( 0.5, -0.5,  0.5),
	vmath.vec3(-0.5, -0.5,  0.5),
	vmath.vec3(-0.5,  0.5,  0.5),

	--Top
	vmath.vec3( 0.5,  0.5,  0.5),
	vmath.vec3(-0.5,  0.5,  0.5),
	vmath.vec3(-0.5,  0.5, -0.5),
	vmath.vec3( 0.5,  0.5, -0.5),

	--Left
	vmath.vec3( 0.5,  0.5,  0.5),
	vmath.vec3( 0.5,  0.5, -0.5),
	vmath.vec3( 0.5, -0.5, -0.5),
	vmath.vec3( 0.5, -0.5,  0.5),

	--Back
	vmath.vec3( 0.5,  0.5, -0.5),
	vmath.vec3(-0.5,  0.5, -0.5),
	vmath.vec3(-0.5, -0.5, -0.5),
	vmath.vec3( 0.5, -0.5, -0.5),

	--Bottom
	vmath.vec3( 0.5, -0.5,  0.5),
	vmath.vec3( 0.5, -0.5, -0.5),
	vmath.vec3(-0.5, -0.5, -0.5),
	vmath.vec3(-0.5, -0.5,  0.5),

	--Right
	vmath.vec3(-0.5,  0.5,  0.5),
	vmath.vec3(-0.5, -0.5,  0.5),
	vmath.vec3(-0.5, -0.5, -0.5),
	vmath.vec3(-0.5,  0.5, -0.5),
};

local normals =
{
	--Front
	vmath.vec3(0.0,  0.0,  1.0),
	vmath.vec3(0.0,  0.0,  1.0),
	vmath.vec3(0.0,  0.0,  1.0),
	vmath.vec3(0.0,  0.0,  1.0),

	--Top
	vmath.vec3(0.0,  1.0,  0.0),
	vmath.vec3(0.0,  1.0,  0.0),
	vmath.vec3(0.0,  1.0,  0.0),
	vmath.vec3(0.0,  1.0,  0.0),

	--Left
	vmath.vec3(1.0,  0.0,  0.0),
	vmath.vec3(1.0,  0.0,  0.0),
	vmath.vec3(1.0,  0.0,  0.0),
	vmath.vec3(1.0,  0.0,  0.0),

	--Back
	vmath.vec3(0.0,  0.0, -1.0),
	vmath.vec3(0.0,  0.0, -1.0),
	vmath.vec3(0.0,  0.0, -1.0),
	vmath.vec3(0.0,  0.0, -1.0),

	--Bottom
	vmath.vec3(0.0, -1.0,  0.0),
	vmath.vec3(0.0, -1.0,  0.0),
	vmath.vec3(0.0, -1.0,  0.0),
	vmath.vec3(0.0, -1.0,  0.0),

	--Right
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
	vmath.vec3(-1.0,  0.0,  0.0),
}

local colors =
{
	vmath.vec4(0.25, 1.0, 0.25, 1.0),
	vmath.vec4(0.25, 1.0, 0.25, 1.0),
	vmath.vec4(0.25, 1.0, 0.25, 1.0),
	vmath.vec4(0.25, 1.0, 0.25, 1.0),

	vmath.vec4(0.5, 0.5, 1.0, 1.0),
	vmath.vec4(0.5, 0.5, 1.0, 1.0),
	vmath.vec4(0.5, 0.5, 1.0, 1.0),
	vmath.vec4(0.5, 0.5, 1.0, 1.0),

	vmath.vec4(1.0, 0.5, 0.5, 1.0),
	vmath.vec4(1.0, 0.5, 0.5, 1.0),
	vmath.vec4(1.0, 0.5, 0.5, 1.0),
	vmath.vec4(1.0, 0.5, 0.5, 1.0),

	vmath.vec4(1.0, 1.0, 0.5, 1.0),
	vmath.vec4(1.0, 1.0, 0.5, 1.0),
	vmath.vec4(1.0, 1.0, 0.5, 1.0),
	vmath.vec4(1.0, 1.0, 0.5, 1.0),

	vmath.vec4(0.5, 1.0, 1.0, 1.0),
	vmath.vec4(0.5, 1.0, 1.0, 1.0),
	vmath.vec4(0.5, 1.0, 1.0, 1.0),
	vmath.vec4(0.5, 1.0, 1.0, 1.0),

	vmath.vec4(1.0, 0.5, 1.0, 1.0),
	vmath.vec4(1.0, 0.5, 1.0, 1.0),
	vmath.vec4(1.0, 0.5, 1.0, 1.0),
	vmath.vec4(1.0, 0.5, 1.0, 1.0),
}

local indices =
{
	vmath.vec3(0, 1, 2),
	vmath.vec3(2, 3, 0),

	vmath.vec3(4, 5, 6),
	vmath.vec3(6, 7, 4),

	vmath.vec3(8, 9, 10),
	vmath.vec3(10, 11, 8),

	vmath.vec3(12, 13, 14),
	vmath.vec3(14, 15, 12),

	vmath.vec3(16, 17, 18),
	vmath.vec3(18, 19, 16),

	vmath.vec3(20, 21, 22),
	vmath.vec3(22, 23, 20),
};

do
	local writer = XmlWriter.XmlWriter("UnitCube.xml");
	writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
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
		writer:PushElement("attribute");
			writer:AddAttribute("index", "2");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(normals));
		writer:PopElement();
		writer:PushElement("vao");
			writer:AddAttribute("name", "lit");
			writer:PushElement("source"); writer:AddAttribute("attrib", "0"); writer:PopElement();
			writer:PushElement("source"); writer:AddAttribute("attrib", "2"); writer:PopElement();
		writer:PopElement();
		writer:PushElement("vao");
			writer:AddAttribute("name", "lit-color");
			writer:PushElement("source"); writer:AddAttribute("attrib", "0"); writer:PopElement();
			writer:PushElement("source"); writer:AddAttribute("attrib", "1"); writer:PopElement();
			writer:PushElement("source"); writer:AddAttribute("attrib", "2"); writer:PopElement();
		writer:PopElement();
		writer:PushElement("vao");
			writer:AddAttribute("name", "color");
			writer:PushElement("source"); writer:AddAttribute("attrib", "0"); writer:PopElement();
			writer:PushElement("source"); writer:AddAttribute("attrib", "1"); writer:PopElement();
		writer:PopElement();
		writer:PushElement("vao");
			writer:AddAttribute("name", "flat");
			writer:PushElement("source"); writer:AddAttribute("attrib", "0"); writer:PopElement();
		writer:PopElement();
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "triangles");
			writer:AddAttribute("type", "ushort");
			writer:AddText(GenStringFromArray(indices, true));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end
