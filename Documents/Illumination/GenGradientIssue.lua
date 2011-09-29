require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "_utils"

local subImageSize = 200;

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

styleLib:AddStyle(nil, "quad",
	SvgWriter.Style():stroke("none"):fill(SvgWriter.uriLocalElement("issue_grad")));
	

--Vertices
local quadPts =
{
	vmath.vec2(-1.0, 1.0),
	vmath.vec2(1.0, 1.0),
	vmath.vec2(1.0, -1.0),
	vmath.vec2(-1.0, -1.0),
};

quadPts = vp:Transform(quadPts);


--Vertices
local pointRadius = 5;
local radiusPt = vmath.vec2(pointRadius, pointRadius);

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), subImages:SvgSize());
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:LinearGradient("issue_grad",
			{
				{offset="0%", color="black"},
				{offset="50%", color="#AAA"},
				{offset="100%", color="#CCC"},
			},
			{"0%", "100%"}, {"100%", "0%"}
		);
	writer:EndDefinitions();

	writer:Polygon(quadPts, {"quad"});
writer:Close();
