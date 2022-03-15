
project("glimg")
	kind "StaticLib"
	language "c++"
	includedirs {"include", "source", "../glload/include"}
	targetdir "lib"

	files {
		"include/glimg/*.h",
		"source/*.h",
		"source/*.cpp",
		"source/*.c",
		"source/*.inc",
	};

	filter "configurations:windows"
		defines {"WIN32"}
	
	filter "configurations:linux"
	    defines {"LOAD_X11"}

	filter "configurations:Debug"
		characterset "Unicode";
		defines {"DEBUG", "_DEBUG", "MEMORY_DEBUGGING"};
		objdir "Debug";
		symbols "On";
		targetname "glimgD";

	filter "configurations:Release"
		defines {"NDEBUG", "RELEASE"};
		characterset "Unicode";
		optimize "Speed";
		omitframepointer "On";
		warnings "Extra";
		editandcontinue "Off";
		objdir "Release";
		targetname "glimg"
