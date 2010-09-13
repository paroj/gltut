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
local fan1 = {};
local fan2 = {};

positions[#positions + 1] = vmath.vec3(0.0, 0.866, 0.0);
colors[#colors + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
fan1[#fan1 + 1] = 0;

local iSegCount, iColorRepeatCount = ...;
iSegCount = iSegCount or 30;
iColorRepeatCount = iColorRepeatCount or 3;

local iAngle = 3.14159 * 2.0 / iSegCount;
local iColorCycleAngle = 3.14159 * 2.0 / iColorRepeatCount;
local highColor = vmath.vec4(0.9, 0.9, 0.9, 1.0);
local lowColor = vmath.vec4(0.5, 0.5, 0.5, 1.0)

for iSeg = 0, (iSegCount - 1), 1 do
	local iCurrAngle = iSeg * iAngle;

	positions[#positions + 1] =
		vmath.vec3(0.5 * math.cos(iCurrAngle), 0.0, 0.5 * math.sin(iCurrAngle));

	fan1[#fan1 + 1] = iSeg + 1;

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
end

--Close the figure.
fan1[#fan1 + 1] = fan1[2];


fan2[#fan2 + 1] = (iSegCount) + 1;

for iSeg = (iSegCount - 1), 0, -1 do
	fan2[#fan2 + 1] = iSeg + 1;
end

--Close the figure.
fan2[#fan2 + 1] = fan2[2];

positions[#positions + 1] = vmath.vec3(0.0, 0.0, 0.0);
colors[#colors + 1] = highColor;

do
	local writer = XmlWriter.XmlWriter("UnitConeTint.xml");
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
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "tri-fan");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(fan1, " "));
		writer:PopElement();
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "tri-fan");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(fan2, " "));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end

do
	local writer = XmlWriter.XmlWriter("UnitCone.xml");
	writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
	writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");
		writer:PushElement("attribute");
			writer:AddAttribute("index", "0");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(positions));
		writer:PopElement();
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "tri-fan");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(fan1, " "));
		writer:PopElement();
		writer:PushElement("indices");
			writer:AddAttribute("cmd", "tri-fan");
			writer:AddAttribute("type", "ushort");
			writer:AddText(table.concat(fan2, " "));
		writer:PopElement();
	writer:PopElement();
	writer:Close();
end
