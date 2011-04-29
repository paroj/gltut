#include <stdlib.h>
#include <string.h>
#include "glxl_ext.h"

#ifdef __glxext_h_
#error Attempt to include glx_exts after including glxext.h
#endif

#define __glxext_h_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#define GLE_FUNCPTR

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

#include <stddef.h>	
	
static int TestPointer(const void *pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;
	
	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
	
	return 1;
}

#ifndef GLX_ARB_get_proc_address
typedef void (*__GLXextFuncPtr)(void);
#endif
#ifndef GLX_SGIX_video_source
typedef XID GLXVideoSourceSGIX;
#endif
#ifndef GLX_SGIX_fbconfig
typedef XID GLXFBConfigIDSGIX;
typedef struct __GLXFBConfigRec *GLXFBConfigSGIX;
#endif
#ifndef GLX_SGIX_pbuffer
typedef XID GLXPbufferSGIX;
typedef struct {
    int type;
    unsigned long serial;	  /* # of last request processed by server */
    Bool send_event;		  /* true if this came for SendEvent request */
    Display *display;		  /* display the event was read from */
    GLXDrawable drawable;	  /* i.d. of Drawable */
    int event_type;		  /* GLX_DAMAGED_SGIX or GLX_SAVED_SGIX */
    int draw_type;		  /* GLX_WINDOW_SGIX or GLX_PBUFFER_SGIX */
    unsigned int mask;	  /* mask indicating which buffers are affected*/
    int x, y;
    int width, height;
    int count;		  /* if nonzero, at least this many more */
} GLXBufferClobberEventSGIX;
#endif
#ifndef GLX_NV_video_output
typedef unsigned int GLXVideoDeviceNV;
#endif
#ifndef GLX_NV_video_capture
typedef XID GLXVideoCaptureDeviceNV;
#endif
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GLX_OML_sync_control extension). */
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
#include <inttypes.h>     /* Fallback option */
#endif
#endif

#if defined(__APPLE__)
#include <mach-o/dyld.h>

void* AppleGLGetProcAddress (const GLubyte *name)
{
  static const struct mach_header* image = NULL;
  NSSymbol symbol;
  char* symbolName;
  if (NULL == image)
  {
    image = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
  }
  /* prepend a '_' for the Unix C symbol mangling convention */
  symbolName = malloc(strlen((const char*)name) + 2);
  strcpy(symbolName+1, (const char*)name);
  symbolName[0] = '_';
  symbol = NULL;
  /* if (NSIsSymbolNameDefined(symbolName))
	 symbol = NSLookupAndBindSymbol(symbolName); */
  symbol = image ? NSLookupSymbolInImage(image, symbolName, NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR) : NULL;
  free(symbolName);
  return symbol ? NSAddressOfSymbol(symbol) : NULL;
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>

void* SunGetProcAddress (const GLubyte* name)
{
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void*(*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif //WIN32_LEAN_AND_MEAN
	#include <windows.h>
	
	#define gleIntGetProcAddress(name) wglGetProcAddress((LPCSTR)name)
#else
	#if defined(__APPLE__)
		#define gleIntGetProcAddress(name) AppleGLGetProcAddress(name)
	#else
		#if defined(__sgi) || defined(__sun)
			#define gleIntGetProcAddress(name) SunGetProcAddress(name)
		#else /* GLX */
		    #include <GL/glx.h>

			#define gleIntGetProcAddress(name) (*glXGetProcAddressARB)(name)
		#endif
	#endif
#endif

int glXext_ARB_get_proc_address = 0;
int glXext_ARB_multisample = 0;
int glXext_ARB_vertex_buffer_object = 0;
int glXext_ARB_fbconfig_float = 0;
int glXext_ARB_framebuffer_sRGB = 0;
int glXext_ARB_create_context = 0;
int glXext_ARB_create_context_profile = 0;
int glXext_ARB_create_context_robustness = 0;
int glXext_SGIS_multisample = 0;
int glXext_EXT_visual_info = 0;
int glXext_SGI_swap_control = 0;
int glXext_SGI_video_sync = 0;
int glXext_SGI_make_current_read = 0;
int glXext_EXT_visual_rating = 0;
int glXext_EXT_import_context = 0;
int glXext_SGIX_fbconfig = 0;
int glXext_SGIX_pbuffer = 0;
int glXext_SGI_cushion = 0;
int glXext_SGIX_video_resize = 0;
int glXext_SGIX_swap_group = 0;
int glXext_SGIX_swap_barrier = 0;
int glXext_SGIS_blended_overlay = 0;
int glXext_SGIS_shared_multisample = 0;
int glXext_SUN_get_transparent_index = 0;
int glXext_3DFX_multisample = 0;
int glXext_MESA_copy_sub_buffer = 0;
int glXext_MESA_pixmap_colormap = 0;
int glXext_MESA_release_buffers = 0;
int glXext_MESA_set_3dfx_mode = 0;
int glXext_SGIX_visual_select_group = 0;
int glXext_OML_swap_method = 0;
int glXext_OML_sync_control = 0;
int glXext_NV_float_buffer = 0;
int glXext_MESA_agp_offset = 0;
int glXext_EXT_fbconfig_packed_float = 0;
int glXext_EXT_framebuffer_sRGB = 0;
int glXext_EXT_texture_from_pixmap = 0;
int glXext_NV_present_video = 0;
int glXext_NV_video_out = 0;
int glXext_NV_swap_group = 0;
int glXext_NV_video_capture = 0;
int glXext_EXT_swap_control = 0;
int glXext_NV_copy_image = 0;
int glXext_INTEL_swap_event = 0;
int glXext_NV_multisample_coverage = 0;
int glXext_AMD_gpu_association = 0;
int glXext_EXT_create_context_es2_profile = 0;


void glXeIntClear()
{
	glXext_ARB_get_proc_address = 0;
	glXext_ARB_multisample = 0;
	glXext_ARB_vertex_buffer_object = 0;
	glXext_ARB_fbconfig_float = 0;
	glXext_ARB_framebuffer_sRGB = 0;
	glXext_ARB_create_context = 0;
	glXext_ARB_create_context_profile = 0;
	glXext_ARB_create_context_robustness = 0;
	glXext_SGIS_multisample = 0;
	glXext_EXT_visual_info = 0;
	glXext_SGI_swap_control = 0;
	glXext_SGI_video_sync = 0;
	glXext_SGI_make_current_read = 0;
	glXext_EXT_visual_rating = 0;
	glXext_EXT_import_context = 0;
	glXext_SGIX_fbconfig = 0;
	glXext_SGIX_pbuffer = 0;
	glXext_SGI_cushion = 0;
	glXext_SGIX_video_resize = 0;
	glXext_SGIX_swap_group = 0;
	glXext_SGIX_swap_barrier = 0;
	glXext_SGIS_blended_overlay = 0;
	glXext_SGIS_shared_multisample = 0;
	glXext_SUN_get_transparent_index = 0;
	glXext_3DFX_multisample = 0;
	glXext_MESA_copy_sub_buffer = 0;
	glXext_MESA_pixmap_colormap = 0;
	glXext_MESA_release_buffers = 0;
	glXext_MESA_set_3dfx_mode = 0;
	glXext_SGIX_visual_select_group = 0;
	glXext_OML_swap_method = 0;
	glXext_OML_sync_control = 0;
	glXext_NV_float_buffer = 0;
	glXext_MESA_agp_offset = 0;
	glXext_EXT_fbconfig_packed_float = 0;
	glXext_EXT_framebuffer_sRGB = 0;
	glXext_EXT_texture_from_pixmap = 0;
	glXext_NV_present_video = 0;
	glXext_NV_video_out = 0;
	glXext_NV_swap_group = 0;
	glXext_NV_video_capture = 0;
	glXext_EXT_swap_control = 0;
	glXext_NV_copy_image = 0;
	glXext_INTEL_swap_event = 0;
	glXext_NV_multisample_coverage = 0;
	glXext_AMD_gpu_association = 0;
	glXext_EXT_create_context_es2_profile = 0;
}




#ifndef GLX_ARB_create_context
typedef GLXContext (GLE_FUNCPTR * PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);

PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
#endif /*GLX_ARB_create_context*/

static int glXeIntLoad_ARB_create_context()
{
	int bIsLoaded = 1;
#ifndef GLX_ARB_create_context
	glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)gleIntGetProcAddress("glXCreateContextAttribsARB");
	if(!TestPointer((const void*)glXCreateContextAttribsARB)) bIsLoaded = 0;
#endif /*GLX_ARB_create_context*/
	return bIsLoaded;
}




#ifndef GLX_ARB_get_proc_address
typedef __GLXextFuncPtr (GLE_FUNCPTR * PFNGLXGETPROCADDRESSARBPROC)(const GLubyte *procName);

PFNGLXGETPROCADDRESSARBPROC glXGetProcAddressARB;
#endif /*GLX_ARB_get_proc_address*/

static int glXeIntLoad_ARB_get_proc_address()
{
	int bIsLoaded = 1;
#ifndef GLX_ARB_get_proc_address
	glXGetProcAddressARB = (PFNGLXGETPROCADDRESSARBPROC)gleIntGetProcAddress("glXGetProcAddressARB");
	if(!TestPointer((const void*)glXGetProcAddressARB)) bIsLoaded = 0;
#endif /*GLX_ARB_get_proc_address*/
	return bIsLoaded;
}





#ifndef GLX_EXT_import_context
typedef Display * (GLE_FUNCPTR * PFNGLXGETCURRENTDISPLAYEXTPROC)();
typedef int (GLE_FUNCPTR * PFNGLXQUERYCONTEXTINFOEXTPROC)(Display *dpy, GLXContext context, int attribute, int *value);
typedef GLXContextID (GLE_FUNCPTR * PFNGLXGETCONTEXTIDEXTPROC)(const GLXContext context);
typedef GLXContext (GLE_FUNCPTR * PFNGLXIMPORTCONTEXTEXTPROC)(Display *dpy, GLXContextID contextID);
typedef void (GLE_FUNCPTR * PFNGLXFREECONTEXTEXTPROC)(Display *dpy, GLXContext context);

PFNGLXGETCURRENTDISPLAYEXTPROC glXGetCurrentDisplayEXT;
PFNGLXQUERYCONTEXTINFOEXTPROC glXQueryContextInfoEXT;
PFNGLXGETCONTEXTIDEXTPROC glXGetContextIDEXT;
PFNGLXIMPORTCONTEXTEXTPROC glXImportContextEXT;
PFNGLXFREECONTEXTEXTPROC glXFreeContextEXT;
#endif /*GLX_EXT_import_context*/

static int glXeIntLoad_EXT_import_context()
{
	int bIsLoaded = 1;
#ifndef GLX_EXT_import_context
	glXGetCurrentDisplayEXT = (PFNGLXGETCURRENTDISPLAYEXTPROC)gleIntGetProcAddress("glXGetCurrentDisplayEXT");
	if(!TestPointer((const void*)glXGetCurrentDisplayEXT)) bIsLoaded = 0;
	glXQueryContextInfoEXT = (PFNGLXQUERYCONTEXTINFOEXTPROC)gleIntGetProcAddress("glXQueryContextInfoEXT");
	if(!TestPointer((const void*)glXQueryContextInfoEXT)) bIsLoaded = 0;
	glXGetContextIDEXT = (PFNGLXGETCONTEXTIDEXTPROC)gleIntGetProcAddress("glXGetContextIDEXT");
	if(!TestPointer((const void*)glXGetContextIDEXT)) bIsLoaded = 0;
	glXImportContextEXT = (PFNGLXIMPORTCONTEXTEXTPROC)gleIntGetProcAddress("glXImportContextEXT");
	if(!TestPointer((const void*)glXImportContextEXT)) bIsLoaded = 0;
	glXFreeContextEXT = (PFNGLXFREECONTEXTEXTPROC)gleIntGetProcAddress("glXFreeContextEXT");
	if(!TestPointer((const void*)glXFreeContextEXT)) bIsLoaded = 0;
#endif /*GLX_EXT_import_context*/
	return bIsLoaded;
}
#ifndef GLX_EXT_swap_control
typedef int (GLE_FUNCPTR * PFNGLXSWAPINTERVALEXTPROC)(Display *dpy, GLXDrawable drawable, int interval);

PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT;
#endif /*GLX_EXT_swap_control*/

static int glXeIntLoad_EXT_swap_control()
{
	int bIsLoaded = 1;
#ifndef GLX_EXT_swap_control
	glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)gleIntGetProcAddress("glXSwapIntervalEXT");
	if(!TestPointer((const void*)glXSwapIntervalEXT)) bIsLoaded = 0;
#endif /*GLX_EXT_swap_control*/
	return bIsLoaded;
}
#ifndef GLX_EXT_texture_from_pixmap
typedef void (GLE_FUNCPTR * PFNGLXBINDTEXIMAGEEXTPROC)(Display *dpy, GLXDrawable drawable, int buffer, const int *attrib_list);
typedef void (GLE_FUNCPTR * PFNGLXRELEASETEXIMAGEEXTPROC)(Display *dpy, GLXDrawable drawable, int buffer);

PFNGLXBINDTEXIMAGEEXTPROC glXBindTexImageEXT;
PFNGLXRELEASETEXIMAGEEXTPROC glXReleaseTexImageEXT;
#endif /*GLX_EXT_texture_from_pixmap*/

static int glXeIntLoad_EXT_texture_from_pixmap()
{
	int bIsLoaded = 1;
#ifndef GLX_EXT_texture_from_pixmap
	glXBindTexImageEXT = (PFNGLXBINDTEXIMAGEEXTPROC)gleIntGetProcAddress("glXBindTexImageEXT");
	if(!TestPointer((const void*)glXBindTexImageEXT)) bIsLoaded = 0;
	glXReleaseTexImageEXT = (PFNGLXRELEASETEXIMAGEEXTPROC)gleIntGetProcAddress("glXReleaseTexImageEXT");
	if(!TestPointer((const void*)glXReleaseTexImageEXT)) bIsLoaded = 0;
#endif /*GLX_EXT_texture_from_pixmap*/
	return bIsLoaded;
}



#ifndef GLX_MESA_agp_offset
typedef unsigned int (GLE_FUNCPTR * PFNGLXGETAGPOFFSETMESAPROC)(const void *pointer);

PFNGLXGETAGPOFFSETMESAPROC glXGetAGPOffsetMESA;
#endif /*GLX_MESA_agp_offset*/

static int glXeIntLoad_MESA_agp_offset()
{
	int bIsLoaded = 1;
#ifndef GLX_MESA_agp_offset
	glXGetAGPOffsetMESA = (PFNGLXGETAGPOFFSETMESAPROC)gleIntGetProcAddress("glXGetAGPOffsetMESA");
	if(!TestPointer((const void*)glXGetAGPOffsetMESA)) bIsLoaded = 0;
#endif /*GLX_MESA_agp_offset*/
	return bIsLoaded;
}
#ifndef GLX_MESA_copy_sub_buffer
typedef void (GLE_FUNCPTR * PFNGLXCOPYSUBBUFFERMESAPROC)(Display *dpy, GLXDrawable drawable, int x, int y, int width, int height);

PFNGLXCOPYSUBBUFFERMESAPROC glXCopySubBufferMESA;
#endif /*GLX_MESA_copy_sub_buffer*/

static int glXeIntLoad_MESA_copy_sub_buffer()
{
	int bIsLoaded = 1;
#ifndef GLX_MESA_copy_sub_buffer
	glXCopySubBufferMESA = (PFNGLXCOPYSUBBUFFERMESAPROC)gleIntGetProcAddress("glXCopySubBufferMESA");
	if(!TestPointer((const void*)glXCopySubBufferMESA)) bIsLoaded = 0;
#endif /*GLX_MESA_copy_sub_buffer*/
	return bIsLoaded;
}
#ifndef GLX_MESA_pixmap_colormap
typedef GLXPixmap (GLE_FUNCPTR * PFNGLXCREATEGLXPIXMAPMESAPROC)(Display *dpy, XVisualInfo *visual, Pixmap pixmap, Colormap cmap);

PFNGLXCREATEGLXPIXMAPMESAPROC glXCreateGLXPixmapMESA;
#endif /*GLX_MESA_pixmap_colormap*/

static int glXeIntLoad_MESA_pixmap_colormap()
{
	int bIsLoaded = 1;
#ifndef GLX_MESA_pixmap_colormap
	glXCreateGLXPixmapMESA = (PFNGLXCREATEGLXPIXMAPMESAPROC)gleIntGetProcAddress("glXCreateGLXPixmapMESA");
	if(!TestPointer((const void*)glXCreateGLXPixmapMESA)) bIsLoaded = 0;
#endif /*GLX_MESA_pixmap_colormap*/
	return bIsLoaded;
}
#ifndef GLX_MESA_release_buffers
typedef Bool (GLE_FUNCPTR * PFNGLXRELEASEBUFFERSMESAPROC)(Display *dpy, GLXDrawable drawable);

PFNGLXRELEASEBUFFERSMESAPROC glXReleaseBuffersMESA;
#endif /*GLX_MESA_release_buffers*/

static int glXeIntLoad_MESA_release_buffers()
{
	int bIsLoaded = 1;
#ifndef GLX_MESA_release_buffers
	glXReleaseBuffersMESA = (PFNGLXRELEASEBUFFERSMESAPROC)gleIntGetProcAddress("glXReleaseBuffersMESA");
	if(!TestPointer((const void*)glXReleaseBuffersMESA)) bIsLoaded = 0;
#endif /*GLX_MESA_release_buffers*/
	return bIsLoaded;
}
#ifndef GLX_MESA_set_3dfx_mode
typedef Bool (GLE_FUNCPTR * PFNGLXSET3DFXMODEMESAPROC)(int mode);

PFNGLXSET3DFXMODEMESAPROC glXSet3DfxModeMESA;
#endif /*GLX_MESA_set_3dfx_mode*/

static int glXeIntLoad_MESA_set_3dfx_mode()
{
	int bIsLoaded = 1;
#ifndef GLX_MESA_set_3dfx_mode
	glXSet3DfxModeMESA = (PFNGLXSET3DFXMODEMESAPROC)gleIntGetProcAddress("glXSet3DfxModeMESA");
	if(!TestPointer((const void*)glXSet3DfxModeMESA)) bIsLoaded = 0;
#endif /*GLX_MESA_set_3dfx_mode*/
	return bIsLoaded;
}
#ifndef GLX_NV_copy_image
typedef void (GLE_FUNCPTR * PFNGLXCOPYIMAGESUBDATANVPROC)(Display *dpy, GLXContext srcCtx, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLXContext dstCtx, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);

PFNGLXCOPYIMAGESUBDATANVPROC glXCopyImageSubDataNV;
#endif /*GLX_NV_copy_image*/

static int glXeIntLoad_NV_copy_image()
{
	int bIsLoaded = 1;
#ifndef GLX_NV_copy_image
	glXCopyImageSubDataNV = (PFNGLXCOPYIMAGESUBDATANVPROC)gleIntGetProcAddress("glXCopyImageSubDataNV");
	if(!TestPointer((const void*)glXCopyImageSubDataNV)) bIsLoaded = 0;
#endif /*GLX_NV_copy_image*/
	return bIsLoaded;
}


#ifndef GLX_NV_present_video
typedef unsigned int * (GLE_FUNCPTR * PFNGLXENUMERATEVIDEODEVICESNVPROC)(Display *dpy, int screen, int *nelements);
typedef int (GLE_FUNCPTR * PFNGLXBINDVIDEODEVICENVPROC)(Display *dpy, unsigned int video_slot, unsigned int video_device, const int *attrib_list);

PFNGLXENUMERATEVIDEODEVICESNVPROC glXEnumerateVideoDevicesNV;
PFNGLXBINDVIDEODEVICENVPROC glXBindVideoDeviceNV;
#endif /*GLX_NV_present_video*/

static int glXeIntLoad_NV_present_video()
{
	int bIsLoaded = 1;
#ifndef GLX_NV_present_video
	glXEnumerateVideoDevicesNV = (PFNGLXENUMERATEVIDEODEVICESNVPROC)gleIntGetProcAddress("glXEnumerateVideoDevicesNV");
	if(!TestPointer((const void*)glXEnumerateVideoDevicesNV)) bIsLoaded = 0;
	glXBindVideoDeviceNV = (PFNGLXBINDVIDEODEVICENVPROC)gleIntGetProcAddress("glXBindVideoDeviceNV");
	if(!TestPointer((const void*)glXBindVideoDeviceNV)) bIsLoaded = 0;
#endif /*GLX_NV_present_video*/
	return bIsLoaded;
}
#ifndef GLX_NV_swap_group
typedef Bool (GLE_FUNCPTR * PFNGLXJOINSWAPGROUPNVPROC)(Display *dpy, GLXDrawable drawable, GLuint group);
typedef Bool (GLE_FUNCPTR * PFNGLXBINDSWAPBARRIERNVPROC)(Display *dpy, GLuint group, GLuint barrier);
typedef Bool (GLE_FUNCPTR * PFNGLXQUERYSWAPGROUPNVPROC)(Display *dpy, GLXDrawable drawable, GLuint *group, GLuint *barrier);
typedef Bool (GLE_FUNCPTR * PFNGLXQUERYMAXSWAPGROUPSNVPROC)(Display *dpy, int screen, GLuint *maxGroups, GLuint *maxBarriers);
typedef Bool (GLE_FUNCPTR * PFNGLXQUERYFRAMECOUNTNVPROC)(Display *dpy, int screen, GLuint *count);
typedef Bool (GLE_FUNCPTR * PFNGLXRESETFRAMECOUNTNVPROC)(Display *dpy, int screen);

PFNGLXJOINSWAPGROUPNVPROC glXJoinSwapGroupNV;
PFNGLXBINDSWAPBARRIERNVPROC glXBindSwapBarrierNV;
PFNGLXQUERYSWAPGROUPNVPROC glXQuerySwapGroupNV;
PFNGLXQUERYMAXSWAPGROUPSNVPROC glXQueryMaxSwapGroupsNV;
PFNGLXQUERYFRAMECOUNTNVPROC glXQueryFrameCountNV;
PFNGLXRESETFRAMECOUNTNVPROC glXResetFrameCountNV;
#endif /*GLX_NV_swap_group*/

static int glXeIntLoad_NV_swap_group()
{
	int bIsLoaded = 1;
#ifndef GLX_NV_swap_group
	glXJoinSwapGroupNV = (PFNGLXJOINSWAPGROUPNVPROC)gleIntGetProcAddress("glXJoinSwapGroupNV");
	if(!TestPointer((const void*)glXJoinSwapGroupNV)) bIsLoaded = 0;
	glXBindSwapBarrierNV = (PFNGLXBINDSWAPBARRIERNVPROC)gleIntGetProcAddress("glXBindSwapBarrierNV");
	if(!TestPointer((const void*)glXBindSwapBarrierNV)) bIsLoaded = 0;
	glXQuerySwapGroupNV = (PFNGLXQUERYSWAPGROUPNVPROC)gleIntGetProcAddress("glXQuerySwapGroupNV");
	if(!TestPointer((const void*)glXQuerySwapGroupNV)) bIsLoaded = 0;
	glXQueryMaxSwapGroupsNV = (PFNGLXQUERYMAXSWAPGROUPSNVPROC)gleIntGetProcAddress("glXQueryMaxSwapGroupsNV");
	if(!TestPointer((const void*)glXQueryMaxSwapGroupsNV)) bIsLoaded = 0;
	glXQueryFrameCountNV = (PFNGLXQUERYFRAMECOUNTNVPROC)gleIntGetProcAddress("glXQueryFrameCountNV");
	if(!TestPointer((const void*)glXQueryFrameCountNV)) bIsLoaded = 0;
	glXResetFrameCountNV = (PFNGLXRESETFRAMECOUNTNVPROC)gleIntGetProcAddress("glXResetFrameCountNV");
	if(!TestPointer((const void*)glXResetFrameCountNV)) bIsLoaded = 0;
#endif /*GLX_NV_swap_group*/
	return bIsLoaded;
}
#ifndef GLX_NV_video_capture
typedef int (GLE_FUNCPTR * PFNGLXBINDVIDEOCAPTUREDEVICENVPROC)(Display *dpy, unsigned int video_capture_slot, GLXVideoCaptureDeviceNV device);
typedef GLXVideoCaptureDeviceNV * (GLE_FUNCPTR * PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC)(Display *dpy, int screen, int *nelements);
typedef void (GLE_FUNCPTR * PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC)(Display *dpy, GLXVideoCaptureDeviceNV device);
typedef int (GLE_FUNCPTR * PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC)(Display *dpy, GLXVideoCaptureDeviceNV device, int attribute, int *value);
typedef void (GLE_FUNCPTR * PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC)(Display *dpy, GLXVideoCaptureDeviceNV device);

PFNGLXBINDVIDEOCAPTUREDEVICENVPROC glXBindVideoCaptureDeviceNV;
PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC glXEnumerateVideoCaptureDevicesNV;
PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC glXLockVideoCaptureDeviceNV;
PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC glXQueryVideoCaptureDeviceNV;
PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC glXReleaseVideoCaptureDeviceNV;
#endif /*GLX_NV_video_capture*/

static int glXeIntLoad_NV_video_capture()
{
	int bIsLoaded = 1;
#ifndef GLX_NV_video_capture
	glXBindVideoCaptureDeviceNV = (PFNGLXBINDVIDEOCAPTUREDEVICENVPROC)gleIntGetProcAddress("glXBindVideoCaptureDeviceNV");
	if(!TestPointer((const void*)glXBindVideoCaptureDeviceNV)) bIsLoaded = 0;
	glXEnumerateVideoCaptureDevicesNV = (PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC)gleIntGetProcAddress("glXEnumerateVideoCaptureDevicesNV");
	if(!TestPointer((const void*)glXEnumerateVideoCaptureDevicesNV)) bIsLoaded = 0;
	glXLockVideoCaptureDeviceNV = (PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC)gleIntGetProcAddress("glXLockVideoCaptureDeviceNV");
	if(!TestPointer((const void*)glXLockVideoCaptureDeviceNV)) bIsLoaded = 0;
	glXQueryVideoCaptureDeviceNV = (PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC)gleIntGetProcAddress("glXQueryVideoCaptureDeviceNV");
	if(!TestPointer((const void*)glXQueryVideoCaptureDeviceNV)) bIsLoaded = 0;
	glXReleaseVideoCaptureDeviceNV = (PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC)gleIntGetProcAddress("glXReleaseVideoCaptureDeviceNV");
	if(!TestPointer((const void*)glXReleaseVideoCaptureDeviceNV)) bIsLoaded = 0;
#endif /*GLX_NV_video_capture*/
	return bIsLoaded;
}


#ifndef GLX_OML_sync_control
typedef Bool (GLE_FUNCPTR * PFNGLXGETSYNCVALUESOMLPROC)(Display *dpy, GLXDrawable drawable, int64_t *ust, int64_t *msc, int64_t *sbc);
typedef Bool (GLE_FUNCPTR * PFNGLXGETMSCRATEOMLPROC)(Display *dpy, GLXDrawable drawable, int32_t *numerator, int32_t *denominator);
typedef int64_t (GLE_FUNCPTR * PFNGLXSWAPBUFFERSMSCOMLPROC)(Display *dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder);
typedef Bool (GLE_FUNCPTR * PFNGLXWAITFORMSCOMLPROC)(Display *dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder, int64_t *ust, int64_t *msc, int64_t *sbc);
typedef Bool (GLE_FUNCPTR * PFNGLXWAITFORSBCOMLPROC)(Display *dpy, GLXDrawable drawable, int64_t target_sbc, int64_t *ust, int64_t *msc, int64_t *sbc);

PFNGLXGETSYNCVALUESOMLPROC glXGetSyncValuesOML;
PFNGLXGETMSCRATEOMLPROC glXGetMscRateOML;
PFNGLXSWAPBUFFERSMSCOMLPROC glXSwapBuffersMscOML;
PFNGLXWAITFORMSCOMLPROC glXWaitForMscOML;
PFNGLXWAITFORSBCOMLPROC glXWaitForSbcOML;
#endif /*GLX_OML_sync_control*/

static int glXeIntLoad_OML_sync_control()
{
	int bIsLoaded = 1;
#ifndef GLX_OML_sync_control
	glXGetSyncValuesOML = (PFNGLXGETSYNCVALUESOMLPROC)gleIntGetProcAddress("glXGetSyncValuesOML");
	if(!TestPointer((const void*)glXGetSyncValuesOML)) bIsLoaded = 0;
	glXGetMscRateOML = (PFNGLXGETMSCRATEOMLPROC)gleIntGetProcAddress("glXGetMscRateOML");
	if(!TestPointer((const void*)glXGetMscRateOML)) bIsLoaded = 0;
	glXSwapBuffersMscOML = (PFNGLXSWAPBUFFERSMSCOMLPROC)gleIntGetProcAddress("glXSwapBuffersMscOML");
	if(!TestPointer((const void*)glXSwapBuffersMscOML)) bIsLoaded = 0;
	glXWaitForMscOML = (PFNGLXWAITFORMSCOMLPROC)gleIntGetProcAddress("glXWaitForMscOML");
	if(!TestPointer((const void*)glXWaitForMscOML)) bIsLoaded = 0;
	glXWaitForSbcOML = (PFNGLXWAITFORSBCOMLPROC)gleIntGetProcAddress("glXWaitForSbcOML");
	if(!TestPointer((const void*)glXWaitForSbcOML)) bIsLoaded = 0;
#endif /*GLX_OML_sync_control*/
	return bIsLoaded;
}



#ifndef GLX_SGIX_fbconfig
typedef int (GLE_FUNCPTR * PFNGLXGETFBCONFIGATTRIBSGIXPROC)(Display *dpy, GLXFBConfigSGIX config, int attribute, int *value);
typedef GLXFBConfigSGIX * (GLE_FUNCPTR * PFNGLXCHOOSEFBCONFIGSGIXPROC)(Display *dpy, int screen, int *attrib_list, int *nelements);
typedef GLXPixmap (GLE_FUNCPTR * PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC)(Display *dpy, GLXFBConfigSGIX config, Pixmap pixmap);
typedef GLXContext (GLE_FUNCPTR * PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC)(Display *dpy, GLXFBConfigSGIX config, int render_type, GLXContext share_list, Bool direct);
typedef XVisualInfo * (GLE_FUNCPTR * PFNGLXGETVISUALFROMFBCONFIGSGIXPROC)(Display *dpy, GLXFBConfigSGIX config);
typedef GLXFBConfigSGIX (GLE_FUNCPTR * PFNGLXGETFBCONFIGFROMVISUALSGIXPROC)(Display *dpy, XVisualInfo *vis);

PFNGLXGETFBCONFIGATTRIBSGIXPROC glXGetFBConfigAttribSGIX;
PFNGLXCHOOSEFBCONFIGSGIXPROC glXChooseFBConfigSGIX;
PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC glXCreateGLXPixmapWithConfigSGIX;
PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC glXCreateContextWithConfigSGIX;
PFNGLXGETVISUALFROMFBCONFIGSGIXPROC glXGetVisualFromFBConfigSGIX;
PFNGLXGETFBCONFIGFROMVISUALSGIXPROC glXGetFBConfigFromVisualSGIX;
#endif /*GLX_SGIX_fbconfig*/

static int glXeIntLoad_SGIX_fbconfig()
{
	int bIsLoaded = 1;
#ifndef GLX_SGIX_fbconfig
	glXGetFBConfigAttribSGIX = (PFNGLXGETFBCONFIGATTRIBSGIXPROC)gleIntGetProcAddress("glXGetFBConfigAttribSGIX");
	if(!TestPointer((const void*)glXGetFBConfigAttribSGIX)) bIsLoaded = 0;
	glXChooseFBConfigSGIX = (PFNGLXCHOOSEFBCONFIGSGIXPROC)gleIntGetProcAddress("glXChooseFBConfigSGIX");
	if(!TestPointer((const void*)glXChooseFBConfigSGIX)) bIsLoaded = 0;
	glXCreateGLXPixmapWithConfigSGIX = (PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC)gleIntGetProcAddress("glXCreateGLXPixmapWithConfigSGIX");
	if(!TestPointer((const void*)glXCreateGLXPixmapWithConfigSGIX)) bIsLoaded = 0;
	glXCreateContextWithConfigSGIX = (PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC)gleIntGetProcAddress("glXCreateContextWithConfigSGIX");
	if(!TestPointer((const void*)glXCreateContextWithConfigSGIX)) bIsLoaded = 0;
	glXGetVisualFromFBConfigSGIX = (PFNGLXGETVISUALFROMFBCONFIGSGIXPROC)gleIntGetProcAddress("glXGetVisualFromFBConfigSGIX");
	if(!TestPointer((const void*)glXGetVisualFromFBConfigSGIX)) bIsLoaded = 0;
	glXGetFBConfigFromVisualSGIX = (PFNGLXGETFBCONFIGFROMVISUALSGIXPROC)gleIntGetProcAddress("glXGetFBConfigFromVisualSGIX");
	if(!TestPointer((const void*)glXGetFBConfigFromVisualSGIX)) bIsLoaded = 0;
#endif /*GLX_SGIX_fbconfig*/
	return bIsLoaded;
}
#ifndef GLX_SGIX_pbuffer
typedef GLXPbufferSGIX (GLE_FUNCPTR * PFNGLXCREATEGLXPBUFFERSGIXPROC)(Display *dpy, GLXFBConfigSGIX config, unsigned int width, unsigned int height, int *attrib_list);
typedef void (GLE_FUNCPTR * PFNGLXDESTROYGLXPBUFFERSGIXPROC)(Display *dpy, GLXPbufferSGIX pbuf);
typedef int (GLE_FUNCPTR * PFNGLXQUERYGLXPBUFFERSGIXPROC)(Display *dpy, GLXPbufferSGIX pbuf, int attribute, unsigned int *value);
typedef void (GLE_FUNCPTR * PFNGLXSELECTEVENTSGIXPROC)(Display *dpy, GLXDrawable drawable, unsigned long mask);
typedef void (GLE_FUNCPTR * PFNGLXGETSELECTEDEVENTSGIXPROC)(Display *dpy, GLXDrawable drawable, unsigned long *mask);

PFNGLXCREATEGLXPBUFFERSGIXPROC glXCreateGLXPbufferSGIX;
PFNGLXDESTROYGLXPBUFFERSGIXPROC glXDestroyGLXPbufferSGIX;
PFNGLXQUERYGLXPBUFFERSGIXPROC glXQueryGLXPbufferSGIX;
PFNGLXSELECTEVENTSGIXPROC glXSelectEventSGIX;
PFNGLXGETSELECTEDEVENTSGIXPROC glXGetSelectedEventSGIX;
#endif /*GLX_SGIX_pbuffer*/

static int glXeIntLoad_SGIX_pbuffer()
{
	int bIsLoaded = 1;
#ifndef GLX_SGIX_pbuffer
	glXCreateGLXPbufferSGIX = (PFNGLXCREATEGLXPBUFFERSGIXPROC)gleIntGetProcAddress("glXCreateGLXPbufferSGIX");
	if(!TestPointer((const void*)glXCreateGLXPbufferSGIX)) bIsLoaded = 0;
	glXDestroyGLXPbufferSGIX = (PFNGLXDESTROYGLXPBUFFERSGIXPROC)gleIntGetProcAddress("glXDestroyGLXPbufferSGIX");
	if(!TestPointer((const void*)glXDestroyGLXPbufferSGIX)) bIsLoaded = 0;
	glXQueryGLXPbufferSGIX = (PFNGLXQUERYGLXPBUFFERSGIXPROC)gleIntGetProcAddress("glXQueryGLXPbufferSGIX");
	if(!TestPointer((const void*)glXQueryGLXPbufferSGIX)) bIsLoaded = 0;
	glXSelectEventSGIX = (PFNGLXSELECTEVENTSGIXPROC)gleIntGetProcAddress("glXSelectEventSGIX");
	if(!TestPointer((const void*)glXSelectEventSGIX)) bIsLoaded = 0;
	glXGetSelectedEventSGIX = (PFNGLXGETSELECTEDEVENTSGIXPROC)gleIntGetProcAddress("glXGetSelectedEventSGIX");
	if(!TestPointer((const void*)glXGetSelectedEventSGIX)) bIsLoaded = 0;
#endif /*GLX_SGIX_pbuffer*/
	return bIsLoaded;
}
#ifndef GLX_SGIX_swap_barrier
typedef void (GLE_FUNCPTR * PFNGLXBINDSWAPBARRIERSGIXPROC)(Display *dpy, GLXDrawable drawable, int barrier);
typedef Bool (GLE_FUNCPTR * PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC)(Display *dpy, int screen, int *max);

PFNGLXBINDSWAPBARRIERSGIXPROC glXBindSwapBarrierSGIX;
PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC glXQueryMaxSwapBarriersSGIX;
#endif /*GLX_SGIX_swap_barrier*/

static int glXeIntLoad_SGIX_swap_barrier()
{
	int bIsLoaded = 1;
#ifndef GLX_SGIX_swap_barrier
	glXBindSwapBarrierSGIX = (PFNGLXBINDSWAPBARRIERSGIXPROC)gleIntGetProcAddress("glXBindSwapBarrierSGIX");
	if(!TestPointer((const void*)glXBindSwapBarrierSGIX)) bIsLoaded = 0;
	glXQueryMaxSwapBarriersSGIX = (PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC)gleIntGetProcAddress("glXQueryMaxSwapBarriersSGIX");
	if(!TestPointer((const void*)glXQueryMaxSwapBarriersSGIX)) bIsLoaded = 0;
#endif /*GLX_SGIX_swap_barrier*/
	return bIsLoaded;
}
#ifndef GLX_SGIX_swap_group
typedef void (GLE_FUNCPTR * PFNGLXJOINSWAPGROUPSGIXPROC)(Display *dpy, GLXDrawable drawable, GLXDrawable member);

PFNGLXJOINSWAPGROUPSGIXPROC glXJoinSwapGroupSGIX;
#endif /*GLX_SGIX_swap_group*/

static int glXeIntLoad_SGIX_swap_group()
{
	int bIsLoaded = 1;
#ifndef GLX_SGIX_swap_group
	glXJoinSwapGroupSGIX = (PFNGLXJOINSWAPGROUPSGIXPROC)gleIntGetProcAddress("glXJoinSwapGroupSGIX");
	if(!TestPointer((const void*)glXJoinSwapGroupSGIX)) bIsLoaded = 0;
#endif /*GLX_SGIX_swap_group*/
	return bIsLoaded;
}
#ifndef GLX_SGIX_video_resize
typedef int (GLE_FUNCPTR * PFNGLXBINDCHANNELTOWINDOWSGIXPROC)(Display *display, int screen, int channel, Window window);
typedef int (GLE_FUNCPTR * PFNGLXCHANNELRECTSGIXPROC)(Display *display, int screen, int channel, int x, int y, int w, int h);
typedef int (GLE_FUNCPTR * PFNGLXQUERYCHANNELRECTSGIXPROC)(Display *display, int screen, int channel, int *dx, int *dy, int *dw, int *dh);
typedef int (GLE_FUNCPTR * PFNGLXQUERYCHANNELDELTASSGIXPROC)(Display *display, int screen, int channel, int *x, int *y, int *w, int *h);
typedef int (GLE_FUNCPTR * PFNGLXCHANNELRECTSYNCSGIXPROC)(Display *display, int screen, int channel, GLenum synctype);

PFNGLXBINDCHANNELTOWINDOWSGIXPROC glXBindChannelToWindowSGIX;
PFNGLXCHANNELRECTSGIXPROC glXChannelRectSGIX;
PFNGLXQUERYCHANNELRECTSGIXPROC glXQueryChannelRectSGIX;
PFNGLXQUERYCHANNELDELTASSGIXPROC glXQueryChannelDeltasSGIX;
PFNGLXCHANNELRECTSYNCSGIXPROC glXChannelRectSyncSGIX;
#endif /*GLX_SGIX_video_resize*/

static int glXeIntLoad_SGIX_video_resize()
{
	int bIsLoaded = 1;
#ifndef GLX_SGIX_video_resize
	glXBindChannelToWindowSGIX = (PFNGLXBINDCHANNELTOWINDOWSGIXPROC)gleIntGetProcAddress("glXBindChannelToWindowSGIX");
	if(!TestPointer((const void*)glXBindChannelToWindowSGIX)) bIsLoaded = 0;
	glXChannelRectSGIX = (PFNGLXCHANNELRECTSGIXPROC)gleIntGetProcAddress("glXChannelRectSGIX");
	if(!TestPointer((const void*)glXChannelRectSGIX)) bIsLoaded = 0;
	glXQueryChannelRectSGIX = (PFNGLXQUERYCHANNELRECTSGIXPROC)gleIntGetProcAddress("glXQueryChannelRectSGIX");
	if(!TestPointer((const void*)glXQueryChannelRectSGIX)) bIsLoaded = 0;
	glXQueryChannelDeltasSGIX = (PFNGLXQUERYCHANNELDELTASSGIXPROC)gleIntGetProcAddress("glXQueryChannelDeltasSGIX");
	if(!TestPointer((const void*)glXQueryChannelDeltasSGIX)) bIsLoaded = 0;
	glXChannelRectSyncSGIX = (PFNGLXCHANNELRECTSYNCSGIXPROC)gleIntGetProcAddress("glXChannelRectSyncSGIX");
	if(!TestPointer((const void*)glXChannelRectSyncSGIX)) bIsLoaded = 0;
#endif /*GLX_SGIX_video_resize*/
	return bIsLoaded;
}

#ifndef GLX_SGI_cushion
typedef void (GLE_FUNCPTR * PFNGLXCUSHIONSGIPROC)(Display *dpy, Window window, float cushion);

PFNGLXCUSHIONSGIPROC glXCushionSGI;
#endif /*GLX_SGI_cushion*/

static int glXeIntLoad_SGI_cushion()
{
	int bIsLoaded = 1;
#ifndef GLX_SGI_cushion
	glXCushionSGI = (PFNGLXCUSHIONSGIPROC)gleIntGetProcAddress("glXCushionSGI");
	if(!TestPointer((const void*)glXCushionSGI)) bIsLoaded = 0;
#endif /*GLX_SGI_cushion*/
	return bIsLoaded;
}
#ifndef GLX_SGI_make_current_read
typedef Bool (GLE_FUNCPTR * PFNGLXMAKECURRENTREADSGIPROC)(Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
typedef GLXDrawable (GLE_FUNCPTR * PFNGLXGETCURRENTREADDRAWABLESGIPROC)();

PFNGLXMAKECURRENTREADSGIPROC glXMakeCurrentReadSGI;
PFNGLXGETCURRENTREADDRAWABLESGIPROC glXGetCurrentReadDrawableSGI;
#endif /*GLX_SGI_make_current_read*/

static int glXeIntLoad_SGI_make_current_read()
{
	int bIsLoaded = 1;
#ifndef GLX_SGI_make_current_read
	glXMakeCurrentReadSGI = (PFNGLXMAKECURRENTREADSGIPROC)gleIntGetProcAddress("glXMakeCurrentReadSGI");
	if(!TestPointer((const void*)glXMakeCurrentReadSGI)) bIsLoaded = 0;
	glXGetCurrentReadDrawableSGI = (PFNGLXGETCURRENTREADDRAWABLESGIPROC)gleIntGetProcAddress("glXGetCurrentReadDrawableSGI");
	if(!TestPointer((const void*)glXGetCurrentReadDrawableSGI)) bIsLoaded = 0;
#endif /*GLX_SGI_make_current_read*/
	return bIsLoaded;
}
#ifndef GLX_SGI_swap_control
typedef int (GLE_FUNCPTR * PFNGLXSWAPINTERVALSGIPROC)(int interval);

PFNGLXSWAPINTERVALSGIPROC glXSwapIntervalSGI;
#endif /*GLX_SGI_swap_control*/

static int glXeIntLoad_SGI_swap_control()
{
	int bIsLoaded = 1;
#ifndef GLX_SGI_swap_control
	glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)gleIntGetProcAddress("glXSwapIntervalSGI");
	if(!TestPointer((const void*)glXSwapIntervalSGI)) bIsLoaded = 0;
#endif /*GLX_SGI_swap_control*/
	return bIsLoaded;
}
#ifndef GLX_SGI_video_sync
typedef int (GLE_FUNCPTR * PFNGLXGETVIDEOSYNCSGIPROC)(unsigned int *count);
typedef int (GLE_FUNCPTR * PFNGLXWAITVIDEOSYNCSGIPROC)(int divisor, int remainder, unsigned int *count);

PFNGLXGETVIDEOSYNCSGIPROC glXGetVideoSyncSGI;
PFNGLXWAITVIDEOSYNCSGIPROC glXWaitVideoSyncSGI;
#endif /*GLX_SGI_video_sync*/

static int glXeIntLoad_SGI_video_sync()
{
	int bIsLoaded = 1;
#ifndef GLX_SGI_video_sync
	glXGetVideoSyncSGI = (PFNGLXGETVIDEOSYNCSGIPROC)gleIntGetProcAddress("glXGetVideoSyncSGI");
	if(!TestPointer((const void*)glXGetVideoSyncSGI)) bIsLoaded = 0;
	glXWaitVideoSyncSGI = (PFNGLXWAITVIDEOSYNCSGIPROC)gleIntGetProcAddress("glXWaitVideoSyncSGI");
	if(!TestPointer((const void*)glXWaitVideoSyncSGI)) bIsLoaded = 0;
#endif /*GLX_SGI_video_sync*/
	return bIsLoaded;
}
#ifndef GLX_SUN_get_transparent_index
typedef Status (GLE_FUNCPTR * PFNGLXGETTRANSPARENTINDEXSUNPROC)(Display *dpy, Window overlay, Window underlay, long *pTransparentIndex);

PFNGLXGETTRANSPARENTINDEXSUNPROC glXGetTransparentIndexSUN;
#endif /*GLX_SUN_get_transparent_index*/

static int glXeIntLoad_SUN_get_transparent_index()
{
	int bIsLoaded = 1;
#ifndef GLX_SUN_get_transparent_index
	glXGetTransparentIndexSUN = (PFNGLXGETTRANSPARENTINDEXSUNPROC)gleIntGetProcAddress("glXGetTransparentIndexSUN");
	if(!TestPointer((const void*)glXGetTransparentIndexSUN)) bIsLoaded = 0;
#endif /*GLX_SUN_get_transparent_index*/
	return bIsLoaded;
}
StrToExtMap glXeIntExtensionMap[] = {
	{"GLX_3DFX_multisample", &glXext_3DFX_multisample, NULL},
	{"GLX_AMD_gpu_association", &glXext_AMD_gpu_association, NULL},
	{"GLX_ARB_create_context", &glXext_ARB_create_context, glXeIntLoad_ARB_create_context},
	{"GLX_ARB_create_context_profile", &glXext_ARB_create_context_profile, NULL},
	{"GLX_ARB_create_context_robustness", &glXext_ARB_create_context_robustness, NULL},
	{"GLX_ARB_fbconfig_float", &glXext_ARB_fbconfig_float, NULL},
	{"GLX_ARB_framebuffer_sRGB", &glXext_ARB_framebuffer_sRGB, NULL},
	{"GLX_ARB_get_proc_address", &glXext_ARB_get_proc_address, glXeIntLoad_ARB_get_proc_address},
	{"GLX_ARB_multisample", &glXext_ARB_multisample, NULL},
	{"GLX_ARB_vertex_buffer_object", &glXext_ARB_vertex_buffer_object, NULL},
	{"GLX_EXT_create_context_es2_profile", &glXext_EXT_create_context_es2_profile, NULL},
	{"GLX_EXT_fbconfig_packed_float", &glXext_EXT_fbconfig_packed_float, NULL},
	{"GLX_EXT_framebuffer_sRGB", &glXext_EXT_framebuffer_sRGB, NULL},
	{"GLX_EXT_import_context", &glXext_EXT_import_context, glXeIntLoad_EXT_import_context},
	{"GLX_EXT_swap_control", &glXext_EXT_swap_control, glXeIntLoad_EXT_swap_control},
	{"GLX_EXT_texture_from_pixmap", &glXext_EXT_texture_from_pixmap, glXeIntLoad_EXT_texture_from_pixmap},
	{"GLX_EXT_visual_info", &glXext_EXT_visual_info, NULL},
	{"GLX_EXT_visual_rating", &glXext_EXT_visual_rating, NULL},
	{"GLX_INTEL_swap_event", &glXext_INTEL_swap_event, NULL},
	{"GLX_MESA_agp_offset", &glXext_MESA_agp_offset, glXeIntLoad_MESA_agp_offset},
	{"GLX_MESA_copy_sub_buffer", &glXext_MESA_copy_sub_buffer, glXeIntLoad_MESA_copy_sub_buffer},
	{"GLX_MESA_pixmap_colormap", &glXext_MESA_pixmap_colormap, glXeIntLoad_MESA_pixmap_colormap},
	{"GLX_MESA_release_buffers", &glXext_MESA_release_buffers, glXeIntLoad_MESA_release_buffers},
	{"GLX_MESA_set_3dfx_mode", &glXext_MESA_set_3dfx_mode, glXeIntLoad_MESA_set_3dfx_mode},
	{"GLX_NV_copy_image", &glXext_NV_copy_image, glXeIntLoad_NV_copy_image},
	{"GLX_NV_float_buffer", &glXext_NV_float_buffer, NULL},
	{"GLX_NV_multisample_coverage", &glXext_NV_multisample_coverage, NULL},
	{"GLX_NV_present_video", &glXext_NV_present_video, glXeIntLoad_NV_present_video},
	{"GLX_NV_swap_group", &glXext_NV_swap_group, glXeIntLoad_NV_swap_group},
	{"GLX_NV_video_capture", &glXext_NV_video_capture, glXeIntLoad_NV_video_capture},
	{"GLX_NV_video_out", &glXext_NV_video_out, NULL},
	{"GLX_OML_swap_method", &glXext_OML_swap_method, NULL},
	{"GLX_OML_sync_control", &glXext_OML_sync_control, glXeIntLoad_OML_sync_control},
	{"GLX_SGIS_blended_overlay", &glXext_SGIS_blended_overlay, NULL},
	{"GLX_SGIS_multisample", &glXext_SGIS_multisample, NULL},
	{"GLX_SGIS_shared_multisample", &glXext_SGIS_shared_multisample, NULL},
	{"GLX_SGIX_fbconfig", &glXext_SGIX_fbconfig, glXeIntLoad_SGIX_fbconfig},
	{"GLX_SGIX_pbuffer", &glXext_SGIX_pbuffer, glXeIntLoad_SGIX_pbuffer},
	{"GLX_SGIX_swap_barrier", &glXext_SGIX_swap_barrier, glXeIntLoad_SGIX_swap_barrier},
	{"GLX_SGIX_swap_group", &glXext_SGIX_swap_group, glXeIntLoad_SGIX_swap_group},
	{"GLX_SGIX_video_resize", &glXext_SGIX_video_resize, glXeIntLoad_SGIX_video_resize},
	{"GLX_SGIX_visual_select_group", &glXext_SGIX_visual_select_group, NULL},
	{"GLX_SGI_cushion", &glXext_SGI_cushion, glXeIntLoad_SGI_cushion},
	{"GLX_SGI_make_current_read", &glXext_SGI_make_current_read, glXeIntLoad_SGI_make_current_read},
	{"GLX_SGI_swap_control", &glXext_SGI_swap_control, glXeIntLoad_SGI_swap_control},
	{"GLX_SGI_video_sync", &glXext_SGI_video_sync, glXeIntLoad_SGI_video_sync},
	{"GLX_SUN_get_transparent_index", &glXext_SUN_get_transparent_index, glXeIntLoad_SUN_get_transparent_index},
};

int glXeIntExtensionMapSize = 47;



