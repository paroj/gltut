require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "_utils"

local subImageSize = 200;

local subImages = SubImage.SubImage(1, 1, subImageSize, subImageSize, 50, 0);

local coordSize = 2;

local vp = Viewport.Viewport(subImages:SubSize(), {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local scaleFactor = 0.25;

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 9;
local textSize = 25;

styleLib:AddStyle(nil, "line",
	SvgWriter.Style():stroke("red"):stroke_width("1.5px"):fill("none"));
	
styleLib:AddStyle(nil, "axes",
	SvgWriter.Style():stroke("black"):stroke_width("2.5px"):fill("none"));
	

--Vertices
local bottom = -0.6;
local left = -0.8;

local linePts =
{
	vmath.vec2(left, bottom),
	vmath.vec2(0.0, 0.3),
	vmath.vec2(0.8, 0.6),
};

linePts = vp:Transform(linePts);

local axesPts =
{
	vmath.vec2(left, 1.0),
	vmath.vec2(left, bottom),
	vmath.vec2(1.0, bottom),
};

axesPts = vp:Transform(axesPts);

--Vertices
local pointRadius = 5;
local radiusPt = vmath.vec2(pointRadius, pointRadius);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), subImages:SvgSize());
	writer:StyleLibrary(styleLib);

	writer:Polyline(axesPts, {"axes"});
	writer:Polyline(linePts, {"line"});
writer:Close();
