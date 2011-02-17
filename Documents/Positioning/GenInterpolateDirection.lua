require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "_utils"

local subImageSize = 300;

local subImages = SubImage.SubImage(1, 1, subImageSize, subImageSize, 50, 0);

local coordSize = 2;

local vp = Viewport.Viewport(subImages:SubSize(), {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local scaleFactor = 0.25;

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 9;

styleLib:AddStyle(nil, "circle", SvgWriter.Style{stroke="black", fill="none"});
styleLib:AddStyle(nil, "center", SvgWriter.Style{stroke="none", fill="black"});

styleLib:AddStyle(nil, "short_path",
	SvgWriter.Style{stroke="blue", stroke_width="8px", fill="none", stroke_opacity="0.3"});
styleLib:AddStyle(nil, "long_path",
	SvgWriter.Style{stroke="red", stroke_width="8px", fill="none", stroke_opacity="0.3"});
	
styleLib:AddStyle(nil, "vector",
	SvgWriter.Style{stroke="black", stroke_width="2px", fill="none", marker_end=SvgWriter.uriLocalElement("arrow")});
	
styleLib:AddStyle(nil, "arrowhead",
	SvgWriter.Style():stroke("none"):fill("black"));
	
styleLib:AddStyle(nil, "label",
	SvgWriter.Style():stroke("none"):fill("black"):font_size("14pt")
		:font_family("monospace"):text_anchor("middle"));

--Circle
local centerPt = vmath.vec2(0, 0);
local radius = 0.8

--Vectors
local vectorAngles = {20, 140, 200}
local vectorEndpts = {}

for i, angle in ipairs(vectorAngles) do
	local radAngle = math.rad(angle);
	vectorEndpts[#vectorEndpts + 1] =
		vmath.vec2(math.cos(radAngle), math.sin(radAngle)) * radius;
end

--Labels
local labelLocs = {};

for i, endPt in ipairs(vectorEndpts) do
	labelLocs[#labelLocs + 1] = (endPt + centerPt) / 2.0;
end

local labelData =
{
	{"q1", vmath.vec2(0, 25)},
	{"q2", vmath.vec2(17, -7)},
	{"-q1", vmath.vec2(0, 25)},
}

--Transform
centerPt = vp:Transform(centerPt);
radius = vp:Length(radius);
vectorEndpts = vp:Transform(vectorEndpts);
labelLocs = vp:Transform(labelLocs);

--Arcs
local shortArc = SvgWriter.Path();
shortArc:M(vectorEndpts[2]):A({radius, radius}, 0, 0, 0, vectorEndpts[3])

local longArc = SvgWriter.Path();
longArc:M(vectorEndpts[2]):A({radius, radius}, 0, 0, 1, vectorEndpts[1])

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {(subImages:Size().x + 1) .."px", (subImages:Size().y + 1) .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_point");
			writer:Circle(vmath.vec2(0, 0), pointRadius, {"vertex"});
		writer:EndGroup();
		WriteStandardArrowhead(writer, "arrow", {"arrowhead"})
	writer:EndDefinitions();
	
	writer:Circle(centerPt, radius, {"circle"});
	
	for i, endPt in ipairs(vectorEndpts) do
		writer:Line(centerPt, endPt, {"vector"});
	end
	
	writer:Path(shortArc, {"short_path"});
	writer:Path(longArc, {"long_path"});

	writer:Circle(centerPt, 8, {"center"});
	
	for i, labelPos in ipairs(labelLocs) do
		writer:Text(labelData[i][1], labelPos + labelData[i][2], {"label"});
	end

writer:Close();
