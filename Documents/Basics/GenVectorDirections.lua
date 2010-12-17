require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local subImages = SubImage.SubImage(1, 1, 300, 300, 100, 0);

local coordSize = 10;

local vp = Viewport.Viewport({300, 300}, {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local vectorColor = "black";
local pointSize = 15;

styleLib:AddStyle(nil, "vector",
	SvgWriter.Style():stroke(vectorColor):marker_end(SvgWriter.uriLocalElement("arrow")));
styleLib:AddStyle(nil, "text",
	SvgWriter.Style():stroke("none"):fill(vectorColor):font_weight("bold"):font_size("25px"):font_family("monospace") );

local axisData = GridAxis.GridAxis2D(vp, nil, styleLib, true, nil);

local vectors =
{
	vmath.vec2(0, 0),
	vmath.vec2(2, 3),

	vmath.vec2(4, -4),
	vmath.vec2(2, -3),

	vmath.vec2(-2.5, 4),
	vmath.vec2(-1.5, -1),

	vmath.vec2(-2.3, -2.7),
	vmath.vec2(-4.3, -1.7),
};

local labelOffset = vmath.vec2(5, -12);

local vectorLabels = 
{
	"A", vmath.vec2(10, 10),
	"B", vmath.vec2(5, -5),
	"C", vmath.vec2(5, 0),
	"D", vmath.vec2(-10, 25),
}

vectors = vp:Transform(vectors);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	axisData:AddDefinitions(writer, "g_axes");
	writer:BeginDefinitions();
		writer:BeginMarker({10, 8}, {10, 4}, "auto", true, nil, "arrow");
			writer:Path(StandardArrowheadPath(), {"fill_black", "thin"});
		writer:EndMarker();
	writer:EndDefinitions();

	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());

	for i=1, #vectors, 2 do
		writer:Line(vectors[i], vectors[i + 1], {"vector"});
		writer:Text(vectorLabels[i],
			((vectors[i] + vectors[i + 1]) / 2) + vectorLabels[i + 1], {"text"});
	end
writer:Close();
