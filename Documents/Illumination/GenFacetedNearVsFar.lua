require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local imageSize = vmath.vec2(400, 150);

local subImages = SubImage.SubImage(1, 2, imageSize.x, imageSize.y, 0, 0);

local coordSize = 6;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

local vp = Viewport.Viewport(imageSize, {-5, 0}, {coordWidth, coordSize})
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local lightSourceColor = "yellow";
local surfaceColor = "lightblue";
local rayColor = "darkblue";

styleLib:AddStyle(nil, "surface", SvgWriter.Style():stroke("none"):fill(surfaceColor));
styleLib:AddStyle(nil, "light", SvgWriter.Style():stroke("none"):fill(lightSourceColor));
styleLib:AddStyle(nil, "arrowhead",
	SvgWriter.Style():stroke(rayColor):fill(rayColor));
	
styleLib:AddStyle(nil, "ray",
	SvgWriter.Style():stroke(rayColor):stroke_width("1px"):stroke_dasharray({3, 3}):marker_end(SvgWriter.uriLocalElement("arrow")));
	
styleLib:AddStyle(nil, "facets",
	SvgWriter.Style():stroke("black"):stroke_width("1px"):stroke_linejoin("round"):fill(surfaceColor));

styleLib:AddStyle(nil, "circle",
	SvgWriter.Style():stroke("black"):stroke_width("2px"):fill("none"));
	
styleLib:AddStyle(nil, "show_clip",
	SvgWriter.Style():stroke("black"):fill("none"));
	
styleLib:AddStyle(nil, "clip_to_area",
	SvgWriter.Style():clip_path(SvgWriter.uriLocalElement("area_clip")));

	
local axisData = GridAxis.GridAxis2D(vp, nil, styleLib, true, nil);

--Surface and light.
local surfaceDim =
{
	vmath.vec2(0, coordSize / 2),
	vmath.vec2(3, -coordSize / 2),
};

local lightSourcePos = 
{
	vmath.vec2(-11, 0),
	vmath.vec2(-4, 0);
}

local lightSourceRadius = 0.4;

lightSourceRadius = vp:Transform(vmath.vector(lightSourceRadius, lightSourceRadius, 0.0));
lightSourceRadius = math.abs(lightSourceRadius.x);


--Vertices
local circleRadius = 8;

local vpCircleRadius = vp:Transform(vmath.vector(circleRadius, circleRadius, 0.0));
vpCircleRadius = math.abs(vpCircleRadius.x);

local circleCenterPt = vmath.vec2(2, -7);

--Facets
local numFacets = 7;

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

--Diffuse Rays
local function CalcRays(lightPos, rayLen)
	rayLen = rayLen or 3;
	
	local rayLines = {};

	local startAngle = (0 / numFacets) * math.pi * 2 + (math.pi / 2);
	local endAngle = (1 / numFacets) * math.pi * 2 + (math.pi / 2);
	local facetAngle = startAngle + (2 * math.pi / numFacets / 2);
	
	local startLoc = vmath.vec2(math.cos(facetAngle), math.sin(facetAngle));
	startLoc = (startLoc * circleRadius) + circleCenterPt;
	rayLines[#rayLines + 1] = startLoc;
	
	local dir = vmath.norm(lightPos - startLoc);
	rayLines[#rayLines + 1] = startLoc + (dir * rayLen);

	local startPt = vmath.vec2(math.cos(startAngle), math.sin(startAngle));
	local endPt = vmath.vec2(math.cos(endAngle), math.sin(endAngle));
	startPt = (startPt * circleRadius) + circleCenterPt;
	endPt = (endPt * circleRadius) + circleCenterPt;
	
	local midPt = (startPt + endPt) / 2;
	rayLines[#rayLines + 1] = midPt;

	dir = vmath.norm(lightPos - midPt);
	rayLines[#rayLines + 1] = midPt + (dir * rayLen);
	
	return rayLines;
end

local rays =
{
	CalcRays(lightSourcePos[1]),
	CalcRays(lightSourcePos[2], 1.5),
}

surfaceDim = vp:Transform(surfaceDim);
lightSourcePos = vp:Transform(lightSourcePos);
rays[1] = subImages:Transform({1, 1}, vp:Transform(rays[1]));
rays[2] = subImages:Transform({1, 2}, vp:Transform(rays[2]));


local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		WriteStandardArrowhead(writer, "arrow", {"arrowhead"});
		
		writer:BeginGroup(nil, "g_surface");
			--Draw surface and light.
			writer:Rect2Pt(surfaceDim[1], surfaceDim[2], nil, {"surface"});
		writer:EndGroup();
		
		writer:BeginGroup(nil, "g_faceted_circle");
			writer:Circle(vp:Transform(circleCenterPt), vpCircleRadius, {"circle"});
			writer:Path(facetPath, {"facets"});
		writer:EndGroup();
		
		writer:BeginClipPath(nil, "area_clip");
			writer:Rect(subImages:Offset(1, 1), subImages:SubSize(), nil, {"show_clip"});
		writer:EndClipPath();
		
	writer:EndDefinitions();

--	axisData:AddDefinitions(writer, "g_axes");
--	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());
--	writer:Use("g_axes", subImages:Offset(1, 2), subImages:SubSize());


	lightSourcePos[1] = subImages:Transform({1, 1}, lightSourcePos[1]);
	lightSourcePos[2] = subImages:Transform({1, 2}, lightSourcePos[2]);

	writer:Circle(lightSourcePos[1], lightSourceRadius, {"light"});
	writer:Circle(lightSourcePos[2], lightSourceRadius, {"light"});
	
	writer:Use("g_faceted_circle", subImages:Offset(1, 1), subImages:SubSize(), {"clip_to_area"});
	writer:Use("g_faceted_circle", subImages:Offset(1, 2), subImages:SubSize(), {"clip_to_area"});

	for i=1, #rays[1], 2 do
		writer:Line(rays[1][i], rays[1][i + 1], {"ray"});
	end
	for i=1, #rays[2], 2 do
		writer:Line(rays[2][i], rays[2][i + 1], {"ray"});
	end
	



writer:Close();
