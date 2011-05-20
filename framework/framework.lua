
local myPath = os.getcwd();

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

		includedirs {"../freeglut-2.6.0/include", "../glload/include",
			"../glimg/include", "../glm-0.9.0.7", "../tinyxml",
			"../framework"}
		
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

		includedirs {"../freeglut-2.6.0/include", "../glload/include",
			"../glimg/include", "../glm-0.9.0.7", "../tinyxml"}
			
		links "framework"

		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags "Symbols"
			libdirs {"../glload/lib", "../glimg/lib", "../tinyxml/lib"}
			links "glloadD"
			links "glimgD"
			links "tinyxml_pmD"
			targetname(projName .. "D")
		
		configuration "Release"
			defines {"RELEASE", "NDEBUG"};
			libdirs {"../glload/lib", "../glimg/lib", "../tinyxml/lib"}
			links "glload"
			links "glimg"
			links "tinyxml_pm"
			targetname(projName)


        configuration {"Debug", "windows"}
			links "../freeglut-2.6.0/VisualStudio2008Static/debug/freeglut_static"
        configuration {"Release", "windows"}
			links "../freeglut-2.6.0/VisualStudio2008Static/release/freeglut_static"
        configuration {"linux"}
            libdirs {"../freeglut-2.6.0/src/.libs"}
			links "glut"
end

