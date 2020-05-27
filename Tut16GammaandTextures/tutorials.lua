
SetupProject("Tut16GammaRamp", "GammaRamp.cpp",
	"data/screenCoords.vert",
	"data/textureGamma.frag", "data/textureNoGamma.frag")

SetupProject("Tut16GammaCheckers", "GammaCheckers.cpp",
	"data/PT.vert",
	"data/textureGamma.frag", "data/textureNoGamma.frag")

SetupProject("Tut16GammaLandscape",
	"GammaLandscape.cpp", "LightEnv.h", "LightEnv.cpp",
	"data/PNT.vert",
	"data/litGamma.frag", "data/litNoGamma.frag")
