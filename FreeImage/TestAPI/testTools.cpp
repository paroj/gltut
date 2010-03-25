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


// ----------------------------------------------------------

/** Create a Zone Plate test pattern.

  The circular zone plate has zero horizontal and vertical frequencies at the center. 
  Horizontal frequencies increase as you move horizontally, and vertical frequencies increase as you move vertically.
  These patterns are useful to:
  <ul>
  <li> evaluate image compression 
  <li> evaluate filter properties 
  <li> evaluate the quality of resampling algorithms 
  <li> adjust gamma correction - at the proper gamma setting, the møires should be minimized 
  </ul>
  Reference: 
  [1] Ken Turkowski, Open Source Repository. [Online] http://www.worldserver.com/turk/opensource/
*/
FIBITMAP* createZonePlateImage(unsigned width, unsigned height, int scale) {
	const double PI = 3.1415926535898;
	BYTE sinTab[256];

	FIBITMAP *dst;
	int i, j, x, y;
	int cX, cY, d;

	// allocate a 8-bit dib
	dst = FreeImage_Allocate(width, height, 8);
	if(!dst)
		return NULL;

	// build a greyscale palette
	RGBQUAD *pal = FreeImage_GetPalette(dst);
	for(i = 0; i < 256; i++) {
		pal[i].rgbRed = i;
		pal[i].rgbGreen = i;
		pal[i].rgbBlue = i;
	}

	// build the sinus table
	for(i = 0; i < 256; i++) {
		sinTab[i] = (BYTE)(127.5 * sin(PI * (i - 127.5) / 127.5) + 127.5);
	}

	cX = width / 2;
	cY = height / 2;
	
	// create a zone plate
	for(i = height, y = -cY; i--; y++) {
		BYTE *dst_bits = FreeImage_GetScanLine(dst, i);
		for (j = width, x = -cX; j--; x++) {
			d = ((x * x + y * y) * scale) >> 8;
			dst_bits[j] = sinTab[d & 0xFF];
		}
	}

	return dst;
}

