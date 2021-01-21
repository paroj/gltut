
project("glutil")
	kind "StaticLib"
	language "c++"
	includedirs {"include", "source",
		"../glload/include", "../glm"}
	targetdir "lib"

	files {
		"include/glutil/*.h",
		"source/*.cpp",
		"source/*.h",
	};
	
	configuration "windows"
		defines {"WIN32"}
	
	configuration "linux"
	    defines {"LOAD_X11"}

	configuration "Debug"
		flags "Unicode";
		defines {"DEBUG", "_DEBUG", "MEMORY_DEBUGGING"};
		objdir "Debug";
		flags "Symbols";
		targetname "glutilD";

	configuration "Release"
		defines {"NDEBUG", "RELEASE"};
		flags "Unicode";
		flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"};
		objdir "Release";
		targetname "glutil"
