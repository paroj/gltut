// ==========================================================
// Photoshop Loader
//
// Design and implementation by
// - Hervé Drolon (drolon@infonie.fr)
//
// Based on LGPL code created and published by http://sourceforge.net/projects/elynx/
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

#include "FreeImage.h"
#include "Utilities.h"
#include "PSDParser.h"

// PSD signature (= '8BPS')
#define PSD_SIGNATURE	0x38425053
// Image resource block signature (= '8BIM')
#define PSD_RESOURCE	0x3842494D

// PSD color modes
#define PSD_BITMAP			0
#define PSD_GRAYSCALE		1
#define PSD_INDEXED			2
#define PSD_RGB				3
#define PSD_CMYK			4
#define PSD_MULTICHANNEL	7
#define PSD_DUOTONE			8
#define PSD_LAB				9

// PSD compression schemes
#define PSD_COMPRESSION_NONE	0	// Raw data
#define PSD_COMPRESSION_RLE		1	// RLE compression (same as TIFF packed bits)

#define SAFE_DELETE_ARRAY(_p_) { if (NULL != (_p_)) { delete [] (_p_); (_p_) = NULL; } }

// --------------------------------------------------------------------------

static inline int 
psdGetValue(const BYTE * iprBuffer, const int iBytes) {
	int v = iprBuffer[0];
	for (int i=1; i<iBytes; ++i) {
		v = (v << 8) | iprBuffer[i];
	}
	return v;
}

// --------------------------------------------------------------------------

psdHeaderInfo::psdHeaderInfo() : _Channels(-1), _Height(-1), _Width(-1), _BitsPerPixel(-1), _ColourMode(-1) {
}

psdHeaderInfo::~psdHeaderInfo() {
}
	
bool psdHeaderInfo::Read(FreeImageIO *io, fi_handle handle) {
	psdHeader header;

	const int n = (int)io->read_proc(&header, sizeof(header), 1, handle);
	if(!n) {
		return false;
	}

	// check the signature
	int nSignature = psdGetValue(header.Signature, sizeof(header.Signature));
	if (PSD_SIGNATURE == nSignature) {
		// check the version
		int nVersion = psdGetValue( header.Version, sizeof(header.Version) );
		if (1 == nVersion) {
			// header.Reserved must be zero
			BYTE psd_reserved[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			if(memcmp(header.Reserved, psd_reserved, 6) != 0) {
				FreeImage_OutputMessageProc(FIF_PSD, "Warning: file header reserved member is not equal to zero");
			}
			// read the header
			_Channels = (short)psdGetValue( header.Channels, sizeof(header.Channels) );
			_Height = psdGetValue( header.Rows, sizeof(header.Rows) );
			_Width = psdGetValue( header.Columns, sizeof(header.Columns) );
			_BitsPerPixel = (short)psdGetValue( header.Depth, sizeof(header.Depth) );
			_ColourMode = (short)psdGetValue( header.Mode, sizeof(header.Mode) );

			return true;
		}
	}

	return false;
}

// --------------------------------------------------------------------------

psdColourModeData::psdColourModeData() : _Length(-1), _plColourData(NULL) {
}

psdColourModeData::~psdColourModeData() { 
	SAFE_DELETE_ARRAY(_plColourData); 
}
	
bool psdColourModeData::Read(FreeImageIO *io, fi_handle handle) {
	if (0 < _Length) { 
		SAFE_DELETE_ARRAY(_plColourData);
	}
	
	BYTE Length[4];
	io->read_proc(&Length, sizeof(Length), 1, handle);
	
	_Length = psdGetValue( Length, sizeof(_Length) );
	if (0 < _Length) {
		_plColourData = new BYTE[_Length];
		io->read_proc(_plColourData, _Length, 1, handle);
	}

	return true;
}
	
bool psdColourModeData::FillPalette(FIBITMAP *dib) {
	RGBQUAD *pal = FreeImage_GetPalette(dib);
	if(pal) {
		for (int i = 0; i < 256; i++) {
			pal[i].rgbRed	= _plColourData[i + 0*256];
			pal[i].rgbGreen = _plColourData[i + 1*256];
			pal[i].rgbBlue	= _plColourData[i + 2*256];
		}
		return true;
	}
	return false;
}

// --------------------------------------------------------------------------

psdImageResource::psdImageResource() : _plName (0) { 
	Reset(); 
}

psdImageResource::~psdImageResource() { 
	SAFE_DELETE_ARRAY(_plName);
}

void psdImageResource::Reset() {
	_Length = -1;
	memset( _OSType, '\0', sizeof(_OSType) );
	_ID = -1;
	SAFE_DELETE_ARRAY(_plName);
	_Size = -1;
}

// --------------------------------------------------------------------------

psdResolutionInfo::psdResolutionInfo() : _widthUnit(-1), _heightUnit(-1), _hRes(-1), _vRes(-1), _hResUnit(-1), _vResUnit(-1) {
}

psdResolutionInfo::~psdResolutionInfo() {
}
	
int psdResolutionInfo::Read(FreeImageIO *io, fi_handle handle) {
	BYTE IntValue[4], ShortValue[2];
	int nBytes=0, n;
	
	// Horizontal resolution in pixels per inch.
	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_hRes = (short)psdGetValue(ShortValue, sizeof(_hRes) );
	// 1=display horizontal resolution in pixels per inch; 2=display horizontal resolution in pixels per cm.
	n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
	nBytes += n * sizeof(IntValue);
	_hResUnit = psdGetValue(IntValue, sizeof(_hResUnit) );
	// Display width as 1=inches; 2=cm; 3=points; 4=picas; 5=columns.
	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_widthUnit = (short)psdGetValue(ShortValue, sizeof(_widthUnit) );
	// Vertical resolution in pixels per inch.
	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_vRes = (short)psdGetValue(ShortValue, sizeof(_vRes) );
	// 1=display vertical resolution in pixels per inch; 2=display vertical resolution in pixels per cm.
	n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
	nBytes += n * sizeof(IntValue);
	_vResUnit = psdGetValue(IntValue, sizeof(_vResUnit) );
	// Display height as 1=inches; 2=cm; 3=points; 4=picas; 5=columns.
	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_heightUnit = (short)psdGetValue(ShortValue, sizeof(_heightUnit) );
	
	return nBytes;
}

void psdResolutionInfo::GetResolutionInfo(unsigned &res_x, unsigned &res_y) {
	if(_hResUnit == 1) {
		// convert pixels / inch to pixel / m
		res_x = (unsigned) (_hRes / 0.0254000 + 0.5);
	} else if(_hResUnit == 2) {
		// convert pixels / cm to pixel / m
		res_x = (unsigned) (_hRes * 100.0 + 0.5);
	}
	if(_vResUnit == 1) {
		// convert pixels / inch to pixel / m
		res_y = (unsigned) (_vRes / 0.0254000 + 0.5);
	} else if(_vResUnit == 2) {
		// convert pixels / cm to pixel / m
		res_y = (unsigned) (_vRes * 100.0 + 0.5);
	}
}

// --------------------------------------------------------------------------

psdResolutionInfo_v2::psdResolutionInfo_v2() { 
	_Channels = _Rows = _Columns = _Depth = _Mode = -1; 
}

psdResolutionInfo_v2::~psdResolutionInfo_v2() {
}

int psdResolutionInfo_v2::Read(FreeImageIO *io, fi_handle handle) {
	BYTE ShortValue[2];
	int nBytes=0, n;
	
	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_Channels = (short)psdGetValue(ShortValue, sizeof(_Channels) );

	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_Rows = (short)psdGetValue(ShortValue, sizeof(_Rows) );
	
	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_Columns = (short)psdGetValue(ShortValue, sizeof(_Columns) );

	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_Depth = (short)psdGetValue(ShortValue, sizeof(_Depth) );

	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_Mode = (short)psdGetValue(ShortValue, sizeof(_Mode) );
	
	return nBytes;
}

// --------------------------------------------------------------------------

psdDisplayInfo::psdDisplayInfo() {
	_Opacity = _ColourSpace = -1;
	for (unsigned n = 0; n < 4; ++n) {
		_Colour[n] = 0;
	}
	_Kind = 0;
	_padding = '0';
}

psdDisplayInfo::~psdDisplayInfo() {
}
	
int psdDisplayInfo::Read(FreeImageIO *io, fi_handle handle) {
	BYTE ShortValue[2];
	int nBytes=0, n;
	
	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_ColourSpace = (short)psdGetValue(ShortValue, sizeof(_ColourSpace) );
	
	for (unsigned i = 0; i < 4; ++i) {
		n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
		nBytes += n * sizeof(ShortValue);
		_Colour[i] = (short)psdGetValue(ShortValue, sizeof(_Colour[i]) );
	}
	
	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_Opacity = (short)psdGetValue(ShortValue, sizeof(_Opacity) );
	assert( 0 <= _Opacity );
	assert( 100 >= _Opacity );
	
	BYTE c[1];
	n = (int)io->read_proc(&c, sizeof(c), 1, handle);
	nBytes += n * sizeof(c);
	_Kind = (BYTE)psdGetValue(c, sizeof(c));
	
	n = (int)io->read_proc(&c, sizeof(c), 1, handle);
	nBytes += n * sizeof(c);
	_padding = (BYTE)psdGetValue(c, sizeof(c));
	assert( 0 == _padding );
	
	return nBytes;
}

// --------------------------------------------------------------------------

psdThumbnail::psdThumbnail() : 
_Format(-1), _Width(-1), _Height(-1), _WidthBytes(-1), _Size(-1), _CompressedSize(-1), _BitPerPixel(-1), _Planes(-1), _plData(NULL) {
}

psdThumbnail::~psdThumbnail() { 
	SAFE_DELETE_ARRAY(_plData); 
}

int psdThumbnail::Read(FreeImageIO *io, fi_handle handle, int iTotalData, bool isBGR) {
	BYTE c[1], ShortValue[2], IntValue[4];
	int nBytes=0, n;
	
	n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
	nBytes += n * sizeof(IntValue);
	_Format = psdGetValue(IntValue, sizeof(_Format) );
	
	n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
	nBytes += n * sizeof(IntValue);
	_Width = psdGetValue(IntValue, sizeof(_Width) );
	
	n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
	nBytes += n * sizeof(IntValue);
	_Height = psdGetValue(IntValue, sizeof(_Height) );
	
	n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
	nBytes += n * sizeof(IntValue);
	_WidthBytes = psdGetValue(IntValue, sizeof(_WidthBytes) );

	n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
	nBytes += n * sizeof(IntValue);
	_Size = psdGetValue(IntValue, sizeof(_Size) );

	n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
	nBytes += n * sizeof(IntValue);
	_CompressedSize = psdGetValue(IntValue, sizeof(_CompressedSize) );

	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_BitPerPixel = (short)psdGetValue(ShortValue, sizeof(_BitPerPixel) );

	n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
	nBytes += n * sizeof(ShortValue);
	_Planes = (short)psdGetValue(ShortValue, sizeof(_Planes) );

	_plData = new BYTE[iTotalData];
	  
	if (isBGR) {
		// In BGR format
		for (int i=0; i<iTotalData; i+=3 ) {
			n = (int)io->read_proc(&c, sizeof(BYTE), 1, handle);
			nBytes += n * sizeof(BYTE);
			_plData[i+2] = (BYTE)psdGetValue(c, sizeof(BYTE) );

			n = (int)io->read_proc(&c, sizeof(BYTE), 1, handle);
			nBytes += n * sizeof(BYTE);
			_plData[i+1] = (BYTE)psdGetValue(c, sizeof(BYTE) );

			n = (int)io->read_proc(&c, sizeof(BYTE), 1, handle);
			nBytes += n * sizeof(BYTE);
			_plData[i+0] = (BYTE)psdGetValue(c, sizeof(BYTE) );
		}
	} else {
		// In RGB format										
		for (int i=0; i<iTotalData; ++i) {
			n = (int)io->read_proc(&c, sizeof(BYTE), 1, handle);
			nBytes += n * sizeof(BYTE);
			_plData[i] = (BYTE)psdGetValue(c, sizeof(BYTE) );
		}
	}

	return nBytes;
}

//---------------------------------------------------------------------------

psdICCProfile::psdICCProfile() : _ProfileSize(0), _ProfileData(NULL) {
}

psdICCProfile::~psdICCProfile() {
	SAFE_DELETE_ARRAY(_ProfileData);
}

int psdICCProfile::Read(FreeImageIO *io, fi_handle handle, int size) {
	int nBytes = 0, n;
	
	SAFE_DELETE_ARRAY(_ProfileData);
	_ProfileData = new BYTE[size];
	if(NULL != _ProfileData) {
		n = (int)io->read_proc(_ProfileData, 1, size, handle);
		_ProfileSize = size;
		nBytes += n * sizeof(BYTE);
	}

	return nBytes;
}

//---------------------------------------------------------------------------

static inline int d2i(double value) { 
	return (int)floor(value + 0.5); 
}

/**
CMYK to RGB 8-bit conversion
*/
static void CMYKToRGB8(float iC, float iM, float iY, float iK, RGBTRIPLE *rgb) {
  int r = d2i( ( 1.f - (iC *(1.f - iK) + iK ) ) * 255.f );
  int g = d2i( ( 1.f - (iM *(1.f - iK) + iK ) ) * 255.f );
  int b = d2i( ( 1.f - (iY *(1.f - iK) + iK ) ) * 255.f );

  if (r < 0) r = 0; else if (r > 255) r = 255;
  if (g < 0) g = 0; else if (g > 255) g = 255;
  if (b < 0) b = 0; else if (b > 255) b = 255;

  rgb->rgbtRed   = (BYTE)r;
  rgb->rgbtGreen = (BYTE)g;
  rgb->rgbtBlue  = (BYTE)b;
}

/**
CMYK to RGB 16-bit conversion
*/
static void CMYKToRGB16(float iC, float iM, float iY, float iK, FIRGB16 *rgb) {
  int r = d2i( ( 1.f - (iC *(1.f - iK) + iK ) ) * 65535.f );
  int g = d2i( ( 1.f - (iM *(1.f - iK) + iK ) ) * 65535.f );
  int b = d2i( ( 1.f - (iY *(1.f - iK) + iK ) ) * 65535.f );

  if (r < 0) r = 0; else if (r > 65535) r = 65535;
  if (g < 0) g = 0; else if (g > 65535) g = 65535;
  if (b < 0) b = 0; else if (b > 65535) b = 65535;

  rgb->red   = (WORD)r;
  rgb->green = (WORD)g;
  rgb->blue  = (WORD)b;
}

#define PSD_CLAMP(v, min, max) ((v < min) ? min : (v > max) ? max : v)

/**
CIELab -> XYZ conversion from http://www.easyrgb.com/
*/
static void CIELabToXYZ(float L, float a, float b, float *X, float *Y, float *Z) {
	float pow_3;
	
	// CIELab -> XYZ conversion 
	// ------------------------
	float var_Y = (L + 16.F ) / 116.F;
	float var_X = a / 500.F + var_Y;
	float var_Z = var_Y - b / 200.F;

	pow_3 = powf(var_Y, 3);
	if(pow_3 > 0.008856F) {
		var_Y = pow_3;
	} else {
		var_Y = ( var_Y - 16.F / 116.F ) / 7.787F;
	}
	pow_3 = powf(var_X, 3);
	if(pow_3 > 0.008856F) {
		var_X = pow_3;
	} else {
		var_X = ( var_X - 16.F / 116.F ) / 7.787F;
	}
	pow_3 = powf(var_Z, 3);
	if(pow_3 > 0.008856F) {
		var_Z = pow_3;
	} else {
		var_Z = ( var_Z - 16.F / 116.F ) / 7.787F;
	}

	static const float ref_X =  95.047F;
	static const float ref_Y = 100.000F;
	static const float ref_Z = 108.883F;

	*X = ref_X * var_X;	// ref_X = 95.047 (Observer= 2°, Illuminant= D65)
	*Y = ref_Y * var_Y;	// ref_Y = 100.000
	*Z = ref_Z * var_Z;	// ref_Z = 108.883
}

/**
XYZ -> RGB conversion from http://www.easyrgb.com/
*/
static void XYZToRGB(float X, float Y, float Z, float *R, float *G, float *B) {
	float var_X = X / 100;        //X from 0 to  95.047      (Observer = 2°, Illuminant = D65)
	float var_Y = Y / 100;        //Y from 0 to 100.000
	float var_Z = Z / 100;        //Z from 0 to 108.883

	float var_R = var_X *  3.2406F + var_Y * -1.5372F + var_Z * -0.4986F;
	float var_G = var_X * -0.9689F + var_Y *  1.8758F + var_Z *  0.0415F;
	float var_B = var_X *  0.0557F + var_Y * -0.2040F + var_Z *  1.0570F;

	float exponent = 1.F / 2.4F;

	if(var_R > 0.0031308F) {
		var_R = 1.055F * powf(var_R, exponent) - 0.055F;
	} else {
		var_R = 12.92F * var_R;
	}
	if(var_G > 0.0031308F) {
		var_G = 1.055F * powf(var_G, exponent) - 0.055F;
	} else {
		var_G = 12.92F * var_G;
	}
	if(var_B > 0.0031308F) {
		var_B = 1.055F * powf(var_B, exponent) - 0.055F;
	} else {
		var_B = 12.92F * var_B;
	}

	*R = var_R;
	*G = var_G;
	*B = var_B;
}

static void CIELabToRGB16(float L, float a, float b, FIRGB16 *rgb) {
	float X, Y, Z;
	float R, G, B;
	const float max_value = 65535.0F;

	CIELabToXYZ(L, a, b, &X, &Y, &Z);
	XYZToRGB(X, Y, Z, &R, &G, &B);
	rgb->red   = (WORD)PSD_CLAMP(R * max_value, 0, max_value);
	rgb->green = (WORD)PSD_CLAMP(G * max_value, 0, max_value);
	rgb->blue  = (WORD)PSD_CLAMP(B * max_value, 0, max_value);	
}

static void CIELabToRGB8(float L, float a, float b, RGBTRIPLE *rgb) {
	float X, Y, Z;
	float R, G, B;
	const float max_value = 255.0F;

	CIELabToXYZ(L, a, b, &X, &Y, &Z);
	XYZToRGB(X, Y, Z, &R, &G, &B);
	rgb->rgbtRed   = (BYTE)PSD_CLAMP(R * max_value, 0, max_value);
	rgb->rgbtGreen = (BYTE)PSD_CLAMP(G * max_value, 0, max_value);
	rgb->rgbtBlue  = (BYTE)PSD_CLAMP(B * max_value, 0, max_value);	
}

//---------------------------------------------------------------------------

psdParser::psdParser() {
	_bThumbnailFilled = false;
	_bDisplayInfoFilled = false;
	_bResolutionInfoFilled = false;
	_bResolutionInfoFilled_v2 = false;
	_bCopyright = false;
	_GlobalAngle = 30;
	_ColourCount = -1;
	_TransparentIndex = -1;
}

psdParser::~psdParser() {
}

bool psdParser::ReadLayerAndMaskInfoSection(FreeImageIO *io, fi_handle handle)	{
	bool bSuccess = false;
	
	BYTE DataLength[4];
	int nBytes = 0;
	int n = (int)io->read_proc(&DataLength, sizeof(DataLength), 1, handle);
	int nTotalBytes = psdGetValue( DataLength, sizeof(DataLength) );
	
	BYTE data[1];
	while( n && ( nBytes < nTotalBytes ) ) {
		data[0] = '\0';
		n = (int)io->read_proc(&data, sizeof(data), 1, handle);
		nBytes += n * sizeof(data);
	}
	
	assert( nBytes == nTotalBytes );
	if ( nBytes == nTotalBytes ) {
		bSuccess = true;
	}
	
	return bSuccess;
}

bool psdParser::ReadImageResource(FreeImageIO *io, fi_handle handle) {
	psdImageResource oResource;
	bool bSuccess = false;
	
	BYTE Length[4];
	int n = (int)io->read_proc(&Length, sizeof(Length), 1, handle);
	
	oResource._Length = psdGetValue( Length, sizeof(oResource._Length) );
	
	int nBytes = 0;
	int nTotalBytes = oResource._Length;
	
	while(nBytes < nTotalBytes) {
		n = 0;
		oResource.Reset();
		
		n = (int)io->read_proc(&oResource._OSType, sizeof(oResource._OSType), 1, handle);
		nBytes += n * sizeof(oResource._OSType);
		assert( 0 == (nBytes % 2) );
		
		int nOSType = psdGetValue((BYTE*)&oResource._OSType, sizeof(oResource._OSType));

		if ( PSD_RESOURCE == nOSType ) {
			BYTE ID[2];
			n = (int)io->read_proc(&ID, sizeof(ID), 1, handle);
			nBytes += n * sizeof(ID);
			
			oResource._ID = (short)psdGetValue( ID, sizeof(ID) );
			
			BYTE SizeOfName;
			n = (int)io->read_proc(&SizeOfName, sizeof(SizeOfName), 1, handle);
			nBytes += n * sizeof(SizeOfName);
			
			int nSizeOfName = psdGetValue( &SizeOfName, sizeof(SizeOfName) );
			if ( 0 < nSizeOfName ) {
				oResource._plName = new BYTE[nSizeOfName];
				n = (int)io->read_proc(oResource._plName, nSizeOfName, 1, handle);
				nBytes += n * nSizeOfName;
			}
			
			if ( 0 == (nSizeOfName % 2) ) {
				n = (int)io->read_proc(&SizeOfName, sizeof(SizeOfName), 1, handle);
				nBytes += n * sizeof(SizeOfName);
			}
			
			BYTE Size[4];
			n = (int)io->read_proc(&Size, sizeof(Size), 1, handle);
			nBytes += n * sizeof(Size);
			
			oResource._Size = psdGetValue( Size, sizeof(oResource._Size) );
			
			if ( 0 != (oResource._Size % 2) ) {
				// resource data must be even
				oResource._Size++;
			}
			if ( 0 < oResource._Size ) {
				BYTE IntValue[4];
				BYTE ShortValue[2];
				
				switch( oResource._ID ) {
					case 1000:
						// Obsolete - Photoshop 2.0
						_bResolutionInfoFilled_v2 = true;
						nBytes += _resolutionInfo_v2.Read(io, handle);
						break;
					
					// ResolutionInfo structure
					case 1005:
						_bResolutionInfoFilled = true;
						nBytes += _resolutionInfo.Read(io, handle);
						break;
						
					// DisplayInfo structure
					case 1007:
						_bDisplayInfoFilled = true;
						nBytes += _displayInfo.Read(io, handle);
						break;
						
					// (Photoshop 4.0) Copyright flag
					// Boolean indicating whether image is copyrighted. Can be set via Property suite or by user in File Info...
					case 1034:
						n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
						nBytes += n * sizeof(ShortValue);
						_bCopyright = (1 == psdGetValue(ShortValue, sizeof(ShortValue)));
						break;
						
					// (Photoshop 4.0) Thumbnail resource for Photoshop 4.0 only
					case 1033:
					// (Photoshop 5.0) Thumbnail resource (supersedes resource 1033)
					case 1036:
					{
						_bThumbnailFilled = true;
						bool bBGR = (1033==oResource._ID);
						int nTotalData = oResource._Size - 28; // header
						nBytes += _thumbnail.Read(io, handle, nTotalData, bBGR);
						break;
					}
					
					// (Photoshop 5.0) Global Angle
					// 4 bytes that contain an integer between 0 and 359, which is the global
					// lighting angle for effects layer. If not present, assumed to be 30.
					case 1037:
						n = (int)io->read_proc(&IntValue, sizeof(IntValue), 1, handle);
						nBytes += n * sizeof(IntValue);
						_GlobalAngle = psdGetValue(IntValue, sizeof(_GlobalAngle) );
						break;

					// ICC profile
					case 1039:
						nBytes += _iccProfile.Read(io, handle, oResource._Size);
						break;

					// (Photoshop 6.0) Indexed Color Table Count
					// 2 bytes for the number of colors in table that are actually defined
					case 1046:
						n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
						nBytes += n * sizeof(ShortValue);
						_ColourCount = (short)psdGetValue(ShortValue, sizeof(ShortValue) );
						break;
						
					// (Photoshop 6.0) Transparency Index.
					// 2 bytes for the index of transparent color, if any.
					case 1047:
						n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
						nBytes += n * sizeof(ShortValue);
						_TransparentIndex = (short)psdGetValue(ShortValue, sizeof(ShortValue) );
						break;
						
					default:
					{
						// skip resource
						BYTE c[1];
						for(int i=0; i<oResource._Size; ++i) {
							n = (int)io->read_proc(&c, sizeof(c), 1, handle);
							nBytes += n * sizeof(c);
						}
					}
					break;
				}
			}
		}
  }
  
  assert(nBytes == nTotalBytes);
  if (nBytes == nTotalBytes) {
	  bSuccess = true;
  }
  
  return bSuccess;
  
} 

FIBITMAP* psdParser::ProcessBuffer(BYTE * iprData) {
	assert(NULL != iprData);
	
	FIBITMAP *Bitmap = NULL;
	int nHeight = _headerInfo._Height;
	int nWidth  = _headerInfo._Width;
	unsigned bytes = _headerInfo._BitsPerPixel / 8;
	int nChannels = _headerInfo._Channels;
	
	switch (_headerInfo._ColourMode) {
		case PSD_BITMAP: // Bitmap
		{
			// monochrome 1-bit
			FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 1);
			if (NULL != dib) {
				// fill the palette
				RGBQUAD *pal = FreeImage_GetPalette(dib);
				if(pal) {
					for (int i = 0; i < 2; i++) {
						BYTE val = i ? 0x0 : 0xFF;
						pal[i].rgbRed   = val;
						pal[i].rgbGreen = val;
						pal[i].rgbBlue  = val;
					}
				}
				// copy buffer
				BYTE *src_bits = (BYTE*)iprData;
				BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
				unsigned src_pitch = (nWidth + 7) / 8;
				unsigned dst_pitch = FreeImage_GetPitch(dib);
				for(int y = 0; y < nHeight; y++) {
					memcpy(dst_bits, src_bits, src_pitch);
					src_bits += src_pitch;
					dst_bits -= dst_pitch;
				}
			}
			Bitmap = dib;
		}
		break;

		case PSD_GRAYSCALE: // Grayscale
		case PSD_DUOTONE: // Duotone
		case PSD_RGB: // RGB
		{
			// 16-bit / channel
			// --------------------------------------------------------------
			if (16 == _headerInfo._BitsPerPixel) {
				if (1 == nChannels) {
					// L 16-bit
					FIBITMAP *dib = FreeImage_AllocateT(FIT_UINT16, nWidth, nHeight);
					if (NULL != dib) {
						// just copy buffer
						BYTE *src_bits = (BYTE*)iprData;
						BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned src_pitch = nChannels * nWidth * bytes;
						unsigned dst_pitch = FreeImage_GetPitch(dib);
						for(int y = 0; y < nHeight; y++) {
							memcpy(dst_bits, src_bits, src_pitch);
							src_bits += src_pitch;
							dst_bits -= dst_pitch;
						}
						Bitmap = dib;
					}
				}
				else if (2 == nChannels) {
					// LA 16-bit : convert to RGBA 16-bit
					FIBITMAP *dib = FreeImage_AllocateT(FIT_RGBA16, nWidth, nHeight);
					if (NULL != dib) {
						unsigned short *src_bits = (unsigned short*)iprData;
						FIRGBA16 *dst_bits = (FIRGBA16*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned pitch = FreeImage_GetPitch(dib) / sizeof(FIRGBA16);
						for(int y = 0; y < nHeight; y++) {
							for(int x = 0; x < nWidth; x++) {
								dst_bits[x].red   = src_bits[0];
								dst_bits[x].green = src_bits[0];
								dst_bits[x].blue  = src_bits[0];
								dst_bits[x].alpha = src_bits[1];
								src_bits += nChannels;
							}
							dst_bits -= pitch;
						}
						Bitmap = dib;
					}
				}
				else if (3 == nChannels) {
					// RGB 16-bit
					FIBITMAP *dib = FreeImage_AllocateT(FIT_RGB16, nWidth, nHeight);
					if (NULL != dib) {
						// just copy buffer
						BYTE *src_bits = (BYTE*)iprData;
						BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned src_pitch = nChannels * nWidth * bytes;
						unsigned dst_pitch = FreeImage_GetPitch(dib);
						for(int y = 0; y < nHeight; y++) {
							memcpy(dst_bits, src_bits, src_pitch);
							src_bits += src_pitch;
							dst_bits -= dst_pitch;
						}
						Bitmap = dib;
					}
				}
				else if (4 == nChannels) {
					// RGBA 16-bit
					FIBITMAP *dib = FreeImage_AllocateT(FIT_RGBA16, nWidth, nHeight);
					if (NULL != dib) {
						// just copy buffer
						BYTE *src_bits = (BYTE*)iprData;
						BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned src_pitch = nChannels * nWidth * bytes;
						unsigned dst_pitch = FreeImage_GetPitch(dib);
						for(int y = 0; y < nHeight; y++) {
							memcpy(dst_bits, src_bits, src_pitch);
							src_bits += src_pitch;
							dst_bits -= dst_pitch;
						}
						Bitmap = dib;
					}
				}
			}
			// 8-bit / channel
			// --------------------------------------------------------------
			else if (8 == _headerInfo._BitsPerPixel) {
				if (1 == nChannels) {
					// L 8-bit
					FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 8);
					if (NULL != dib) {
						// build a greyscale palette
						RGBQUAD *pal = FreeImage_GetPalette(dib);
						for (int i = 0; i < 256; i++) {
							pal[i].rgbRed	= (BYTE)i;
							pal[i].rgbGreen = (BYTE)i;
							pal[i].rgbBlue	= (BYTE)i;
						}
						// just copy buffer
						BYTE *src_bits = (BYTE*)iprData;
						BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned src_pitch = nChannels * nWidth * bytes;
						unsigned dst_pitch = FreeImage_GetPitch(dib);
						for(int y = 0; y < nHeight; y++) {
							memcpy(dst_bits, src_bits, src_pitch);
							src_bits += src_pitch;
							dst_bits -= dst_pitch;
						}
						Bitmap = dib;
					}
				}
				else if (2 == nChannels) {
					// LA 8-bit : convert to RGBA 32-bit
					FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 32);
					if (NULL != dib) {
						BYTE *src_bits = (BYTE*)iprData;
						BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned src_pitch = nChannels * nWidth * bytes;
						unsigned dst_pitch = FreeImage_GetPitch(dib);
						for(int y = 0; y < nHeight; y++) {
							BYTE *p_src = src_bits;
							BYTE *p_dst = dst_bits;
							for(int x = 0; x < nWidth; x++) {
								p_dst[FI_RGBA_RED]   = p_src[0];
								p_dst[FI_RGBA_GREEN] = p_src[0];
								p_dst[FI_RGBA_BLUE]  = p_src[0];
								p_dst[FI_RGBA_ALPHA] = p_src[1];
								p_src += nChannels;
								p_dst += 4;
							}
							src_bits += src_pitch;
							dst_bits -= dst_pitch;
						}
						Bitmap = dib;
					}
				}
				else if (3 == nChannels) {
					// RGB 8-bit
					FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 24);
					if (NULL != dib) {
						// just copy buffer
						BYTE *src_bits = (BYTE*)iprData;
						BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned src_pitch = nChannels * nWidth * bytes;
						unsigned dst_pitch = FreeImage_GetPitch(dib);
						for(int y = 0; y < nHeight; y++) {
							BYTE *p_src = src_bits;
							BYTE *p_dst = dst_bits;
							for(int x = 0; x < nWidth; x++) {
								p_dst[FI_RGBA_RED]   = p_src[0];
								p_dst[FI_RGBA_GREEN] = p_src[1];
								p_dst[FI_RGBA_BLUE]  = p_src[2];
								p_src += nChannels;
								p_dst += nChannels;
							}
							src_bits += src_pitch;
							dst_bits -= dst_pitch;
						}
						Bitmap = dib;
					}
				}
				else if (4 == nChannels) {
					// RGBA 8-bit
					FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 32);
					if (NULL != dib) {
						// just copy buffer
						BYTE *src_bits = (BYTE*)iprData;
						BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned src_pitch = nChannels * nWidth * bytes;
						unsigned dst_pitch = FreeImage_GetPitch(dib);
						for(int y = 0; y < nHeight; y++) {
							BYTE *p_src = src_bits;
							BYTE *p_dst = dst_bits;
							for(int x = 0; x < nWidth; x++) {
								p_dst[FI_RGBA_RED]   = p_src[0];
								p_dst[FI_RGBA_GREEN] = p_src[1];
								p_dst[FI_RGBA_BLUE]  = p_src[2];
								p_dst[FI_RGBA_ALPHA] = p_src[3];
								p_src += nChannels;
								p_dst += nChannels;
							}
							src_bits += src_pitch;
							dst_bits -= dst_pitch;
						}
						Bitmap = dib;
					}
				}
				else {
					assert(false);// do nothing
				}
			}
			// 32-bit / channel => undocumented HDR 
			// --------------------------------------------------------------
			else if (32 == _headerInfo._BitsPerPixel) {
				if (3 == nChannels) {
					// RGBF 32-bit
					FIBITMAP *dib = FreeImage_AllocateT(FIT_RGBF, nWidth, nHeight);
					if (NULL != dib) {
						// just copy buffer
						BYTE *src_bits = (BYTE*)iprData;
						BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
						unsigned src_pitch = nChannels * nWidth * bytes;
						unsigned dst_pitch = FreeImage_GetPitch(dib);
						for(int y = 0; y < nHeight; y++) {
							memcpy(dst_bits, src_bits, src_pitch);
							src_bits += src_pitch;
							dst_bits -= dst_pitch;
						}
						Bitmap = dib;
					}
				}
			}
		}
		break;
		
		case PSD_INDEXED: // Indexed
		{
			// iprData holds the indices of loop through the palette 
			assert(0 != _colourModeData._plColourData);
			assert(768 == _colourModeData._Length);
			assert(0 < _ColourCount);

			// grey or palettised 8 bits
			FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 8);
			if (NULL != dib) {
				// get the palette
				if (_colourModeData.FillPalette(dib)) {
					// copy buffer
					BYTE *src_bits = (BYTE*)iprData;
					BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
					unsigned src_pitch = nChannels * nWidth * bytes;
					unsigned dst_pitch = FreeImage_GetPitch(dib);
					for(int y = 0; y < nHeight; y++) {
						memcpy(dst_bits, src_bits, src_pitch);
						src_bits += src_pitch;
						dst_bits -= dst_pitch;
					}
				}
			}
			Bitmap = dib;
		}
		break;
		
		case PSD_CMYK: // CMYK
		{
			float C, M, Y, K;
			float s = 1.f / pow( 2.0f, _headerInfo._BitsPerPixel);
			
			if (16 == _headerInfo._BitsPerPixel) {
				// CMYK 16-bit : convert to RGB 16-bit
				FIBITMAP *dib = FreeImage_AllocateT(FIT_RGB16, nWidth, nHeight);
				if (NULL != dib) {
					BYTE *src_bits = (BYTE*)iprData;
					BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
					unsigned src_pitch = nChannels * nWidth * bytes;
					unsigned dst_pitch = FreeImage_GetPitch(dib);
					for(int y = 0; y < nHeight; y++) {
						unsigned short *src_line = (unsigned short*)src_bits;
						FIRGB16 *dst_line = (FIRGB16*)dst_bits;
						for(int x = 0; x < nWidth; x++) {
							C = (1.f - (float)psdGetValue((BYTE*)&src_line[0], bytes ) * s );
							M = (1.f - (float)psdGetValue((BYTE*)&src_line[1], bytes ) * s );
							Y = (1.f - (float)psdGetValue((BYTE*)&src_line[2], bytes ) * s );
							K = (1.f - (float)psdGetValue((BYTE*)&src_line[3], bytes ) * s );
							CMYKToRGB16(C, M, Y, K, &dst_line[x]);
							src_line += nChannels;
						}
						src_bits += src_pitch;
						dst_bits -= dst_pitch;
					}
					Bitmap = dib;
				}
			}
			else {
				// CMYK 8-bit : convert to RGB 8-bit
				FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 24);
				if (NULL != dib) {
					BYTE *src_bits = (BYTE*)iprData;
					BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
					unsigned src_pitch = nChannels * nWidth * bytes;
					unsigned dst_pitch = FreeImage_GetPitch(dib);
					for(int y = 0; y < nHeight; y++) {
						BYTE *src_line = (BYTE*)src_bits;
						RGBTRIPLE *dst_line = (RGBTRIPLE*)dst_bits;
						for(int x = 0; x < nWidth; x++) {
							C = (1.f - (float)psdGetValue((BYTE*)&src_line[0], bytes ) * s );
							M = (1.f - (float)psdGetValue((BYTE*)&src_line[1], bytes ) * s );
							Y = (1.f - (float)psdGetValue((BYTE*)&src_line[2], bytes ) * s );
							K = (1.f - (float)psdGetValue((BYTE*)&src_line[3], bytes ) * s );
							CMYKToRGB8(C, M, Y, K, &dst_line[x]);
							src_line += nChannels;
						}
						src_bits += src_pitch;
						dst_bits -= dst_pitch;
					}
					Bitmap = dib;
				}
			}
		}
		break;
		
		case PSD_MULTICHANNEL: // Multichannel
		{
			// assume format is in either CMY or CMYK
			assert(3 <= nChannels);
			float C, M, Y, K;
			float s = 1.f / pow( 2.0f, _headerInfo._BitsPerPixel);
			
			if (16 == _headerInfo._BitsPerPixel) {
				// CMY(K) 16-bit : convert to RGB 16-bit
				FIBITMAP *dib = FreeImage_AllocateT(FIT_RGB16, nWidth, nHeight);
				if (NULL != dib) {
					BYTE *src_bits = (BYTE*)iprData;
					BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
					unsigned src_pitch = nChannels * nWidth * bytes;
					unsigned dst_pitch = FreeImage_GetPitch(dib);
					for(int y = 0; y < nHeight; y++) {
						unsigned short *src_line = (unsigned short*)src_bits;
						FIRGB16 *dst_line = (FIRGB16*)dst_bits;
						for(int x = 0; x < nWidth; x++) {
							C = (1.f - (float)psdGetValue((BYTE*)&src_line[0], bytes ) * s );
							M = (1.f - (float)psdGetValue((BYTE*)&src_line[1], bytes ) * s );
							Y = (1.f - (float)psdGetValue((BYTE*)&src_line[2], bytes ) * s );
							K = (4 <= nChannels) ? (1.f - (float)psdGetValue((BYTE*)&src_line[nChannels], bytes )*s ) : 0;
							CMYKToRGB16(C, M, Y, K, &dst_line[x]);
							src_line += nChannels;
						}
						src_bits += src_pitch;
						dst_bits -= dst_pitch;
					}
					Bitmap = dib;
				}
			}
			else {
				// CMY(K) 8-bit : convert to RGB 8-bit
				FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 24);
				if (NULL != dib) {
					BYTE *src_bits = (BYTE*)iprData;
					BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
					unsigned src_pitch = nChannels * nWidth * bytes;
					unsigned dst_pitch = FreeImage_GetPitch(dib);
					for(int y = 0; y < nHeight; y++) {
						BYTE *src_line = (BYTE*)src_bits;
						RGBTRIPLE *dst_line = (RGBTRIPLE*)dst_bits;
						for(int x = 0; x < nWidth; x++) {
							C = (1.f - (float)psdGetValue((BYTE*)&src_line[0], bytes ) * s );
							M = (1.f - (float)psdGetValue((BYTE*)&src_line[1], bytes ) * s );
							Y = (1.f - (float)psdGetValue((BYTE*)&src_line[2], bytes ) * s );
							K = (4 <= nChannels) ? (1.f - (float)psdGetValue((BYTE*)&src_line[nChannels], bytes )*s ) : 0;
							CMYKToRGB8(C, M, Y, K, &dst_line[x]);
							src_line += nChannels;
						}
						src_bits += src_pitch;
						dst_bits -= dst_pitch;
					}
					Bitmap = dib;
				}
			}
		}
		break;
		
		case PSD_LAB: // Lab
		{
			const unsigned dMaxColours = 1 << _headerInfo._BitsPerPixel;
			const float sL = 100.F / dMaxColours;
			const float sa = 256.F / dMaxColours;
			const float sb = 256.F / dMaxColours;
			float L, a, b;
			
			if (16 == _headerInfo._BitsPerPixel) {
				// CIE Lab 16-bit : convert to RGB 16-bit
				FIBITMAP *dib = FreeImage_AllocateT(FIT_RGB16, nWidth, nHeight);
				if (NULL != dib) {
					BYTE *src_bits = (BYTE*)iprData;
					BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
					unsigned src_pitch = nChannels * nWidth * bytes;
					unsigned dst_pitch = FreeImage_GetPitch(dib);
					for(int y = 0; y < nHeight; y++) {
						unsigned short *src_line = (unsigned short*)src_bits;
						FIRGB16 *dst_line = (FIRGB16*)dst_bits;
						for(int x = 0; x < nWidth; x++) {
							L = (float)psdGetValue((BYTE*)&src_line[0], bytes ) * sL;
							a = (float)psdGetValue((BYTE*)&src_line[1], bytes ) * sa - 128.F;
							b = (float)psdGetValue((BYTE*)&src_line[2], bytes ) * sb - 128.F;
							CIELabToRGB16(L, a, b, &dst_line[x]);
							src_line += nChannels;
						}
						src_bits += src_pitch;
						dst_bits -= dst_pitch;
					}
					Bitmap = dib;
				}
			} else {
				// CIE Lab 8-bit : convert to RGB 8-bit
				FIBITMAP *dib = FreeImage_Allocate(nWidth, nHeight, 24);
				if (NULL != dib) {
					BYTE *src_bits = (BYTE*)iprData;
					BYTE *dst_bits = (BYTE*)FreeImage_GetScanLine(dib, nHeight-1);
					unsigned src_pitch = nChannels * nWidth * bytes;
					unsigned dst_pitch = FreeImage_GetPitch(dib);
					for(int y = 0; y < nHeight; y++) {
						BYTE *src_line = (BYTE*)src_bits;
						RGBTRIPLE *dst_line = (RGBTRIPLE*)dst_bits;
						for(int x = 0; x < nWidth; x++) {
							L = (float)psdGetValue((BYTE*)&src_line[0], bytes ) * sL;
							a = (float)psdGetValue((BYTE*)&src_line[1], bytes ) * sa - 128.F;
							b = (float)psdGetValue((BYTE*)&src_line[2], bytes ) * sb - 128.F;
							CIELabToRGB8(L, a, b, &dst_line[x]);
							src_line += nChannels;
						}
						src_bits += src_pitch;
						dst_bits -= dst_pitch;
					}
					Bitmap = dib;
				}
			}
		}
		break;
		
		default:
			break;
  }

  return Bitmap;
} 

FIBITMAP* psdParser::ReadImageData(FreeImageIO *io, fi_handle handle) {
	FIBITMAP *Bitmap = NULL;

	if(handle != NULL) {
		BYTE ShortValue[2];
		int n = (int)io->read_proc(&ShortValue, sizeof(ShortValue), 1, handle);
		short nCompression = (short)psdGetValue( ShortValue, sizeof(ShortValue) );
		
		switch ( nCompression ) {
			case PSD_COMPRESSION_NONE: // raw data
			{
				int nWidth = _headerInfo._Width;
				int nHeight = _headerInfo._Height;
				int bytes = _headerInfo._BitsPerPixel / 8;

				int nPixels = nWidth * nHeight;
				int nTotalBytes = nPixels * bytes * _headerInfo._Channels;

				if(_headerInfo._BitsPerPixel == 1) {
					// special case for PSD_BITMAP mode
					bytes = 1;
					nWidth = (nWidth + 7) / 8;
					nWidth = ( nWidth > 0 ) ? nWidth : 1;
					nPixels = nWidth * nHeight;
					nTotalBytes = nWidth * nHeight;
				}
				
				BYTE * plData = 0;
				BYTE * plPixel = 0;
				
				int nBytes = 0;

				switch (_headerInfo._ColourMode) {
					case PSD_BITMAP:
					{				
						plData = new BYTE [nTotalBytes];
						plPixel = new BYTE [bytes];
						
						while(nBytes < nTotalBytes) {
							n = (int)io->read_proc(plPixel, bytes, 1, handle);
							memcpy(plData+nBytes, plPixel, bytes );
							nBytes += n * bytes;
						}
						SAFE_DELETE_ARRAY(plPixel);
					}
					break;

					case PSD_INDEXED: // Indexed
					{
						assert( (-1 != _ColourCount) && (0 < _ColourCount) );
						assert( NULL != _colourModeData._plColourData );
						
						plData = new BYTE [nTotalBytes];
						plPixel = new BYTE [bytes];
						
						while(nBytes < nTotalBytes) {
							n = (int)io->read_proc(plPixel, bytes, 1, handle);
							memcpy(plData+nBytes, plPixel, bytes );
							nBytes += n * bytes;
						}
						SAFE_DELETE_ARRAY(plPixel);
					}
					break;
					
					case PSD_GRAYSCALE: // Grayscale
					case PSD_DUOTONE: // Duotone
					case PSD_RGB: // RGB
					{
						plData = new BYTE [nTotalBytes];
						plPixel = new BYTE [bytes];
						int nPixelCounter = 0;
						int nChannels = _headerInfo._Channels;
						
						for(int c = 0; c < nChannels; c++) {
							nPixelCounter = c * bytes;
							for(int nPos = 0; nPos < nPixels; ++nPos) {
								n = (int)io->read_proc(plPixel, bytes, 1, handle);
								if(n == 0) {
									break;
								}								
								if(2 == bytes) { 
									// swap for uint16
									SwapShort((WORD*)&plPixel[0]);
								} else if(4 == bytes) {
									// swap for float
									SwapLong((DWORD*)&plPixel[0]);
								}
								memcpy( plData + nPixelCounter, plPixel, bytes );
								nBytes += n * bytes;
								nPixelCounter += nChannels*bytes;
							}
						}
						SAFE_DELETE_ARRAY(plPixel);
					}
					break;
					
					case PSD_CMYK: // CMYK
					case PSD_MULTICHANNEL: // Multichannel
					{
						plPixel = new BYTE[bytes];
						plData = new BYTE[nTotalBytes];
						
						int nPixelCounter = 0;
						for (int c=0; c<_headerInfo._Channels; c++) {
							nPixelCounter = c*bytes;
							for ( int nPos = 0; nPos < nPixels; ++nPos ) {
								n = (int)io->read_proc(plPixel, bytes, 1, handle);
								if(n == 0) {
									break;
								}
								memcpy(plData + nPixelCounter, plPixel, bytes );
								nBytes += n * bytes;
								
								nPixelCounter += _headerInfo._Channels*bytes;
							}
						}
						SAFE_DELETE_ARRAY(plPixel);
					}
					break;
					
					case PSD_LAB: // Lab
					{
						plPixel = new BYTE[bytes];
						plData = new BYTE[nTotalBytes];
						int nPixelCounter = 0;
						for(int c = 0; c < 3; c++) {
							nPixelCounter = c*bytes;
							for ( int nPos = 0; nPos < nPixels; ++nPos ) {
								n = (int)io->read_proc(plPixel, bytes, 1, handle);
								if(n == 0) {
									break;
								}
								memcpy(plData + nPixelCounter, plPixel, bytes);
								nBytes += n * bytes;
								nPixelCounter += 3*bytes;
							}
						}
						SAFE_DELETE_ARRAY(plPixel);
					}
					break;
				}
				
				assert( nBytes == nTotalBytes );
				if (nBytes == nTotalBytes) {
					if (plData) {
						switch (_headerInfo._BitsPerPixel) {
							case 1: 						
							case 8: 
							case 16:
							case 32:
								Bitmap = ProcessBuffer(plData);
								break;
								
							default: // Unsupported 
								break;
						}
					}
				}

				SAFE_DELETE_ARRAY(plData);
			}
			break;
			
			
			case PSD_COMPRESSION_RLE: // RLE compression
			{
				int nWidth = _headerInfo._Width;
				int nHeight = _headerInfo._Height;
				int bytes = _headerInfo._BitsPerPixel / 8;
				
				int nPixels = nWidth * nHeight;
				int nTotalBytes = nPixels * bytes * _headerInfo._Channels;

				if(_headerInfo._BitsPerPixel == 1) {
					// special case for PSD_BITMAP mode
					bytes = 1;
					nWidth = (nWidth + 7) / 8;
					nWidth = ( nWidth > 0 ) ? nWidth : 1;
					nPixels = nWidth * nHeight;
					nTotalBytes = nWidth * nHeight;
				}
				
				BYTE * plData = new BYTE[nTotalBytes];
				BYTE * p = plData;
				int nValue = 0;
				
				BYTE ByteValue[1];
				
				int Count = 0;
				
				// The RLE-compressed data is preceeded by a 2-byte data count for each row in the data,
				// which we're going to just skip.
				io->seek_proc(handle, nHeight * _headerInfo._Channels * 2, SEEK_CUR);
				
				for (int channel = 0; channel < _headerInfo._Channels; channel++) {
					// Read the RLE data.
					Count = 0;
					while (Count < nPixels) {
						io->read_proc(&ByteValue, sizeof(ByteValue), 1, handle);
						
						int len = psdGetValue( ByteValue, sizeof(ByteValue) );
						if ( 128 > len ) {
							len++;
							Count += len;
							
							while (len) {
								io->read_proc(&ByteValue, sizeof(ByteValue), 1, handle);
								nValue = psdGetValue( ByteValue, sizeof(ByteValue) );
								*p = (BYTE)nValue;
								p += sizeof(ByteValue);
								len--;
							}
						}
						else if ( 128 < len ) {
							// Next -len+1 bytes in the dest are replicated from next source byte.
							// (Interpret len as a negative 8-bit int.)
							len ^= 0x0FF;
							len += 2;
							io->read_proc(&ByteValue, sizeof(ByteValue), 1, handle);
							
							nValue = psdGetValue( ByteValue, sizeof(ByteValue) );
							Count += len;
							while (len) {
								*p = (BYTE)nValue;
								p += sizeof(ByteValue);
								len--;
							}
						}
						else if ( 128 == len ) {
							// Do nothing
						}
					}
				}
				
				BYTE * prSource = plData;
				BYTE * plDest = new BYTE[nTotalBytes];
				memset(plDest, 254, nTotalBytes);
				
				int nPixelCounter = 0;
				for(int c=0; c<_headerInfo._Channels; c++) {
					nPixelCounter = c*bytes;
					for (int nPos = 0; nPos<nPixels; ++nPos) {
						memcpy( plDest + nPixelCounter, prSource, bytes );
						prSource++;
						nPixelCounter += _headerInfo._Channels*bytes;
					}
				}
				SAFE_DELETE_ARRAY(plData);
				
				if (plDest) {
					switch (_headerInfo._BitsPerPixel) {
						case 1: 	
						case 8: 
						case 16:
							Bitmap = ProcessBuffer(plDest);
							break;
							
						default: // Unsupported format
							break;
					}
				}
				SAFE_DELETE_ARRAY(plDest);
			}
			break;

			case 2: // ZIP without prediction, no specification
				break;
				
			case 3: // ZIP with prediction, no specification
				break;
				
			default: // Unknown format
				break;
		}
	}
	
	return Bitmap;

} 

FIBITMAP* psdParser::Load(FreeImageIO *io, fi_handle handle, int s_format_id) {
	FIBITMAP *Bitmap = NULL;
		
	try {
		if (NULL == handle) {
			throw("Cannot open file");
		}
		
		if (!_headerInfo.Read(io, handle)) {
			throw("Error in header");
		}

		if (!_colourModeData.Read(io, handle)) {
			throw("Error in ColourMode Data");
		}
		
		if (!ReadImageResource(io, handle)) {
			throw("Error in Image Resource");
		}
		
		if (!ReadLayerAndMaskInfoSection(io, handle)) {
			throw("Error in Mask Info");
		}
		
		Bitmap = ReadImageData(io, handle);
		if (NULL == Bitmap) {
			throw("Error in Image Data");
		}

		// set resolution info
		if(NULL != Bitmap) {
			unsigned res_x = 2835;	// 72 dpi
			unsigned res_y = 2835;	// 72 dpi
			if (_bResolutionInfoFilled) {
				_resolutionInfo.GetResolutionInfo(res_x, res_y);
			}
			FreeImage_SetDotsPerMeterX(Bitmap, res_x);
			FreeImage_SetDotsPerMeterY(Bitmap, res_y);	
		}

		// set ICC profile
		if(NULL != _iccProfile._ProfileData) {
			FreeImage_CreateICCProfile(Bitmap, _iccProfile._ProfileData, _iccProfile._ProfileSize);
		}
		
	} catch(const char *text) {
		FreeImage_OutputMessageProc(s_format_id, text);
	}

	return Bitmap;
} 
