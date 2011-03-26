--This should be at the front of all the GLX files that use functions.

return [[
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#define GLE_FUNCPTR
]]
