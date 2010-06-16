
dofile("../framework/framework.lua")

SetupSolution("Tutorial5")
SetupProject("Overlap No Depth", "OverlapNoDepth.cpp",
	"data/Standard.frag", "data/Standard.vert")
SetupProject("Base Vertex with Overlap", "BaseVertexOverlap.cpp",
	"data/Standard.frag", "data/Standard.vert")
SetupProject("Depth Buffering", "DepthBuffer.cpp",
	"data/Standard.frag", "data/Standard.vert")
SetupProject("Vertex Clipping", "VertexClipping.cpp",
	"data/Standard.frag", "data/Standard.vert")
SetupProject("Depth Clamping", "DepthClamping.cpp",
	"data/Standard.frag", "data/Standard.vert")
