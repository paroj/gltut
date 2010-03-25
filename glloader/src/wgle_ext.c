#include <stdlib.h>
#include <string.h>
#include "wgle_ext.h"

#include <stddef.h>	
	
static int TestPointer(const void *pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;
	
	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
	
	return 1;
}

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
			#define gleIntGetProcAddress(name) (*glXGetProcAddressARB)(name)
		#endif
	#endif
#endif

int wglext_ARB_buffer_region = 0;
int wglext_ARB_multisample = 0;
int wglext_ARB_extensions_string = 0;
int wglext_ARB_pixel_format = 0;
int wglext_ARB_make_current_read = 0;
int wglext_ARB_pbuffer = 0;
int wglext_ARB_render_texture = 0;
int wglext_ARB_pixel_format_float = 0;
int wglext_ARB_create_context = 0;
int wglext_ARB_create_context_profile = 0;
int wglext_EXT_make_current_read = 0;
int wglext_EXT_pixel_format = 0;
int wglext_EXT_pbuffer = 0;
int wglext_EXT_depth_float = 0;
int wglext_3DFX_multisample = 0;
int wglext_EXT_multisample = 0;
int wglext_I3D_digital_video_control = 0;
int wglext_I3D_gamma = 0;
int wglext_I3D_genlock = 0;
int wglext_I3D_image_buffer = 0;
int wglext_I3D_swap_frame_lock = 0;
int wglext_NV_render_depth_texture = 0;
int wglext_NV_render_texture_rectangle = 0;
int wglext_ATI_pixel_format_float = 0;
int wglext_NV_float_buffer = 0;
int wglext_3DL_stereo_control = 0;
int wglext_EXT_pixel_format_packed_float = 0;
int wglext_EXT_framebuffer_sRGB = 0;
int wglext_NV_present_video = 0;
int wglext_NV_video_out = 0;
int wglext_NV_swap_group = 0;
int wglext_NV_gpu_affinity = 0;
int wglext_AMD_gpu_association = 0;


void wgleIntClear()
{
	wglext_ARB_buffer_region = 0;
	wglext_ARB_multisample = 0;
	wglext_ARB_extensions_string = 0;
	wglext_ARB_pixel_format = 0;
	wglext_ARB_make_current_read = 0;
	wglext_ARB_pbuffer = 0;
	wglext_ARB_render_texture = 0;
	wglext_ARB_pixel_format_float = 0;
	wglext_ARB_create_context = 0;
	wglext_ARB_create_context_profile = 0;
	wglext_EXT_make_current_read = 0;
	wglext_EXT_pixel_format = 0;
	wglext_EXT_pbuffer = 0;
	wglext_EXT_depth_float = 0;
	wglext_3DFX_multisample = 0;
	wglext_EXT_multisample = 0;
	wglext_I3D_digital_video_control = 0;
	wglext_I3D_gamma = 0;
	wglext_I3D_genlock = 0;
	wglext_I3D_image_buffer = 0;
	wglext_I3D_swap_frame_lock = 0;
	wglext_NV_render_depth_texture = 0;
	wglext_NV_render_texture_rectangle = 0;
	wglext_ATI_pixel_format_float = 0;
	wglext_NV_float_buffer = 0;
	wglext_3DL_stereo_control = 0;
	wglext_EXT_pixel_format_packed_float = 0;
	wglext_EXT_framebuffer_sRGB = 0;
	wglext_NV_present_video = 0;
	wglext_NV_video_out = 0;
	wglext_NV_swap_group = 0;
	wglext_NV_gpu_affinity = 0;
	wglext_AMD_gpu_association = 0;
}



typedef BOOL (GLE_FUNCPTR * PFNWGLSETSTEREOEMITTERSTATE3DLPROC)(HDC hDC, UINT uState);

PFNWGLSETSTEREOEMITTERSTATE3DLPROC wglSetStereoEmitterState3DL;

static int wgleIntLoad_3DL_stereo_control()
{
	int bIsLoaded = 1;
	wglSetStereoEmitterState3DL = (PFNWGLSETSTEREOEMITTERSTATE3DLPROC)gleIntGetProcAddress("wglSetStereoEmitterState3DL");
	if(!TestPointer(wglSetStereoEmitterState3DL)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef UINT (GLE_FUNCPTR * PFNWGLGETGPUIDSAMDPROC)(UINT maxCount, UINT *ids);
typedef INT (GLE_FUNCPTR * PFNWGLGETGPUINFOAMDPROC)(UINT id, int property, GLenum dataType, UINT size, void *data);
typedef UINT (GLE_FUNCPTR * PFNWGLGETCONTEXTGPUIDAMDPROC)(HGLRC hglrc);
typedef HGLRC (GLE_FUNCPTR * PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)(UINT id);
typedef HGLRC (GLE_FUNCPTR * PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)(UINT id, HGLRC hShareContext, const int *attribList);
typedef BOOL (GLE_FUNCPTR * PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)(HGLRC hglrc);
typedef BOOL (GLE_FUNCPTR * PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)(HGLRC hglrc);
typedef HGLRC (GLE_FUNCPTR * PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)();
typedef VOID (GLE_FUNCPTR * PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)(HGLRC dstCtx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

PFNWGLGETGPUIDSAMDPROC wglGetGPUIDsAMD;
PFNWGLGETGPUINFOAMDPROC wglGetGPUInfoAMD;
PFNWGLGETCONTEXTGPUIDAMDPROC wglGetContextGPUIDAMD;
PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC wglCreateAssociatedContextAMD;
PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC wglCreateAssociatedContextAttribsAMD;
PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC wglDeleteAssociatedContextAMD;
PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC wglMakeAssociatedContextCurrentAMD;
PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC wglGetCurrentAssociatedContextAMD;
PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC wglBlitContextFramebufferAMD;

static int wgleIntLoad_AMD_gpu_association()
{
	int bIsLoaded = 1;
	wglGetGPUIDsAMD = (PFNWGLGETGPUIDSAMDPROC)gleIntGetProcAddress("wglGetGPUIDsAMD");
	if(!TestPointer(wglGetGPUIDsAMD)) bIsLoaded = 0;
	wglGetGPUInfoAMD = (PFNWGLGETGPUINFOAMDPROC)gleIntGetProcAddress("wglGetGPUInfoAMD");
	if(!TestPointer(wglGetGPUInfoAMD)) bIsLoaded = 0;
	wglGetContextGPUIDAMD = (PFNWGLGETCONTEXTGPUIDAMDPROC)gleIntGetProcAddress("wglGetContextGPUIDAMD");
	if(!TestPointer(wglGetContextGPUIDAMD)) bIsLoaded = 0;
	wglCreateAssociatedContextAMD = (PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)gleIntGetProcAddress("wglCreateAssociatedContextAMD");
	if(!TestPointer(wglCreateAssociatedContextAMD)) bIsLoaded = 0;
	wglCreateAssociatedContextAttribsAMD = (PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)gleIntGetProcAddress("wglCreateAssociatedContextAttribsAMD");
	if(!TestPointer(wglCreateAssociatedContextAttribsAMD)) bIsLoaded = 0;
	wglDeleteAssociatedContextAMD = (PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)gleIntGetProcAddress("wglDeleteAssociatedContextAMD");
	if(!TestPointer(wglDeleteAssociatedContextAMD)) bIsLoaded = 0;
	wglMakeAssociatedContextCurrentAMD = (PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)gleIntGetProcAddress("wglMakeAssociatedContextCurrentAMD");
	if(!TestPointer(wglMakeAssociatedContextCurrentAMD)) bIsLoaded = 0;
	wglGetCurrentAssociatedContextAMD = (PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)gleIntGetProcAddress("wglGetCurrentAssociatedContextAMD");
	if(!TestPointer(wglGetCurrentAssociatedContextAMD)) bIsLoaded = 0;
	wglBlitContextFramebufferAMD = (PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)gleIntGetProcAddress("wglBlitContextFramebufferAMD");
	if(!TestPointer(wglBlitContextFramebufferAMD)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef HANDLE (GLE_FUNCPTR * PFNWGLCREATEBUFFERREGIONARBPROC)(HDC hDC, int iLayerPlane, UINT uType);
typedef VOID (GLE_FUNCPTR * PFNWGLDELETEBUFFERREGIONARBPROC)(HANDLE hRegion);
typedef BOOL (GLE_FUNCPTR * PFNWGLSAVEBUFFERREGIONARBPROC)(HANDLE hRegion, int x, int y, int width, int height);
typedef BOOL (GLE_FUNCPTR * PFNWGLRESTOREBUFFERREGIONARBPROC)(HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc);

PFNWGLCREATEBUFFERREGIONARBPROC wglCreateBufferRegionARB;
PFNWGLDELETEBUFFERREGIONARBPROC wglDeleteBufferRegionARB;
PFNWGLSAVEBUFFERREGIONARBPROC wglSaveBufferRegionARB;
PFNWGLRESTOREBUFFERREGIONARBPROC wglRestoreBufferRegionARB;

static int wgleIntLoad_ARB_buffer_region()
{
	int bIsLoaded = 1;
	wglCreateBufferRegionARB = (PFNWGLCREATEBUFFERREGIONARBPROC)gleIntGetProcAddress("wglCreateBufferRegionARB");
	if(!TestPointer(wglCreateBufferRegionARB)) bIsLoaded = 0;
	wglDeleteBufferRegionARB = (PFNWGLDELETEBUFFERREGIONARBPROC)gleIntGetProcAddress("wglDeleteBufferRegionARB");
	if(!TestPointer(wglDeleteBufferRegionARB)) bIsLoaded = 0;
	wglSaveBufferRegionARB = (PFNWGLSAVEBUFFERREGIONARBPROC)gleIntGetProcAddress("wglSaveBufferRegionARB");
	if(!TestPointer(wglSaveBufferRegionARB)) bIsLoaded = 0;
	wglRestoreBufferRegionARB = (PFNWGLRESTOREBUFFERREGIONARBPROC)gleIntGetProcAddress("wglRestoreBufferRegionARB");
	if(!TestPointer(wglRestoreBufferRegionARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef HGLRC (GLE_FUNCPTR * PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int *attribList);

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

static int wgleIntLoad_ARB_create_context()
{
	int bIsLoaded = 1;
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)gleIntGetProcAddress("wglCreateContextAttribsARB");
	if(!TestPointer(wglCreateContextAttribsARB)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef const char * (GLE_FUNCPTR * PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);

PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;

static int wgleIntLoad_ARB_extensions_string()
{
	int bIsLoaded = 1;
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)gleIntGetProcAddress("wglGetExtensionsStringARB");
	if(!TestPointer(wglGetExtensionsStringARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef BOOL (GLE_FUNCPTR * PFNWGLMAKECONTEXTCURRENTARBPROC)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
typedef HDC (GLE_FUNCPTR * PFNWGLGETCURRENTREADDCARBPROC)();

PFNWGLMAKECONTEXTCURRENTARBPROC wglMakeContextCurrentARB;
PFNWGLGETCURRENTREADDCARBPROC wglGetCurrentReadDCARB;

static int wgleIntLoad_ARB_make_current_read()
{
	int bIsLoaded = 1;
	wglMakeContextCurrentARB = (PFNWGLMAKECONTEXTCURRENTARBPROC)gleIntGetProcAddress("wglMakeContextCurrentARB");
	if(!TestPointer(wglMakeContextCurrentARB)) bIsLoaded = 0;
	wglGetCurrentReadDCARB = (PFNWGLGETCURRENTREADDCARBPROC)gleIntGetProcAddress("wglGetCurrentReadDCARB");
	if(!TestPointer(wglGetCurrentReadDCARB)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef HPBUFFERARB (GLE_FUNCPTR * PFNWGLCREATEPBUFFERARBPROC)(HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
typedef HDC (GLE_FUNCPTR * PFNWGLGETPBUFFERDCARBPROC)(HPBUFFERARB hPbuffer);
typedef int (GLE_FUNCPTR * PFNWGLRELEASEPBUFFERDCARBPROC)(HPBUFFERARB hPbuffer, HDC hDC);
typedef BOOL (GLE_FUNCPTR * PFNWGLDESTROYPBUFFERARBPROC)(HPBUFFERARB hPbuffer);
typedef BOOL (GLE_FUNCPTR * PFNWGLQUERYPBUFFERARBPROC)(HPBUFFERARB hPbuffer, int iAttribute, int *piValue);

PFNWGLCREATEPBUFFERARBPROC wglCreatePbufferARB;
PFNWGLGETPBUFFERDCARBPROC wglGetPbufferDCARB;
PFNWGLRELEASEPBUFFERDCARBPROC wglReleasePbufferDCARB;
PFNWGLDESTROYPBUFFERARBPROC wglDestroyPbufferARB;
PFNWGLQUERYPBUFFERARBPROC wglQueryPbufferARB;

static int wgleIntLoad_ARB_pbuffer()
{
	int bIsLoaded = 1;
	wglCreatePbufferARB = (PFNWGLCREATEPBUFFERARBPROC)gleIntGetProcAddress("wglCreatePbufferARB");
	if(!TestPointer(wglCreatePbufferARB)) bIsLoaded = 0;
	wglGetPbufferDCARB = (PFNWGLGETPBUFFERDCARBPROC)gleIntGetProcAddress("wglGetPbufferDCARB");
	if(!TestPointer(wglGetPbufferDCARB)) bIsLoaded = 0;
	wglReleasePbufferDCARB = (PFNWGLRELEASEPBUFFERDCARBPROC)gleIntGetProcAddress("wglReleasePbufferDCARB");
	if(!TestPointer(wglReleasePbufferDCARB)) bIsLoaded = 0;
	wglDestroyPbufferARB = (PFNWGLDESTROYPBUFFERARBPROC)gleIntGetProcAddress("wglDestroyPbufferARB");
	if(!TestPointer(wglDestroyPbufferARB)) bIsLoaded = 0;
	wglQueryPbufferARB = (PFNWGLQUERYPBUFFERARBPROC)gleIntGetProcAddress("wglQueryPbufferARB");
	if(!TestPointer(wglQueryPbufferARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef BOOL (GLE_FUNCPTR * PFNWGLGETPIXELFORMATATTRIBIVARBPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);
typedef BOOL (GLE_FUNCPTR * PFNWGLGETPIXELFORMATATTRIBFVARBPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues);
typedef BOOL (GLE_FUNCPTR * PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC wglGetPixelFormatAttribfvARB;
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;

static int wgleIntLoad_ARB_pixel_format()
{
	int bIsLoaded = 1;
	wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)gleIntGetProcAddress("wglGetPixelFormatAttribivARB");
	if(!TestPointer(wglGetPixelFormatAttribivARB)) bIsLoaded = 0;
	wglGetPixelFormatAttribfvARB = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)gleIntGetProcAddress("wglGetPixelFormatAttribfvARB");
	if(!TestPointer(wglGetPixelFormatAttribfvARB)) bIsLoaded = 0;
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)gleIntGetProcAddress("wglChoosePixelFormatARB");
	if(!TestPointer(wglChoosePixelFormatARB)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef BOOL (GLE_FUNCPTR * PFNWGLBINDTEXIMAGEARBPROC)(HPBUFFERARB hPbuffer, int iBuffer);
typedef BOOL (GLE_FUNCPTR * PFNWGLRELEASETEXIMAGEARBPROC)(HPBUFFERARB hPbuffer, int iBuffer);
typedef BOOL (GLE_FUNCPTR * PFNWGLSETPBUFFERATTRIBARBPROC)(HPBUFFERARB hPbuffer, const int *piAttribList);

PFNWGLBINDTEXIMAGEARBPROC wglBindTexImageARB;
PFNWGLRELEASETEXIMAGEARBPROC wglReleaseTexImageARB;
PFNWGLSETPBUFFERATTRIBARBPROC wglSetPbufferAttribARB;

static int wgleIntLoad_ARB_render_texture()
{
	int bIsLoaded = 1;
	wglBindTexImageARB = (PFNWGLBINDTEXIMAGEARBPROC)gleIntGetProcAddress("wglBindTexImageARB");
	if(!TestPointer(wglBindTexImageARB)) bIsLoaded = 0;
	wglReleaseTexImageARB = (PFNWGLRELEASETEXIMAGEARBPROC)gleIntGetProcAddress("wglReleaseTexImageARB");
	if(!TestPointer(wglReleaseTexImageARB)) bIsLoaded = 0;
	wglSetPbufferAttribARB = (PFNWGLSETPBUFFERATTRIBARBPROC)gleIntGetProcAddress("wglSetPbufferAttribARB");
	if(!TestPointer(wglSetPbufferAttribARB)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef BOOL (GLE_FUNCPTR * PFNWGLMAKECONTEXTCURRENTEXTPROC)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
typedef HDC (GLE_FUNCPTR * PFNWGLGETCURRENTREADDCEXTPROC)();

PFNWGLMAKECONTEXTCURRENTEXTPROC wglMakeContextCurrentEXT;
PFNWGLGETCURRENTREADDCEXTPROC wglGetCurrentReadDCEXT;

static int wgleIntLoad_EXT_make_current_read()
{
	int bIsLoaded = 1;
	wglMakeContextCurrentEXT = (PFNWGLMAKECONTEXTCURRENTEXTPROC)gleIntGetProcAddress("wglMakeContextCurrentEXT");
	if(!TestPointer(wglMakeContextCurrentEXT)) bIsLoaded = 0;
	wglGetCurrentReadDCEXT = (PFNWGLGETCURRENTREADDCEXTPROC)gleIntGetProcAddress("wglGetCurrentReadDCEXT");
	if(!TestPointer(wglGetCurrentReadDCEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef HPBUFFEREXT (GLE_FUNCPTR * PFNWGLCREATEPBUFFEREXTPROC)(HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
typedef HDC (GLE_FUNCPTR * PFNWGLGETPBUFFERDCEXTPROC)(HPBUFFEREXT hPbuffer);
typedef int (GLE_FUNCPTR * PFNWGLRELEASEPBUFFERDCEXTPROC)(HPBUFFEREXT hPbuffer, HDC hDC);
typedef BOOL (GLE_FUNCPTR * PFNWGLDESTROYPBUFFEREXTPROC)(HPBUFFEREXT hPbuffer);
typedef BOOL (GLE_FUNCPTR * PFNWGLQUERYPBUFFEREXTPROC)(HPBUFFEREXT hPbuffer, int iAttribute, int *piValue);

PFNWGLCREATEPBUFFEREXTPROC wglCreatePbufferEXT;
PFNWGLGETPBUFFERDCEXTPROC wglGetPbufferDCEXT;
PFNWGLRELEASEPBUFFERDCEXTPROC wglReleasePbufferDCEXT;
PFNWGLDESTROYPBUFFEREXTPROC wglDestroyPbufferEXT;
PFNWGLQUERYPBUFFEREXTPROC wglQueryPbufferEXT;

static int wgleIntLoad_EXT_pbuffer()
{
	int bIsLoaded = 1;
	wglCreatePbufferEXT = (PFNWGLCREATEPBUFFEREXTPROC)gleIntGetProcAddress("wglCreatePbufferEXT");
	if(!TestPointer(wglCreatePbufferEXT)) bIsLoaded = 0;
	wglGetPbufferDCEXT = (PFNWGLGETPBUFFERDCEXTPROC)gleIntGetProcAddress("wglGetPbufferDCEXT");
	if(!TestPointer(wglGetPbufferDCEXT)) bIsLoaded = 0;
	wglReleasePbufferDCEXT = (PFNWGLRELEASEPBUFFERDCEXTPROC)gleIntGetProcAddress("wglReleasePbufferDCEXT");
	if(!TestPointer(wglReleasePbufferDCEXT)) bIsLoaded = 0;
	wglDestroyPbufferEXT = (PFNWGLDESTROYPBUFFEREXTPROC)gleIntGetProcAddress("wglDestroyPbufferEXT");
	if(!TestPointer(wglDestroyPbufferEXT)) bIsLoaded = 0;
	wglQueryPbufferEXT = (PFNWGLQUERYPBUFFEREXTPROC)gleIntGetProcAddress("wglQueryPbufferEXT");
	if(!TestPointer(wglQueryPbufferEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef BOOL (GLE_FUNCPTR * PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, int *piValues);
typedef BOOL (GLE_FUNCPTR * PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, FLOAT *pfValues);
typedef BOOL (GLE_FUNCPTR * PFNWGLCHOOSEPIXELFORMATEXTPROC)(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

PFNWGLGETPIXELFORMATATTRIBIVEXTPROC wglGetPixelFormatAttribivEXT;
PFNWGLGETPIXELFORMATATTRIBFVEXTPROC wglGetPixelFormatAttribfvEXT;
PFNWGLCHOOSEPIXELFORMATEXTPROC wglChoosePixelFormatEXT;

static int wgleIntLoad_EXT_pixel_format()
{
	int bIsLoaded = 1;
	wglGetPixelFormatAttribivEXT = (PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)gleIntGetProcAddress("wglGetPixelFormatAttribivEXT");
	if(!TestPointer(wglGetPixelFormatAttribivEXT)) bIsLoaded = 0;
	wglGetPixelFormatAttribfvEXT = (PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)gleIntGetProcAddress("wglGetPixelFormatAttribfvEXT");
	if(!TestPointer(wglGetPixelFormatAttribfvEXT)) bIsLoaded = 0;
	wglChoosePixelFormatEXT = (PFNWGLCHOOSEPIXELFORMATEXTPROC)gleIntGetProcAddress("wglChoosePixelFormatEXT");
	if(!TestPointer(wglChoosePixelFormatEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef BOOL (GLE_FUNCPTR * PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC)(HDC hDC, int iAttribute, int *piValue);
typedef BOOL (GLE_FUNCPTR * PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC)(HDC hDC, int iAttribute, const int *piValue);

PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC wglGetDigitalVideoParametersI3D;
PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC wglSetDigitalVideoParametersI3D;

static int wgleIntLoad_I3D_digital_video_control()
{
	int bIsLoaded = 1;
	wglGetDigitalVideoParametersI3D = (PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC)gleIntGetProcAddress("wglGetDigitalVideoParametersI3D");
	if(!TestPointer(wglGetDigitalVideoParametersI3D)) bIsLoaded = 0;
	wglSetDigitalVideoParametersI3D = (PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC)gleIntGetProcAddress("wglSetDigitalVideoParametersI3D");
	if(!TestPointer(wglSetDigitalVideoParametersI3D)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef BOOL (GLE_FUNCPTR * PFNWGLGETGAMMATABLEPARAMETERSI3DPROC)(HDC hDC, int iAttribute, int *piValue);
typedef BOOL (GLE_FUNCPTR * PFNWGLSETGAMMATABLEPARAMETERSI3DPROC)(HDC hDC, int iAttribute, const int *piValue);
typedef BOOL (GLE_FUNCPTR * PFNWGLGETGAMMATABLEI3DPROC)(HDC hDC, int iEntries, USHORT *puRed, USHORT *puGreen, USHORT *puBlue);
typedef BOOL (GLE_FUNCPTR * PFNWGLSETGAMMATABLEI3DPROC)(HDC hDC, int iEntries, const USHORT *puRed, const USHORT *puGreen, const USHORT *puBlue);

PFNWGLGETGAMMATABLEPARAMETERSI3DPROC wglGetGammaTableParametersI3D;
PFNWGLSETGAMMATABLEPARAMETERSI3DPROC wglSetGammaTableParametersI3D;
PFNWGLGETGAMMATABLEI3DPROC wglGetGammaTableI3D;
PFNWGLSETGAMMATABLEI3DPROC wglSetGammaTableI3D;

static int wgleIntLoad_I3D_gamma()
{
	int bIsLoaded = 1;
	wglGetGammaTableParametersI3D = (PFNWGLGETGAMMATABLEPARAMETERSI3DPROC)gleIntGetProcAddress("wglGetGammaTableParametersI3D");
	if(!TestPointer(wglGetGammaTableParametersI3D)) bIsLoaded = 0;
	wglSetGammaTableParametersI3D = (PFNWGLSETGAMMATABLEPARAMETERSI3DPROC)gleIntGetProcAddress("wglSetGammaTableParametersI3D");
	if(!TestPointer(wglSetGammaTableParametersI3D)) bIsLoaded = 0;
	wglGetGammaTableI3D = (PFNWGLGETGAMMATABLEI3DPROC)gleIntGetProcAddress("wglGetGammaTableI3D");
	if(!TestPointer(wglGetGammaTableI3D)) bIsLoaded = 0;
	wglSetGammaTableI3D = (PFNWGLSETGAMMATABLEI3DPROC)gleIntGetProcAddress("wglSetGammaTableI3D");
	if(!TestPointer(wglSetGammaTableI3D)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef BOOL (GLE_FUNCPTR * PFNWGLENABLEGENLOCKI3DPROC)(HDC hDC);
typedef BOOL (GLE_FUNCPTR * PFNWGLDISABLEGENLOCKI3DPROC)(HDC hDC);
typedef BOOL (GLE_FUNCPTR * PFNWGLISENABLEDGENLOCKI3DPROC)(HDC hDC, BOOL *pFlag);
typedef BOOL (GLE_FUNCPTR * PFNWGLGENLOCKSOURCEI3DPROC)(HDC hDC, UINT uSource);
typedef BOOL (GLE_FUNCPTR * PFNWGLGETGENLOCKSOURCEI3DPROC)(HDC hDC, UINT *uSource);
typedef BOOL (GLE_FUNCPTR * PFNWGLGENLOCKSOURCEEDGEI3DPROC)(HDC hDC, UINT uEdge);
typedef BOOL (GLE_FUNCPTR * PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)(HDC hDC, UINT *uEdge);
typedef BOOL (GLE_FUNCPTR * PFNWGLGENLOCKSAMPLERATEI3DPROC)(HDC hDC, UINT uRate);
typedef BOOL (GLE_FUNCPTR * PFNWGLGETGENLOCKSAMPLERATEI3DPROC)(HDC hDC, UINT *uRate);
typedef BOOL (GLE_FUNCPTR * PFNWGLGENLOCKSOURCEDELAYI3DPROC)(HDC hDC, UINT uDelay);
typedef BOOL (GLE_FUNCPTR * PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)(HDC hDC, UINT *uDelay);
typedef BOOL (GLE_FUNCPTR * PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)(HDC hDC, UINT *uMaxLineDelay, UINT *uMaxPixelDelay);

PFNWGLENABLEGENLOCKI3DPROC wglEnableGenlockI3D;
PFNWGLDISABLEGENLOCKI3DPROC wglDisableGenlockI3D;
PFNWGLISENABLEDGENLOCKI3DPROC wglIsEnabledGenlockI3D;
PFNWGLGENLOCKSOURCEI3DPROC wglGenlockSourceI3D;
PFNWGLGETGENLOCKSOURCEI3DPROC wglGetGenlockSourceI3D;
PFNWGLGENLOCKSOURCEEDGEI3DPROC wglGenlockSourceEdgeI3D;
PFNWGLGETGENLOCKSOURCEEDGEI3DPROC wglGetGenlockSourceEdgeI3D;
PFNWGLGENLOCKSAMPLERATEI3DPROC wglGenlockSampleRateI3D;
PFNWGLGETGENLOCKSAMPLERATEI3DPROC wglGetGenlockSampleRateI3D;
PFNWGLGENLOCKSOURCEDELAYI3DPROC wglGenlockSourceDelayI3D;
PFNWGLGETGENLOCKSOURCEDELAYI3DPROC wglGetGenlockSourceDelayI3D;
PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC wglQueryGenlockMaxSourceDelayI3D;

static int wgleIntLoad_I3D_genlock()
{
	int bIsLoaded = 1;
	wglEnableGenlockI3D = (PFNWGLENABLEGENLOCKI3DPROC)gleIntGetProcAddress("wglEnableGenlockI3D");
	if(!TestPointer(wglEnableGenlockI3D)) bIsLoaded = 0;
	wglDisableGenlockI3D = (PFNWGLDISABLEGENLOCKI3DPROC)gleIntGetProcAddress("wglDisableGenlockI3D");
	if(!TestPointer(wglDisableGenlockI3D)) bIsLoaded = 0;
	wglIsEnabledGenlockI3D = (PFNWGLISENABLEDGENLOCKI3DPROC)gleIntGetProcAddress("wglIsEnabledGenlockI3D");
	if(!TestPointer(wglIsEnabledGenlockI3D)) bIsLoaded = 0;
	wglGenlockSourceI3D = (PFNWGLGENLOCKSOURCEI3DPROC)gleIntGetProcAddress("wglGenlockSourceI3D");
	if(!TestPointer(wglGenlockSourceI3D)) bIsLoaded = 0;
	wglGetGenlockSourceI3D = (PFNWGLGETGENLOCKSOURCEI3DPROC)gleIntGetProcAddress("wglGetGenlockSourceI3D");
	if(!TestPointer(wglGetGenlockSourceI3D)) bIsLoaded = 0;
	wglGenlockSourceEdgeI3D = (PFNWGLGENLOCKSOURCEEDGEI3DPROC)gleIntGetProcAddress("wglGenlockSourceEdgeI3D");
	if(!TestPointer(wglGenlockSourceEdgeI3D)) bIsLoaded = 0;
	wglGetGenlockSourceEdgeI3D = (PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)gleIntGetProcAddress("wglGetGenlockSourceEdgeI3D");
	if(!TestPointer(wglGetGenlockSourceEdgeI3D)) bIsLoaded = 0;
	wglGenlockSampleRateI3D = (PFNWGLGENLOCKSAMPLERATEI3DPROC)gleIntGetProcAddress("wglGenlockSampleRateI3D");
	if(!TestPointer(wglGenlockSampleRateI3D)) bIsLoaded = 0;
	wglGetGenlockSampleRateI3D = (PFNWGLGETGENLOCKSAMPLERATEI3DPROC)gleIntGetProcAddress("wglGetGenlockSampleRateI3D");
	if(!TestPointer(wglGetGenlockSampleRateI3D)) bIsLoaded = 0;
	wglGenlockSourceDelayI3D = (PFNWGLGENLOCKSOURCEDELAYI3DPROC)gleIntGetProcAddress("wglGenlockSourceDelayI3D");
	if(!TestPointer(wglGenlockSourceDelayI3D)) bIsLoaded = 0;
	wglGetGenlockSourceDelayI3D = (PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)gleIntGetProcAddress("wglGetGenlockSourceDelayI3D");
	if(!TestPointer(wglGetGenlockSourceDelayI3D)) bIsLoaded = 0;
	wglQueryGenlockMaxSourceDelayI3D = (PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)gleIntGetProcAddress("wglQueryGenlockMaxSourceDelayI3D");
	if(!TestPointer(wglQueryGenlockMaxSourceDelayI3D)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef LPVOID (GLE_FUNCPTR * PFNWGLCREATEIMAGEBUFFERI3DPROC)(HDC hDC, DWORD dwSize, UINT uFlags);
typedef BOOL (GLE_FUNCPTR * PFNWGLDESTROYIMAGEBUFFERI3DPROC)(HDC hDC, LPVOID pAddress);
typedef BOOL (GLE_FUNCPTR * PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC)(HDC hDC, const HANDLE *pEvent, const LPVOID *pAddress, const DWORD *pSize, UINT count);
typedef BOOL (GLE_FUNCPTR * PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC)(HDC hDC, const LPVOID *pAddress, UINT count);

PFNWGLCREATEIMAGEBUFFERI3DPROC wglCreateImageBufferI3D;
PFNWGLDESTROYIMAGEBUFFERI3DPROC wglDestroyImageBufferI3D;
PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC wglAssociateImageBufferEventsI3D;
PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC wglReleaseImageBufferEventsI3D;

static int wgleIntLoad_I3D_image_buffer()
{
	int bIsLoaded = 1;
	wglCreateImageBufferI3D = (PFNWGLCREATEIMAGEBUFFERI3DPROC)gleIntGetProcAddress("wglCreateImageBufferI3D");
	if(!TestPointer(wglCreateImageBufferI3D)) bIsLoaded = 0;
	wglDestroyImageBufferI3D = (PFNWGLDESTROYIMAGEBUFFERI3DPROC)gleIntGetProcAddress("wglDestroyImageBufferI3D");
	if(!TestPointer(wglDestroyImageBufferI3D)) bIsLoaded = 0;
	wglAssociateImageBufferEventsI3D = (PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC)gleIntGetProcAddress("wglAssociateImageBufferEventsI3D");
	if(!TestPointer(wglAssociateImageBufferEventsI3D)) bIsLoaded = 0;
	wglReleaseImageBufferEventsI3D = (PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC)gleIntGetProcAddress("wglReleaseImageBufferEventsI3D");
	if(!TestPointer(wglReleaseImageBufferEventsI3D)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef BOOL (GLE_FUNCPTR * PFNWGLENABLEFRAMELOCKI3DPROC)();
typedef BOOL (GLE_FUNCPTR * PFNWGLDISABLEFRAMELOCKI3DPROC)();
typedef BOOL (GLE_FUNCPTR * PFNWGLISENABLEDFRAMELOCKI3DPROC)(BOOL *pFlag);
typedef BOOL (GLE_FUNCPTR * PFNWGLQUERYFRAMELOCKMASTERI3DPROC)(BOOL *pFlag);

PFNWGLENABLEFRAMELOCKI3DPROC wglEnableFrameLockI3D;
PFNWGLDISABLEFRAMELOCKI3DPROC wglDisableFrameLockI3D;
PFNWGLISENABLEDFRAMELOCKI3DPROC wglIsEnabledFrameLockI3D;
PFNWGLQUERYFRAMELOCKMASTERI3DPROC wglQueryFrameLockMasterI3D;

static int wgleIntLoad_I3D_swap_frame_lock()
{
	int bIsLoaded = 1;
	wglEnableFrameLockI3D = (PFNWGLENABLEFRAMELOCKI3DPROC)gleIntGetProcAddress("wglEnableFrameLockI3D");
	if(!TestPointer(wglEnableFrameLockI3D)) bIsLoaded = 0;
	wglDisableFrameLockI3D = (PFNWGLDISABLEFRAMELOCKI3DPROC)gleIntGetProcAddress("wglDisableFrameLockI3D");
	if(!TestPointer(wglDisableFrameLockI3D)) bIsLoaded = 0;
	wglIsEnabledFrameLockI3D = (PFNWGLISENABLEDFRAMELOCKI3DPROC)gleIntGetProcAddress("wglIsEnabledFrameLockI3D");
	if(!TestPointer(wglIsEnabledFrameLockI3D)) bIsLoaded = 0;
	wglQueryFrameLockMasterI3D = (PFNWGLQUERYFRAMELOCKMASTERI3DPROC)gleIntGetProcAddress("wglQueryFrameLockMasterI3D");
	if(!TestPointer(wglQueryFrameLockMasterI3D)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef BOOL (GLE_FUNCPTR * PFNWGLENUMGPUSNVPROC)(UINT iGpuIndex, HGPUNV *phGpu);
typedef BOOL (GLE_FUNCPTR * PFNWGLENUMGPUDEVICESNVPROC)(HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice);
typedef HDC (GLE_FUNCPTR * PFNWGLCREATEAFFINITYDCNVPROC)(const HGPUNV *phGpuList);
typedef BOOL (GLE_FUNCPTR * PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)(HDC hAffinityDC, UINT iGpuIndex, HGPUNV *hGpu);
typedef BOOL (GLE_FUNCPTR * PFNWGLDELETEDCNVPROC)(HDC hdc);

PFNWGLENUMGPUSNVPROC wglEnumGpusNV;
PFNWGLENUMGPUDEVICESNVPROC wglEnumGpuDevicesNV;
PFNWGLCREATEAFFINITYDCNVPROC wglCreateAffinityDCNV;
PFNWGLENUMGPUSFROMAFFINITYDCNVPROC wglEnumGpusFromAffinityDCNV;
PFNWGLDELETEDCNVPROC wglDeleteDCNV;

static int wgleIntLoad_NV_gpu_affinity()
{
	int bIsLoaded = 1;
	wglEnumGpusNV = (PFNWGLENUMGPUSNVPROC)gleIntGetProcAddress("wglEnumGpusNV");
	if(!TestPointer(wglEnumGpusNV)) bIsLoaded = 0;
	wglEnumGpuDevicesNV = (PFNWGLENUMGPUDEVICESNVPROC)gleIntGetProcAddress("wglEnumGpuDevicesNV");
	if(!TestPointer(wglEnumGpuDevicesNV)) bIsLoaded = 0;
	wglCreateAffinityDCNV = (PFNWGLCREATEAFFINITYDCNVPROC)gleIntGetProcAddress("wglCreateAffinityDCNV");
	if(!TestPointer(wglCreateAffinityDCNV)) bIsLoaded = 0;
	wglEnumGpusFromAffinityDCNV = (PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)gleIntGetProcAddress("wglEnumGpusFromAffinityDCNV");
	if(!TestPointer(wglEnumGpusFromAffinityDCNV)) bIsLoaded = 0;
	wglDeleteDCNV = (PFNWGLDELETEDCNVPROC)gleIntGetProcAddress("wglDeleteDCNV");
	if(!TestPointer(wglDeleteDCNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef int (GLE_FUNCPTR * PFNWGLENUMERATEVIDEODEVICESNVPROC)(HDC hDC, HVIDEOOUTPUTDEVICENV *phDeviceList);
typedef BOOL (GLE_FUNCPTR * PFNWGLBINDVIDEODEVICENVPROC)(HDC hDC, unsigned int uVideoSlot, HVIDEOOUTPUTDEVICENV hVideoDevice, const int *piAttribList);
typedef BOOL (GLE_FUNCPTR * PFNWGLQUERYCURRENTCONTEXTNVPROC)(int iAttribute, int *piValue);

PFNWGLENUMERATEVIDEODEVICESNVPROC wglEnumerateVideoDevicesNV;
PFNWGLBINDVIDEODEVICENVPROC wglBindVideoDeviceNV;
PFNWGLQUERYCURRENTCONTEXTNVPROC wglQueryCurrentContextNV;

static int wgleIntLoad_NV_present_video()
{
	int bIsLoaded = 1;
	wglEnumerateVideoDevicesNV = (PFNWGLENUMERATEVIDEODEVICESNVPROC)gleIntGetProcAddress("wglEnumerateVideoDevicesNV");
	if(!TestPointer(wglEnumerateVideoDevicesNV)) bIsLoaded = 0;
	wglBindVideoDeviceNV = (PFNWGLBINDVIDEODEVICENVPROC)gleIntGetProcAddress("wglBindVideoDeviceNV");
	if(!TestPointer(wglBindVideoDeviceNV)) bIsLoaded = 0;
	wglQueryCurrentContextNV = (PFNWGLQUERYCURRENTCONTEXTNVPROC)gleIntGetProcAddress("wglQueryCurrentContextNV");
	if(!TestPointer(wglQueryCurrentContextNV)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef BOOL (GLE_FUNCPTR * PFNWGLJOINSWAPGROUPNVPROC)(HDC hDC, GLuint group);
typedef BOOL (GLE_FUNCPTR * PFNWGLBINDSWAPBARRIERNVPROC)(GLuint group, GLuint barrier);
typedef BOOL (GLE_FUNCPTR * PFNWGLQUERYSWAPGROUPNVPROC)(HDC hDC, GLuint *group, GLuint *barrier);
typedef BOOL (GLE_FUNCPTR * PFNWGLQUERYMAXSWAPGROUPSNVPROC)(HDC hDC, GLuint *maxGroups, GLuint *maxBarriers);
typedef BOOL (GLE_FUNCPTR * PFNWGLQUERYFRAMECOUNTNVPROC)(HDC hDC, GLuint *count);
typedef BOOL (GLE_FUNCPTR * PFNWGLRESETFRAMECOUNTNVPROC)(HDC hDC);

PFNWGLJOINSWAPGROUPNVPROC wglJoinSwapGroupNV;
PFNWGLBINDSWAPBARRIERNVPROC wglBindSwapBarrierNV;
PFNWGLQUERYSWAPGROUPNVPROC wglQuerySwapGroupNV;
PFNWGLQUERYMAXSWAPGROUPSNVPROC wglQueryMaxSwapGroupsNV;
PFNWGLQUERYFRAMECOUNTNVPROC wglQueryFrameCountNV;
PFNWGLRESETFRAMECOUNTNVPROC wglResetFrameCountNV;

static int wgleIntLoad_NV_swap_group()
{
	int bIsLoaded = 1;
	wglJoinSwapGroupNV = (PFNWGLJOINSWAPGROUPNVPROC)gleIntGetProcAddress("wglJoinSwapGroupNV");
	if(!TestPointer(wglJoinSwapGroupNV)) bIsLoaded = 0;
	wglBindSwapBarrierNV = (PFNWGLBINDSWAPBARRIERNVPROC)gleIntGetProcAddress("wglBindSwapBarrierNV");
	if(!TestPointer(wglBindSwapBarrierNV)) bIsLoaded = 0;
	wglQuerySwapGroupNV = (PFNWGLQUERYSWAPGROUPNVPROC)gleIntGetProcAddress("wglQuerySwapGroupNV");
	if(!TestPointer(wglQuerySwapGroupNV)) bIsLoaded = 0;
	wglQueryMaxSwapGroupsNV = (PFNWGLQUERYMAXSWAPGROUPSNVPROC)gleIntGetProcAddress("wglQueryMaxSwapGroupsNV");
	if(!TestPointer(wglQueryMaxSwapGroupsNV)) bIsLoaded = 0;
	wglQueryFrameCountNV = (PFNWGLQUERYFRAMECOUNTNVPROC)gleIntGetProcAddress("wglQueryFrameCountNV");
	if(!TestPointer(wglQueryFrameCountNV)) bIsLoaded = 0;
	wglResetFrameCountNV = (PFNWGLRESETFRAMECOUNTNVPROC)gleIntGetProcAddress("wglResetFrameCountNV");
	if(!TestPointer(wglResetFrameCountNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef BOOL (GLE_FUNCPTR * PFNWGLGETVIDEODEVICENVPROC)(HDC hDC, int numDevices, HPVIDEODEV *hVideoDevice);
typedef BOOL (GLE_FUNCPTR * PFNWGLRELEASEVIDEODEVICENVPROC)(HPVIDEODEV hVideoDevice);
typedef BOOL (GLE_FUNCPTR * PFNWGLBINDVIDEOIMAGENVPROC)(HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer);
typedef BOOL (GLE_FUNCPTR * PFNWGLRELEASEVIDEOIMAGENVPROC)(HPBUFFERARB hPbuffer, int iVideoBuffer);
typedef BOOL (GLE_FUNCPTR * PFNWGLSENDPBUFFERTOVIDEONVPROC)(HPBUFFERARB hPbuffer, int iBufferType, unsigned long *pulCounterPbuffer, BOOL bBlock);
typedef BOOL (GLE_FUNCPTR * PFNWGLGETVIDEOINFONVPROC)(HPVIDEODEV hpVideoDevice, unsigned long *pulCounterOutputPbuffer, unsigned long *pulCounterOutputVideo);

PFNWGLGETVIDEODEVICENVPROC wglGetVideoDeviceNV;
PFNWGLRELEASEVIDEODEVICENVPROC wglReleaseVideoDeviceNV;
PFNWGLBINDVIDEOIMAGENVPROC wglBindVideoImageNV;
PFNWGLRELEASEVIDEOIMAGENVPROC wglReleaseVideoImageNV;
PFNWGLSENDPBUFFERTOVIDEONVPROC wglSendPbufferToVideoNV;
PFNWGLGETVIDEOINFONVPROC wglGetVideoInfoNV;

static int wgleIntLoad_NV_video_out()
{
	int bIsLoaded = 1;
	wglGetVideoDeviceNV = (PFNWGLGETVIDEODEVICENVPROC)gleIntGetProcAddress("wglGetVideoDeviceNV");
	if(!TestPointer(wglGetVideoDeviceNV)) bIsLoaded = 0;
	wglReleaseVideoDeviceNV = (PFNWGLRELEASEVIDEODEVICENVPROC)gleIntGetProcAddress("wglReleaseVideoDeviceNV");
	if(!TestPointer(wglReleaseVideoDeviceNV)) bIsLoaded = 0;
	wglBindVideoImageNV = (PFNWGLBINDVIDEOIMAGENVPROC)gleIntGetProcAddress("wglBindVideoImageNV");
	if(!TestPointer(wglBindVideoImageNV)) bIsLoaded = 0;
	wglReleaseVideoImageNV = (PFNWGLRELEASEVIDEOIMAGENVPROC)gleIntGetProcAddress("wglReleaseVideoImageNV");
	if(!TestPointer(wglReleaseVideoImageNV)) bIsLoaded = 0;
	wglSendPbufferToVideoNV = (PFNWGLSENDPBUFFERTOVIDEONVPROC)gleIntGetProcAddress("wglSendPbufferToVideoNV");
	if(!TestPointer(wglSendPbufferToVideoNV)) bIsLoaded = 0;
	wglGetVideoInfoNV = (PFNWGLGETVIDEOINFONVPROC)gleIntGetProcAddress("wglGetVideoInfoNV");
	if(!TestPointer(wglGetVideoInfoNV)) bIsLoaded = 0;
	return bIsLoaded;
}
StrToExtMap wgleIntExtensionMap[] = {
	{"WGL_3DFX_multisample", &wglext_3DFX_multisample, NULL},
	{"WGL_3DL_stereo_control", &wglext_3DL_stereo_control, wgleIntLoad_3DL_stereo_control},
	{"WGL_AMD_gpu_association", &wglext_AMD_gpu_association, wgleIntLoad_AMD_gpu_association},
	{"WGL_ARB_buffer_region", &wglext_ARB_buffer_region, wgleIntLoad_ARB_buffer_region},
	{"WGL_ARB_create_context", &wglext_ARB_create_context, wgleIntLoad_ARB_create_context},
	{"WGL_ARB_create_context_profile", &wglext_ARB_create_context_profile, NULL},
	{"WGL_ARB_extensions_string", &wglext_ARB_extensions_string, wgleIntLoad_ARB_extensions_string},
	{"WGL_ARB_make_current_read", &wglext_ARB_make_current_read, wgleIntLoad_ARB_make_current_read},
	{"WGL_ARB_multisample", &wglext_ARB_multisample, NULL},
	{"WGL_ARB_pbuffer", &wglext_ARB_pbuffer, wgleIntLoad_ARB_pbuffer},
	{"WGL_ARB_pixel_format", &wglext_ARB_pixel_format, wgleIntLoad_ARB_pixel_format},
	{"WGL_ARB_pixel_format_float", &wglext_ARB_pixel_format_float, NULL},
	{"WGL_ARB_render_texture", &wglext_ARB_render_texture, wgleIntLoad_ARB_render_texture},
	{"WGL_ATI_pixel_format_float", &wglext_ATI_pixel_format_float, NULL},
	{"WGL_EXT_depth_float", &wglext_EXT_depth_float, NULL},
	{"WGL_EXT_framebuffer_sRGB", &wglext_EXT_framebuffer_sRGB, NULL},
	{"WGL_EXT_make_current_read", &wglext_EXT_make_current_read, wgleIntLoad_EXT_make_current_read},
	{"WGL_EXT_multisample", &wglext_EXT_multisample, NULL},
	{"WGL_EXT_pbuffer", &wglext_EXT_pbuffer, wgleIntLoad_EXT_pbuffer},
	{"WGL_EXT_pixel_format", &wglext_EXT_pixel_format, wgleIntLoad_EXT_pixel_format},
	{"WGL_EXT_pixel_format_packed_float", &wglext_EXT_pixel_format_packed_float, NULL},
	{"WGL_I3D_digital_video_control", &wglext_I3D_digital_video_control, wgleIntLoad_I3D_digital_video_control},
	{"WGL_I3D_gamma", &wglext_I3D_gamma, wgleIntLoad_I3D_gamma},
	{"WGL_I3D_genlock", &wglext_I3D_genlock, wgleIntLoad_I3D_genlock},
	{"WGL_I3D_image_buffer", &wglext_I3D_image_buffer, wgleIntLoad_I3D_image_buffer},
	{"WGL_I3D_swap_frame_lock", &wglext_I3D_swap_frame_lock, wgleIntLoad_I3D_swap_frame_lock},
	{"WGL_NV_float_buffer", &wglext_NV_float_buffer, NULL},
	{"WGL_NV_gpu_affinity", &wglext_NV_gpu_affinity, wgleIntLoad_NV_gpu_affinity},
	{"WGL_NV_present_video", &wglext_NV_present_video, wgleIntLoad_NV_present_video},
	{"WGL_NV_render_depth_texture", &wglext_NV_render_depth_texture, NULL},
	{"WGL_NV_render_texture_rectangle", &wglext_NV_render_texture_rectangle, NULL},
	{"WGL_NV_swap_group", &wglext_NV_swap_group, wgleIntLoad_NV_swap_group},
	{"WGL_NV_video_out", &wglext_NV_video_out, wgleIntLoad_NV_video_out},
};

int wgleIntExtensionMapSize = 33;



void wgleIntLoadBaseFuncs()
{
	int bIsLoaded = 1; //Unimportant here.
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)gleIntGetProcAddress("wglGetExtensionsStringARB");
	if(!TestPointer(wglGetExtensionsStringARB)) bIsLoaded = 0;
}
