
local myPath = os.getcwd();

function SetupSolution(slnName)
	solution(slnName)
		configurations {"Debug", "Release"}
		defines {"_CRT_SECURE_NO_WARNINGS", "_CRT_SECURE_NO_DEPRECATE", "_SCL_SECURE_NO_WARNINGS", "TIXML_USE_STL"}
		defines {"FREEGLUT_STATIC", "WIN32"}
		
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

		includedirs {"../freeglut-2.6.0/include", "../glloader/include",
			"../FreeImage/dist", "../glm-0.9.0.7", "../tinyxml", "../framework"}
		
		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags "Symbols"
			targetname("frameworkD")

		configuration "Release"
			defines {"RELEASE", "NDEBUG"};
			targetname("framework")

	os.chdir(currPath);
end

function SetupProject(projName, ...)
	project(projName)
		kind "ConsoleApp"
		language "c++"
		
		files {...}
		targetdir "bin"

		includedirs {"../freeglut-2.6.0/include", "../glloader/include",
			"../FreeImage/dist", "../glm-0.9.0.7", "../tinyxml"}
			
		links "framework"

		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags "Symbols"
			links "../freeglut-2.6.0/VisualStudio2008Static/debug/freeglut_static"
			links "../FreeImage/dist/FreeImageD"
			links "../glloader/lib/glloaderD"
			links "../tinyxml/lib/tinyxml_pmD"
			targetname(projName .. "D")
		
		configuration "Release"
			defines {"RELEASE", "NDEBUG"};
			links "../freeglut-2.6.0/VisualStudio2008Static/release/freeglut_static"
			links "../FreeImage/dist/FreeImage"
			links "../glloader/lib/glloader"
			links "../tinyxml/lib/tinyxml_pm"
			targetname(projName)
end

