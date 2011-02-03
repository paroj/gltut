require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local subImages = SubImage.SubImage(1, 1, 250, 250, 0, 0);

local coordSize = 20;

local vp = Viewport.Viewport(subImages:SubSize(), {0, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();


local triangleStyles =
{
	{"first_tri", "skyblue"},
	{"second_tri", "orange"},
	{"third_tri", "yellowgreen"},
}

local pointSize = 15;

styleLib
	:AddTable(nil, "base_triangle", {stroke="black", stroke_width="1px"})
	:AddTable(nil, triangleStyles[1][1], {fill=triangleStyles[1][2]})
	:AddTable(nil, triangleStyles[2][1], {fill=triangleStyles[2][2]})
	:AddTable(nil, triangleStyles[3][1], {fill=triangleStyles[3][2]})
	:AddTable(nil, "overlap_clip", {clip_path=SvgWriter.uriLocalElement("overlap")})
	
--Triangles

local trianglePos =
{
	{4, 8}, {-5, -8.5}, {-7.5, -6},
	{-9, -4}, {8.5, -3}, {7.5, -6.5},
	{6, -9}, {1, 9}, {-2, 7},
}

local outTris = {};
for i, position in ipairs(trianglePos) do
	outTris[i] = vp:Transform(vmath.vec2(unpack(position)));
end

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginClipPath(nil, "overlap");
			local points = vp:Transform{vmath.vec2(-coordSize/2, coordSize/2),
				vmath.vec2(coordSize/2, 0)}
			writer:Rect2Pt(points[1], points[2], nil, {"show_clip"});
		writer:EndClipPath();
	writer:EndDefinitions();

	for i=1, #outTris, 3 do
		writer:Polygon({outTris[i], outTris[i+1], outTris[i+2]},
			{"base_triangle", triangleStyles[math.ceil(i/3)][1]});
	end

	--Draw the overlapping region.
	writer:Polygon({outTris[1], outTris[2], outTris[3]},
		{"base_triangle", triangleStyles[1][1], "overlap_clip"});

writer:Close();
