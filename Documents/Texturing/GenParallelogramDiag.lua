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
local image = PixelImage.PixelImage("Parallelogram.txt")

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
local texCoord = vmath.vec2(0.395, 0.385)
local samplePt = texCoord * image:Size();

local lowLeftPt = samplePt - vmath.vec2(5.5, 5.5)
local upRightPt = samplePt + vmath.vec2(5.5, 5.5)

local pts =
{
	vmath.vec2(1.2, 1.7),
	vmath.vec2(1.8, 4.3),
	vmath.vec2(5.3, 4.4),
	vmath.vec2(4.3, 1.8),
}
pts = vp:Transform(pts);

local pathSampleArea = SvgWriter:Path();
pathSampleArea
	:M(pts[1])
	:L(pts[2])
	:L(pts[3])
	:L(pts[4])
	:Z()

samplePt = vp:Transform(samplePt);

local ptRadius = vp:Length(0.25)

local sampleBoxes =
{
	{vmath.vec2(1, 5), vmath.vec2(1, 1)},
	{vmath.vec2(4, 5), vmath.vec2(1, 1)},
	{vmath.vec2(4, 4), vmath.vec2(1, 1)},
	{vmath.vec2(2, 4), vmath.vec2(2, 2)},
}


local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	image:Draw(writer, vmath.vec2(0, 0), subImages:Size(), {"grid"});
	
	for i, box in ipairs(sampleBoxes) do
		image:DrawPixelRect(writer, vmath.vec2(0, 0), subImages:Size(),
			box[1], box[2],
			{"sample_box"})
	end
	
	writer:Path(pathSampleArea, {"frag_area"})
	
	writer:Circle(samplePt, ptRadius, {"sample_pt"})
writer:Close();
