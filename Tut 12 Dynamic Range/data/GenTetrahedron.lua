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
	vmath.vec3( 1.0,  1.0,  1.0),
	vmath.vec3(-1.0, -1.0,  1.0),
	vmath.vec3(-1.0,  1.0, -1.0),
	
	vmath.vec3(-1.0, -1.0,  1.0),
	vmath.vec3( 1.0,  1.0,  1.0),
	vmath.vec3( 1.0, -1.0, -1.0),

	vmath.vec3(-1.0,  1.0, -1.0),
	vmath.vec3( 1.0, -1.0, -1.0),
	vmath.vec3( 1.0,  1.0,  1.0),

	vmath.vec3( 1.0, -1.0, -1.0),
	vmath.vec3(-1.0,  1.0, -1.0),
	vmath.vec3(-1.0, -1.0,  1.0),
	
};

local normals = {}

for i = 1, #positions, 3 do
	local vFirst = positions[i + 1] - positions[i];
	local vSecond = positions[i + 2] - positions[i];
	local normal = vmath.norm(vSecond:cross(vFirst));
	normals[#normals + 1] = normal;
	normals[#normals + 1] = normal;
	normals[#normals + 1] = normal;
end

local colors =
{
	vmath.vec4(0.25, 1.0, 0.25, 1.0),
	vmath.vec4(0.25, 1.0, 0.25, 1.0),
	vmath.vec4(0.25, 1.0, 0.25, 1.0),
	
	vmath.vec4(0.5, 0.5, 1.0, 1.0),
	vmath.vec4(0.5, 0.5, 1.0, 1.0),
	vmath.vec4(0.5, 0.5, 1.0, 1.0),
	
	vmath.vec4(1.0, 0.5, 0.5, 1.0),
	vmath.vec4(1.0, 0.5, 0.5, 1.0),
	vmath.vec4(1.0, 0.5, 0.5, 1.0),
	
	vmath.vec4(0.3, 0.3, 0.3, 1.0),
	vmath.vec4(0.3, 0.3, 0.3, 1.0),
	vmath.vec4(0.3, 0.3, 0.3, 1.0),
}

do
	local writer = XmlWriter.XmlWriter("UnitTetrahedron.xml");
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
		writer:PushElement("arrays");
			writer:AddAttribute("cmd", "triangles");
			writer:AddAttribute("start", "0");
			writer:AddAttribute("count", tostring(#positions));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end
