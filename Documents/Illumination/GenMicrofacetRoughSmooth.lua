require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local imageSize = vmath.vec2(400, 100);

local subImages = SubImage.SubImage(1, 2, imageSize.x, imageSize.y, 0, 25);

local coordSize = 3;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

local vp = Viewport.Viewport(imageSize, {0, 0}, {coordWidth, coordSize})
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local lightSourceColor = "yellow";
local surfaceColor = "lightblue";
local rayColor = "darkblue";

styleLib:AddStyle(nil, "surface", SvgWriter.Style():stroke("none"):fill(surfaceColor));

--Surface and light.
local surfaceDim =
{
	vmath.vec2(-coordWidth / 2, 0), vmath.vec2(coordWidth / 2, -coordSize / 2),
};

local function GenerateSurfacePath(heights)
	local path = SvgWriter.Path();
	
	path:M(vp:Transform(surfaceDim[2]));
	path:L(vp:Transform(vmath.vec2(surfaceDim[1][1], surfaceDim[2][2])));
	path:L(vp:Transform(surfaceDim[1]));
	
	local baseHeight = 0;
	local facetWidth = (coordWidth / #heights);
	for i=1, #heights do
		local xPos = surfaceDim[1][1] + (i * facetWidth);
		path:L(vp:Transform(vmath.vec2(xPos, heights[i] + baseHeight)));
	end
	
	path:Z();
	return path;
end

local smoothHeights =
{
	0.2,
	-0.15,
	0.1,
	0.2,
	0.1,
	-0.05,
	0.03,
	-0.13,
	-0.18,
	0.2,
	-0.13,
	-0.04,
	0,
}

local roughHeights =
{
	0.8,
	-0.2,
	0.8,
	0.4,
	0.3,
	-0.7,
	0.4,
	-0.2,
	-0.1,
	0.9,
	-0.5,
	-0.2,
	0.4,
}

local smoothPath = GenerateSurfacePath(smoothHeights);
local roughPath = GenerateSurfacePath(roughHeights);

local lightSourceRadius = 10;

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		WriteStandardArrowhead(writer, "arrow", {"arrowhead"});
		
		writer:BeginGroup(nil, "g_smooth_surface");
			writer:Path(smoothPath, {"surface"});
		writer:EndGroup();
		writer:BeginGroup(nil, "g_rough_surface");
			writer:Path(roughPath, {"surface"});
		writer:EndGroup();

	writer:EndDefinitions();

	writer:Use("g_smooth_surface", subImages:Offset(1, 1), subImages:SubSize());
	writer:Use("g_rough_surface", subImages:Offset(1, 2), subImages:SubSize());

writer:Close();
