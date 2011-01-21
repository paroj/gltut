require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "Colors"
require "_utils"

local imageSize = vmath.vec2(500, 300);

local subImages = SubImage.SubImage(1, 1, imageSize.x, imageSize.y, 0, 0);

local coordSize = 10;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

local vp = Viewport.Viewport({500, 300}, {0, 3}, {coordWidth, coordSize})
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
	vmath.vec2(-coordWidth / 2, 0), vmath.vec2(coordWidth / 2, -3),
};

local lightSourcePos = vmath.vec2(-7, 6);
local lightSourceRadius = 20;

surfaceDim = vp:Transform(surfaceDim);
lightSourcePos = vp:Transform(lightSourcePos);

--Light rays
local posRayStart = -4.0;

local rayPoints =
{
	-3, 0,
}

local rayLines = {}

for i,pos in ipairs(rayPoints) do
	rayLines[#rayLines + 1] = vmath.vec2(pos, 0);
end

rayLines = vp:Transform(rayLines);


--Labels
local viewLabel =
{
	{"A", vmath.vec2(12, 5)},
	{"B", vmath.vec2(12, 5)},
}

local reflectLabelOffset = vmath.vec2(0, 20)

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

	--Draw lines.
	for i=1, #rayLines do
		writer:Line(lightSourcePos, rayLines[i], {"lightRay"});
	end
	
	--Draw reflections.
	local finalPos = {}
	for i=1, #rayLines do
		local incident = vmath.norm(rayLines[i] - lightSourcePos);
		local reflect = vmath.vec2(incident.x, -incident.y);
		
		local yLen = surfaceDim[1].y - lightSourcePos.y;
		local len = yLen / incident.y;
		finalPos[i] = (len * reflect) + rayLines[i];
		
		writer:Line(finalPos[i], rayLines[i], {"lightRay"});
	end

	writer:Circle(lightSourcePos, lightSourceRadius, {"light"});
	
	for i=1, #viewLabel do
		local label = viewLabel[i];
		writer:Text(label[1], label[2] + finalPos[i], {"label"});
		writer:Use("g_point", finalPos[i], radiusPt * 2);
	end

	writer:Use("g_point", rayLines[1], radiusPt * 2);
	writer:Text("P", rayLines[1] + reflectLabelOffset, {"label"});
	
writer:Close();
