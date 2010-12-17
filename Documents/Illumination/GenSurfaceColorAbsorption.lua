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

local rayColors =
{
	"blue", "lightblue", "orange", "red", "blue", "lightblue", "violet", "gainsboro",
	"seashell", "lightblue", "fuchsia", "darksalmon", "lightblue", "gold", "lightblue",
};

local lightSourceColor = "yellow";
local surfaceColor = "lightblue";

styleLib:AddStyle(nil, "surface", SvgWriter.Style():stroke("none"):fill(surfaceColor));
styleLib:AddStyle(nil, "light", SvgWriter.Style():stroke("none"):fill(lightSourceColor));

for i,color in ipairs(rayColors) do
	styleLib:AddStyle(nil, "ray-" .. color, SvgWriter.Style():stroke(color):stroke_width("1px"));
end
	
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

local rayLines = {}
for i,pos in ipairs(rayColors) do
	rayLines[#rayLines + 1] = vmath.vec2(-4.0 + ((i - 1) * 0.5), 0);
end

rayLines = vp:Transform(rayLines);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		WriteStandardArrowhead(writer, "arrow", {"arrowhead"});
		WriteStandardArrowhead(writer, "arrow-sum", {"arrowhead-sum"});
	writer:EndDefinitions();

--	axisData:AddDefinitions(writer, "g_axes");
--	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());
	
	--Draw lines.
	for i=1, #rayLines do
		writer:Line(lightSourcePos, rayLines[i], {"ray-" .. rayColors[i]});
	end
	
	--Draw reflections.
	for i=1, #rayLines do
		if(rayColors[i] == surfaceColor) then
			local incident = vmath.norm(rayLines[i] - lightSourcePos);
			local reflect = vmath.vec2(incident.x, -incident.y);
			
			local yLen = surfaceDim[1].y - lightSourcePos.y;
			local len = yLen / incident.y;
			local finalPos = (len * reflect) + rayLines[i];
			
			writer:Line(finalPos, rayLines[i], {"ray-" .. rayColors[i]});
		end
	end
	
	--Draw surface and light.
	writer:Rect2Pt(surfaceDim[1], surfaceDim[2], nil, {"surface"});
	writer:Circle(lightSourcePos, lightSourceRadius, {"light"});

writer:Close();
