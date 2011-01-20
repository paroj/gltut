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

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 9;
local textSize = 25;

styleLib:AddStyle(nil, "facets",
	SvgWriter.Style():stroke("black"):stroke_width("1px"):stroke_linejoin("round"):fill("none"));

styleLib:AddStyle(nil, "circle",
	SvgWriter.Style():stroke("black"):fill("none"));
	

--Vertices
local circleRadius = 0.8;

local vpCircleRadius = vp:Transform(vmath.vector(circleRadius, circleRadius, 0.0));
vpCircleRadius = math.abs(vpCircleRadius.x);

local circleCenterPt = vmath.vec2(0, 0);

--Facets
local numFacets = 8;

local facetPath = SvgWriter:Path();

for i=1, numFacets do
	local angle = ((i - 1) / numFacets) * math.pi * 2 + (math.pi / 2);
	local point = vmath.vec2(math.cos(angle), math.sin(angle));
	point = (point * circleRadius) + circleCenterPt;
	
	point = vp:Transform(point);

	if(i == 1) then
		facetPath:M(point);
	else
		facetPath:L(point);
	end
end

facetPath:Z();

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {(subImages:Size().x + 1) .."px", (subImages:Size().y + 1) .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_faceted_circle");
			writer:Circle(vp:Transform(circleCenterPt), vpCircleRadius, {"circle"});
			writer:Path(facetPath, {"facets"});
		writer:EndGroup();
	writer:EndDefinitions();
	
	writer:Use("g_faceted_circle", subImages:Offset(1, 1), subImages:SubSize());

writer:Close();
