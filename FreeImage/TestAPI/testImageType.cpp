// ==========================================================
// FreeImage 3 Test Script
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


#include "TestSuite.h"

// Local test functions
// ----------------------------------------------------------

BOOL testClone(const char *lpszPathName) {
	FIBITMAP *dib1 = NULL, *dib2 = NULL; 

	try {
		FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(lpszPathName);

		dib1 = FreeImage_Load(fif, lpszPathName, 0); 
		if(!dib1) throw(1);
		
		dib2 = FreeImage_Clone(dib1); 
		if(!dib2) throw(1);
		
		FreeImage_Unload(dib1); 
		FreeImage_Unload(dib2); 

		return TRUE;
	} 
	catch(int) {
		if(dib1) FreeImage_Unload(dib1); 
		if(dib2) FreeImage_Unload(dib2); 
		return FALSE;
	}
	
	return FALSE; 
}

void testAllocateCloneUnload(const char *lpszPathName) {
	printf("testAllocateCloneUnload ...");

	BOOL bResult = testClone(lpszPathName);
	assert(bResult);

	printf("\tOK\n");
}

BOOL testAllocateCloneUnloadType(FREE_IMAGE_TYPE image_type, unsigned width, unsigned height) {
	FIBITMAP *image = NULL;
	FIBITMAP *clone = NULL;
	FIBITMAP *standard = NULL;

	unsigned x, y;

	try {
		// test allocation function
		image = FreeImage_AllocateT(image_type, width, height, 8);
		if(!image) throw(1);

		FREE_IMAGE_TYPE type = FreeImage_GetImageType(image);
		if(image_type != type) throw(1);

		// test pixel access
		switch(image_type) {
			case FIT_BITMAP:
				if(FreeImage_GetBPP(image) == 8) {
					for(y = 0; y < FreeImage_GetHeight(image); y++) {
						BYTE *bits = (BYTE *)FreeImage_GetScanLine(image, y);
						for(x = 0; x < FreeImage_GetWidth(image); x++) {
							bits[x] = 128;
						}
					}
				}
				break;
			case FIT_UINT16:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					unsigned short *bits = (unsigned short *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x] = 128;
					}
				}
				break;
			case FIT_INT16:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					short *bits = (short *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x] = 128;
					}
				}
				break;
			case FIT_UINT32:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					unsigned long *bits = (unsigned long *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x] = 128;
					}
				}
				break;
			case FIT_INT32:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					long *bits = (long *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x] = 128;
					}
				}
				break;
			case FIT_FLOAT:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					float *bits = (float *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x] = 128;
					}
				}
				break;
			case FIT_DOUBLE:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					double *bits = (double *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x] = 128;
					}
				}
				break;
			case FIT_COMPLEX:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					FICOMPLEX *bits = (FICOMPLEX *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x].r = 128;
						bits[x].i = 128;
					}
				}
				break;
			case FIT_RGB16:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					FIRGB16 *bits = (FIRGB16 *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x].red = 128;
						bits[x].green = 128;
						bits[x].blue = 128;
					}
				}
				break;
			case FIT_RGBF:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					FIRGBF *bits = (FIRGBF *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x].red = 128;
						bits[x].green = 128;
						bits[x].blue = 128;
					}
				}
				break;
			case FIT_RGBA16:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					FIRGBA16 *bits = (FIRGBA16 *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x].red = 128;
						bits[x].green = 128;
						bits[x].blue = 128;
						bits[x].alpha = 128;
					}
				}
				break;	
			case FIT_RGBAF:
				for(y = 0; y < FreeImage_GetHeight(image); y++) {
					FIRGBAF *bits = (FIRGBAF *)FreeImage_GetScanLine(image, y);
					for(x = 0; x < FreeImage_GetWidth(image); x++) {
						bits[x].red = 128;
						bits[x].green = 128;
						bits[x].blue = 128;
						bits[x].alpha = 128;
					}
				}
				break;
		}

		
		// test clone function
		clone = FreeImage_Clone(image);
		if(!clone) throw(1);

		if(FreeImage_GetImageType(clone) != image_type)	throw(1);

		switch(image_type) {
			case FIT_BITMAP:
				if(FreeImage_GetBPP(clone) == 8) {
					for(y = 0; y < FreeImage_GetHeight(clone); y++) {
						BYTE *bits = (BYTE *)FreeImage_GetScanLine(clone, y);
						for(x = 0; x < FreeImage_GetWidth(clone); x++) {
							if(bits[x] != 128)
								throw(1);
						}
					}
				}
				break;
			case FIT_UINT16:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					unsigned short *bits = (unsigned short *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if(bits[x] != 128)
							throw(1);
					}
				}
				break;
			case FIT_INT16:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					short *bits = (short *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if(bits[x] != 128)
							throw(1);
					}
				}
				break;
			case FIT_UINT32:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					unsigned long *bits = (unsigned long *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if(bits[x] != 128)
							throw(1);
					}
				}
				break;
			case FIT_INT32:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					long *bits = (long *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if(bits[x] != 128)
							throw(1);
					}
				}
				break;
			case FIT_FLOAT:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					float *bits = (float *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if(bits[x] != 128)
							throw(1);
					}
				}
				break;
			case FIT_DOUBLE:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					double *bits = (double *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if(bits[x] != 128)
							throw(1);
					}
				}
				break;
			case FIT_COMPLEX:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					FICOMPLEX *bits = (FICOMPLEX *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if((bits[x].r != 128) || ((bits[x].r - bits[x].i) != 0))
							throw(1);
					}
				}
				break;
			case FIT_RGB16:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					FIRGB16 *bits = (FIRGB16 *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if((bits[x].red != 128) || (bits[x].green != 128) || (bits[x].blue != 128))
							throw(1);
					}
				}
				break;
			case FIT_RGBF:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					FIRGBF *bits = (FIRGBF *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if((bits[x].red != 128) || (bits[x].green != 128) || (bits[x].blue != 128))
							throw(1);
					}
				}
				break;
			case FIT_RGBA16:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					FIRGBA16 *bits = (FIRGBA16 *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if((bits[x].red != 128) || (bits[x].green != 128) || (bits[x].blue != 128) || (bits[x].alpha != 128))
							throw(1);
					}
				}
				break;	
			case FIT_RGBAF:
				for(y = 0; y < FreeImage_GetHeight(clone); y++) {
					FIRGBAF *bits = (FIRGBAF *)FreeImage_GetScanLine(clone, y);
					for(x = 0; x < FreeImage_GetWidth(clone); x++) {
						if((bits[x].red != 128) || (bits[x].green != 128) || (bits[x].blue != 128) || (bits[x].alpha != 128))
							throw(1);
					}
				}
				break;

		}

		// test unload function
		FreeImage_Unload(clone);
		clone = NULL;
		FreeImage_Unload(image);
		image = NULL;

	} catch(int) {
		if(image) FreeImage_Unload(image);
		if(clone) FreeImage_Unload(clone);
		return FALSE;
	}
	return TRUE;
}

BOOL testLoadSaveConvertImageType(FIBITMAP *src, FREE_IMAGE_TYPE image_type, unsigned width, unsigned height) {
	FIBITMAP *dst = NULL;
	FIBITMAP *chk = NULL;
	BOOL bResult = TRUE;

	try {
		// convert to type image_type
		dst = FreeImage_ConvertToType(src, image_type);
		if(!dst) throw(1);

		// save image as TIFF
		bResult = FreeImage_Save(FIF_TIFF, dst, "TestImageType.tif", TIFF_DEFAULT);
		if(!bResult) throw(1);

		// destroy dst
		FreeImage_Unload(dst);
		dst = NULL;

		// load image
		dst = FreeImage_Load(FIF_TIFF, "TestImageType.tif", TIFF_DEFAULT);
		if(!dst) throw(1);

		// convert to standard bitmap (linear scaling)
		chk = FreeImage_ConvertToType(dst, FIT_BITMAP, TRUE);
		if(!chk) throw(1);
		FreeImage_Unload(dst);
		dst = NULL;

		// save image as TIFF
		bResult = FreeImage_Save(FIF_TIFF, chk, "TestImageType.tif", TIFF_DEFAULT);
		if(!bResult) throw(1);
		FreeImage_Unload(chk);
		chk = NULL;


	} catch(int) {
		if(dst) FreeImage_Unload(dst);
		if(chk) FreeImage_Unload(chk);
		return FALSE;
	}

	return TRUE;
}

BOOL testLoadSaveConvertComplexType(FIBITMAP *src, unsigned width, unsigned height, FREE_IMAGE_COLOR_CHANNEL channel) {
	FIBITMAP *dst = NULL;
	FIBITMAP *chk_double = NULL;
	FIBITMAP *chk = NULL;
	BOOL bResult = TRUE;

	try {
		// convert to type FICOMPLEX
		dst = FreeImage_ConvertToType(src, FIT_COMPLEX);
		if(!dst) throw(1);

		// save image as TIFF
		bResult = FreeImage_Save(FIF_TIFF, dst, "TestImageType.tif", TIFF_DEFAULT);
		if(!bResult) throw(1);

		// destroy dst
		FreeImage_Unload(dst);
		dst = NULL;

		// load image
		dst = FreeImage_Load(FIF_TIFF, "TestImageType.tif", TIFF_DEFAULT);
		if(!dst) throw(1);

		
		// convert to type FIT_DOUBLE
		chk_double = FreeImage_GetComplexChannel(dst, channel);
		if(!chk_double) throw(1);
		FreeImage_Unload(dst);
		dst = NULL;
		
		// convert to standard bitmap (linear scaling)
		chk = FreeImage_ConvertToType(chk_double, FIT_BITMAP, TRUE);
		if(!chk) throw(1);
		FreeImage_Unload(chk_double);
		chk_double = NULL;

		// save image as TIFF
		bResult = FreeImage_Save(FIF_TIFF, chk, "TestImageType.tif", TIFF_DEFAULT);
		if(!bResult) throw(1);
		FreeImage_Unload(chk);
		chk = NULL;


	} catch(int) {
		if(dst) FreeImage_Unload(dst);
		if(chk_double) FreeImage_Unload(chk_double);
		if(chk) FreeImage_Unload(chk);
		return FALSE;
	}

	return TRUE;
}

// Main test functions
// ----------------------------------------------------------

void testImageType(unsigned width, unsigned height) {
	BOOL bResult = FALSE;

	printf("testImageType ...");

	bResult = testAllocateCloneUnloadType(FIT_BITMAP, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_UINT16, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_INT16, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_UINT32, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_INT32, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_FLOAT, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_DOUBLE, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_COMPLEX, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_RGB16, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_RGBA16, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_RGBF, width, height);
	assert(bResult);
	bResult = testAllocateCloneUnloadType(FIT_RGBAF, width, height);
	assert(bResult);


	printf("\tOK\n");
}


void testImageTypeTIFF(unsigned width, unsigned height) {
	BOOL bResult = FALSE;

	printf("testImageTypeTIFF ...");

	// create a test 8-bit image
	FIBITMAP *src = createZonePlateImage(width, height, 128);
	assert(src != NULL);

	// save for further examination
	bResult = FreeImage_Save(FIF_PNG, src, "zoneplate.png", PNG_DEFAULT);
	assert(bResult);

	// test load /save / convert
	// -------------------------	

	bResult = testLoadSaveConvertImageType(src, FIT_BITMAP, width, height);
	assert(bResult);
	bResult = testLoadSaveConvertImageType(src, FIT_UINT16, width, height);
	assert(bResult);
	bResult = testLoadSaveConvertImageType(src, FIT_INT16, width, height);
	assert(bResult);
	bResult = testLoadSaveConvertImageType(src, FIT_UINT32, width, height);
	assert(bResult);
	bResult = testLoadSaveConvertImageType(src, FIT_INT32, width, height);
	assert(bResult);
	bResult = testLoadSaveConvertImageType(src, FIT_FLOAT, width, height);
	assert(bResult);
	bResult = testLoadSaveConvertImageType(src, FIT_DOUBLE, width, height);
	assert(bResult);

	// complex type
	bResult = testLoadSaveConvertComplexType(src, width, height, FICC_REAL);
	assert(bResult);
	bResult = testLoadSaveConvertComplexType(src, width, height, FICC_IMAG);
	assert(bResult);
	bResult = testLoadSaveConvertComplexType(src, width, height, FICC_MAG);
	assert(bResult);
	bResult = testLoadSaveConvertComplexType(src, width, height, FICC_PHASE);
	assert(bResult);

	// free test image
	FreeImage_Unload(src);

	printf("\tOK\n");
}
