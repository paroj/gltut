
dofile("../glsdk/links.lua")

local myPath = os.getcwd();
local usedLibs = {"glload", "glimage", "glm", "glutil", "glmesh", "freeglut"}

function SetupSolution(slnName)
	solution(slnName)
		configurations {"Debug", "Release"}
		defines {"_CRT_SECURE_NO_WARNINGS", "_CRT_SECURE_NO_DEPRECATE", "_SCL_SECURE_NO_WARNINGS", "TIXML_USE_STL"}
		defines {"FREEGLUT_STATIC"}
		
    	configuration "windows"
        	defines {"WIN32"}
        	
       	configuration "linux"
    	    defines {"LOAD_X11"}
		
	local currPath = os.getcwd();
	os.chdir(myPath);
		
	project "framework"
		kind "StaticLib"
		language "c++"
		
		files  "../framework/*.cpp"
		files  "../framework/*.h"
		excludes "../framework/empty.cpp"
		
		targetdir "../framework/lib"
		objdir "../framework/lib"

		includedirs {"../tinyxml", "../framework"}
		
		UseLibs(usedLibs)
		
		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags "Symbols"
			targetname("frameworkD")

		configuration "Release"
			defines {"RELEASE", "NDEBUG"};
			flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"};
			targetname("framework")


	os.chdir(currPath);
end

function SetupProject(projName, ...)
	project(projName)
		kind "ConsoleApp"
		language "c++"
		
		files {...}

		UseLibs(usedLibs)

		includedirs {"../tinyxml", "../framework"}
			
		links "framework"

		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags "Symbols"
			libdirs {"../tinyxml/lib"}
			links "tinyxml_pmD"
			targetname(projName .. "D")
		
		configuration "Release"
			defines {"RELEASE", "NDEBUG"};
			flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"};
			libdirs {"../tinyxml/lib"}
			links "tinyxml_pm"
			targetname(projName)

		configuration {"windows"}
			links {"glu32", "opengl32", "gdi32", "winmm", "user32"}

	    configuration "linux"
	        links {"GL", "GLU"}

end

