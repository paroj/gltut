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
local cylStrip = {};

local iSegCount, iColorRepeatCount = ...;
iSegCount = iSegCount or 30;
iColorRepeatCount = iColorRepeatCount or 3;

local iAngle = 3.14159 * 2.0 / iSegCount;
local iColorCycleAngle = 3.14159 * 2.0 / iColorRepeatCount;
local highColor = vmath.vec4(0.9, 0.8, 0.8, 1.0);
local lowColor = vmath.vec4(0.6, 0.6, 0.5, 1.0)

--Compute caps
positions[#positions + 1] = vmath.vec3(0.0, 0.5, 0.0);
colors[#colors + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
normals[#normals + 1] = vmath.vec3(0.0, 1.0, 0.0);
topFan[#topFan + 1] = 0;
botFan[#botFan + 1] = (iSegCount * 2) + 1;

local firstSideIx = #positions;

for iSeg = 0, (iSegCount - 1), 1 do
	local iCurrAngle = iSeg * iAngle;

	positions[#positions + 1] =
		vmath.vec3(0.5 * math.cos(iCurrAngle), 0.5, 0.5 * math.sin(iCurrAngle));
	positions[#positions + 1] =
		vmath.vec3(0.5 * math.cos(iCurrAngle), -0.5, 0.5 * math.sin(iCurrAngle));

	normals[#normals + 1] = vmath.vec3(0.0, 1.0, 0.0);
	normals[#normals + 1] = vmath.vec3(0.0, -1.0, 0.0);
		
	local clrDist = math.mod(iCurrAngle, iColorCycleAngle) / iColorCycleAngle;
	if(clrDist > 0.5) then
		local interp = (clrDist - 0.5) * 2;
		colors[#colors + 1] = (interp * highColor) +
			((1 - interp) * lowColor);
	else
		local interp = clrDist * 2;
		colors[#colors + 1] = (interp * lowColor) +
			((1 - interp) * highColor);
	end
	
	colors[#colors + 1] = colors[#colors];

	topFan[#topFan + 1] = 1 + (iSeg * 2);
	botFan[#botFan + 1] = 1 + (((iSegCount - iSeg) * 2) - 1);
end

topFan[#topFan + 1] = topFan[2];
botFan[#botFan + 1] = botFan[2];

positions[#positions + 1] = vmath.vec3(0.0, -0.5, 0.0);
colors[#colors + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
normals[#normals + 1] = vmath.vec3(0.0, -1.0, 0.0);

--Compute sides.
for iSeg = 0, (iSegCount - 1), 1 do
	local iCurrAngle = iSeg * iAngle;

	positions[#positions + 1] =
		vmath.vec3(0.5 * math.cos(iCurrAngle), 0.5, 0.5 * math.sin(iCurrAngle));
	positions[#positions + 1] =
		vmath.vec3(0.5 * math.cos(iCurrAngle), -0.5, 0.5 * math.sin(iCurrAngle));

	normals[#normals + 1] = vmath.vec3(math.cos(iCurrAngle), 0, math.sin(iCurrAngle));
	normals[#normals + 1] = normals[#normals];
		
	local clrDist = math.mod(iCurrAngle, iColorCycleAngle) / iColorCycleAngle;
	if(clrDist > 0.5) then
		local interp = (clrDist - 0.5) * 2;
		colors[#colors + 1] = (interp * highColor) +
			((1 - interp) * lowColor);
	else
		local interp = clrDist * 2;
		colors[#colors + 1] = (interp * lowColor) +
			((1 - interp) * highColor);
	end
	
	colors[#colors + 1] = colors[#colors];

	cylStrip[#cylStrip + 1] = #positions - 2;
	cylStrip[#cylStrip + 1] = #positions - 1;
end

cylStrip[#cylStrip + 1] = cylStrip[1];
cylStrip[#cylStrip + 1] = cylStrip[2];

do
	local writer = XmlWriter.XmlWriter("UnitCylinder.xml");
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
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "tri-strip");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(cylStrip, " "));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end
