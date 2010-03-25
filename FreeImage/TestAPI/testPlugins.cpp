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

// Show plugins
// ----------------------------------------------------------
void showPlugins() {
	// print version & copyright infos

	printf("FreeImage version: %s\n\n%s\n\n", FreeImage_GetVersion(), FreeImage_GetCopyrightMessage());

	// print plugins info

	for (int j = FreeImage_GetFIFCount() - 1; j >= 0; --j)
		printf("bitmap type %d (%s): %s (%s)\n", j, FreeImage_GetFormatFromFIF((FREE_IMAGE_FORMAT)j), FreeImage_GetFIFDescription((FREE_IMAGE_FORMAT)j), FreeImage_GetFIFExtensionList((FREE_IMAGE_FORMAT)j));
	printf("\n");
}

