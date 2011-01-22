
require "vmath"
require "SvgWriter"

module(..., package.seeall);

local function AddMembers(classInst, members)
	members = members or ClassMembers;
	for funcName, func in pairs(members) do
		classInst[funcName] = func;
	end
end

local ClassMembers = {}
local axisStyleName = "__axis";
local axisArrowStyleName = "__axis_arrow_end";
local axisArrowUriName = "__axis_arrow";
local gridStyleName = "__grid";

local axisIndex = 1;

function ClassMembers:fix(name) return name .. self.axisIndex end

function ClassMembers:AddDefinitions(writer, name)
	writer:BeginDefinitions();
		writer:BeginMarker({10, 8}, {10, 4}, "auto", true, nil, self:fix(axisArrowUriName));
			writer:Path(self.arrowheadPath, {"fill_black", "thin"});
		writer:EndMarker();
	
		writer:BeginGroup(nil, name);
			if(self.bGrid) then
				writer:Path(self.gridPath, {self:fix(gridStyleName)});
			end

			for i=1, #self.axes, 2 do
				writer:Line(self.axes[i], self.axes[i+1],
					{self:fix(axisStyleName), self:fix(axisArrowStyleName)});
			end
		writer:EndGroup();
	writer:EndDefinitions();
end

function GridAxis2D(vp, axisStyle, styleLib, bGrid, gridStyle, gridScale)
	assert(styleLib);
	assert(vp);
	
	axisStyle = axisStyle or SvgWriter.Style():stroke("black"):fill("none"):stroke_width("2px");
	gridStyle = gridStyle or SvgWriter.Style():stroke("#CCC"):fill("none"):stroke_width("1px");
	gridScale = gridScale or 1.0;
	
	local axisGridObj = {};
	axisGridObj.axisIndex = axisIndex;
	axisGridObj.bGrid = bGrid;
	axisIndex = axisIndex + 1;
	
	styleLib:AddStyle(nil, axisStyleName .. axisGridObj.axisIndex, axisStyle);
	styleLib:AddStyle(nil, axisArrowStyleName .. axisGridObj.axisIndex,
		SvgWriter.Style():marker_end(
			SvgWriter.uriLocalElement(axisArrowUriName .. axisGridObj.axisIndex)));

	--Create the axis path.
	local upperBound, lowerBound = vp:Extents();
	local axes = {}

	if(lowerBound[2] < 0) then
		axes[#axes + 1] = vmath.vec2(0, 0);
		axes[#axes + 1] = vmath.vec2(0, lowerBound[2]);
	end
	if(upperBound[2] > 0) then
		axes[#axes + 1] = vmath.vec2(0, 0);
		axes[#axes + 1] = vmath.vec2(0, upperBound[2]);
	end
	if(upperBound[1] > 0) then
		axes[#axes + 1] = vmath.vec2(0, 0);
		axes[#axes + 1] = vmath.vec2(upperBound[1], 0);
	end
	if(lowerBound[1] < 0) then
		axes[#axes + 1] = vmath.vec2(0, 0);
		axes[#axes + 1] = vmath.vec2(lowerBound[1], 0);
	end

	axes = vp:Transform(axes);
	
	axisGridObj.axes = axes;
	
	--Create arrowhead paths
	local arrowheadPath = SvgWriter.Path();
	arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();
	axisGridObj.arrowheadPath = arrowheadPath;
	
	local viewportScale = vmath.vec2(vp:Size());
	
	--Create grid path, if needed.
	if(bGrid) then
		styleLib:AddStyle(nil, gridStyleName .. axisGridObj.axisIndex, gridStyle);
		
		local gridPath = SvgWriter.Path();

		--Vertical lines.
		for i = lowerBound[1], upperBound[1], gridScale do
			local points =
			{
				vmath.vec2(i, lowerBound[2]);
				vmath.vec2(i, upperBound[2]);
			};
			
			points = vp:Transform(points)
			gridPath:M(points[1]):V(points[2][2]);
		end

		--Horizontal lines.
		for i = lowerBound[2], upperBound[2], gridScale do
			local points =
			{
				vmath.vec2(lowerBound[1], i);
				vmath.vec2(upperBound[1], i);
			};
			
			points = vp:Transform(points)
			gridPath:M(points[1]):H(points[2][1]);
		end
		
		axisGridObj.gridPath = gridPath;
	end
	
	AddMembers(axisGridObj, ClassMembers);
	return axisGridObj;
end

