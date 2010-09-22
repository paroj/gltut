require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"

--local subImageSize = 350;

local subImages = SubImage.SubImage(1, 1, 700, 300, 50, 50);

local viewportWidth = 10;
local subSize = subImages:SubSize();
local viewportSize = {viewportWidth, viewportWidth * subSize[2] / subSize[1]};

local vp = Viewport.Viewport(subImages:SubSize(), {0, 0}, viewportSize)
local trans2 = Viewport.Transform2D()
--vp:SetTransform(trans2);

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 9;

local coordAxisWidth = "2px";
local xCoordAxisColor = "green";
local yCoordAxisColor = "red";
local objectColor = "#E0E0FF";
local textSize = 20;

styleLib:AddStyle(nil, "border",
	SvgWriter.Style():stroke("black"):fill("none"));
	
styleLib:AddStyle(nil, "main_triangle",
	SvgWriter.Style():stroke("black"):stroke_width("1px"):fill("none"));
	
styleLib:AddStyle(nil, "text",
	SvgWriter.Style():stroke("black"):stroke_width("1px"):font_size(textSize .. "px")
		:font_family("monospace"):text_anchor("middle"));
	
styleLib:AddStyle(nil, "stream_edge",
	SvgWriter.Style():stroke("red"):stroke_width("4px"):fill("none"):stroke_opacity(0.5)
		:stroke_linejoin("round"):stroke_linecap("round"));

styleLib:AddStyle(nil, "ccw_wind_order",
	SvgWriter.Style():stroke("red"):stroke_width("1px"):fill("none")
		:marker_mid(SvgWriter.uriLocalElement("m_ccw_arrow"))
		:marker_end(SvgWriter.uriLocalElement("m_ccw_arrow")));
	
styleLib:AddStyle(nil, "ccw_arrow",
	SvgWriter.Style():stroke("none"):stroke_width("1px"):fill("red"));
	
styleLib:AddStyle(nil, "cw_wind_order",
	SvgWriter.Style():stroke("blue"):stroke_width("1px"):fill("none")
		:marker_mid(SvgWriter.uriLocalElement("m_cw_arrow"))
		:marker_end(SvgWriter.uriLocalElement("m_cw_arrow")));
	
styleLib:AddStyle(nil, "cw_arrow",
	SvgWriter.Style():stroke("none"):stroke_width("1px"):fill("blue"));
	


local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();

local bigArrowheadPath = SvgWriter.Path();
bigArrowheadPath:M{0, 0}:L{10, 10}:L{0, 20};


--Triangle points.
local triangleWidth = 1;
local triangleHeight = triangleWidth * math.sin(math.rad(60));

local triangleScale = 2.5;
triangleWidth = triangleWidth * triangleScale;
triangleHeight = triangleHeight * triangleScale;

local numTris = 6;

local trianglePoints =
{
	vmath.vec2(-4, -triangleHeight / 2),
	vmath.vec2(-4 + (triangleWidth / 2), triangleHeight / 2),
}

for i = 1, numTris do
	local offsetTri = trianglePoints[math.mod(i, 2)];
	offsetTri = offsetTri or trianglePoints[2];

	trianglePoints[#trianglePoints + 1] = offsetTri + vmath.vec2((1 + math.floor((i - 1)/2)) * triangleWidth, 0);
end

local worldPoints = vp:Transform(trianglePoints);

--Write regular
local writer = SvgWriter.SvgWriter("TriangleStrip.svg", {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_point");
			writer:Circle({0, 0}, pointSize/2, {"point"});
		writer:EndGroup();
	writer:EndDefinitions();
	
	for i, point in ipairs(worldPoints) do
		writer:Use("g_point", point);
	end

	for i = 3, #worldPoints do
		writer:Polygon({worldPoints[i - 2], worldPoints[i - 1], worldPoints[i]}, {"main_triangle"});
	end
	
	local heightOffset = {25, -13};
	
	writer:Polyline(worldPoints, {"stream_edge"});

	--Draw the numbers.
	local textDisplacement = 25;
	for i = 1, #worldPoints do
		local offset = heightOffset[math.mod(i, 2)];
		offset = offset or heightOffset[2];
		writer:Text(tonumber(i - 1), worldPoints[i] + vmath.vec2(0, offset), {"text"});
	end
writer:Close();

local unitCWCirclePoints =
{
	vmath.vec2{0.0, 1.0},
	vmath.vec2{-0.866, -0.5},
	vmath.vec2{0.866, -0.5},
}

local circleCwPath = SvgWriter.Path();
local circleCcwPath = SvgWriter.Path();

do
	local circleHeight = vp:Length(triangleHeight / 2);
	local circleRadius = circleHeight / 2;
	local xform = Viewport:Transform2D();
	xform:Scale({circleRadius, circleRadius});
	

	centerCwTriPoints = xform:Transform(unitCWCirclePoints);
	xform:Scale({1.0, -1.0});
	centerCcwTriPoints = xform:Transform(unitCWCirclePoints)

	circleCwPath:M(centerCwTriPoints[#centerCwTriPoints])
	circleCcwPath:M(centerCcwTriPoints[#centerCcwTriPoints])

	for i = 1, #centerCwTriPoints do
		circleCwPath:A({circleRadius, circleRadius}, 0, 0, 1, centerCwTriPoints[i])
		circleCcwPath:A({circleRadius, circleRadius}, 0, 0, 0, centerCcwTriPoints[i])
	end
end


--Write winding order.
writer = SvgWriter.SvgWriter("StripWindingOrder.svg", {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_point");
			writer:Circle({0, 0}, pointSize/2, {"point"});
		writer:EndGroup();
		writer:BeginMarker({10, 8}, {0, 4}, "auto", true, nil, "m_cw_arrow");
			writer:Path(arrowheadPath, {"cw_arrow"});
		writer:EndMarker();
		writer:BeginMarker({10, 8}, {0, 4}, "auto", true, nil, "m_ccw_arrow");
			writer:Path(arrowheadPath, {"ccw_arrow"});
		writer:EndMarker();
		writer:BeginGroup(nil, "g_cwCircle");
			writer:Path(circleCwPath, "cw_wind_order");
		writer:EndGroup();
		writer:BeginGroup(nil, "g_ccwCircle");
			writer:Path(circleCcwPath, "ccw_wind_order");
		writer:EndGroup();
	writer:EndDefinitions();
	
	for i, point in ipairs(worldPoints) do
		writer:Use("g_point", point);
	end

	for i = 3, #worldPoints do
		writer:Polygon({worldPoints[i - 2], worldPoints[i - 1], worldPoints[i]}, {"main_triangle"});
	end
	
	local circleSelector = {"g_cwCircle", "g_ccwCircle"}
	local signSelector = {1, -1};
	
	for i = 2, #worldPoints - 1 do
		local winding = math.mod(i, 2) + 1;
		local loc = vmath.vec2(trianglePoints[i]);
		loc[2] = trianglePoints[i - 1][2] +
			signSelector[winding] *(math.tan(math.rad(30)) * triangleWidth / 2);
		writer:Use(circleSelector[winding], vp:Transform(loc));
	end

	--Draw the numbers.
	local textOffset = {25, -13};
	for i = 1, #worldPoints do
		local offset = textOffset[math.mod(i, 2)];
		offset = offset or textOffset[2];
		writer:Text(tonumber(i - 1), worldPoints[i] + vmath.vec2(0, offset), {"text"});
	end
writer:Close();

