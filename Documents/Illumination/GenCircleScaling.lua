require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "_utils"

local subImageSize = 250;

local subImages = SubImage.SubImage(2, 1, subImageSize, subImageSize, 50, 0);

local coordSize = 2;

local vp = Viewport.Viewport(subImages:SubSize(), {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local scaleFactor = 0.25;

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 9;

styleLib:AddStyle(nil, "circle",
	SvgWriter.Style():stroke("black"):fill("none"));
	

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();

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

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {(subImages:Size().x + 1) .."px", (subImages:Size().y + 1) .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_circle");
			writer:Circle(vp:Transform(circleCenterPt), vpCircleRadius, {"circle"});
		writer:EndGroup();
		writer:BeginGroup(nil, "g_ellipse");
			writer:Ellipse(vp:Transform(circleCenterPt),
				{vpCircleRadius, vpEllipseRadius}, {"circle"});
		writer:EndGroup();
	writer:EndDefinitions();
	
	local xpoints = nil;
	--TopLeft
	writer:Use("g_circle", subImages:Offset(1, 1), subImages:SubSize());
	
	--TopRight
	writer:Use("g_ellipse", subImages:Offset(2, 1), subImages:SubSize());
	
writer:Close();
