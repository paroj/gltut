// ==========================================================
// FreeImagePlus Test Script
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

#ifndef TEST_FREEIMAGEPLUS_API_H
#define TEST_FREEIMAGEPLUS_API_H

#include "../FreeImagePlus.h"
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#include <iostream>

// --------------------------------------------------------------------------
// Memory IO test scripts

/// Test saving to a memory stream
void testSaveMemIO(const char *lpszPathName);
/// Test loading from a buffer attached to a memory stream
void testLoadMemIO(const char *lpszPathName);
/// Test extracting a memory buffer from a memory stream
void testAcquireMemIO(const char *lpszPathName);
/// Test Loading / Saving from / to a memory stream using fipImage
void testImageMemIO(const char *lpszPathName);
/// Test the above functions
void testMemIO(const char *lpszPathName);

// --------------------------------------------------------------------------
// Multipage test scripts

BOOL testCloneMultiPage(const char *input, const char *output, int output_flag);
void testMultiPage(const char *lpszMultiPage);


#endif // TEST_FREEIMAGEPLUS_API_H
