// ==========================================================
// TIFF Loader and Writer
//
// Design and implementation by 
// - Floris van den Berg (flvdberg@wxs.nl)
// - Hervé Drolon (drolon@infonie.fr)
// - Markus Loibl (markus.loibl@epost.de)
// - Luca Piergentili (l.pierge@terra.es)
// - Detlev Vendt (detlev.vendt@brillit.de)
//
// This file is part of FreeImage 3
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at your own risk!
// ==========================================================

#ifdef _MSC_VER 
#pragma warning (disable : 4786) // identifier was truncated to 'number' characters
#endif

#ifdef unix
#undef unix
#endif
#ifdef __unix
#undef __unix
#endif

#include "../LibTIFF/tiffiop.h"
#include "FreeImage.h"
#include "Utilities.h"
#include "../Metadata/FreeImageTag.h"

// ----------------------------------------------------------
//   geotiff interface (see XTIFF.cpp)
// ----------------------------------------------------------

// Extended TIFF Directory GEO Tag Support
void XTIFFInitialize();

// GeoTIFF profile
void tiff_read_geotiff_profile(TIFF *tif, FIBITMAP *dib);
void tiff_write_geotiff_profile(TIFF *tif, FIBITMAP *dib);

// ----------------------------------------------------------
//   exif interface (see XTIFF.cpp)
// ----------------------------------------------------------

// TIFF Exif profile
BOOL tiff_read_exif_tags(TIFF *tif, TagLib::MDMODEL md_model, FIBITMAP *dib);

// ----------------------------------------------------------
//   LogLuv conversion functions interface (see TIFFLogLuv.cpp)
// ----------------------------------------------------------

void tiff_ConvertLineXYZToRGB(BYTE *target, BYTE *source, double stonits, int width_in_pixels);
void tiff_ConvertLineRGBToXYZ(BYTE *target, BYTE *source, int width_in_pixels);

// ----------------------------------------------------------

/** Supported loading methods */
typedef enum {
	LoadAsRBGA			= 0, 
	LoadAsCMYK			= 1, 
	LoadAs8BitTrns		= 2, 
	LoadAsGenericStrip	= 3, 
	LoadAsTiled			= 4,
	LoadAsRGBF			= 5
} TIFFLoadMethod;

// ----------------------------------------------------------
//   local prototypes
// ----------------------------------------------------------

static tsize_t _tiffReadProc(thandle_t handle, tdata_t buf, tsize_t size);
static tsize_t _tiffWriteProc(thandle_t handle, tdata_t buf, tsize_t size);
static toff_t _tiffSeekProc(thandle_t handle, toff_t off, int whence);
static int _tiffCloseProc(thandle_t fd);
static int _tiffMapProc(thandle_t fd, tdata_t* pbase, toff_t* psize);
static void _tiffUnmapProc(thandle_t fd, tdata_t base, toff_t size);

static uint16 CheckColormap(int n, uint16* r, uint16* g, uint16* b);
static uint16 GetPhotometric(FIBITMAP *dib);

static void ReadResolution(TIFF *tiff, FIBITMAP *dib);
static void WriteResolution(TIFF *tiff, FIBITMAP *dib);

static void ReadPalette(TIFF *tiff, uint16 photometric, uint16 bitspersample, FIBITMAP *dib);

static FIBITMAP* CreateImageType(FREE_IMAGE_TYPE fit, int width, int height, uint16 bitspersample, uint16 samplesperpixel);
static FREE_IMAGE_TYPE ReadImageType(TIFF *tiff, uint16 bitspersample, uint16 samplesperpixel);
static void WriteImageType(TIFF *tiff, FREE_IMAGE_TYPE fit);

static void WriteCompression(TIFF *tiff, uint16 bitspersample, uint16 samplesperpixel, uint16 photometric, int flags);

static BOOL tiff_read_iptc_profile(TIFF *tiff, FIBITMAP *dib);
static BOOL tiff_read_xmp_profile(TIFF *tiff, FIBITMAP *dib);
static BOOL tiff_read_exif_profile(TIFF *tiff, FIBITMAP *dib);
static void ReadMetadata(TIFF *tiff, FIBITMAP *dib);

static BOOL tiff_write_iptc_profile(TIFF *tiff, FIBITMAP *dib);
static BOOL tiff_write_xmp_profile(TIFF *tiff, FIBITMAP *dib);
static void WriteMetadata(TIFF *tiff, FIBITMAP *dib);

static TIFFLoadMethod FindLoadMethod(TIFF *tif, uint16 photometric, uint16 bitspersample, uint16 samplesperpixel, FREE_IMAGE_TYPE image_type, int flags);


// ==========================================================
// Plugin Interface
// ==========================================================

static int s_format_id;

typedef struct {
    FreeImageIO *io;
	fi_handle handle;
	TIFF *tif;
} fi_TIFFIO;

// ----------------------------------------------------------
//   libtiff interface 
// ----------------------------------------------------------

static tsize_t 
_tiffReadProc(thandle_t handle, tdata_t buf, tsize_t size) {
	fi_TIFFIO *fio = (fi_TIFFIO*)handle;
	return fio->io->read_proc(buf, size, 1, fio->handle) * size;
}

static tsize_t
_tiffWriteProc(thandle_t handle, tdata_t buf, tsize_t size) {
	fi_TIFFIO *fio = (fi_TIFFIO*)handle;
	return fio->io->write_proc(buf, size, 1, fio->handle) * size;
}

static toff_t
_tiffSeekProc(thandle_t handle, toff_t off, int whence) {
	fi_TIFFIO *fio = (fi_TIFFIO*)handle;
	fio->io->seek_proc(fio->handle, off, whence);
	return fio->io->tell_proc(fio->handle);
}

static int
_tiffCloseProc(thandle_t fd) {
	return 0;
}

#include <sys/stat.h>

static toff_t
_tiffSizeProc(thandle_t handle) {
    fi_TIFFIO *fio = (fi_TIFFIO*)handle;
    long currPos = fio->io->tell_proc(fio->handle);
    fio->io->seek_proc(fio->handle, 0, SEEK_END);
    long fileSize = fio->io->tell_proc(fio->handle);
    fio->io->seek_proc(fio->handle, currPos, SEEK_SET);
    return fileSize;
}

static int
_tiffMapProc(thandle_t fd, tdata_t* pbase, toff_t* psize) {
	return 0;
}

static void
_tiffUnmapProc(thandle_t fd, tdata_t base, toff_t size) {
}

// ----------------------------------------------------------
//   Open a TIFF file descriptor for read/writing.
// ----------------------------------------------------------

TIFF *
TIFFFdOpen(thandle_t handle, const char *name, const char *mode) {
	TIFF *tif;

    // Set up the callback for extended TIFF directory tag support
	// (see XTIFF.cpp)
    XTIFFInitialize();	
	
	// Open the file; the callback will set everything up
	tif = TIFFClientOpen(name, mode, handle,
	    _tiffReadProc, _tiffWriteProc, _tiffSeekProc, _tiffCloseProc,
	    _tiffSizeProc, _tiffMapProc, _tiffUnmapProc);

	// Warning: tif_fd is declared as 'int' currently (see libTIFF), 
    // may result in incorrect file pointers inside libTIFF on 
    // 64bit machines (sizeof(int) != sizeof(long)). 
    // Needs to be fixed within libTIFF.
    if (tif)
		tif->tif_fd = (long)handle;

	return tif;
}

// ----------------------------------------------------------
//   Open a TIFF file for read/writing.
// ----------------------------------------------------------

TIFF*
TIFFOpen(const char* name, const char* mode) {
	return 0;
}

// ----------------------------------------------------------
//   TIFF library FreeImage-specific routines.
// ----------------------------------------------------------

tdata_t
_TIFFmalloc(tsize_t s) {
	return malloc(s);
}

void
_TIFFfree(tdata_t p) {
	free(p);
}

tdata_t
_TIFFrealloc(tdata_t p, tsize_t s) {
	return realloc(p, s);
}

void
_TIFFmemset(tdata_t p, int v, tsize_t c) {
	memset(p, v, (size_t) c);
}

void
_TIFFmemcpy(tdata_t d, const tdata_t s, tsize_t c) {
	memcpy(d, s, (size_t) c);
}

int
_TIFFmemcmp(const tdata_t p1, const tdata_t p2, tsize_t c) {
	return (memcmp(p1, p2, (size_t) c));
}

// ----------------------------------------------------------
//   in FreeImage warnings and errors are disabled
// ----------------------------------------------------------

static void
msdosWarningHandler(const char* module, const char* fmt, va_list ap) {
}

TIFFErrorHandler _TIFFwarningHandler = msdosWarningHandler;

static void
msdosErrorHandler(const char* module, const char* fmt, va_list ap) {
	
	// use this for diagnostic only (do not use otherwise, even in DEBUG mode)
	/*
	if (module != NULL) {
		char msg[1024];
		vsprintf(msg, fmt, ap);
		FreeImage_OutputMessageProc(s_format_id, "%s: %s", module, msg);
	}
	*/
}

TIFFErrorHandler _TIFFerrorHandler = msdosErrorHandler;

// ----------------------------------------------------------

#define CVT(x)      (((x) * 255L) / ((1L<<16)-1))
#define	SCALE(x)	(((x)*((1L<<16)-1))/255)

// ==========================================================
// Internal functions
// ==========================================================

static uint16
CheckColormap(int n, uint16* r, uint16* g, uint16* b) {
    while (n-- > 0) {
        if (*r++ >= 256 || *g++ >= 256 || *b++ >= 256) {
			return 16;
		}
	}

    return 8;
}

/**
Get the TIFFTAG_PHOTOMETRIC value from the dib
*/
static uint16
GetPhotometric(FIBITMAP *dib) {
	FREE_IMAGE_COLOR_TYPE color_type = FreeImage_GetColorType(dib);
	switch(color_type) {
		case FIC_MINISWHITE:	// min value is white
			return PHOTOMETRIC_MINISWHITE;
		case FIC_MINISBLACK:	// min value is black
			return PHOTOMETRIC_MINISBLACK;
		case FIC_PALETTE:		// color map indexed
			return PHOTOMETRIC_PALETTE;
		case FIC_RGB:			// RGB color model
		case FIC_RGBALPHA:		// RGB color model with alpha channel
			return PHOTOMETRIC_RGB;
		case FIC_CMYK:			// CMYK color model
			return PHOTOMETRIC_RGB;	// default to RGB unless the save flag is set to TIFF_CMYK
		default:
			return PHOTOMETRIC_MINISBLACK;
	}
}

/**
Get the resolution from the TIFF and fill the dib with universal units
*/
static void 
ReadResolution(TIFF *tiff, FIBITMAP *dib) {
	float fResX = 300.0;
	float fResY = 300.0;
	uint16 resUnit = RESUNIT_INCH;

	TIFFGetField(tiff, TIFFTAG_RESOLUTIONUNIT, &resUnit);
	TIFFGetField(tiff, TIFFTAG_XRESOLUTION, &fResX);
	TIFFGetField(tiff, TIFFTAG_YRESOLUTION, &fResY);
	
	// If we don't have a valid resolution unit and valid resolution is specified then assume inch
	if (resUnit == RESUNIT_NONE && fResX > 0.0 && fResY > 0.0) {
		resUnit = RESUNIT_INCH;
	}
	if (resUnit == RESUNIT_INCH) {
		FreeImage_SetDotsPerMeterX(dib, (unsigned) (fResX/0.0254000 + 0.5));
		FreeImage_SetDotsPerMeterY(dib, (unsigned) (fResY/0.0254000 + 0.5));
	} else if(resUnit == RESUNIT_CENTIMETER) {
		FreeImage_SetDotsPerMeterX(dib, (unsigned) (fResX*100.0 + 0.5));
		FreeImage_SetDotsPerMeterY(dib, (unsigned) (fResY*100.0 + 0.5));
	}
}

/**
Set the resolution to the TIFF using english units
*/
static void 
WriteResolution(TIFF *tiff, FIBITMAP *dib) {
	double res;

	TIFFSetField(tiff, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);

	res = (unsigned long) (0.5 + 0.0254 * FreeImage_GetDotsPerMeterX(dib));
	TIFFSetField(tiff, TIFFTAG_XRESOLUTION, res);

	res = (unsigned long) (0.5 + 0.0254 * FreeImage_GetDotsPerMeterY(dib));
	TIFFSetField(tiff, TIFFTAG_YRESOLUTION, res);
}

/**
Fill the dib palette according to the TIFF photometric
*/
static void 
ReadPalette(TIFF *tiff, uint16 photometric, uint16 bitspersample, FIBITMAP *dib) {
	RGBQUAD *pal = FreeImage_GetPalette(dib);

	switch(photometric) {
		case PHOTOMETRIC_MINISBLACK:	// bitmap and greyscale image types
		case PHOTOMETRIC_MINISWHITE:
			// Monochrome image

			if (bitspersample == 1) {
				if (photometric == PHOTOMETRIC_MINISWHITE) {
					pal[0].rgbRed = pal[0].rgbGreen = pal[0].rgbBlue = 255;
					pal[1].rgbRed = pal[1].rgbGreen = pal[1].rgbBlue = 0;
				} else {
					pal[0].rgbRed = pal[0].rgbGreen = pal[0].rgbBlue = 0;
					pal[1].rgbRed = pal[1].rgbGreen = pal[1].rgbBlue = 255;
				}

			} else if ((bitspersample == 4) ||(bitspersample == 8)) {
				// need to build the scale for greyscale images
				int ncolors = FreeImage_GetColorsUsed(dib);

				if (photometric == PHOTOMETRIC_MINISBLACK) {
					for (int i = 0; i < ncolors; i++) {
						pal[i].rgbRed	=
						pal[i].rgbGreen =
						pal[i].rgbBlue	= (BYTE)(i*(255/(ncolors-1)));
					}
				} else {
					for (int i = 0; i < ncolors; i++) {
						pal[i].rgbRed	=
						pal[i].rgbGreen =
						pal[i].rgbBlue	= (BYTE)(255-i*(255/(ncolors-1)));
					}
				}
			}

			break;

		case PHOTOMETRIC_PALETTE:	// color map indexed
			uint16 *red;
			uint16 *green;
			uint16 *blue;
			
			TIFFGetField(tiff, TIFFTAG_COLORMAP, &red, &green, &blue); 

			// load the palette in the DIB

			if (CheckColormap(1<<bitspersample, red, green, blue) == 16) {
				for (int i = (1 << bitspersample) - 1; i >= 0; i--) {
					pal[i].rgbRed =(BYTE) CVT(red[i]);
					pal[i].rgbGreen = (BYTE) CVT(green[i]);
					pal[i].rgbBlue = (BYTE) CVT(blue[i]);           
				}
			} else {
				for (int i = (1 << bitspersample) - 1; i >= 0; i--) {
					pal[i].rgbRed = (BYTE) red[i];
					pal[i].rgbGreen = (BYTE) green[i];
					pal[i].rgbBlue = (BYTE) blue[i];        
				}
			}

			break;						
	}
}

/** 
Allocate a FIBITMAP
@param fit Image type
@param width Image width in pixels
@param height Image height in pixels
@param bitspersample # bits per sample
@param samplesperpixel # samples per pixel
@return Returns the allocated image if successful, returns NULL otherwise
*/
static FIBITMAP* 
CreateImageType(FREE_IMAGE_TYPE fit, int width, int height, uint16 bitspersample, uint16 samplesperpixel) {
	FIBITMAP *dib = NULL;

	uint16 bpp = bitspersample * samplesperpixel;

	if(fit == FIT_BITMAP) {
		// standard bitmap type 

		if(bitspersample == 16) {
			if(samplesperpixel == 1) {
				// 16-bit greyscale -> convert to 8-bit
				dib = FreeImage_Allocate(width, height, 8);
			}
			else if(samplesperpixel == 3) {
				// 48-bit RGB -> convert to 24-bit RGB
				dib = FreeImage_Allocate(width, height, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
			}
		}
		else if(bpp == 16) {
			if((samplesperpixel == 2) && (bitspersample == 8)) {
				// 8-bit indexed + 8-bit alpha channel -> convert to 8-bit transparent
				dib = FreeImage_Allocate(width, height, 8);
			} else {
				// 16-bit RGB -> expect it to be 565
				dib = FreeImage_Allocate(width, height, bpp, FI16_565_RED_MASK, FI16_565_GREEN_MASK, FI16_565_BLUE_MASK);
			}
		}
		else if(bpp == 24) {
			// BGR
			dib = FreeImage_Allocate(width, height, bpp, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		}
		else if(bpp == 32) {
			// BGRA
			dib = FreeImage_Allocate(width, height, bpp, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		}
		else {
			// anything else <= 8-bit
			dib = FreeImage_Allocate(width, height, bpp);
		}
	} else {
		// other bitmap types
		
		dib = FreeImage_AllocateT(fit, width, height, bpp);
	}

	return dib;
}

/** 
Read the TIFFTAG_SAMPLEFORMAT tag and convert to FREE_IMAGE_TYPE
@param tiff LibTIFF TIFF Handle
@param bitspersample # bit per sample
@param samplesperpixel # samples per pixel
@return Returns the image type as a FREE_IMAGE_TYPE value
*/
static FREE_IMAGE_TYPE 
ReadImageType(TIFF *tiff, uint16 bitspersample, uint16 samplesperpixel) {
	uint16 sampleformat = 0;
	FREE_IMAGE_TYPE fit = FIT_BITMAP;

	uint16 bpp = bitspersample * samplesperpixel;

	// try the sampleformat tag
    if(TIFFGetField(tiff, TIFFTAG_SAMPLEFORMAT, &sampleformat)) {

        switch (sampleformat) {
			case SAMPLEFORMAT_UINT:
				switch (bpp) {
					case 1:
					case 4:
					case 8:
					case 24:
						fit = FIT_BITMAP;
						break;
					case 16:
						// 8-bit + alpha or 16-bit greyscale
						if(samplesperpixel == 2) {
							fit = FIT_BITMAP;
						} else {
							fit = FIT_UINT16;
						}
						break;
					case 32:
						if(samplesperpixel == 4) {
							fit = FIT_BITMAP;
						} else {
							fit = FIT_UINT32;
						}
						break;
					case 48:
						if(samplesperpixel == 3) {
							fit = FIT_RGB16;
						}
						break;
					case 64:
						if(samplesperpixel == 4) {
							fit = FIT_RGBA16;
						}
						break;
				}
				break;

			case SAMPLEFORMAT_INT:
				switch (bpp) {
					case 16:
						if(samplesperpixel == 3) {
							fit = FIT_BITMAP;
						} else {
							fit = FIT_INT16;
						}
						break;
					case 32:
						fit = FIT_INT32;
						break;
				}
				break;

			case SAMPLEFORMAT_IEEEFP:
				switch (bpp) {
					case 32:
						fit = FIT_FLOAT;
						break;
					case 64:
						fit = FIT_DOUBLE;
						break;
					case 96:
						fit = FIT_RGBF;
						break;
				}
				break;
			case SAMPLEFORMAT_COMPLEXIEEEFP:
				switch (bpp) {
					case 64:
						break;
					case 128:
						fit = FIT_COMPLEX;
						break;
				}
				break;

			}
    }
	// no sampleformat tag : assume SAMPLEFORMAT_UINT
	else {
		if(samplesperpixel == 1) {
			switch (bpp) {
				case 16:
					fit = FIT_UINT16;
					break;
					
				case 32:
					fit = FIT_UINT32;
					break;
			}
		}
		else if(samplesperpixel == 3) {
			if(bpp == 48) fit = FIT_RGB16;
		}
		else if(samplesperpixel == 4) {
			if(bpp == 64) fit = FIT_RGBA16;
		}

	}

    return fit;
}

/** 
Convert FREE_IMAGE_TYPE and write TIFFTAG_SAMPLEFORMAT
@param tiff LibTIFF TIFF Handle
@param fit Image type as a FREE_IMAGE_TYPE value
*/
static void 
WriteImageType(TIFF *tiff, FREE_IMAGE_TYPE fit) {
	switch(fit) {
		case FIT_BITMAP:	// standard image: 1-, 4-, 8-, 16-, 24-, 32-bit
		case FIT_UINT16:	// array of unsigned short	: unsigned 16-bit
		case FIT_UINT32:	// array of unsigned long	: unsigned 32-bit
		case FIT_RGB16:		// 48-bit RGB image			: 3 x 16-bit
		case FIT_RGBA16:	// 64-bit RGBA image		: 4 x 16-bit
			TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
			break;

		case FIT_INT16:		// array of short	: signed 16-bit
		case FIT_INT32:		// array of long	: signed 32-bit
			TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_INT);
			break;

		case FIT_FLOAT:		// array of float	: 32-bit
		case FIT_DOUBLE:	// array of double	: 64-bit
		case FIT_RGBF:		// 96-bit RGB float image	: 3 x 32-bit IEEE floating point
		case FIT_RGBAF:		// 128-bit RGBA float image	: 4 x 32-bit IEEE floating point
			TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_IEEEFP);
			break;

		case FIT_COMPLEX:	// array of COMPLEX : 2 x 64-bit
			TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_COMPLEXIEEEFP);
			break;
	}
}

/**
Select the compression algorithm
@param tiff LibTIFF TIFF Handle
@param 
*/
static void 
WriteCompression(TIFF *tiff, uint16 bitspersample, uint16 samplesperpixel, uint16 photometric, int flags) {
	uint16 compression;
	uint16 bitsperpixel = bitspersample * samplesperpixel;

	if(photometric == PHOTOMETRIC_LOGLUV) {
		compression = COMPRESSION_SGILOG;
	} else if ((flags & TIFF_PACKBITS) == TIFF_PACKBITS) {
		compression = COMPRESSION_PACKBITS;
	} else if ((flags & TIFF_DEFLATE) == TIFF_DEFLATE) {
		compression = COMPRESSION_DEFLATE;
	} else if ((flags & TIFF_ADOBE_DEFLATE) == TIFF_ADOBE_DEFLATE) {
		compression = COMPRESSION_ADOBE_DEFLATE;
	} else if ((flags & TIFF_NONE) == TIFF_NONE) {
		compression = COMPRESSION_NONE;
	} else if ((bitsperpixel == 1) && ((flags & TIFF_CCITTFAX3) == TIFF_CCITTFAX3)) {
		compression = COMPRESSION_CCITTFAX3;
	} else if ((bitsperpixel == 1) && ((flags & TIFF_CCITTFAX4) == TIFF_CCITTFAX4)) {
		compression = COMPRESSION_CCITTFAX4;
	} else if ((flags & TIFF_LZW) == TIFF_LZW) {
		compression = COMPRESSION_LZW;
	} else if ((flags & TIFF_JPEG) == TIFF_JPEG) {
		if(((bitsperpixel == 8) && (photometric != PHOTOMETRIC_PALETTE)) || (bitsperpixel == 24)) {
			compression = COMPRESSION_JPEG;
			// RowsPerStrip must be multiple of 8 for JPEG
			uint32 rowsperstrip = (uint32) -1;
			rowsperstrip = TIFFDefaultStripSize(tiff, rowsperstrip);
            rowsperstrip = rowsperstrip + (8 - (rowsperstrip % 8));
			// overwrite previous RowsPerStrip
			TIFFSetField(tiff, TIFFTAG_ROWSPERSTRIP, rowsperstrip);
		} else {
			// default to LZW
			compression = COMPRESSION_LZW;
		}
	}
	else {
		// default compression scheme

		switch(bitsperpixel) {
			case 1 :
				compression = COMPRESSION_CCITTFAX4;
				break;

			case 4 :
			case 8 :
			case 16 :
			case 24 :
			case 32 :
				compression = COMPRESSION_LZW;
				break;
			case 48:
			case 64 :
			case 128:
				compression = COMPRESSION_LZW;
				break;

			default :
				compression = COMPRESSION_NONE;
				break;
		}
	}

	TIFFSetField(tiff, TIFFTAG_COMPRESSION, compression);

	if(compression == COMPRESSION_LZW) {
		// This option is only meaningful with LZW compression: a predictor value of 2 
		// causes each scanline of the output image to undergo horizontal differencing 
		// before it is encoded; a value of 1 forces each scanline to be encoded without differencing.

		// Found on LibTIFF mailing list : 
		// LZW without differencing works well for 1-bit images, 4-bit grayscale images, 
		// and many palette-color images. But natural 24-bit color images and some 8-bit 
		// grayscale images do much better with differencing.

		if((bitspersample == 8) || (bitspersample == 16)) {
			if ((bitsperpixel >= 8) && (photometric != PHOTOMETRIC_PALETTE))
				TIFFSetField(tiff, TIFFTAG_PREDICTOR, 2);
			else
				TIFFSetField(tiff, TIFFTAG_PREDICTOR, 1);
		} else {
			TIFFSetField(tiff, TIFFTAG_PREDICTOR, 1);
		}
	}
	else if(compression == COMPRESSION_CCITTFAX3) {
		// try to be compliant with the TIFF Class F specification
		// that documents the TIFF tags specific to FAX applications
		// see http://palimpsest.stanford.edu/bytopic/imaging/std/tiff-f.html
		uint32 group3options = GROUP3OPT_2DENCODING | GROUP3OPT_FILLBITS;	
		TIFFSetField(tiff, TIFFTAG_GROUP3OPTIONS, group3options);	// 2d-encoded, has aligned EOL
		TIFFSetField(tiff, TIFFTAG_FILLORDER, FILLORDER_LSB2MSB);	// lsb-to-msb fillorder
	}
}

// ==========================================================
// TIFF metadata routines
// ==========================================================

/**
	Read the TIFFTAG_RICHTIFFIPTC tag (IPTC/NAA or Adobe Photoshop profile)
*/
static BOOL 
tiff_read_iptc_profile(TIFF *tiff, FIBITMAP *dib) {
	BYTE *profile = NULL;
	uint32 profile_size = 0;

    if(TIFFGetField(tiff,TIFFTAG_RICHTIFFIPTC, &profile_size, &profile) == 1) {
        if (TIFFIsByteSwapped(tiff) != 0)
			TIFFSwabArrayOfLong((uint32 *) profile, (unsigned long)profile_size);

		return read_iptc_profile(dib, profile, 4 * profile_size);
	}

	return FALSE;
}

/**
	Read the TIFFTAG_XMLPACKET tag (XMP profile)
	@param dib Input FIBITMAP
	@param tiff LibTIFF TIFF handle
	@return Returns TRUE if successful, FALSE otherwise
*/
static BOOL  
tiff_read_xmp_profile(TIFF *tiff, FIBITMAP *dib) {
	BYTE *profile = NULL;
	uint32 profile_size = 0;

	if (TIFFGetField(tiff, TIFFTAG_XMLPACKET, &profile_size, &profile) == 1) {
		// create a tag
		FITAG *tag = FreeImage_CreateTag();
		if(!tag) return FALSE;

		FreeImage_SetTagID(tag, TIFFTAG_XMLPACKET);	// 700
		FreeImage_SetTagKey(tag, g_TagLib_XMPFieldName);
		FreeImage_SetTagLength(tag, profile_size);
		FreeImage_SetTagCount(tag, profile_size);
		FreeImage_SetTagType(tag, FIDT_ASCII);
		FreeImage_SetTagValue(tag, profile);

		// store the tag
		FreeImage_SetMetadata(FIMD_XMP, dib, FreeImage_GetTagKey(tag), tag);

		// destroy the tag
		FreeImage_DeleteTag(tag);

		return TRUE;
	}

	return FALSE;
}

/**
	Read the Exif profile embedded in a TIFF
	@param dib Input FIBITMAP
	@param tiff LibTIFF TIFF handle
	@return Returns TRUE if successful, FALSE otherwise
*/
static BOOL 
tiff_read_exif_profile(TIFF *tiff, FIBITMAP *dib) {
    uint32 exif_offset = 0;

	// read EXIF-TIFF tags
	tiff_read_exif_tags(tiff, TagLib::EXIF_MAIN, dib);

	// get the IFD offset
	if(TIFFGetField(tiff, TIFFTAG_EXIFIFD, &exif_offset)) {
		// read EXIF tags
		if(!TIFFReadEXIFDirectory(tiff, exif_offset))
			return FALSE;

		return tiff_read_exif_tags(tiff, TagLib::EXIF_EXIF, dib);
	}

	return FALSE;
}

/**
Read TIFF special profiles
*/
static void 
ReadMetadata(TIFF *tiff, FIBITMAP *dib) {

	// IPTC/NAA
	tiff_read_iptc_profile(tiff, dib);

	// Adobe XMP
	tiff_read_xmp_profile(tiff, dib);

	// GeoTIFF
	tiff_read_geotiff_profile(tiff, dib);

	// Exif-TIFF
	tiff_read_exif_profile(tiff, dib);
}

// ----------------------------------------------------------

/**
	Write the TIFFTAG_RICHTIFFIPTC tag (IPTC/NAA or Adobe Photoshop profile)
*/
static BOOL 
tiff_write_iptc_profile(TIFF *tiff, FIBITMAP *dib) {
	if(FreeImage_GetMetadataCount(FIMD_IPTC, dib)) {
		BYTE *profile = NULL;
		uint32 profile_size = 0;
		// create a binary profile
		if(write_iptc_profile(dib, &profile, &profile_size)) {
			uint32 iptc_size = profile_size;
			iptc_size += (4-(iptc_size & 0x03)); // Round up for long word alignment
			BYTE *iptc_profile = (BYTE*)malloc(iptc_size);
			if(!iptc_profile) {
				free(profile);
				return FALSE;
			}
			memset(iptc_profile, 0, iptc_size);
			memcpy(iptc_profile, profile, profile_size);
			if (TIFFIsByteSwapped(tiff))
				TIFFSwabArrayOfLong((uint32 *) iptc_profile, (unsigned long)iptc_size/4);
			// Tag is type TIFF_LONG so byte length is divided by four
			TIFFSetField(tiff, TIFFTAG_RICHTIFFIPTC, iptc_size/4, iptc_profile);
			// release the profile data
			free(iptc_profile);
			free(profile);

			return TRUE;
		}
	}

	return FALSE;
}

/**
	Write the TIFFTAG_XMLPACKET tag (XMP profile)
	@param dib Input FIBITMAP
	@param tiff LibTIFF TIFF handle
	@return Returns TRUE if successful, FALSE otherwise
*/
static BOOL  
tiff_write_xmp_profile(TIFF *tiff, FIBITMAP *dib) {
	FITAG *tag_xmp = NULL;
	FreeImage_GetMetadata(FIMD_XMP, dib, g_TagLib_XMPFieldName, &tag_xmp);

	if(tag_xmp && (NULL != FreeImage_GetTagValue(tag_xmp))) {
		
		TIFFSetField(tiff, TIFFTAG_XMLPACKET, (uint32)FreeImage_GetTagLength(tag_xmp), (BYTE*)FreeImage_GetTagValue(tag_xmp));

		return TRUE;		
	}

	return FALSE;
}

/**
Write TIFF special profiles
*/
static void 
WriteMetadata(TIFF *tiff, FIBITMAP *dib) {
	// IPTC
	tiff_write_iptc_profile(tiff, dib);

	// Adobe XMP
	tiff_write_xmp_profile(tiff, dib);

	// GeoTIFF tags
	tiff_write_geotiff_profile(tiff, dib);
}

// ==========================================================
// Plugin Implementation
// ==========================================================

static const char * DLL_CALLCONV
Format() {
	return "TIFF";
}

static const char * DLL_CALLCONV
Description() {
	return "Tagged Image File Format";
}

static const char * DLL_CALLCONV
Extension() {
	return "tif,tiff";
}

static const char * DLL_CALLCONV
RegExpr() {
	return "^[MI][MI][\\x01*][\\x01*]";
}

static const char * DLL_CALLCONV
MimeType() {
	return "image/tiff";
}

static BOOL DLL_CALLCONV
Validate(FreeImageIO *io, fi_handle handle) {	
	BYTE tiff_id1[] = { 0x49, 0x49, 0x2A, 0x00 };
	BYTE tiff_id2[] = { 0x4D, 0x4D, 0x00, 0x2A };
	BYTE signature[4] = { 0, 0, 0, 0 };

	io->read_proc(signature, 1, 4, handle);

	if(memcmp(tiff_id1, signature, 4) == 0)
		return TRUE;

	if(memcmp(tiff_id2, signature, 4) == 0)
		return TRUE;

	return FALSE;
}

static BOOL DLL_CALLCONV
SupportsExportDepth(int depth) {
	return (
			(depth == 1)  ||
			(depth == 4)  ||
			(depth == 8)  ||
			(depth == 24) ||
			(depth == 32)
		);
}

static BOOL DLL_CALLCONV 
SupportsExportType(FREE_IMAGE_TYPE type) {
	return (
		(type == FIT_BITMAP)  ||
		(type == FIT_UINT16)  ||
		(type == FIT_INT16)   ||
		(type == FIT_UINT32)  ||
		(type == FIT_INT32)   ||
		(type == FIT_FLOAT)   ||
		(type == FIT_DOUBLE)  ||
		(type == FIT_COMPLEX) || 
		(type == FIT_RGB16)   || 
		(type == FIT_RGBA16)  || 
		(type == FIT_RGBF)
	);
}

static BOOL DLL_CALLCONV
SupportsICCProfiles() {
	return TRUE;
}

// ----------------------------------------------------------

static void * DLL_CALLCONV
Open(FreeImageIO *io, fi_handle handle, BOOL read) {
	// wrapper for TIFF I/O
	fi_TIFFIO *fio = (fi_TIFFIO*)malloc(sizeof(fi_TIFFIO));
	if(!fio) return NULL;
	fio->io = io;
	fio->handle = handle;

	if (read) {
		fio->tif = TIFFFdOpen((thandle_t)fio, "", "r");
	} else {
		fio->tif = TIFFFdOpen((thandle_t)fio, "", "w");
	}
	if(fio->tif == NULL) {
		free(fio);
		FreeImage_OutputMessageProc(s_format_id, "Error while opening TIFF: data is invalid");
		return NULL;
	}
	return fio;
}

static void DLL_CALLCONV
Close(FreeImageIO *io, fi_handle handle, void *data) {
	if(data) {
		fi_TIFFIO *fio = (fi_TIFFIO*)data;
		TIFFClose(fio->tif);
		free(fio);
	}
}

// ----------------------------------------------------------

static int DLL_CALLCONV
PageCount(FreeImageIO *io, fi_handle handle, void *data) {
	if(data) {
		fi_TIFFIO *fio = (fi_TIFFIO*)data;
		TIFF *tif = (TIFF *)fio->tif;
		int nr_ifd = 0;

		do {
			nr_ifd++;
		} while (TIFFReadDirectory(tif));
				
		return nr_ifd;
	}

	return 0;
}

// ----------------------------------------------------------

/**
check for uncommon bitspersample values (e.g. 10, 12, ...)
@param photometric TIFFTAG_PHOTOMETRIC tiff tag
@param bitspersample TIFFTAG_BITSPERSAMPLE tiff tag
@return Returns FALSE if a uncommon bit-depth is encountered, returns TRUE otherwise
*/
static BOOL IsValidBitsPerSample(uint16 photometric, uint16 bitspersample) {
	switch(bitspersample) {
		case 1:
		case 4:
			if((photometric == PHOTOMETRIC_MINISWHITE) || (photometric == PHOTOMETRIC_MINISBLACK) || (photometric == PHOTOMETRIC_PALETTE)) { 
				return TRUE;
			} else {
				return FALSE;
			}
			break;
		case 8:
			return TRUE;
		case 16:
			if(photometric != PHOTOMETRIC_PALETTE) { 
				return TRUE;
			} else {
				return FALSE;
			}
			break;
		case 32:
			return TRUE;
		case 64:
		case 128:
			if(photometric == PHOTOMETRIC_MINISBLACK) { 
				return TRUE;
			} else {
				return FALSE;
			}
			break;
		default:
			return FALSE;
	}
}

static TIFFLoadMethod  
FindLoadMethod(TIFF *tif, FREE_IMAGE_TYPE image_type, int flags) {
	uint16 bitspersample;
	uint16 samplesperpixel;
	uint16 photometric;
	uint16 planar_config;

	TIFFLoadMethod loadMethod = LoadAsGenericStrip;

	TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &photometric);
	TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
	TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bitspersample);
	TIFFGetFieldDefaulted(tif, TIFFTAG_PLANARCONFIG, &planar_config);

	BOOL bIsTiled = (TIFFIsTiled(tif) == 0) ? FALSE:TRUE;

	switch(photometric) {
		// convert to 24 or 32 bits RGB if the image is full color
		case PHOTOMETRIC_RGB:
			if((image_type == FIT_RGB16) || (image_type == FIT_RGBA16)) {
				// load 48-bit RGB and 64-bit RGBA without conversion 
				loadMethod = LoadAsGenericStrip;
			} else if(bitspersample >= 8) {
				loadMethod = LoadAsRBGA;
			} 
			break;
		case PHOTOMETRIC_YCBCR:
		case PHOTOMETRIC_CIELAB:
		case PHOTOMETRIC_ICCLAB:
		case PHOTOMETRIC_ITULAB:
			loadMethod = LoadAsRBGA;
			break;
		case PHOTOMETRIC_LOGLUV:
			loadMethod = LoadAsRGBF;
			break;
		case PHOTOMETRIC_SEPARATED:
			if(planar_config == PLANARCONFIG_CONTIG) {
				// if image is PHOTOMETRIC_SEPARATED _and_ comes with an ICC profile, 
				// then the image should preserve its original (CMYK) colour model and 
				// should be read as CMYK (to keep the match of pixel and profile and 
				// to avoid multiple conversions. Conversion can be done by changing 
				// the profile from it's original CMYK to an RGB profile with an 
				// apropriate color management system. Works with non-tiled TIFFs.
				if((((flags & TIFF_CMYK) == TIFF_CMYK) || samplesperpixel > 4) && !bIsTiled) {
					loadMethod = LoadAsCMYK;
				} else {
					loadMethod = LoadAsRBGA;
				}
			} else if(planar_config == PLANARCONFIG_SEPARATE) {
				// TIFFReadRGBAImage doesn't support this case ...
				loadMethod = LoadAsCMYK;
			}
			break;
		case PHOTOMETRIC_MINISWHITE:
		case PHOTOMETRIC_MINISBLACK:
		case PHOTOMETRIC_PALETTE:
			// When samplesperpixel = 2 and bitspersample = 8, set the image as a
			// 8-bit indexed image + 8-bit alpha layer image
			// and convert to a 8-bit image with a transparency table
			if((samplesperpixel == 2) && (bitspersample == 8)) {
				loadMethod = LoadAs8BitTrns;
			} else {
				loadMethod = LoadAsGenericStrip;
			}
			break;
		default:
			loadMethod = LoadAsGenericStrip;
			break;
	}

	if((loadMethod == LoadAsGenericStrip) && bIsTiled) {
		loadMethod = LoadAsTiled;
	}

	return loadMethod;
}


static FIBITMAP * DLL_CALLCONV
Load(FreeImageIO *io, fi_handle handle, int page, int flags, void *data) {
	if ((handle != NULL) && (data != NULL)) {
		TIFF   *tif = NULL;
		uint32 height = 0; 
		uint32 width = 0; 
		uint16 bitspersample = 1;
		uint16 samplesperpixel = 1;
		uint32 rowsperstrip;  
		uint16 photometric = PHOTOMETRIC_MINISWHITE;
		uint16 compression = COMPRESSION_NONE;
		uint16 planar_config;

		FIBITMAP *dib = NULL;
		uint32 iccSize = 0;		// ICC profile length
		void *iccBuf = NULL;	// ICC profile data		

		try {	
			fi_TIFFIO *fio = (fi_TIFFIO*)data;
			tif = fio->tif;

			if (page != -1) {
				if (!tif || !TIFFSetDirectory(tif, (tdir_t)page)) {
					throw "Error encountered while opening TIFF file";			
				}
			}

			// first, get the photometric, the compression and basic metadata
			// ---------------------------------------------------------------------------------

			TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &photometric);
			TIFFGetField(tif, TIFFTAG_COMPRESSION, &compression);

			// check for HDR formats
			// ---------------------------------------------------------------------------------

			if(photometric == PHOTOMETRIC_LOGLUV) {
				// check the compression
				if(compression != COMPRESSION_SGILOG && compression != COMPRESSION_SGILOG24) {
					throw "Only support SGILOG compressed LogLuv data";
				}
				// set decoder to output in IEEE 32-bit float XYZ values
				TIFFSetField(tif, TIFFTAG_SGILOGDATAFMT, SGILOGDATAFMT_FLOAT);
			}

			// ---------------------------------------------------------------------------------

			TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
			TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
			TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
			TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bitspersample);
			TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &rowsperstrip);   			
			TIFFGetField(tif, TIFFTAG_ICCPROFILE, &iccSize, &iccBuf);
			TIFFGetFieldDefaulted(tif, TIFFTAG_PLANARCONFIG, &planar_config);

			// check for unsupported formats
			// ---------------------------------------------------------------------------------

			if((photometric == PHOTOMETRIC_SEPARATED) && (bitspersample == 16))
				throw "Unable to handle 16-bit CMYK TIFF";

			if(IsValidBitsPerSample(photometric, bitspersample) == FALSE) {
				FreeImage_OutputMessageProc(s_format_id, 
					"Unable to handle this format: bitspersample = %d, samplesperpixel = %d, photometric = %d", 
					(int)bitspersample, (int)samplesperpixel, (int)photometric);
				throw (char*)NULL;
			}

			// ---------------------------------------------------------------------------------

			// get image data type

			FREE_IMAGE_TYPE image_type = ReadImageType(tif, bitspersample, samplesperpixel);

			// get the most appropriate loading method

			TIFFLoadMethod loadMethod = FindLoadMethod(tif, image_type, flags);

			// ---------------------------------------------------------------------------------

			if(loadMethod == LoadAsRBGA) {
				// ---------------------------------------------------------------------------------
				// RGB[A] loading using the TIFFReadRGBAImage() API
				// ---------------------------------------------------------------------------------

				BOOL has_alpha = FALSE;   

				// Read the whole image into one big RGBA buffer and then 
				// convert it to a DIB. This is using the traditional
				// TIFFReadRGBAImage() API that we trust.

				uint32 *raster = (uint32*)_TIFFmalloc(width * height * sizeof(uint32));
				if (raster == NULL) {
					throw FI_MSG_ERROR_MEMORY;
				}

				// read the image in one chunk into an RGBA array

				if (!TIFFReadRGBAImage(tif, width, height, raster, 1)) {
					_TIFFfree(raster);
					throw FI_MSG_ERROR_UNSUPPORTED_FORMAT;
				}

				// TIFFReadRGBAImage always deliveres 3 or 4 samples per pixel images
				// (RGB or RGBA, see below). Cut-off possibly present channels (additional 
				// alpha channels) from e.g. Photoshop. Any CMYK(A..) is now treated as RGB,
				// any additional alpha channel on RGB(AA..) is lost on conversion to RGB(A)

				if(samplesperpixel > 4) {
					FreeImage_OutputMessageProc(s_format_id, "Warning: %d additional alpha channel(s) ignored", samplesperpixel-4);
					samplesperpixel = 4;
				}

				// create a new DIB (take care of different samples-per-pixel in case 
				// of converted CMYK image (RGB conversion is on sample per pixel less)

				if (photometric == PHOTOMETRIC_SEPARATED && samplesperpixel == 4) {
					samplesperpixel = 3;
				}

				dib = CreateImageType(image_type, width, height, bitspersample, samplesperpixel);
				if (dib == NULL) {
					// free the raster pointer and output an error if allocation failed

					_TIFFfree(raster);

					throw FI_MSG_ERROR_DIB_MEMORY;
				}
				
				// fill in the resolution (english or universal)

				ReadResolution(tif, dib);

				// read the raster lines and save them in the DIB
				// with RGB mode, we have to change the order of the 3 samples RGB
				// We use macros for extracting components from the packed ABGR 
				// form returned by TIFFReadRGBAImage.

				uint32 *row = &raster[0];

				if (samplesperpixel == 4) {
					// 32-bit RGBA
					for (uint32 y = 0; y < height; y++) {
						BYTE *bits = FreeImage_GetScanLine(dib, y);
						for (uint32 x = 0; x < width; x++) {
							bits[FI_RGBA_BLUE]	= (BYTE)TIFFGetB(row[x]);
							bits[FI_RGBA_GREEN] = (BYTE)TIFFGetG(row[x]);
							bits[FI_RGBA_RED]	= (BYTE)TIFFGetR(row[x]);
							bits[FI_RGBA_ALPHA] = (BYTE)TIFFGetA(row[x]);

							if (bits[FI_RGBA_ALPHA] != 0)
								has_alpha = TRUE;								

							bits += 4;
						}
						row += width;
					}
				} else {
					// 24-bit RGB
					for (uint32 y = 0; y < height; y++) {
						BYTE *bits = FreeImage_GetScanLine(dib, y);
						for (uint32 x = 0; x < width; x++) {
							bits[FI_RGBA_BLUE]	= (BYTE)TIFFGetB(row[x]);
							bits[FI_RGBA_GREEN] = (BYTE)TIFFGetG(row[x]);
							bits[FI_RGBA_RED]	= (BYTE)TIFFGetR(row[x]);

							bits += 3;
						}
						row += width;
					}
				}

				_TIFFfree(raster);

				FreeImage_SetTransparent(dib, has_alpha);

			} else if(loadMethod == LoadAs8BitTrns) {
				// ---------------------------------------------------------------------------------
				// 8-bit + 8-bit alpha layer loading
				// ---------------------------------------------------------------------------------

				// create a new 8-bit DIB
				dib = CreateImageType(image_type, width, height, bitspersample, samplesperpixel);
				if (dib == NULL) {
					throw FI_MSG_ERROR_MEMORY;
				}

				// fill in the resolution (english or universal)

				ReadResolution(tif, dib);

				// set up the colormap based on photometric	

				ReadPalette(tif, photometric, bitspersample, dib);

				// calculate the line + pitch (separate for scr & dest)

				tsize_t src_line = TIFFScanlineSize(tif);
				// here, the pitch is 2x less than the original as we only keep the first layer				
				int dst_pitch = FreeImage_GetPitch(dib);

				// transparency table for 8-bit + 8-bit alpha images

				BYTE trns[256]; 
				// clear the transparency table
				memset(trns, 0xFF, 256 * sizeof(BYTE));


				// In the tiff file the lines are save from up to down 
				// In a DIB the lines must be saved from down to up

				BYTE *bits = FreeImage_GetScanLine(dib, height - 1);

				// read the tiff lines and save them in the DIB

				if(planar_config == PLANARCONFIG_CONTIG) {

					BYTE *buf = (BYTE*)malloc(TIFFStripSize(tif) * sizeof(BYTE));
					if(buf == NULL) throw FI_MSG_ERROR_MEMORY;


					for (uint32 y = 0; y < height; y += rowsperstrip) {
						int32 nrow = (y + rowsperstrip > height ? height - y : rowsperstrip);

						if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, 0), buf, nrow * src_line) == -1) {
							free(buf);
							throw FI_MSG_ERROR_PARSING;
						}
						for (int l = 0; l < nrow; l++) {
							BYTE *p = bits;
							BYTE *b = buf + l * src_line;

							for(uint32 x = 0; x < (uint32)(src_line / samplesperpixel); x++) {
								// copy the 8-bit layer
								*p = b[0];
								// convert the 8-bit alpha layer to a trns table
								trns[ b[0] ] = b[1];

								p++;
								b += samplesperpixel;
							}
							bits -= dst_pitch;
						}
					}

					free(buf);
				}
				else if(planar_config == PLANARCONFIG_SEPARATE) {
					tsize_t stripsize = TIFFStripSize(tif) * sizeof(BYTE);
					BYTE *buf = (BYTE*)malloc(2 * stripsize);
					BYTE *grey = buf;
					BYTE *alpha = buf + stripsize;

					for (uint32 y = 0; y < height; y += rowsperstrip) {
						int32 nrow = (y + rowsperstrip > height ? height - y : rowsperstrip);

						if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, 0), grey, nrow * src_line) == -1) {
							free(buf);
							throw FI_MSG_ERROR_PARSING;
						} 
						if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, 1), alpha, nrow * src_line) == -1) {
							free(buf);
							throw FI_MSG_ERROR_PARSING;
						} 

						for (int l = 0; l < nrow; l++) {
							BYTE *p = bits;
							BYTE *g = grey + l * src_line;
							BYTE *a = alpha + l * src_line;

							for(uint32 x = 0; x < (uint32)(src_line); x++) {
								// copy the 8-bit layer
								*p = g[0];
								// convert the 8-bit alpha layer to a trns table
								trns[ g[0] ] = a[0];

								p++;
								g++;
								a++;
							}
							bits -= dst_pitch;
						}
					}

					free(buf);

				}
				
				FreeImage_SetTransparencyTable(dib, &trns[0], 256);
				FreeImage_SetTransparent(dib, TRUE);

			} else if(loadMethod == LoadAsCMYK) {
				// ---------------------------------------------------------------------------------
				// CMYK loading
				// ---------------------------------------------------------------------------------

				BOOL has_alpha = FALSE;    

				// At this place, samplesperpixel could be > 4, esp. when a CMYK(A) format
				// is recognized. Where all other formats are handled straight-forward, this
				// format has to be handled special 

				BOOL isCMYKA = (photometric == PHOTOMETRIC_SEPARATED) && (samplesperpixel > 4);
				uint16 spp = MIN(samplesperpixel, (uint16)4);
				if((planar_config == PLANARCONFIG_SEPARATE) && !isCMYKA && ((flags & TIFF_CMYK) != TIFF_CMYK)) {
					// CMYK picture => convert to RGB 24-bit
					spp = 3;
				}

				// create a new DIB
				dib = CreateImageType(image_type, width, height, bitspersample, spp);
				if (dib == NULL) {
					throw FI_MSG_ERROR_MEMORY;
				}

				// fill in the resolution (english or universal)

				ReadResolution(tif, dib);

				// calculate the line + pitch (separate for scr & dest)

				tsize_t src_line = TIFFScanlineSize(tif);
				int dst_pitch = FreeImage_GetPitch(dib);

				// In the tiff file the lines are save from up to down 
				// In a DIB the lines must be saved from down to up

				BYTE *bits = FreeImage_GetScanLine(dib, height - 1);

				// read the tiff lines and save them in the DIB

				if(planar_config == PLANARCONFIG_CONTIG) {
					BYTE *buf = (BYTE*)malloc(TIFFStripSize(tif) * sizeof(BYTE));
					if(buf == NULL) throw FI_MSG_ERROR_MEMORY;

					for (uint32 y = 0; y < height; y += rowsperstrip) {
						int32 nrow = (y + rowsperstrip > height ? height - y : rowsperstrip);

						if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, 0), buf, nrow * src_line) == -1) {
							free(buf);
							throw FI_MSG_ERROR_PARSING;
						} 
						if(isCMYKA) {
							// CMYKA picture
							for (int l = 0; l < nrow; l++) {
								// Here we know: samples-per-pixel was >= 5 on CMYKA picture
								// This should be converted to RGBA or CMYK, depending on 
								// TIFF_CMYK is given. The resulting image always has 32bpp.

								BYTE *p = bits;
								BYTE *b = buf + l * src_line;

								for (uint32 x = 0; x < (uint32)(src_line / samplesperpixel); x++) {
									if ((flags & TIFF_CMYK) == TIFF_CMYK) {
										memcpy(p, b, spp);
									} else {
										BYTE k = 255 - b[3];
										p[FI_RGBA_RED]	 = (k*(255-b[0]))/255;
										p[FI_RGBA_GREEN] = (k*(255-b[1]))/255;
										p[FI_RGBA_BLUE]	 = (k*(255-b[2]))/255;
										if ((p[FI_RGBA_ALPHA] = b[4]) != 0)
											has_alpha = TRUE;								
									}
									b += samplesperpixel;
									p += spp;
								}
								bits -= dst_pitch;
							}								
						}
						else  {
							// CMYK picture: just copy
							for (int l = 0; l < nrow; l++) {								
								BYTE *b = buf + l * src_line;
								memcpy(bits, b, src_line);
								bits -= dst_pitch;
							}
						}						
					}

					free(buf);
				}
				else if(planar_config == PLANARCONFIG_SEPARATE) {
					uint16 sample;
					BYTE *channel;
					tsize_t stripsize = TIFFStripSize(tif) * sizeof(BYTE);
					BYTE *buf = (BYTE*)malloc(samplesperpixel * stripsize);
					if(buf == NULL) throw FI_MSG_ERROR_MEMORY;

					for (uint32 y = 0; y < height; y += rowsperstrip) {
						int32 nrow = (y + rowsperstrip > height ? height - y : rowsperstrip);

						// read all separated strips
						channel = buf;
						for(sample = 0; sample < samplesperpixel; sample++) {
							if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, sample), channel, nrow * src_line) == -1) {
								free(buf);
								throw FI_MSG_ERROR_PARSING;
							} 
							channel += stripsize;
						}
						if ((flags & TIFF_CMYK) == TIFF_CMYK) {
							// CMYK or CMYKA picture: load as 32-bit CMYK, skipping possibly present alpha channel(s)
							for (int l = 0; l < nrow; l++) {
								channel = buf;
								for(sample = 0; sample < spp; sample++) {
									BYTE *src_bits = channel + l * src_line;
									BYTE *dst_bits = bits;
									for (uint32 x = 0; x < (uint32)(src_line); x++) {
										dst_bits[sample] = src_bits[x];
										dst_bits += spp;
									}
									channel += stripsize;
								}
								bits -= dst_pitch;
							}
						}
						else if(isCMYKA) {
							// CMYKA picture: convert to RGBA, skipping possibly some alpha channel(s)
							for (int l = 0; l < nrow; l++) {
								BYTE *c_channel = buf + l * src_line;
								BYTE *m_channel = buf + stripsize + l * src_line;
								BYTE *y_channel = buf + 2*stripsize + l * src_line;
								BYTE *k_channel = buf + 3*stripsize + l * src_line;
								BYTE *a_channel = buf + 4*stripsize + l * src_line;
								BYTE *dst_bits = bits;
								for (uint32 x = 0; x < (uint32)(src_line); x++) {
									BYTE k = 255 - k_channel[x];
									dst_bits[FI_RGBA_RED]	= (k*(255-c_channel[x]))/255;
									dst_bits[FI_RGBA_GREEN] = (k*(255-m_channel[x]))/255;
									dst_bits[FI_RGBA_BLUE]	= (k*(255-y_channel[x]))/255;
									if ((dst_bits[FI_RGBA_ALPHA] = a_channel[x]) != 0)
										has_alpha = TRUE;
									dst_bits += spp;
								}
								bits -= dst_pitch;
							}
						}
						else  {							
							// CMYK picture: convert to RGB
							for (int l = 0; l < nrow; l++) {								
								BYTE *c_channel = buf + l * src_line;
								BYTE *m_channel = buf + stripsize + l * src_line;
								BYTE *y_channel = buf + 2*stripsize + l * src_line;
								BYTE *k_channel = buf + 3*stripsize + l * src_line;
								BYTE *dst_bits = bits;
								for (uint32 x = 0; x < (uint32)(src_line); x++) {
									BYTE k = 255 - k_channel[x];
									dst_bits[FI_RGBA_RED]	= (k*(255-c_channel[x]))/255;
									dst_bits[FI_RGBA_GREEN] = (k*(255-m_channel[x]))/255;
									dst_bits[FI_RGBA_BLUE]	= (k*(255-y_channel[x]))/255;
									dst_bits += spp;
								}
								bits -= dst_pitch;
							}
						}						
					}

					free(buf);
				}

				FreeImage_SetTransparent(dib, has_alpha);

			} else if(loadMethod == LoadAsGenericStrip) {
				// ---------------------------------------------------------------------------------
				// Generic loading
				// ---------------------------------------------------------------------------------

				// create a new DIB
				dib = CreateImageType(image_type, width, height, bitspersample, samplesperpixel);
				if (dib == NULL) {
					throw FI_MSG_ERROR_MEMORY;
				}

				// fill in the resolution (english or universal)

				ReadResolution(tif, dib);

				// set up the colormap based on photometric	

				ReadPalette(tif, photometric, bitspersample, dib);

				// calculate the line + pitch (separate for scr & dest)

				tsize_t src_line = TIFFScanlineSize(tif);
				int dst_pitch = FreeImage_GetPitch(dib);

				// In the tiff file the lines are save from up to down 
				// In a DIB the lines must be saved from down to up

				BYTE *bits = FreeImage_GetScanLine(dib, height - 1);

				// read the tiff lines and save them in the DIB

				if(planar_config == PLANARCONFIG_CONTIG) {
					BOOL bThrowMessage = FALSE;
					BYTE *buf = (BYTE*)malloc(TIFFStripSize(tif) * sizeof(BYTE));
					if(buf == NULL) throw FI_MSG_ERROR_MEMORY;

					for (uint32 y = 0; y < height; y += rowsperstrip) {
						int32 nrow = (y + rowsperstrip > height ? height - y : rowsperstrip);

						if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, 0), buf, nrow * src_line) == -1) {
							// ignore errors as they can be frequent and not really valid errors, especially with fax images
							bThrowMessage = TRUE;							
							/*
							free(buf);
							throw FI_MSG_ERROR_PARSING;
							*/
						} 
						// color/greyscale picture (1-, 4-, 8-bit) or special type (int, long, double, ...)
						// ... just copy 
						for (int l = 0; l < nrow; l++) {							
							memcpy(bits, buf + l * src_line, src_line);
							bits -= dst_pitch;
						}
					}

					free(buf);

					if(bThrowMessage) {
						FreeImage_OutputMessageProc(s_format_id, "Warning: parsing error. Image may be incomplete or contain invalid data !");
					}
				}
				else if(planar_config == PLANARCONFIG_SEPARATE) {
					BOOL bThrowMessage = FALSE;
					uint16 sample;
					BYTE *channel;
					tsize_t stripsize = TIFFStripSize(tif) * sizeof(BYTE);
					BYTE *buf = (BYTE*)malloc(samplesperpixel * stripsize);
					if(buf == NULL) throw FI_MSG_ERROR_MEMORY;
					
					int bytespersample = bitspersample / 8;
					int bytesperpixel = bytespersample * samplesperpixel;

					for (uint32 y = 0; y < height; y += rowsperstrip) {
						int32 nrow = (y + rowsperstrip > height ? height - y : rowsperstrip);

						// read all separated strips
						channel = buf;
						for(sample = 0; sample < samplesperpixel; sample++) {
							if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, sample), channel, nrow * src_line) == -1) {
								// ignore errors as they can be frequent and not really valid errors, especially with fax images
								bThrowMessage = TRUE;								
								/*
								free(buf);
								throw FI_MSG_ERROR_PARSING;
								*/
							} 
							channel += stripsize;
						}

						// reconstruct the picture						
						for (int l = 0; l < nrow; l++) {							
							channel = buf;
							for(sample = 0; sample < samplesperpixel; sample++) {
								BYTE *src_bits = channel + l * src_line;
								BYTE *dst_bits = bits + sample * bytespersample;
								for (uint32 x = 0; x < (uint32)(src_line / bytespersample); x++) {
									memcpy(dst_bits, src_bits, bytespersample);
									src_bits += bytespersample;
									dst_bits += bytesperpixel;
								}
								channel += stripsize;
							}
							bits -= dst_pitch;
						}
					}

					free(buf);

					if(bThrowMessage) {
						FreeImage_OutputMessageProc(s_format_id, "Warning: parsing error. Image may be incomplete or contain invalid data !");
					}
				}

			} else if(loadMethod == LoadAsTiled) {
				// ---------------------------------------------------------------------------------
				// Tiled image loading
				// ---------------------------------------------------------------------------------

				uint32 tileWidth, tileHeight;
				uint32 src_line = 0;

				// create a new DIB
				dib = CreateImageType(image_type, width, height, bitspersample, samplesperpixel);
				if (dib == NULL) {
					throw FI_MSG_ERROR_MEMORY;
				}

				// fill in the resolution (english or universal)

				ReadResolution(tif, dib);

				// set up the colormap based on photometric	

				ReadPalette(tif, photometric, bitspersample, dib);

				// get the tile geometry
				if(!TIFFGetField(tif, TIFFTAG_TILEWIDTH, &tileWidth) || !TIFFGetField(tif, TIFFTAG_TILELENGTH, &tileHeight)) {
					throw "Invalid tiled TIFF image";
				}

				// get the maximum number of bytes required to contain a tile
				tsize_t tileSize = TIFFTileSize(tif);

				// allocate tile buffer
				BYTE *tileBuffer = (BYTE*)malloc(tileSize * sizeof(BYTE));
				if(tileBuffer == NULL) throw FI_MSG_ERROR_MEMORY;

				// calculate src line and dst pitch
				int dst_pitch = FreeImage_GetPitch(dib);
				int tileRowSize = TIFFTileRowSize(tif);
				int imageRowSize = TIFFScanlineSize(tif);


				// In the tiff file the lines are save from up to down 
				// In a DIB the lines must be saved from down to up

				BYTE *bits = FreeImage_GetScanLine(dib, height - 1);

				// read the tiff lines and save them in the DIB

				if(planar_config == PLANARCONFIG_CONTIG) {
					uint32 x, y, rowSize;
					for (y = 0; y < height; y += tileHeight) {						
						int32 nrows = (y + tileHeight > height ? height - y : tileHeight);					

						for (x = 0, rowSize = 0; x < width; x += tileWidth, rowSize += tileRowSize) {
							memset(tileBuffer, 0, tileSize);

							// read one tile
							if (TIFFReadTile(tif, tileBuffer, x, y, 0, 0) < 0) {
								free(tileBuffer);
								throw "Corrupted tiled TIFF file";
							}
							// convert to strip
							if(x + tileWidth > width) {
								src_line = imageRowSize - rowSize;
							} else {
								src_line = tileRowSize;
							}
							BYTE *src_bits = tileBuffer;
							BYTE *dst_bits = bits + rowSize;
							for(int k = 0; k < nrows; k++) {
								memcpy(dst_bits, src_bits, src_line);
								src_bits += tileRowSize;
								dst_bits -= dst_pitch;
							}
						}

						bits -= nrows * dst_pitch;
					}

				}
				else if(planar_config == PLANARCONFIG_SEPARATE) {
					free(tileBuffer);
					throw "Separated tiled TIFF images are not supported"; 
				}

				free(tileBuffer);

			} else if(loadMethod == LoadAsRGBF) {
				// ---------------------------------------------------------------------------------
				// RGBF loading
				// ---------------------------------------------------------------------------------

				double	stonits;	// input conversion to nits
				if (!TIFFGetField(tif, TIFFTAG_STONITS, &stonits)) {
					stonits = 1;
				}
				
				// create a new DIB
				dib = CreateImageType(image_type, width, height, bitspersample, samplesperpixel);
				if (dib == NULL) {
					throw FI_MSG_ERROR_MEMORY;
				}

				// fill in the resolution (english or universal)

				ReadResolution(tif, dib);

				// calculate the line + pitch (separate for scr & dest)

				tsize_t src_line = TIFFScanlineSize(tif);
				int dst_pitch = FreeImage_GetPitch(dib);

				// In the tiff file the lines are save from up to down 
				// In a DIB the lines must be saved from down to up

				BYTE *bits = FreeImage_GetScanLine(dib, height - 1);

				// read the tiff lines and save them in the DIB

				if(planar_config == PLANARCONFIG_CONTIG) {
					BYTE *buf = (BYTE*)malloc(TIFFStripSize(tif) * sizeof(BYTE));
					if(buf == NULL) throw FI_MSG_ERROR_MEMORY;

					for (uint32 y = 0; y < height; y += rowsperstrip) {
						int32 nrow = (y + rowsperstrip > height ? height - y : rowsperstrip);

						if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, 0), buf, nrow * src_line) == -1) {
							free(buf);
							throw FI_MSG_ERROR_PARSING;
						} 
						// convert from XYZ to RGB
						for (int l = 0; l < nrow; l++) {						
							tiff_ConvertLineXYZToRGB(bits, buf + l * src_line, stonits, width);
							bits -= dst_pitch;
						}
					}

					free(buf);
				}
				else if(planar_config == PLANARCONFIG_SEPARATE) {
					// this cannot happend according to the LogLuv specification
					throw "Unable to handle PLANARCONFIG_SEPARATE LogLuv images";
				}

			} else {
				// ---------------------------------------------------------------------------------
				// Unknown or unsupported format
				// ---------------------------------------------------------------------------------

				throw FI_MSG_ERROR_UNSUPPORTED_FORMAT;
			}

			// copy ICC profile data (must be done after FreeImage_Allocate)

			FreeImage_CreateICCProfile(dib, iccBuf, iccSize);		
			if (photometric == PHOTOMETRIC_SEPARATED && ((flags & TIFF_CMYK) == TIFF_CMYK)) {
				FreeImage_GetICCProfile(dib)->flags |= FIICC_COLOR_IS_CMYK;
			}			

			// copy TIFF metadata (must be done after FreeImage_Allocate)

			ReadMetadata(tif, dib);

			return (FIBITMAP *)dib;

		} catch (const char *message) {			
			if(dib)	FreeImage_Unload(dib);
			if(message) FreeImage_OutputMessageProc(s_format_id, message);
			return NULL;
		}
	}

	return NULL;	   
}

static BOOL DLL_CALLCONV
Save(FreeImageIO *io, FIBITMAP *dib, fi_handle handle, int page, int flags, void *data) {
	if ((dib != NULL) && (handle != NULL) && (data != NULL)) {
		fi_TIFFIO *fio = (fi_TIFFIO*)data;
		TIFF *out = fio->tif;

		int32 height;
		int32 width;
		uint32 rowsperstrip = (uint32) -1;
		uint16 bitsperpixel;
		uint16 bitspersample;
		uint16 samplesperpixel;
		uint16 photometric;
		uint32 pitch;
		int32 x, y;

		FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);

		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		bitsperpixel = (uint16)FreeImage_GetBPP(dib);

		FIICCPROFILE *iccProfile = FreeImage_GetICCProfile(dib);

		if(image_type == FIT_BITMAP) {
			// standard image: 1-, 4-, 8-, 16-, 24-, 32-bit

			samplesperpixel = ((bitsperpixel == 24) ? 3 : ((bitsperpixel == 32) ? 4 : 1));
			bitspersample = bitsperpixel / samplesperpixel;
			photometric	= GetPhotometric(dib);

			if((bitsperpixel == 8) && FreeImage_IsTransparent(dib)) {
				// 8-bit transparent picture : convert later to 8-bit + 8-bit alpha
				samplesperpixel = 2;
				bitspersample = 8;
			}
			else if(bitsperpixel == 32) {
				// 32-bit images : check for CMYK or alpha transparency

				if((((iccProfile->flags & FIICC_COLOR_IS_CMYK) == FIICC_COLOR_IS_CMYK) || ((flags & TIFF_CMYK) == TIFF_CMYK))) {
					// CMYK support
					photometric = PHOTOMETRIC_SEPARATED;
					TIFFSetField(out, TIFFTAG_INKSET, INKSET_CMYK);
					TIFFSetField(out, TIFFTAG_NUMBEROFINKS, 4);
				}
				else if(photometric == PHOTOMETRIC_RGB) {
					// transparency mask support
					uint16 sampleinfo[1]; 
					// unassociated alpha data is transparency information
					sampleinfo[0] = EXTRASAMPLE_UNASSALPHA;
					TIFFSetField(out, TIFFTAG_EXTRASAMPLES, 1, sampleinfo);
				}
			}
		} else if(image_type == FIT_RGB16) {
			// 48-bit RGB

			samplesperpixel = 3;
			bitspersample = bitsperpixel / samplesperpixel;
			photometric	= PHOTOMETRIC_RGB;
		} else if(image_type == FIT_RGBA16) {
			// 64-bit RGBA

			samplesperpixel = 4;
			bitspersample = bitsperpixel / samplesperpixel;
			photometric	= PHOTOMETRIC_RGB;
			// transparency mask support
			uint16 sampleinfo[1]; 
			// unassociated alpha data is transparency information
			sampleinfo[0] = EXTRASAMPLE_UNASSALPHA;
			TIFFSetField(out, TIFFTAG_EXTRASAMPLES, 1, sampleinfo);
		} else if(image_type == FIT_RGBF) {
			// 96-bit RGBF => store with a LogLuv encoding

			samplesperpixel = 3;
			bitspersample = bitsperpixel / samplesperpixel;
			photometric	= PHOTOMETRIC_LOGLUV;
			// the library converts to and from floating-point XYZ CIE values
			TIFFSetField(out, TIFFTAG_SGILOGDATAFMT, SGILOGDATAFMT_FLOAT);
			// TIFFSetField(out, TIFFTAG_STONITS, 1.0);   // assume unknown 
		} else {
			// special image type (int, long, double, ...)

			samplesperpixel = 1;
			bitspersample = bitsperpixel;
			photometric	= PHOTOMETRIC_MINISBLACK;
		}

		// set image data type

		WriteImageType(out, image_type);
		
		// write possible ICC profile

		if (iccProfile->size && iccProfile->data) {
			TIFFSetField(out, TIFFTAG_ICCPROFILE, iccProfile->size, iccProfile->data);
		}

		// handle standard width/height/bpp stuff

		TIFFSetField(out, TIFFTAG_IMAGEWIDTH, width);
		TIFFSetField(out, TIFFTAG_IMAGELENGTH, height);
		TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, samplesperpixel);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, bitspersample);
		TIFFSetField(out, TIFFTAG_PHOTOMETRIC, photometric);
		TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);	// single image plane 
		TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
		TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, rowsperstrip));

		// handle metrics

		WriteResolution(out, dib);

		// multi-paging

		if (page >= 0) {
			char page_number[20];
			sprintf(page_number, "Page %d", page);

			TIFFSetField(out, TIFFTAG_SUBFILETYPE, FILETYPE_PAGE);
			TIFFSetField(out, TIFFTAG_PAGENUMBER, page);
			TIFFSetField(out, TIFFTAG_PAGENAME, page_number);
		} else {
			TIFFSetField(out, TIFFTAG_SUBFILETYPE, 0);
		}

		// palettes (image colormaps are automatically scaled to 16-bits)

		if (photometric == PHOTOMETRIC_PALETTE) {
			uint16 *r, *g, *b;
			uint16 nColors = (uint16)FreeImage_GetColorsUsed(dib);
			RGBQUAD *pal = FreeImage_GetPalette(dib);

			r = (uint16 *) _TIFFmalloc(sizeof(uint16) * 3 * nColors);
			if(r == NULL) throw FI_MSG_ERROR_MEMORY;
			g = r + nColors;
			b = g + nColors;

			for (int i = nColors - 1; i >= 0; i--) {
				r[i] = SCALE((uint16)pal[i].rgbRed);
				g[i] = SCALE((uint16)pal[i].rgbGreen);
				b[i] = SCALE((uint16)pal[i].rgbBlue);
			}

			TIFFSetField(out, TIFFTAG_COLORMAP, r, g, b);

			_TIFFfree(r);
		}

		// compression

		WriteCompression(out, bitspersample, samplesperpixel, photometric, flags);

		// metadata

		WriteMetadata(out, dib);


		// read the DIB lines from bottom to top
		// and save them in the TIF
		// -------------------------------------
		
		pitch = FreeImage_GetPitch(dib);

		if(image_type == FIT_BITMAP) {
			// standard bitmap type
		
			switch(bitsperpixel) {
				case 1 :
				case 4 :
				case 8 :
				{
					if((bitsperpixel == 8) && FreeImage_IsTransparent(dib)) {
						// 8-bit transparent picture : convert to 8-bit + 8-bit alpha

						// get the transparency table
						BYTE *trns = FreeImage_GetTransparencyTable(dib);

						BYTE *buffer = (BYTE *)malloc(2 * width * sizeof(BYTE));
						if(buffer == NULL) throw FI_MSG_ERROR_MEMORY;

						for (y = height - 1; y >= 0; y--) {
							BYTE *bits = FreeImage_GetScanLine(dib, y);

							BYTE *p = bits, *b = buffer;

							for(x = 0; x < width; x++) {
								// copy the 8-bit layer
								b[0] = *p;
								// convert the trns table to a 8-bit alpha layer
								b[1] = trns[ b[0] ];

								p++;
								b += samplesperpixel;
							}

							// write the scanline to disc

							TIFFWriteScanline(out, buffer, height - y - 1, 0);
						}

						free(buffer);
					}
					else {
						// other cases
						BYTE *buffer = (BYTE *)malloc(pitch * sizeof(BYTE));
						if(buffer == NULL) throw FI_MSG_ERROR_MEMORY;
						for (y = 0; y < height; y++) {
							// get a copy of the scanline
							memcpy(buffer, FreeImage_GetScanLine(dib, height - y - 1), pitch);
							// write the scanline to disc
							TIFFWriteScanline(out, buffer, y, 0);
						}
						free(buffer);
					}

					break;
				}				

				case 24:
				case 32:
				{
					BYTE *buffer = (BYTE *)malloc(pitch * sizeof(BYTE));
					if(buffer == NULL) throw FI_MSG_ERROR_MEMORY;

					for (y = 0; y < height; y++) {
						// get a copy of the scanline

						memcpy(buffer, FreeImage_GetScanLine(dib, height - y - 1), pitch);

#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR
						if (photometric != PHOTOMETRIC_SEPARATED) {
							// TIFFs store color data RGB(A) instead of BGR(A)
		
							BYTE *pBuf = buffer;
		
							for (x = 0; x < width; x++) {
								INPLACESWAP(pBuf[0], pBuf[2]);
								pBuf += samplesperpixel;
							}
						}
#endif
						// write the scanline to disc

						TIFFWriteScanline(out, buffer, y, 0);
					}

					free(buffer);

					break;
				}
			}

		} else if(image_type == FIT_RGBF) {
			// RGBF image => store as XYZ using a LogLuv encoding

			BYTE *buffer = (BYTE *)malloc(pitch * sizeof(BYTE));
			if(buffer == NULL) throw FI_MSG_ERROR_MEMORY;

			for (y = 0; y < height; y++) {
				// get a copy of the scanline and convert from RGB to XYZ
				tiff_ConvertLineRGBToXYZ(buffer, FreeImage_GetScanLine(dib, height - y - 1), width);
				// write the scanline to disc
				TIFFWriteScanline(out, buffer, y, 0);
			}
			free(buffer);
		} else {
			// special bitmap type (int, long, double, etc.)

			switch(bitsperpixel) {
				case 16:
				case 32:
				case 48:
				case 64:
				case 128:
				{
					BYTE *buffer = (BYTE *)malloc(pitch * sizeof(BYTE));
					if(buffer == NULL) throw FI_MSG_ERROR_MEMORY;

					for (y = 0; y < height; y++) {
						// get a copy of the scanline
						memcpy(buffer, FreeImage_GetScanLine(dib, height - y - 1), pitch);
						// write the scanline to disc
						TIFFWriteScanline(out, buffer, y, 0);
					}
					free(buffer);
				}	
				break;
			}
		}

		// write out the directory tag if we wrote a page other than -1

		if (page >= 0)
			TIFFWriteDirectory(out);		

		return TRUE;
	}

	return FALSE;
}

// ==========================================================
//   Init
// ==========================================================

void DLL_CALLCONV
InitTIFF(Plugin *plugin, int format_id) {
	s_format_id = format_id;

	plugin->format_proc = Format;
	plugin->description_proc = Description;
	plugin->extension_proc = Extension;
	plugin->regexpr_proc = RegExpr;
	plugin->open_proc = Open;
	plugin->close_proc = Close;
	plugin->pagecount_proc = PageCount;
	plugin->pagecapability_proc = NULL;
	plugin->load_proc = Load;
	plugin->save_proc = Save;
	plugin->validate_proc = Validate;
	plugin->mime_proc = MimeType;
	plugin->supports_export_bpp_proc = SupportsExportDepth;
	plugin->supports_export_type_proc = SupportsExportType;
	plugin->supports_icc_profiles_proc = SupportsICCProfiles;
}
