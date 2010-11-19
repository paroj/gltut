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
		
		array[#array + 1] = "        " .. table.concat(elements, " ");
	end
	
	return table.concat(array, "\n");
end

local nearZ = -2.0;
local farZ = -8.0;
local midZ = (nearZ + farZ) / 2.0;

local posEquilateral =
{
	vmath.vec3( -1.0,  1.0, nearZ),
	vmath.vec3( -1.0, -1.0, nearZ),
	vmath.vec3(  1.0, -1.0, nearZ),
	vmath.vec3(  1.0,  1.0, nearZ),

	vmath.vec3( -1.0,  1.0, midZ),
	vmath.vec3( -1.0, -1.0, midZ),
	vmath.vec3(  1.0, -1.0, midZ),
	vmath.vec3(  1.0,  1.0, midZ),

	vmath.vec3( -1.0,  1.0, midZ),
	vmath.vec3( -1.0, -1.0, midZ),
	vmath.vec3(  1.0, -1.0, midZ),
	vmath.vec3(  1.0,  1.0, midZ),

	vmath.vec3( -1.0,  1.0, farZ),
	vmath.vec3( -1.0, -1.0, farZ),
	vmath.vec3(  1.0, -1.0, farZ),
	vmath.vec3(  1.0,  1.0, farZ),
};

local function FauxProject(theVec)
	return vmath.vec3(theVec);
end

local posFaux = {}

for i, value in ipairs(posEquilateral) do
	if(value.z == nearZ) then
		posFaux[#posFaux + 1] = FauxProject(value);
	else
		local ratio = nearZ / value.z;
		posFaux[#posFaux + 1] = value * ratio;
--		posFaux[#posFaux].z = nearZ;
	end
end

local nearColor = vmath.vec4(1.0, 0.0, 0.0, 1.0);
local farColor = vmath.vec4(0.0, 1.0, 0.0, 1.0);
local midColor = (nearColor + farColor) / 2.0;

local colors =
{
	nearColor,
	nearColor,
	nearColor,
	nearColor,
	
	midColor,
	midColor,
	midColor,
	midColor,

	midColor,
	midColor,
	midColor,
	midColor,

	farColor,
	farColor,
	farColor,
	farColor,
}

local indices =
{
	0, 1, 4,
	1, 5, 4,
	
	1, 2, 6,
	1, 6, 5,
	
	2, 6, 3,
	3, 6, 7,

	8, 9, 12,
	9, 13, 12,
	
	9, 10, 14,
	9, 14, 13,
	
	10, 14, 11,
	11, 14, 15,
}

do
	local writer = XmlWriter.XmlWriter("RealHallway.xml");
	writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
	writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");
		writer:PushElement("attribute");
			writer:AddAttribute("index", "0");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(posEquilateral));
		writer:PopElement();
		writer:PushElement("attribute");
			writer:AddAttribute("index", "1");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "4");
			writer:AddText(GenStringFromArray(colors));
		writer:PopElement();
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "triangles");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(indices, " "));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end

do
	local writer = XmlWriter.XmlWriter("FauxHallway.xml");
	writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
	writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");
		writer:PushElement("attribute");
			writer:AddAttribute("index", "0");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(posFaux));
		writer:PopElement();
		writer:PushElement("attribute");
			writer:AddAttribute("index", "1");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "4");
			writer:AddText(GenStringFromArray(colors));
		writer:PopElement();
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "triangles");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(indices, " "));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end
