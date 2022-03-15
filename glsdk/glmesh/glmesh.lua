
project("glmesh")
	kind "StaticLib"
	language "c++"
	includedirs {"include", "source",
		"../glload/include", "../glutil/include", "../glm"}
	targetdir "lib"

	files {
		"include/glmesh/*.h",
		"source/*.cpp",
		"source/*.h",
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
		targetname "glmeshD";

	filter "configurations:Release"
		defines {"NDEBUG", "RELEASE"};
		characterset "Unicode";
		optimize "Speed";
		omitframepointer "On";
		warnings "Extra";
		editandcontinue "Off";
		objdir "Release";
		targetname "glmesh"
