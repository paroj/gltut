require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "Colors"
require "_utils"

local imageSize = vmath.vec2(400, 150);

local subImages = SubImage.SubImage(1, 1, imageSize.x, imageSize.y, 0, 0);

local coordSize = 8;
local coordWidth = coordSize * (imageSize.x / imageSize.y);

local vp = Viewport.Viewport(imageSize, {0, 2}, {coordWidth, coordSize})
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();

local lightSourceColor = Colors.clr("lightSource");
local surfaceColor = Colors.clr("surface");
local textSize = 14;

styleLib:AddStyle(nil, "surface", SvgWriter.Style():stroke("none"):fill(surfaceColor));

styleLib:AddStyle(nil, "label",
	SvgWriter.Style():stroke("none"):fill("black"):font_size(textSize .. "pt")
		:text_anchor("middle"));
		
styleLib:AddStyle(nil, "point", SvgWriter.Style():stroke("none"):fill("black"));

styleLib:AddStyle(nil, "src_arrowhead",
	SvgWriter.Style():stroke("black"):fill("black"));
	
styleLib:AddStyle(nil, "dir_arrowhead",
	SvgWriter.Style():stroke("green"):fill("green"));
	
styleLib:AddStyle(nil, "src_direction",
	SvgWriter.Style():stroke("black"):stroke_width("1px"):marker_end(SvgWriter.uriLocalElement("src_arrow")));
	
styleLib:AddStyle(nil, "normal_direction",
	SvgWriter.Style():stroke("green"):stroke_width("1px"):marker_end(SvgWriter.uriLocalElement("dir_arrow")));

local function WriteFile(filename, viewPos, labels)
	--Surface and light.
	local surfaceDim =
	{
		vmath.vec2(-coordWidth / 2, 0), vmath.vec2(coordWidth / 2, -2),
	};

	local lightPos = vmath.vec2(-7, 2);
	local thePoint = vmath.vec2(0, 0);

	--Compute reflection and half-angle vectors.
	local reflectDir = nil;
	local halfAngleDir = nil;

	do
		local finalPos = {}
		local incident = vmath.norm(lightPos - thePoint);
		local viewDir = vmath.norm(viewPos - thePoint);
		
		reflectDir = vmath.vec2(-incident.x, incident.y);
		halfAngleDir = vmath.norm(viewDir + incident);
	end

	local vectorLengths = 4;

	--Compute the normal vector.
	local normalDir = vmath.vec2(0, 1);

	--Compute all of the vectors we need to draw.
	local vectors = 
	{
		(normalDir * vectorLengths) + thePoint,
		lightPos,
		viewPos,
		(reflectDir * vectorLengths) + thePoint,
		(halfAngleDir * vectorLengths) + thePoint,
	}

	vectors = vp:Transform(vectors);
	thePoint = vp:Transform(thePoint);

	surfaceDim = vp:Transform(surfaceDim);

	--Vertices
	local pointRadius = 4;
	local radiusPt = vmath.vec2(pointRadius, pointRadius);

	local writer = SvgWriter.SvgWriter(ConstructSVGName(filename), {subImages:Size().x .."px", subImages:Size().y .. "px"});
		writer:StyleLibrary(styleLib);
		writer:BeginDefinitions();
			WriteStandardArrowhead(writer, "dir_arrow", {"dir_arrowhead"});
			WriteStandardArrowhead(writer, "src_arrow", {"src_arrowhead"});
		writer:EndDefinitions();

		--Draw surface and light.
		writer:Rect2Pt(surfaceDim[1], surfaceDim[2], nil, {"surface"});
		
		--Draw the lines
		for i=1, #vectors do
			writer:Line(thePoint, vectors[i], {labels[i][2]});
		end
		
		--Draw the labels
		for i=1, #labels do
			writer:Text(labels[i][1], labels[i][3] + vectors[i], {"label"});
		end

	--	writer:Use("g_point", viewPoint, radiusPt * 2);
	--	writer:Text("V", viewPoint + viewLabelOffset, {"label"});
	writer:Close();
end

local mainLabels =
{
	{"N", "src_direction", vmath.vec2(10, 0)},
	{"L", "src_direction", vmath.vec2(-10, 4)},
	{"V", "src_direction", vmath.vec2(8, 0)},
	{"R", "normal_direction", vmath.vec2(4, -8)},
	{"H", "normal_direction", vmath.vec2(-4, -4)},
}

WriteFile(arg[0], vmath.vec2(2, 4), mainLabels);

local perfectLabels =
{
	{"N", "src_direction", vmath.vec2(10, 0)},
	{"L", "src_direction", vmath.vec2(-10, 4)},
	{"V", "src_direction", vmath.vec2(8, 0)},
	{"R", "normal_direction", vmath.vec2(4, -8)},
	{"H", "normal_direction", vmath.vec2(-10, 0)},
}

WriteFile("GenHalfangleVectorPerfect.lua", vmath.vec2(7, 2), perfectLabels);

