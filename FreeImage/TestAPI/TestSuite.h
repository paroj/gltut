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

#ifndef TEST_FREEIMAGE_API_H
#define TEST_FREEIMAGE_API_H

#include "FreeImage.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>

#if (defined(WIN32) || defined(__WIN32__))
#if (defined(_DEBUG))
#include <crtdbg.h>
#endif
#endif // WIN32


// Some useful tools
// ==========================================================
FIBITMAP* createZonePlateImage(unsigned width, unsigned height, int scale);

// Test plugins capabilities
// ==========================================================
void showPlugins();

// Image types test suite
// ==========================================================
void testAllocateCloneUnload(const char *lpszPathName);
BOOL testAllocateCloneUnloadType(FREE_IMAGE_TYPE image_type, unsigned width, unsigned height);
void testImageType(unsigned width, unsigned height);
void testImageTypeTIFF(unsigned width, unsigned height);

// IO test suite
// ==========================================================

void testMemIO(const char *lpszPathName);

// Multipage test suite
// ==========================================================

void testBuildMPage(char *src_filename, char *dst_filename, FREE_IMAGE_FORMAT dst_fif, unsigned bpp);
void testMPageCache(char *src_filename);

// JPEG test suite
// ==========================================================

void testJPEG();

// Channels test suite
// ==========================================================

void testImageChannels(unsigned width, unsigned height);


#endif // TEST_FREEIMAGE_API_H


