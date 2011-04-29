--[[
Running this file will convert all of the current spec files into lua files.

The lua files can have dofile run on them; this will return a table as formatted in
ExtractSpecsToFile.lua.
]]

require "_ExtractSpecsToFile"

ExtractSpecsToFile("glspec.lua", {
	glspec = "gl.spec",
	enumext = "enumext.spec",
	gltm = "gl.tm"
	})

ExtractSpecsToFile("wglspec.lua", {
	glspec = "wglext.spec",
	enumext = "wglenumext.spec",
	gltm = "wgl.tm"
	},
	"WGL")

ExtractSpecsToFile("glxspec.lua", {
	glspec = "glxext.spec",
	enumext = "glxenumext.spec",
	gltm = "glx.tm"
	})

