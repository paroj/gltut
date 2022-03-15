
newoption {
	trigger			= "plainc",
	description		= "Set this to build GL Load without C++ support.",
}


project("glload")
	kind "StaticLib"
	includedirs {"include", "source"}
	targetdir "lib"

	if(_OPTIONS["plainc"]) then
		language "c"
	else
		language "c++"
	end

	files {
		"include/glload/gl_*.h",
		"include/glload/gl_*.hpp",
		"include/glload/gll.h",
		"include/glload/gll.hpp",
		"source/gl_*",
	};
	
	filter "configurations:plainc"
		excludes {
			"source/*.cpp",
			"include/glload/*.hpp",
		}
	
	filter "configurations:windows"
		defines {"WIN32"}
		files {"include/glload/wgl_*.h",}
		files {"source/wgl_*"}
	
	filter "configurations:linux"
	    defines {"LOAD_X11"}
		files {"include/glload/glx_*.h"}
		files {"source/glx_*"}

	filter "configurations:Debug"
		characterset "Unicode";
		defines {"DEBUG", "_DEBUG", "MEMORY_DEBUGGING"};
		objdir "Debug";
		symbols "On";
		targetname "glloadD";

	filter "configurations:Release"
		defines {"NDEBUG", "RELEASE"};
		characterset "Unicode";
		optimize "Speed";
		omitframepointer "On";
		warnings "Extra";
		editandcontinue "Off";
		objdir "Release";
		targetname "glload"
