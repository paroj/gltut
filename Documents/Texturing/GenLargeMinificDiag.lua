require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "PixelImage"
require "_utils"

-- Sizing
local imageSize = vmath.vec2(300, 300);

local subImages = SubImage.SubImage(1, 1, imageSize.x, imageSize.y, 0, 50);

local coordSize = 6;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

--image
local image = PixelImage.PixelImage("HighMipmap.txt")

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
local texCoord = vmath.vec2(0.57125, 0.60625)
local samplePt = texCoord * image:Size();
local sampleRect = {PixelImage.RectForSamplePt(image, samplePt)}

local pts =
{
	samplePt - vmath.vec2(2.1, 2.1),
	samplePt + vmath.vec2(2.1, 2.1),
}
pts = vp:Transform(pts);

local pathSampleArea = SvgWriter:Path();
pathSampleArea
	:M(pts[1])
	:L{pts[1].x, pts[2].y}
	:L(pts[2])
	:L{pts[2].x, pts[1].y}
	:Z()

samplePt = vp:Transform(samplePt);

local ptRadius = vp:Length(0.1)

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	image:Draw(writer, vmath.vec2(0, 0), subImages:Size(), {"grid"});
	image:DrawPixelRect(writer, vmath.vec2(0, 0), subImages:Size(),
		sampleRect[1], sampleRect[2],
		{"sample_box"})
	
	writer:Path(pathSampleArea, {"frag_area"})
	
	writer:Circle(samplePt, ptRadius, {"sample_pt"})
writer:Close();
