require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local imageWidth = 300;
local imageHeight = 200;
local imageSize = vmath.vec2(imageWidth, imageHeight);

local subImages = SubImage.SubImage(1, 1, imageWidth, imageHeight, 100, 0);

local coordSize = 8;

local vp = Viewport.Viewport(subImages:SubSize(), {0, -1}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local worldExtents = vp:Extents();
worldExtents[1] = -worldExtents[1];

local function ProjectPoint(tPoint, projection)
	if(vmath.vtype(tPoint) == "table") then
		local ret = {}
		for i, realPoint in ipairs(tPoint) do
			ret[i] = ProjectPoint(realPoint, projection)
		end
		return ret;
	end

	local lineDir = tPoint - projection.eyeLoc;
	local offset = (projection.lineLoc.y - projection.eyeLoc.y) / lineDir.y;
	return (lineDir * offset) + projection.eyeLoc;
end


----------------------------------
-- Styles
local styleLib = SvgWriter.StyleLibrary();

styleLib:AddStyle(nil, "black",
	SvgWriter.Style():stroke("black"));
	
styleLib:AddStyle(nil, "red",
	SvgWriter.Style():stroke("red"));
	
styleLib:AddStyle(nil, "line_of_proj",
	SvgWriter.Style():stroke("red"):stroke_width("1px"):stroke_dasharray({4, 8}));
	
styleLib:AddStyle(nil, "object",
	SvgWriter.Style():stroke("#00C000"):stroke_width("1px"));
	
styleLib:AddStyle(nil, "object_projected",
	SvgWriter.Style():stroke("#00C000"):stroke_width("8px"));
	
styleLib:AddStyle(nil, "line_standard",
	SvgWriter.Style():stroke_width("1px"));
	
styleLib:AddStyle(nil, "projected",
	SvgWriter.Style():stroke_width("8px"));
	
styleLib:AddStyle(nil, "dashed",
	SvgWriter.Style():stroke_dasharray({4, 8}));

styleLib:AddStyle(nil, "circle_plane",
	SvgWriter.Style():stroke("black"):stroke_width("2px"));
	
	
styleLib:AddStyle(nil, "fill_black",
	SvgWriter.Style():fill("black"));
	
styleLib:AddStyle(nil, "fill_transluscent",
	SvgWriter.Style():fill("blue"):fill_opacity(0.1));

styleLib:AddStyle(nil, "fill_none",
	SvgWriter.Style():fill("none"));
	
styleLib:AddStyle(nil, "background",
	SvgWriter.Style():fill("#E0E0E0"):stroke("none"));
	

----------------------------------
-- Point setup.

local lineProjection = {}
lineProjection.lineLoc = vmath.vec2(0.0, worldExtents[1] * 0.5);
lineProjection.eyeLoc = vmath.vec2(0.0, worldExtents[1] * 0.75);
lineProjection.lineWidth = 2.0;
lineProjection.lineEndPts =
{
	vmath.vec2(-lineProjection.lineWidth / 2, lineProjection.lineLoc.y),
	vmath.vec2(lineProjection.lineWidth / 2, lineProjection.lineLoc.y),
}
lineProjection.finalEndPts = vp:Transform(lineProjection.lineEndPts)
lineProjection.finalEyeLoc = vp:Transform(lineProjection.eyeLoc)

local sideProjLines = {}
sideProjLines[1] = vmath.vec2(lineProjection.lineEndPts[1])
sideProjLines[1].x = worldExtents[1];
sideProjLines[2] = vmath.vec2(lineProjection.lineEndPts[2])
sideProjLines[2].x = worldExtents[2];

sideProjLines = vp:Transform(sideProjLines);

local projectFrustum =
{
	vmath.vec2(lineProjection.lineEndPts[1]),
	vmath.vec2(lineProjection.lineEndPts[2]),
}

do
	local lineDir = lineProjection.lineEndPts[2] - lineProjection.eyeLoc;
	local offset = (worldExtents[2] - lineProjection.eyeLoc.y) / lineDir.y;
	projectFrustum[3] = (lineDir * offset) + lineProjection.eyeLoc;
	lineDir = lineProjection.eyeLoc - lineProjection.lineEndPts[1];
	offset = (worldExtents[2] - lineProjection.eyeLoc.y) / lineDir.y;
	projectFrustum[4] = (lineDir * offset) + lineProjection.eyeLoc;
end

projectFrustum = vp:Transform(projectFrustum);


local rectShape =
{
	vmath.vec2(0.8, 0.0),
	vmath.vec2(0.5, 0.0),
	vmath.vec2(0.5, 1.5),
	vmath.vec2(0.8, 1.5),
}

local rectProj = ProjectPoint(rectShape, lineProjection)

rectShape = vp:Transform(rectShape);
rectProj = vp:Transform(rectProj);

local rectProjOffset = {}
for i, tPoint in ipairs(rectProj) do
	rectProjOffset[i] = tPoint + vmath.vec2(0, -1);
end

local lineShape =
{
	vmath.vec2(-3.3, -1.5),
	vmath.vec2(-0.5, 3.0),
}

local lineProj = ProjectPoint(lineShape, lineProjection)

lineShape = vp:Transform(lineShape);
lineProj = vp:Transform(lineProj);

--Circle Location
local circleCenter = vmath.vec2(-1.5, 0);
local circleRadius = 1.0;

local circleSizePlane =
{
	circleCenter + vmath.vec2(circleRadius, 0),
	circleCenter - vmath.vec2(circleRadius, 0),
}

circleCenter = vp:Transform(circleCenter);
circleRadius = vp:Length(circleRadius);

local lineProj = ProjectPoint(circleSizePlane, lineProjection)

circleSizePlane = vp:Transform(circleSizePlane);
lineProj = vp:Transform(lineProj);


----------------------------------------
-- The SVG itself
local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {imageWidth .."px", imageHeight .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	--Background
	writer:Polygon(projectFrustum, {"background"})
	
	--Projection
	writer:Line(circleSizePlane[1], lineProj[1], {"line_of_proj"});
	writer:Line(circleSizePlane[2], lineProj[2], {"line_of_proj"});
	writer:Line(lineProj[1], lineProj[2], {"object_projected"});

	--Draw circle.
	writer:Circle(circleCenter, circleRadius, {"object", "fill_none"});
	writer:Line(circleSizePlane[1], circleSizePlane[2], {"circle_plane"});
	
	--Draw the projection plane.
	writer:Line(lineProjection.finalEndPts[1], lineProjection.finalEndPts[2],
		{"black", "line_standard"});
	writer:Line(lineProjection.finalEndPts[1], sideProjLines[1],
		{"black", "line_standard", "dashed"});
	writer:Line(lineProjection.finalEndPts[2], sideProjLines[2],
		{"black", "line_standard", "dashed"});
	
	writer:Circle(lineProjection.finalEyeLoc, imageWidth / 100,
		{"black", "fill_black"})
	writer:Line(lineProjection.finalEndPts[1], lineProjection.finalEyeLoc,
		{"black", "line_standard", "dashed"});
	writer:Line(lineProjection.finalEndPts[2], lineProjection.finalEyeLoc,
		{"black", "line_standard", "dashed"});
writer:Close();
