require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"

subImageSize = 250;

local subImages = SubImage.SubImage(3, 2, subImageSize, subImageSize, 50, 50);

local labelOffset = vmath.vec2(-35, 135);

local coordSize = 14;

local vp = Viewport.Viewport({subImageSize, subImageSize}, {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local vpUpRight = Viewport.Viewport({subImageSize, subImageSize}, {0, 0}, coordSize)
vpUpRight:SetTransform(trans2);

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 10;

local coordAxisWidth = "2px";
local xCoordAxisColor = "#20FF20";
local yCoordAxisColor = "red";
local objectColor = "#AFAFFF";

styleLib:AddStyle(nil, "text",
	SvgWriter.Style():stroke("black"):stroke_width("1px"):font_size("30px"):font_family("monospace"));
	
styleLib:AddStyle(nil, "grid",
	SvgWriter.Style():stroke("#CCC"):fill("none"):stroke_width("1px"));

styleLib:AddStyle(nil, "axes",
	SvgWriter.Style():stroke("black"):fill("none"):stroke_width("2px")
		:marker_end(SvgWriter.uriLocalElement("arrow")));

styleLib:AddStyle(nil, "point",
	SvgWriter.Style():stroke(objectColor):fill(objectColor));
	
styleLib:AddStyle(nil, "triangle",
	SvgWriter.Style():stroke(objectColor):stroke_width("2px"):fill("none")
		:marker(SvgWriter.uriLocalElement("m_point")));
	
styleLib:AddStyle(nil, "x_axis",
	SvgWriter.Style():stroke(xCoordAxisColor):stroke_width(coordAxisWidth):fill("none")
--		:marker_end(SvgWriter.uriLocalElement("big_arrow_x_axis"))
		);
	
styleLib:AddStyle(nil, "y_axis",
	SvgWriter.Style():stroke(yCoordAxisColor):stroke_width(coordAxisWidth):fill("none")
--		:marker_end(SvgWriter.uriLocalElement("big_arrow_y_axis"))
		);
	
styleLib:AddStyle(nil, "x_axis_marker",
	SvgWriter.Style():stroke(xCoordAxisColor):stroke_width(coordAxisWidth):fill("none"));

styleLib:AddStyle(nil, "y_axis_marker",
	SvgWriter.Style():stroke(yCoordAxisColor):stroke_width(coordAxisWidth):fill("none"));

styleLib:AddStyle(nil, "arrow_end",
	SvgWriter.Style():marker_end(SvgWriter.uriLocalElement("arrow")));

styleLib:AddStyle(nil, "text",
	SvgWriter.Style():font_size("30px"):font_family("monospace") );

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();

local bigArrowheadPath = SvgWriter.Path();
bigArrowheadPath:M{0, 0}:L{10, 10}:L{0, 20};

--Generate grid.
local upperBound, lowerBound = vp:Extents();

local gridPath = SvgWriter.Path();

--Vertical lines.
for i = lowerBound[1], upperBound[1] do
	local points =
	{
		vmath.vec2(i, lowerBound[2]);
		vmath.vec2(i, upperBound[2]);
	};
	
	points = vp:Transform(points)
	gridPath:M(points[1]):V(points[2][2]);
end

--Horizontal lines.
for i = lowerBound[2], upperBound[2] do
	local points =
	{
		vmath.vec2(lowerBound[1], i);
		vmath.vec2(upperBound[1], i);
	};
	
	points = vp:Transform(points)
	gridPath:M(points[1]):H(points[2][1]);
end

local axesPath = SvgWriter.Path();

local axes = {}

axes[#axes + 1] = vmath.vec2((upperBound[1] + lowerBound[1]) / 2, 0);
axes[#axes + 1] = vmath.vec2((upperBound[1] + lowerBound[1]) / 2, lowerBound[2]);
axes[#axes + 1] = vmath.vec2((upperBound[1] + lowerBound[1]) / 2, 0);
axes[#axes + 1] = vmath.vec2((upperBound[1] + lowerBound[1]) / 2, upperBound[2]);
axes[#axes + 1] = vmath.vec2(0, (upperBound[2] + lowerBound[2]) / 2);
axes[#axes + 1] = vmath.vec2(upperBound[1], (upperBound[2] + lowerBound[2]) / 2);
axes[#axes + 1] = vmath.vec2(0, (upperBound[2] + lowerBound[2]) / 2);
axes[#axes + 1] = vmath.vec2(lowerBound[1], (upperBound[2] + lowerBound[2]) / 2);

axes = vp:Transform(axes)

--Draw coodinate axes and objects.
local coordAxes =
{
	vmath.vec2(0, 0),
	vmath.vec2(1, 0),
	vmath.vec2(0, 1),
}

local triangle =
{
	vmath.vec2(0.5, 3.5),
	vmath.vec2(1.0, -2),
	vmath.vec2(-2.0, -3.5),
}


local writer = SvgWriter.SvgWriter("TransOrderGeom.svg", {subImages:Size().x .."px", subImages:Size().y .. "px"});
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
		writer:BeginGroup(nil, "g_axes");
			writer:Path(gridPath, {"grid"});
			for i=1, #axes, 2 do
				writer:Line(axes[i], axes[i+1], {"axes"});
			end
		writer:EndGroup();
	writer:EndDefinitions();

	--Left side.
	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());
	
	local origCoordAxes = subImages:Transform({1, 1}, vp:Transform(coordAxes))
	writer:Line(origCoordAxes[1], origCoordAxes[2], {"x_axis"});
	writer:Line(origCoordAxes[1], origCoordAxes[3], {"y_axis"});

	local origTriangle = subImages:Transform({1, 1}, vp:Transform(triangle))
	writer:Polygon(origTriangle, {"triangle"});

	--Middle side.
	writer:Use("g_axes", subImages:Offset(2, 1), subImages:SubSize());

	trans2:Translate(vmath.vec2(2, 1));
	local newCoordAxes = subImages:Transform({2, 1}, vpUpRight:Transform(coordAxes))
	writer:Line(newCoordAxes[1], newCoordAxes[2], {"x_axis"});
	writer:Line(newCoordAxes[1], newCoordAxes[3], {"y_axis"});

	local newTriangle = subImages:Transform({2, 1}, vpUpRight:Transform(triangle))
	writer:Polygon(newTriangle, {"triangle"});
	
	--Right side
	writer:Use("g_axes", subImages:Offset(3, 1), subImages:SubSize());

	trans2:Identity();
	trans2:Scale(vmath.vec2(2, 0.5));
	trans2:Translate(vmath.vec2(2, 1));
	local newCoordAxes = subImages:Transform({3, 1}, vpUpRight:Transform(coordAxes))
	writer:Line(newCoordAxes[1], newCoordAxes[2], {"x_axis"});
	writer:Line(newCoordAxes[1], newCoordAxes[3], {"y_axis"});

	local newTriangle = subImages:Transform({3, 1}, vpUpRight:Transform(triangle))
	writer:Polygon(newTriangle, {"triangle"});

	trans2:Identity();

	--Left side.
	writer:Use("g_axes", subImages:Offset(1, 2), subImages:SubSize());
	
	local origCoordAxes = subImages:Transform({1, 2}, vp:Transform(coordAxes))
	writer:Line(origCoordAxes[1], origCoordAxes[2], {"x_axis"});
	writer:Line(origCoordAxes[1], origCoordAxes[3], {"y_axis"});

	local origTriangle = subImages:Transform({1, 2}, vp:Transform(triangle))
	writer:Polygon(origTriangle, {"triangle"});

	--Middle side.
	writer:Use("g_axes", subImages:Offset(2, 2), subImages:SubSize());

	trans2:Scale(vmath.vec2(2, 0.5));
	local newCoordAxes = subImages:Transform({2, 2}, vpUpRight:Transform(coordAxes))
	writer:Line(newCoordAxes[1], newCoordAxes[2], {"x_axis"});
	writer:Line(newCoordAxes[1], newCoordAxes[3], {"y_axis"});

	local newTriangle = subImages:Transform({2, 2}, vpUpRight:Transform(triangle))
	writer:Polygon(newTriangle, {"triangle"});
	
	--Right side
	writer:Use("g_axes", subImages:Offset(3, 2), subImages:SubSize());

	trans2:Identity();
	trans2:Translate(vmath.vec2(2, 1));
	trans2:Scale(vmath.vec2(2, 0.5));
	local newCoordAxes = subImages:Transform({3, 2}, vpUpRight:Transform(coordAxes))
	writer:Line(newCoordAxes[1], newCoordAxes[2], {"x_axis"});
	writer:Line(newCoordAxes[1], newCoordAxes[3], {"y_axis"});

	local newTriangle = subImages:Transform({3, 2}, vpUpRight:Transform(triangle))
	writer:Polygon(newTriangle, {"triangle"});

	--Labels
	writer:Text("T", labelOffset + subImages:Offset(2, 1), {"text"});
	writer:Text("S", labelOffset + subImages:Offset(3, 1), {"text"});
	writer:Text("S", labelOffset + subImages:Offset(2, 2), {"text"});
	writer:Text("T", labelOffset + subImages:Offset(3, 2), {"text"});
writer:Close();
