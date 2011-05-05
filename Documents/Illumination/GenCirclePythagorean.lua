require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local subImages = SubImage.SubImage(1, 1, 350, 250, 100, 0);

local coordSize = 12;

local vp = Viewport.Viewport(subImages:SubSize(), {0, 2}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local vectorColor = "darkgreen";
local vectorFindColor = "darkorange";
local circleColor = "black";
local pointSize = 15;

styleLib:AddStyle(nil, "vector", SvgWriter.Style{
	stroke=vectorColor, stroke_width="2px", marker_end=SvgWriter.uriLocalElement("arrow")});
styleLib:AddStyle(nil, "arrowhead", SvgWriter.Style{
	stroke=vectorColor, fill=vectorColor});
styleLib:AddStyle(nil, "text", SvgWriter.Style{
	stroke="none", fill=vectorColor, font_weight="bold",
	font_size="25px", font_family="monospace"});
	
styleLib:AddStyle(nil, "vector-hyp", SvgWriter.Style{
	stroke=vectorFindColor, stroke_width="2px", marker_end=SvgWriter.uriLocalElement("arrow-hyp")});
styleLib:AddStyle(nil, "arrowhead-hyp", SvgWriter.Style{
	stroke=vectorFindColor, fill=vectorFindColor});
styleLib:AddStyle(nil, "text-hyp", SvgWriter.Style{
	stroke="none", fill=vectorFindColor, font_weight="bold",
	font_size="25px", font_family="monospace"});
	
styleLib:AddStyle(nil, "circle", SvgWriter.Style{
	stroke=circleColor, fill="none"});

	
local axisData = GridAxis.GridAxis2D(vp, 
	SvgWriter.Style{stroke="black", fill="none", stroke_width="1px"},
	styleLib, false, nil);

--Compute circle.	
local circleRadius = (coordSize / 2) - 1;
local vpRadius = vp:Length(circleRadius);

local circlePts =
{
	vmath.vec2(circleRadius, 0),
	vmath.vec2(-circleRadius, 0),
}

circlePts = vp:Transform(circlePts);

local circlePath = SvgWriter.Path();
circlePath:M(circlePts[1]):A({vpRadius, vpRadius}, 0, 1, 0, circlePts[2]);

--Compute vectors
local angle = math.pi * 0.20;
local circlePos = vmath.vec2(math.cos(angle), math.sin(angle)) * circleRadius;

local vectors =
{
	vmath.vec2(0, 0),
	vmath.vec2(circlePos.x, 0),

	vmath.vec2(circlePos.x, 0),
	vmath.vec2(circlePos),

	vmath.vec2(0, 0),
	vmath.vec2(circlePos),
};

local vectorLabels = 
{
	"X", vmath.vec2(0, 22),
	"Y", vmath.vec2(5, 10),
	"R", vmath.vec2(-5, -15),
}

local styles =
{
	{{"vector"}, {"text"}}, 
	{{"vector-hyp"}, {"text-hyp"}}, 
	{{"vector"}, {"text"}}, 
};

vectors = vp:Transform(vectors);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	axisData:AddDefinitions(writer, "g_axes");
	writer:BeginDefinitions();
		WriteStandardArrowhead(writer, "arrow", {"arrowhead"});
		WriteStandardArrowhead(writer, "arrow-hyp", {"arrowhead-hyp"});
	writer:EndDefinitions();

	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());
	
	writer:Path(circlePath, {"circle"});

	for i=1, #vectors, 2 do
		writer:Line(vectors[i], vectors[i + 1], styles[(i+1)/2][1]);
		writer:Text(vectorLabels[i],
			((vectors[i] + vectors[i + 1]) / 2) + vectorLabels[i + 1], styles[(i+1)/2][2]);
	end
writer:Close();
