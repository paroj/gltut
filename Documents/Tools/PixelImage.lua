require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "_utils"

module(..., package.seeall);

local function AddMembersToClass(theTable, theMembers)
	for funcName, func in pairs(theMembers) do
		theTable[funcName] = func;
	end
	
	return theTable;
end

local ImageMembers = {}

function ImageMembers:Size()
	return vmath.vec2(self.imageSize);
end

function ImageMembers:Style(styleLib, prefix)
	prefix = prefix or "color_"
	
	assert(not self.styleMap, "Can only write style once.");
	local styleMap = {};
	self.styleMap = styleMap;
	
	local styleIndex = 0;
	for clrChar, clrValue in pairs(self.colorTable) do
		local styleName = prefix .. styleIndex;
		styleMap[clrChar] = styleName;
		styleLib:AddStyle(nil, styleName,
			SvgWriter.Style():stroke("none"):fill(clrValue));
		styleIndex = styleIndex + 1;
	end
end

function ImageMembers:Draw(writer, topLeft, widthHeight, gridStyles, gridId)
	assert(self.styleMap, "Style has not been added yet.");
	
	local offset = topLeft;
	local scale = widthHeight / self.imageSize;
	for i, row in ipairs(self.pixelData) do
		local pixelX = 0;
		for clrChar in row:gmatch("%S") do
			assert(self.styleMap[clrChar]);
			local location = vmath.vec2(pixelX, i-1);
			location = location * scale;
			location = location + offset;
			writer:Rect(location, scale,
				nil, {self.styleMap[clrChar]});
			pixelX = pixelX + 1;
		end
	end
	
	if(not gridStyles) then
		return;
	end
	
	local path = SvgWriter.Path()
	--Draw the grid, using the given style set.
	for y = 2, self.imageSize[2] do
		local location = vmath.vec2(0, y-1);
		location = location * scale;
		location = location + offset;
		path:M(location):h(widthHeight[1])
	end
	for x = 2, self.imageSize[1] do
		local location = vmath.vec2(x-1, 0);
		location = location * scale;
		location = location + offset;
		path:M(location):v(widthHeight[2])
	end
	
	writer:Path(path, gridStyles, gridId);
end

function ImageMembers:DrawPixelRect(writer, topLeft, widthHeight,
									pixelTopLeft, pixelWidthHeight,
									style, id)
	pixelWidthHeight = pixelWidthHeight or vmath.vec2(1, 1);
	local offset = topLeft;
	local scale = widthHeight / self.imageSize;
	
	local location = vmath.vec2(pixelTopLeft);
	location = location * scale;
	location = location + offset;

	writer:Rect(location, scale * pixelWidthHeight, nil, style, id);
end

function ImageMembers:RectForSamplePt(samplePt)
	local pixelCoordX, remainX = math.modf(samplePt.x);
	if(remainX < 0.5) then
		pixelCoordX = pixelCoordX - 1;
	end

	local pixelCoordY, remainY = math.modf(self.imageSize[2] - samplePt.y);
	if(remainY < 0.5) then
		pixelCoordY = pixelCoordY - 1;
	end

	return vmath.vec2(pixelCoordX, pixelCoordY), vmath.vec2(2, 2)
end



function PixelImage(imageFilename)
	local image = {};
	
	local hFile = io.open(imageFilename, "rt");
	local numColors = nil;
	image.pixelData = {}
	image.colorTable = {};
	for line in hFile:lines() do
		if(not numColors) then
			--Header.
			local width, height, colorCount = line:match("(%d+) (%d+) (%d+)");
			assert(width);
			image.imageSize = vmath.vec2(width, height);
			numColors = colorCount;
		else
			if(numColors ~= 0) then
				--Color
				local clrChar, clrValue = line:match("(%S) c (%#%x%x%x%x%x%x)");
				assert(clrChar, line);
				image.colorTable[clrChar] = clrValue
				numColors = numColors - 1;
			else
				--Pixel data.
				if(#line ~= 0) then
					image.pixelData[#image.pixelData + 1] = line;
				end
			end
		end
	end
	hFile:close();

	return 	AddMembersToClass(image, ImageMembers)
end

function RectForSamplePt(image, samplePt)
	return image:RectForSamplePt(samplePt)
end

