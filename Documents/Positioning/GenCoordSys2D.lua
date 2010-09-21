require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"

local subImages = SubImage.SubImage(1, 2, 300, 300, 0, 100);

local coordSize = 8;
local dotRadius = 5;

local vp = Viewport.Viewport({300, 300}, {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 10;

styleLib:AddStyle(nil, "black",
	SvgWriter.Style():stroke("black"));
	
styleLib:AddStyle(nil, "x_axis_marker",
	SvgWriter.Style():stroke("green"):fill("none"):stroke_width("3px"));
	
styleLib:AddStyle(nil, "y_axis_marker",
	SvgWriter.Style():stroke("red"):fill("none"):stroke_width("3px"));
	
styleLib:AddStyle(nil, "x_axis",
	SvgWriter.Style():stroke("green"):stroke_width("3px"):marker_end(SvgWriter.uriLocalElement("big_arrow_x_axis")));
	
styleLib:AddStyle(nil, "y_axis",
	SvgWriter.Style():stroke("red"):stroke_width("3px"):marker_end(SvgWriter.uriLocalElement("big_arrow_y_axis")));
	
styleLib:AddStyle(nil, "wide",
	SvgWriter.Style():stroke_width("2px"));
	
styleLib:AddStyle(nil, "thin",
	SvgWriter.Style():stroke_width("1px"));

styleLib:AddStyle(nil, "fill_black",
	SvgWriter.Style():fill("black"));
	
styleLib:AddStyle(nil, "fill_none",
	SvgWriter.Style():fill("none"));

styleLib:AddStyle(nil, "arrow_end",
	SvgWriter.Style():marker_end(SvgWriter.uriLocalElement("arrow")));

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();

local bigArrowheadPath = SvgWriter.Path();
bigArrowheadPath:M{0, 0}:L{10, 10}:L{0, 20};

--Generate axes.
local axes = {};

local upperBound, lowerBound = vp:Extents();
axes[#axes + 1] = vmath.vec2((upperBound[1] + lowerBound[1]) / 2, 0);
axes[#axes + 1] = vmath.vec2((upperBound[1] + lowerBound[1]) / 2, lowerBound[2]);
axes[#axes + 1] = vmath.vec2((upperBound[1] + lowerBound[1]) / 2, 0);
axes[#axes + 1] = vmath.vec2((upperBound[1] + lowerBound[1]) / 2, upperBound[2]);
axes[#axes + 1] = vmath.vec2(0, (upperBound[2] + lowerBound[2]) / 2);
axes[#axes + 1] = vmath.vec2(upperBound[1], (upperBound[2] + lowerBound[2]) / 2);
axes[#axes + 1] = vmath.vec2(0, (upperBound[2] + lowerBound[2]) / 2);
axes[#axes + 1] = vmath.vec2(lowerBound[1], (upperBound[2] + lowerBound[2]) / 2);

--Draw Coordinate.
local coordsX = {};
local coordsY = {};

coordsX[#coordsX + 1] = vmath.vec2(0, 0);
coordsX[#coordsX + 1] = vmath.vec2(1, 0);
coordsX[#coordsX + 1] = vmath.vec2(1, 0);
coordsX[#coordsX + 1] = vmath.vec2(2, 0);

coordsY[#coordsY + 1] = vmath.vec2(2, 0);
coordsY[#coordsY + 1] = vmath.vec2(2, 1);
coordsY[#coordsY + 1] = vmath.vec2(2, 1);
coordsY[#coordsY + 1] = vmath.vec2(2, 2);


local writer = SvgWriter.SvgWriter("CoordSys2D.svg", {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginMarker({pointSize, pointSize}, {pointSize/2, pointSize/2}, "auto", true, nil, "point");
			writer:Circle({pointSize/2, pointSize/2}, pointSize/2, {"fill_black", "black"});
		writer:EndMarker();
		writer:BeginMarker({10, 8}, {10, 4}, "auto", true, nil, "arrow");
			writer:Path(arrowheadPath, {"fill_black", "thin"});
		writer:EndMarker();
		writer:BeginMarker({10, 20}, {10, 10}, "auto", true, nil, "big_arrow_y_axis");
			writer:Path(bigArrowheadPath, {"y_axis_marker"});
		writer:EndMarker();
		writer:BeginMarker({10, 20}, {10, 10}, "auto", true, nil, "big_arrow_x_axis");
			writer:Path(bigArrowheadPath, {"x_axis_marker"});
		writer:EndMarker();
	writer:EndDefinitions();

	--Draw the axes for the regular coord system.
	local topAxes = subImages:Transform({1, 1}, vp:Transform(axes))
	for i=1, #axes, 2 do
		writer:Line(topAxes[i], topAxes[i + 1], {"black", "thin", "arrow_end"});
	end
	
	local topCoordX = subImages:Transform({1, 1}, vp:Transform(coordsX))
	for i=1, #topCoordX, 2 do
		writer:Line(topCoordX[i], topCoordX[i + 1], {"x_axis"});
	end
	
	local topCoordY = subImages:Transform({1, 1}, vp:Transform(coordsY))
	writer:Circle(topCoordY[#topCoordY], dotRadius, {"fill_black", "black"});
	for i=1, #topCoordY, 2 do
		writer:Line(topCoordY[i], topCoordY[i + 1], {"y_axis"});
	end
	

	
	--Setup the skewed coordinate system.
	local basisVectors = {};
	local tempTrans = Viewport.Transform2D()
	tempTrans:Rotate(-15);
	basisVectors[1] = tempTrans:Matrix():Transform(vmath.vec2(1, 0));
	tempTrans:Identity();
	tempTrans:Rotate(15);
	basisVectors[2] = tempTrans:Matrix():Transform(vmath.vec2(0, 1));
	tempTrans:Identity();
	
	local transformMatrix = tempTrans:Matrix();
	tempTrans:Identity();
	transformMatrix:SetCol(1, vmath.vec3(basisVectors[1], 0.0));
	transformMatrix:SetCol(2, vmath.vec3(basisVectors[2], 0.0));
	
	--Draw the axes for the skewed coord system.
	trans2:MultMatrix(transformMatrix);
	local botAxes = subImages:Transform({1, 2}, vp:Transform(axes))
	for i=1, #axes, 2 do
		writer:Line(botAxes[i], botAxes[i + 1], {"black", "thin", "arrow_end"});
	end
	
	local botCoordX = subImages:Transform({1, 2}, vp:Transform(coordsX))
	for i=1, #botCoordX, 2 do
		writer:Line(botCoordX[i], botCoordX[i + 1], {"x_axis"});
	end
	
	local botCoordY = subImages:Transform({1, 2}, vp:Transform(coordsY))
	writer:Circle(botCoordY[#topCoordY], dotRadius, {"fill_black", "black"});
	for i=1, #botCoordY, 2 do
		writer:Line(botCoordY[i], botCoordY[i + 1], {"y_axis"});
	end
	
writer:Close();
