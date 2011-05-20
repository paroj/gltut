
project("glload")
	kind "StaticLib"
	language "c++"
	includedirs {"include", "source"}
	targetdir "lib"

	files {
		"include/glload/gl_*.h",
		"include/glload/gll.h",
		"source/gll*.c",
		"source/gll*.cpp",
		"source/gll*.h",
	};
	
	configuration "windows"
		defines {"WIN32"}
		files {"include/glload/wgl_*.h",}
		files {"source/wgll*.c",
			"source/wgll*.cpp",
			"source/wgll*.h",}
	
	configuration "linux"
	    defines {"LOAD_X11"}
		files {"include/glload/glx_*.h"}
		files {"source/glxl*.c",
			"source/glxl*.cpp",
			"source/glxl*.h",}

	configuration "Debug"
		flags "Unicode";
		defines {"DEBUG", "_DEBUG", "MEMORY_DEBUGGING"};
		objdir "Debug";
		flags "Symbols";
		targetname "glloadD";

	configuration "Release"
		defines {"NDEBUG", "RELEASE"};
		flags "Unicode";
		flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"};
		objdir "Release";
		targetname "glload"
