require "SvgWriter"
require "vmath"

local imageWidth, imageHeight = 500, 500;

local yAngle = math.rad(45);
local zAngle = math.rad(20);

local ySin, yCos = math.sin(yAngle), math.cos(yAngle);
local zSin, zCos = math.sin(zAngle), math.cos(zAngle);

local yMat = vmath.mat4(
	vmath.vec4(yCos, 0, ySin, 0),
	vmath.vec4(0, 1, 0, 0),
	vmath.vec4(-ySin, 0, yCos, 0),
	vmath.vec4(0, 0, 0, 1))
	
local zMat = vmath.mat4(
	vmath.vec4(1, 0, 0, 0),
	vmath.vec4(0, zCos, -zSin, 0),
	vmath.vec4(0, zSin, zCos, 0),
	vmath.vec4(0, 0, 0, 1))

local worldScale = 0.1;
	
local scalingMatrix = vmath.mat4(
	vmath.vec4(worldScale, 0, 0, 0),
	vmath.vec4(0, worldScale, 0, 0),
	vmath.vec4(0, 0, worldScale, 0),
	vmath.vec4(0, 0, 0, 1))
	
local fullMat = (scalingMatrix * zMat) * yMat

local function LocalTransform(listOfPoints)
	local ret = {};
	for i, point in ipairs(listOfPoints) do
		ret[#ret + 1] = fullMat:Transform(point);
	end
	
	return ret;
end

local viewportMatrix = vmath.mat4(
	vmath.vec4(imageWidth / 2, 0, 0, imageWidth / 2),
	vmath.vec4(0, imageHeight / 2, 0, imageHeight / 2),
	vmath.vec4(0, 0, 1, 0),
	vmath.vec4(0, 0, 0, 1))

local function ViewportTransform(listOfPoints)
	local ret = {};
	for i, point in ipairs(listOfPoints) do
		ret[#ret + 1] = vmath.vec2(viewportMatrix:Transform(point));
	end
	
	return ret;
end

local initialBoxPoints = {
	vmath.vec3(		 7.1,	 4.0,	 5.0),
	vmath.vec3(		-7.1,	 4.0,	 5.0),
	vmath.vec3(		 7.1,	-4.0,	 5.0),
	vmath.vec3(		-7.1,	-4.0,	 5.0),
	vmath.vec3(		 1.77,	 1.0,	-5.0),
	vmath.vec3(		-1.77,	 1.0,	-5.0),
	vmath.vec3(		 1.77,	-1.0,	-5.0),
	vmath.vec3(		-1.77,	-1.0,	-5.0),
}

local initialAxisPoints =
{
	vmath.vec3(4.435, 0.0, 0.0),
	vmath.vec3(10.0, 0.0, 0.0),
	
	vmath.vec3(-4.435, 0.0, 0.0),
	vmath.vec3(-10.0, 0.0, 0.0),
	
	vmath.vec3(0.0, 2.5, 0.0),
	vmath.vec3(0.0, 10.0, 0.0),

	vmath.vec3(0.0, -2.5, 0.0),
	vmath.vec3(0.0, -10.0, 0.0),

	vmath.vec3(0.0, 0.0, 5.0),
	vmath.vec3(0.0, 0.0, 10.0),

	vmath.vec3(0.0, 0.0, -5.0),
	vmath.vec3(0.0, 0.0, -10.0),
}

local boxPoints = ViewportTransform(LocalTransform(initialBoxPoints));
local axisPoints = ViewportTransform(LocalTransform(initialAxisPoints));


local boxIndexList =
{
	{2, 4, 8, 6},
	{1, 2, 6, 5},
	{1, 2, 4, 3},

	{1, 3, 7, 5},
	{3, 4, 8, 7},
	{5, 6, 8, 7},
}

local boxList = {}

for i, box in ipairs(boxIndexList) do
	boxList[i] = {
		boxPoints[box[1]],
		boxPoints[box[2]],
		boxPoints[box[3]],
		boxPoints[box[4]]}
end

local styleLib = SvgWriter.StyleLibrary();

styleLib:AddStyle(nil, "black",
	SvgWriter.Style():stroke("black"):stroke_width("1px"));
	
styleLib:AddStyle(nil, "dashed",
	SvgWriter.Style():stroke_dasharray({3, 3}));
	
	
styleLib:AddStyle(nil, "fill_black",
	SvgWriter.Style():fill("black"));
	
styleLib:AddStyle(nil, "fill_transluscent",
	SvgWriter.Style():fill("blue"):fill_opacity(0.1));

styleLib:AddStyle(nil, "arrowended",
	SvgWriter.Style():marker_end(SvgWriter.uriLocalElement("arrowhead")));

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();


	
local writer = SvgWriter.SvgWriter("RectViewFrustum.svg", {imageWidth .."px", imageHeight .. "px"}, true);
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginMarker({10, 8}, {10, 4}, "auto", nil, nil, "arrowhead");
			writer:Path(arrowheadPath, "black");
		writer:EndMarker();
	writer:EndDefinitions();

	--Draw the rear-most lines, with markers.
	writer:Line(axisPoints[3], axisPoints[4], {"black", "arrowended"});
	writer:Line(axisPoints[7], axisPoints[8], {"black", "arrowended"});
	writer:Line(axisPoints[9], axisPoints[10], {"black", "arrowended"});
	
	--Draw the rear-most box sides.
	writer:Polygon(boxList[1], {"black", "fill_transluscent"});
	writer:Polygon(boxList[2], {"black", "fill_transluscent"});
	writer:Polygon(boxList[3], {"black", "fill_transluscent"});
	
	--Draw the internal lines, no markers.
	writer:Line(axisPoints[1], axisPoints[3], {"black", "dashed"});
	writer:Line(axisPoints[5], axisPoints[7], {"black", "dashed"});
	writer:Line(axisPoints[9], axisPoints[11], {"black", "dashed"});
	
	--Draw the front-most boxes.
	writer:Polygon(boxList[4], {"black", "fill_transluscent"});
	writer:Polygon(boxList[5], {"black", "fill_transluscent"});
	writer:Polygon(boxList[6], {"black", "fill_transluscent"});
	
	--Draw the front-most lines, with markers.
	writer:Line(axisPoints[1], axisPoints[2], {"black", "arrowended"});
	writer:Line(axisPoints[5], axisPoints[6], {"black", "arrowended"});
	writer:Line(axisPoints[11], axisPoints[12], {"black", "arrowended"});
	
writer:Close();



