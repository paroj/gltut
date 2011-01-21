require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "Colors"
require "_utils"

local imageSize = vmath.vec2(400, 150);

local subImages = SubImage.SubImage(1, 1, imageSize.x, imageSize.y, 0, 0);

local coordSize = 8;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

local vp = Viewport.Viewport(imageSize, {0, 2}, {coordWidth, coordSize})
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local lightSourceColor = Colors.clr("lightSource");
local surfaceColor = Colors.clr("surface");
local textSize = 14;

styleLib:AddStyle(nil, "surface", SvgWriter.Style():stroke("none"):fill(surfaceColor));
styleLib:AddStyle(nil, "light", SvgWriter.Style():stroke("none"):fill(lightSourceColor));

styleLib:AddStyle(nil, "lightRay", SvgWriter.Style():stroke(surfaceColor));

styleLib:AddStyle(nil, "label",
	SvgWriter.Style():stroke("none"):fill("black"):font_size(textSize .. "pt")
		:text_anchor("middle"));
		
styleLib:AddStyle(nil, "point", SvgWriter.Style():stroke("none"):fill("black"));

local axisData = GridAxis.GridAxis2D(vp, nil, styleLib, true, nil);

--Surface and light.
local surfaceDim =
{
	vmath.vec2(-coordWidth / 2, 0), vmath.vec2(coordWidth / 2, -2),
};

local lightPos = vmath.vec2(-7, 2);
local lightSourceRadius = 20;

surfaceDim = vp:Transform(surfaceDim);
lightPos = vp:Transform(lightPos);

--Light rays
local thePoint = vmath.vec2(0, 0);
local viewPoint = vmath.vec2(-4, 4);

thePoint = vp:Transform(thePoint);
viewPoint = vp:Transform(viewPoint);

--Labels
local reflectLabelOffset = vmath.vec2(12, 5)
local pointLabelOffset = vmath.vec2(0, 20)
local viewLabelOffset = vmath.vec2(-12, 5);

--Vertices
local pointRadius = 4;
local radiusPt = vmath.vec2(pointRadius, pointRadius);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_point");
			writer:Circle(vmath.vec2(0, 0), pointRadius, {"vertex"});
		writer:EndGroup();
	writer:EndDefinitions();

	--Draw surface and light.
	writer:Rect2Pt(surfaceDim[1], surfaceDim[2], nil, {"surface"});

	--Draw the light ray.
	writer:Line(lightPos, thePoint, {"lightRay"});

	--Draw the view direction
	writer:Line(viewPoint, thePoint, {"lightRay"});
	
	--Draw the reflection direction.
	local finalPos = {}
	local incident = vmath.norm(thePoint - lightPos);
	local reflect = vmath.vec2(incident.x, -incident.y);
	
	local yLen = surfaceDim[1].y - lightPos.y;
	local len = yLen / incident.y;
	local finalPos = (len * reflect) + thePoint;
	writer:Line(finalPos, thePoint, {"lightRay"});
	
	writer:Circle(lightPos, lightSourceRadius, {"light"});
	
	writer:Use("g_point", finalPos, radiusPt * 2);
	writer:Text("R", reflectLabelOffset + finalPos, {"label"});
	
	writer:Use("g_point", thePoint, radiusPt * 2);
	writer:Text("P", thePoint + pointLabelOffset, {"label"});

	writer:Use("g_point", viewPoint, radiusPt * 2);
	writer:Text("V", viewPoint + viewLabelOffset, {"label"});
	
writer:Close();
