require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"

local subImageSize = 350;

local subImages = SubImage.SubImage(1, 1, subImageSize, subImageSize, 50, 50);

--Gives a [-1, 1] range.
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

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();

local bigArrowheadPath = SvgWriter.Path();
bigArrowheadPath:M{0, 0}:L{10, 10}:L{0, 20};


--Triangle points.
--local distance = 1.3;
local rotTrans = Viewport.Transform2D()

local trianglePoints = 
{
	vmath.vec2(0.5, 0.8),
}

local distances = {1.3, 1.5, 0.9, 1.4, 1.2}
local angles = {20, 25, 20, 25, 5}

rotTrans:Rotate(-13)

for i, distance in ipairs(distances) do
	local offset = vmath.vec2(0, -distance);
	trianglePoints[#trianglePoints + 1] = rotTrans:Matrix():Transform(offset) + trianglePoints[1];
	rotTrans:Rotate(angles[i]);
end


local worldPoints = vp:Transform(trianglePoints);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_point");
			writer:Circle({0, 0}, pointSize/2, {"point"});
		writer:EndGroup();
	writer:EndDefinitions();
	
	for i, point in ipairs(worldPoints) do
		writer:Use("g_point", point);
	end
	
	for i = 2, (#worldPoints - 1) do
		writer:Polygon({worldPoints[1], worldPoints[i], worldPoints[i + 1]}, {"main_triangle"});
	end
	
	writer:Polyline(worldPoints, {"stream_edge"});
	
	--Draw the numbers.
	writer:Text("0", worldPoints[1] - vmath.vec2(-8, 8), {"text"});
	
	local textDisplacement = 25;
	for i = 2, #worldPoints do
		local direction = vmath.norm(worldPoints[i] - worldPoints[1]);
		writer:Text(tonumber(i - 1), worldPoints[i] + (direction * 25), {"text"});
	end
	
writer:Close();
