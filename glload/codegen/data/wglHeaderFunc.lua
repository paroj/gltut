--This should be at the front of all the WGL files that use functions.

return [[
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif //WIN32_LEAN_AND_MEAN

#include <windows.h>

#ifdef GLE_FUNCPTR
#undef GLE_FUNCPTR
#endif //GLE_FUNCPTR
#define GLE_FUNCPTR WINAPI
]]