SetupProject("Tut14BasicTexture", "BasicTexture.cpp",
	"data/PN.vert",
	"data/ShaderGaussian.frag",
	"data/TextureGaussian.frag")

SetupProject("Tut14PerspectiveInterpolation", "PerspectiveInterpolation.cpp",
	"data/SmoothVertexColors.vert",
	"data/SmoothVertexColors.frag",
	"data/NoCorrectVertexColors.vert",
	"data/NoCorrectVertexColors.frag")

SetupProject("Tut14MaterialTexture", "MaterialTexture.cpp",
	"data/PN.vert",
	"data/PNT.vert",
	"data/FixedShininess.frag",
	"data/TextureShininess.frag",
	"data/TextureCompute.frag")
	