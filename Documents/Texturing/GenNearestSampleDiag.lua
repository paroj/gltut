require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "PixelImage"
require "_utils"

-- Sizing
local imageSize = vmath.vec2(400, 400);

local subImages = SubImage.SubImage(1, 1, imageSize.x, imageSize.y, 0, 50);

local coordSize = 6;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

--image
local image = PixelImage.PixelImage("NearestSampleDiag.txt")

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
styleLib:AddStyle(nil, "sample_box",
	SvgWriter.Style():stroke("red"):stroke_width("7px"):stroke_opacity(0.7)
	:stroke_linejoin("round"):fill("none"));
styleLib:AddStyle(nil, "sample_pt",
	SvgWriter.Style():stroke("none"):fill("green"));
	
--Sample point.
local samplePt = vmath.vec2(1.75, 1.75);

local pts =
{
	samplePt - vmath.vec2(0.4, 0.4),
	samplePt + vmath.vec2(0.4, 0.4),
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

local ptRadius = vp:Length(0.05)

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	image:Draw(writer, vmath.vec2(0, 0), subImages:Size(), {"grid"});
	
	writer:Path(pathSampleArea, {"sample_box"})
	
	writer:Circle(samplePt, ptRadius, {"sample_pt"})
writer:Close();
