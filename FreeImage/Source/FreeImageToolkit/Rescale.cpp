// ==========================================================
// Upsampling / downsampling routine
//
// Design and implementation by
// - Hervé Drolon (drolon@infonie.fr)
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

#include "Resize.h"

FIBITMAP * DLL_CALLCONV 
FreeImage_Rescale(FIBITMAP *src, int dst_width, int dst_height, FREE_IMAGE_FILTER filter) {
	FIBITMAP *dst = NULL;

	if (!src || (dst_width <= 0) || (dst_height <= 0) || (FreeImage_GetWidth(src) <= 0) || (FreeImage_GetHeight(src) <= 0)) {
		return NULL;
	}

	// select the filter
	CGenericFilter *pFilter = NULL;
	switch(filter) {
		case FILTER_BOX:
			pFilter = new CBoxFilter();
			break;
		case FILTER_BICUBIC:
			pFilter = new CBicubicFilter();
			break;
		case FILTER_BILINEAR:
			pFilter = new CBilinearFilter();
			break;
		case FILTER_BSPLINE:
			pFilter = new CBSplineFilter();
			break;
		case FILTER_CATMULLROM:
			pFilter = new CCatmullRomFilter();
			break;
		case FILTER_LANCZOS3:
			pFilter = new CLanczos3Filter();
			break;
	}

	CResizeEngine Engine(pFilter);

	// perform upsampling or downsampling

	if((FreeImage_GetBPP(src) == 4) || (FreeImage_GetColorType(src) == FIC_PALETTE)) {
		// special case for 4-bit images or color map indexed images ...
		if(FreeImage_IsTransparent(src) == FALSE) {
			FIBITMAP *src24 = NULL;
			FIBITMAP *dst24 = NULL;
			try {
				// transparent conversion to 24-bit (any transparency table will be destroyed)
				src24 = FreeImage_ConvertTo24Bits(src);
				if(!src24) throw(1);
				// perform upsampling or downsampling
				dst24 = Engine.scale(src24, dst_width, dst_height);
				if(!dst24) throw(1);
				// color quantize to 8-bit
				dst = FreeImage_ColorQuantize(dst24, FIQ_NNQUANT);
				// free and return
				FreeImage_Unload(src24);
				FreeImage_Unload(dst24);
			} catch(int) {
				if(src24) FreeImage_Unload(src24);
				if(dst24) FreeImage_Unload(dst24);
			}
		} else {
			FIBITMAP *src32 = NULL;
			try {
				// transparent conversion to 32-bit (keep transparency)
				src32 = FreeImage_ConvertTo32Bits(src);
				if(!src32) throw(1);
				// perform upsampling or downsampling
				dst = Engine.scale(src32, dst_width, dst_height);
				if(!dst) throw(1);
				// free and return
				FreeImage_Unload(src32);
			} catch(int) {
				if(src32) FreeImage_Unload(src32);
				if(dst) FreeImage_Unload(dst);
			}
		}
	}
	else if((FreeImage_GetBPP(src) == 16) && (FreeImage_GetImageType(src) == FIT_BITMAP)) {
		// convert 16-bit RGB to 24-bit
		FIBITMAP *src24 = NULL;
		try {
			// transparent conversion to 24-bit (any transparency table will be destroyed)
			src24 = FreeImage_ConvertTo24Bits(src);
			if(!src24) throw(1);
			// perform upsampling or downsampling
			dst = Engine.scale(src24, dst_width, dst_height);
			if(!dst) throw(1);
			// free and return
			FreeImage_Unload(src24);
		} catch(int) {
			if(src24) FreeImage_Unload(src24);
			if(dst) FreeImage_Unload(dst);
		}
	}
	else {
		// normal case : 
		// 1- or 8-bit greyscale, 24- or 32-bit RGB(A) images
		// 16-bit greyscale, 48- or 64-bit RGB(A) images
		// 32-bit float, 96- or 128-bit RGB(A) float images
		dst = Engine.scale(src, dst_width, dst_height);
	}


	delete pFilter;

	// copy metadata from src to dst
	FreeImage_CloneMetadata(dst, src);
	
	return dst;
}

FIBITMAP * DLL_CALLCONV 
FreeImage_MakeThumbnail(FIBITMAP *dib, int max_pixel_size, BOOL convert) {
	FIBITMAP *thumbnail = NULL;
	int new_width, new_height;

	if(!dib || (max_pixel_size <= 0)) return NULL;

	int width	= FreeImage_GetWidth(dib);
	int height = FreeImage_GetHeight(dib);

	if(max_pixel_size == 0) max_pixel_size = 1;

	if((width < max_pixel_size) && (height < max_pixel_size)) {
		// image is smaller than the requested thumbnail
		return FreeImage_Clone(dib);
	}

	if(width > height) {
		new_width = max_pixel_size;
		// change image height with the same ratio
		double ratio = ((double)new_width / (double)width);
		new_height = (int)(height * ratio + 0.5);
		if(new_height == 0) new_height = 1;
	} else {
		new_height = max_pixel_size;
		// change image width with the same ratio
		double ratio = ((double)new_height / (double)height);
		new_width = (int)(width * ratio + 0.5);
		if(new_width == 0) new_width = 1;
	}

	const FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);

	// perform downsampling using a bilinear interpolation

	switch(image_type) {
		case FIT_BITMAP:
		case FIT_UINT16:
		case FIT_RGB16:
		case FIT_RGBA16:
		case FIT_FLOAT:
		case FIT_RGBF:
		case FIT_RGBAF:
		{
			FREE_IMAGE_FILTER filter = FILTER_BILINEAR;
			thumbnail = FreeImage_Rescale(dib, new_width, new_height, filter);
		}
		break;

		case FIT_INT16:
		case FIT_UINT32:
		case FIT_INT32:
		case FIT_DOUBLE:
		case FIT_COMPLEX:
		default:
			// cannot rescale this kind of image
			thumbnail = NULL;
			break;
	}

	if((thumbnail != NULL) && (image_type != FIT_BITMAP) && convert) {
		// convert to a standard bitmap
		FIBITMAP *bitmap = NULL;
		switch(image_type) {
			case FIT_UINT16:
				bitmap = FreeImage_ConvertTo8Bits(thumbnail);
				break;
			case FIT_RGB16:
				bitmap = FreeImage_ConvertTo24Bits(thumbnail);
				break;
			case FIT_RGBA16:
				bitmap = FreeImage_ConvertTo32Bits(thumbnail);
				break;
			case FIT_FLOAT:
				bitmap = FreeImage_ConvertToStandardType(thumbnail, TRUE);
				break;
			case FIT_RGBF:
				bitmap = FreeImage_ToneMapping(thumbnail, FITMO_DRAGO03);
				break;
			case FIT_RGBAF:
				// no way to keep the transparency yet ...
				FIBITMAP *rgbf = FreeImage_ConvertToRGBF(thumbnail);
				bitmap = FreeImage_ToneMapping(rgbf, FITMO_DRAGO03);
				FreeImage_Unload(rgbf);
				break;
		}
		if(bitmap != NULL) {
			FreeImage_Unload(thumbnail);
			thumbnail = bitmap;
		}
	}

	// copy metadata from src to dst
	FreeImage_CloneMetadata(thumbnail, dib);
	
	return thumbnail;
}
