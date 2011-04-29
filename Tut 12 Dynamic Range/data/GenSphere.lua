require "XmlWriter"
require "vmath"

local function GenStringFromArray(theArray)
	local array = {" "}
	for i, vector in ipairs(theArray) do
		array[#array + 1] = "        " .. table.concat(vector, " ");
	end
	
	return table.concat(array, "\n");
end

local positions = {};
local colors = {};
local normals = {};
local topFan = {};
local botFan = {};
local strips = {};
local restartIndex = 65535;

local iSegCount, iColorRepeatCount, iRingCount = ...;
iSegCount = iSegCount or 15;
iColorRepeatCount = iColorRepeatCount or 3;
iRingCount = iRingCount or 8;

local rhoAngle = math.pi * 2.0 / iSegCount;
local thetaAngle = math.pi / (iRingCount + 1);
local iColorCycleAngle = math.pi * 2.0 / iColorRepeatCount;
local highColor = vmath.vec4(0.9, 0.5, 0.5, 1.0);
local lowColor = vmath.vec4(0.5, 0.1, 0.1, 1.0)

--Compute vertex attributes
positions[#positions + 1] = vmath.vec3(0.0, 0.5, 0.0);
colors[#colors + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
normals[#normals + 1] = vmath.vec3(0.0, 1.0, 0.0);

local firstSideIx = #positions;

for iRing = 1, iRingCount do
	local theta = (thetaAngle * iRing)
	local sinTheta, cosTheta = math.sin(theta), math.cos(theta);

	for iSeg = 0, (iSegCount - 1) do
		local rho = rhoAngle * iSeg;
		local sinRho, cosRho = math.sin(rho), math.cos(rho);
		
		local point = vmath.vec3(sinTheta * cosRho, cosTheta, sinTheta * sinRho);
		positions[#positions + 1] = 0.5 * point;
		normals[#normals + 1] = vmath.vec3(sinTheta * cosRho, cosTheta, sinTheta * sinRho);
		colors[#colors + 1] = vmath.vec4(
			vmath.vec3(sinTheta * cosRho, cosTheta, sinTheta * sinRho), 1.0);
	end
end

positions[#positions + 1] = vmath.vec3(0.0, -0.5, 0.0);
colors[#colors + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
normals[#normals + 1] = vmath.vec3(0.0, -1.0, 0.0);

--Compute cap fans.
topFan[#topFan + 1] = 0;
botFan[#botFan + 1] = #positions - 1;

for iSeg = 1, iSegCount do
	topFan[#topFan + 1] = iSeg;
	botFan[#botFan + 1] = (#positions - 1) - iSeg;
end

topFan[#topFan + 1] = 1;
botFan[#botFan + 1] = (#positions - 2);

--Compute the strips.

for iRing = 1, iRingCount - 1 do
	local topRingStart = 1 + ((iRing - 1) * iSegCount);
	local botRingStart = 1 + (iRing * iSegCount);
	local strip = {};
	strips[#strips + 1] = strip;
	
	for iSeg = 0, (iSegCount - 1) do
		strip[#strip + 1] = topRingStart + iSeg;
		strip[#strip + 1] = botRingStart + iSeg;
	end

	strip[#strip + 1] = topRingStart;
	strip[#strip + 1] = botRingStart;
end


do
	local writer = XmlWriter.XmlWriter("UnitSphere.xml");
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
			writer:AddAttribute("name", "lit-color");
			writer:PushElement("source"); writer:AddAttribute("attrib", "0"); writer:PopElement();
			writer:PushElement("source"); writer:AddAttribute("attrib", "1"); writer:PopElement();
			writer:PushElement("source"); writer:AddAttribute("attrib", "2"); writer:PopElement();
		writer:PopElement();
		writer:PushElement("vao");
			writer:AddAttribute("name", "lit");
			writer:PushElement("source"); writer:AddAttribute("attrib", "0"); writer:PopElement();
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
			writer:AddAttribute("cmd", "tri-fan");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(topFan, " "));
		writer:PopElement();
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "tri-fan");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(botFan, " "));
		writer:PopElement();
		for i, strip in ipairs(strips) do
			writer:PushElement("indices");
				writer:AddAttribute("cmd", "tri-strip");
				writer:AddAttribute("type", "ushort");
				writer:AddText(table.concat(strip, " "));
			writer:PopElement();
		end
	writer:PopElement();
	writer:Close();
end
