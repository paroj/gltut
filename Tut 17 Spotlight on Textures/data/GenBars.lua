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

local function MakeBar(length)
	local bar = {}
	
	bar.positions =
	{
		--Front
		vmath.vec3( 0.5,  0.5,  0.5 * length),
		vmath.vec3( 0.5, -0.5,  0.5 * length),
		vmath.vec3(-0.5, -0.5,  0.5 * length),
		vmath.vec3(-0.5,  0.5,  0.5 * length),

		--Top
		vmath.vec3( 0.5,  0.5,  0.5 * length),
		vmath.vec3(-0.5,  0.5,  0.5 * length),
		vmath.vec3(-0.5,  0.5, -0.5 * length),
		vmath.vec3( 0.5,  0.5, -0.5 * length),

		--Right
		vmath.vec3( 0.5,  0.5,  0.5 * length),
		vmath.vec3( 0.5,  0.5, -0.5 * length),
		vmath.vec3( 0.5, -0.5, -0.5 * length),
		vmath.vec3( 0.5, -0.5,  0.5 * length),

		--Back
		vmath.vec3( 0.5,  0.5, -0.5 * length),
		vmath.vec3(-0.5,  0.5, -0.5 * length),
		vmath.vec3(-0.5, -0.5, -0.5 * length),
		vmath.vec3( 0.5, -0.5, -0.5 * length),

		--Bottom
		vmath.vec3( 0.5, -0.5,  0.5 * length),
		vmath.vec3( 0.5, -0.5, -0.5 * length),
		vmath.vec3(-0.5, -0.5, -0.5 * length),
		vmath.vec3(-0.5, -0.5,  0.5 * length),

		--Left
		vmath.vec3(-0.5,  0.5,  0.5 * length),
		vmath.vec3(-0.5, -0.5,  0.5 * length),
		vmath.vec3(-0.5, -0.5, -0.5 * length),
		vmath.vec3(-0.5,  0.5, -0.5 * length),
	};

	bar.normals =
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

		--Right
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

		--Left
		vmath.vec3(-1.0,  0.0,  0.0),
		vmath.vec3(-1.0,  0.0,  0.0),
		vmath.vec3(-1.0,  0.0,  0.0),
		vmath.vec3(-1.0,  0.0,  0.0),
	}

	bar.texCoords =
	{
		--Front
		vmath.vec2(1.0, 1.0),
		vmath.vec2(1.0, 0.0),
		vmath.vec2(0.0, 0.0),
		vmath.vec2(0.0, 1.0),

		--Top
		vmath.vec2(1.0 * length, 1.0),
		vmath.vec2(1.0 * length, 0.0),
		vmath.vec2(0.0 * length, 0.0),
		vmath.vec2(0.0 * length, 1.0),

		--Right
		vmath.vec2(0.0 * length, 1.0),
		vmath.vec2(1.0 * length, 1.0),
		vmath.vec2(1.0 * length, 0.0),
		vmath.vec2(0.0 * length, 0.0),
		
		--Back
		vmath.vec2(0.0, 1.0),
		vmath.vec2(1.0, 1.0),
		vmath.vec2(1.0, 0.0),
		vmath.vec2(0.0, 0.0),
		
		--Bottom
		vmath.vec2(1.0, 1.0 * length),
		vmath.vec2(1.0, 0.0 * length),
		vmath.vec2(0.0, 0.0 * length),
		vmath.vec2(0.0, 1.0 * length),

		--Left
		vmath.vec2(1.0 * length, 1.0),
		vmath.vec2(1.0 * length, 0.0),
		vmath.vec2(0.0 * length, 0.0),
		vmath.vec2(0.0 * length, 1.0),
	}

	bar.indices =
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
	}
	
	return bar;
end

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

local function WriteBar(filename, bar)
	if(type(bar) == "number") then
		bar = MakeBar(bar);
	end

	do
		local writer = XmlWriter.XmlWriter(filename);
		writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
		writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");
			writer:PushElement("attribute");
				writer:AddAttribute("index", "0");
				writer:AddAttribute("type", "float");
				writer:AddAttribute("size", "3");
				writer:AddText(GenStringFromArray(bar.positions));
			writer:PopElement();
			writer:PushElement("attribute");
				writer:AddAttribute("index", "2");
				writer:AddAttribute("type", "float");
				writer:AddAttribute("size", "3");
				writer:AddText(GenStringFromArray(bar.normals));
			writer:PopElement();
			writer:PushElement("attribute");
				writer:AddAttribute("index", "5");
				writer:AddAttribute("type", "float");
				writer:AddAttribute("size", "2");
				writer:AddText(GenStringFromArray(bar.texCoords));
			writer:PopElement();
			WriteVAO(writer, "lit", 0, 2);
			WriteVAO(writer, "lit-tex", 0, 2, 5);
			WriteVAO(writer, "tex", 0, 5);
			WriteVAO(writer, "flat", 0);
			writer:PushElement("indices");
				writer:AddAttribute("cmd", "triangles");
				writer:AddAttribute("type", "ushort");
				writer:AddText(GenStringFromArray(bar.indices, true));
			writer:PopElement();
		writer:PopElement();
		writer:Close();
	end
end

WriteBar("ShortBar.xml", 3);
WriteBar("LongBar.xml", 9);

