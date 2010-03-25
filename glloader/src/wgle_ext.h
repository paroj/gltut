#ifndef WGLE_EXT_H
#define WGLE_EXT_H


#ifdef __wglext_h_
#error Attempt to include wgle after including wglext.h
#endif

#define __wglext_h_

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif //WIN32_LEAN_AND_MEAN

#include <windows.h>

#ifdef GLE_FUNCPTR
#undef GLE_FUNCPTR
#endif //GLE_FUNCPTR
#define GLE_FUNCPTR WINAPI

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

#ifndef WGL_ARB_pbuffer
DECLARE_HANDLE(HPBUFFERARB);
#endif
#ifndef WGL_EXT_pbuffer
DECLARE_HANDLE(HPBUFFEREXT);
#endif
#ifndef WGL_NV_present_video
DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
#endif
#ifndef WGL_NV_video_out
DECLARE_HANDLE(HPVIDEODEV);
#endif
#ifndef WGL_NV_gpu_affinity
DECLARE_HANDLE(HPGPUNV);
DECLARE_HANDLE(HGPUNV);
typedef struct _GPU_DEVICE {
    DWORD  cb;
    CHAR   DeviceName[32];
    CHAR   DeviceString[128];
    DWORD  Flags;
    RECT   rcVirtualScreen;
} GPU_DEVICE, *PGPU_DEVICE;
#endif

#include "gle_util.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus



extern StrToExtMap wgleIntExtensionMap[];
extern int wgleIntExtensionMapSize;

void wgleIntClear();



typedef const char * (GLE_FUNCPTR * PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
extern PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;

void wgleIntLoadBaseFuncs();

#ifdef __cplusplus
}
#endif //__cplusplus


#endif //WGLE_EXT_H

