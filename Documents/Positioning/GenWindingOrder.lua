require "SvgWriter"
require "vmath"
require "SubImage"

-- Sizing
local subImages = SubImage.SubImage(2, 1, 300, 300, 100, 0);

local pointSize = 10
local circleRadius = subImages:SubSize().x / 8

-- Styles
local styleLib = SvgWriter.StyleLibrary();

styleLib:AddStyle(nil, "black",
	SvgWriter.Style():stroke("black"):stroke_width("1px"));
	
styleLib:AddStyle(nil, "wide_black",
	SvgWriter.Style():stroke("black"):stroke_width("3px"));

styleLib:AddStyle(nil, "fill_black",
	SvgWriter.Style():fill("black"));
	
styleLib:AddStyle(nil, "fill_none",
	SvgWriter.Style():fill("none"));
	
styleLib:AddStyle(nil, "text",
	SvgWriter.Style():font_size("30px"):font_family("monospace") );
	
styleLib:AddStyle(nil, "pointed",
	SvgWriter.Style():marker(SvgWriter.uriLocalElement("point")));

styleLib:AddStyle(nil, "arrows",
	SvgWriter.Style():marker_mid(SvgWriter.uriLocalElement("arrow")):marker_end(SvgWriter.uriLocalElement("arrow")));

-- Paths and other data.

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();

local trianglePoints =
{
	subImages:SubSize() * vmath.vec2{0.3, 0.2},
	subImages:SubSize() * vmath.vec2{0.8, 0.6},
	subImages:SubSize() * vmath.vec2{0.1, 0.8},
}

local cwLabelOffsets = 
{
	vmath.vec2{-7, -12},
	vmath.vec2{9, 7},
	vmath.vec2{-25, 25},
}

local centerPoint = vmath.vec2();

for i, tPoint in ipairs(trianglePoints) do
	centerPoint = centerPoint + tPoint;
end
centerPoint = centerPoint / 3.0;

local unitCWCirclePoints =
{
	vmath.vec2{0.0, 1.0},
	vmath.vec2{-0.866, -0.5},
	vmath.vec2{0.866, -0.5},
}

local circleCwPath = SvgWriter.Path();
local circleCcwPath = SvgWriter.Path();

do
	local centerCwTriPoints, centerCcwTriPoints = {}, {}

	for i, tPoint in ipairs(unitCWCirclePoints) do
		centerCwTriPoints[i] = (circleRadius * tPoint) + centerPoint;
		centerCcwTriPoints[i] = (circleRadius * (tPoint * vmath.vec2(1.0, -1.0))) + centerPoint;
	end

	circleCwPath:M(centerCwTriPoints[#centerCwTriPoints])
	circleCcwPath:M(centerCcwTriPoints[#centerCcwTriPoints])

	for i = 1, #centerCwTriPoints do
		circleCwPath:A({circleRadius, circleRadius}, 0, 0, 1, centerCwTriPoints[i])
		circleCcwPath:A({circleRadius, circleRadius}, 0, 0, 0, centerCcwTriPoints[i])
	end
end


-- The SVG itself.
local writer = SvgWriter.SvgWriter("WindingOrder.svg", {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginMarker({pointSize, pointSize}, {pointSize/2, pointSize/2}, "auto", true, nil, "point");
			writer:Circle({pointSize/2, pointSize/2}, pointSize/2, {"fill_black", "black"});
		writer:EndMarker();
		writer:BeginMarker({10, 8}, {0, 4}, "auto", true, nil, "arrow");
			writer:Path(arrowheadPath, {"fill_black", "black"});
		writer:EndMarker();
		writer:BeginGroup(nil, "g_triangle");
			writer:Polygon(trianglePoints)
		writer:EndGroup();
		writer:BeginGroup(nil, "g_cwCircle");
			writer:Path(circleCwPath, "arrows");
		writer:EndGroup();
		writer:BeginGroup(nil, "g_ccwCircle");
			writer:Path(circleCcwPath, "arrows");
		writer:EndGroup();
		writer:BeginGroup(nil, "g_cwLabels");
			for i, offset in ipairs(cwLabelOffsets) do
				writer:Text(tostring(i), trianglePoints[i] + offset);
			end
		writer:EndGroup();
		writer:BeginGroup(nil, "g_ccwLabels");
			writer:Text("1", trianglePoints[1] + cwLabelOffsets[1]);
			writer:Text("2", trianglePoints[3] + cwLabelOffsets[3]);
			writer:Text("3", trianglePoints[2] + cwLabelOffsets[2]);
		writer:EndGroup();
	writer:EndDefinitions();

	--First subimage: just the triangle.
	writer:Use("g_triangle", subImages:Offset(1, 1), subImages:SubSize(), {"black", "fill_none", "pointed"});
	writer:Use("g_triangle", subImages:Offset(2, 1), subImages:SubSize(), {"black", "fill_none", "pointed"});
	writer:Use("g_cwLabels", subImages:Offset(1, 1), subImages:SubSize(), {"black", "text"});
	writer:Use("g_cwCircle", subImages:Offset(1, 1), subImages:SubSize(), {"black", "fill_none"});
	writer:Use("g_ccwLabels", subImages:Offset(2, 1), subImages:SubSize(), {"black", "text"});
	writer:Use("g_ccwCircle", subImages:Offset(2, 1), subImages:SubSize(), {"black", "fill_none"});
--	writer:Rect(subImages:Offset(1, 1), subImages:SubSize(), nil, {"black", "fill_none"});
--	writer:Rect(subImages:Offset(2, 1), subImages:SubSize(), nil, {"black", "fill_none"});
	
writer:Close();



