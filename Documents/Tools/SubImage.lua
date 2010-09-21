
require "vmath"

module(..., package.seeall);

local ClassMembers = {}

local function AddMembers(classInst, members)
	members = members or ClassMembers;
	for funcName, func in pairs(members) do
		classInst[funcName] = func;
	end
end

function ClassMembers:Size()
	local size = vmath.vec2(0.0, 0.0);
	
	size.x = self.subImageSize.x * self.imageArray.x +
		(self.spacing.x * (self.imageArray.x - 1));

	size.y = self.subImageSize.y * self.imageArray.y +
		(self.spacing.y * (self.imageArray.y - 1));
		
	return size;
end

function ClassMembers:Offset(x, y)
	if(y == nil) then
		y = x.y;
		x = x.x;
	end

	x = x - 1;
	y = y - 1;

	local offset = vmath.vec2(0.0, 0.0);

	offset.x = (self.subImageSize.x + self.spacing.x) * x;
	offset.y = (self.subImageSize.y + self.spacing.y) * y;

	return offset;
end

function ClassMembers:NumImages()
	return self.imageArray;
end

function ClassMembers:SubSize()
	return self.subImageSize;
end

--Points must be in pixel coordinates, relative to the upper-left.
function ClassMembers:Transform(image, points)
	local offset = self:Offset(image[1], image[2]);
	if(vmath.vtype(points) == "table") then
		local ret = {};
		for i, realPoint in ipairs(points) do
			ret[i] = vmath.vec2(realPoint) + offset;
		end
		return ret;
	end
	
	return vmath.vec2(points) + offset;
end



function SubImage(subImagesX, subImagesY, subImageWidth, subImageHeight,
				  subImageHSpacing, subImageVSpacing)

	if(not subImageHeight) then
		subImageVSpacing = subImageWidth.y;
		subImageHSpacing = subImageWidth.x;
		subImageHeight = subImagesY.y;
		subImageWidth = subImagesY.x;
		subImagesY = subImagesX.y;
		subImagesX = subImagesX.x;
	end
	
	local subImage = {};
	
	subImage.subImageSize = vmath.vec2(subImageWidth, subImageHeight);
	subImage.imageArray = vmath.vec2(subImagesX, subImagesY);
	subImage.spacing = vmath.vec2(subImageHSpacing, subImageVSpacing);
	
	AddMembers(subImage, ClassMembers);
	
	return subImage;
end





