require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "PixelImage"
require "_utils"

-- Sizing
local imageSize = vmath.vec2(350, 350);

local subImages = SubImage.SubImage(1, 1, imageSize.x, imageSize.y, 0, 50);

local coordSize = 6;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

--image
local image = PixelImage.PixelImage("Checkerboard.txt")

local pixelSize = image:Size();
pixelSize = pixelSize / 2;
pixelSize.y = pixelSize.y;

local vp = Viewport.Viewport(imageSize, pixelSize, image:Size())
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

--styles
local styleLib = SvgWriter.StyleLibrary();
image:Style(styleLib);
styleLib:AddStyle(nil, "grid",
	SvgWriter.Style():stroke("#888"):stroke_width("1.5px"):fill("none"));
styleLib:AddStyle(nil, "frag_area",
	SvgWriter.Style():stroke("red"):stroke_width("7px"):stroke_opacity(0.7)
	:stroke_linejoin("round"):fill("none"));
styleLib:AddStyle(nil, "sample_box",
	SvgWriter.Style():stroke("#4B4"):stroke_width("4px"):fill("none"));
styleLib:AddStyle(nil, "sample_pt",
	SvgWriter.Style():stroke("none"):fill("goldenrod"));
	
--Sample point.
local texCoord = vmath.vec2(0.5, 0.5)
local samplePt = texCoord * image:Size();

local lowLeftPt = samplePt - vmath.vec2(5.5, 5.5)
local upRightPt = samplePt + vmath.vec2(5.5, 5.5)

local offset = vmath.vec2(0.8, -0.8)

local pts =
{
	lowLeftPt + offset,
	lowLeftPt - offset,
	upRightPt - offset,
	upRightPt + offset,
}
pts = vp:Transform(pts);

local pathSampleArea = SvgWriter:Path();
pathSampleArea
	:M(pts[1])
	:L(pts[2])
	:L(pts[3])
	:L(pts[4])
	:Z()

local sampleTopLeft;

for i, pt in ipairs(pts) do
	if(sampleTopLeft) then
		sampleTopLeft.x = math.min(sampleTopLeft.x, pt.x)
		sampleTopLeft.y = math.min(sampleTopLeft.y, pt.y)
	else
		sampleTopLeft = vmath.vec2(pt);
	end
end

local sampleSize;

for i, pt in ipairs(pts) do
	if(sampleSize) then
		sampleSize.x = math.max(sampleSize.x, pt.x - sampleTopLeft.x)
		sampleSize.y = math.max(sampleSize.y, pt.y - sampleTopLeft.y)
	else
		sampleSize = vmath.vec2(pt) - sampleTopLeft;
	end
end

samplePt = vp:Transform(samplePt);

local ptRadius = vp:Length(0.25)

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), subImages:SvgSize());
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	image:Draw(writer, vmath.vec2(0, 0), subImages:Size(), {"grid"});
	
	writer:Path(pathSampleArea, {"frag_area"})
	
	writer:Circle(samplePt, ptRadius, {"sample_pt"})
writer:Close();

local writer = SvgWriter.SvgWriter("Mipmap" .. ConstructSVGName(arg[0]), subImages:SvgSize());
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	image:Draw(writer, vmath.vec2(0, 0), subImages:Size(), {"grid"});
	
	image:DrawPixelRect(writer, vmath.vec2(0, 0), subImages:Size(),
		vmath.vec2(2, 2), vmath.vec2(12, 12),
		{"sample_box"})
	
	writer:Path(pathSampleArea, {"frag_area"})
	
	writer:Circle(samplePt, ptRadius, {"sample_pt"})
writer:Close();
