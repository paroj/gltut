require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local imageSize = vmath.vec2(500, 300);

local subImages = SubImage.SubImage(1, 1, imageSize.x, imageSize.y, 0, 0);

local coordSize = 10;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

local vp = Viewport.Viewport({500, 300}, {0, 3}, {coordWidth, coordSize})
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local lightSourceColor = "yellow";
local surfaceColor = "lightblue";

styleLib:AddStyle(nil, "surface", SvgWriter.Style():stroke("none"):fill(surfaceColor));
styleLib:AddStyle(nil, "light", SvgWriter.Style():stroke("none"):fill(lightSourceColor));
styleLib:AddStyle(nil, "arrowhead",
	SvgWriter.Style():stroke(surfaceColor):fill(surfaceColor));
	
styleLib:AddStyle(nil, "ray",
	SvgWriter.Style():stroke(surfaceColor):stroke_width("1px"):stroke_dasharray({3, 3}):marker_end(SvgWriter.uriLocalElement("arrow")));
	
styleLib:AddStyle(nil, "incident-ray",
	SvgWriter.Style():stroke(surfaceColor):stroke_width("2px"):marker_end(SvgWriter.uriLocalElement("arrow")));
	
local axisData = GridAxis.GridAxis2D(vp, nil, styleLib, true, nil);

--Surface and light.
local surfaceDim =
{
	vmath.vec2(-coordWidth / 2, 0), vmath.vec2(coordWidth / 2, -3),
};

local lightSourcePos = vmath.vec2(-7, 6);
local lightSourceRadius = 20;

surfaceDim = vp:Transform(surfaceDim);
lightSourcePos = vp:Transform(lightSourcePos);

--Light rays
local intersectPt = vmath.vec2(0, 0);

intersectPt = vp:Transform(intersectPt);

--Diffuse Rays
local rayEndPts = {};
local iNumRays = 11;

local length = 3;

for i = 1, iNumRays do
	local angle = -math.pi / 2;
	angle = angle + ((math.pi / (iNumRays + 1)) * i);
	rayEndPts[#rayEndPts + 1] = length * vmath.vec2(math.sin(angle), math.cos(angle));
end

rayEndPts = vp:Transform(rayEndPts);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		WriteStandardArrowhead(writer, "arrow", {"arrowhead"});
	writer:EndDefinitions();

--	axisData:AddDefinitions(writer, "g_axes");
--	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());
	
	--Draw lines.
	writer:Line(lightSourcePos, intersectPt, {"incident-ray"});
	
	--Draw diffuse reflections.
	for i = 1, iNumRays do
		writer:Line(intersectPt, rayEndPts[i], {"ray"});
	end
	
	--Draw surface and light.
	writer:Rect2Pt(surfaceDim[1], surfaceDim[2], nil, {"surface"});
	writer:Circle(lightSourcePos, lightSourceRadius, {"light"});

writer:Close();
