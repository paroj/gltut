if(_ACTION == "gmake") then
	if(os.target() == "linux" or os.target() == "bsd") then
		os.execute("sh ./configure");
	end
end

project "freeglut"
	kind "StaticLib"
	language "c"
	includedirs {"include"}
	targetdir "lib"
	files {"src/*.c"};
	
	defines {"FREEGLUT_STATIC", "_LIB", "FREEGLUT_LIB_PRAGMAS=0"}
	
	filter "configurations:windows"
		defines "WIN32"

	filter {"configurations:gmake", "configurations:linux or bsd"}
        defines {"HAVE_CONFIG_H", }
        includedirs {"."}

	filter {"configurations:linux or bsd"}
        defines {"HAVE_CONFIG_H", }
        includedirs {"."}
		
	filter "configurations:Debug"
		targetsuffix "D"
		defines "_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG";
		optimize "Speed";
		omitframepointer "On";
		warnings "Extra";
		editandcontinue "Off";
