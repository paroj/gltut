
solution "glloader"
	configurations {"Debug", "Release"}
	defines {"_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS", "WIN32"}

project "glloader"
	kind "StaticLib"
	language "c++"
	targetdir "lib"
	
	files "src/*.*"
	includedirs "./include"
	
	configuration "Debug"
		defines {"DEBUG", "_DEBUG"}
		flags "Symbols"
		targetname "glloaderD"
	
	configuration "Release"
		defines {"NDEBUG", "RELEASE"};
		targetname "glloader"
