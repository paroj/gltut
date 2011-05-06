require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local pixelSize = nil;

local hFile = io.open("PixelImage.txt", "r");
local numColors = nil;
local colorTable = {};
local pixelData = {};
for line in hFile:lines() do
	if(not numColors) then
		--Header.
		local width, height, colorCount = line:match("(%d+) (%d+) (%d+)");
		assert(width);
		pixelSize = vmath.vec2(width, height);
		numColors = colorCount;
	else
		if(numColors ~= 0) then
			--Color
			local clrChar, clrValue = line:match("(%S) c (%#%x%x%x%x%x%x)");
			assert(clrChar, line);
			colorTable[clrChar] = clrValue
			numColors = numColors - 1;
		else
			--Pixel data.
			if(#line ~= 0) then
				pixelData[#pixelData + 1] = line;
			end
		end
	end
end
hFile:close();

local magnification = 16;
local spacing = 40;

local imageWidth = pixelSize.x + spacing + (pixelSize.x * magnification);
local imageHeight = pixelSize.y * magnification;

local styleLib = SvgWriter.StyleLibrary();

local styleMap = {};
local styleIndex = 0;
for clrChar, clrValue in pairs(colorTable) do
	local styleName = "color_" .. styleIndex;
	styleMap[clrChar] = styleName;
	styleLib:AddStyle(nil, styleName,
		SvgWriter.Style():stroke("none"):fill(clrValue));
	styleIndex = styleIndex + 1;
end


	
local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {imageWidth .."px", imageHeight .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	for i, row in ipairs(pixelData) do
		local pixelX = 0;
		for clrChar in row:gmatch("%S") do
			writer:Rect({pixelX, i-1}, {1, 1}, nil, {styleMap[clrChar]});
			pixelX = pixelX + 1;
		end
	end

	local offset = vmath.vec2(pixelSize.x + spacing, 0);
	for i, row in ipairs(pixelData) do
		local pixelX = 0;
		for clrChar in row:gmatch("%S") do
			assert(styleMap[clrChar]);
			local location = vmath.vec2(pixelX, i-1);
			location = location * magnification;
			location = location + offset;
			writer:Rect(location, {magnification, magnification},
				nil, {styleMap[clrChar]});
			pixelX = pixelX + 1;
		end
	end

writer:Close();



