#ifndef GLX_EXTS_H
#define GLX_EXTS_H


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

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


extern int glXext_ARB_get_proc_address;
extern int glXext_ARB_multisample;
extern int glXext_ARB_vertex_buffer_object;
extern int glXext_ARB_fbconfig_float;
extern int glXext_ARB_framebuffer_sRGB;
extern int glXext_ARB_create_context;
extern int glXext_ARB_create_context_profile;
extern int glXext_ARB_create_context_robustness;
extern int glXext_SGIS_multisample;
extern int glXext_EXT_visual_info;
extern int glXext_SGI_swap_control;
extern int glXext_SGI_video_sync;
extern int glXext_SGI_make_current_read;
extern int glXext_EXT_visual_rating;
extern int glXext_EXT_import_context;
extern int glXext_SGIX_fbconfig;
extern int glXext_SGIX_pbuffer;
extern int glXext_SGI_cushion;
extern int glXext_SGIX_video_resize;
extern int glXext_SGIX_swap_group;
extern int glXext_SGIX_swap_barrier;
extern int glXext_SGIS_blended_overlay;
extern int glXext_SGIS_shared_multisample;
extern int glXext_SUN_get_transparent_index;
extern int glXext_3DFX_multisample;
extern int glXext_MESA_copy_sub_buffer;
extern int glXext_MESA_pixmap_colormap;
extern int glXext_MESA_release_buffers;
extern int glXext_MESA_set_3dfx_mode;
extern int glXext_SGIX_visual_select_group;
extern int glXext_OML_swap_method;
extern int glXext_OML_sync_control;
extern int glXext_NV_float_buffer;
extern int glXext_MESA_agp_offset;
extern int glXext_EXT_fbconfig_packed_float;
extern int glXext_EXT_framebuffer_sRGB;
extern int glXext_EXT_texture_from_pixmap;
extern int glXext_NV_present_video;
extern int glXext_NV_video_out;
extern int glXext_NV_swap_group;
extern int glXext_NV_video_capture;
extern int glXext_EXT_swap_control;
extern int glXext_NV_copy_image;
extern int glXext_INTEL_swap_event;
extern int glXext_NV_multisample_coverage;
extern int glXext_AMD_gpu_association;
extern int glXext_EXT_create_context_es2_profile;


/******************************
* Version: 1.3
******************************/

#define GLX_WINDOW_BIT 0x00000001
#define GLX_PIXMAP_BIT 0x00000002
#define GLX_PBUFFER_BIT 0x00000004
#define GLX_RGBA_BIT 0x00000001
#define GLX_COLOR_INDEX_BIT 0x00000002
#define GLX_PBUFFER_CLOBBER_MASK 0x08000000
#define GLX_FRONT_LEFT_BUFFER_BIT 0x00000001
#define GLX_FRONT_RIGHT_BUFFER_BIT 0x00000002
#define GLX_BACK_LEFT_BUFFER_BIT 0x00000004
#define GLX_BACK_RIGHT_BUFFER_BIT 0x00000008
#define GLX_AUX_BUFFERS_BIT 0x00000010
#define GLX_DEPTH_BUFFER_BIT 0x00000020
#define GLX_STENCIL_BUFFER_BIT 0x00000040
#define GLX_ACCUM_BUFFER_BIT 0x00000080
#define GLX_CONFIG_CAVEAT 0x20
#define GLX_X_VISUAL_TYPE 0x22
#define GLX_TRANSPARENT_TYPE 0x23
#define GLX_TRANSPARENT_INDEX_VALUE 0x24
#define GLX_TRANSPARENT_RED_VALUE 0x25
#define GLX_TRANSPARENT_GREEN_VALUE 0x26
#define GLX_TRANSPARENT_BLUE_VALUE 0x27
#define GLX_TRANSPARENT_ALPHA_VALUE 0x28
#define GLX_DONT_CARE 0xFFFFFFFF
#define GLX_NONE 0x8000
#define GLX_SLOW_CONFIG 0x8001
#define GLX_TRUE_COLOR 0x8002
#define GLX_DIRECT_COLOR 0x8003
#define GLX_PSEUDO_COLOR 0x8004
#define GLX_STATIC_COLOR 0x8005
#define GLX_GRAY_SCALE 0x8006
#define GLX_STATIC_GRAY 0x8007
#define GLX_TRANSPARENT_RGB 0x8008
#define GLX_TRANSPARENT_INDEX 0x8009
#define GLX_VISUAL_ID 0x800B
#define GLX_SCREEN 0x800C
#define GLX_NON_CONFORMANT_CONFIG 0x800D
#define GLX_DRAWABLE_TYPE 0x8010
#define GLX_RENDER_TYPE 0x8011
#define GLX_X_RENDERABLE 0x8012
#define GLX_FBCONFIG_ID 0x8013
#define GLX_RGBA_TYPE 0x8014
#define GLX_COLOR_INDEX_TYPE 0x8015
#define GLX_MAX_PBUFFER_WIDTH 0x8016
#define GLX_MAX_PBUFFER_HEIGHT 0x8017
#define GLX_MAX_PBUFFER_PIXELS 0x8018
#define GLX_PRESERVED_CONTENTS 0x801B
#define GLX_LARGEST_PBUFFER 0x801C
#define GLX_WIDTH 0x801D
#define GLX_HEIGHT 0x801E
#define GLX_EVENT_MASK 0x801F
#define GLX_DAMAGED 0x8020
#define GLX_SAVED 0x8021
#define GLX_WINDOW 0x8022
#define GLX_PBUFFER 0x8023
#define GLX_PBUFFER_HEIGHT 0x8040
#define GLX_PBUFFER_WIDTH 0x8041


/******************************
* Version: 1.4
******************************/

#define GLX_SAMPLE_BUFFERS 100000
#define GLX_SAMPLES 100001




/******************************
* Extension: GLX_3DFX_multisample
******************************/

#define GLX_SAMPLE_BUFFERS_3DFX 0x8050
#define GLX_SAMPLES_3DFX 0x8051


/******************************
* Extension: GLX_AMD_gpu_association
******************************/

#define GLX_GPU_VENDOR_AMD 0x1F00
#define GLX_GPU_RENDERER_STRING_AMD 0x1F01
#define GLX_GPU_OPENGL_VERSION_STRING_AMD 0x1F02
#define GLX_GPU_FASTEST_TARGET_GPUS_AMD 0x21A2
#define GLX_GPU_RAM_AMD 0x21A3
#define GLX_GPU_CLOCK_AMD 0x21A4
#define GLX_GPU_NUM_PIPES_AMD 0x21A5
#define GLX_GPU_NUM_SIMD_AMD 0x21A6
#define GLX_GPU_NUM_RB_AMD 0x21A7
#define GLX_GPU_NUM_SPI_AMD 0x21A8


/******************************
* Extension: GLX_ARB_create_context
******************************/

#define GLX_CONTEXT_DEBUG_BIT_ARB 0x00000001
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
#define GLX_CONTEXT_FLAGS_ARB 0x2094


#ifndef GLX_ARB_create_context
#define GLX_ARB_create_context 1

typedef GLXContext (GLE_FUNCPTR * PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);

extern PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
#endif /*GLX_ARB_create_context*/

/******************************
* Extension: GLX_ARB_create_context_profile
******************************/

#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126


/******************************
* Extension: GLX_ARB_create_context_robustness
******************************/

#define GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB 0x00000004
#define GLX_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#define GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define GLX_NO_RESET_NOTIFICATION_ARB 0x8261


/******************************
* Extension: GLX_ARB_fbconfig_float
******************************/

#define GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#define GLX_RGBA_FLOAT_BIT_ARB 0x00000004


/******************************
* Extension: GLX_ARB_framebuffer_sRGB
******************************/

#define GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2


/******************************
* Extension: GLX_ARB_get_proc_address
******************************/

#ifndef GLX_ARB_get_proc_address
#define GLX_ARB_get_proc_address 1

typedef __GLXextFuncPtr (GLE_FUNCPTR * PFNGLXGETPROCADDRESSARBPROC)(const GLubyte *procName);

extern PFNGLXGETPROCADDRESSARBPROC glXGetProcAddressARB;
#endif /*GLX_ARB_get_proc_address*/

/******************************
* Extension: GLX_ARB_multisample
******************************/

#define GLX_SAMPLE_BUFFERS_ARB 100000
#define GLX_SAMPLES_ARB 100001


/******************************
* Extension: GLX_ARB_vertex_buffer_object
******************************/

#define GLX_CONTEXT_ALLOW_BUFFER_BYTE_ORDER_MISMATCH_ARB 0x2095


/******************************
* Extension: GLX_EXT_create_context_es2_profile
******************************/

#define GLX_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000004


/******************************
* Extension: GLX_EXT_fbconfig_packed_float
******************************/

#define GLX_RGBA_UNSIGNED_FLOAT_TYPE_EXT 0x20B1
#define GLX_RGBA_UNSIGNED_FLOAT_BIT_EXT 0x00000008


/******************************
* Extension: GLX_EXT_framebuffer_sRGB
******************************/

#define GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT 0x20B2


/******************************
* Extension: GLX_EXT_import_context
******************************/

#define GLX_SHARE_CONTEXT_EXT 0x800A
#define GLX_VISUAL_ID_EXT 0x800B
#define GLX_SCREEN_EXT 0x800C


#ifndef GLX_EXT_import_context
#define GLX_EXT_import_context 1

typedef Display * (GLE_FUNCPTR * PFNGLXGETCURRENTDISPLAYEXTPROC)();
typedef int (GLE_FUNCPTR * PFNGLXQUERYCONTEXTINFOEXTPROC)(Display *dpy, GLXContext context, int attribute, int *value);
typedef GLXContextID (GLE_FUNCPTR * PFNGLXGETCONTEXTIDEXTPROC)(const GLXContext context);
typedef GLXContext (GLE_FUNCPTR * PFNGLXIMPORTCONTEXTEXTPROC)(Display *dpy, GLXContextID contextID);
typedef void (GLE_FUNCPTR * PFNGLXFREECONTEXTEXTPROC)(Display *dpy, GLXContext context);

extern PFNGLXGETCURRENTDISPLAYEXTPROC glXGetCurrentDisplayEXT;
extern PFNGLXQUERYCONTEXTINFOEXTPROC glXQueryContextInfoEXT;
extern PFNGLXGETCONTEXTIDEXTPROC glXGetContextIDEXT;
extern PFNGLXIMPORTCONTEXTEXTPROC glXImportContextEXT;
extern PFNGLXFREECONTEXTEXTPROC glXFreeContextEXT;
#endif /*GLX_EXT_import_context*/

/******************************
* Extension: GLX_EXT_swap_control
******************************/

#define GLX_SWAP_INTERVAL_EXT 0x20F1
#define GLX_MAX_SWAP_INTERVAL_EXT 0x20F2


#ifndef GLX_EXT_swap_control
#define GLX_EXT_swap_control 1

typedef int (GLE_FUNCPTR * PFNGLXSWAPINTERVALEXTPROC)(Display *dpy, GLXDrawable drawable, int interval);

extern PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT;
#endif /*GLX_EXT_swap_control*/

/******************************
* Extension: GLX_EXT_texture_from_pixmap
******************************/

#define GLX_TEXTURE_1D_BIT_EXT 0x00000001
#define GLX_TEXTURE_2D_BIT_EXT 0x00000002
#define GLX_TEXTURE_RECTANGLE_BIT_EXT 0x00000004
#define GLX_BIND_TO_TEXTURE_RGB_EXT 0x20D0
#define GLX_BIND_TO_TEXTURE_RGBA_EXT 0x20D1
#define GLX_BIND_TO_MIPMAP_TEXTURE_EXT 0x20D2
#define GLX_BIND_TO_TEXTURE_TARGETS_EXT 0x20D3
#define GLX_Y_INVERTED_EXT 0x20D4
#define GLX_TEXTURE_FORMAT_EXT 0x20D5
#define GLX_TEXTURE_TARGET_EXT 0x20D6
#define GLX_MIPMAP_TEXTURE_EXT 0x20D7
#define GLX_TEXTURE_FORMAT_NONE_EXT 0x20D8
#define GLX_TEXTURE_FORMAT_RGB_EXT 0x20D9
#define GLX_TEXTURE_FORMAT_RGBA_EXT 0x20DA
#define GLX_TEXTURE_1D_EXT 0x20DB
#define GLX_TEXTURE_2D_EXT 0x20DC
#define GLX_TEXTURE_RECTANGLE_EXT 0x20DD
#define GLX_FRONT_LEFT_EXT 0x20DE
#define GLX_FRONT_RIGHT_EXT 0x20DF
#define GLX_BACK_LEFT_EXT 0x20E0
#define GLX_BACK_RIGHT_EXT 0x20E1
#define GLX_FRONT_EXT 0x20DE /* GLX_FRONT_LEFT_EXT */
#define GLX_BACK_EXT 0x20E0 /* GLX_BACK_LEFT_EXT */
#define GLX_AUX0_EXT 0x20E2
#define GLX_AUX1_EXT 0x20E3
#define GLX_AUX2_EXT 0x20E4
#define GLX_AUX3_EXT 0x20E5
#define GLX_AUX4_EXT 0x20E6
#define GLX_AUX5_EXT 0x20E7
#define GLX_AUX6_EXT 0x20E8
#define GLX_AUX7_EXT 0x20E9
#define GLX_AUX8_EXT 0x20EA
#define GLX_AUX9_EXT 0x20EB


#ifndef GLX_EXT_texture_from_pixmap
#define GLX_EXT_texture_from_pixmap 1

typedef void (GLE_FUNCPTR * PFNGLXBINDTEXIMAGEEXTPROC)(Display *dpy, GLXDrawable drawable, int buffer, const int *attrib_list);
typedef void (GLE_FUNCPTR * PFNGLXRELEASETEXIMAGEEXTPROC)(Display *dpy, GLXDrawable drawable, int buffer);

extern PFNGLXBINDTEXIMAGEEXTPROC glXBindTexImageEXT;
extern PFNGLXRELEASETEXIMAGEEXTPROC glXReleaseTexImageEXT;
#endif /*GLX_EXT_texture_from_pixmap*/

/******************************
* Extension: GLX_EXT_visual_info
******************************/

#define GLX_X_VISUAL_TYPE_EXT 0x22
#define GLX_TRANSPARENT_TYPE_EXT 0x23
#define GLX_TRANSPARENT_INDEX_VALUE_EXT 0x24
#define GLX_TRANSPARENT_RED_VALUE_EXT 0x25
#define GLX_TRANSPARENT_GREEN_VALUE_EXT 0x26
#define GLX_TRANSPARENT_BLUE_VALUE_EXT 0x27
#define GLX_TRANSPARENT_ALPHA_VALUE_EXT 0x28
#define GLX_NONE_EXT 0x8000
#define GLX_TRUE_COLOR_EXT 0x8002
#define GLX_DIRECT_COLOR_EXT 0x8003
#define GLX_PSEUDO_COLOR_EXT 0x8004
#define GLX_STATIC_COLOR_EXT 0x8005
#define GLX_GRAY_SCALE_EXT 0x8006
#define GLX_STATIC_GRAY_EXT 0x8007
#define GLX_TRANSPARENT_RGB_EXT 0x8008
#define GLX_TRANSPARENT_INDEX_EXT 0x8009


/******************************
* Extension: GLX_EXT_visual_rating
******************************/

#define GLX_NONE_EXT 0x8000
#define GLX_VISUAL_CAVEAT_EXT 0x20
#define GLX_SLOW_VISUAL_EXT 0x8001
#define GLX_NON_CONFORMANT_VISUAL_EXT 0x800D


/******************************
* Extension: GLX_INTEL_swap_event
******************************/

#define GLX_BUFFER_SWAP_COMPLETE_INTEL_MASK 0x04000000
#define GLX_EXCHANGE_COMPLETE_INTEL 0x8180
#define GLX_COPY_COMPLETE_INTEL 0x8181
#define GLX_FLIP_COMPLETE_INTEL 0x8182


/******************************
* Extension: GLX_MESA_agp_offset
******************************/

#ifndef GLX_MESA_agp_offset
#define GLX_MESA_agp_offset 1

typedef unsigned int (GLE_FUNCPTR * PFNGLXGETAGPOFFSETMESAPROC)(const void *pointer);

extern PFNGLXGETAGPOFFSETMESAPROC glXGetAGPOffsetMESA;
#endif /*GLX_MESA_agp_offset*/

/******************************
* Extension: GLX_MESA_copy_sub_buffer
******************************/

#ifndef GLX_MESA_copy_sub_buffer
#define GLX_MESA_copy_sub_buffer 1

typedef void (GLE_FUNCPTR * PFNGLXCOPYSUBBUFFERMESAPROC)(Display *dpy, GLXDrawable drawable, int x, int y, int width, int height);

extern PFNGLXCOPYSUBBUFFERMESAPROC glXCopySubBufferMESA;
#endif /*GLX_MESA_copy_sub_buffer*/

/******************************
* Extension: GLX_MESA_pixmap_colormap
******************************/

#ifndef GLX_MESA_pixmap_colormap
#define GLX_MESA_pixmap_colormap 1

typedef GLXPixmap (GLE_FUNCPTR * PFNGLXCREATEGLXPIXMAPMESAPROC)(Display *dpy, XVisualInfo *visual, Pixmap pixmap, Colormap cmap);

extern PFNGLXCREATEGLXPIXMAPMESAPROC glXCreateGLXPixmapMESA;
#endif /*GLX_MESA_pixmap_colormap*/

/******************************
* Extension: GLX_MESA_release_buffers
******************************/

#ifndef GLX_MESA_release_buffers
#define GLX_MESA_release_buffers 1

typedef Bool (GLE_FUNCPTR * PFNGLXRELEASEBUFFERSMESAPROC)(Display *dpy, GLXDrawable drawable);

extern PFNGLXRELEASEBUFFERSMESAPROC glXReleaseBuffersMESA;
#endif /*GLX_MESA_release_buffers*/

/******************************
* Extension: GLX_MESA_set_3dfx_mode
******************************/

#define GLX_3DFX_WINDOW_MODE_MESA 0x1
#define GLX_3DFX_FULLSCREEN_MODE_MESA 0x2


#ifndef GLX_MESA_set_3dfx_mode
#define GLX_MESA_set_3dfx_mode 1

typedef Bool (GLE_FUNCPTR * PFNGLXSET3DFXMODEMESAPROC)(int mode);

extern PFNGLXSET3DFXMODEMESAPROC glXSet3DfxModeMESA;
#endif /*GLX_MESA_set_3dfx_mode*/

/******************************
* Extension: GLX_NV_copy_image
******************************/

#ifndef GLX_NV_copy_image
#define GLX_NV_copy_image 1

typedef void (GLE_FUNCPTR * PFNGLXCOPYIMAGESUBDATANVPROC)(Display *dpy, GLXContext srcCtx, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLXContext dstCtx, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);

extern PFNGLXCOPYIMAGESUBDATANVPROC glXCopyImageSubDataNV;
#endif /*GLX_NV_copy_image*/

/******************************
* Extension: GLX_NV_float_buffer
******************************/

#define GLX_FLOAT_COMPONENTS_NV 0x20B0


/******************************
* Extension: GLX_NV_multisample_coverage
******************************/

#define GLX_COVERAGE_SAMPLES_NV 100001
#define GLX_COLOR_SAMPLES_NV 0x20B3


/******************************
* Extension: GLX_NV_present_video
******************************/

#define GLX_NUM_VIDEO_SLOTS_NV 0x20F0


#ifndef GLX_NV_present_video
#define GLX_NV_present_video 1

typedef unsigned int * (GLE_FUNCPTR * PFNGLXENUMERATEVIDEODEVICESNVPROC)(Display *dpy, int screen, int *nelements);
typedef int (GLE_FUNCPTR * PFNGLXBINDVIDEODEVICENVPROC)(Display *dpy, unsigned int video_slot, unsigned int video_device, const int *attrib_list);

extern PFNGLXENUMERATEVIDEODEVICESNVPROC glXEnumerateVideoDevicesNV;
extern PFNGLXBINDVIDEODEVICENVPROC glXBindVideoDeviceNV;
#endif /*GLX_NV_present_video*/

/******************************
* Extension: GLX_NV_swap_group
******************************/

#ifndef GLX_NV_swap_group
#define GLX_NV_swap_group 1

typedef Bool (GLE_FUNCPTR * PFNGLXJOINSWAPGROUPNVPROC)(Display *dpy, GLXDrawable drawable, GLuint group);
typedef Bool (GLE_FUNCPTR * PFNGLXBINDSWAPBARRIERNVPROC)(Display *dpy, GLuint group, GLuint barrier);
typedef Bool (GLE_FUNCPTR * PFNGLXQUERYSWAPGROUPNVPROC)(Display *dpy, GLXDrawable drawable, GLuint *group, GLuint *barrier);
typedef Bool (GLE_FUNCPTR * PFNGLXQUERYMAXSWAPGROUPSNVPROC)(Display *dpy, int screen, GLuint *maxGroups, GLuint *maxBarriers);
typedef Bool (GLE_FUNCPTR * PFNGLXQUERYFRAMECOUNTNVPROC)(Display *dpy, int screen, GLuint *count);
typedef Bool (GLE_FUNCPTR * PFNGLXRESETFRAMECOUNTNVPROC)(Display *dpy, int screen);

extern PFNGLXJOINSWAPGROUPNVPROC glXJoinSwapGroupNV;
extern PFNGLXBINDSWAPBARRIERNVPROC glXBindSwapBarrierNV;
extern PFNGLXQUERYSWAPGROUPNVPROC glXQuerySwapGroupNV;
extern PFNGLXQUERYMAXSWAPGROUPSNVPROC glXQueryMaxSwapGroupsNV;
extern PFNGLXQUERYFRAMECOUNTNVPROC glXQueryFrameCountNV;
extern PFNGLXRESETFRAMECOUNTNVPROC glXResetFrameCountNV;
#endif /*GLX_NV_swap_group*/

/******************************
* Extension: GLX_NV_video_capture
******************************/

#define GLX_DEVICE_ID_NV 0x20CD
#define GLX_UNIQUE_ID_NV 0x20CE
#define GLX_NUM_VIDEO_CAPTURE_SLOTS_NV 0x20CF


#ifndef GLX_NV_video_capture
#define GLX_NV_video_capture 1

typedef int (GLE_FUNCPTR * PFNGLXBINDVIDEOCAPTUREDEVICENVPROC)(Display *dpy, unsigned int video_capture_slot, GLXVideoCaptureDeviceNV device);
typedef GLXVideoCaptureDeviceNV * (GLE_FUNCPTR * PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC)(Display *dpy, int screen, int *nelements);
typedef void (GLE_FUNCPTR * PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC)(Display *dpy, GLXVideoCaptureDeviceNV device);
typedef int (GLE_FUNCPTR * PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC)(Display *dpy, GLXVideoCaptureDeviceNV device, int attribute, int *value);
typedef void (GLE_FUNCPTR * PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC)(Display *dpy, GLXVideoCaptureDeviceNV device);

extern PFNGLXBINDVIDEOCAPTUREDEVICENVPROC glXBindVideoCaptureDeviceNV;
extern PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC glXEnumerateVideoCaptureDevicesNV;
extern PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC glXLockVideoCaptureDeviceNV;
extern PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC glXQueryVideoCaptureDeviceNV;
extern PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC glXReleaseVideoCaptureDeviceNV;
#endif /*GLX_NV_video_capture*/

/******************************
* Extension: GLX_NV_video_out
******************************/

#define GLX_VIDEO_OUT_COLOR_NV 0x20C3
#define GLX_VIDEO_OUT_ALPHA_NV 0x20C4
#define GLX_VIDEO_OUT_DEPTH_NV 0x20C5
#define GLX_VIDEO_OUT_COLOR_AND_ALPHA_NV 0x20C6
#define GLX_VIDEO_OUT_COLOR_AND_DEPTH_NV 0x20C7
#define GLX_VIDEO_OUT_FRAME_NV 0x20C8
#define GLX_VIDEO_OUT_FIELD_1_NV 0x20C9
#define GLX_VIDEO_OUT_FIELD_2_NV 0x20CA
#define GLX_VIDEO_OUT_STACKED_FIELDS_1_2_NV 0x20CB
#define GLX_VIDEO_OUT_STACKED_FIELDS_2_1_NV 0x20CC


/******************************
* Extension: GLX_OML_swap_method
******************************/

#define GLX_SWAP_METHOD_OML 0x8060
#define GLX_SWAP_EXCHANGE_OML 0x8061
#define GLX_SWAP_COPY_OML 0x8062
#define GLX_SWAP_UNDEFINED_OML 0x8063


/******************************
* Extension: GLX_OML_sync_control
******************************/

#ifndef GLX_OML_sync_control
#define GLX_OML_sync_control 1

typedef Bool (GLE_FUNCPTR * PFNGLXGETSYNCVALUESOMLPROC)(Display *dpy, GLXDrawable drawable, int64_t *ust, int64_t *msc, int64_t *sbc);
typedef Bool (GLE_FUNCPTR * PFNGLXGETMSCRATEOMLPROC)(Display *dpy, GLXDrawable drawable, int32_t *numerator, int32_t *denominator);
typedef int64_t (GLE_FUNCPTR * PFNGLXSWAPBUFFERSMSCOMLPROC)(Display *dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder);
typedef Bool (GLE_FUNCPTR * PFNGLXWAITFORMSCOMLPROC)(Display *dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder, int64_t *ust, int64_t *msc, int64_t *sbc);
typedef Bool (GLE_FUNCPTR * PFNGLXWAITFORSBCOMLPROC)(Display *dpy, GLXDrawable drawable, int64_t target_sbc, int64_t *ust, int64_t *msc, int64_t *sbc);

extern PFNGLXGETSYNCVALUESOMLPROC glXGetSyncValuesOML;
extern PFNGLXGETMSCRATEOMLPROC glXGetMscRateOML;
extern PFNGLXSWAPBUFFERSMSCOMLPROC glXSwapBuffersMscOML;
extern PFNGLXWAITFORMSCOMLPROC glXWaitForMscOML;
extern PFNGLXWAITFORSBCOMLPROC glXWaitForSbcOML;
#endif /*GLX_OML_sync_control*/

/******************************
* Extension: GLX_SGIS_blended_overlay
******************************/

#define GLX_BLENDED_RGBA_SGIS 0x8025


/******************************
* Extension: GLX_SGIS_multisample
******************************/

#define GLX_SAMPLE_BUFFERS_SGIS 100000
#define GLX_SAMPLES_SGIS 100001


/******************************
* Extension: GLX_SGIS_shared_multisample
******************************/

#define GLX_MULTISAMPLE_SUB_RECT_WIDTH_SGIS 0x8026
#define GLX_MULTISAMPLE_SUB_RECT_HEIGHT_SGIS 0x8027


/******************************
* Extension: GLX_SGIX_fbconfig
******************************/

#define GLX_SCREEN_EXT 0x800C
#define GLX_WINDOW_BIT_SGIX 0x00000001
#define GLX_PIXMAP_BIT_SGIX 0x00000002
#define GLX_RGBA_BIT_SGIX 0x00000001
#define GLX_COLOR_INDEX_BIT_SGIX 0x00000002
#define GLX_DRAWABLE_TYPE_SGIX 0x8010
#define GLX_RENDER_TYPE_SGIX 0x8011
#define GLX_X_RENDERABLE_SGIX 0x8012
#define GLX_FBCONFIG_ID_SGIX 0x8013
#define GLX_RGBA_TYPE_SGIX 0x8014
#define GLX_COLOR_INDEX_TYPE_SGIX 0x8015


#ifndef GLX_SGIX_fbconfig
#define GLX_SGIX_fbconfig 1

typedef int (GLE_FUNCPTR * PFNGLXGETFBCONFIGATTRIBSGIXPROC)(Display *dpy, GLXFBConfigSGIX config, int attribute, int *value);
typedef GLXFBConfigSGIX * (GLE_FUNCPTR * PFNGLXCHOOSEFBCONFIGSGIXPROC)(Display *dpy, int screen, int *attrib_list, int *nelements);
typedef GLXPixmap (GLE_FUNCPTR * PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC)(Display *dpy, GLXFBConfigSGIX config, Pixmap pixmap);
typedef GLXContext (GLE_FUNCPTR * PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC)(Display *dpy, GLXFBConfigSGIX config, int render_type, GLXContext share_list, Bool direct);
typedef XVisualInfo * (GLE_FUNCPTR * PFNGLXGETVISUALFROMFBCONFIGSGIXPROC)(Display *dpy, GLXFBConfigSGIX config);
typedef GLXFBConfigSGIX (GLE_FUNCPTR * PFNGLXGETFBCONFIGFROMVISUALSGIXPROC)(Display *dpy, XVisualInfo *vis);

extern PFNGLXGETFBCONFIGATTRIBSGIXPROC glXGetFBConfigAttribSGIX;
extern PFNGLXCHOOSEFBCONFIGSGIXPROC glXChooseFBConfigSGIX;
extern PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC glXCreateGLXPixmapWithConfigSGIX;
extern PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC glXCreateContextWithConfigSGIX;
extern PFNGLXGETVISUALFROMFBCONFIGSGIXPROC glXGetVisualFromFBConfigSGIX;
extern PFNGLXGETFBCONFIGFROMVISUALSGIXPROC glXGetFBConfigFromVisualSGIX;
#endif /*GLX_SGIX_fbconfig*/

/******************************
* Extension: GLX_SGIX_pbuffer
******************************/

#define GLX_PBUFFER_BIT_SGIX 0x00000004
#define GLX_BUFFER_CLOBBER_MASK_SGIX 0x08000000
#define GLX_FRONT_LEFT_BUFFER_BIT_SGIX 0x00000001
#define GLX_FRONT_RIGHT_BUFFER_BIT_SGIX 0x00000002
#define GLX_BACK_LEFT_BUFFER_BIT_SGIX 0x00000004
#define GLX_BACK_RIGHT_BUFFER_BIT_SGIX 0x00000008
#define GLX_AUX_BUFFERS_BIT_SGIX 0x00000010
#define GLX_DEPTH_BUFFER_BIT_SGIX 0x00000020
#define GLX_STENCIL_BUFFER_BIT_SGIX 0x00000040
#define GLX_ACCUM_BUFFER_BIT_SGIX 0x00000080
#define GLX_SAMPLE_BUFFERS_BIT_SGIX 0x00000100
#define GLX_MAX_PBUFFER_WIDTH_SGIX 0x8016
#define GLX_MAX_PBUFFER_HEIGHT_SGIX 0x8017
#define GLX_MAX_PBUFFER_PIXELS_SGIX 0x8018
#define GLX_OPTIMAL_PBUFFER_WIDTH_SGIX 0x8019
#define GLX_OPTIMAL_PBUFFER_HEIGHT_SGIX 0x801A
#define GLX_PRESERVED_CONTENTS_SGIX 0x801B
#define GLX_LARGEST_PBUFFER_SGIX 0x801C
#define GLX_WIDTH_SGIX 0x801D
#define GLX_HEIGHT_SGIX 0x801E
#define GLX_EVENT_MASK_SGIX 0x801F
#define GLX_DAMAGED_SGIX 0x8020
#define GLX_SAVED_SGIX 0x8021
#define GLX_WINDOW_SGIX 0x8022
#define GLX_PBUFFER_SGIX 0x8023


#ifndef GLX_SGIX_pbuffer
#define GLX_SGIX_pbuffer 1

typedef GLXPbufferSGIX (GLE_FUNCPTR * PFNGLXCREATEGLXPBUFFERSGIXPROC)(Display *dpy, GLXFBConfigSGIX config, unsigned int width, unsigned int height, int *attrib_list);
typedef void (GLE_FUNCPTR * PFNGLXDESTROYGLXPBUFFERSGIXPROC)(Display *dpy, GLXPbufferSGIX pbuf);
typedef int (GLE_FUNCPTR * PFNGLXQUERYGLXPBUFFERSGIXPROC)(Display *dpy, GLXPbufferSGIX pbuf, int attribute, unsigned int *value);
typedef void (GLE_FUNCPTR * PFNGLXSELECTEVENTSGIXPROC)(Display *dpy, GLXDrawable drawable, unsigned long mask);
typedef void (GLE_FUNCPTR * PFNGLXGETSELECTEDEVENTSGIXPROC)(Display *dpy, GLXDrawable drawable, unsigned long *mask);

extern PFNGLXCREATEGLXPBUFFERSGIXPROC glXCreateGLXPbufferSGIX;
extern PFNGLXDESTROYGLXPBUFFERSGIXPROC glXDestroyGLXPbufferSGIX;
extern PFNGLXQUERYGLXPBUFFERSGIXPROC glXQueryGLXPbufferSGIX;
extern PFNGLXSELECTEVENTSGIXPROC glXSelectEventSGIX;
extern PFNGLXGETSELECTEDEVENTSGIXPROC glXGetSelectedEventSGIX;
#endif /*GLX_SGIX_pbuffer*/

/******************************
* Extension: GLX_SGIX_swap_barrier
******************************/

#ifndef GLX_SGIX_swap_barrier
#define GLX_SGIX_swap_barrier 1

typedef void (GLE_FUNCPTR * PFNGLXBINDSWAPBARRIERSGIXPROC)(Display *dpy, GLXDrawable drawable, int barrier);
typedef Bool (GLE_FUNCPTR * PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC)(Display *dpy, int screen, int *max);

extern PFNGLXBINDSWAPBARRIERSGIXPROC glXBindSwapBarrierSGIX;
extern PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC glXQueryMaxSwapBarriersSGIX;
#endif /*GLX_SGIX_swap_barrier*/

/******************************
* Extension: GLX_SGIX_swap_group
******************************/

#ifndef GLX_SGIX_swap_group
#define GLX_SGIX_swap_group 1

typedef void (GLE_FUNCPTR * PFNGLXJOINSWAPGROUPSGIXPROC)(Display *dpy, GLXDrawable drawable, GLXDrawable member);

extern PFNGLXJOINSWAPGROUPSGIXPROC glXJoinSwapGroupSGIX;
#endif /*GLX_SGIX_swap_group*/

/******************************
* Extension: GLX_SGIX_video_resize
******************************/

#define GLX_SYNC_FRAME_SGIX 0x00000000
#define GLX_SYNC_SWAP_SGIX 0x00000001


#ifndef GLX_SGIX_video_resize
#define GLX_SGIX_video_resize 1

typedef int (GLE_FUNCPTR * PFNGLXBINDCHANNELTOWINDOWSGIXPROC)(Display *display, int screen, int channel, Window window);
typedef int (GLE_FUNCPTR * PFNGLXCHANNELRECTSGIXPROC)(Display *display, int screen, int channel, int x, int y, int w, int h);
typedef int (GLE_FUNCPTR * PFNGLXQUERYCHANNELRECTSGIXPROC)(Display *display, int screen, int channel, int *dx, int *dy, int *dw, int *dh);
typedef int (GLE_FUNCPTR * PFNGLXQUERYCHANNELDELTASSGIXPROC)(Display *display, int screen, int channel, int *x, int *y, int *w, int *h);
typedef int (GLE_FUNCPTR * PFNGLXCHANNELRECTSYNCSGIXPROC)(Display *display, int screen, int channel, GLenum synctype);

extern PFNGLXBINDCHANNELTOWINDOWSGIXPROC glXBindChannelToWindowSGIX;
extern PFNGLXCHANNELRECTSGIXPROC glXChannelRectSGIX;
extern PFNGLXQUERYCHANNELRECTSGIXPROC glXQueryChannelRectSGIX;
extern PFNGLXQUERYCHANNELDELTASSGIXPROC glXQueryChannelDeltasSGIX;
extern PFNGLXCHANNELRECTSYNCSGIXPROC glXChannelRectSyncSGIX;
#endif /*GLX_SGIX_video_resize*/

/******************************
* Extension: GLX_SGIX_visual_select_group
******************************/

#define GLX_VISUAL_SELECT_GROUP_SGIX 0x8028


/******************************
* Extension: GLX_SGI_cushion
******************************/

#ifndef GLX_SGI_cushion
#define GLX_SGI_cushion 1

typedef void (GLE_FUNCPTR * PFNGLXCUSHIONSGIPROC)(Display *dpy, Window window, float cushion);

extern PFNGLXCUSHIONSGIPROC glXCushionSGI;
#endif /*GLX_SGI_cushion*/

/******************************
* Extension: GLX_SGI_make_current_read
******************************/

#ifndef GLX_SGI_make_current_read
#define GLX_SGI_make_current_read 1

typedef Bool (GLE_FUNCPTR * PFNGLXMAKECURRENTREADSGIPROC)(Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
typedef GLXDrawable (GLE_FUNCPTR * PFNGLXGETCURRENTREADDRAWABLESGIPROC)();

extern PFNGLXMAKECURRENTREADSGIPROC glXMakeCurrentReadSGI;
extern PFNGLXGETCURRENTREADDRAWABLESGIPROC glXGetCurrentReadDrawableSGI;
#endif /*GLX_SGI_make_current_read*/

/******************************
* Extension: GLX_SGI_swap_control
******************************/

#ifndef GLX_SGI_swap_control
#define GLX_SGI_swap_control 1

typedef int (GLE_FUNCPTR * PFNGLXSWAPINTERVALSGIPROC)(int interval);

extern PFNGLXSWAPINTERVALSGIPROC glXSwapIntervalSGI;
#endif /*GLX_SGI_swap_control*/

/******************************
* Extension: GLX_SGI_video_sync
******************************/

#ifndef GLX_SGI_video_sync
#define GLX_SGI_video_sync 1

typedef int (GLE_FUNCPTR * PFNGLXGETVIDEOSYNCSGIPROC)(unsigned int *count);
typedef int (GLE_FUNCPTR * PFNGLXWAITVIDEOSYNCSGIPROC)(int divisor, int remainder, unsigned int *count);

extern PFNGLXGETVIDEOSYNCSGIPROC glXGetVideoSyncSGI;
extern PFNGLXWAITVIDEOSYNCSGIPROC glXWaitVideoSyncSGI;
#endif /*GLX_SGI_video_sync*/

/******************************
* Extension: GLX_SUN_get_transparent_index
******************************/

#ifndef GLX_SUN_get_transparent_index
#define GLX_SUN_get_transparent_index 1

typedef Status (GLE_FUNCPTR * PFNGLXGETTRANSPARENTINDEXSUNPROC)(Display *dpy, Window overlay, Window underlay, long *pTransparentIndex);

extern PFNGLXGETTRANSPARENTINDEXSUNPROC glXGetTransparentIndexSUN;
#endif /*GLX_SUN_get_transparent_index*/

#ifdef __cplusplus
}
#endif //__cplusplus


#endif //GLX_EXTS_H

