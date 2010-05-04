
dofile("../framework/framework.lua")

SetupSolution("Tutorial4")
SetupProject("Orthographic Cube", "OrthoCube.cpp",
	"data/StandardColors.frag", "data/OrthoWithOffset.vert")
SetupProject("ShaderPerspective", "ShaderPerspective.cpp",
	"data/StandardColors.frag", "data/ManualPerspective.vert")
SetupProject("MatrixPerspective", "MatrixPerspective.cpp",
	"data/StandardColors.frag", "data/MatrixPerspective.vert")
SetupProject("AspectRatio", "AspectRatio.cpp",
	"data/StandardColors.frag", "data/MatrixPerspective.vert")
