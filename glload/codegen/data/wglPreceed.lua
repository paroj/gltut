--[[This file returns a string that should be placed at the front of all
WGL headers.]]


return [[
#ifdef __wglext_h_
#error Attempt to include wgl_exts after including wglext.h
#endif

#define __wglext_h_
]]
