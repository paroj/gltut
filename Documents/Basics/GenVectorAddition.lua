require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local subImages = SubImage.SubImage(1, 1, 300, 300, 100, 0);

local coordSize = 10;

local vp = Viewport.Viewport({300, 300}, {0, 3}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local vectorColor = "black";
local vectorSumColor = "red";
local pointSize = 15;

styleLib:AddStyle(nil, "vector",
	SvgWriter.Style():stroke(vectorColor):marker_end(SvgWriter.uriLocalElement("arrow")));
styleLib:AddStyle(nil, "arrowhead",
	SvgWriter.Style():stroke(vectorColor):fill(vectorColor));
styleLib:AddStyle(nil, "text",
	SvgWriter.Style():stroke("none"):fill(vectorColor):font_weight("bold"):font_size("25px"):font_family("monospace") );
	
styleLib:AddStyle(nil, "vector-sum",
	SvgWriter.Style():stroke(vectorSumColor):marker_end(SvgWriter.uriLocalElement("arrow-sum")));
styleLib:AddStyle(nil, "arrowhead-sum",
	SvgWriter.Style():stroke(vectorSumColor):fill(vectorSumColor));
styleLib:AddStyle(nil, "text-sum",
	SvgWriter.Style():stroke("none"):fill(vectorSumColor):font_weight("bold"):font_size("25px"):font_family("monospace"):text_anchor("end") );
	
local axisData = GridAxis.GridAxis2D(vp, nil, styleLib, true, nil);

local vectors =
{
	vmath.vec2(0, 0),
	vmath.vec2(3, 4),

	vmath.vec2(0, 0),
	vmath.vec2(-4, 2),

	vmath.vec2(0, 0),
	vmath.vec2(-1, 6),
};

local labelOffset = vmath.vec2(5, -12);

local vectorLabels = 
{
	"A", vmath.vec2(10, 10),
	"B", vmath.vec2(5, -5),
	"A+B", vmath.vec2(-20, -40),
}

local styles =
{
	{{"vector"}, {"text"}}, 
	{{"vector"}, {"text"}}, 
	{{"vector-sum"}, {"text-sum"}}, 
};

vectors = vp:Transform(vectors);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	axisData:AddDefinitions(writer, "g_axes");
	writer:BeginDefinitions();
		WriteStandardArrowhead(writer, "arrow", {"arrowhead"});
		WriteStandardArrowhead(writer, "arrow-sum", {"arrowhead-sum"});
	writer:EndDefinitions();

	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());

	for i=1, #vectors, 2 do
		writer:Line(vectors[i], vectors[i + 1], styles[(i+1)/2][1]);
		writer:Text(vectorLabels[i],
			((vectors[i] + vectors[i + 1]) / 2) + vectorLabels[i + 1], styles[(i+1)/2][2]);
	end
writer:Close();
