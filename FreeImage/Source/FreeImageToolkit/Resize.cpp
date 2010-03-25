// ==========================================================
// Upsampling / downsampling classes
//
// Design and implementation by
// - Hervé Drolon (drolon@infonie.fr)
// - Detlev Vendt (detlev.vendt@brillit.de)
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

/**
  Filter weights table.
  This class stores contribution information for an entire line (row or column).
*/
CWeightsTable::CWeightsTable(CGenericFilter *pFilter, DWORD uDstSize, DWORD uSrcSize) {
	DWORD u;
	double dWidth;
	double dFScale = 1.0;
	double dFilterWidth = pFilter->GetWidth();

	// scale factor
	double dScale = double(uDstSize) / double(uSrcSize);

	if(dScale < 1.0) {
		// minification
		dWidth = dFilterWidth / dScale; 
		dFScale = dScale; 
	} else {
		// magnification
		dWidth= dFilterWidth; 
	}

	// allocate a new line contributions structure
	//
	// window size is the number of sampled pixels
	m_WindowSize = 2 * (int)ceil(dWidth) + 1; 
	m_LineLength = uDstSize; 
	 // allocate list of contributions 
	m_WeightTable = (Contribution*)malloc(m_LineLength * sizeof(Contribution));
	for(u = 0 ; u < m_LineLength ; u++) {
		// allocate contributions for every pixel
		m_WeightTable[u].Weights = (double*)malloc(m_WindowSize * sizeof(double));
	}

	// offset for discrete to continuous coordinate conversion
	double dOffset = (0.5 / dScale) - 0.5;


	for(u = 0; u < m_LineLength; u++) {
		// scan through line of contributions
		double dCenter = (double)u / dScale + dOffset;   // reverse mapping
		// find the significant edge points that affect the pixel
		int iLeft = MAX (0, (int)floor (dCenter - dWidth)); 
		int iRight = MIN ((int)ceil (dCenter + dWidth), int(uSrcSize) - 1); 

		// cut edge points to fit in filter window in case of spill-off
		if((iRight - iLeft + 1) > int(m_WindowSize)) {
			if(iLeft < (int(uSrcSize) - 1 / 2)) {
				iLeft++; 
			} else {
				iRight--; 
			}
		}

		m_WeightTable[u].Left = iLeft; 
		m_WeightTable[u].Right = iRight;

		int iSrc = 0;
		double dTotalWeight = 0;  // zero sum of weights
		for(iSrc = iLeft; iSrc <= iRight; iSrc++) {
			// calculate weights
			double weight = dFScale * pFilter->Filter(dFScale * (dCenter - (double)iSrc));
			m_WeightTable[u].Weights[iSrc-iLeft] = weight;
			dTotalWeight += weight;
		}
		if((dTotalWeight > 0) && (dTotalWeight != 1)) {
			// normalize weight of neighbouring points
			for(iSrc = iLeft; iSrc <= iRight; iSrc++) {
				// normalize point
				m_WeightTable[u].Weights[iSrc-iLeft] /= dTotalWeight; 
			}
			// simplify the filter, discarding null weights at the right
			iSrc = iRight - iLeft;
			while(m_WeightTable[u].Weights[iSrc] == 0){
				m_WeightTable[u].Right--;
				iSrc--;
				if(m_WeightTable[u].Right == m_WeightTable[u].Left)
					break;
			}

		}
   } 
}

CWeightsTable::~CWeightsTable() {
	for(DWORD u = 0; u < m_LineLength; u++) {
		// free contributions for every pixel
		free(m_WeightTable[u].Weights);
	}
	// free list of pixels contributions
	free(m_WeightTable);
}

// ---------------------------------------------

/**
 CResizeEngine<br>
 This class performs filtered zoom. It scales an image to the desired dimensions with 
 any of the CGenericFilter derived filter class.<br>
 It works with 8-, 24- and 32-bit buffers.<br><br>

 <b>References</b> : <br>
 [1] Paul Heckbert, C code to zoom raster images up or down, with nice filtering. 
 UC Berkeley, August 1989. [online] http://www-2.cs.cmu.edu/afs/cs.cmu.edu/Web/People/ph/heckbert.html
 [2] Eran Yariv, Two Pass Scaling using Filters. The Code Project, December 1999. 
 [online] http://www.codeproject.com/bitmap/2_pass_scaling.asp

*/

FIBITMAP* CResizeEngine::scale(FIBITMAP *src, unsigned dst_width, unsigned dst_height) { 
	DWORD src_width  = FreeImage_GetWidth(src); 
	DWORD src_height = FreeImage_GetHeight(src);

	unsigned redMask	= FreeImage_GetRedMask(src);
	unsigned greenMask	= FreeImage_GetGreenMask(src);
	unsigned blueMask	= FreeImage_GetBlueMask(src);

	unsigned bpp = FreeImage_GetBPP(src);
	if(bpp == 1) {
		// convert output to 8-bit
		bpp = 8;
	}

	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(src);

	// allocate the dst image
	FIBITMAP *dst = FreeImage_AllocateT(image_type, dst_width, dst_height, bpp, redMask, greenMask, blueMask);
	if(!dst) return NULL;
	
	if(bpp == 8) {
		if(FreeImage_GetColorType(src) == FIC_MINISWHITE) {
			// build an inverted greyscale palette
			RGBQUAD *dst_pal = FreeImage_GetPalette(dst);
			for(int i = 0; i < 256; i++) {
				dst_pal[i].rgbRed = dst_pal[i].rgbGreen =
					dst_pal[i].rgbBlue = (BYTE)(255 - i);
			}
		} else {
			// build a greyscale palette
			RGBQUAD *dst_pal = FreeImage_GetPalette(dst);
			for(int i = 0; i < 256; i++) {
				dst_pal[i].rgbRed = dst_pal[i].rgbGreen =
					dst_pal[i].rgbBlue = (BYTE)i;
			}
		}
	}

	// decide which filtering order (xy or yx) is faster for this mapping by
	// counting convolution multiplies

	if(dst_width*src_height <= dst_height*src_width) {
		// xy filtering
		// -------------

		// allocate a temporary image
		FIBITMAP *tmp = FreeImage_AllocateT(image_type, dst_width, src_height, bpp, redMask, greenMask, blueMask);
		if(!tmp) {
			FreeImage_Unload(dst);
			return NULL;
		}

		// scale source image horizontally into temporary image
		horizontalFilter(src, src_width, src_height, tmp, dst_width, src_height);

		// scale temporary image vertically into result image    
		verticalFilter(tmp, dst_width, src_height, dst, dst_width, dst_height);

		// free temporary image
		FreeImage_Unload(tmp);

	} else {
		// yx filtering
		// -------------

		// allocate a temporary image
		FIBITMAP *tmp = FreeImage_AllocateT(image_type, src_width, dst_height, bpp, redMask, greenMask, blueMask);
		if(!tmp) {
			FreeImage_Unload(dst);
			return NULL;
		}

		// scale source image vertically into temporary image
		verticalFilter(src, src_width, src_height, tmp, src_width, dst_height);

		// scale temporary image horizontally into result image    
		horizontalFilter(tmp, src_width, dst_height, dst, dst_width, dst_height);

		// free temporary image
		FreeImage_Unload(tmp);
	}

	return dst;
} 


/// Performs horizontal image filtering
void CResizeEngine::horizontalFilter(FIBITMAP *src, unsigned src_width, unsigned src_height, FIBITMAP *dst, unsigned dst_width, unsigned dst_height) { 
	if(dst_width == src_width) {
		// no scaling required, just copy
		switch(FreeImage_GetBPP(src)) {
			case 1:
			{
				if(FreeImage_GetBPP(dst) != 8) break;
				for(unsigned y = 0; y < dst_height; y++) {
					// convert each row 
					BYTE *src_bits = FreeImage_GetScanLine(src, y);
					BYTE *dst_bits = FreeImage_GetScanLine(dst, y);
					FreeImage_ConvertLine1To8(dst_bits, src_bits, dst_width);
				}
			}
			break;

			default:
			{
				BYTE *src_bits = FreeImage_GetBits(src);
				BYTE *dst_bits = FreeImage_GetBits(dst);
				memcpy(dst_bits, src_bits, dst_height * FreeImage_GetPitch(dst));
			}
			break;
		}
	}
	else {
		unsigned index;	// pixel index

		// allocate and calculate the contributions
		CWeightsTable weightsTable(m_pFilter, dst_width, src_width); 
		
		// step through rows
		switch(FreeImage_GetImageType(src)) {
			case FIT_BITMAP:
			{
				switch(FreeImage_GetBPP(src)) {
					case 1:
					{
						// scale and convert to 8-bit
						if(FreeImage_GetBPP(dst) != 8) break;

						for(unsigned y = 0; y < dst_height; y++) {
							// scale each row 
							BYTE *src_bits = FreeImage_GetScanLine(src, y);
							BYTE *dst_bits = FreeImage_GetScanLine(dst, y);

							for(unsigned x = 0; x < dst_width; x++) {
								// loop through row
								double value = 0;
								int iLeft = weightsTable.getLeftBoundary(x);    // retrieve left boundary
								int iRight = weightsTable.getRightBoundary(x);  // retrieve right boundary

								for(int i = iLeft; i <= iRight; i++) {
									// scan between boundaries
									// accumulate weighted effect of each neighboring pixel
									double weight = weightsTable.getWeight(x, i-iLeft);
									
									BYTE pixel = (src_bits[i >> 3] & (0x80 >> (i & 0x07))) != 0;
									value += (weight * (double)pixel);
								} 
								value *= 255;

								// clamp and place result in destination pixel
								dst_bits[x] = (BYTE)MIN(MAX((int)0, (int)(value + 0.5)), (int)255);
							} 
						}
					}
					break;

					case 8:
					case 24:
					case 32:
					{
						// Calculate the number of bytes per pixel (1 for 8-bit, 3 for 24-bit or 4 for 32-bit)
						unsigned bytespp = FreeImage_GetLine(src) / FreeImage_GetWidth(src);

						for(unsigned y = 0; y < dst_height; y++) {
							// scale each row 
							BYTE *src_bits = FreeImage_GetScanLine(src, y);
							BYTE *dst_bits = FreeImage_GetScanLine(dst, y);

							for(unsigned x = 0; x < dst_width; x++) {
								// loop through row
								double value[4] = {0, 0, 0, 0};					// 4 = 32bpp max
								int iLeft = weightsTable.getLeftBoundary(x);    // retrieve left boundary
								int iRight = weightsTable.getRightBoundary(x);  // retrieve right boundary

								for(int i = iLeft; i <= iRight; i++) {
									// scan between boundaries
									// accumulate weighted effect of each neighboring pixel
									double weight = weightsTable.getWeight(x, i-iLeft);
									
									index = i * bytespp;
									for (unsigned j = 0; j < bytespp; j++) {
										value[j] += (weight * (double)src_bits[index++]); 
									}
								} 

								// clamp and place result in destination pixel
								for (unsigned j = 0; j < bytespp; j++) {
									dst_bits[j] = (BYTE)MIN(MAX((int)0, (int)(value[j] + 0.5)), (int)255);
								}

								dst_bits += bytespp;
							} 
						}
					}
					break;
				}
			}
			break;

			case FIT_UINT16:
			case FIT_RGB16:
			case FIT_RGBA16:
			{
				// Calculate the number of words per pixel (1 for 16-bit, 3 for 48-bit or 4 for 64-bit)
				unsigned wordspp = (FreeImage_GetLine(src) / FreeImage_GetWidth(src)) / sizeof(WORD);

				for(unsigned y = 0; y < dst_height; y++) {
					// scale each row 
					WORD *src_bits = (WORD*)FreeImage_GetScanLine(src, y);
					WORD *dst_bits = (WORD*)FreeImage_GetScanLine(dst, y);

					for(unsigned x = 0; x < dst_width; x++) {
						// loop through row
						double value[4] = {0, 0, 0, 0};					// 4 = 64bpp max
						int iLeft = weightsTable.getLeftBoundary(x);    // retrieve left boundary
						int iRight = weightsTable.getRightBoundary(x);  // retrieve right boundary

						for(int i = iLeft; i <= iRight; i++) {
							// scan between boundaries
							// accumulate weighted effect of each neighboring pixel
							double weight = weightsTable.getWeight(x, i-iLeft);
							
							index = i * wordspp;
							for (unsigned j = 0; j < wordspp; j++) {
								value[j] += (weight * (double)src_bits[index++]); 
							}
						} 

						// clamp and place result in destination pixel
						for (unsigned j = 0; j < wordspp; j++) {
							dst_bits[j] = (WORD)MIN(MAX((int)0, (int)(value[j] + 0.5)), (int)0xFFFF);
						}

						dst_bits += wordspp;
					} 
				}
			}
			break;

			case FIT_FLOAT:
			case FIT_RGBF:
			case FIT_RGBAF:
			{
				// Calculate the number of floats per pixel (1 for 32-bit, 3 for 96-bit or 4 for 128-bit)
				unsigned floatspp = (FreeImage_GetLine(src) / FreeImage_GetWidth(src)) / sizeof(float);

				for(unsigned y = 0; y < dst_height; y++) {
					// scale each row 
					float *src_bits = (float*)FreeImage_GetScanLine(src, y);
					float *dst_bits = (float*)FreeImage_GetScanLine(dst, y);

					for(unsigned x = 0; x < dst_width; x++) {
						// loop through row
						double value[4] = {0, 0, 0, 0};					// 4 = 64bpp max
						int iLeft = weightsTable.getLeftBoundary(x);    // retrieve left boundary
						int iRight = weightsTable.getRightBoundary(x);  // retrieve right boundary

						for(int i = iLeft; i <= iRight; i++) {
							// scan between boundaries
							// accumulate weighted effect of each neighboring pixel
							double weight = weightsTable.getWeight(x, i-iLeft);
							
							index = i * floatspp;
							for (unsigned j = 0; j < floatspp; j++) {
								value[j] += (weight * (double)src_bits[index++]); 
							}
						} 

						// place result in destination pixel
						for (unsigned j = 0; j < floatspp; j++) {
							dst_bits[j] = (float)value[j];
						}

						dst_bits += floatspp;
					} 
				}
			}
			break;

		}
	}
} 

/// Performs vertical image filtering
void CResizeEngine::verticalFilter(FIBITMAP *src, unsigned src_width, unsigned src_height, FIBITMAP *dst, unsigned dst_width, unsigned dst_height) { 
	if(src_height == dst_height) {
		// no scaling required, just copy
		switch(FreeImage_GetBPP(src)) {
			case 1:
			{
				if(FreeImage_GetBPP(dst) != 8) break;
				for(unsigned y = 0; y < dst_height; y++) {
					// convert each row 
					BYTE *src_bits = FreeImage_GetScanLine(src, y);
					BYTE *dst_bits = FreeImage_GetScanLine(dst, y);
					FreeImage_ConvertLine1To8(dst_bits, src_bits, dst_width);
				}
			}
			break;

			default:
			{
				BYTE *src_bits = FreeImage_GetBits(src);
				BYTE *dst_bits = FreeImage_GetBits(dst);
				memcpy(dst_bits, src_bits, dst_height * FreeImage_GetPitch(dst));
			}
			break;
		}

	}
	else {
		unsigned index;	// pixel index

		// allocate and calculate the contributions
		CWeightsTable weightsTable(m_pFilter, dst_height, src_height); 


		// step through columns
		switch(FreeImage_GetImageType(src)) {
			case FIT_BITMAP:
			{
				switch(FreeImage_GetBPP(src)) {
					case 1:
					{
						// scale and convert to 8-bit
						if(FreeImage_GetBPP(dst) != 8) break;

						unsigned src_pitch = FreeImage_GetPitch(src);
						unsigned dst_pitch = FreeImage_GetPitch(dst);

						for(unsigned x = 0; x < dst_width; x++) {

							// work on column x in dst
							BYTE *dst_bits = FreeImage_GetBits(dst) + x;

							// scale each column
							for(unsigned y = 0; y < dst_height; y++) {
								// loop through column
								double value = 0;
								int iLeft = weightsTable.getLeftBoundary(y);    // retrieve left boundary
								int iRight = weightsTable.getRightBoundary(y);  // retrieve right boundary

								BYTE *src_bits = FreeImage_GetScanLine(src, iLeft);

								for(int i = iLeft; i <= iRight; i++) {
									// scan between boundaries
									// accumulate weighted effect of each neighboring pixel
									double weight = weightsTable.getWeight(y, i-iLeft);	
									
									BYTE pixel = (src_bits[x >> 3] & (0x80 >> (x & 0x07))) != 0;
									value += (weight * (double)pixel);

									src_bits += src_pitch;
								}
								value *= 255;

								// clamp and place result in destination pixel
								*dst_bits = (BYTE)MIN(MAX((int)0, (int)(value + 0.5)), (int)255);

								dst_bits += dst_pitch;
							}
						}
					}
					break;

					case 8:
					case 24:
					case 32:
					{
						// Calculate the number of bytes per pixel (1 for 8-bit, 3 for 24-bit or 4 for 32-bit)
						unsigned bytespp = FreeImage_GetLine(src) / FreeImage_GetWidth(src);

						unsigned src_pitch = FreeImage_GetPitch(src);
						unsigned dst_pitch = FreeImage_GetPitch(dst);

						for(unsigned x = 0; x < dst_width; x++) {
							index = x * bytespp;

							// work on column x in dst
							BYTE *dst_bits = FreeImage_GetBits(dst) + index;

							// scale each column
							for(unsigned y = 0; y < dst_height; y++) {
								// loop through column
								double value[4] = {0, 0, 0, 0};					// 4 = 32bpp max
								int iLeft = weightsTable.getLeftBoundary(y);    // retrieve left boundary
								int iRight = weightsTable.getRightBoundary(y);  // retrieve right boundary

								BYTE *src_bits = FreeImage_GetScanLine(src, iLeft) + index;

								for(int i = iLeft; i <= iRight; i++) {
									// scan between boundaries
									// accumulate weighted effect of each neighboring pixel
									double weight = weightsTable.getWeight(y, i-iLeft);							
									for (unsigned j = 0; j < bytespp; j++) {
										value[j] += (weight * (double)src_bits[j]);
									}

									src_bits += src_pitch;
								}

								// clamp and place result in destination pixel
								for (unsigned j = 0; j < bytespp; j++) {
									dst_bits[j] = (BYTE)MIN(MAX((int)0, (int)(value[j] + 0.5)), (int)255);
								}

								dst_bits += dst_pitch;
							}
						}
					}
					break;
				}
			}
			break;

			case FIT_UINT16:
			case FIT_RGB16:
			case FIT_RGBA16:
			{
				// Calculate the number of words per pixel (1 for 16-bit, 3 for 48-bit or 4 for 64-bit)
				unsigned wordspp = (FreeImage_GetLine(src) / FreeImage_GetWidth(src)) / sizeof(WORD);

				unsigned src_pitch = FreeImage_GetPitch(src) / sizeof(WORD);
				unsigned dst_pitch = FreeImage_GetPitch(dst) / sizeof(WORD);

				for(unsigned x = 0; x < dst_width; x++) {
					index = x * wordspp;

					// work on column x in dst
					WORD *dst_bits = (WORD*)FreeImage_GetBits(dst) + index;

					// scale each column
					for(unsigned y = 0; y < dst_height; y++) {
						// loop through column
						double value[4] = {0, 0, 0, 0};					// 4 = 64bpp max
						int iLeft = weightsTable.getLeftBoundary(y);    // retrieve left boundary
						int iRight = weightsTable.getRightBoundary(y);  // retrieve right boundary

						WORD *src_bits = (WORD*)FreeImage_GetScanLine(src, iLeft) + index;

						for(int i = iLeft; i <= iRight; i++) {
							// scan between boundaries
							// accumulate weighted effect of each neighboring pixel
							double weight = weightsTable.getWeight(y, i-iLeft);							
							for (unsigned j = 0; j < wordspp; j++) {
								value[j] += (weight * (double)src_bits[j]);
							}

							src_bits += src_pitch;
						}

						// clamp and place result in destination pixel
						for (unsigned j = 0; j < wordspp; j++) {
							dst_bits[j] = (WORD)MIN(MAX((int)0, (int)(value[j] + 0.5)), (int)0xFFFF);
						}

						dst_bits += dst_pitch;
					}
				}
			}
			break;

			case FIT_FLOAT:
			case FIT_RGBF:
			case FIT_RGBAF:
			{
				// Calculate the number of floats per pixel (1 for 32-bit, 3 for 96-bit or 4 for 128-bit)
				unsigned floatspp = (FreeImage_GetLine(src) / FreeImage_GetWidth(src)) / sizeof(float);

				unsigned src_pitch = FreeImage_GetPitch(src) / sizeof(float);
				unsigned dst_pitch = FreeImage_GetPitch(dst) / sizeof(float);

				for(unsigned x = 0; x < dst_width; x++) {
					index = x * floatspp;

					// work on column x in dst
					float *dst_bits = (float*)FreeImage_GetBits(dst) + index;

					// scale each column
					for(unsigned y = 0; y < dst_height; y++) {
						// loop through column
						double value[4] = {0, 0, 0, 0};					// 4 = 64bpp max
						int iLeft = weightsTable.getLeftBoundary(y);    // retrieve left boundary
						int iRight = weightsTable.getRightBoundary(y);  // retrieve right boundary

						float *src_bits = (float*)FreeImage_GetScanLine(src, iLeft) + index;

						for(int i = iLeft; i <= iRight; i++) {
							// scan between boundaries
							// accumulate weighted effect of each neighboring pixel
							double weight = weightsTable.getWeight(y, i-iLeft);							
							for (unsigned j = 0; j < floatspp; j++) {
								value[j] += (weight * (double)src_bits[j]);
							}

							src_bits += src_pitch;
						}

						// clamp and place result in destination pixel
						for (unsigned j = 0; j < floatspp; j++) {
							dst_bits[j] = (float)value[j];
						}

						dst_bits += dst_pitch;
					}
				}
			}
			break;

		}
	}
} 

