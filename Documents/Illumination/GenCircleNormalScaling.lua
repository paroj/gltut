require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "_utils"

local subImageSize = 250;

local subImages = SubImage.SubImage(3, 1, subImageSize, subImageSize, 50, 0);

local coordSize = 2;

local vp = Viewport.Viewport(subImages:SubSize(), {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local scaleFactor = 0.33;

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 9;

local coordAxisWidth = "2px";
local xCoordAxisColor = "green";
local yCoordAxisColor = "red";
local objectColor = "#E0E0FF";
local normalColor = "red";

styleLib:AddStyle(nil, "circle",
	SvgWriter.Style():stroke("black"):fill("none"));
	
styleLib:AddStyle(nil, "normal",
	SvgWriter.Style():stroke(normalColor):stroke_width("1px"):
		fill(normalColor):marker_end(SvgWriter.uriLocalElement("arrow_normal")));
	
styleLib:AddStyle(nil, "normal_head",
	SvgWriter.Style():stroke(normalColor):stroke_width("1px"):fill(normalColor));

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{8, 4}:L{0, 0}:L{0, 8}:Z();

local bigArrowheadPath = SvgWriter.Path();
bigArrowheadPath:M{0, 0}:L{10, 10}:L{0, 20};

--Cell Border
local borderPath = SvgWriter.Path();
borderPath:M(vp:Transform(vmath.vec2(1, 1)));
borderPath:L(vp:Transform(vmath.vec2(1, -1)));
borderPath:L(vp:Transform(vmath.vec2(-1, -1)));
borderPath:L(vp:Transform(vmath.vec2(-1, 1)));
borderPath:Z();

--Circle/Ellipse radius
local circleRadius = 0.7;
local ellipseRadius = circleRadius * scaleFactor;

local vpCircleRadius = vp:Transform(vmath.vector(circleRadius, circleRadius, 0.0));
vpCircleRadius = math.abs(vpCircleRadius.x);

local vpEllipseRadius = vpCircleRadius * scaleFactor;

local circleCenterPt = vmath.vec2(0, 0);

--Normals for the circles.
local numNormals = 14;
local normalLen = 0.15;

local circleNormals = {};
local badNormals = {};
local goodNormals = {};

local vectorScale = vmath.vec2(1, scaleFactor);

for i = 1, numNormals do
	local angle = ((i - 1) / numNormals) * math.pi * 2 + (math.pi / 2);
	local tail = vmath.vec2(math.cos(angle), math.sin(angle));
	tail = (tail * circleRadius) + circleCenterPt;
	
	local dir = vmath.vec2(math.cos(angle), math.sin(angle));
	
	circleNormals[#circleNormals + 1] = tail;
	circleNormals[#circleNormals + 1] = tail + (dir * normalLen);
	
	tail = tail * vectorScale;
	local badDir = vmath.normalize(dir * vectorScale);
	badNormals[#badNormals + 1] = tail;
	badNormals[#badNormals + 1] = tail + (badDir * normalLen);
	
	local goodDir = vmath.normalize(dir / vectorScale);
	goodNormals[#goodNormals + 1] = tail;
	goodNormals[#goodNormals + 1] = tail + (goodDir * normalLen);
end

circleNormals = vp:Transform(circleNormals);
badNormals = vp:Transform(badNormals);
goodNormals = vp:Transform(goodNormals);


local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {(subImages:Size().x + 1) .."px", (subImages:Size().y + 1) .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginMarker({10, 8}, {0, 4}, "auto", true, nil, "arrow_normal");
			writer:Path(arrowheadPath, {"normal_head"});
		writer:EndMarker();
		writer:BeginGroup(nil, "g_circle");
			writer:Circle(vp:Transform(circleCenterPt), vpCircleRadius, {"circle"});
		writer:EndGroup();
		writer:BeginGroup(nil, "g_circle_normals");
			for i = 2, numNormals * 2, 2 do
				writer:Line(circleNormals[i - 1], circleNormals[i], {"normal"});
			end
		writer:EndGroup();
		writer:BeginGroup(nil, "g_bad_normals");
			for i = 2, numNormals * 2, 2 do
				writer:Line(badNormals[i - 1], badNormals[i], {"normal"});
			end
		writer:EndGroup();
		writer:BeginGroup(nil, "g_good_normals");
			for i = 2, numNormals * 2, 2 do
				writer:Line(goodNormals[i - 1], goodNormals[i], {"normal"});
			end
		writer:EndGroup();
		writer:BeginGroup(nil, "g_ellipse");
			writer:Ellipse(vp:Transform(circleCenterPt),
				{vpCircleRadius, vpEllipseRadius}, {"circle"});
		writer:EndGroup();
	writer:EndDefinitions();
	
	local xpoints = nil;
	--Left
	writer:Use("g_circle", subImages:Offset(1, 1), subImages:SubSize());
	writer:Use("g_circle_normals", subImages:Offset(1, 1), subImages:SubSize());
	
	--Middle
	writer:Use("g_ellipse", subImages:Offset(2, 1), subImages:SubSize());
	writer:Use("g_bad_normals", subImages:Offset(2, 1), subImages:SubSize());
	
	--Right
	writer:Use("g_ellipse", subImages:Offset(3, 1), subImages:SubSize());
	writer:Use("g_good_normals", subImages:Offset(3, 1), subImages:SubSize());
writer:Close();
