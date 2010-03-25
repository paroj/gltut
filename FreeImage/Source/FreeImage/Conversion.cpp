// ==========================================================
// Bitmap conversion routines
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Hervé Drolon (drolon@infonie.fr)
// - Jani Kajala (janik@remedy.fi)
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

#include "FreeImage.h"
#include "Utilities.h"
#include "Quantizers.h"

// ----------------------------------------------------------

#define CONVERT(from, to) case to : FreeImage_ConvertLine##from##To##to(bits, scanline, FreeImage_GetWidth(dib)); break;
#define CONVERTWITHPALETTE(from, to) case to : FreeImage_ConvertLine##from##To##to(bits, scanline, FreeImage_GetWidth(dib), FreeImage_GetPalette(dib)); break;

#define CONVERTTO16(from) \
	case 16 : \
		if ((red_mask == FI16_555_RED_MASK) && (green_mask == FI16_555_GREEN_MASK) && (blue_mask == FI16_555_BLUE_MASK)) { \
			FreeImage_ConvertLine##from##To16_555(bits, scanline, FreeImage_GetWidth(dib)); \
		} else { \
			FreeImage_ConvertLine##from##To16_565(bits, scanline, FreeImage_GetWidth(dib)); \
		} \
		break;

#define CONVERTTO16WITHPALETTE(from) \
	case 16 : \
		if ((red_mask == FI16_555_RED_MASK) && (green_mask == FI16_555_GREEN_MASK) && (blue_mask == FI16_555_BLUE_MASK)) { \
			FreeImage_ConvertLine##from##To16_555(bits, scanline, FreeImage_GetWidth(dib), FreeImage_GetPalette(dib)); \
		} else { \
			FreeImage_ConvertLine##from##To16_565(bits, scanline, FreeImage_GetWidth(dib), FreeImage_GetPalette(dib)); \
		} \
		break;

// ==========================================================

FIBITMAP * DLL_CALLCONV
FreeImage_ColorQuantize(FIBITMAP *dib, FREE_IMAGE_QUANTIZE quantize) {
	return FreeImage_ColorQuantizeEx(dib, quantize);
}

FIBITMAP * DLL_CALLCONV
FreeImage_ColorQuantizeEx(FIBITMAP *dib, FREE_IMAGE_QUANTIZE quantize, int PaletteSize, int ReserveSize, RGBQUAD *ReservePalette) {
	if( PaletteSize < 2 ) PaletteSize = 2;
	if( PaletteSize > 256 ) PaletteSize = 256;
	if( ReserveSize < 0 ) ReserveSize = 0;
	if( ReserveSize > PaletteSize ) ReserveSize = PaletteSize;
	if (dib) {
		if (FreeImage_GetBPP(dib) == 24) {
			switch(quantize) {
				case FIQ_WUQUANT :
				{
					try {
						WuQuantizer Q (dib);
						FIBITMAP *dst = Q.Quantize(PaletteSize, ReserveSize, ReservePalette);
						if(dst) {
							// copy metadata from src to dst
							FreeImage_CloneMetadata(dst, dib);
						}
						return dst;
					} catch (const char *) {
						return NULL;
					}
				}
				case FIQ_NNQUANT :
				{
					// sampling factor in range 1..30. 
					// 1 => slower (but better), 30 => faster. Default value is 1
					const int sampling = 1;

					NNQuantizer Q(PaletteSize);
					FIBITMAP *dst = Q.Quantize(dib, ReserveSize, ReservePalette, sampling);
					if(dst) {
						// copy metadata from src to dst
						FreeImage_CloneMetadata(dst, dib);
					}
					return dst;
				}
			}
		}
	}

	return NULL;
}

// ==========================================================

FIBITMAP * DLL_CALLCONV
FreeImage_ConvertFromRawBits(BYTE *bits, int width, int height, int pitch, unsigned bpp, unsigned red_mask, unsigned green_mask, unsigned blue_mask, BOOL topdown) {
	FIBITMAP *dib = FreeImage_Allocate(width, height, bpp, red_mask, green_mask, blue_mask);

	if (dib != NULL) {
		if (topdown) {
			for (int i = height - 1; i >= 0; --i) {
				memcpy(FreeImage_GetScanLine(dib, i), bits, FreeImage_GetLine(dib));
				bits += pitch;
			}
		} else {
			for (int i = 0; i < height; ++i) {			
				memcpy(FreeImage_GetScanLine(dib, i), bits, FreeImage_GetLine(dib));
				bits += pitch;
			}
		}
	}

	return dib;
}

void DLL_CALLCONV
FreeImage_ConvertToRawBits(BYTE *bits, FIBITMAP *dib, int pitch, unsigned bpp, unsigned red_mask, unsigned green_mask, unsigned blue_mask, BOOL topdown) {
	if ((dib != NULL) && (bits != NULL)) {
		for (unsigned i = 0; i < FreeImage_GetHeight(dib); ++i) {
			BYTE *scanline = FreeImage_GetScanLine(dib, topdown ? (FreeImage_GetHeight(dib) - i - 1) : i);

			if ((bpp == 16) && (FreeImage_GetBPP(dib) == 16)) {
				// convert 555 to 565 or vice versa

				if ((red_mask == FI16_555_RED_MASK) && (green_mask == FI16_555_GREEN_MASK) && (blue_mask == FI16_555_BLUE_MASK)) {
					if ((FreeImage_GetRedMask(dib) == FI16_565_RED_MASK) && (FreeImage_GetGreenMask(dib) == FI16_565_GREEN_MASK) && (FreeImage_GetBlueMask(dib) == FI16_565_BLUE_MASK)) {
						FreeImage_ConvertLine16_565_To16_555(bits, scanline, FreeImage_GetWidth(dib));
					} else {
						memcpy(bits, scanline, FreeImage_GetLine(dib));
					}
				} else {
					if ((FreeImage_GetRedMask(dib) == FI16_555_RED_MASK) && (FreeImage_GetGreenMask(dib) == FI16_555_GREEN_MASK) && (FreeImage_GetBlueMask(dib) == FI16_555_BLUE_MASK)) {
						FreeImage_ConvertLine16_555_To16_565(bits, scanline, FreeImage_GetWidth(dib));
					} else {
						memcpy(bits, scanline, FreeImage_GetLine(dib));
					}
				}
			} else if (FreeImage_GetBPP(dib) != bpp) {
				switch(FreeImage_GetBPP(dib)) {
					case 1 :
						switch(bpp) {
							CONVERT(1, 8)
							CONVERTTO16WITHPALETTE(1)
							CONVERTWITHPALETTE(1, 24)
							CONVERTWITHPALETTE(1, 32)
						};

						break;

					case 4 :
						switch(bpp) {
							CONVERT(4, 8)
							CONVERTTO16WITHPALETTE(4)
							CONVERTWITHPALETTE(4, 24)
							CONVERTWITHPALETTE(4, 32)
						};

						break;

					case 8 :
						switch(bpp) {
							CONVERTTO16WITHPALETTE(8)
							CONVERTWITHPALETTE(8, 24)
							CONVERTWITHPALETTE(8, 32)
						};

						break;

					case 24 :
						switch(bpp) {
							CONVERT(24, 8)
							CONVERTTO16(24)
							CONVERT(24, 32)
						};

						break;

					case 32 :
						switch(bpp) {
							CONVERT(32, 8)
							CONVERTTO16(32)
							CONVERT(32, 24)
						};

						break;
				};
			} else {
				memcpy(bits, scanline, FreeImage_GetLine(dib));
			}

			bits += pitch;
		}
	}
}
