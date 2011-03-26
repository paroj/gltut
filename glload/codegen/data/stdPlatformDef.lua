--[[
Returns a table that is compatible with the platformDef field of MakeCoreSourceFile. Used for building the standard GL version of this.
]]

return {
	{
		define = "WIN32",
		statements = {"#include<windows.h>", "#include <GL/gl.h>"},
		versions = {"1.0", "1.1"},
	},
};
