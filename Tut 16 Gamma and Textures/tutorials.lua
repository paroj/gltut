
SetupProject("Tut 16 Gamma Ramp", "GammaRamp.cpp",
	"data/screenCoords.vert",
	"data/textureGamma.frag", "data/textureNoGamma.frag")

SetupProject("Tut 16 Gamma Checkers", "Gamma Checkers.cpp",
	"data/PT.vert",
	"data/textureGamma.frag", "data/textureNoGamma.frag")

SetupProject("Tut 16 Gamma Landscape",
	"Gamma Landscape.cpp", "LightEnv.h", "LightEnv.cpp",
	"data/PNT.vert",
	"data/litGamma.frag", "data/litNoGamma.frag")
