// ==========================================================
// Bitmap conversion routines
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Hervé Drolon (drolon@infonie.fr)
// - Jani Kajala (janik@remedy.fi)
// - Karl-Heinz Bussian (khbussian@moss.de)
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

// ----------------------------------------------------------
//  internal conversions X to 8 bits
// ----------------------------------------------------------

void DLL_CALLCONV
FreeImage_ConvertLine1To8(BYTE *target, BYTE *source, int width_in_pixels) {
	for (int cols = 0; cols < width_in_pixels; cols++)
		target[cols] = (source[cols >> 3] & (0x80 >> (cols & 0x07))) != 0 ? 255 : 0;	
}

void DLL_CALLCONV
FreeImage_ConvertLine4To8(BYTE *target, BYTE *source, int width_in_pixels) {
	int count_new = 0;
	int count_org = 0;
	BOOL hinibble = TRUE;

	while (count_new < width_in_pixels) {
		if (hinibble) {
			target[count_new] = (source[count_org] & 0xF0) >> 4;
		} else {
			target[count_new] = (source[count_org] & 0x0F);

			count_org++;
		}

		hinibble = !hinibble;

		count_new++;
	}
}

void DLL_CALLCONV
FreeImage_ConvertLine16To8_555(BYTE *target, BYTE *source, int width_in_pixels) {
	WORD *bits = (WORD *)source;

	for (int cols = 0; cols < width_in_pixels; cols++) {
		target[cols] = GREY((((bits[cols] & FI16_555_RED_MASK) >> FI16_555_RED_SHIFT) * 0xFF) / 0x1F,
			                (((bits[cols] & FI16_555_GREEN_MASK) >> FI16_555_GREEN_SHIFT) * 0xFF) / 0x1F,
							(((bits[cols] & FI16_555_BLUE_MASK) >> FI16_555_BLUE_SHIFT) * 0xFF) / 0x1F);
	}
}

void DLL_CALLCONV
FreeImage_ConvertLine16To8_565(BYTE *target, BYTE *source, int width_in_pixels) {
	WORD *bits = (WORD *)source;

	for (int cols = 0; cols < width_in_pixels; cols++)
		target[cols] = GREY((((bits[cols] & FI16_565_RED_MASK) >> FI16_565_RED_SHIFT) * 0xFF) / 0x1F,
			        (((bits[cols] & FI16_565_GREEN_MASK) >> FI16_565_GREEN_SHIFT) * 0xFF) / 0x3F,
					(((bits[cols] & FI16_565_BLUE_MASK) >> FI16_565_BLUE_SHIFT) * 0xFF) / 0x1F);	
}

void DLL_CALLCONV
FreeImage_ConvertLine24To8(BYTE *target, BYTE *source, int width_in_pixels) {
	for (int cols = 0; cols < width_in_pixels; cols++) {
		target[cols] = GREY(source[FI_RGBA_RED], source[FI_RGBA_GREEN], source[FI_RGBA_BLUE]);

		source += 3;
	}
}

void DLL_CALLCONV
FreeImage_ConvertLine32To8(BYTE *target, BYTE *source, int width_in_pixels) {
	for (int cols = 0; cols < width_in_pixels; cols++) {
		target[cols] = GREY(source[FI_RGBA_RED], source[FI_RGBA_GREEN], source[FI_RGBA_BLUE]);

		source += 4;
	}
}

// ----------------------------------------------------------
//   smart convert X to 8 bits
// ----------------------------------------------------------

FIBITMAP * DLL_CALLCONV
FreeImage_ConvertTo8Bits(FIBITMAP *dib) {
	if(!dib) return NULL;

	const int bpp = FreeImage_GetBPP(dib);

	const FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);
	if((image_type != FIT_BITMAP) && (image_type != FIT_UINT16)) {
		return NULL;
	}

	if(bpp != 8) {
		const int width  = FreeImage_GetWidth(dib);
		const int height = FreeImage_GetHeight(dib);
		FIBITMAP *new_dib = FreeImage_Allocate(width, height, 8);

		if(new_dib == NULL) {
			return NULL;
		}

		// copy metadata from src to dst
		FreeImage_CloneMetadata(new_dib, dib);

		// Build a greyscale palette (*always* needed for image processing)

		RGBQUAD *new_pal = FreeImage_GetPalette(new_dib);

		for(int i = 0; i < 256; i++) {
			new_pal[i].rgbRed	= (BYTE)i;
			new_pal[i].rgbGreen = (BYTE)i;
			new_pal[i].rgbBlue	= (BYTE)i;
		}

		if(image_type == FIT_BITMAP) {

			switch(bpp) {
				case 1:
				{
					if(FreeImage_GetColorType(dib) == FIC_PALETTE) {

						// Copy the palette

						RGBQUAD *old_pal = FreeImage_GetPalette(dib);
						memcpy(&new_pal[0], &old_pal[0], sizeof(RGBQUAD));
						memcpy(&new_pal[255], &old_pal[1], sizeof(RGBQUAD));

					}
					else if(FreeImage_GetColorType(dib) == FIC_MINISWHITE) {
						
						// Reverse the grayscale palette

						for(int i = 0; i < 256; i++) {
							new_pal[i].rgbRed = new_pal[i].rgbGreen = new_pal[i].rgbBlue = (BYTE)(255 - i);
						}
					}


					// Expand and copy the bitmap data

					for (int rows = 0; rows < height; rows++) {
						FreeImage_ConvertLine1To8(FreeImage_GetScanLine(new_dib, rows), FreeImage_GetScanLine(dib, rows), width);
					}
					return new_dib;
				}

				case 4 :
				{
					if(FreeImage_GetColorType(dib) == FIC_PALETTE) {

						// Copy the palette

						RGBQUAD *old_pal = FreeImage_GetPalette(dib);

						for (int i = 0; i < 16; i++) {
							new_pal[i].rgbRed	= old_pal[i].rgbRed;
							new_pal[i].rgbGreen = old_pal[i].rgbGreen;
							new_pal[i].rgbBlue	= old_pal[i].rgbBlue;
						}
					}

					// Expand and copy the bitmap data

					for (int rows = 0; rows < height; rows++) {
						FreeImage_ConvertLine4To8(FreeImage_GetScanLine(new_dib, rows), FreeImage_GetScanLine(dib, rows), width);					
					}
					return new_dib;
				}

				case 16 :
				{
					// Expand and copy the bitmap data

					for (int rows = 0; rows < height; rows++) {
						if ((FreeImage_GetRedMask(dib) == FI16_565_RED_MASK) && (FreeImage_GetGreenMask(dib) == FI16_565_GREEN_MASK) && (FreeImage_GetBlueMask(dib) == FI16_565_BLUE_MASK)) {
							FreeImage_ConvertLine16To8_565(FreeImage_GetScanLine(new_dib, rows), FreeImage_GetScanLine(dib, rows), width);
						} else {
							FreeImage_ConvertLine16To8_555(FreeImage_GetScanLine(new_dib, rows), FreeImage_GetScanLine(dib, rows), width);
						}
					}
					
					return new_dib;
				}

				case 24 :
				{
					// Expand and copy the bitmap data

					for (int rows = 0; rows < height; rows++) {
						FreeImage_ConvertLine24To8(FreeImage_GetScanLine(new_dib, rows), FreeImage_GetScanLine(dib, rows), width);					
					}
					return new_dib;
				}

				case 32 :
				{
					// Expand and copy the bitmap data

					for (int rows = 0; rows < height; rows++) {
						FreeImage_ConvertLine32To8(FreeImage_GetScanLine(new_dib, rows), FreeImage_GetScanLine(dib, rows), width);
					}
					return new_dib;
				}
			}

		} else if(image_type == FIT_UINT16) {

			const unsigned src_pitch = FreeImage_GetPitch(dib);
			const unsigned dst_pitch = FreeImage_GetPitch(new_dib);
			const BYTE *src_bits = FreeImage_GetBits(dib);
			BYTE *dst_bits = FreeImage_GetBits(new_dib);
			for (int rows = 0; rows < height; rows++) {
				const WORD *src_pixel = (WORD*)src_bits;
				BYTE *dst_pixel = (BYTE*)dst_bits;
				for(int cols = 0; cols < width; cols++) {
					dst_pixel[cols] = (BYTE)(src_pixel[cols] >> 8);
				}
				src_bits += src_pitch;
				dst_bits += dst_pitch;
			}

			return new_dib;

		} 

	} // bpp != 8

	return FreeImage_Clone(dib);
}

FIBITMAP * DLL_CALLCONV
FreeImage_ConvertToGreyscale(FIBITMAP *dib) {
	if(!dib) return NULL;

	const FREE_IMAGE_COLOR_TYPE color_type = FreeImage_GetColorType(dib);
	const int bpp = FreeImage_GetBPP(dib);

	if((color_type == FIC_PALETTE) || (color_type == FIC_MINISWHITE)) {
		const int width  = FreeImage_GetWidth(dib);
		const int height = FreeImage_GetHeight(dib);
		FIBITMAP *new_dib = FreeImage_Allocate(width, height, 8);

		if(new_dib == NULL) {
			return NULL;
		}

		// copy metadata from src to dst
		FreeImage_CloneMetadata(new_dib, dib);

		// Build a greyscale palette

		RGBQUAD *new_pal = FreeImage_GetPalette(new_dib);

		for(int i = 0; i < 256; i++) {
			new_pal[i].rgbRed	= (BYTE)i;
			new_pal[i].rgbGreen = (BYTE)i;
			new_pal[i].rgbBlue	= (BYTE)i;
		}

		// allocate a 24-bit buffer

		BYTE *buffer = (BYTE*)malloc( CalculatePitch(CalculateLine(width, 24)) );
		if(NULL == buffer) {
			FreeImage_Unload(new_dib);
			return NULL;
		}

		// Convert the palette to 24-bit, then to 8-bit

		switch(bpp) {
			case 1:
			{
				for (int rows = 0; rows < height; rows++) {
					FreeImage_ConvertLine1To24(buffer, FreeImage_GetScanLine(dib, rows), width, FreeImage_GetPalette(dib));
					FreeImage_ConvertLine24To8(FreeImage_GetScanLine(new_dib, rows), buffer, width);
				}
			}
			break;

			case 4:
			{
				for (int rows = 0; rows < height; rows++) {
					FreeImage_ConvertLine4To24(buffer, FreeImage_GetScanLine(dib, rows), width, FreeImage_GetPalette(dib));
					FreeImage_ConvertLine24To8(FreeImage_GetScanLine(new_dib, rows), buffer, width);
				}
			}
			break;

			case 8:
			{
				for (int rows = 0; rows < height; rows++) {
					FreeImage_ConvertLine8To24(buffer, FreeImage_GetScanLine(dib, rows), width, FreeImage_GetPalette(dib));
					FreeImage_ConvertLine24To8(FreeImage_GetScanLine(new_dib, rows), buffer, width);
				}
			}
			break;

		}
		free(buffer);

		return new_dib;

	} 
	
	// Convert the bitmap to 8-bit greyscale
	return FreeImage_ConvertTo8Bits(dib);
}
