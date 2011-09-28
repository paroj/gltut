require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "PixelImage"
require "_utils"

local image = PixelImage.PixelImage("PixelImage.txt")

local styleLib = SvgWriter.StyleLibrary();
image:Style(styleLib);

local magnification = 16;
local spacing = 40;

local imageWidth = image:Size().x + spacing + (image:Size().x * magnification);
local imageHeight = image:Size().y * magnification;

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {imageWidth .."px", imageHeight .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
	writer:EndDefinitions();
	
	image:Draw(writer, vmath.vec2(0, 0), image:Size());
	image:Draw(writer, vmath.vec2(image:Size().x + spacing, 0),
		image:Size() * magnification);
	
writer:Close();

