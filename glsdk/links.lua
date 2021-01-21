local thisDirectory = os.getcwd();

local LibDeps = 
{
	glmesh = {"glload", "glm"},
	glutil = {"glm"},
}

local LinkFuncs =
{
	glload = function()
		includedirs "glload/include"
		libdirs "glload/lib"

		configuration "Debug"
			links {"glloadD"}

		configuration "Release"
			links {"glload"}
	end,
	glimage = function()
		includedirs "glimg/include"
		libdirs "glimg/lib"

		configuration "Debug"
			links {"glimgD"}

		configuration "Release"
			links {"glimg"}
	end,
	glutil = function()
		includedirs "glutil/include"
		libdirs "glutil/lib"

		configuration "Debug"
			links {"glutilD"}

		configuration "Release"
			links {"glutil"}
	end,
	glmesh = function()
		includedirs "glmesh/include"
		libdirs "glmesh/lib"

		configuration "Debug"
			links {"glmeshD"}

		configuration "Release"
			links {"glmesh"}
	end,
	glm = function()
		includedirs "glm"
	end,
	freeglut = function()
		includedirs "freeglut/include"
		libdirs "freeglut/lib"
		defines {"FREEGLUT_STATIC", "_LIB", "FREEGLUT_LIB_PRAGMAS=0"}
		
		configuration "Debug"
			links {"freeglutD"}
		
		configuration "Release"
			links {"freeglut"}
	end,
}

local InclFuncs =
{
	glload = function()
		includedirs "glload/include"
		libdirs "glload/lib"
	end,
	glimage = function()
		includedirs "glimg/include"
		libdirs "glimg/lib"
	end,
	glutil = function()
		includedirs "glutil/include"
		libdirs "glutil/lib"
	end,
	glmesh = function()
		includedirs "glmesh/include"
		libdirs "glmesh/lib"
	end,
	glm = function()
		includedirs "glm"
	end,
	freeglut = function()
		includedirs "freeglut/include"
		libdirs "freeglut/lib"
		defines {"FREEGLUT_STATIC", "_LIB", "FREEGLUT_LIB_PRAGMAS=0"}
	end,
}

local function ProcTable(tbl, libTbl)
	for i, lib in ipairs(tbl) do
		if(type(lib) == "string") then
			if(not libTbl[lib]) then
				print("Bad library named ", lib);
			else
				local prevDir = os.getcwd()
				os.chdir(thisDirectory)
				configuration {}

				libTbl[lib]()
				
				configuration {}
				os.chdir(prevDir)
			end
		elseif(type(lib) == "table") then
			ProcTable(lib, libTbl);
		end
	end
end

local function FlattenTable(tbl, ret)
	ret = ret or {}
	for _, entry in ipairs(tbl) do
		if(type(entry) == "table") then
			FlattenTable(entry, ret)
		else
			ret[#ret + 1] = entry
		end
	end
	return ret
end

local function FixupDependencies(libTbl)
	local libList = FlattenTable(libTbl)

	local current = {}
	for _, lib in ipairs(libList) do
		current[lib] = "find"
	end
	
	repeat
		local toAdd = {}
		for lib, deps in pairs(current) do
			if(deps == "find") then
				if(LibDeps[lib]) then
					for _, newLib in ipairs(LibDeps[lib]) do
						if(not current[newLib]) then
							toAdd[#toAdd + 1] = newLib
						end
					end
				end
				current[lib] = true
			end
		end
		
		for _, lib in ipairs(toAdd) do
			current[lib] = "find"
		end
	until (#toAdd == 0)
	
	local ret = {}
	for lib, _ in pairs(current) do
		ret[#ret + 1] = lib
	end
	
	return ret
end

function UseLibs(...)
	local libList = FixupDependencies {...}
	ProcTable(libList, LinkFuncs)
end

function InclLibs(...)
	local libList = FixupDependencies {...}
	ProcInclTable(libList, InclFuncs)
end
