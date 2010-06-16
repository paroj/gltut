require "SvgWriter"
require "vmath"

vec2 = vmath.vec2;

-- Sizing
local numSubImages = 2;
local subImageWidth, subImageHeight = 400, 400;
local subImageSpacing = 100;
local belowImageSpaceing = 50;

local imageWidth = (subImageWidth * numSubImages) + (subImageSpacing * (numSubImages - 1));
local imageHeight = subImageHeight + belowImageSpaceing;

local subImageSize = vmath.vec2{subImageWidth, subImageHeight};
local pointSize = 10
local circleRadius = subImageWidth / 8

local subImagePositions = {}

for i = 1, numSubImages, 1 do
	subImagePositions[i] = vmath.vec2{(subImageWidth + subImageSpacing) * (i-1), 0};
end

local worldWidth = 4;
local halfWorldWidth = worldWidth / 2;
local leftWorldOffset = vmath.vec2(0, halfWorldWidth * 0.75)
local leftWorldVertRange = vmath.vec2(-halfWorldWidth - leftWorldOffset[2], halfWorldWidth -leftWorldOffset[2])

local function TransformPointToLeftWnd(tPoint)
	if(vmath.vtype(tPoint) == "table") then
		local ret = {}
		for i, realPoint in ipairs(tPoint) do
			ret[i] = TransformPointToLeftWnd(realPoint)
		end
		return ret;
	end

	local final = vmath.vec2(tPoint);
	final = final + leftWorldOffset;
	final = final + (halfWorldWidth);
	final = final * (subImageSize / worldWidth);
	final = final + subImagePositions[1]
	return final;
end

local function TransformPointToRightWnd(tPoint)
	if(vmath.vtype(tPoint) == "table") then
		local ret = {}
		for i, realPoint in ipairs(tPoint) do
			ret[i] = TransformPointToRightWnd(realPoint)
		end
		return ret;
	end

	local final = vmath.vec2(tPoint);
	final.y = -final.y
	final = final + (halfWorldWidth);
	final = final * (subImageSize / worldWidth);
	final = final + subImagePositions[2]
	return final;
end

local zNear, zFar = -1.0, -3.0;
local zCenter = (zFar + zNear) / 2;
local zScale = math.abs(zFar - zNear) / 2;

local function TransformToNDC(tPoint)
	if(vmath.vtype(tPoint) == "table") then
		local ret = {}
		for i, realPoint in ipairs(tPoint) do
			ret[i] = TransformToNDC(realPoint)
		end
		return ret;
	end
	
	local final = vec2(tPoint);
	--[[
	final.y = (final.y - zCenter);
	final.y = final.y / zScale;
	final.y = -final.y;
	
	final.x = final.x / -(tPoint.y)
	]]
	local near, far = -zNear, -zFar;
	final.y = (final.y * ((far + near)/(near-far))) + ((2 * near * far)/(near-far))
	final = final / -(tPoint.y)
	return final;
end


-- Styles
local styleLib = SvgWriter.StyleLibrary();

styleLib:AddStyle(nil, "black",
	SvgWriter.Style():stroke("black"):stroke_width("1px"));
	
styleLib:AddStyle(nil, "stroke_none",
	SvgWriter.Style():stroke("none"));
	
styleLib:AddStyle(nil, "object_lines",
	SvgWriter.Style():stroke("#00C000"):stroke_width("1px"):fill("none"));
	
styleLib:AddStyle(nil, "object_circles",
	SvgWriter.Style():fill("#00C000"):stroke("black"):stroke_width("0.5px"));
	
styleLib:AddStyle(nil, "radial_eye",
	SvgWriter.Style():stroke("black"):stroke_dasharray{3, 3});
	
styleLib:AddStyle(nil, "wide_black",
	SvgWriter.Style():stroke("black"):stroke_width("3px"));

styleLib:AddStyle(nil, "fill_black",
	SvgWriter.Style():fill("black"));
	
styleLib:AddStyle(nil, "fill_frustum",
	SvgWriter.Style():fill("#E0E0E0"));
	
styleLib:AddStyle(nil, "fill_none",
	SvgWriter.Style():fill("none"));
	
styleLib:AddStyle(nil, "text",
	SvgWriter.Style():font_size("30px"):font_family("monospace") );
	
styleLib:AddStyle(nil, "axis_label",
	SvgWriter.Style():stroke("black"):font_size("30px"):font_family("monospace") );
	
styleLib:AddStyle(nil, "image_label",
	SvgWriter.Style():stroke("black"):font_size("40px"):font_family("serif"):text_anchor("middle") );
	
styleLib:AddStyle(nil, "pointed",
	SvgWriter.Style():marker(SvgWriter.uriLocalElement("point")));

styleLib:AddStyle(nil, "arrow_ended",
	SvgWriter.Style():marker_end(SvgWriter.uriLocalElement("arrow")));
styleLib:AddStyle(nil, "arrows",
	SvgWriter.Style():marker_mid(SvgWriter.uriLocalElement("arrow")):marker_end(SvgWriter.uriLocalElement("arrow")));
styleLib:AddStyle(nil, "double_arrowheaded",
	SvgWriter.Style():marker_start(SvgWriter.uriLocalElement("arrow")):marker_end(SvgWriter.uriLocalElement("arrow")));

-- Paths and other data.

local arrowWidth, arrowLength = 12, 16;

local arrowheadPath = SvgWriter.Path();
arrowheadPath:M{arrowLength, arrowWidth / 2}:L{0, 0}:L{0, arrowWidth}:Z();

local leftAxisLocs =
{
	vec2(0, 0),
	vec2(0, leftWorldVertRange[1]),
	vec2(0, leftWorldVertRange[2]),
	vec2(-worldWidth/2, 0),
	vec2(worldWidth/2, 0),
}

local numAxisHashes = 8
local leftAxisHashes = {}
local startPt = leftAxisLocs[2];
local dir = leftAxisLocs[3] - leftAxisLocs[2]
local hashSize = worldWidth / 25;
for i = 1, numAxisHashes - 1 do
	local leftPt = startPt + (dir * (i / numAxisHashes));
	local rightPt = vec2(leftPt);
	if(math.mod(i, 2) == 0) then
		leftPt.x = leftPt.x + hashSize * 0.75
		rightPt.x = rightPt.x - hashSize * 0.75
	else
		leftPt.x = leftPt.x + hashSize/2
		rightPt.x = rightPt.x - hashSize/2
	end
	leftAxisHashes[#leftAxisHashes + 1] = leftPt;
	leftAxisHashes[#leftAxisHashes + 1] = rightPt;
end

startPt = leftAxisLocs[4];
dir = leftAxisLocs[5] - leftAxisLocs[4]
for i = 1, numAxisHashes - 1 do
	local botPt = startPt + (dir * (i / numAxisHashes));
	local topPt = vec2(botPt);
	if(math.mod(i, 2) == 0) then
		botPt.y = botPt.y + hashSize * 0.75
		topPt.y = topPt.y - hashSize * 0.75
	else
		botPt.y = botPt.y + hashSize/2
		topPt.y = topPt.y - hashSize/2
	end
	leftAxisHashes[#leftAxisHashes + 1] = botPt;
	leftAxisHashes[#leftAxisHashes + 1] = topPt;
end

leftAxisHashes = TransformPointToLeftWnd(leftAxisHashes);
leftAxisLocs = TransformPointToLeftWnd(leftAxisLocs);


local rightAxisLocs =
{
	vec2(0, 0),
	vec2(0, -worldWidth/2),
	vec2(0, worldWidth/2),
	vec2(-worldWidth/2, 0),
	vec2(worldWidth/2, 0),
}

local rightAxisHashes = {}
local startPt = rightAxisLocs[2];
local dir = rightAxisLocs[3] - rightAxisLocs[2]
hashSize = worldWidth / 25;
for i = 1, numAxisHashes - 1 do
	local leftPt = startPt + (dir * (i / numAxisHashes));
	local rightPt = vec2(leftPt);
	if(math.mod(i, 2) == 0) then
		leftPt.x = leftPt.x + hashSize * 0.75
		rightPt.x = rightPt.x - hashSize * 0.75
	else
		leftPt.x = leftPt.x + hashSize/2
		rightPt.x = rightPt.x - hashSize/2
	end
	rightAxisHashes[#rightAxisHashes + 1] = leftPt;
	rightAxisHashes[#rightAxisHashes + 1] = rightPt;
end

startPt = rightAxisLocs[4];
dir = rightAxisLocs[5] - rightAxisLocs[4]
for i = 1, numAxisHashes - 1 do
	local botPt = startPt + (dir * (i / numAxisHashes));
	local topPt = vec2(botPt);
	if(math.mod(i, 2) == 0) then
		botPt.y = botPt.y + hashSize * 0.75
		topPt.y = topPt.y - hashSize * 0.75
	else
		botPt.y = botPt.y + hashSize/2
		topPt.y = topPt.y - hashSize/2
	end
	rightAxisHashes[#rightAxisHashes + 1] = botPt;
	rightAxisHashes[#rightAxisHashes + 1] = topPt;
end

rightAxisHashes = TransformPointToRightWnd(rightAxisHashes);
rightAxisLocs = TransformPointToRightWnd(rightAxisLocs);


local function TransformBoth(tPoint)
	if(vmath.vtype(tPoint) == "table") then
		local ret = {}
		for i, realPoint in ipairs(tPoint) do
			ret[i] = TransformBoth(realPoint)
		end
		return ret;
	end

	local testPtLeft = tPoint;
	local testPtRight = TransformToNDC(testPtLeft);
	testPtLeft = TransformPointToLeftWnd(testPtLeft);
	testPtRight = TransformPointToRightWnd(testPtRight);
	
	return {testPtLeft, testPtRight};
end

local testPts =
{
	vec2(1.5, -0.75),
	vec2(0.5, -0.75),

	vec2(1.5, -1.25),
	vec2(0.5, -1.25),

	vec2(1.5, -1.75),
	vec2(0.5, -1.75),

	vec2(1.5, -2.25),
	vec2(0.5, -2.25),

	vec2(1.5, -2.75),
	vec2(0.5, -2.75),

	vec2(1.5, -3.25),
	vec2(0.5, -3.25),
};

testPts = TransformBoth(testPts)

local leftBlocksPath = SvgWriter.Path();
local rightBlocksPath = SvgWriter.Path();

for i = 1, #testPts - 2, 2 do
	leftBlocksPath:M(testPts[i + 2][1]):L(testPts[i][1]):L(testPts[i + 1][1]):L(testPts[i + 3][1]);
	rightBlocksPath:M(testPts[i + 2][2]):L(testPts[i][2]):L(testPts[i + 1][2]):L(testPts[i + 3][2]);
end

leftBlocksPath:Z();
rightBlocksPath:Z();

local frustumPoints =
{
	vec2(zNear, zNear),
	vec2(-zNear, zNear),
	vec2(worldWidth/2, -worldWidth/2),
	vec2(worldWidth/2, zFar),
	vec2(-worldWidth/2, zFar),
	vec2(-worldWidth/2, -worldWidth/2),
}

frustumPoints = TransformPointToLeftWnd(frustumPoints);

local leftViewArea = SvgWriter.Path()

leftViewArea:M(frustumPoints[1]);

for i = 2, #frustumPoints do
	leftViewArea:L(frustumPoints[i]);
end

leftViewArea:Z();

local rightViewArea = { vec2(-1, -1), vec2(1, 1); }
rightViewArea = TransformPointToRightWnd(rightViewArea);

local leftOrigin = TransformPointToLeftWnd(vec2(0, 0));

local leftAxisLocations = { vec2(halfWorldWidth, 0), vec2(0, leftWorldVertRange[1]) };
leftAxisLocations = TransformPointToLeftWnd(leftAxisLocations);
local rightAxisLocations = { vec2(halfWorldWidth, 0), vec2(0, halfWorldWidth) }
rightAxisLocations = TransformPointToRightWnd(rightAxisLocations);

local axisLabelPixelOffsets = { vec2(-45, -10), vec2(-50, 30) };

local imageTitleLoc = {vec2(subImageWidth / 2, subImageHeight)}
imageTitleLoc[2] = imageTitleLoc[1] + vec2(subImageWidth + subImageSpacing, 0)
local imageTitleOffset = vec2(0, 40)


-- The SVG itself.
local writer = SvgWriter.SvgWriter("CameraToPerspective.svg", {imageWidth .."px", imageHeight .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginMarker({pointSize, pointSize}, {pointSize/2, pointSize/2}, "auto", true, nil, "point");
			writer:Circle({pointSize/2, pointSize/2}, pointSize/2, {"fill_black", "black"});
		writer:EndMarker();
		writer:BeginMarker({arrowLength, arrowWidth}, {arrowLength, arrowWidth / 2}, "auto", true, nil, "arrow");
			writer:Path(arrowheadPath, {"fill_black", "black"});
		writer:EndMarker();
	writer:EndDefinitions();
	
	--Draw the viewing volumes.
	writer:Path(leftViewArea, {"stroke_none", "fill_frustum"});
	writer:Rect2Pt(rightViewArea[1], rightViewArea[2], nil, {"stroke_none", "fill_frustum"});
	
	--Draw the eye lines.
	writer:Line(leftOrigin, frustumPoints[3], {"radial_eye"});
	writer:Line(leftOrigin, frustumPoints[6], {"radial_eye"});
	
	--Draw the coordinate axes.
	for i, endPt in ipairs(leftAxisLocs) do
		if(i ~= 1) then
			writer:Line(leftAxisLocs[1], leftAxisLocs[i], {"black", "arrow_ended"})
		end
	end
	
	for i = 1, #leftAxisHashes, 2 do
		writer:Line(leftAxisHashes[i], leftAxisHashes[i+1], {"black"})
	end

	for i, endPt in ipairs(rightAxisLocs) do
		if(i ~= 1) then
			writer:Line(rightAxisLocs[1], rightAxisLocs[i], {"black", "arrow_ended"})
		end
	end
	
	for i = 1, #rightAxisHashes, 2 do
		writer:Line(rightAxisHashes[i], rightAxisHashes[i+1], {"black"})
	end

	--Draw the objects
	writer:Path(leftBlocksPath, {"object_lines"});
	writer:Path(rightBlocksPath, {"object_lines"});
	
	for i, ptPair in ipairs(testPts) do
		writer:Circle(ptPair[1], 5, {"object_circles"});
		writer:Circle(ptPair[2], 5, {"object_circles"});
	end
	
	--label the axes.
	writer:Text("+X", leftAxisLocations[1] + axisLabelPixelOffsets[1], {"axis_label"})
	writer:Text("-Z", leftAxisLocations[2] + axisLabelPixelOffsets[2], {"axis_label"})
	writer:Text("+X", rightAxisLocations[1] + axisLabelPixelOffsets[1], {"axis_label"})
	writer:Text("+Z", rightAxisLocations[2] + axisLabelPixelOffsets[2], {"axis_label"})

	--label the images
	writer:Text("Camera Space", imageTitleLoc[1] + imageTitleOffset, {"image_label"});
	writer:Text("Norm. Device Coord.", imageTitleLoc[2] + imageTitleOffset, {"image_label"});
	
--	writer:Rect(subImagePositions[1], subImageSize, nil, {"black", "fill_none"});
--	writer:Rect(subImagePositions[2], subImageSize, nil, {"black", "fill_none"});
--	writer:Rect2Pt(TransformPointToLeftWnd(vmath.vec2(-1, -1)), TransformPointToLeftWnd(vmath.vec2(1, 1)), nil, {"fill_none", "black"});
	
writer:Close();



