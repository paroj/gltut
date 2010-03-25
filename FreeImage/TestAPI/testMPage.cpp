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

void  
testBuildMPage(char *src_filename, char *dst_filename, FREE_IMAGE_FORMAT dst_fif, unsigned bpp) {
	// get the file type
	FREE_IMAGE_FORMAT src_fif = FreeImage_GetFileType(src_filename);
	// load the file
	FIBITMAP *src = FreeImage_Load(src_fif, src_filename, 0); //24bit image 
	unsigned src_bpp = FreeImage_GetBPP(src);
	// convert to the requested bitdepth
	if(src_bpp != bpp) {
		FIBITMAP *tmp = NULL;
		switch(bpp) {
			case 8:
				tmp = FreeImage_ConvertTo8Bits(src);
				break;
			case 24:
				tmp = FreeImage_ConvertTo24Bits(src);
				break;
		}
		assert(tmp != NULL);
		FreeImage_Unload(src); 
		src = tmp;
	}

	FIMULTIBITMAP *out = FreeImage_OpenMultiBitmap(dst_fif, dst_filename, TRUE, FALSE, FALSE); 
	for(int size = 16; size <= 48; size += 16 ) { 
		FIBITMAP *rescaled = FreeImage_Rescale(src, size, size, FILTER_CATMULLROM);
		if((src_bpp == 8) && FreeImage_IsTransparent(src)) {
			// copy the transparency table
			BYTE *trns = FreeImage_GetTransparencyTable(src);
			int count = FreeImage_GetTransparencyCount(src);
			FreeImage_SetTransparencyTable(rescaled, trns, count);
		}
		FreeImage_AppendPage(out, rescaled); 
		FreeImage_Unload(rescaled); 
	} 
	
	FreeImage_Unload(src); 
	
	FreeImage_CloseMultiBitmap(out, 0); 

}

void testMPageCache(char *src_filename) {
	const char *dst_filename = "mpages.tif";

	BOOL keep_cache_in_memory = FALSE;

	// get the file type
	FREE_IMAGE_FORMAT src_fif = FreeImage_GetFileType(src_filename);
	// load the file
	FIBITMAP *src = FreeImage_Load(src_fif, src_filename, 0); //24bit image 
	assert(src != NULL);

	// convert to 24-bit
	if(FreeImage_GetBPP(src) != 24) {
		FIBITMAP *tmp = FreeImage_ConvertTo24Bits(src);
		assert(tmp != NULL);
		FreeImage_Unload(src); 
		src = tmp;
	}

	FIMULTIBITMAP *out = FreeImage_OpenMultiBitmap(FIF_TIFF, dst_filename, TRUE, FALSE, keep_cache_in_memory); 

	// attempt to create 16 480X360 images in a 24-bit TIFF multipage file
	FIBITMAP *rescaled = FreeImage_Rescale(src, 480, 360, FILTER_CATMULLROM);
	for(int i = 0; i < 16; i++) { 		
		FreeImage_AppendPage(out, rescaled); 
	} 
	FreeImage_Unload(rescaled); 
	
	FreeImage_Unload(src); 
	
	FreeImage_CloseMultiBitmap(out, 0); 
}
