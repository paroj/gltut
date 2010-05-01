require "SvgWriter"
require "vmath"

--Parameters
local subImageWidth, subImageHeight = 200, 300;
local subImageSpacing = 100;
local numSubImages = 3;

local imageWidth = (subImageWidth * numSubImages) + (subImageSpacing * (numSubImages - 1));
local imageHeight = subImageHeight;

local subImageSize = {subImageWidth, imageHeight};

local subImagePositions = {}

for i = 1, numSubImages, 1 do
	subImagePositions[i] = {(subImageWidth + subImageSpacing) * (i-1), 0};
end

local gridSize = subImageWidth / 8;

-- Styles
local styleLib = SvgWriter.StyleLibrary();

styleLib:AddStyle(nil, "black",
	SvgWriter.Style():stroke("black"):stroke_width("1px"));
	
styleLib:AddStyle(nil, "wide_black",
	SvgWriter.Style():stroke("black"):stroke_width("3px"));
	
styleLib:AddStyle(nil, "trans_wide_black",
	SvgWriter.Style():stroke("black"):stroke_width("3px"):stroke_opacity(0.4));
	
styleLib:AddStyle(nil, "grey",
	SvgWriter.Style():stroke("#C0C0C0"):stroke_width("1px"));
	
styleLib:AddStyle(nil, "wide_grey",
	SvgWriter.Style():stroke("#C0C0C0"):stroke_width("3px"));
	
styleLib:AddStyle(nil, "trans_wide_grey",
	SvgWriter.Style():stroke("#C0C0C0"):stroke_width("3px"):stroke_opacity(0.1));

styleLib:AddStyle(nil, "no_stroke",
	SvgWriter.Style():stroke("none"));
	
styleLib:AddStyle(nil, "dashed",
	SvgWriter.Style():stroke_dasharray({3, 3}));
	
styleLib:AddStyle(nil, "fill_black",
	SvgWriter.Style():fill("black"));
	
styleLib:AddStyle(nil, "fill_none",
	SvgWriter.Style():fill("none"));
	
styleLib:AddStyle(nil, "fill_blue",
	SvgWriter.Style():fill("blue"));

styleLib:AddStyle(nil, "pointed",
	SvgWriter.Style():marker(SvgWriter.uriLocalElement("point")));

-- Paths and other data.

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();

local gridPath = SvgWriter.Path();
for x = (gridSize/2), subImageWidth, gridSize do
	gridPath:M{x, 0}:V(subImageHeight)
end

for y = (gridSize/2), subImageHeight, gridSize do
	gridPath:M{0, y}:H(subImageWidth)
end

local centerPositions = {}

for x = gridSize, subImageWidth - 1, gridSize do
	for y = gridSize, subImageHeight - 1, gridSize do
		centerPositions[#centerPositions + 1] = {x, y}
	end
end

local fillSquareIndices =
{
	{3, 6},
	{3, 7},
	{3, 8},
	{3, 9},

	{4, 3},
	{4, 4},
	{4, 5},
	{4, 6},
	{4, 7},
	{4, 8},
	{4, 9},

	{5, 5},
	{5, 6},
	{5, 7},
	{5, 8},

	{6, 7},
}

local fillSquarePositions = {}

for i, index in ipairs(fillSquareIndices) do
	fillSquarePositions[#fillSquarePositions + 1] =
		{((index[1] - 1) * gridSize) + (gridSize/2), ((index[2] - 1) * gridSize) + (gridSize/2)}
end


-- The SVG itself.
local writer = SvgWriter.SvgWriter("TriangleScanConvert.svg", {imageWidth .."px", imageHeight .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginMarker({gridSize/2, gridSize/2}, {gridSize/4, gridSize/4}, "auto", true, nil, "point");
			writer:Circle({gridSize/4, gridSize/4}, gridSize/4, {"black", "fill_black"});
		writer:EndMarker();
		writer:BeginGroup(nil, "g_triangle");
			writer:Polygon({{95, 50}, {160, 190}, {50, 260}})
		writer:EndGroup();
		writer:BeginGroup(nil, "g_grid");
			writer:Path(gridPath);
		writer:EndGroup();
		writer:BeginGroup(nil, "g_gridCenters");
			for i, pos in ipairs(centerPositions) do
				writer:Circle(pos, gridSize/7);
			end
		writer:EndGroup();
		writer:BeginGroup(nil, "g_scanConvert");
			for i, pos in ipairs(fillSquarePositions) do
				writer:Rect(pos, {gridSize, gridSize});
			end
		writer:EndGroup();
	writer:EndDefinitions();

	--First subimage: just the triangle.
	writer:Use("g_triangle", subImagePositions[1], subImageSize, {"black", "fill_none"});
	
	--Second subimage: triangle + grid + circles
	writer:Use("g_grid", subImagePositions[2], subImageSize, {"black", "fill_none"});
	writer:Use("g_gridCenters", subImagePositions[2], subImageSize, {"black", "fill_none"});
	writer:Use("g_triangle", subImagePositions[2], subImageSize, {"trans_wide_black", "fill_none"});

	--Third subimage: triangle + grid + fill.
	writer:Use("g_scanConvert", subImagePositions[3], subImageSize, {"no_stroke", "fill_blue"});
	writer:Use("g_grid", subImagePositions[3], subImageSize, {"black", "fill_none"});
	writer:Use("g_triangle", subImagePositions[3], subImageSize, {"trans_wide_black", "fill_none"});

	
writer:Close();



