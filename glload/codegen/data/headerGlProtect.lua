--[[
The returned string protects against the accidental inclusion of other GL headers.
]]

return [[
#if defined(__gl_h_) || defined(__GL_H__)
#error Attempt to include gle after including gl.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error Attempt to include gle after including glext.h
#endif
#if defined(__gl_ATI_h_)
#error Attempt to include gle after including glATI.h
#endif

#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gl_ATI_h_

]]