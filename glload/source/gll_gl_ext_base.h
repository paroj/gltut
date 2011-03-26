#ifndef GLL_GL_EXT_BASE_H
#define GLL_GL_EXT_BASE_H


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


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

#ifndef APIENTRY
	#define GLE_REMOVE_APIENTRY
	#if defined(__MINGW32__)
		#define APIENTRY __stdcall
	#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
		#define APIENTRY __stdcall
	#else
		#define APIENTRY
	#endif
#endif //APIENTRY

#ifdef GLE_FUNCPTR
#undef GLE_FUNCPTR
#endif //GLE_FUNCPTR

#if defined(_WIN32)
	#define GLE_FUNCPTR APIENTRY
#else
	#define GLE_FUNCPTR
#endif

#include <stddef.h>
#ifndef GL_VERSION_2_0
/* GL type for program/shader text */
typedef char GLchar;
#endif
#ifndef GL_VERSION_1_5
/* GL types for handling large vertex buffer objects */
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
#endif
#ifndef GL_ARB_vertex_buffer_object
/* GL types for handling large vertex buffer objects */
typedef ptrdiff_t GLintptrARB;
typedef ptrdiff_t GLsizeiptrARB;
#endif
#ifndef GL_ARB_shader_objects
/* GL types for program/shader text and shader object handles */
typedef char GLcharARB;
typedef unsigned int GLhandleARB;
#endif
/* GL type for "half" precision (s10e5) float data in host memory */
#ifndef GL_ARB_half_float_pixel
typedef unsigned short GLhalfARB;
#endif
#ifndef GL_NV_half_float
typedef unsigned short GLhalfNV;
#endif
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
#ifndef GL_EXT_timer_query
typedef int64_t GLint64EXT;
typedef uint64_t GLuint64EXT;
#endif
#ifndef GL_ARB_sync
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef struct __GLsync *GLsync;
#endif
#ifndef GL_ARB_cl_event
/* These incomplete types let us declare types compatible with OpenCL's cl_context and cl_event */
struct _cl_context;
struct _cl_event;
#endif
#ifndef GL_ARB_debug_output
typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,GLvoid *userParam);
#endif
#ifndef GL_AMD_debug_output
typedef void (APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,GLvoid *userParam);
#endif
#ifndef GL_NV_vdpau_interop
typedef GLintptr GLvdpauSurfaceNV;
#endif

#define GL_VERSION 0x1F02
#define GL_EXTENSIONS 0x1F03
#define GL_NUM_EXTENSIONS 0x821D
#define GL_CONTEXT_PROFILE_MASK 0x9126
#define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_TRUE 1
#define GL_FALSE 0

typedef const GLubyte * (GLE_FUNCPTR * PFNGLGETSTRINGPROC)(GLenum name);
extern PFNGLGETSTRINGPROC __gleGetString;
#define glGetString __gleGetString
typedef const GLubyte * (GLE_FUNCPTR * PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
extern PFNGLGETSTRINGIPROC __gleGetStringi;
#define glGetStringi __gleGetStringi
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERVPROC)(GLenum pname, GLint *params);
extern PFNGLGETINTEGERVPROC __gleGetIntegerv;
#define glGetIntegerv __gleGetIntegerv

void gleIntLoadBaseFuncs();

#ifdef GLE_REMOVE_APIENTRY
	#undef GLE_REMOVE_APIENTRY
	#undef APIENTRY
#endif //GLE_REMOVE_APIENTRY


#ifdef __cplusplus
}
#endif //__cplusplus


#endif //GLL_GL_EXT_BASE_H


