
solution "tinyxml_pm"
	configurations {"Debug", "Release"}
	defines {"_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS", "WIN32", "TIXML_USE_STL"}

project "tinyxml_pm"
	kind "StaticLib"
	language "c++"
	targetdir "lib"
	
	files
	{
		"tinyxml.cpp",
		"tinyxmlerror.cpp",
		"tinyxmlparser.cpp",
		"tinystr.cpp",
	}
	
	configuration "Debug"
		defines {"DEBUG", "_DEBUG"}
		flags "Symbols"
		targetname "tinyxml_pmD"
	
	configuration "Release"
		defines {"NDEBUG", "RELEASE"};
		targetname "tinyxml_pm"
