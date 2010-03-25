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

void testJPEGTransform(const char *src_file) {
	BOOL bResult;
	BOOL perfect;

	// perfect transformation
	perfect = TRUE;
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_FLIP_H, perfect);
	assert(bResult == FALSE);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_FLIP_V, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_TRANSPOSE, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_TRANSVERSE, perfect);
	assert(bResult == FALSE);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_ROTATE_90, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_ROTATE_180, perfect);
	assert(bResult == FALSE);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_ROTATE_270, perfect);
	assert(bResult == FALSE);

	// non perfect transformation
	perfect = FALSE;
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_FLIP_H, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_FLIP_V, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_TRANSPOSE, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_TRANSVERSE, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_ROTATE_90, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_ROTATE_180, perfect);
	assert(bResult);
	bResult = FreeImage_JPEGTransform(src_file, "test.jpg", FIJPEG_OP_ROTATE_270, perfect);
	assert(bResult);

}

void testJPEGCrop(const char *src_file) {
	BOOL bResult;
	bResult = FreeImage_JPEGCrop(src_file, "test.jpg", 50, 100, 359, 354);
	assert(bResult);
	bResult = FreeImage_JPEGCrop(src_file, "test.jpg", 50, 100, 650, 500);
	assert(bResult == FALSE);
}

// Main test function
// ----------------------------------------------------------

void testJPEG() {
	const char *src_file = "exif.jpg";

	printf("testJPEG (should throw exceptions) ...");

	// lossless transform - both perfect/non perfect
	testJPEGTransform(src_file);
	// cropping - both perfect/non perfect
	testJPEGCrop(src_file);

	printf("\tOK\n");
}
