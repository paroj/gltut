require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"

local subImages = SubImage.SubImage(1, 1, 300, 300, 100, 0);

local coordSize = 10;

local vp = Viewport.Viewport({300, 300}, {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local objectColor = "#AFAFFF";
local pointSize = 15;

styleLib:AddStyle(nil, "point",
	SvgWriter.Style():stroke(objectColor):fill(objectColor));
styleLib:AddStyle(nil, "text",
	SvgWriter.Style():stroke("none"):fill(objectColor):font_size("25px"):font_family("monospace"):font_weight("bold") );

local axisData = GridAxis.GridAxis2D(vp, nil, styleLib, true, nil);

local points =
{
	vmath.vec2(2, 3),
	vmath.vec2(-3, 2.5),
	vmath.vec2(0.5, -3),
};

local labelOffset = vmath.vec2(5, -12);

local pointLabels = 
{
	"A",
	"B",
	"C",
}

points = vp:Transform(points);

local writer = SvgWriter.SvgWriter("VectorPosition.svg", {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	axisData:AddDefinitions(writer, "g_axes");
	
	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());

	local circlePos = vp:Transform(vmath.vec2(2, 3));

	for i=1, #points do
		writer:Circle(points[i], pointSize / 2, {"point"});
		writer:Text(pointLabels[i], points[i] + labelOffset, {"text"});
	end
writer:Close();
