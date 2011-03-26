--[[This file returns a string that should be placed at the front of all
GLX headers.]]


return [[
#ifdef __glxext_h_
#error Attempt to include glx_exts after including glxext.h
#endif

#define __glxext_h_
]]
