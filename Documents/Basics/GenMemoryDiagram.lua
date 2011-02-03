require "SvgWriter"
require "vmath"
require "Viewport"
require "SubImage"
require "GridAxis"
require "_utils"

local subImages = SubImage.SubImage(1, 3, 700, 60, 0, 0);

local coordSize = 10;

local vp = Viewport.Viewport(subImages:SubSize(), {coordSize/2, 0}, coordSize)
local trans2 = Viewport.Transform2D()
vp:SetTransform(trans2);

local styleLib = SvgWriter.StyleLibrary();



local vectorColor = "black";
local vectorSumColor = "red";
local pointSize = 15;

styleLib:AddStyle(nil, "label", SvgWriter.Style{
	stroke="none", fill=vectorColor, font_weight="bold", font_size="15pt",
	font_family="serif",
});

styleLib:AddStyle(nil, "test", SvgWriter.Style{ stroke="black"});

styleLib:AddStyle(nil, "bytes", SvgWriter.Style{ stroke="black", stroke_width="1px", fill="lightblue"});
styleLib:AddStyle(nil, "floats", SvgWriter.Style{ stroke="red", stroke_width="2px", fill="none"});
styleLib:AddStyle(nil, "vecs", SvgWriter.Style{ stroke="darkblue", stroke_width="3px", fill="none"});

styleLib:AddStyle(nil, "positions", SvgWriter.Style{
	stroke="none", fill="yellow", fill_opacity="0.3"
});

styleLib:AddStyle(nil, "colors", SvgWriter.Style{
	stroke="none", fill="gray", fill_opacity="0.3"
});

local testLine =
{
	vmath.vec2(0, 0),
	vmath.vec2(coordSize, 0),
};

testLine = vp:Transform(testLine);

--Block drawing.
local blockHeight = 0.40;

local function GetBlockArray(numBlocks, leftPos, width)
	local blockArray = {};
	
	blockWidth = width / numBlocks;
	
	for i = 1, numBlocks do
		blockArray[#blockArray + 1] = vmath.vec2(leftPos + (blockWidth * (i - 1)), blockHeight / 2);
		blockArray[#blockArray + 1] = vmath.vec2(leftPos + (blockWidth * i), -blockHeight / 2);
	end
	
	return blockArray;
end

local function GetRectSequence(bytesPerValue, valuesPerVec, vecsPerArray, numArrays, leftPos, width)
	local byteArray = nil;
	if(bytesPerValue) then
		local numBytes = bytesPerValue;
		numBytes = numBytes * (valuesPerVec or 1);
		numBytes = numBytes * (vecsPerArray or 1);
		numBytes = numBytes * (numArrays or 1);
		
		byteArray = GetBlockArray(numBytes, leftPos, width);
	end
	
	local valueArray = nil;
	if(valuesPerVec) then
		local numValues = valuesPerVec;
		numValues = numValues * (vecsPerArray or 1);
		numValues = numValues * (numArrays or 1);
		
		valueArray = GetBlockArray(numValues, leftPos, width)
	else
		valueArray = GetBlockArray(1, leftPos, width)
	end
	
	local vecArray = nil;
	
	if(vecsPerArray) then
		local numVecs = vecsPerArray;
		numVecs = numVecs * (numArrays or 1);
		
		vecArray = GetBlockArray(numVecs, leftPos, width)
	else
		if(valuesPerVec) then
			vecArray = GetBlockArray(1, leftPos, width)
		end
	end
	
	local arraysArray = nil;
	if(numArrays) then
		arraysArray = GetBlockArray(numArrays, leftPos, width);
	end
	
	return byteArray, valueArray, vecArray, arraysArray;
end

local sequences =
{
	{3, 4},
	{4, 4, 4},
	{7.4, nil, 4, 3, 2},
}

local startPos = 2.5;

local rectSequences = {};

for i, sequence in ipairs(sequences) do
	rectSequences[i] =
		{GetRectSequence(sequence[2], sequence[3], sequence[4], sequence[5], startPos, sequence[1])};
end

local rectStyles =
{
	"bytes",
	"floats",
	"vecs",
	"arrays",
}


--Text
local globalLabelOffset = vmath.vec2(0.0, -0.05)
local labels =
{
	{"float (4 bytes):", "g_float"},
	{"vec4 (16 bytes):", "g_vec4"},
	{"vertexData:", "g_vertexData"},
};

local writer = SvgWriter.SvgWriter(ConstructSVGName(arg[0]), {subImages:Size().x .."px", subImages:Size().y .. "px"});
	writer:StyleLibrary(styleLib);
	writer:BeginDefinitions();
		writer:BeginGroup(nil, "g_test");
			writer:Line(testLine[1], testLine[2], "test");
		writer:EndGroup();
		for i=1, #sequences do
			writer:BeginGroup(nil, labels[i][2]);
				for j=1, 4 do
					if(rectSequences[i][j]) then
						local floatRects = vp:Transform(rectSequences[i][j])
						for k=1, #floatRects, 2 do
							local style = rectStyles[j];
							if(j == 4) then
								if(k == 1) then style = "positions" else style = "colors" end
							end
							writer:Rect2Pt(floatRects[k], floatRects[k + 1], nil, style);
						end
					end
				end
			writer:EndGroup();
		end
	writer:EndDefinitions();
	
	for i=1, #labels do
		local loc = vmath.vec2(0, 0);
		loc = loc + globalLabelOffset;
		if(labels[i][3]) then loc = loc + labels[i][3] end
		loc = subImages:Transform({1, i}, vp:Transform(loc));
		writer:Text(labels[i][1], loc, "label");
	end

	
	for i=1, #labels do
		writer:Use(labels[i][2], subImages:Offset(1, i), subImages:SubSize());
	end
	
--	writer:Use("g_test", subImages:Offset(1, 3), subImages:SubSize());

writer:Close();
