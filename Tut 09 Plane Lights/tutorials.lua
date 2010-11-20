
SetupProject("Tut 09 Vertex Directional Lighting", "Vertex Directional Lighting.cpp",
	"data/PosVertexLighting_PCN.vert",
	"data/PosVertexLighting_PN.vert",
	"data/PosTransform.vert",
	"data/UniformColor.frag",
	"data/ColorPassthrough.frag")

SetupProject("Tut 09 Perspective Interpolation", "Perspective Interpolation.cpp",
	"data/SmoothVertexColors.vert",
	"data/SmoothVertexColors.frag",
	"data/NoCorrectVertexColors.vert",
	"data/NoCorrectVertexColors.frag")

SetupProject("Tut 09 Fragment Directional Lighting", "Fragment Directional Lighting.cpp",
	"data/ModelPosVertexLighting_PCN.vert",
	"data/ModelPosVertexLighting_PN.vert",
	"data/ColorPassthrough.frag",
	"data/FragmentLighting_PCN.vert",
	"data/FragmentLighting_PN.vert",
	"data/FragmentLighting.frag")

