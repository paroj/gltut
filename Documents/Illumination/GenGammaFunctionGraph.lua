require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local imageSize = vmath.vector{600, 600};
local subImages = SubImage.SubImage({1, 1}, imageSize, {100, 0});

local coordSize = 1;

--Top, right, bottom, left
local margins = {20, 20, 50, 50}

local viewportSize = imageSize -
	vmath.vector{margins[2] + margins[4], margins[1] + margins[3]};

local vp = Viewport.Viewport(viewportSize, {0.5, 0.5}, coordSize, {margins[4], margins[1]})
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local bkgColor = "whitesmoke";
local gridLineClr = "lightgrey";
local gridBorderClr = "grey";
local gridAxisClr = "black";
local gridHashClr = "black";

local linearRGBClr = "grey";
local gammaClr = "red";
local arrowColor = "darksalmon";
local curveLabelColor = "darkred";

local axisLabelSize = 15;
local arrowLabelSize = 20;
local curveLabelSize = 30;

styleLib:AddStyle(nil, "grid-line", SvgWriter.Style{
	stroke=gridLineClr, fill="none"});
styleLib:AddStyle(nil, "grid-background", SvgWriter.Style{
	stroke="none", fill=bkgColor});
styleLib:AddStyle(nil, "grid-border", SvgWriter.Style{
	stroke=gridBorderClr, fill="none"});
styleLib:AddStyle(nil, "grid-axis", SvgWriter.Style{
	stroke=gridAxisClr, fill="none", stroke_width="2px"});
styleLib:AddStyle(nil, "grid-axis-hash", SvgWriter.Style{
	stroke=gridHashClr, fill="none", stroke_width="0.5px"});
	
styleLib:AddStyle(nil, "grid-axis-label", SvgWriter.Style{
	stroke="none", fill="black", font_family="sans-serif", font_size=tostring(axisLabelSize)});
styleLib:AddStyle(nil, "grid-axis-label-x", SvgWriter.Style{
	text_anchor="middle"});
styleLib:AddStyle(nil, "grid-axis-label-y", SvgWriter.Style{
	text_anchor="end"});
styleLib:AddStyle(nil, "grid-axis-hash", SvgWriter.Style{
	text_anchor="end"});
	
styleLib:AddStyle(nil, "linear-rgb",
	SvgWriter.Style{stroke=linearRGBClr, fill="none"});
styleLib:AddStyle(nil, "gamma-func",
	SvgWriter.Style{stroke=gammaClr, fill="none", stroke_width="4px",
		clip_path=SvgWriter.uriLocalElement("graph-clip")});
styleLib:AddStyle(nil, "gamma-correct-dash",
	SvgWriter.Style{stroke_dasharray={21, 6}});

styleLib:AddStyle(nil, "pointer-arrow",
	SvgWriter.Style{stroke=arrowColor, fill="none",
		stroke_width="3px",
		marker_start=SvgWriter.uriLocalElement("arrow-rear"),
		marker_end=SvgWriter.uriLocalElement("arrow-head")});
styleLib:AddStyle(nil, "pointer-arrow-dash",
	SvgWriter.Style{stroke_dasharray={14, 5}});
styleLib:AddStyle(nil, "pointer-arrow-label",
	SvgWriter.Style{stroke="none", fill=arrowColor,
		font_family="sans-serif", font_weight="bold",
		font_size=tostring(arrowLabelSize).."px", text_anchor="end"});
styleLib:AddStyle(nil, "pointer-arrow-marker",
	SvgWriter.Style{stroke="none", fill=arrowColor});
	
styleLib:AddStyle(nil, "curve-label",
	SvgWriter.Style{stroke="none", fill=curveLabelColor,
		font_family="sans-serif", font_weight="bold",
		font_size=tostring(curveLabelSize).."px"});
styleLib:AddStyle(nil, "text-left-justified",
	SvgWriter.Style{text_anchor="start"});
styleLib:AddStyle(nil, "text-right-justified",
	SvgWriter.Style{text_anchor="end"});

	

	
function DrawLines(writer, lineList, ...)
	local path = SvgWriter.Path();
	
	for i = 1, #lineList, 2 do
		path:M(lineList[i]):L(lineList[i+1]);
	end
	
	writer:Path(path, ...);
end

local graphBox =
{
	vmath.vec2(0, 0),
	vmath.vec2(1, 0),
	vmath.vec2(0, 1),
	vmath.vec2(1, 1),
};

graphBox = vp:Transform(graphBox);

local gridLines = {}

for i = 1, 9 do
	local yValue = i / 10;
	gridLines[#gridLines + 1] = vmath.vec2(0, yValue);
	gridLines[#gridLines + 1] = vmath.vec2(1, yValue);
end

gridLines[#gridLines + 1] = vmath.vec2(0.5, 0);
gridLines[#gridLines + 1] = vmath.vec2(0.5, 1);

gridLines = vp:Transform(gridLines);

local borderLines =
{
	vmath.vec2(0, 1),
	vmath.vec2(1, 1),
	vmath.vec2(1, 1),
	vmath.vec2(1, 0),
}

borderLines = vp:Transform(borderLines);

local axisLines =
{
	vmath.vec2(0, 1),
	vmath.vec2(0, 0),
	vmath.vec2(0, 0),
	vmath.vec2(1, 0),
}

axisLines = vp:Transform(axisLines);

axisLabels = 
{
	"0",
	"0.1",
	"0.2",
	"0.3",
	"0.4",
	"0.5",
	"0.6",
	"0.7",
	"0.8",
	"0.9",
	"1",
}

local pxAxisLabelOffset =
{
	vmath.vec2(0, axisLabelSize + 5),
	vmath.vec2(-5, (axisLabelSize / 2) - 2),
};

local hashSize = 5;


local linearLines = {vmath.vec2(0, 0), vmath.vec2(1, 1)};
linearLines = vp:Transform(linearLines);

local maxDistance = 0.05;
function CalcPath(currXVal, nextXVal, path, gamma)
	if(nextXVal > 1.0) then
		nextXVal = 1.0;
	end
	local currVal = vmath.vec2(currXVal, currXVal ^ gamma);
	local nextVal = vmath.vec2(nextXVal, nextXVal ^ gamma);
	local len = vmath.length(currVal - nextVal);
	if(len < maxDistance) then
		path:L(vp:Transform(nextVal));
		print(nextVal, len, maxDistance);
		if(nextXVal == 1.0) then
			return;
		else
			return CalcPath(nextXVal, nextXVal + 0.1, path, gamma); --tail call
		end
	else
--		print("here!");
		return CalcPath(currXVal, currXVal + (nextXVal - currXVal)/2, path, gamma); --tail call
	end
end

local gammaFuncPath = SvgWriter.Path()
local gammaCorrectPath = SvgWriter.Path()

gammaCorrectPath:M(vp:Transform(vmath.vec2(0, 0)));
CalcPath(0.0, 0.1, gammaCorrectPath, 0.454545);

gammaFuncPath:M(vp:Transform(vmath.vec2(0, 0)));
CalcPath(0.0, 0.1, gammaFuncPath, 2.2);

--[[
local numLineSegments = 150;
for i = 1, numLineSegments do
	local xVal = (i - 1) / (numLineSegments - 1);
	local gammaFunc = vmath.vec2(xVal, xVal ^ 2.2);
	local gammaCorrect = vmath.vec2(xVal, xVal ^ 0.454545);
	gammaFunc = vp:Transform(gammaFunc);
	gammaCorrect = vp:Transform(gammaCorrect);
	if(i == 1) then
		gammaFuncPath:M(gammaFunc);
		gammaCorrectPath:M(gammaCorrect);
	else
		gammaFuncPath:L(gammaFunc);
		gammaCorrectPath:L(gammaCorrect);
	end
end
]]

local curveLabels =
{
	{{"gamma", "correction", "1/2.2"}, vmath.vec2(0.325, 0.77), vmath.vec2(0, 0), {"curve-label", "text-right-justified"}},
	{{"CRT", "gamma", "2.2"}, vmath.vec2(0.7, 0.375), vmath.vec2(0, 0), {"curve-label", "text-left-justified"}},
}

for i, curveLabel in ipairs(curveLabels) do
	curveLabel[2] = vp:Transform(curveLabel[2]);
end

local gammaHalf = 0.5 ^ 2.2;
local pointers =
{
	vmath.vec2(0.5, 0.5);
	vmath.vec2(0.5, gammaHalf);
	vmath.vec2(gammaHalf, gammaHalf);
	vmath.vec2(gammaHalf, 0.5);
};

pointers = vp:Transform(pointers);

local pointerLabels =
{
	{"0.5",   vmath.vec2(pointers[1]), vmath.vec2(-15, 0)},
	{"0.218", vmath.vec2(pointers[2]), vmath.vec2(-15, 0)},
	{"0.218", vmath.vec2(pointers[3]), vmath.vec2(-15, 0)},
	{"0.5",   vmath.vec2(pointers[4]), vmath.vec2(-15, 0)},
}

local sphereRadius = 7;
local pointerOffset = 4;

pointers[2][2] = pointers[2][2] - (sphereRadius + pointerOffset);
pointers[4][2] = pointers[4][2] + (sphereRadius + pointerOffset);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginClipPath(nil, "graph-clip");
			writer:Rect2Pt(graphBox[1], graphBox[4], nil, nil);
		writer:EndClipPath();
		writer:BeginMarker({sphereRadius*2, sphereRadius*2},
			{sphereRadius, sphereRadius}, nil, true, nil, "arrow-rear");
			writer:Circle({sphereRadius, sphereRadius}, sphereRadius,
				{"pointer-arrow-marker"});
		writer:EndMarker();
		writer:BeginMarker({sphereRadius*3, sphereRadius*2},
			{sphereRadius*2, sphereRadius}, "auto", true, nil, "arrow-head");
			writer:Polygon({
					{sphereRadius*3, sphereRadius},
					{0, 0},
					{5, sphereRadius},
					{0, sphereRadius*2}},
				{"pointer-arrow-marker"});
		writer:EndMarker();
	writer:EndDefinitions();

	--Draw background.
	writer:Rect2Pt(graphBox[1], graphBox[4], nil, {"grid-background"});
	DrawLines(writer, gridLines, {"grid-line"});
	
	--Draw the functions.
	DrawLines(writer, linearLines, {"linear-rgb"});
	writer:Path(gammaFuncPath, {"gamma-func"});
	writer:Path(gammaCorrectPath, {"gamma-func", "gamma-correct-dash"});
	
	--Draw the curve labels
	for i, label in ipairs(curveLabels) do
		writer:TextMultiline(label[1], label[2], curveLabelSize, label[4]);
	end

	--Draw the pointers.
	writer:Line(pointers[1], pointers[2], {"pointer-arrow"});
	writer:Line(pointers[3], pointers[4], {"pointer-arrow", "pointer-arrow-dash"});
	
	--Draw pointer labels.
	for i, label in ipairs(pointerLabels) do
		writer:Text(label[1], label[2] + label[3], {"pointer-arrow-label"});
	end
	
	--Draw the X-axis labels and hashes.
	local hashes = {};
	for i = 1, #axisLabels do
		local currValue = (i - 1) / 10;
		local currLoc = vp:Transform(vmath.vec2(currValue, 0));
		hashes[#hashes + 1] = vmath.vec2(currLoc); --copy to preserve
		currLoc[2] = currLoc[2] + hashSize;
		hashes[#hashes + 1] = currLoc;
		writer:Text(axisLabels[i], currLoc + pxAxisLabelOffset[1],
			{"grid-axis-label", "grid-axis-label-x"});
	end

	--Draw the Y-axis labels and hashes.
	for i = 1, #axisLabels do
		local currValue = (i - 1) / 10;
		local currLoc = vp:Transform(vmath.vec2(0, currValue));
		hashes[#hashes + 1] = vmath.vec2(currLoc); --copy to preserve
		currLoc[1] = currLoc[1] - hashSize;
		hashes[#hashes + 1] = currLoc;
		writer:Text(axisLabels[i], currLoc + pxAxisLabelOffset[2],
			{"grid-axis-label", "grid-axis-label-y"});
	end

	DrawLines(writer, hashes, {"grid-axis-hash"});

	--Draw border.
	DrawLines(writer, borderLines, {"grid-border"});
	DrawLines(writer, axisLines, {"grid-axis"});
	
writer:Close();
