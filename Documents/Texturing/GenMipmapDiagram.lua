require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "PixelImage"
require "_utils"

-- Sizing
local imageSize = vmath.vec2(250, 250);

local highImage = vmath.vec2(1, 1)
local lowImage = vmath.vec2(2, 1)

local subImages = SubImage.SubImage(2, 1, imageSize.x, imageSize.y, 25, 50);

--image
local imageHigh = PixelImage.PixelImage("HighMipmap.txt")
local imageLow = PixelImage.PixelImage("LowMipmap.txt")

local pixelSize = imageHigh:Size();
pixelSize = pixelSize / 2;
pixelSize.y = pixelSize.y;

local vpHigh = Viewport.Viewport(imageSize, pixelSize, imageHigh:Size())
local trans2 = Viewport.Transform2D()
vpHigh:SetTransform(trans2);

pixelSize = imageLow:Size();
pixelSize = pixelSize / 2;
pixelSize.y = pixelSize.y;

local vpLow = Viewport.Viewport(imageSize, pixelSize, imageLow:Size())
local trans2 = Viewport.Transform2D()
vpLow:SetTransform(trans2);

--styles
local styleLib = SvgWriter.StyleLibrary();
imageHigh:Style(styleLib, "_high");
imageLow:Style(styleLib, "_low");
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
local texCoord = vmath.vec2(0.57125, 0.60625)
local samplePtHigh = texCoord * imageHigh:Size();
local sampleRectHigh = {imageHigh:RectForSamplePt(samplePtHigh)}

local samplePtLow = texCoord * imageLow:Size();
local sampleRectLow = {imageLow:RectForSamplePt(samplePtLow)}

local ptsHigh =
{
	samplePtHigh - vmath.vec2(2.1, 2.1),
	samplePtHigh + vmath.vec2(2.1, 2.1),
}
ptsHigh = subImages:Transform(highImage, vpHigh:Transform(ptsHigh));

local ptsLow =
{
	samplePtLow - vmath.vec2(1.05, 1.05),
	samplePtLow + vmath.vec2(1.05, 1.05),
}
ptsLow = subImages:Transform(lowImage, vpLow:Transform(ptsLow));

local pathSampleAreaHigh = SvgWriter:Path();
pathSampleAreaHigh
	:M(ptsLow[1])
	:L{ptsLow[1].x, ptsLow[2].y}
	:L(ptsLow[2])
	:L{ptsLow[2].x, ptsLow[1].y}
	:Z()

samplePtHigh = subImages:Transform(highImage, vpHigh:Transform(samplePtHigh));

local pathSampleAreaLow = SvgWriter:Path();
pathSampleAreaLow
	:M(ptsHigh[1])
	:L{ptsHigh[1].x, ptsHigh[2].y}
	:L(ptsHigh[2])
	:L{ptsHigh[2].x, ptsHigh[1].y}
	:Z()

samplePtLow = subImages:Transform(lowImage, vpLow:Transform(samplePtLow));

local ptRadius = vpHigh:Length(0.15)

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), subImages:SvgSize());
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	imageHigh:Draw(writer, subImages:Offset(highImage),
		subImages:SubSize(), {"grid"});
	imageLow:Draw(writer, subImages:Offset(lowImage),
		subImages:SubSize(), {"grid"});

	imageHigh:DrawPixelRect(writer, subImages:Offset(highImage), subImages:SubSize(),
		sampleRectHigh[1], sampleRectHigh[2],
		{"sample_box"})
	
	imageLow:DrawPixelRect(writer, subImages:Offset(lowImage), subImages:SubSize(),
		sampleRectLow[1], sampleRectLow[2],
		{"sample_box"})
	
	writer:Path(pathSampleAreaHigh, {"frag_area"})
	writer:Path(pathSampleAreaLow, {"frag_area"})
	
	writer:Circle(samplePtHigh, ptRadius, {"sample_pt"})
	writer:Circle(samplePtLow, ptRadius, {"sample_pt"})
writer:Close();
