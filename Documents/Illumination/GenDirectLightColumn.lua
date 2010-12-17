require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local imageSize = vmath.vec2(300, 300);

local subImages = SubImage.SubImage(1, 1, imageSize.x, imageSize.y, 0, 0);

local coordSize = 10;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

local vp = Viewport.Viewport(imageSize, {0, 3}, {coordWidth, coordSize})
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local lightSourceColor = "yellow";
local surfaceColor = "lightblue";

styleLib:AddStyle(nil, "surface", SvgWriter.Style():stroke("none"):fill(surfaceColor));
styleLib:AddStyle(nil, "light", SvgWriter.Style():stroke("none"):fill(lightSourceColor));
styleLib:AddStyle(nil, "light-ray",
	SvgWriter.Style():stroke("black"):stroke_width("1px"):marker_end(SvgWriter.uriLocalElement("arrow")));
styleLib:AddStyle(nil, "intersect",
	SvgWriter.Style():stroke("black"):stroke_width("4px"));

styleLib:AddStyle(nil, "arrowhead",
	SvgWriter.Style():stroke("black"):fill("black"):stroke_width("1px"));

local axisData = GridAxis.GridAxis2D(vp, nil, styleLib, true, nil);

--Surface.
local surfaceDim =
{
	vmath.vec2(-coordWidth / 2, 0), vmath.vec2(coordWidth / 2, -3),
};

surfaceDim = vp:Transform(surfaceDim);

--Light column
local lightDir = vmath.norm(vmath.vec2(0, -1));
local offsetDir = vmath.vec2(lightDir.y, -lightDir.x);

print(offsetDir)

local lightDirVerts =
{
	(coordSize * 2 * -lightDir),
	(2 * -lightDir),
};

local intersectionPts = {};
local tempPts = {}

tempPts[1] = lightDirVerts[2] + (0.5 * offsetDir)
tempPts[2] = lightDirVerts[2] + (-0.5 * offsetDir)

for i = 1, #tempPts do
	local dist = math.abs(tempPts[i].y / lightDir.y);
	
	intersectionPts[i] = lightDir * dist + tempPts[i];
end

local columnVerts =
{
	vmath.vec2(intersectionPts[1]),
	vmath.vec2(intersectionPts[2]),
	intersectionPts[2] + (-lightDir * coordSize * 2),
	intersectionPts[1] + (-lightDir * coordSize * 2),
};


--[[
local columnVerts =
{
	vmath.vec2(-0.5, coordSize),
	vmath.vec2(-0.5, 0),
	vmath.vec2(0.5, 0),
	vmath.vec2(0.5, coordSize),
}
]]

intersectionPts = vp:Transform(intersectionPts);
columnVerts = vp:Transform(columnVerts);

local columnPath = SvgWriter.Path();
columnPath:M(columnVerts[1]);
for i = 2, #columnVerts do
	columnPath:L(columnVerts[i]);
end
columnPath:Z();

lightDirVerts = vp:Transform(lightDirVerts);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		WriteStandardArrowhead(writer, "arrow", {"arrowhead"});
	writer:EndDefinitions();

--	axisData:AddDefinitions(writer, "g_axes");
--	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());
	
	--Draw light column.
	writer:Path(columnPath, {"light"});
	writer:Line(lightDirVerts[1], lightDirVerts[2], {"light-ray"});
	
	--Draw surface.
	writer:Rect2Pt(surfaceDim[1], surfaceDim[2], nil, {"surface"});
	
	--Draw intersection.
	writer:Line(intersectionPts[1], intersectionPts[2], {"intersect"});

writer:Close();
