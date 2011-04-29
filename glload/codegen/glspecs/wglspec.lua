return {
	["typemap"] = {
		["LPVOID"] = [==[LPVOID]==],
		["HPBUFFERARB"] = [==[HPBUFFERARB]==],
		["GLfloat"] = [==[GLfloat]==],
		["HVIDEOOUTPUTDEVICENV"] = [==[HVIDEOOUTPUTDEVICENV]==],
		["HGLRC"] = [==[HGLRC]==],
		["GLbitfield"] = [==[GLbitfield]==],
		["INT64"] = [==[INT64]==],
		["BOOL"] = [==[BOOL]==],
		["HPGPUNV"] = [==[HPGPUNV]==],
		["PGPU_DEVICE"] = [==[PGPU_DEVICE]==],
		["USHORT"] = [==[USHORT]==],
		["String"] = [==[const char *]==],
		["VoidPointer"] = [==[void*]==],
		["GLuint"] = [==[GLuint]==],
		["INT"] = [==[INT]==],
		["DWORD"] = [==[DWORD]==],
		["GLushort"] = [==[GLushort]==],
		["float"] = [==[float]==],
		["FLOAT"] = [==[FLOAT]==],
		["HVIDEOINPUTDEVICENV"] = [==[HVIDEOINPUTDEVICENV]==],
		["GLboolean"] = [==[GLboolean]==],
		["HPVIDEODEV"] = [==[HPVIDEODEV]==],
		["void"] = [==[*]==],
		["HDC"] = [==[HDC]==],
		["GLsizei"] = [==[GLsizei]==],
		["GLenum"] = [==[GLenum]==],
		["int"] = [==[int]==],
		["HPBUFFEREXT"] = [==[HPBUFFEREXT]==],
		["VOID"] = [==[VOID]==],
		["UINT"] = [==[UINT]==],
		["HANDLE"] = [==[HANDLE]==],
		["GLint"] = [==[GLint]==],
		["uint"] = [==[unsigned int]==],
		["HGPUNV"] = [==[HGPUNV]==],
		["INT32"] = [==[INT32]==],
		["ulong"] = [==[unsigned long]==],
	},
	["funcData"] = {
		["properties"] = {
			["category"] = {
				[==[wgl]==],
				[==[ARB_buffer_region]==],
				[==[ARB_extensions_string]==],
				[==[ARB_pixel_format]==],
				[==[ARB_make_current_read]==],
				[==[ARB_pbuffer]==],
				[==[ARB_render_texture]==],
				[==[ARB_pixel_format_float]==],
				[==[EXT_display_color_table]==],
				[==[EXT_extensions_string]==],
				[==[EXT_make_current_read]==],
				[==[EXT_pbuffer]==],
				[==[EXT_pixel_format]==],
				[==[EXT_swap_control]==],
				[==[OML_sync_control]==],
				[==[I3D_digital_video_control]==],
				[==[I3D_gamma]==],
				[==[I3D_genlock]==],
				[==[I3D_image_buffer]==],
				[==[I3D_swap_frame_lock]==],
				[==[I3D_swap_frame_usage]==],
				[==[NV_vertex_array_range]==],
				[==[3DL_stereo_control]==],
				[==[NV_swap_group]==],
				[==[NV_video_output]==],
				[==[NV_present_video]==],
				[==[ARB_create_context]==],
				[==[NV_gpu_affinity]==],
				[==[AMD_gpu_association]==],
				[==[NV_video_capture]==],
				[==[NV_copy_image]==],
				[==[ARB_framebuffer_sRGB]==],
			},
			["required-props"] = {
			},
			["passthru"] = {
			},
			["param"] = {
				[==[retval]==],
				[==[retained]==],
			},
		},
		["passthru"] = {
			[==[#ifndef WGL_ARB_pbuffer]==],
			[==[DECLARE_HANDLE(HPBUFFERARB);]==],
			[==[#endif]==],
			[==[#ifndef WGL_EXT_pbuffer]==],
			[==[DECLARE_HANDLE(HPBUFFEREXT);]==],
			[==[#endif]==],
			[==[#ifndef WGL_NV_present_video]==],
			[==[DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);]==],
			[==[#endif]==],
			[==[#ifndef WGL_NV_video_output]==],
			[==[DECLARE_HANDLE(HPVIDEODEV);]==],
			[==[#endif]==],
			[==[#ifndef WGL_NV_gpu_affinity]==],
			[==[DECLARE_HANDLE(HPGPUNV);]==],
			[==[DECLARE_HANDLE(HGPUNV);]==],
			[==[typedef struct _GPU_DEVICE {]==],
			[==[    DWORD  cb;]==],
			[==[    CHAR   DeviceName[32];]==],
			[==[    CHAR   DeviceString[128];]==],
			[==[    DWORD  Flags;]==],
			[==[    RECT   rcVirtualScreen;]==],
			[==[} GPU_DEVICE, *PGPU_DEVICE;]==],
			[==[#endif]==],
			[==[#ifndef WGL_NV_video_capture]==],
			[==[DECLARE_HANDLE(HVIDEOINPUTDEVICENV);]==],
			[==[#endif]==],
		},
		["functions"] = {
			{
				["name"] = [==[CreateBufferRegionARB]==],
				["return"] = [==[HANDLE]==],
				["category"] = [==[ARB_buffer_region]==],
				["param"] = [==[uType]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iLayerPlane]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[uType]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[DeleteBufferRegionARB]==],
				["return"] = [==[VOID]==],
				["category"] = [==[ARB_buffer_region]==],
				["param"] = [==[hRegion]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HANDLE]==],
						["name"] = [==[hRegion]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[SaveBufferRegionARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_buffer_region]==],
				["param"] = [==[height]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HANDLE]==],
						["name"] = [==[hRegion]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[x]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[y]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[width]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[height]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[RestoreBufferRegionARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_buffer_region]==],
				["param"] = [==[ySrc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HANDLE]==],
						["name"] = [==[hRegion]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[x]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[y]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[width]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[height]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[xSrc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[ySrc]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[GetExtensionsStringARB]==],
				["return"] = [==[String]==],
				["category"] = [==[ARB_extensions_string]==],
				["param"] = [==[hdc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[GetPixelFormatAttribivARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_pixel_format]==],
				["param"] = [==[piValues]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iPixelFormat]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iLayerPlane]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[nAttributes]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[nAttributes]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttributes]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[nAttributes]]==],
						["type"] = [==[int]==],
						["name"] = [==[piValues]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetPixelFormatAttribfvARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_pixel_format]==],
				["param"] = [==[pfValues]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iPixelFormat]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iLayerPlane]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[nAttributes]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[nAttributes]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttributes]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[nAttributes]]==],
						["type"] = [==[FLOAT]==],
						["name"] = [==[pfValues]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[ChoosePixelFormatARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_pixel_format]==],
				["param"] = [==[nNumFormats]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttribIList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[FLOAT]==],
						["name"] = [==[pfAttribFList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[nMaxFormats]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE(nNumFormats)]]==],
						["type"] = [==[int]==],
						["name"] = [==[piFormats]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["input"] = false,
						["type"] = [==[UINT]==],
						["name"] = [==[nNumFormats]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[MakeContextCurrentARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_make_current_read]==],
				["param"] = [==[hglrc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDrawDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hReadDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hglrc]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["category"] = [==[ARB_make_current_read]==],
				["return"] = [==[HDC]==],
				["name"] = [==[GetCurrentReadDCARB]==],
				["params"] = {
				},
			},
			{
				["name"] = [==[CreatePbufferARB]==],
				["return"] = [==[HPBUFFERARB]==],
				["category"] = [==[ARB_pbuffer]==],
				["param"] = [==[piAttribList]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iPixelFormat]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iWidth]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iHeight]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttribList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetPbufferDCARB]==],
				["return"] = [==[HDC]==],
				["category"] = [==[ARB_pbuffer]==],
				["param"] = [==[hPbuffer]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[ReleasePbufferDCARB]==],
				["return"] = [==[int]==],
				["category"] = [==[ARB_pbuffer]==],
				["param"] = [==[hDC]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[DestroyPbufferARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_pbuffer]==],
				["param"] = [==[hPbuffer]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[QueryPbufferARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_pbuffer]==],
				["param"] = [==[piValue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iAttribute]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[int]==],
						["name"] = [==[piValue]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[BindTexImageARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_render_texture]==],
				["param"] = [==[iBuffer]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iBuffer]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[ReleaseTexImageARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_render_texture]==],
				["param"] = [==[iBuffer]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iBuffer]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[SetPbufferAttribARB]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[ARB_render_texture]==],
				["param"] = [==[piAttribList]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttribList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[CreateContextAttribsARB]==],
				["return"] = [==[HGLRC]==],
				["category"] = [==[ARB_create_context]==],
				["param"] = [==[attribList]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hShareContext]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[attribList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[CreateDisplayColorTableEXT]==],
				["return"] = [==[GLboolean]==],
				["category"] = [==[EXT_display_color_table]==],
				["param"] = [==[id]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[GLushort]==],
						["name"] = [==[id]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[LoadDisplayColorTableEXT]==],
				["return"] = [==[GLboolean]==],
				["category"] = [==[EXT_display_color_table]==],
				["param"] = [==[length]==],
				["params"] = {
					{
						["other"] = [==[[length]]==],
						["type"] = [==[GLushort]==],
						["name"] = [==[table]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLuint]==],
						["name"] = [==[length]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[BindDisplayColorTableEXT]==],
				["return"] = [==[GLboolean]==],
				["category"] = [==[EXT_display_color_table]==],
				["param"] = [==[id]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[GLushort]==],
						["name"] = [==[id]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[DestroyDisplayColorTableEXT]==],
				["return"] = [==[VOID]==],
				["category"] = [==[EXT_display_color_table]==],
				["param"] = [==[id]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[GLushort]==],
						["name"] = [==[id]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["category"] = [==[EXT_extensions_string]==],
				["return"] = [==[String]==],
				["name"] = [==[GetExtensionsStringEXT]==],
				["params"] = {
				},
			},
			{
				["name"] = [==[MakeContextCurrentEXT]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[EXT_make_current_read]==],
				["param"] = [==[hglrc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDrawDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hReadDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hglrc]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["category"] = [==[EXT_make_current_read]==],
				["return"] = [==[HDC]==],
				["name"] = [==[GetCurrentReadDCEXT]==],
				["params"] = {
				},
			},
			{
				["name"] = [==[CreatePbufferEXT]==],
				["return"] = [==[HPBUFFEREXT]==],
				["category"] = [==[EXT_pbuffer]==],
				["param"] = [==[piAttribList]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iPixelFormat]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iWidth]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iHeight]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttribList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetPbufferDCEXT]==],
				["return"] = [==[HDC]==],
				["category"] = [==[EXT_pbuffer]==],
				["param"] = [==[hPbuffer]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFEREXT]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[ReleasePbufferDCEXT]==],
				["return"] = [==[int]==],
				["category"] = [==[EXT_pbuffer]==],
				["param"] = [==[hDC]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFEREXT]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[DestroyPbufferEXT]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[EXT_pbuffer]==],
				["param"] = [==[hPbuffer]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFEREXT]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[QueryPbufferEXT]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[EXT_pbuffer]==],
				["param"] = [==[piValue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFEREXT]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iAttribute]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[int]==],
						["name"] = [==[piValue]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[GetPixelFormatAttribivEXT]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[EXT_pixel_format]==],
				["param"] = [==[piValues]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iPixelFormat]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iLayerPlane]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[nAttributes]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[nAttributes]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttributes]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[nAttributes]]==],
						["type"] = [==[int]==],
						["name"] = [==[piValues]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetPixelFormatAttribfvEXT]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[EXT_pixel_format]==],
				["param"] = [==[pfValues]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iPixelFormat]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iLayerPlane]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[nAttributes]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[nAttributes]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttributes]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[nAttributes]]==],
						["type"] = [==[FLOAT]==],
						["name"] = [==[pfValues]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[ChoosePixelFormatEXT]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[EXT_pixel_format]==],
				["param"] = [==[nNumFormats]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttribIList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[FLOAT]==],
						["name"] = [==[pfAttribFList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[nMaxFormats]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE(nNumFormats)]]==],
						["type"] = [==[int]==],
						["name"] = [==[piFormats]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["input"] = false,
						["type"] = [==[UINT]==],
						["name"] = [==[nNumFormats]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[SwapIntervalEXT]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[EXT_swap_control]==],
				["param"] = [==[interval]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[interval]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["category"] = [==[EXT_swap_control]==],
				["return"] = [==[int]==],
				["name"] = [==[GetSwapIntervalEXT]==],
				["params"] = {
				},
			},
			{
				["name"] = [==[AllocateMemoryNV]==],
				["return"] = [==[VoidPointer]==],
				["category"] = [==[NV_vertex_array_range]==],
				["param"] = [==[priority]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[GLsizei]==],
						["name"] = [==[size]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLfloat]==],
						["name"] = [==[readfreq]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLfloat]==],
						["name"] = [==[writefreq]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLfloat]==],
						["name"] = [==[priority]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[FreeMemoryNV]==],
				["return"] = [==[void]==],
				["category"] = [==[NV_vertex_array_range]==],
				["param"] = [==[pointer]==],
				["params"] = {
					{
						["other"] = [==[[1]]==],
						["type"] = [==[void]==],
						["name"] = [==[pointer]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetSyncValuesOML]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[OML_sync_control]==],
				["param"] = [==[sbc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[ust]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[msc]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[sbc]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetMscRateOML]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[OML_sync_control]==],
				["param"] = [==[denominator]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT32]==],
						["name"] = [==[numerator]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT32]==],
						["name"] = [==[denominator]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[SwapBuffersMscOML]==],
				["return"] = [==[INT64]==],
				["category"] = [==[OML_sync_control]==],
				["param"] = [==[remainder]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[target_msc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[divisor]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[remainder]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[SwapLayerBuffersMscOML]==],
				["return"] = [==[INT64]==],
				["category"] = [==[OML_sync_control]==],
				["param"] = [==[remainder]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[fuPlanes]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[target_msc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[divisor]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[remainder]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[WaitForMscOML]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[OML_sync_control]==],
				["param"] = [==[sbc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[target_msc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[divisor]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[remainder]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[ust]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[msc]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[sbc]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[WaitForSbcOML]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[OML_sync_control]==],
				["param"] = [==[sbc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[INT64]==],
						["name"] = [==[target_sbc]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[ust]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[msc]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[1]]==],
						["type"] = [==[INT64]==],
						["name"] = [==[sbc]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetDigitalVideoParametersI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_digital_video_control]==],
				["param"] = [==[piValue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iAttribute]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE(iAttribute)]]==],
						["type"] = [==[int]==],
						["name"] = [==[piValue]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[SetDigitalVideoParametersI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_digital_video_control]==],
				["param"] = [==[piValue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iAttribute]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE(iAttribute)]]==],
						["type"] = [==[int]==],
						["name"] = [==[piValue]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetGammaTableParametersI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_gamma]==],
				["param"] = [==[piValue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iAttribute]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE(iAttribute)]]==],
						["type"] = [==[int]==],
						["name"] = [==[piValue]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[SetGammaTableParametersI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_gamma]==],
				["param"] = [==[piValue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iAttribute]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE(iAttribute)]]==],
						["type"] = [==[int]==],
						["name"] = [==[piValue]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetGammaTableI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_gamma]==],
				["param"] = [==[puBlue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iEntries]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[iEntries]]==],
						["type"] = [==[USHORT]==],
						["name"] = [==[puRed]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[iEntries]]==],
						["type"] = [==[USHORT]==],
						["name"] = [==[puGreen]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[iEntries]]==],
						["type"] = [==[USHORT]==],
						["name"] = [==[puBlue]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[SetGammaTableI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_gamma]==],
				["param"] = [==[puBlue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iEntries]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[iEntries]]==],
						["type"] = [==[USHORT]==],
						["name"] = [==[puRed]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[iEntries]]==],
						["type"] = [==[USHORT]==],
						["name"] = [==[puGreen]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[iEntries]]==],
						["type"] = [==[USHORT]==],
						["name"] = [==[puBlue]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[EnableGenlockI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[hDC]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[DisableGenlockI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[hDC]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[IsEnabledGenlockI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[pFlag]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[BOOL]==],
						["name"] = [==[pFlag]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[GenlockSourceI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uSource]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[uSource]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[GetGenlockSourceI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uSource]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[UINT]==],
						["name"] = [==[uSource]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[GenlockSourceEdgeI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uEdge]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[uEdge]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[GetGenlockSourceEdgeI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uEdge]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[UINT]==],
						["name"] = [==[uEdge]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[GenlockSampleRateI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uRate]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[uRate]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[GetGenlockSampleRateI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uRate]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[UINT]==],
						["name"] = [==[uRate]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[GenlockSourceDelayI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uDelay]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[uDelay]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[GetGenlockSourceDelayI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uDelay]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[UINT]==],
						["name"] = [==[uDelay]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[QueryGenlockMaxSourceDelayI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_genlock]==],
				["param"] = [==[uMaxPixelDelay]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[UINT]==],
						["name"] = [==[uMaxLineDelay]==],
						["kind"] = [==[reference]==],
					},
					{
						["input"] = false,
						["type"] = [==[UINT]==],
						["name"] = [==[uMaxPixelDelay]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[CreateImageBufferI3D]==],
				["return"] = [==[LPVOID]==],
				["category"] = [==[I3D_image_buffer]==],
				["param"] = [==[uFlags]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[DWORD]==],
						["name"] = [==[dwSize]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[uFlags]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[DestroyImageBufferI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_image_buffer]==],
				["param"] = [==[pAddress]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[LPVOID]==],
						["name"] = [==[pAddress]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[AssociateImageBufferEventsI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_image_buffer]==],
				["param"] = [==[count]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[count]]==],
						["type"] = [==[HANDLE]==],
						["name"] = [==[pEvent]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[count]]==],
						["type"] = [==[LPVOID]==],
						["name"] = [==[pAddress]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["other"] = [==[[count]]==],
						["type"] = [==[DWORD]==],
						["name"] = [==[pSize]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[count]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[ReleaseImageBufferEventsI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_image_buffer]==],
				["param"] = [==[count]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[count]]==],
						["type"] = [==[LPVOID]==],
						["name"] = [==[pAddress]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[count]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["category"] = [==[I3D_swap_frame_lock]==],
				["return"] = [==[BOOL]==],
				["name"] = [==[EnableFrameLockI3D]==],
				["params"] = {
				},
			},
			{
				["category"] = [==[I3D_swap_frame_lock]==],
				["return"] = [==[BOOL]==],
				["name"] = [==[DisableFrameLockI3D]==],
				["params"] = {
				},
			},
			{
				["name"] = [==[IsEnabledFrameLockI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_swap_frame_lock]==],
				["param"] = [==[pFlag]==],
				["params"] = {
					{
						["input"] = false,
						["type"] = [==[BOOL]==],
						["name"] = [==[pFlag]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[QueryFrameLockMasterI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_swap_frame_lock]==],
				["param"] = [==[pFlag]==],
				["params"] = {
					{
						["input"] = false,
						["type"] = [==[BOOL]==],
						["name"] = [==[pFlag]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[GetFrameUsageI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_swap_frame_usage]==],
				["param"] = [==[pUsage]==],
				["params"] = {
					{
						["input"] = false,
						["type"] = [==[float]==],
						["name"] = [==[pUsage]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["category"] = [==[I3D_swap_frame_usage]==],
				["return"] = [==[BOOL]==],
				["name"] = [==[BeginFrameTrackingI3D]==],
				["params"] = {
				},
			},
			{
				["category"] = [==[I3D_swap_frame_usage]==],
				["return"] = [==[BOOL]==],
				["name"] = [==[EndFrameTrackingI3D]==],
				["params"] = {
				},
			},
			{
				["name"] = [==[QueryFrameTrackingI3D]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[I3D_swap_frame_usage]==],
				["param"] = [==[pLastMissedUsage]==],
				["params"] = {
					{
						["input"] = false,
						["type"] = [==[DWORD]==],
						["name"] = [==[pFrameCount]==],
						["kind"] = [==[reference]==],
					},
					{
						["input"] = false,
						["type"] = [==[DWORD]==],
						["name"] = [==[pMissedFrames]==],
						["kind"] = [==[reference]==],
					},
					{
						["input"] = false,
						["type"] = [==[float]==],
						["name"] = [==[pLastMissedUsage]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[SetStereoEmitterState3DL]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[3DL_stereo_control]==],
				["param"] = [==[uState]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[uState]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[EnumerateVideoDevicesNV]==],
				["return"] = [==[int]==],
				["category"] = [==[NV_present_video]==],
				["param"] = [==[phDeviceList]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[HVIDEOOUTPUTDEVICENV]==],
						["name"] = [==[phDeviceList]==],
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[BindVideoDeviceNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_present_video]==],
				["param"] = [==[piAttribList]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[uint]==],
						["name"] = [==[uVideoSlot]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HVIDEOOUTPUTDEVICENV]==],
						["name"] = [==[hVideoDevice]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[piAttribList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[QueryCurrentContextNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_present_video]==],
				["param"] = [==[piValue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iAttribute]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[piValue]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetVideoDeviceNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_output]==],
				["param"] = [==[hVideoDevice]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[numDevices]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[HPVIDEODEV]==],
						["name"] = [==[hVideoDevice]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[ReleaseVideoDeviceNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_output]==],
				["param"] = [==[hVideoDevice]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPVIDEODEV]==],
						["name"] = [==[hVideoDevice]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[BindVideoImageNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_output]==],
				["param"] = [==[iVideoBuffer]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPVIDEODEV]==],
						["name"] = [==[hVideoDevice]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iVideoBuffer]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[ReleaseVideoImageNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_output]==],
				["param"] = [==[iVideoBuffer]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iVideoBuffer]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[SendPbufferToVideoNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_output]==],
				["param"] = [==[bBlock]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPBUFFERARB]==],
						["name"] = [==[hPbuffer]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iBufferType]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[ulong]==],
						["name"] = [==[pulCounterPbuffer]==],
						["kind"] = [==[reference]==],
					},
					{
						["input"] = true,
						["type"] = [==[BOOL]==],
						["name"] = [==[bBlock]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[GetVideoInfoNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_output]==],
				["param"] = [==[pulCounterOutputVideo]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HPVIDEODEV]==],
						["name"] = [==[hpVideoDevice]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[ulong]==],
						["name"] = [==[pulCounterOutputPbuffer]==],
						["kind"] = [==[reference]==],
					},
					{
						["input"] = false,
						["type"] = [==[ulong]==],
						["name"] = [==[pulCounterOutputVideo]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[JoinSwapGroupNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_swap_group]==],
				["param"] = [==[group]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLuint]==],
						["name"] = [==[group]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[BindSwapBarrierNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_swap_group]==],
				["param"] = [==[barrier]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[GLuint]==],
						["name"] = [==[group]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLuint]==],
						["name"] = [==[barrier]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[QuerySwapGroupNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_swap_group]==],
				["param"] = [==[barrier]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[GLuint]==],
						["name"] = [==[group]==],
						["kind"] = [==[reference]==],
					},
					{
						["input"] = false,
						["type"] = [==[GLuint]==],
						["name"] = [==[barrier]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[QueryMaxSwapGroupsNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_swap_group]==],
				["param"] = [==[maxBarriers]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[GLuint]==],
						["name"] = [==[maxGroups]==],
						["kind"] = [==[reference]==],
					},
					{
						["input"] = false,
						["type"] = [==[GLuint]==],
						["name"] = [==[maxBarriers]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[QueryFrameCountNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_swap_group]==],
				["param"] = [==[count]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[GLuint]==],
						["name"] = [==[count]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[ResetFrameCountNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_swap_group]==],
				["param"] = [==[hDC]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDC]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[EnumGpusNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_gpu_affinity]==],
				["param"] = [==[phGpu]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[iGpuIndex]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[HGPUNV]==],
						["name"] = [==[phGpu]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[EnumGpuDevicesNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_gpu_affinity]==],
				["param"] = [==[lpGpuDevice]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HGPUNV]==],
						["name"] = [==[hGpu]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[iDeviceIndex]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[PGPU_DEVICE]==],
						["name"] = [==[lpGpuDevice]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[CreateAffinityDCNV]==],
				["return"] = [==[HDC]==],
				["category"] = [==[NV_gpu_affinity]==],
				["param"] = [==[phGpuList]==],
				["params"] = {
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[HGPUNV]==],
						["name"] = [==[phGpuList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[EnumGpusFromAffinityDCNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_gpu_affinity]==],
				["param"] = [==[hGpu]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hAffinityDC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[iGpuIndex]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[HGPUNV]==],
						["name"] = [==[hGpu]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[DeleteDCNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_gpu_affinity]==],
				["param"] = [==[hdc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hdc]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[GetGPUIDsAMD]==],
				["return"] = [==[UINT]==],
				["category"] = [==[AMD_gpu_association]==],
				["param"] = [==[ids]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[maxCount]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[maxCount]]==],
						["type"] = [==[UINT]==],
						["name"] = [==[ids]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetGPUInfoAMD]==],
				["return"] = [==[INT]==],
				["category"] = [==[AMD_gpu_association]==],
				["param"] = [==[data]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[id]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[property]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLenum]==],
						["name"] = [==[dataType]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[size]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE(dataType,size)]]==],
						["type"] = [==[void]==],
						["name"] = [==[data]==],
						["input"] = false,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[GetContextGPUIDAMD]==],
				["return"] = [==[UINT]==],
				["category"] = [==[AMD_gpu_association]==],
				["param"] = [==[hglrc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hglrc]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[CreateAssociatedContextAMD]==],
				["return"] = [==[HGLRC]==],
				["category"] = [==[AMD_gpu_association]==],
				["param"] = [==[id]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[id]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[CreateAssociatedContextAttribsAMD]==],
				["return"] = [==[HGLRC]==],
				["category"] = [==[AMD_gpu_association]==],
				["param"] = [==[attribList]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[id]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hShareContext]==],
						["kind"] = [==[value]==],
					},
					{
						["other"] = [==[[COMPSIZE()]]==],
						["type"] = [==[int]==],
						["name"] = [==[attribList]==],
						["input"] = true,
						["kind"] = [==[array]==],
					},
				},
			},
			{
				["name"] = [==[DeleteAssociatedContextAMD]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[AMD_gpu_association]==],
				["param"] = [==[hglrc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hglrc]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[MakeAssociatedContextCurrentAMD]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[AMD_gpu_association]==],
				["param"] = [==[hglrc]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hglrc]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["category"] = [==[AMD_gpu_association]==],
				["return"] = [==[HGLRC]==],
				["name"] = [==[GetCurrentAssociatedContextAMD]==],
				["params"] = {
				},
			},
			{
				["name"] = [==[BlitContextFramebufferAMD]==],
				["return"] = [==[VOID]==],
				["category"] = [==[AMD_gpu_association]==],
				["param"] = [==[filter]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[dstCtx]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[srcX0]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[srcY0]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[srcX1]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[srcY1]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[dstX0]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[dstY0]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[dstX1]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[dstY1]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLbitfield]==],
						["name"] = [==[mask]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLenum]==],
						["name"] = [==[filter]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[BindVideoCaptureDeviceNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_capture]==],
				["param"] = [==[hDevice]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[UINT]==],
						["name"] = [==[uVideoSlot]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HVIDEOINPUTDEVICENV]==],
						["name"] = [==[hDevice]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[EnumerateVideoCaptureDevicesNV]==],
				["return"] = [==[UINT]==],
				["category"] = [==[NV_video_capture]==],
				["param"] = [==[phDeviceList]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[HVIDEOINPUTDEVICENV]==],
						["name"] = [==[phDeviceList]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[LockVideoCaptureDeviceNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_capture]==],
				["param"] = [==[hDevice]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HVIDEOINPUTDEVICENV]==],
						["name"] = [==[hDevice]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[QueryVideoCaptureDeviceNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_capture]==],
				["param"] = [==[piValue]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HVIDEOINPUTDEVICENV]==],
						["name"] = [==[hDevice]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[int]==],
						["name"] = [==[iAttribute]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = false,
						["type"] = [==[int]==],
						["name"] = [==[piValue]==],
						["kind"] = [==[reference]==],
					},
				},
			},
			{
				["name"] = [==[ReleaseVideoCaptureDeviceNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_video_capture]==],
				["param"] = [==[hDevice]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HDC]==],
						["name"] = [==[hDc]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HVIDEOINPUTDEVICENV]==],
						["name"] = [==[hDevice]==],
						["kind"] = [==[value]==],
					},
				},
			},
			{
				["name"] = [==[CopyImageSubDataNV]==],
				["return"] = [==[BOOL]==],
				["category"] = [==[NV_copy_image]==],
				["param"] = [==[depth]==],
				["params"] = {
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hSrcRC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLuint]==],
						["name"] = [==[srcName]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLenum]==],
						["name"] = [==[srcTarget]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[srcLevel]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[srcX]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[srcY]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[srcZ]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[HGLRC]==],
						["name"] = [==[hDstRC]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLuint]==],
						["name"] = [==[dstName]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLenum]==],
						["name"] = [==[dstTarget]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[dstLevel]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[dstX]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[dstY]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLint]==],
						["name"] = [==[dstZ]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLsizei]==],
						["name"] = [==[width]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLsizei]==],
						["name"] = [==[height]==],
						["kind"] = [==[value]==],
					},
					{
						["input"] = true,
						["type"] = [==[GLsizei]==],
						["name"] = [==[depth]==],
						["kind"] = [==[value]==],
					},
				},
			},
		},
	},
	["extensions"] = {
		[==[ARB_buffer_region]==],
		[==[ARB_multisample]==],
		[==[ARB_extensions_string]==],
		[==[ARB_pixel_format]==],
		[==[ARB_make_current_read]==],
		[==[ARB_pbuffer]==],
		[==[ARB_render_texture]==],
		[==[ARB_pixel_format_float]==],
		[==[ARB_framebuffer_sRGB]==],
		[==[ARB_create_context]==],
		[==[ARB_create_context_profile]==],
		[==[ARB_create_context_robustness]==],
		[==[EXT_make_current_read]==],
		[==[EXT_pixel_format]==],
		[==[EXT_pbuffer]==],
		[==[EXT_depth_float]==],
		[==[3DFX_multisample]==],
		[==[EXT_multisample]==],
		[==[I3D_digital_video_control]==],
		[==[I3D_gamma]==],
		[==[I3D_genlock]==],
		[==[I3D_image_buffer]==],
		[==[I3D_swap_frame_lock]==],
		[==[NV_render_depth_texture]==],
		[==[NV_render_texture_rectangle]==],
		[==[ATI_pixel_format_float]==],
		[==[NV_float_buffer]==],
		[==[3DL_stereo_control]==],
		[==[EXT_pixel_format_packed_float]==],
		[==[EXT_framebuffer_sRGB]==],
		[==[NV_present_video]==],
		[==[NV_video_out]==],
		[==[NV_swap_group]==],
		[==[NV_gpu_affinity]==],
		[==[AMD_gpu_association]==],
		[==[NV_video_capture]==],
		[==[NV_copy_image]==],
		[==[NV_multisample_coverage]==],
		[==[EXT_create_context_es2_profile]==],
	},
	["enumerations"] = {
		{
			["value"] = [==[0x00000001]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_buffer_region]==],
			},
			["name"] = [==[FRONT_COLOR_BUFFER_BIT_ARB]==],
		},
		{
			["value"] = [==[0x00000002]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_buffer_region]==],
			},
			["name"] = [==[BACK_COLOR_BUFFER_BIT_ARB]==],
		},
		{
			["value"] = [==[0x00000004]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_buffer_region]==],
			},
			["name"] = [==[DEPTH_BUFFER_BIT_ARB]==],
		},
		{
			["value"] = [==[0x00000008]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_buffer_region]==],
			},
			["name"] = [==[STENCIL_BUFFER_BIT_ARB]==],
		},
		{
			["value"] = [==[0x2041]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_multisample]==],
			},
			["name"] = [==[SAMPLE_BUFFERS_ARB]==],
		},
		{
			["value"] = [==[0x2042]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_multisample]==],
			},
			["name"] = [==[SAMPLES_ARB]==],
		},
		{
			["value"] = [==[0x2000]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[NUMBER_PIXEL_FORMATS_ARB]==],
		},
		{
			["value"] = [==[0x2001]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[DRAW_TO_WINDOW_ARB]==],
		},
		{
			["value"] = [==[0x2002]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[DRAW_TO_BITMAP_ARB]==],
		},
		{
			["value"] = [==[0x2003]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[ACCELERATION_ARB]==],
		},
		{
			["value"] = [==[0x2004]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[NEED_PALETTE_ARB]==],
		},
		{
			["value"] = [==[0x2005]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[NEED_SYSTEM_PALETTE_ARB]==],
		},
		{
			["value"] = [==[0x2006]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SWAP_LAYER_BUFFERS_ARB]==],
		},
		{
			["value"] = [==[0x2007]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SWAP_METHOD_ARB]==],
		},
		{
			["value"] = [==[0x2008]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[NUMBER_OVERLAYS_ARB]==],
		},
		{
			["value"] = [==[0x2009]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[NUMBER_UNDERLAYS_ARB]==],
		},
		{
			["value"] = [==[0x200A]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[TRANSPARENT_ARB]==],
		},
		{
			["copy"] = false,
			["name"] = [==[TRANSPARENT_RED_VALUE_ARB]==],
			["value"] = [==[0x2037]==],
			["extensions"] = {
				[==[ARB_pixel_format]==],
				[==[ARB_pbuffer]==],
			},
		},
		{
			["copy"] = false,
			["name"] = [==[TRANSPARENT_GREEN_VALUE_ARB]==],
			["value"] = [==[0x2038]==],
			["extensions"] = {
				[==[ARB_pixel_format]==],
				[==[ARB_pbuffer]==],
			},
		},
		{
			["copy"] = false,
			["name"] = [==[TRANSPARENT_BLUE_VALUE_ARB]==],
			["value"] = [==[0x2039]==],
			["extensions"] = {
				[==[ARB_pixel_format]==],
				[==[ARB_pbuffer]==],
			},
		},
		{
			["copy"] = false,
			["name"] = [==[TRANSPARENT_ALPHA_VALUE_ARB]==],
			["value"] = [==[0x203A]==],
			["extensions"] = {
				[==[ARB_pixel_format]==],
				[==[ARB_pbuffer]==],
			},
		},
		{
			["copy"] = false,
			["name"] = [==[TRANSPARENT_INDEX_VALUE_ARB]==],
			["value"] = [==[0x203B]==],
			["extensions"] = {
				[==[ARB_pixel_format]==],
				[==[ARB_pbuffer]==],
			},
		},
		{
			["value"] = [==[0x200C]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SHARE_DEPTH_ARB]==],
		},
		{
			["value"] = [==[0x200D]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SHARE_STENCIL_ARB]==],
		},
		{
			["value"] = [==[0x200E]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SHARE_ACCUM_ARB]==],
		},
		{
			["value"] = [==[0x200F]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SUPPORT_GDI_ARB]==],
		},
		{
			["value"] = [==[0x2010]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SUPPORT_OPENGL_ARB]==],
		},
		{
			["value"] = [==[0x2011]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[DOUBLE_BUFFER_ARB]==],
		},
		{
			["value"] = [==[0x2012]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[STEREO_ARB]==],
		},
		{
			["value"] = [==[0x2013]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[PIXEL_TYPE_ARB]==],
		},
		{
			["value"] = [==[0x2014]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[COLOR_BITS_ARB]==],
		},
		{
			["value"] = [==[0x2015]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[RED_BITS_ARB]==],
		},
		{
			["value"] = [==[0x2016]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[RED_SHIFT_ARB]==],
		},
		{
			["value"] = [==[0x2017]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[GREEN_BITS_ARB]==],
		},
		{
			["value"] = [==[0x2018]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[GREEN_SHIFT_ARB]==],
		},
		{
			["value"] = [==[0x2019]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[BLUE_BITS_ARB]==],
		},
		{
			["value"] = [==[0x201A]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[BLUE_SHIFT_ARB]==],
		},
		{
			["value"] = [==[0x201B]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[ALPHA_BITS_ARB]==],
		},
		{
			["value"] = [==[0x201C]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[ALPHA_SHIFT_ARB]==],
		},
		{
			["value"] = [==[0x201D]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[ACCUM_BITS_ARB]==],
		},
		{
			["value"] = [==[0x201E]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[ACCUM_RED_BITS_ARB]==],
		},
		{
			["value"] = [==[0x201F]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[ACCUM_GREEN_BITS_ARB]==],
		},
		{
			["value"] = [==[0x2020]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[ACCUM_BLUE_BITS_ARB]==],
		},
		{
			["value"] = [==[0x2021]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[ACCUM_ALPHA_BITS_ARB]==],
		},
		{
			["value"] = [==[0x2022]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[DEPTH_BITS_ARB]==],
		},
		{
			["value"] = [==[0x2023]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[STENCIL_BITS_ARB]==],
		},
		{
			["value"] = [==[0x2024]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[AUX_BUFFERS_ARB]==],
		},
		{
			["value"] = [==[0x2025]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[NO_ACCELERATION_ARB]==],
		},
		{
			["value"] = [==[0x2026]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[GENERIC_ACCELERATION_ARB]==],
		},
		{
			["value"] = [==[0x2027]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[FULL_ACCELERATION_ARB]==],
		},
		{
			["value"] = [==[0x2028]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SWAP_EXCHANGE_ARB]==],
		},
		{
			["value"] = [==[0x2029]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SWAP_COPY_ARB]==],
		},
		{
			["value"] = [==[0x202A]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[SWAP_UNDEFINED_ARB]==],
		},
		{
			["value"] = [==[0x202B]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[TYPE_RGBA_ARB]==],
		},
		{
			["value"] = [==[0x202C]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format]==],
			},
			["name"] = [==[TYPE_COLORINDEX_ARB]==],
		},
		{
			["value"] = [==[0x2043]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_make_current_read]==],
			},
			["name"] = [==[ERROR_INVALID_PIXEL_TYPE_ARB]==],
		},
		{
			["value"] = [==[0x2054]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_make_current_read]==],
			},
			["name"] = [==[ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB]==],
		},
		{
			["value"] = [==[0x202D]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pbuffer]==],
			},
			["name"] = [==[DRAW_TO_PBUFFER_ARB]==],
		},
		{
			["value"] = [==[0x202E]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pbuffer]==],
			},
			["name"] = [==[MAX_PBUFFER_PIXELS_ARB]==],
		},
		{
			["value"] = [==[0x202F]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pbuffer]==],
			},
			["name"] = [==[MAX_PBUFFER_WIDTH_ARB]==],
		},
		{
			["value"] = [==[0x2030]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pbuffer]==],
			},
			["name"] = [==[MAX_PBUFFER_HEIGHT_ARB]==],
		},
		{
			["value"] = [==[0x2033]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pbuffer]==],
			},
			["name"] = [==[PBUFFER_LARGEST_ARB]==],
		},
		{
			["value"] = [==[0x2034]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pbuffer]==],
			},
			["name"] = [==[PBUFFER_WIDTH_ARB]==],
		},
		{
			["value"] = [==[0x2035]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pbuffer]==],
			},
			["name"] = [==[PBUFFER_HEIGHT_ARB]==],
		},
		{
			["value"] = [==[0x2036]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pbuffer]==],
			},
			["name"] = [==[PBUFFER_LOST_ARB]==],
		},
		{
			["value"] = [==[0x2070]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RGB_ARB]==],
		},
		{
			["value"] = [==[0x2071]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RGBA_ARB]==],
		},
		{
			["value"] = [==[0x2072]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_FORMAT_ARB]==],
		},
		{
			["value"] = [==[0x2073]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_TARGET_ARB]==],
		},
		{
			["value"] = [==[0x2074]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[MIPMAP_TEXTURE_ARB]==],
		},
		{
			["value"] = [==[0x2075]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_RGB_ARB]==],
		},
		{
			["value"] = [==[0x2076]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_RGBA_ARB]==],
		},
		{
			["value"] = [==[0x2077]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[NO_TEXTURE_ARB]==],
		},
		{
			["value"] = [==[0x2078]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_CUBE_MAP_ARB]==],
		},
		{
			["value"] = [==[0x2079]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_1D_ARB]==],
		},
		{
			["value"] = [==[0x207A]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_2D_ARB]==],
		},
		{
			["value"] = [==[0x207B]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[MIPMAP_LEVEL_ARB]==],
		},
		{
			["value"] = [==[0x207C]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[CUBE_MAP_FACE_ARB]==],
		},
		{
			["value"] = [==[0x207D]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_CUBE_MAP_POSITIVE_X_ARB]==],
		},
		{
			["value"] = [==[0x207E]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_CUBE_MAP_NEGATIVE_X_ARB]==],
		},
		{
			["value"] = [==[0x207F]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_CUBE_MAP_POSITIVE_Y_ARB]==],
		},
		{
			["value"] = [==[0x2080]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB]==],
		},
		{
			["value"] = [==[0x2081]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_CUBE_MAP_POSITIVE_Z_ARB]==],
		},
		{
			["value"] = [==[0x2082]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB]==],
		},
		{
			["value"] = [==[0x2083]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[FRONT_LEFT_ARB]==],
		},
		{
			["value"] = [==[0x2084]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[FRONT_RIGHT_ARB]==],
		},
		{
			["value"] = [==[0x2085]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[BACK_LEFT_ARB]==],
		},
		{
			["value"] = [==[0x2086]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[BACK_RIGHT_ARB]==],
		},
		{
			["value"] = [==[0x2087]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX0_ARB]==],
		},
		{
			["value"] = [==[0x2088]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX1_ARB]==],
		},
		{
			["value"] = [==[0x2089]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX2_ARB]==],
		},
		{
			["value"] = [==[0x208A]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX3_ARB]==],
		},
		{
			["value"] = [==[0x208B]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX4_ARB]==],
		},
		{
			["value"] = [==[0x208C]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX5_ARB]==],
		},
		{
			["value"] = [==[0x208D]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX6_ARB]==],
		},
		{
			["value"] = [==[0x208E]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX7_ARB]==],
		},
		{
			["value"] = [==[0x208F]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX8_ARB]==],
		},
		{
			["value"] = [==[0x2090]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_render_texture]==],
			},
			["name"] = [==[AUX9_ARB]==],
		},
		{
			["value"] = [==[0x21A0]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_pixel_format_float]==],
			},
			["name"] = [==[TYPE_RGBA_FLOAT_ARB]==],
		},
		{
			["value"] = [==[0x20A9]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_framebuffer_sRGB]==],
			},
			["name"] = [==[FRAMEBUFFER_SRGB_CAPABLE_ARB]==],
		},
		{
			["value"] = [==[0x00000001]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context]==],
			},
			["name"] = [==[CONTEXT_DEBUG_BIT_ARB]==],
		},
		{
			["value"] = [==[0x00000002]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context]==],
			},
			["name"] = [==[CONTEXT_FORWARD_COMPATIBLE_BIT_ARB]==],
		},
		{
			["value"] = [==[0x2091]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context]==],
			},
			["name"] = [==[CONTEXT_MAJOR_VERSION_ARB]==],
		},
		{
			["value"] = [==[0x2092]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context]==],
			},
			["name"] = [==[CONTEXT_MINOR_VERSION_ARB]==],
		},
		{
			["value"] = [==[0x2093]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context]==],
			},
			["name"] = [==[CONTEXT_LAYER_PLANE_ARB]==],
		},
		{
			["value"] = [==[0x2094]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context]==],
			},
			["name"] = [==[CONTEXT_FLAGS_ARB]==],
		},
		{
			["value"] = [==[0x2095]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context]==],
			},
			["name"] = [==[ERROR_INVALID_VERSION_ARB]==],
		},
		{
			["value"] = [==[0x9126]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context_profile]==],
			},
			["name"] = [==[CONTEXT_PROFILE_MASK_ARB]==],
		},
		{
			["value"] = [==[0x00000001]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context_profile]==],
			},
			["name"] = [==[CONTEXT_CORE_PROFILE_BIT_ARB]==],
		},
		{
			["value"] = [==[0x00000002]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context_profile]==],
			},
			["name"] = [==[CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB]==],
		},
		{
			["value"] = [==[0x2096]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context_profile]==],
			},
			["name"] = [==[ERROR_INVALID_PROFILE_ARB]==],
		},
		{
			["value"] = [==[0x00000004]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context_robustness]==],
			},
			["name"] = [==[CONTEXT_ROBUST_ACCESS_BIT_ARB]==],
		},
		{
			["value"] = [==[0x8252]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context_robustness]==],
			},
			["name"] = [==[LOSE_CONTEXT_ON_RESET_ARB]==],
		},
		{
			["value"] = [==[0x8256]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context_robustness]==],
			},
			["name"] = [==[CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB]==],
		},
		{
			["value"] = [==[0x8261]==],
			["copy"] = false,
			["extensions"] = {
				[==[ARB_create_context_robustness]==],
			},
			["name"] = [==[NO_RESET_NOTIFICATION_ARB]==],
		},
		{
			["value"] = [==[0x2043]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_make_current_read]==],
			},
			["name"] = [==[ERROR_INVALID_PIXEL_TYPE_EXT]==],
		},
		{
			["value"] = [==[0x2000]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[NUMBER_PIXEL_FORMATS_EXT]==],
		},
		{
			["value"] = [==[0x2001]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[DRAW_TO_WINDOW_EXT]==],
		},
		{
			["value"] = [==[0x2002]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[DRAW_TO_BITMAP_EXT]==],
		},
		{
			["value"] = [==[0x2003]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[ACCELERATION_EXT]==],
		},
		{
			["value"] = [==[0x2004]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[NEED_PALETTE_EXT]==],
		},
		{
			["value"] = [==[0x2005]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[NEED_SYSTEM_PALETTE_EXT]==],
		},
		{
			["value"] = [==[0x2006]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SWAP_LAYER_BUFFERS_EXT]==],
		},
		{
			["value"] = [==[0x2007]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SWAP_METHOD_EXT]==],
		},
		{
			["value"] = [==[0x2008]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[NUMBER_OVERLAYS_EXT]==],
		},
		{
			["value"] = [==[0x2009]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[NUMBER_UNDERLAYS_EXT]==],
		},
		{
			["value"] = [==[0x200A]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[TRANSPARENT_EXT]==],
		},
		{
			["value"] = [==[0x200B]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[TRANSPARENT_VALUE_EXT]==],
		},
		{
			["value"] = [==[0x200C]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SHARE_DEPTH_EXT]==],
		},
		{
			["value"] = [==[0x200D]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SHARE_STENCIL_EXT]==],
		},
		{
			["value"] = [==[0x200E]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SHARE_ACCUM_EXT]==],
		},
		{
			["value"] = [==[0x200F]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SUPPORT_GDI_EXT]==],
		},
		{
			["value"] = [==[0x2010]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SUPPORT_OPENGL_EXT]==],
		},
		{
			["value"] = [==[0x2011]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[DOUBLE_BUFFER_EXT]==],
		},
		{
			["value"] = [==[0x2012]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[STEREO_EXT]==],
		},
		{
			["value"] = [==[0x2013]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[PIXEL_TYPE_EXT]==],
		},
		{
			["value"] = [==[0x2014]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[COLOR_BITS_EXT]==],
		},
		{
			["value"] = [==[0x2015]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[RED_BITS_EXT]==],
		},
		{
			["value"] = [==[0x2016]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[RED_SHIFT_EXT]==],
		},
		{
			["value"] = [==[0x2017]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[GREEN_BITS_EXT]==],
		},
		{
			["value"] = [==[0x2018]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[GREEN_SHIFT_EXT]==],
		},
		{
			["value"] = [==[0x2019]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[BLUE_BITS_EXT]==],
		},
		{
			["value"] = [==[0x201A]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[BLUE_SHIFT_EXT]==],
		},
		{
			["value"] = [==[0x201B]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[ALPHA_BITS_EXT]==],
		},
		{
			["value"] = [==[0x201C]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[ALPHA_SHIFT_EXT]==],
		},
		{
			["value"] = [==[0x201D]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[ACCUM_BITS_EXT]==],
		},
		{
			["value"] = [==[0x201E]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[ACCUM_RED_BITS_EXT]==],
		},
		{
			["value"] = [==[0x201F]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[ACCUM_GREEN_BITS_EXT]==],
		},
		{
			["value"] = [==[0x2020]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[ACCUM_BLUE_BITS_EXT]==],
		},
		{
			["value"] = [==[0x2021]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[ACCUM_ALPHA_BITS_EXT]==],
		},
		{
			["value"] = [==[0x2022]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[DEPTH_BITS_EXT]==],
		},
		{
			["value"] = [==[0x2023]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[STENCIL_BITS_EXT]==],
		},
		{
			["value"] = [==[0x2024]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[AUX_BUFFERS_EXT]==],
		},
		{
			["value"] = [==[0x2025]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[NO_ACCELERATION_EXT]==],
		},
		{
			["value"] = [==[0x2026]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[GENERIC_ACCELERATION_EXT]==],
		},
		{
			["value"] = [==[0x2027]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[FULL_ACCELERATION_EXT]==],
		},
		{
			["value"] = [==[0x2028]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SWAP_EXCHANGE_EXT]==],
		},
		{
			["value"] = [==[0x2029]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SWAP_COPY_EXT]==],
		},
		{
			["value"] = [==[0x202A]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[SWAP_UNDEFINED_EXT]==],
		},
		{
			["value"] = [==[0x202B]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[TYPE_RGBA_EXT]==],
		},
		{
			["value"] = [==[0x202C]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format]==],
			},
			["name"] = [==[TYPE_COLORINDEX_EXT]==],
		},
		{
			["value"] = [==[0x202D]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[DRAW_TO_PBUFFER_EXT]==],
		},
		{
			["value"] = [==[0x202E]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[MAX_PBUFFER_PIXELS_EXT]==],
		},
		{
			["value"] = [==[0x202F]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[MAX_PBUFFER_WIDTH_EXT]==],
		},
		{
			["value"] = [==[0x2030]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[MAX_PBUFFER_HEIGHT_EXT]==],
		},
		{
			["value"] = [==[0x2031]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[OPTIMAL_PBUFFER_WIDTH_EXT]==],
		},
		{
			["value"] = [==[0x2032]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[OPTIMAL_PBUFFER_HEIGHT_EXT]==],
		},
		{
			["value"] = [==[0x2033]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[PBUFFER_LARGEST_EXT]==],
		},
		{
			["value"] = [==[0x2034]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[PBUFFER_WIDTH_EXT]==],
		},
		{
			["value"] = [==[0x2035]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pbuffer]==],
			},
			["name"] = [==[PBUFFER_HEIGHT_EXT]==],
		},
		{
			["value"] = [==[0x2040]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_depth_float]==],
			},
			["name"] = [==[DEPTH_FLOAT_EXT]==],
		},
		{
			["value"] = [==[0x2060]==],
			["copy"] = false,
			["extensions"] = {
				[==[3DFX_multisample]==],
			},
			["name"] = [==[SAMPLE_BUFFERS_3DFX]==],
		},
		{
			["value"] = [==[0x2061]==],
			["copy"] = false,
			["extensions"] = {
				[==[3DFX_multisample]==],
			},
			["name"] = [==[SAMPLES_3DFX]==],
		},
		{
			["value"] = [==[0x2041]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_multisample]==],
			},
			["name"] = [==[SAMPLE_BUFFERS_EXT]==],
		},
		{
			["value"] = [==[0x2042]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_multisample]==],
			},
			["name"] = [==[SAMPLES_EXT]==],
		},
		{
			["value"] = [==[0x2050]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_digital_video_control]==],
			},
			["name"] = [==[DIGITAL_VIDEO_CURSOR_ALPHA_FRAMEBUFFER_I3D]==],
		},
		{
			["value"] = [==[0x2051]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_digital_video_control]==],
			},
			["name"] = [==[DIGITAL_VIDEO_CURSOR_ALPHA_VALUE_I3D]==],
		},
		{
			["value"] = [==[0x2052]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_digital_video_control]==],
			},
			["name"] = [==[DIGITAL_VIDEO_CURSOR_INCLUDED_I3D]==],
		},
		{
			["value"] = [==[0x2053]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_digital_video_control]==],
			},
			["name"] = [==[DIGITAL_VIDEO_GAMMA_CORRECTED_I3D]==],
		},
		{
			["value"] = [==[0x204E]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_gamma]==],
			},
			["name"] = [==[GAMMA_TABLE_SIZE_I3D]==],
		},
		{
			["value"] = [==[0x204F]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_gamma]==],
			},
			["name"] = [==[GAMMA_EXCLUDE_DESKTOP_I3D]==],
		},
		{
			["value"] = [==[0x2044]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_MULTIVIEW_I3D]==],
		},
		{
			["value"] = [==[0x2045]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_EXTENAL_SYNC_I3D]==],
		},
		{
			["value"] = [==[0x2046]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_EXTENAL_FIELD_I3D]==],
		},
		{
			["value"] = [==[0x2047]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_EXTENAL_TTL_I3D]==],
		},
		{
			["value"] = [==[0x2048]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_DIGITAL_SYNC_I3D]==],
		},
		{
			["value"] = [==[0x2049]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_DIGITAL_FIELD_I3D]==],
		},
		{
			["value"] = [==[0x204A]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_EDGE_FALLING_I3D]==],
		},
		{
			["value"] = [==[0x204B]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_EDGE_RISING_I3D]==],
		},
		{
			["value"] = [==[0x204C]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_genlock]==],
			},
			["name"] = [==[GENLOCK_SOURCE_EDGE_BOTH_I3D]==],
		},
		{
			["value"] = [==[0x00000001]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_image_buffer]==],
			},
			["name"] = [==[IMAGE_BUFFER_MIN_ACCESS_I3D]==],
		},
		{
			["value"] = [==[0x00000002]==],
			["copy"] = false,
			["extensions"] = {
				[==[I3D_image_buffer]==],
			},
			["name"] = [==[IMAGE_BUFFER_LOCK_I3D]==],
		},
		{
			["value"] = [==[0x20A3]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_render_depth_texture]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_DEPTH_NV]==],
		},
		{
			["value"] = [==[0x20A4]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_render_depth_texture]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RECTANGLE_DEPTH_NV]==],
		},
		{
			["value"] = [==[0x20A5]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_render_depth_texture]==],
			},
			["name"] = [==[DEPTH_TEXTURE_FORMAT_NV]==],
		},
		{
			["value"] = [==[0x20A6]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_render_depth_texture]==],
			},
			["name"] = [==[TEXTURE_DEPTH_COMPONENT_NV]==],
		},
		{
			["value"] = [==[0x20A7]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_render_depth_texture]==],
			},
			["name"] = [==[DEPTH_COMPONENT_NV]==],
		},
		{
			["value"] = [==[0x20A0]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_render_texture_rectangle]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RECTANGLE_RGB_NV]==],
		},
		{
			["value"] = [==[0x20A1]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_render_texture_rectangle]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RECTANGLE_RGBA_NV]==],
		},
		{
			["value"] = [==[0x20A2]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_render_texture_rectangle]==],
			},
			["name"] = [==[TEXTURE_RECTANGLE_NV]==],
		},
		{
			["value"] = [==[0x21A0]==],
			["copy"] = false,
			["extensions"] = {
				[==[ATI_pixel_format_float]==],
			},
			["name"] = [==[TYPE_RGBA_FLOAT_ATI]==],
		},
		{
			["value"] = [==[0x20B0]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[FLOAT_COMPONENTS_NV]==],
		},
		{
			["value"] = [==[0x20B1]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV]==],
		},
		{
			["value"] = [==[0x20B2]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV]==],
		},
		{
			["value"] = [==[0x20B3]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV]==],
		},
		{
			["value"] = [==[0x20B4]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV]==],
		},
		{
			["value"] = [==[0x20B5]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[TEXTURE_FLOAT_R_NV]==],
		},
		{
			["value"] = [==[0x20B6]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[TEXTURE_FLOAT_RG_NV]==],
		},
		{
			["value"] = [==[0x20B7]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[TEXTURE_FLOAT_RGB_NV]==],
		},
		{
			["value"] = [==[0x20B8]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_float_buffer]==],
			},
			["name"] = [==[TEXTURE_FLOAT_RGBA_NV]==],
		},
		{
			["value"] = [==[0x2055]==],
			["copy"] = false,
			["extensions"] = {
				[==[3DL_stereo_control]==],
			},
			["name"] = [==[STEREO_EMITTER_ENABLE_3DL]==],
		},
		{
			["value"] = [==[0x2056]==],
			["copy"] = false,
			["extensions"] = {
				[==[3DL_stereo_control]==],
			},
			["name"] = [==[STEREO_EMITTER_DISABLE_3DL]==],
		},
		{
			["value"] = [==[0x2057]==],
			["copy"] = false,
			["extensions"] = {
				[==[3DL_stereo_control]==],
			},
			["name"] = [==[STEREO_POLARITY_NORMAL_3DL]==],
		},
		{
			["value"] = [==[0x2058]==],
			["copy"] = false,
			["extensions"] = {
				[==[3DL_stereo_control]==],
			},
			["name"] = [==[STEREO_POLARITY_INVERT_3DL]==],
		},
		{
			["value"] = [==[0x20A8]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_pixel_format_packed_float]==],
			},
			["name"] = [==[TYPE_RGBA_UNSIGNED_FLOAT_EXT]==],
		},
		{
			["value"] = [==[0x20A9]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_framebuffer_sRGB]==],
			},
			["name"] = [==[FRAMEBUFFER_SRGB_CAPABLE_EXT]==],
		},
		{
			["value"] = [==[0x20F0]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_present_video]==],
			},
			["name"] = [==[NUM_VIDEO_SLOTS_NV]==],
		},
		{
			["value"] = [==[0x20C0]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[BIND_TO_VIDEO_RGB_NV]==],
		},
		{
			["value"] = [==[0x20C1]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[BIND_TO_VIDEO_RGBA_NV]==],
		},
		{
			["value"] = [==[0x20C2]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[BIND_TO_VIDEO_RGB_AND_DEPTH_NV]==],
		},
		{
			["value"] = [==[0x20C3]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_COLOR_NV]==],
		},
		{
			["value"] = [==[0x20C4]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_ALPHA_NV]==],
		},
		{
			["value"] = [==[0x20C5]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_DEPTH_NV]==],
		},
		{
			["value"] = [==[0x20C6]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_COLOR_AND_ALPHA_NV]==],
		},
		{
			["value"] = [==[0x20C7]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_COLOR_AND_DEPTH_NV]==],
		},
		{
			["value"] = [==[0x20C8]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_FRAME]==],
		},
		{
			["value"] = [==[0x20C9]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_FIELD_1]==],
		},
		{
			["value"] = [==[0x20CA]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_FIELD_2]==],
		},
		{
			["value"] = [==[0x20CB]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_STACKED_FIELDS_1_2]==],
		},
		{
			["value"] = [==[0x20CC]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_out]==],
			},
			["name"] = [==[VIDEO_OUT_STACKED_FIELDS_2_1]==],
		},
		{
			["value"] = [==[0x20D0]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_gpu_affinity]==],
			},
			["name"] = [==[ERROR_INCOMPATIBLE_AFFINITY_MASKS_NV]==],
		},
		{
			["value"] = [==[0x20D1]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_gpu_affinity]==],
			},
			["name"] = [==[ERROR_MISSING_AFFINITY_MASK_NV]==],
		},
		{
			["value"] = [==[0x1F00]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_VENDOR_AMD]==],
		},
		{
			["value"] = [==[0x1F01]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_RENDERER_STRING_AMD]==],
		},
		{
			["value"] = [==[0x1F02]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_OPENGL_VERSION_STRING_AMD]==],
		},
		{
			["value"] = [==[0x21A2]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_FASTEST_TARGET_GPUS_AMD]==],
		},
		{
			["value"] = [==[0x21A3]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_RAM_AMD]==],
		},
		{
			["value"] = [==[0x21A4]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_CLOCK_AMD]==],
		},
		{
			["value"] = [==[0x21A5]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_NUM_PIPES_AMD]==],
		},
		{
			["value"] = [==[0x21A6]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_NUM_SIMD_AMD]==],
		},
		{
			["value"] = [==[0x21A7]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_NUM_RB_AMD]==],
		},
		{
			["value"] = [==[0x21A8]==],
			["copy"] = false,
			["extensions"] = {
				[==[AMD_gpu_association]==],
			},
			["name"] = [==[GPU_NUM_SPI_AMD]==],
		},
		{
			["value"] = [==[0x20CE]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_capture]==],
			},
			["name"] = [==[UNIQUE_ID_NV]==],
		},
		{
			["value"] = [==[0x20CF]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_video_capture]==],
			},
			["name"] = [==[NUM_VIDEO_CAPTURE_SLOTS_NV]==],
		},
		{
			["value"] = [==[0x2042]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_multisample_coverage]==],
			},
			["name"] = [==[COVERAGE_SAMPLES_NV]==],
		},
		{
			["value"] = [==[0x20B9]==],
			["copy"] = false,
			["extensions"] = {
				[==[NV_multisample_coverage]==],
			},
			["name"] = [==[COLOR_SAMPLES_NV]==],
		},
		{
			["value"] = [==[0x00000004]==],
			["copy"] = false,
			["extensions"] = {
				[==[EXT_create_context_es2_profile]==],
			},
			["name"] = [==[CONTEXT_ES2_PROFILE_BIT_EXT]==],
		},
	},
};
