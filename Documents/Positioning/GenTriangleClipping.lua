require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"

local subImageSize = 250;

local subImages = SubImage.SubImage(2, 2, subImageSize, subImageSize, 50, 50);

local coordSize = 2;

local vp = Viewport.Viewport(subImages:SubSize(), {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 9;

local coordAxisWidth = "2px";
local xCoordAxisColor = "green";
local yCoordAxisColor = "red";
local objectColor = "#E0E0FF";

styleLib:AddStyle(nil, "border",
	SvgWriter.Style():stroke("black"):fill("none"));
	
styleLib:AddStyle(nil, "clip_line",
	SvgWriter.Style():stroke("black"):stroke_width("2px"):fill("none"));
	
styleLib:AddStyle(nil, "clip_region",
	SvgWriter.Style():stroke("none"):fill(objectColor));
	
styleLib:AddStyle(nil, "main_triangle",
	SvgWriter.Style():stroke("black"):stroke_width("1px"):fill("none"));
	
styleLib:AddStyle(nil, "new_point",
	SvgWriter.Style():stroke("none"):fill("red"));
	
styleLib:AddStyle(nil, "new_edge",
	SvgWriter.Style():stroke("red"):stroke_width("4px"):fill("none"):stroke_opacity(0.4):stroke_linejoin("round"):stroke_linecap("round"));
	
	

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

--Clipping Region
local leftClipExtent = -0.5;
local bottomClipExtent = -0.25;

local clipLines = SvgWriter.Path();
clipLines:M(vp:Transform(vmath.vec2(leftClipExtent, 1)));
clipLines:L(vp:Transform(vmath.vec2(leftClipExtent, bottomClipExtent)));
clipLines:L(vp:Transform(vmath.vec2(1, bottomClipExtent)));

local clipRegion = SvgWriter.Path();
clipRegion:M(vp:Transform(vmath.vec2(leftClipExtent, 1)));
clipRegion:L(vp:Transform(vmath.vec2(leftClipExtent, bottomClipExtent)));
clipRegion:L(vp:Transform(vmath.vec2(1, bottomClipExtent)));
clipRegion:L(vp:Transform(vmath.vec2(1, 1)));
clipRegion:Z();

--Triangles
local triangles = {}
triangles[1] =
{
	vmath.vec2(0, 0),
	vmath.vec2(0.4, 0.8),
	vmath.vec2(0.75, -0.1),
}

triangles[2] =
{
	vmath.vec2(0.25, 0.25),
	vmath.vec2(-0.25, -0.75),
	vmath.vec2(0.5, -0.5),
}

triangles[3] =
{
	vmath.vec2(-0.25, 0.0),
	vmath.vec2(0.25, -0.75),
	vmath.vec2(0.75, 0.5),
}

triangles[4] =
{
	vmath.vec2(-0.75, 0.5),
	vmath.vec2(0.75, -0.75),
	vmath.vec2(0.5, 0.75),
}

--New Triangles
local newPoints = {}
newPoints[1] = {}

newPoints[2] =
{
	vmath.vec2(0.0, -0.25),
	vmath.vec2(0.41666, -0.25),
}

newPoints[3] =
{
	vmath.vec2(-0.08333, -0.25),
	vmath.vec2(0.45, -0.25),
}

newPoints[4] =
{
	vmath.vec2(-0.5, 0.291667),
	vmath.vec2(-0.5, 0.55),
	vmath.vec2(0.15, -0.25),
	vmath.vec2(0.6667, -0.25),
}


local writer = SvgWriter.SvgWriter("TriangleClipping.svg", {(subImages:Size().x + 1) .."px", (subImages:Size().y + 1) .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginMarker({pointSize, pointSize}, {pointSize/2, pointSize/2}, "auto", true, nil, "m_point");
			writer:Circle({pointSize/2, pointSize/2}, pointSize/2, {"point"});
		writer:EndMarker();
		writer:BeginMarker({10, 8}, {10, 4}, "auto", true, nil, "arrow");
			writer:Path(arrowheadPath, {"fill_black", "thin"});
		writer:EndMarker();
		writer:BeginMarker({10, 20}, {10, 10}, "auto", true, nil, "big_arrow_y_axis");
			writer:Path(bigArrowheadPath, {"y_axis_marker"});
		writer:EndMarker();
		writer:BeginMarker({10, 20}, {10, 10}, "auto", true, nil, "big_arrow_x_axis");
			writer:Path(bigArrowheadPath, {"x_axis_marker"});
		writer:EndMarker();
		writer:BeginGroup(nil, "g_background");
			writer:Path(clipRegion, {"clip_region"});
			writer:Path(borderPath, {"border"});
			writer:Path(clipLines, {"clip_line"});
		writer:EndGroup();
		writer:BeginGroup(nil, "g_new_point");
			writer:Circle({0, 0}, pointSize/2, {"new_point"});
		writer:EndGroup();
	writer:EndDefinitions();
	
	local xpoints = nil;
	--TopLeft
	writer:Use("g_background", subImages:Offset(1, 1), subImages:SubSize());
	
	xpoints = subImages:Transform({1, 1}, vp:Transform(triangles[1]));
	writer:Polygon(xpoints, {"main_triangle"});
	
	if(#newPoints[1] > 0) then
		local xform = subImages:Transform({1, 1}, vp:Transform(newPoints[1]));
		for i, point in ipairs(xform) do
			writer:Use("g_new_point", point);
		end
	end
	
	--TopRight
	writer:Use("g_background", subImages:Offset(2, 1), subImages:SubSize());

	xpoints = subImages:Transform({2, 1}, vp:Transform(triangles[2]));
	writer:Polygon(xpoints, {"main_triangle"});
	
	if(#newPoints[2] > 0) then
		local xform = subImages:Transform({2, 1}, vp:Transform(newPoints[2]));
		for i, point in ipairs(xform) do
			writer:Use("g_new_point", point);
		end
		
		writer:Polyline({xpoints[1], xform[2], xform[1], xpoints[1]}, {"new_edge"});
	end
	
	--BottomLeft
	writer:Use("g_background", subImages:Offset(1, 2), subImages:SubSize());

	xpoints = subImages:Transform({1, 2}, vp:Transform(triangles[3]));
	writer:Polygon(xpoints, {"main_triangle"});

	if(#newPoints[3] > 0) then
		local xform = subImages:Transform({1, 2}, vp:Transform(newPoints[3]));
		for i, point in ipairs(xform) do
			writer:Use("g_new_point", point);
		end

		writer:Polyline(
			{
				xform[1],
				xform[2],
				xpoints[3],
				xform[1],
				xpoints[1],
				xpoints[3],
			},
			{"new_edge"});
	end
	
	--BottomRight
	writer:Use("g_background", subImages:Offset(2, 2), subImages:SubSize());

	xpoints = subImages:Transform({2, 2}, vp:Transform(triangles[4]));
	writer:Polygon(xpoints, {"main_triangle"});
	
	if(#newPoints[4] > 0) then
		local xform = subImages:Transform({2, 2}, vp:Transform(newPoints[4]));
		for i, point in ipairs(xform) do
			writer:Use("g_new_point", point);
		end
		
		writer:Polyline(
			{
				xform[1],
				xform[2],
				xpoints[3],
				xform[1],
				xform[3],
				xpoints[3],
				xform[4],
				xform[3],
			},
			{"new_edge"});
	end
	

writer:Close();
