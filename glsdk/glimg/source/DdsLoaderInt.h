/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLIMG_DIRECT_DRAW_SURFACE_INTERNAL_LOADER_H
#define GLIMG_DIRECT_DRAW_SURFACE_INTERNAL_LOADER_H


namespace glimg
{
	namespace
	{
		typedef unsigned int DWORD;

		enum MagicNumbers
		{
			DDS_MAGIC_NUMBER		= 0x20534444,	//"DDS "
			DDS10_FOUR_CC			= 0x30314458,	//"DX10"

			DDSFOURCC_DXT1			= 0x31545844, //"DXT1"
			DDSFOURCC_DXT3			= 0x33545844, //"DXT3"
			DDSFOURCC_DXT5			= 0x35545844, //"DXT5"
		};

		struct ddsPixelFormat
		{
			DWORD			dwSize;
			DWORD			dwFlags;
			DWORD			dwFourCC;
			DWORD			dwRGBBitCount;
			DWORD			dwRBitMask;
			DWORD			dwGBitMask;
			DWORD			dwBBitMask;
			DWORD			dwABitMask;
		};

		enum ddsPixelFormatFlags
		{
			DDPF_ALPHAPIXELS		= 0x00000001,
			DDPF_ALPHA				= 0x00000002,
			DDPF_FOURCC				= 0x00000004,
			DDPF_RGB				= 0x00000040,
			DDPF_YUV				= 0x00000200,
			DDPF_LUMINANCE			= 0x00020000,
		};

		struct ddsHeader
		{
			DWORD			dwSize;
			DWORD			dwFlags;
			DWORD			dwHeight;
			DWORD			dwWidth;
			DWORD			dwPitchOrLinearSize;
			DWORD			dwDepth;
			DWORD			dwMipMapCount;
			DWORD			dwReserved1[11];
			ddsPixelFormat	ddspf;
			DWORD			dwCaps;
			DWORD			dwCaps2;
			DWORD			dwCaps3;
			DWORD			dwCaps4;
			DWORD			dwReserved2;
		};

		enum ddsFlags
		{
			DDSD_CAPS                   = 0x00000001,
			DDSD_HEIGHT                 = 0x00000002,
			DDSD_WIDTH                  = 0x00000004,
			DDSD_PITCH                  = 0x00000008,
			DDSD_PIXELFORMAT            = 0x00001000,
			DDSD_MIPMAPCOUNT            = 0x00020000,
			DDSD_LINEARSIZE             = 0x00080000,
			DDSD_DEPTH                  = 0x00800000,
		};

		enum ddsCaps
		{
			DDSCAPS_COMPLEX				= 0x00000008,
			DDSCAPS_MIPMAP				= 0x00400000,
			DDSCAPS_TEXTURE				= 0x00001000,
		};

		enum ddsCaps2
		{
			DDSCAPS2_CUBEMAP			= 0x00000200,
			DDSCAPS2_CUBEMAP_POSITIVEX	= 0x00000400,
			DDSCAPS2_CUBEMAP_NEGATIVEX	= 0x00000800,
			DDSCAPS2_CUBEMAP_POSITIVEY	= 0x00001000,
			DDSCAPS2_CUBEMAP_NEGATIVEY	= 0x00002000,
			DDSCAPS2_CUBEMAP_POSITIVEZ	= 0x00004000,
			DDSCAPS2_CUBEMAP_NEGATIVEZ	= 0x00008000,
			DDSCAPS2_VOLUME				= 0x00200000,

			DDSCAPS2_CUBEMAP_ALL		= DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX |
											DDSCAPS2_CUBEMAP_NEGATIVEX | DDSCAPS2_CUBEMAP_POSITIVEY |
											DDSCAPS2_CUBEMAP_NEGATIVEY | DDSCAPS2_CUBEMAP_POSITIVEZ |
											DDSCAPS2_CUBEMAP_NEGATIVEZ,
		};

		struct dds10Header
		{
			DWORD			dxgiFormat;
			DWORD			resourceDimension;
			DWORD			miscFlag;
			DWORD			arraySize;
			DWORD			reserved;
		};

		enum dds10ResourceDimensions
		{
			DDS_DIMENSION_TEXTURE1D		= 2,
			DDS_DIMENSION_TEXTURE2D		= 3,
			DDS_DIMENSION_TEXTURE3D		= 4,
		};

		enum dds10MiscFlags
		{
			DDS_RESOURCE_MISC_TEXTURECUBE	= 0x00000004,
		};

		enum DXGI_FORMAT
		{
			DXGI_FORMAT_UNKNOWN                      = 0,
			DXGI_FORMAT_R32G32B32A32_TYPELESS        = 1,
			DXGI_FORMAT_R32G32B32A32_FLOAT           = 2,
			DXGI_FORMAT_R32G32B32A32_UINT            = 3,
			DXGI_FORMAT_R32G32B32A32_SINT            = 4,
			DXGI_FORMAT_R32G32B32_TYPELESS           = 5,
			DXGI_FORMAT_R32G32B32_FLOAT              = 6,
			DXGI_FORMAT_R32G32B32_UINT               = 7,
			DXGI_FORMAT_R32G32B32_SINT               = 8,
			DXGI_FORMAT_R16G16B16A16_TYPELESS        = 9,
			DXGI_FORMAT_R16G16B16A16_FLOAT           = 10,
			DXGI_FORMAT_R16G16B16A16_UNORM           = 11,
			DXGI_FORMAT_R16G16B16A16_UINT            = 12,
			DXGI_FORMAT_R16G16B16A16_SNORM           = 13,
			DXGI_FORMAT_R16G16B16A16_SINT            = 14,
			DXGI_FORMAT_R32G32_TYPELESS              = 15,
			DXGI_FORMAT_R32G32_FLOAT                 = 16,
			DXGI_FORMAT_R32G32_UINT                  = 17,
			DXGI_FORMAT_R32G32_SINT                  = 18,
			DXGI_FORMAT_R32G8X24_TYPELESS            = 19,
			DXGI_FORMAT_D32_FLOAT_S8X24_UINT         = 20,
			DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS     = 21,
			DXGI_FORMAT_X32_TYPELESS_G8X24_UINT      = 22,
			DXGI_FORMAT_R10G10B10A2_TYPELESS         = 23,
			DXGI_FORMAT_R10G10B10A2_UNORM            = 24,
			DXGI_FORMAT_R10G10B10A2_UINT             = 25,
			DXGI_FORMAT_R11G11B10_FLOAT              = 26,
			DXGI_FORMAT_R8G8B8A8_TYPELESS            = 27,
			DXGI_FORMAT_R8G8B8A8_UNORM               = 28,
			DXGI_FORMAT_R8G8B8A8_UNORM_SRGB          = 29,
			DXGI_FORMAT_R8G8B8A8_UINT                = 30,
			DXGI_FORMAT_R8G8B8A8_SNORM               = 31,
			DXGI_FORMAT_R8G8B8A8_SINT                = 32,
			DXGI_FORMAT_R16G16_TYPELESS              = 33,
			DXGI_FORMAT_R16G16_FLOAT                 = 34,
			DXGI_FORMAT_R16G16_UNORM                 = 35,
			DXGI_FORMAT_R16G16_UINT                  = 36,
			DXGI_FORMAT_R16G16_SNORM                 = 37,
			DXGI_FORMAT_R16G16_SINT                  = 38,
			DXGI_FORMAT_R32_TYPELESS                 = 39,
			DXGI_FORMAT_D32_FLOAT                    = 40,
			DXGI_FORMAT_R32_FLOAT                    = 41,
			DXGI_FORMAT_R32_UINT                     = 42,
			DXGI_FORMAT_R32_SINT                     = 43,
			DXGI_FORMAT_R24G8_TYPELESS               = 44,
			DXGI_FORMAT_D24_UNORM_S8_UINT            = 45,
			DXGI_FORMAT_R24_UNORM_X8_TYPELESS        = 46,
			DXGI_FORMAT_X24_TYPELESS_G8_UINT         = 47,
			DXGI_FORMAT_R8G8_TYPELESS                = 48,
			DXGI_FORMAT_R8G8_UNORM                   = 49,
			DXGI_FORMAT_R8G8_UINT                    = 50,
			DXGI_FORMAT_R8G8_SNORM                   = 51,
			DXGI_FORMAT_R8G8_SINT                    = 52,
			DXGI_FORMAT_R16_TYPELESS                 = 53,
			DXGI_FORMAT_R16_FLOAT                    = 54,
			DXGI_FORMAT_D16_UNORM                    = 55,
			DXGI_FORMAT_R16_UNORM                    = 56,
			DXGI_FORMAT_R16_UINT                     = 57,
			DXGI_FORMAT_R16_SNORM                    = 58,
			DXGI_FORMAT_R16_SINT                     = 59,
			DXGI_FORMAT_R8_TYPELESS                  = 60,
			DXGI_FORMAT_R8_UNORM                     = 61,
			DXGI_FORMAT_R8_UINT                      = 62,
			DXGI_FORMAT_R8_SNORM                     = 63,
			DXGI_FORMAT_R8_SINT                      = 64,
			DXGI_FORMAT_A8_UNORM                     = 65,
			DXGI_FORMAT_R1_UNORM                     = 66,
			DXGI_FORMAT_R9G9B9E5_SHAREDEXP           = 67,
			DXGI_FORMAT_R8G8_B8G8_UNORM              = 68,
			DXGI_FORMAT_G8R8_G8B8_UNORM              = 69,
			DXGI_FORMAT_BC1_TYPELESS                 = 70,
			DXGI_FORMAT_BC1_UNORM                    = 71,
			DXGI_FORMAT_BC1_UNORM_SRGB               = 72,
			DXGI_FORMAT_BC2_TYPELESS                 = 73,
			DXGI_FORMAT_BC2_UNORM                    = 74,
			DXGI_FORMAT_BC2_UNORM_SRGB               = 75,
			DXGI_FORMAT_BC3_TYPELESS                 = 76,
			DXGI_FORMAT_BC3_UNORM                    = 77,
			DXGI_FORMAT_BC3_UNORM_SRGB               = 78,
			DXGI_FORMAT_BC4_TYPELESS                 = 79,
			DXGI_FORMAT_BC4_UNORM                    = 80,
			DXGI_FORMAT_BC4_SNORM                    = 81,
			DXGI_FORMAT_BC5_TYPELESS                 = 82,
			DXGI_FORMAT_BC5_UNORM                    = 83,
			DXGI_FORMAT_BC5_SNORM                    = 84,
			DXGI_FORMAT_B5G6R5_UNORM                 = 85,
			DXGI_FORMAT_B5G5R5A1_UNORM               = 86,
			DXGI_FORMAT_B8G8R8A8_UNORM               = 87,
			DXGI_FORMAT_B8G8R8X8_UNORM               = 88,
			DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM   = 89,
			DXGI_FORMAT_B8G8R8A8_TYPELESS            = 90,
			DXGI_FORMAT_B8G8R8A8_UNORM_SRGB          = 91,
			DXGI_FORMAT_B8G8R8X8_TYPELESS            = 92,
			DXGI_FORMAT_B8G8R8X8_UNORM_SRGB          = 93,
			DXGI_FORMAT_BC6H_TYPELESS                = 94,
			DXGI_FORMAT_BC6H_UF16                    = 95,
			DXGI_FORMAT_BC6H_SF16                    = 96,
			DXGI_FORMAT_BC7_TYPELESS                 = 97,
			DXGI_FORMAT_BC7_UNORM                    = 98,
			DXGI_FORMAT_BC7_UNORM_SRGB               = 99,
			DXGI_FORMAT_FORCE_UINT                   = 0xffffffffUL 
		};

	}
}


#endif //GLIMG_DIRECT_DRAW_SURFACE_INTERNAL_LOADER_H	
