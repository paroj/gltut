
local realPrint = print;
--package.cpath = package.cpath..";./?.dll;./?.so;../lib/?.so;../lib/vc_dll/?.dll;../lib/bcc_dll/?.dll;../lib/mingw_dll/?.dll;"
require("wx")
print = realPrint;

require "XmlWriter"
require "vmath"
require "lfs"

--[[
Command line format:

lua ConvCollada.lua <inputFile> <meshName> [options]

* <inputFile>: the Collada file to process.
* <meshName>: the name of the mesh in the Collada file to process.

Options:

* -mapfile <mapFileName>		: Specifies how semantic names map to attribute indices
* -mapstd						: Equivalent to -mapfile <ConvCollada.lua dir>stdmap.txt
* -map <semanticName>=<number> ...	:Specifies how semantic names map to attribute indices.
* -vao <vaoName> <number> <number> ...	:Specifies a named VAO, with attribute indices.
* -o <outputFilename>

You must provide one of the -map fields. You do not have to provide a -vao or -o. The default
filename is the <inputFile>.xml.
]]

--Utility iterator over all child XML nodes. Nodes of ANY type.
local function ixmlnodes(parNode)
	local currNode = parNode:GetChildren();
	return function()
		local ret = currNode;
		if(currNode) then currNode = currNode:GetNext() end
		return ret;
	end
end

--Iterator over all child XML elements. ONLY elements.
local function ixmlelements(parNode, nodeName)
	local currNode = parNode:GetChildren();
	if(nodeName) then
		while(currNode and
			not (currNode:GetType() == wx.wxXML_ELEMENT_NODE and
			currNode:GetName() == nodeName)) do
			
			currNode = currNode:GetNext();
		end
		
		return function()
			local ret = currNode;
			if(currNode) then
				repeat
					currNode = currNode:GetNext();
				until((not currNode) or
					(currNode:GetType() == wx.wxXML_ELEMENT_NODE and
					currNode:GetName() == nodeName))
			end
			return ret;
		end
	else
		while(currNode and
			currNode:GetType() ~= wx.wxXML_ELEMENT_NODE) do
			
			currNode = currNode:GetNext();
		end
		
		return function()
			local ret = currNode;
			if(currNode) then
				repeat
					currNode = currNode:GetNext();
				until((not currNode) or currNode:GetType() == wx.wxXML_ELEMENT_NODE)
			end
			return ret;
		end
	end
end

local function findXmlChild(parNode, nodeName)
	for xChild in ixmlelements(parNode, nodeName) do
		return xChild;
	end
	
	return nil;
end

local function popOne(first, ...)
	return ...
end

local function popTwo(first, second, ...)
	return ...
end


local inputFile, meshName = ...;
assert(inputFile, "You must provide an input file.");
assert(meshName, "You must provide a mesh name to export.");

local optionProcs = {}

function optionProcs.mapfile(options, optionList, iCurrOption)
	assert(optionList[iCurrOption] and optionList[iCurrOption]:sub(1, 1) ~= "-",
		"You must specify a mapping file name.");
		
	local filename = optionList[iCurrOption];
		
	local hFile = assert(io.open(filename, "r"),
		"Could not open the mapping file \"" .. filename .. "\".");
	
	for line in hFile:lines() do
		local semantic, number = line:match("([^%=]+)%=(%d+)");
		if(semantic) then
			options.map[semantic] = number;
		end
	end
	
	hFile:close();
	
	return 1;
end

function optionProcs.mapstd(options, optionList, iCurrOption)
	local fnameLoc = arg[0]:match([[()[^%\%/]+$]]) - 1;
	local thisDir = arg[0]:sub(1, fnameLoc)
	optionProcs.mapfile(options, {thisDir .. "stdmap.txt"}, 1);
	return 0;
end

function optionProcs.map(options, optionList, iCurrOption)
	assert(optionList[iCurrOption] and optionList[iCurrOption]:sub(1, 1) ~= "-",
		"You must specify at least one mapping.");
		
	local iProcCount = 0;
	while(optionList[iCurrOption] and optionList[iCurrOption]:sub(1, 1) ~= "-") do
		local currOpt = optionList[iCurrOption];
		local semantic, number = currOpt:match("([^%=]+)%=(%d+)");
		
		assert(semantic, "Semantic mapping must be specified as SEMANTIC=attrib.");
		
		options.map[semantic] = number;
		iCurrOption = iCurrOption + 1;
		iProcCount = iProcCount + 1;
	end
	
	return iProcCount;
end

function optionProcs.vao(options, optionList, iCurrOption)
	assert(optionList[iCurrOption] and optionList[iCurrOption]:sub(1, 1) ~= "-",
		"You must specify a VAO name.");
	local vao = {};
	local vaoName = optionList[iCurrOption];
	assert(not options.vaos[vaoName], "The VAO named \"" .. vaoName .. "\" has already been specified.");
	iCurrOption = iCurrOption + 1;

	assert(optionList[iCurrOption] and optionList[iCurrOption]:sub(1, 1) ~= "-",
		"You must specify at least one VAO attribute.");

	local iProcCount = 1;
	while(optionList[iCurrOption] and optionList[iCurrOption]:sub(1, 1) ~= "-") do
		assert(tonumber(optionList[iCurrOption]),
			"The VAO attribute must be a valid attribute index.");
			
		vao[#vao + 1] = optionList[iCurrOption];
		iCurrOption = iCurrOption + 1;
		iProcCount = iProcCount + 1;
	end
	
	options.vaos[vaoName] = vao;
	
	return iProcCount;
end

function optionProcs.o(options, optionList, iCurrOption)
	options.outputFile = optionList[iCurrOption];
	return 1;
end

local function ParseOptions(optionList)
	local options =
	{
		map = {},
		outputFile = inputFile:gsub("%.[^%.]+$", ".xml"),
		vaos = {},
	}
	
	local iCurrOption = 1;
	while(iCurrOption <= #optionList) do
		local currOpt = optionList[iCurrOption];
		assert(currOpt:sub(1, 1) == "-",
			"Malformed option list starting at \"" .. currOpt .. "\"");
		
		currOpt = currOpt:sub(2, -1);
		assert(optionProcs[currOpt], "Unknown option called \"" .. currOpt .. "\"");
		
		local iNumSkip = optionProcs[currOpt](options, optionList, iCurrOption + 1);
		iCurrOption = iCurrOption + 1 + iNumSkip;
	end

	return options;
end


local options = ParseOptions({popTwo(...)});

local reverseMap = {}
local bFoundMap = false;
for semantic, number in pairs(options.map) do
	reverseMap[number] = semantic;
	bFoundMap = true;
end

assert(bFoundMap, "No -map, -mapstd, or -mapfile option was used. Cannot export a mesh.");

--Check to see if any VAOs talk about non-existent attributes.
for vaoName, vao in pairs(options.vaos) do
	for j, source in ipairs(vao) do
		assert(reverseMap[source],
			"The VAO \"" .. vaoName .. "\" revers to the attribute " .. source .. " which is not in the map.");
	end
end


local colladaDoc, test = wx.wxXmlDocument(inputFile);
assert(colladaDoc, "Could not load XML file \"" .. inputFile .. "\"");
print(inputFile);
assert(colladaDoc:IsOk(), "Could not load XML file \"" .. inputFile .. "\"");

local xColladaElem = colladaDoc:GetRoot();

--Find the library_geometries node.
local xGeometries = nil;
for xChild in ixmlelements(xColladaElem) do
	if(xChild:GetName() == "library_geometries") then
		xGeometries = xChild;
		break;
	end
end

assert(xGeometries, "There are no meshes in the COLLADA file.");

--Find the 'geometry' node with the name designated for export.
local xTargetGeom = nil;
for xChild in ixmlelements(xGeometries, "geometry") do
	if(xChild:GetPropVal("id", "") == meshName) then
		xTargetGeom = xChild;
		break;
	end
end

assert(xTargetGeom, "Could not find the geometry with id '" .. meshName .. "' in the document.");

local xMeshToWrite = nil;
for xChild in ixmlelements(xTargetGeom, "mesh") do
	assert(xMeshToWrite == nil, "Multiple meshes in a geometry are not yet supported.");
	xMeshToWrite = xChild;
end

assert(xMeshToWrite, "Could not find a mesh within the geometry with id '" .. meshName .. "'");

--Collate all of the sources in the mesh.
local sources = {};
local bFound = false;
for xChild in ixmlelements(xMeshToWrite, "source") do
	local bHasId, id = xChild:GetPropVal("id");
	assert(bHasId, "Malformed COLLADA. No 'id' attribute on 'source' element.");
	sources["#" .. id] = xChild;
	bFound = true;
end

assert(bFound, "Could not find any 'source' elements in the '" .. meshName .. "'.");

--Get any vertex remappings.
local vertexRemap = {};
local vertexRemapId = nil;
for xChild in ixmlelements(xMeshToWrite, "vertices") do
	local bHasId, id = xChild:GetPropVal("id");
	assert(bHasId, "Malformed COLLADA. No 'id' attribute on 'vertices' element.");
	vertexRemapId = "#" .. id;
	local bFound = false;
	for xInput in ixmlelements(xChild, "input") do
		assert(not bFound, "Cannot process multiple 'vertices' 'input' elements yet.");
		
		local bHasId, semantic = xInput:GetPropVal("semantic");
		assert(bHasId, "An 'input' element on 'vertices' doesn't have a semantic.");
		local bHasId, source = xInput:GetPropVal("source");
		assert(bHasId, "An 'input' element on 'vertices' doesn't have a source.");
		vertexRemap[semantic] = source;
		bFound = true;
	end
end

--Get the triangle data.
local triangleData = {};
for xChild in ixmlelements(xMeshToWrite, "polylist") do
	triangleData.xObj = xChild;
	triangleData.xIndices = findXmlChild(xChild, "p"):GetChildren();
	triangleData.inputs = {};
	triangleData.numInputs = 0;
	for xInput in ixmlelements(xChild, "input") do
		local bHasId, semantic = xInput:GetPropVal("semantic");
		assert(bHasId, "An 'input' element on 'polylist' doesn't have a semantic.");
		local bHasId, source = xInput:GetPropVal("source");
		assert(bHasId, "An 'input' element on 'polylist' doesn't have a source.");
		triangleData.inputs[semantic] = source;
		
		triangleData.numInputs = triangleData.numInputs + 1;
	end
end

--Our VAO mapping has semantics. Create a mapping between triangle data and 
-- actual attributes.
local outputMap = {};
local outputIndexOffset = {}
for semantic, source in pairs(triangleData.inputs) do
	if(options.map[semantic]) then
		outputMap[semantic] = source;
		if(source == vertexRemapId) then
			for vSemantic, vSource in pairs(vertexRemap) do
				outputMap[semantic] = vSource;
				break;
			end
		end

		for xInput in ixmlelements(triangleData.xObj, "input") do
			if(semantic == xInput:GetPropVal("semantic", "")) then
				outputIndexOffset[semantic] = tonumber(xInput:GetPropVal("offset", ""));
			end
		end
	else
		print("Warning: semantic '" .. semantic ..
			"' does not have a map entry. It will not be written to the file.");
	end
end

--[[
Retrieves the basic data type and size of an attribute from the COLLADA doc.
Returns, in order:
* the MeshFormat "type"
* the MeshFormat "size", as an integer
* a Lua pattern string that returns a value. Suitable for use with string.gmatch
* the XML text node containing the array.
]]
local function ParseDataType(xSource)
	local typeMap = 
	{
		float_array = "float",
	}

	local retType = nil;
	local valueElem = nil;
	for colladaType, meshType in pairs(typeMap) do
		valueElem = findXmlChild(xSource, colladaType);
		if(valueElem) then
			retType = meshType;
			break;
		end
	end
	
	assert(retType, "Could not find the type for the 'source' named '" ..
		xSource:GetPropVal("id", "") .. "'.");
	
	local xTech = assert(findXmlChild(xSource, "technique_common"),
		"Malformed COLLADA: Missing 'technique_common' descriptor on 'source'.");

	local xAccess = assert(findXmlChild(xTech, "accessor"),
		"Malformed COLLADA: Missing 'technique_common' descriptor on 'source'.");

	local bHasProp, stride = xAccess:GetPropVal("stride");
	assert(bHasProp, "Malformed COLLADA: missing 'stride' on 'accessor'.");
	
	stride = tonumber(stride);
	
	return retType, stride, "([%+%-]?[%d%.]+e?[%+%-]?[%d%.]*)", valueElem:GetChildren();
end

local function WriteTextForArray(writer, valueArray, stride, indexList, indexOffset)
	writer:AddText("\n");
	
	for i=1, #indexList, triangleData.numInputs do
		writer:AddText("\t\t")
		local indexIx = i + indexOffset;
		local index = indexList[indexIx];
		index = index * stride;
		for j=1, stride do
			index = index + 1;	--One-base index.
			writer:AddText(valueArray[index], " ");
		end
		writer:AddText("\n");
	end
end

--Load the indices into Lua
local indexList = {}
local revIndices = {}
for index in triangleData.xIndices:GetContent():gmatch("(%d+)") do
	revIndices[#revIndices + 1] = tonumber(index);	--zero-base index
	
	--Reverse the winding order.
	if(#revIndices == triangleData.numInputs * 3) then
		for vertex=3, 1, -1 do
			for input=1, triangleData.numInputs do
				local index = (vertex-1) * triangleData.numInputs + input
				indexList[#indexList + 1] = revIndices[index];
			end
		end
	
		revIndices = {};
	end
end

assert(#revIndices == 0);

--Write the mesh.
local writer = XmlWriter.XmlWriter(options.outputFile);
writer:AddPI("oxygen", [[RNGSchema="../../Documents/meshFormat.rnc" type="compact"]]);
writer:PushElement("mesh", "http://www.arcsynthesis.com/gltut/mesh");

--Write the attributes, in order of their indices.
for semantic, source in pairs(outputMap) do
	writer:PushElement("attribute");
		writer:AddAttribute("index", tostring(options.map[semantic]));
		
		local meshType, stride, pttrn, valueText = ParseDataType(sources[source]);
		
		writer:AddAttribute("type", meshType);
		writer:AddAttribute("size", tostring(stride));
		
		local valueArray = {};
		local numberArray = {};
		for value in valueText:GetContent():gmatch(pttrn) do
			valueArray[#valueArray + 1] = value;
			numberArray[#numberArray + 1] = tostring(tonumber(value));
		end

		WriteTextForArray(writer, valueArray, stride, indexList, outputIndexOffset[semantic]);
	writer:PopElement();
end

--Write the VAOs
for vaoName, vao in pairs(options.vaos) do
	writer:PushElement("vao");
		writer:AddAttribute("name", vaoName);
		for i, attrib in ipairs(vao) do
			writer:PushElement("source");
				writer:AddAttribute("attrib", tostring(attrib));
			writer:PopElement();
		end
	writer:PopElement();
end

--Write the rendering command(s)
	writer:PushElement("arrays");
		writer:AddAttribute("cmd", "triangles");
		writer:AddAttribute("start", "0");
		local numTris = tonumber(triangleData.xObj:GetPropVal("count", ""));
		writer:AddAttribute("count", tostring(numTris * 3));
	writer:PopElement();

writer:PopElement();
writer:Close();

