--[[
Calling dofile on this will generate all of the header and source files needed
for GLE.
]]

require "_LoadLuaSpec";
require "_MakeExtHeaderFile";
require "_MakeMainHeaderFile";
require "_MakeMainSourceFile";
require "_MakeCoreHeaderFile";
require "_MakeCoreSourceFile";
require "_util";

local specFileLoc = GetSpecFilePath();



---------------------------
--Create standard OpenGL files.
local specData = LoadLuaSpec(specFileLoc .. "glspec.lua");
	
local glPreceedData = {
	dofile(GetDataFilePath() .. "headerGlProtect.lua"),
	dofile(GetDataFilePath() .. "glDefStr.lua"),
	dofile(GetDataFilePath() .. "headerFunc.lua"),
	footer = {
		dofile(GetDataFilePath() .. "footerFunc.lua"),
	},
}

--Write the external headers.
local glOutputs = {
	{"gl_2_1", "2.1", true},
	{"gl_3_0", "3.0", true},
	{"gl_3_1", "3.1", true},
	{"gl_3_1_comp", "3.1", false},
	{"gl_3_2", "3.2", true},
	{"gl_3_2_comp", "3.2", false},
	{"gl_3_3", "3.3", true},
	{"gl_3_3_comp", "3.3", false},
	{"gl_4_0", "4.0", true},
	{"gl_4_0_comp", "4.0", false},
	{"gl_4_1", "4.1", true},
	{"gl_4_1_comp", "4.1", false},
};

for i, output in ipairs(glOutputs) do
	MakeExtHeaderFile(output[1], specData, "GL", "gl",
		output[2], output[3], glPreceedData);
end

local function GetVersionProfIterator()
	local currIx = 1;
	
	return function()
		if(currIx > #glOutputs) then return nil, nil; end;
		
		local currValue = glOutputs[currIx];
		currIx = currIx + 1;
		local profile = nil;
		
		if(currValue[3]) then profile = "core"; else profile = "compatibility"; end;
		
		return currValue[2], profile;
	end
end

--Write the internal headers.
local baseData = {
	enums = {"VERSION", "EXTENSIONS", "NUM_EXTENSIONS", "CONTEXT_PROFILE_MASK", "CONTEXT_CORE_PROFILE_BIT", "CONTEXT_COMPATIBILITY_PROFILE_BIT", "TRUE", "FALSE"},
	
	funcs = {"GetString", "GetStringi", "GetIntegerv"},

	bFuncsAreCore = true,
	
	enumPrefix = "GL",
	
	preceedData = glPreceedData,
};

MakeMainHeaderFile("gll_gl_ext", specData, "gl", GetVersionProfIterator(), baseData);

MakeCoreHeaderFile("gll_gl_core", specData, "gl");

--Write the internal source files.

local platformDef = dofile(GetDataFilePath() .. "stdPlatformDef.lua");

MakeMainSourceFile("gll_gl_ext", specData, "GL", "gl", GetVersionProfIterator(), glPreceedData,
	baseData, {file = "gll_gl_core"});

MakeCoreSourceFile("gll_gl_core", specData, "gl", platformDef);

---------------------------
--Create WGL files.
local wglSpecData = LoadLuaSpec(specFileLoc .. "wglspec.lua");

local wglPreceedData = {
	dofile(GetDataFilePath() .. "wglPreceed.lua"),
	dofile(GetDataFilePath() .. "wglHeaderFunc.lua"),
	dofile(GetDataFilePath() .. "glDefStr.lua"),
}

local wglbaseData = {
	enums = {},
	funcs = {"GetExtensionsStringARB"},
	bFuncsAreCore = false,
	enumPrefix = "WGL",
	preceedData = wglPreceedData
};


MakeExtHeaderFile("wgl_exts", wglSpecData, "WGL", "wgl", nil, false, wglPreceedData);

MakeMainHeaderFile("wgll_ext", wglSpecData, "wgl", nil, wglbaseData);

MakeMainSourceFile("wgll_ext", wglSpecData, "WGL", "wgl", nil, wglPreceedData,
	wglbaseData, nil);
	
	
---------------------------
--Create GLX files.
local glxSpecData = LoadLuaSpec(specFileLoc .. "glxspec.lua");

local glxPreceedData = {
	dofile(GetDataFilePath() .. "glxPreceed.lua"),
	dofile(GetDataFilePath() .. "glxHeaderFunc.lua"),
	dofile(GetDataFilePath() .. "glDefStr.lua"),
}

MakeExtHeaderFile("glx_exts", glxSpecData, "GLX", "glX", nil, false, glxPreceedData);

MakeMainHeaderFile("glxl_ext", glxSpecData, "glX", nil, glxbaseData);

MakeMainSourceFile("glxl_ext", glxSpecData, "GLX", "glX", nil, glxPreceedData,
	glxbaseData, nil);
	
	
	
	
	
	
	
