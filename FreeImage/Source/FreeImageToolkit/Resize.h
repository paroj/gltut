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

#ifndef _RESIZE_H_
#define _RESIZE_H_

#include "FreeImage.h"
#include "Utilities.h"
#include "Filters.h" 

/**
  Filter weights table.<br>
  This class stores contribution information for an entire line (row or column).
*/
class CWeightsTable
{
/** 
  Sampled filter weight table.<br>
  Contribution information for a single pixel
*/
typedef struct {
	/// Normalized weights of neighboring pixels
	double *Weights;
	/// Bounds of source pixels window
	int Left, Right;   
} Contribution;  

private:
	/// Row (or column) of contribution weights 
	Contribution *m_WeightTable;
	/// Filter window size (of affecting source pixels) 
	DWORD m_WindowSize;
	/// Length of line (no. of rows / cols) 
	DWORD m_LineLength;

public:
	/** 
	Constructor<br>
	Allocate and compute the weights table
	@param pFilter Filter used for upsampling or downsampling
	@param uLineSize Length (in pixels) of the destination line buffer
	@param uSrcSize Length (in pixels) of the source line buffer
	*/
	CWeightsTable(CGenericFilter *pFilter, DWORD uDstSize, DWORD uSrcSize);

	/**
	Destructor<br>
	Destroy the weights table
	*/
	~CWeightsTable();

	/** Retrieve a filter weight, given source and destination positions
	@param dst_pos Pixel position in destination line buffer
	@param src_pos Pixel position in source line buffer
	@return Returns the filter weight
	*/
	double getWeight(int dst_pos, int src_pos) {
		return m_WeightTable[dst_pos].Weights[src_pos];
	}

	/** Retrieve left boundary of source line buffer
	@param dst_pos Pixel position in destination line buffer
	@return Returns the left boundary of source line buffer
	*/
	int getLeftBoundary(int dst_pos) {
		return m_WeightTable[dst_pos].Left;
	}

	/** Retrieve right boundary of source line buffer
	@param dst_pos Pixel position in destination line buffer
	@return Returns the right boundary of source line buffer
	*/
	int getRightBoundary(int dst_pos) {
		return m_WeightTable[dst_pos].Right;
	}
};

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
class CResizeEngine
{
private:
	/// Pointer to the FIR / IIR filter
	CGenericFilter* m_pFilter;

public:

    /// Constructor
	CResizeEngine(CGenericFilter* filter):m_pFilter(filter) {}

    /// Destructor
	virtual ~CResizeEngine() {}

    /** Scale an image to the desired dimensions
	@param src Pointer to the source image
	@param dst_width Destination image width
	@param dst_height Destination image height
	@return Returns the scaled image if successful, returns NULL otherwise
	*/
	FIBITMAP* scale(FIBITMAP *src, unsigned dst_width, unsigned dst_height);

private:

    /// Performs horizontal image filtering
	void horizontalFilter(FIBITMAP *src, unsigned src_width, unsigned src_height, FIBITMAP *dst, unsigned dst_width, unsigned dst_height);

    /// Performs vertical image filtering
    void verticalFilter(FIBITMAP *src, unsigned src_width, unsigned src_height, FIBITMAP *dst, unsigned dst_width, unsigned dst_height);
};



#endif //   _RESIZE_H_
