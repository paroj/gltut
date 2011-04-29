
require "vmath"

module(..., package.seeall);

local function AddMembers(classInst, members)
	for funcName, func in pairs(members) do
		classInst[funcName] = func;
	end
end


--2D Viewport.
local View = {}

function View:Size()
	return self.pixelSize;
end

--Takes points in viewport space, returns points in pixel space.
--Applies the current transform
function View:Transform(points)
	if(vmath.vtype(points) == "table") then
		local ret = {};
		for i, realPoint in ipairs(points) do
			ret[i] = self:Transform(realPoint);
		end
		return ret;
	end
	
	local point = points;

	if(self.transform) then
		point = self.transform:Matrix():Transform(point)
	end;

	point = self.matrix:Transform(point);
	point = point + self.pixelOffset;
	
	return point;
end

--Takes points in viewport space, returns points in pixel space.
--Does not apply the current transform
function View:ViewportTransform(...)
	local transform = self.transform;
	self.transform = nil;
	local ret = self:Transform(...);
	self.transform = transform;
	return ret;
end

function View:SetTransform(transform)
	self.transform = transform;
end

--Returns the top-right and bottom-left corners of the viewport in viewport space.
function View:Extents()
	local halfSize = self.vpSize / 2;
	local upperBound = self.vpOrigin + halfSize;
	local lowerBound = self.vpOrigin - halfSize;
	return upperBound, lowerBound;
end

--Computes what the given viewport length will be in pixel coordinates.
function View:Length(testVal)
	local originVec = vmath.vec2(0, 0);
	local testVec = vmath.vec2(testVal, 0);
	local test1 = self:Transform(originVec);
	local test2 = self:Transform(testVec);
	return vmath.length(test2 - test1);
end

function Viewport(pixelSize, vpOrigin, vpSize, vpPixelOffset)
	local viewport = {};
	
	viewport.pixelSize = vmath.vec2(pixelSize);
	viewport.vpOrigin = vmath.vec2(vpOrigin);
	viewport.pxCenter = viewport.pixelSize / 2;
	if(type(vpSize) == "number") then
		vpSize = vmath.vec2(vpSize, vpSize * (pixelSize[2] / pixelSize[1]))
	end;
	viewport.vpSize = vmath.vec2(vpSize);
	
	if(vpPixelOffset) then
		viewport.pixelOffset = vmath.vec2(vpPixelOffset);
	else
		viewport.pixelOffset = vmath.vec2(0.0, 0.0);
	end
	
	local trans = Transform2D();
	trans:Translate(viewport.pxCenter);
	trans:Scale(viewport.pixelSize);
	trans:Scale(vmath.vec2(1, -1));
	trans:Scale(1.0 / viewport.vpSize);
	trans:Translate(-viewport.vpOrigin);

	viewport.matrix = trans;
	
	AddMembers(viewport, View);
	return viewport;
end


-- Transform 2D.
local function Identity3()
	return vmath.mat3(vmath.vec3{1, 0, 0}, vmath.vec3{0, 1, 0}, vmath.vec3{0, 0, 1});
end

local Trans2D = {}

function Trans2D:Translate(offset)
	local trans = Identity3();
	trans:SetCol(3, vmath.vec3(offset, 1));
	self.currMatrix = self.currMatrix * trans;
end

function Trans2D:Scale(scale)
	local scaleMat = Identity3();
	scaleMat[1][1] = scale[1];
	scaleMat[2][2] = scale[2];
	self.currMatrix = self.currMatrix * scaleMat;
end

function Trans2D:Rotate(angleDeg)
	local rotation = Identity3();
	angleDeg = math.rad(angleDeg);
	local sinAng, cosAng = math.sin(angleDeg), math.cos(angleDeg);
	
	rotation[1][1] = cosAng; rotation[2][1] = -sinAng;
	rotation[1][2] = sinAng; rotation[2][2] = cosAng;
	
	self.currMatrix = self.currMatrix * rotation;
end

function Trans2D:MultMatrix(matrix)
	self.currMatrix = self.currMatrix * matrix;
end

function Trans2D:Push()
	if(not self.stack) then
		self.stack = {};
		self.stack.top = 0;
	end
	
	self.stack[self.stack.top + 1] = self.currMatrix;
	self.stack.top = self.stack.top + 1;
end

function Trans2D:Pop()
	assert(self.stack, "No Push has been called yet.");
	assert(self.stack.top > 0, "Matrix stack underflow.");
	self.currMatrix = self.stack[self.stack.top];
	self.stack.top = self.stack.top - 1;
end

function Trans2D:Identity()
	self.currMatrix = Identity3();
end

function Trans2D:Matrix()
	return self.currMatrix;
end

function Trans2D:Vector(point)
	return vmath.vec2(point);
end

function Trans2D:Transform(points)
	if(vmath.vtype(points) == "table") then
		local ret = {};
		for i, realPoint in ipairs(points) do
			ret[i] = self:Transform(realPoint);
		end
		return ret;
	end
	
	return self.currMatrix:Transform(points);
end

function Transform2D()
	local transform = {};
	transform.currMatrix = Identity3();
	AddMembers(transform, Trans2D);
	return transform;
end


-- Transform 3D.
local function Identity4()
	return vmath.mat4(
		vmath.vec4{1, 0, 0, 0},
		vmath.vec4{0, 1, 0, 0},
		vmath.vec3{0, 0, 1, 0},
		vmath.vec3{0, 0, 0, 1});
end

local Trans3D = {}

Trans3D.Push = Trans2D.Push;
Trans3D.Pop = Trans2D.Pop;

function Trans3D:Translate(offset)
	local trans = Identity4();
	trans:SetCol(4, vmath.vec4(offset, 1));
	self.currMatrix = self.currMatrix * trans;
end

function Trans3D:Scale(scale)
	local scaleMat = Identity4();
	scaleMat[1][1] = scale[1];
	scaleMat[2][2] = scale[2];
	scaleMat[3][3] = scale[3];
	self.currMatrix = self.currMatrix * scaleMat;
end

function Trans3D:RotateX(angleDeg)
	local rotation = Identity4();
	angleDeg = math.rad(angleDeg);
	local sinAng, cosAng = math.sin(angleDeg), math.cos(angleDeg);
	
	rotation[2][2] = cosAng; rotation[3][2] = -sinAng;
	rotation[2][3] = sinAng; rotation[3][3] = cosAng;
	
	self.currMatrix = self.currMatrix * rotation;
end

function Trans3D:RotateY(angleDeg)
	local rotation = Identity4();
	angleDeg = math.rad(angleDeg);
	local sinAng, cosAng = math.sin(angleDeg), math.cos(angleDeg);
	
	rotation[1][1] = cosAng; rotation[3][1] = sinAng;
	rotation[1][3] = -sinAng; rotation[3][3] = cosAng;
	
	self.currMatrix = self.currMatrix * rotation;
end

function Trans3D:RotateZ(angleDeg)
	local rotation = Identity4();
	angleDeg = math.rad(angleDeg);
	local sinAng, cosAng = math.sin(angleDeg), math.cos(angleDeg);
	
	rotation[1][1] = cosAng; rotation[2][1] = -sinAng;
	rotation[1][2] = sinAng; rotation[2][2] = cosAng;
	
	self.currMatrix = self.currMatrix * rotation;
end

Trans3D.MultMatrix = Trans2D.MultMatrix;
Trans3D.Transform = Trans2D.Transform


function Trans3D:Identity()
	self.currMatrix = Identity4();
end

function Trans3D:Matrix()
	return self.currMatrix;
end

function Trans3D:Vector(point)
	return vmath.vec3(point);
end

function Transform3D()
	local transform = {};
	transform.currMatrix = Identity4();
	AddMembers(transform, Trans3D);
	return transform;
end


