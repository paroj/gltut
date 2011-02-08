require "XmlWriter"
require "vmath"

local function GenStringFromArray(theArray)
	local array = {" "}
	for i, vector in ipairs(theArray) do
		array[#array + 1] = "        " .. table.concat(vector, " ");
	end
	
	return table.concat(array, "\n");
end

local iSegCount = ...;
iSegCount = iSegCount or 40;

local gimbalPoints = {{}, {}, {}};
local gimbalColors = {{}, {}, {}};
local gimbalRadii = {28, 24, 20};
local gimbalConnect = {4, 4, 4};
local gimbalTriStrips = {{}, {}, {}, {}};
local gimbalTris = {};
local gimbalNames = {"Large", "Medium", "Small"};

local iAngle = 3.14159 * 2.0 / iSegCount;

--Compute circle attributes.
local function AddSegments(SegmentFunc)
	for iSeg = 1, iSegCount do
		local iCurrAngle = iSeg * iAngle;
		local radialDir = vmath.vec2(math.cos(iCurrAngle), math.sin(iCurrAngle));
		
		for iGimbal = 1, #gimbalRadii do
			local vShort = radialDir * (gimbalRadii[iGimbal] - 1.0);
			local vLong = radialDir * (gimbalRadii[iGimbal] + 1.0);
			
			SegmentFunc(iGimbal, vShort, vLong)
		end
	end
end

local halfHeight = 1.0;

local SegmentAdders =
{
	function (iGimbal, vShort, vLong)
		local iLen = #gimbalPoints[iGimbal];
		gimbalPoints[iGimbal][iLen + 1] = vmath.vec3(vLong[1], vLong[2], halfHeight);
		gimbalPoints[iGimbal][iLen + 2] = vmath.vec3(vShort[1], vShort[2], halfHeight);
		gimbalColors[iGimbal][iLen + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
		gimbalColors[iGimbal][iLen + 2] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	end,
	function (iGimbal, vShort, vLong)
		local iLen = #gimbalPoints[iGimbal];
		gimbalPoints[iGimbal][iLen + 1] = vmath.vec3(vShort[1], vShort[2], halfHeight);
		gimbalPoints[iGimbal][iLen + 2] = vmath.vec3(vShort[1], vShort[2], -halfHeight);
		gimbalColors[iGimbal][iLen + 1] = vmath.vec4(0.5, 0.5, 0.5, 1.0);
		gimbalColors[iGimbal][iLen + 2] = vmath.vec4(0.5, 0.5, 0.5, 1.0);
	end,
	function (iGimbal, vShort, vLong)
		local iLen = #gimbalPoints[iGimbal];
		gimbalPoints[iGimbal][iLen + 1] = vmath.vec3(vShort[1], vShort[2], -halfHeight);
		gimbalPoints[iGimbal][iLen + 2] = vmath.vec3(vLong[1], vLong[2], -halfHeight);
		gimbalColors[iGimbal][iLen + 1] = vmath.vec4(0.9, 0.9, 0.9, 1.0);
		gimbalColors[iGimbal][iLen + 2] = vmath.vec4(0.9, 0.9, 0.9, 1.0);
	end,
	function (iGimbal, vShort, vLong)
		local iLen = #gimbalPoints[iGimbal];
		gimbalPoints[iGimbal][iLen + 1] = vmath.vec3(vLong[1], vLong[2], -halfHeight);
		gimbalPoints[iGimbal][iLen + 2] = vmath.vec3(vLong[1], vLong[2], halfHeight);
		gimbalColors[iGimbal][iLen + 1] = vmath.vec4(0.75, 0.75, 0.75, 1.0);
		gimbalColors[iGimbal][iLen + 2] = vmath.vec4(0.75, 0.75, 0.75, 1.0);
	end,
}

for i, adder in ipairs(SegmentAdders) do
	AddSegments(adder);
end

--Add the connecting pieces, on the left and right.
local conSize = halfHeight * 0.6;
local function AddConnector(radius, offset, points, color)
	--Inside the current gimbal
	points[#points + 1] = vmath.vec3(radius, conSize, conSize);
	points[#points + 1] = vmath.vec3(radius, -conSize, conSize);
	points[#points + 1] = vmath.vec3(radius, -conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius, conSize, -conSize);
	
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);

	--Inside the outer gimbal.
	points[#points + 1] = vmath.vec3(radius + offset, conSize, conSize);
	points[#points + 1] = vmath.vec3(radius + offset, -conSize, conSize);
	points[#points + 1] = vmath.vec3(radius + offset, -conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius + offset, conSize, -conSize);
	
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	
	--Front.
	points[#points + 1] = vmath.vec3(radius, conSize, conSize);
	points[#points + 1] = vmath.vec3(radius, -conSize, conSize);
	points[#points + 1] = vmath.vec3(radius + offset, -conSize, conSize);
	points[#points + 1] = vmath.vec3(radius + offset, conSize, conSize);
	
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	color[#color + 1] = vmath.vec4(1.0, 1.0, 1.0, 1.0);
	
	--Back.
	points[#points + 1] = vmath.vec3(radius, conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius, -conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius + offset, -conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius + offset, conSize, -conSize);
	
	color[#color + 1] = vmath.vec4(0.9, 0.9, 0.9, 1.0);
	color[#color + 1] = vmath.vec4(0.9, 0.9, 0.9, 1.0);
	color[#color + 1] = vmath.vec4(0.9, 0.9, 0.9, 1.0);
	color[#color + 1] = vmath.vec4(0.9, 0.9, 0.9, 1.0);
	
	--Top.
	points[#points + 1] = vmath.vec3(radius, conSize, conSize);
	points[#points + 1] = vmath.vec3(radius, conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius + offset, conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius + offset, conSize, conSize);
	
	color[#color + 1] = vmath.vec4(0.75, 0.75, 0.75, 1.0);
	color[#color + 1] = vmath.vec4(0.75, 0.75, 0.75, 1.0);
	color[#color + 1] = vmath.vec4(0.75, 0.75, 0.75, 1.0);
	color[#color + 1] = vmath.vec4(0.75, 0.75, 0.75, 1.0);
	
	--Bottom.
	points[#points + 1] = vmath.vec3(radius, -conSize, conSize);
	points[#points + 1] = vmath.vec3(radius, -conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius + offset, -conSize, -conSize);
	points[#points + 1] = vmath.vec3(radius + offset, -conSize, conSize);
	
	color[#color + 1] = vmath.vec4(0.5, 0.5, 0.5, 1.0);
	color[#color + 1] = vmath.vec4(0.5, 0.5, 0.5, 1.0);
	color[#color + 1] = vmath.vec4(0.5, 0.5, 0.5, 1.0);
	color[#color + 1] = vmath.vec4(0.5, 0.5, 0.5, 1.0);
end

for iGimbal = 1, #gimbalRadii do
	local points = gimbalPoints[iGimbal];
	local colors = gimbalColors[iGimbal];

	--Right connector.
	AddConnector(gimbalRadii[iGimbal], gimbalConnect[iGimbal],
		gimbalPoints[iGimbal], gimbalColors[iGimbal]);
	
	--Left connector.
	AddConnector(-gimbalRadii[iGimbal], -gimbalConnect[iGimbal],
		gimbalPoints[iGimbal], gimbalColors[iGimbal]);
end

--Compute strips.
--Number of attributes that each circle strip takes.
local indexOffset = iSegCount * 2;
local function AddStripIndices(strip, baseIndex, stripIx)
	strip[#strip + 1] = baseIndex + indexOffset * stripIx;
	strip[#strip + 1] = baseIndex + indexOffset * stripIx + 1;
end


for iSeg = 1, iSegCount do
	local baseIndex = ((iSeg - 1) * 2);
	AddStripIndices(gimbalTriStrips[1], baseIndex, 0);
	AddStripIndices(gimbalTriStrips[2], baseIndex, 1);
	AddStripIndices(gimbalTriStrips[3], baseIndex, 2);
	AddStripIndices(gimbalTriStrips[4], baseIndex, 3);
end

local lastStripIndex = iSegCount * 2;
AddStripIndices(gimbalTriStrips[1], 0, 0);
AddStripIndices(gimbalTriStrips[2], 0, 1);
AddStripIndices(gimbalTriStrips[3], 0, 2);
AddStripIndices(gimbalTriStrips[4], 0, 3);

local firstTriIndex = indexOffset * 4;
local numValuesPerConnecter = 24;

local connectTris = {
--Inside the current gimbal
	0, 1, 2,
	2, 3, 0,
--Inside the outer gimbal.
	4, 6, 5,
	6, 4, 7,
--Front.
	8, 10, 9,
	11, 10, 8,
--Back.
	12, 13, 14,
	15, 12, 14,
--Top.
	16, 17, 18,
	18, 19, 16,
--Bottom.
	20, 22, 21,
	22, 20, 23,
}

for i=1, #connectTris, 3 do
	connectTris[#connectTris + 1] = connectTris[i] + numValuesPerConnecter;
	connectTris[#connectTris + 1] = connectTris[i + 2] + numValuesPerConnecter;
	connectTris[#connectTris + 1] = connectTris[i + 1] + numValuesPerConnecter;
end

for i, index in ipairs(connectTris) do
	gimbalTris[#gimbalTris + 1] = firstTriIndex + index;
end



--Write the gimbal to the file.
local function WriteGimbal(iGimbal)
	local writer = XmlWriter.XmlWriter(gimbalNames[iGimbal] .. "Gimbal.xml");
	writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
	writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");
		writer:PushElement("attribute");
			writer:AddAttribute("index", "0");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "3");
			writer:AddText(GenStringFromArray(gimbalPoints[iGimbal]));
		writer:PopElement();
		writer:PushElement("attribute");
			writer:AddAttribute("index", "1");
			writer:AddAttribute("type", "float");
			writer:AddAttribute("size", "4");
			writer:AddText(GenStringFromArray(gimbalColors[iGimbal]));
		writer:PopElement();
		for iStrip = 1, #gimbalTriStrips do
			writer:PushElement("indices");
				writer:AddAttribute("cmd", "tri-strip");
				writer:AddAttribute("type", "ushort");
				writer:AddText(table.concat(gimbalTriStrips[iStrip], " "));
			writer:PopElement();
		end
		if(#gimbalTris > 0) then
			writer:PushElement("indices");
				writer:AddAttribute("cmd", "triangles");
				writer:AddAttribute("type", "ushort");
				writer:AddText(table.concat(gimbalTris, " "));
			writer:PopElement();
		end
	writer:PopElement();
	writer:Close();
end

for iGimbal = 1, #gimbalRadii do
	WriteGimbal(iGimbal);
end
