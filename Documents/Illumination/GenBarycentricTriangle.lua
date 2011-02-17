require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "_utils"

local subImageSize = 300;

local subImages = SubImage.SubImage(1, 1, subImageSize, subImageSize, 50, 0);

local coordSize = 2;

local vp = Viewport.Viewport(subImages:SubSize(), {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local scaleFactor = 0.25;

-- Styles
local styleLib = SvgWriter.StyleLibrary();
local pointSize = 9;
local textSize = 25;

styleLib:AddStyle(nil, "triangle",
	SvgWriter.Style():stroke("black"):fill("none"));
	
styleLib:AddStyle(nil, "baryPts",
	SvgWriter.Style():stroke("violet"):stroke_width("4px"):fill("none"):stroke_opacity(0.5));
	
styleLib:AddStyle(nil, "vertex",
	SvgWriter.Style():stroke("black"):fill("black"));
	
styleLib:AddStyle(nil, "label",
	SvgWriter.Style():stroke("none"):fill("black"):font_size(textSize .. "px")
		:font_family("monospace"):text_anchor("middle"));

styleLib:AddStyle(nil, "vertex_label",
	SvgWriter.Style():stroke("none"):fill("black"):font_size(textSize .. "px")
		:font_family("monospace"):font_weight("bold"):text_anchor("middle"));

local function Output(convertName, barycoords)
	--Triangle
	local trianglePts =
	{
		vmath.vec2(0.2, 0.7),
		vmath.vec2(0.7, -0.3),
		vmath.vec2(-0.7, -0.6),
	};

	local baryPt = vmath.vec2(0, 0);

	for i, pt in ipairs(trianglePts) do
		baryPt = baryPt + (pt * barycoords[i]);
	end

	baryPt = vp:Transform(baryPt);

	trianglePts = vp:Transform(trianglePts);

	--Bary-lines
	local baryLines = SvgWriter.Path();
	for i, pt in ipairs(trianglePts) do
		baryLines:M(baryPt):L(pt);
	end

	--Labels
	local vertexLableOffsets =
	{
		vmath.vec2(15, -5),
		vmath.vec2(18, 5),
		vmath.vec2(-18, 10),
	}

	local lineLabelOffsets = 
	{
		vmath.vec2(12, 8),
		vmath.vec2(9, -9),
		vmath.vec2(0, -13),
	}

	local labels =
	{
		"A",
		"B",
		"C",
	}

	local baryLabels =
	{
		"&#x03b1;",
		"&#x03b2;",
		"&#x03b3;",
	}

	local baryPtOffset = vmath.vec2(0, 25);
		

	--Vertices
	local pointRadius = 5;
	local radiusPt = vmath.vec2(pointRadius, pointRadius);

	local writer = SvgWriter.SvgWriter(ConstructSVGName(convertName), {(subImages:Size().x + 1) .."px", (subImages:Size().y + 1) .. "px"});
		writer:StyleLibrary(styleLib);
		writer:BeginDefinitions();
			writer:BeginGroup(nil, "g_point");
				writer:Circle(vmath.vec2(0, 0), pointRadius, {"vertex"});
			writer:EndGroup();
		writer:EndDefinitions();

		writer:Polygon(trianglePts, {"triangle"});
		
		writer:Path(baryLines, {"baryPts"});
		
		for i, pt in ipairs(trianglePts) do
			writer:Use("g_point", pt, radiusPt * 2);
		end

		writer:Use("g_point", baryPt, radiusPt * 2);
		
		writer:Text("P", baryPt + baryPtOffset, {"vertex_label"});

		for i = 1, #trianglePts do
			local labelPt = baryPt + trianglePts[i];
			labelPt = labelPt / 2.0;
			writer:Text(baryLabels[i], labelPt + lineLabelOffsets[i], {"label"});
		end

		for i = 1, #vertexLableOffsets do
			writer:Text(labels[i], trianglePts[i] + vertexLableOffsets[i], {"vertex_label"});
		end
	writer:Close();
end

	local barycoords =


Output(arg[0],
	{
		0.33333333,
		0.33333333,
		0.33333333,
	});

Output(arg[0]:gsub("%.lua", "Edge.lua"),
	{
		0.0,
		0.5,
		0.5,
	});
