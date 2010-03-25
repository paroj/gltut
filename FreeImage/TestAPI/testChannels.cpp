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

void test24BitsChannels(unsigned width, unsigned height) {
	BOOL bResult = FALSE;

	// create a test 8-bit image
	FIBITMAP *src = createZonePlateImage(width, height, 128);
	if(src != NULL) {
		// convert to 24-bit
		FIBITMAP *tmp = FreeImage_ConvertTo24Bits(src);
		FreeImage_Unload(src);
		src = tmp;
	}
	assert(src != NULL);

	// save for further examination
	bResult = FreeImage_Save(FIF_PNG, src, "zoneplate.png", PNG_DEFAULT);
	assert(bResult);

	// test get/set channel
	// -------------------------	
	FIBITMAP *channel = FreeImage_GetChannel(src, FICC_GREEN);
	assert(channel != NULL);
	bResult = FreeImage_SetChannel(src, channel, FICC_GREEN);
	assert(bResult);	
	FreeImage_Unload(channel);

	FreeImage_Unload(src);
}

void test32BitsChannels(unsigned width, unsigned height) {
	BOOL bResult = FALSE;

	// create a test 8-bit image
	FIBITMAP *src = createZonePlateImage(width, height, 128);
	if(src != NULL) {
		// convert to 32-bit
		FIBITMAP *tmp = FreeImage_ConvertTo32Bits(src);
		FreeImage_Unload(src);
		src = tmp;
	}
	assert(src != NULL);

	// save for further examination
	bResult = FreeImage_Save(FIF_PNG, src, "zoneplate.png", PNG_DEFAULT);
	assert(bResult);

	// test get/set channel
	// -------------------------	
	FIBITMAP *channel = FreeImage_GetChannel(src, FICC_ALPHA);
	assert(channel != NULL);
	bResult = FreeImage_SetChannel(src, channel, FICC_ALPHA);
	assert(bResult);	
	FreeImage_Unload(channel);

	FreeImage_Unload(src);
}

void testRGBAChannels(FREE_IMAGE_TYPE image_type, unsigned width, unsigned height, BOOL bUseAlpha) {
	BOOL bResult = FALSE;

	// create a test image
	FIBITMAP *src = FreeImage_AllocateT(image_type, width, height);
	assert(src != NULL);

	// test get/set channel
	// -------------------------	
	{
		FIBITMAP *channel = FreeImage_GetChannel(src, FICC_GREEN);
		assert(channel != NULL);
		bResult = FreeImage_SetChannel(src, channel, FICC_GREEN);
		assert(bResult);	
		FreeImage_Unload(channel);
	}
	
	if(bUseAlpha) {
		FIBITMAP *alpha = FreeImage_GetChannel(src, FICC_ALPHA);
		assert(alpha != NULL);
		bResult = FreeImage_SetChannel(src, alpha, FICC_ALPHA);
		assert(bResult);	
		FreeImage_Unload(alpha);
	}

	FreeImage_Unload(src);
}

// Main test functions
// ----------------------------------------------------------

void testImageChannels(unsigned width, unsigned height) {

	BOOL bResult = FALSE;

	printf("testImageChannels ...");

	test24BitsChannels(width, height);
	test32BitsChannels(width, height);

	testRGBAChannels(FIT_RGB16, width, height, FALSE);
	testRGBAChannels(FIT_RGBA16, width, height, TRUE);

	testRGBAChannels(FIT_RGBF, width, height, FALSE);
	testRGBAChannels(FIT_RGBAF, width, height, TRUE);

	printf("\tOK\n");
}
