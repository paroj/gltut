
dofile("../framework/framework.lua")

SetupSolution("Tutorial2")
SetupProject("Fragment Position", "FragPosition.cpp",
	"data/FragPosition.frag", "data/FragPosition.vert")
	
SetupProject("Vertex Colors", "VertexColors.cpp",
	"data/VertexColors.frag", "data/VertexColors.vert")
