require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local subImages = SubImage.SubImage(1, 1, 600, 300, 0, 0);

local coordWidth = 20;

local vp = Viewport.Viewport({600, 300}, {0, 4}, coordWidth)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);


local vectorColor = "black";
local vectorSumColor = "red";
local pointSize = 15;

local styleLib = SvgWriter.StyleLibrary();

styleLib:AddStyle(nil, "std_normal",
	SvgWriter.Style():stroke("red"):fill("none"));

styleLib:AddStyle(nil, "tall",
	SvgWriter.Style():stroke("blue"):fill("none"));

styleLib:AddStyle(nil, "short",
	SvgWriter.Style():stroke("orange"):fill("none"));

styleLib:AddStyle(nil, "label",
	SvgWriter.Style():stroke("none"):fill(vectorColor):font_size("14pt"):font_family("monospace"):font_weight("bold"):text_anchor("middle") );

styleLib:AddStyle(nil, "legend_text",
	SvgWriter.Style():stroke("none"):fill(vectorColor):font_size("14pt"):font_family("monospace"):font_weight("bold") );

styleLib:AddStyle(nil, "vertex", SvgWriter.Style():stroke("none"):fill("black"));

--Generate axis data.
local axisData = GridAxis.GridAxis2D(vp, nil, styleLib, true, nil);


local plotScale = vmath.vec2(0.5, 8);

local function MakeGaussianPath(sigmaSqr)
	local path = SvgWriter.Path();
	
	local variance = 2 * sigmaSqr;
	local constant = 1 / math.sqrt(variance * math.pi);
	
	local maxValue = 0;
	
	local function ComputeGauss(x)
		x = plotScale[1] * x;
		local x2 = x*x;
		local expTerm = math.exp(-x2 / variance);
		
		if(maxValue < plotScale[2] * (constant * expTerm)) then
			maxValue = plotScale[2] * (constant * expTerm);
		end
		return plotScale[2] * (constant * expTerm);
	end
	
	local bFirst = true;
	
	for i = -coordWidth, coordWidth, 0.25 do
		if(bFirst) then
			path:M(vp:Transform(vmath.vec2(i, ComputeGauss(i))))
			bFirst = false;
		else
			path:L(vp:Transform(vmath.vec2(i, ComputeGauss(i))))
		end
	end
	
	return path;
end

local distributions =
{
	{1, "std_normal"},
	{0.2, "tall"},
	{5, "short"},
}

local paths = {};
for i=1, #distributions do
	paths[i] = MakeGaussianPath(distributions[i][1]);
end

--Labels
local horizontalLabels =
{
	{8, vmath.vec2(0, 20)},
	{-8, vmath.vec2(0, 20)},
	{16, vmath.vec2(0, 20)},
	{-16, vmath.vec2(0, 20)},
}

local verticalLabels =
{
	{1.0, vmath.vec2(20, 5);}
}

--Legend
local legendStart = vp:Transform(vmath.vec2(4.7, 7.5));
local legendLineWidth = 35;
local legendItemHeight = 30;
local legendTextSpace = 10;
local legendTextVertOffset = 5;

local pointRadius = 4;
local radiusPt = vmath.vec2(pointRadius, pointRadius);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	axisData:AddDefinitions(writer, "g_axes");
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_point");
			writer:Circle(vmath.vec2(0, 0), pointRadius, {"vertex"});
		writer:EndGroup();
	writer:EndDefinitions();


	writer:Use("g_axes", subImages:Offset(1, 1), subImages:SubSize());
	
	for i=1, #distributions do
		writer:Path(paths[i], {distributions[i][2]});
	end
	
	for i=1, #horizontalLabels do
		local point = vmath.vec2(horizontalLabels[i][1], 0);
		point = point * plotScale;
		point = vp:Transform(point);
		writer:Use("g_point", point, radiusPt * 2);
		writer:Text(tostring(horizontalLabels[i][1]), point + horizontalLabels[i][2], {"label"});
	end
	
	for i=1, #verticalLabels do
		local point = vmath.vec2(0, verticalLabels[i][1] * plotScale[2]);
		point = vp:Transform(point);
		writer:Use("g_point", point, radiusPt * 2);
		writer:Text(tostring(verticalLabels[i][1]), point + verticalLabels[i][2], {"label"});
	end
	
	for i=1, #distributions do
		local point = legendStart + vmath.vec2(0, (i-1) * legendItemHeight);
		writer:Line(point, point + vmath.vec2(legendLineWidth, 0), distributions[i][2]);
		point = point + vmath.vec2(legendLineWidth + legendTextSpace, legendTextVertOffset);
		writer:Text("&#x03C3; = ".. tostring(distributions[i][1]), point, {"legend_text"});
	end
	
writer:Close();
