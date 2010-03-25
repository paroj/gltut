unit FreeImage;

// ==========================================================
// Delphi wrapper for FreeImage 3
//
// Design and implementation by
// - Simon Beavis
// - Peter Byström
// - Anatoliy Pulyaevskiy (xvel84@rambler.ru)
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

interface

uses Windows;

{$MINENUMSIZE 4} // Make sure enums are stored as an integer to be compatible with C/C++

const
  FIDLL = 'FreeImage.dll';
  
// --------------------------------------------------------------------------
// Bitmap types -------------------------------------------------------------
// --------------------------------------------------------------------------

type
  FIBITMAP = record
    data : Pointer;
  end;
  PFIBITMAP = ^FIBITMAP;

  FIMULTIBITMAP = record
    data : Pointer;
  end;
  PFIMULTIBITMAP = ^FIMULTIBITMAP;

// --------------------------------------------------------------------------
// Indexes for byte arrays, masks and shifts for treating pixels as words ---
// These coincide with the order of RGBQUAD and RGBTRIPLE -------------------
// Little Endian (x86 / MS Windows, Linux) : BGR(A) order -------------------
// --------------------------------------------------------------------------

const
  FI_RGBA_RED         = 2;
  FI_RGBA_GREEN       = 1;
  FI_RGBA_BLUE        = 0;
  FI_RGBA_ALPHA       = 3;
  FI_RGBA_RED_MASK    = $00FF0000;
  FI_RGBA_GREEN_MASK  = $0000FF00;
  FI_RGBA_BLUE_MASK   = $000000FF;
  FI_RGBA_ALPHA_MASK  = $FF000000;
  FI_RGBA_RED_SHIFT   = 16;
  FI_RGBA_GREEN_SHIFT = 8;
  FI_RGBA_BLUE_SHIFT  = 0;
  FI_RGBA_ALPHA_SHIFT = 24;

// --------------------------------------------------------------------------
// The 16bit macros only include masks and shifts, --------------------------
// since each color element is not byte aligned -----------------------------
// --------------------------------------------------------------------------

const
  FI16_555_RED_MASK		 = $7C00;
  FI16_555_GREEN_MASK	 = $03E0;
  FI16_555_BLUE_MASK	 = $001F;
  FI16_555_RED_SHIFT	 = 10;
  FI16_555_GREEN_SHIFT = 5;
  FI16_555_BLUE_SHIFT	 = 0;
  FI16_565_RED_MASK		 = $F800;
  FI16_565_GREEN_MASK	 = $07E0;
  FI16_565_BLUE_MASK	 = $001F;
  FI16_565_RED_SHIFT	 = 11;
  FI16_565_GREEN_SHIFT = 5;
  FI16_565_BLUE_SHIFT	 = 0;

// --------------------------------------------------------------------------
// ICC profile support ------------------------------------------------------
// --------------------------------------------------------------------------

const
  FIICC_DEFAULT = $0;
  FIICC_COLOR_IS_CMYK	= $1;

type
  FIICCPROFILE = record
    flags : WORD;   // info flag
    size : DWORD;   // profile's size measured in bytes
    data : Pointer; // points to a block of contiguous memory containing the profile
  end;
  PFIICCPROFILE = ^FIICCPROFILE;

// --------------------------------------------------------------------------
// Important enums ----------------------------------------------------------
// --------------------------------------------------------------------------

type
  FREE_IMAGE_FORMAT         = type Integer;
  FREE_IMAGE_TYPE           = type Integer;
  FREE_IMAGE_COLOR_TYPE     = type Integer;
  FREE_IMAGE_QUANTIZE       = type Integer;
  FREE_IMAGE_DITHER         = type Integer;
  FREE_IMAGE_FILTER         = type Integer;
  FREE_IMAGE_COLOR_CHANNEL  = type Integer;
  FREE_IMAGE_MDTYPE         = type Integer;
  FREE_IMAGE_MDMODEL        = type Integer;
  FREE_IMAGE_JPEG_OPERATION = type Integer;
  FREE_IMAGE_TMO            = type Integer;

const
  // I/O image format identifiers.
  FIF_UNKNOWN = FREE_IMAGE_FORMAT(-1);
  FIF_BMP     = FREE_IMAGE_FORMAT(0);
  FIF_ICO     = FREE_IMAGE_FORMAT(1);
  FIF_JPEG    = FREE_IMAGE_FORMAT(2);
  FIF_JNG     = FREE_IMAGE_FORMAT(3);
  FIF_KOALA   = FREE_IMAGE_FORMAT(4);
  FIF_LBM     = FREE_IMAGE_FORMAT(5);
  FIF_IFF     = FIF_LBM;
  FIF_MNG     = FREE_IMAGE_FORMAT(6);
  FIF_PBM     = FREE_IMAGE_FORMAT(7);
  FIF_PBMRAW  = FREE_IMAGE_FORMAT(8);
  FIF_PCD     = FREE_IMAGE_FORMAT(9);
  FIF_PCX     = FREE_IMAGE_FORMAT(10);
  FIF_PGM     = FREE_IMAGE_FORMAT(11);
  FIF_PGMRAW  = FREE_IMAGE_FORMAT(12);
  FIF_PNG     = FREE_IMAGE_FORMAT(13);
  FIF_PPM     = FREE_IMAGE_FORMAT(14);
  FIF_PPMRAW  = FREE_IMAGE_FORMAT(15);
  FIF_RAS     = FREE_IMAGE_FORMAT(16);
  FIF_TARGA   = FREE_IMAGE_FORMAT(17);
  FIF_TIFF    = FREE_IMAGE_FORMAT(18);
  FIF_WBMP    = FREE_IMAGE_FORMAT(19);
  FIF_PSD     = FREE_IMAGE_FORMAT(20);
  FIF_CUT     = FREE_IMAGE_FORMAT(21);
  FIF_XBM     = FREE_IMAGE_FORMAT(22);
  FIF_XPM     = FREE_IMAGE_FORMAT(23);
  FIF_DDS     = FREE_IMAGE_FORMAT(24);
  FIF_GIF     = FREE_IMAGE_FORMAT(25);
  FIF_HDR     = FREE_IMAGE_FORMAT(26);
  FIF_FAXG3   = FREE_IMAGE_FORMAT(27);
  FIF_SGI     = FREE_IMAGE_FORMAT(28);  

  // Image type used in FreeImage.
  FIT_UNKNOWN = FREE_IMAGE_TYPE(0);  // unknown type
  FIT_BITMAP  = FREE_IMAGE_TYPE(1);	 // standard image: 1-, 4-, 8-, 16-, 24-, 32-bit
  FIT_UINT16  = FREE_IMAGE_TYPE(2);	 // array of unsigned short: unsigned 16-bit
  FIT_INT16   = FREE_IMAGE_TYPE(3);  // array of short: signed 16-bit
  FIT_UINT32  = FREE_IMAGE_TYPE(4);	 // array of unsigned long: unsigned 32-bit
  FIT_INT32   = FREE_IMAGE_TYPE(5);	 // array of long: signed 32-bit
  FIT_FLOAT   = FREE_IMAGE_TYPE(6);	 // array of float: 32-bit IEEE floating point
  FIT_DOUBLE  = FREE_IMAGE_TYPE(7);	 // array of double: 64-bit IEEE floating point
  FIT_COMPLEX = FREE_IMAGE_TYPE(8);	 // array of FICOMPLEX: 2 x 64-bit IEEE floating point
  FIT_RGB16	  = FREE_IMAGE_TYPE(9);	 // 48-bit RGB image: 3 x 16-bit
	FIT_RGBA16	= FREE_IMAGE_TYPE(10); // 64-bit RGBA image: 4 x 16-bit
	FIT_RGBF	  = FREE_IMAGE_TYPE(11); // 96-bit RGB float image: 3 x 32-bit IEEE floating point
	FIT_RGBAF	  = FREE_IMAGE_TYPE(12); // 128-bit RGBA float image: 4 x 32-bit IEEE floating point

  // Image color type used in FreeImage.
  FIC_MINISWHITE = FREE_IMAGE_COLOR_TYPE(0); // min value is white
  FIC_MINISBLACK = FREE_IMAGE_COLOR_TYPE(1); // min value is black
  FIC_RGB        = FREE_IMAGE_COLOR_TYPE(2); // RGB color model
  FIC_PALETTE    = FREE_IMAGE_COLOR_TYPE(3); // color map indexed
  FIC_RGBALPHA   = FREE_IMAGE_COLOR_TYPE(4); // RGB color model with alpha channel
  FIC_CMYK       = FREE_IMAGE_COLOR_TYPE(5); // CMYK color model

  // Color quantization algorithms. Constants used in FreeImage_ColorQuantize.
  FIQ_WUQUANT = FREE_IMAGE_QUANTIZE(0);	// Xiaolin Wu color quantization algorithm
  FIQ_NNQUANT = FREE_IMAGE_QUANTIZE(1);	// NeuQuant neural-net quantization algorithm by Anthony Dekker

  // Dithering algorithms. Constants used FreeImage_Dither.
  FID_FS            = FREE_IMAGE_DITHER(0);	// Floyd & Steinberg error diffusion
  FID_BAYER4x4      = FREE_IMAGE_DITHER(1);	// Bayer ordered dispersed dot dithering (order 2 dithering matrix)
  FID_BAYER8x8      = FREE_IMAGE_DITHER(2);	// Bayer ordered dispersed dot dithering (order 3 dithering matrix)
  FID_CLUSTER6x6    = FREE_IMAGE_DITHER(3);	// Ordered clustered dot dithering (order 3 - 6x6 matrix)
  FID_CLUSTER8x8    = FREE_IMAGE_DITHER(4);	// Ordered clustered dot dithering (order 4 - 8x8 matrix)
  FID_CLUSTER16x16  = FREE_IMAGE_DITHER(5); // Ordered clustered dot dithering (order 8 - 16x16 matrix)

  // Lossless JPEG transformations Constants used in FreeImage_JPEGTransform
	FIJPEG_OP_NONE			  = FREE_IMAGE_JPEG_OPERATION(0);	// no transformation
	FIJPEG_OP_FLIP_H		  = FREE_IMAGE_JPEG_OPERATION(1);	// horizontal flip
	FIJPEG_OP_FLIP_V		  = FREE_IMAGE_JPEG_OPERATION(2);	// vertical flip
	FIJPEG_OP_TRANSPOSE		= FREE_IMAGE_JPEG_OPERATION(3);	// transpose across UL-to-LR axis
	FIJPEG_OP_TRANSVERSE	= FREE_IMAGE_JPEG_OPERATION(4);	// transpose across UR-to-LL axis
	FIJPEG_OP_ROTATE_90		= FREE_IMAGE_JPEG_OPERATION(5);	// 90-degree clockwise rotation
	FIJPEG_OP_ROTATE_180	= FREE_IMAGE_JPEG_OPERATION(6);	// 180-degree rotation
	FIJPEG_OP_ROTATE_270	= FREE_IMAGE_JPEG_OPERATION(7); // 270-degree clockwise (or 90 ccw)

  // Tone mapping operators. Constants used in FreeImage_ToneMapping.
  FITMO_DRAGO03	   = FREE_IMAGE_TMO(0);	// Adaptive logarithmic mapping (F. Drago, 2003)
	FITMO_REINHARD05 = FREE_IMAGE_TMO(1);	// Dynamic range reduction inspired by photoreceptor physiology (E. Reinhard, 2005)

  // Upsampling / downsampling filters. Constants used in FreeImage_Rescale.
  FILTER_BOX	      = FREE_IMAGE_FILTER(0);	// Box, pulse, Fourier window, 1st order (constant) b-spline
  FILTER_BICUBIC    = FREE_IMAGE_FILTER(1);	// Mitchell & Netravali's two-param cubic filter
  FILTER_BILINEAR   = FREE_IMAGE_FILTER(2);	// Bilinear filter
  FILTER_BSPLINE    = FREE_IMAGE_FILTER(3);	// 4th order (cubic) b-spline
  FILTER_CATMULLROM = FREE_IMAGE_FILTER(4);	// Catmull-Rom spline, Overhauser spline
  FILTER_LANCZOS3   = FREE_IMAGE_FILTER(5);	// Lanczos3 filter

  // Color channels. Constants used in color manipulation routines.
  FICC_RGB   = FREE_IMAGE_COLOR_CHANNEL(0); // Use red, green and blue channels
  FICC_RED   = FREE_IMAGE_COLOR_CHANNEL(1); // Use red channel
  FICC_GREEN = FREE_IMAGE_COLOR_CHANNEL(2); // Use green channel
  FICC_BLUE  = FREE_IMAGE_COLOR_CHANNEL(3); // Use blue channel
  FICC_ALPHA = FREE_IMAGE_COLOR_CHANNEL(4); // Use alpha channel
  FICC_BLACK = FREE_IMAGE_COLOR_CHANNEL(5); // Use black channel
  FICC_REAL  = FREE_IMAGE_COLOR_CHANNEL(6); // Complex images: use real part
  FICC_IMAG  = FREE_IMAGE_COLOR_CHANNEL(7); // Complex images: use imaginary part
  FICC_MAG   = FREE_IMAGE_COLOR_CHANNEL(8); // Complex images: use magnitude
  FICC_PHASE = FREE_IMAGE_COLOR_CHANNEL(9);	// Complex images: use phase

  // Tag data type information (based on TIFF specifications)
  FIDT_NOTYPE	   = FREE_IMAGE_MDTYPE(0);	// placeholder
  FIDT_BYTE	     = FREE_IMAGE_MDTYPE(1);	// 8-bit unsigned integer
  FIDT_ASCII	   = FREE_IMAGE_MDTYPE(2);	// 8-bit bytes w/ last byte null
  FIDT_SHORT	   = FREE_IMAGE_MDTYPE(3);	// 16-bit unsigned integer
  FIDT_LONG	     = FREE_IMAGE_MDTYPE(4);	// 32-bit unsigned integer
  FIDT_RATIONAL  = FREE_IMAGE_MDTYPE(5);	// 64-bit unsigned fraction
  FIDT_SBYTE	   = FREE_IMAGE_MDTYPE(6);	// 8-bit signed integer
  FIDT_UNDEFINED = FREE_IMAGE_MDTYPE(7);	// 8-bit untyped data
  FIDT_SSHORT	   = FREE_IMAGE_MDTYPE(8);	// 16-bit signed integer
  FIDT_SLONG	   = FREE_IMAGE_MDTYPE(9);	// 32-bit signed integer
  FIDT_SRATIONAL = FREE_IMAGE_MDTYPE(10); // 64-bit signed fraction
  FIDT_FLOAT	   = FREE_IMAGE_MDTYPE(11); // 32-bit IEEE floating point
  FIDT_DOUBLE	   = FREE_IMAGE_MDTYPE(12); // 64-bit IEEE floating point
  FIDT_IFD	     = FREE_IMAGE_MDTYPE(13);	// 32-bit unsigned integer (offset)
  FIDT_PALETTE	 = FREE_IMAGE_MDTYPE(14);	// 32-bit RGBQUAD

  // Metadata models supported by FreeImage
  FIMD_NODATA	        = FREE_IMAGE_MDMODEL(-1);
  FIMD_COMMENTS	      = FREE_IMAGE_MDMODEL(0);  // single comment or keywords
  FIMD_EXIF_MAIN      = FREE_IMAGE_MDMODEL(1);  // Exif-TIFF metadata
  FIMD_EXIF_EXIF      = FREE_IMAGE_MDMODEL(2);  // Exif-specific metadata
  FIMD_EXIF_GPS	      = FREE_IMAGE_MDMODEL(3);  // Exif GPS metadata
  FIMD_EXIF_MAKERNOTE = FREE_IMAGE_MDMODEL(4);  // Exif maker note metadata
  FIMD_EXIF_INTEROP   = FREE_IMAGE_MDMODEL(5);  // Exif interoperability metadata
  FIMD_IPTC	          = FREE_IMAGE_MDMODEL(6);  // IPTC/NAA metadata
  FIMD_XMP	          = FREE_IMAGE_MDMODEL(7);  // Abobe XMP metadata
  FIMD_GEOTIFF	      = FREE_IMAGE_MDMODEL(8);  // GeoTIFF metadata (to be implemented)
  FIMD_ANIMATION		  = FREE_IMAGE_MDMODEL(9);  // Animation metadata
  FIMD_CUSTOM	        = FREE_IMAGE_MDMODEL(10); // Used to attach other metadata types to a dib

//{$endif}

type
  // Handle to a metadata model
  FIMETADATA = record
    data: Pointer;
  end;
  PFIMETADATA = ^FIMETADATA;

  // Handle to a metadata tag
  FITAG = record
    data: Pointer;
  end;
  PFITAG = ^FITAG;

// --------------------------------------------------------------------------
// File IO routines ---------------------------------------------------------
// --------------------------------------------------------------------------

type
  FI_Handle = Pointer;
  PCardinal = ^Cardinal;
  PInt = ^Integer;

  FI_ReadProc = function(buffer : pointer; size : Cardinal; count : Cardinal; handle : fi_handle) : PCardinal; stdcall;
  FI_WriteProc = function(buffer : pointer; size, count : Cardinal; handle : FI_Handle) : PCardinal; stdcall;
  FI_SeekProc = function(handle : fi_handle; offset : longint; origin : integer) : pint; stdcall;
  FI_TellProc = function(handle : fi_handle) : PCardinal; stdcall;

  FreeImageIO = packed record
    read_proc : FI_ReadProc;     // pointer to the function used to read data
    write_proc: FI_WriteProc;    // pointer to the function used to write data
    seek_proc : FI_SeekProc;     // pointer to the function used to seek
    tell_proc : FI_TellProc;     // pointer to the function used to aquire the current position
  end;
  PFreeImageIO = ^FreeImageIO;

  // Handle to a memory I/O stream
  FIMEMORY = record
    data: Pointer;
  end;
  PFIMEMORY = ^FIMEMORY;

const
  // constants used in FreeImage_Seek for Origin parameter
  SEEK_SET = 0;
  SEEK_CUR = 1;
  SEEK_END = 2;

// --------------------------------------------------------------------------
// Plugin routines ----------------------------------------------------------
// --------------------------------------------------------------------------

type
  PPluginStruct = ^PluginStruct;

  FI_InitProc = procedure(Plugin: PPluginStruct; Format_ID: Integer); stdcall;
  FI_FormatProc = function: PChar; stdcall;
  FI_DescriptionProc = function: PChar; stdcall;
  FI_ExtensionListProc = function: PChar; stdcall;
  FI_RegExprProc = function: PChar; stdcall;
  FI_OpenProc = function(IO: PFreeImageIO; Handle: FI_Handle; Read: Boolean): Pointer; stdcall;
  FI_CloseProc = procedure(IO: PFreeImageIO; Handle: FI_Handle; Data: Pointer); stdcall;
  FI_PageCountProc = function(IO: PFreeImageIO; Handle: FI_Handle; Data: Pointer): Integer; stdcall;
  FI_PageCapabilityProc = function(IO: PFreeImageIO; Handle: FI_Handle; Data: Pointer): integer; stdcall;
  FI_LoadProc = function(IO: PFreeImageIO; Handle: FI_Handle; Page, Flags: Integer; data: pointer): PFIBITMAP; stdcall;
  FI_SaveProc = function(IO: PFreeImageIO; Dib: PFIBITMAP; Handle: FI_Handle; Page, Flags: Integer; Data: Pointer): Boolean; stdcall;
  FI_ValidateProc = function(IO: PFreeImageIO; Handle: FI_Handle): Boolean; stdcall;
  FI_MimeProc = function: PChar; stdcall;
  FI_SupportsExportBPPProc = function(Bpp: integer): boolean; stdcall;
  FI_SupportsExportTypeProc = function(AType: FREE_IMAGE_TYPE): Boolean; stdcall;
  FI_SupportsICCProfilesProc = function: Boolean; stdcall;

  PluginStruct = record
    format_proc: FI_FormatProc;
    description_proc: FI_DescriptionProc;
    extension_proc: FI_ExtensionListProc;
    regexpr_proc: FI_RegExprProc;
    open_proc: FI_OpenProc;
    close_proc: FI_CloseProc;
    pagecount_proc: FI_PageCountProc;
    pagecapability_proc: FI_PageCapabilityProc;
    load_proc: FI_LoadProc;
    save_proc: FI_SaveProc;
    validate_proc: FI_ValidateProc;
    mime_proc: FI_MimeProc;
    supports_export_bpp_proc: FI_SupportsExportBPPProc;
    supports_export_type_proc: FI_SupportsExportTypeProc;
    supports_icc_profiles_proc: FI_SupportsICCProfilesProc;
  end;

// --------------------------------------------------------------------------
// Load/Save flag constants -------------------------------------------------
// --------------------------------------------------------------------------

const
  BMP_DEFAULT         = 0;
  BMP_SAVE_RLE        = 1;
  CUT_DEFAULT         = 0;
  DDS_DEFAULT         = 0;
  FAXG3_DEFAULT       = 0;
  GIF_DEFAULT         = 0;
  ICO_DEFAULT         = 0;
  ICO_MAKEALPHA       = 1;     // convert to 32bpp and create an alpha channel from the AND-mask when loading
  IFF_DEFAULT         = 0;
  JPEG_DEFAULT        = 0;
  JPEG_FAST           = 1;
  JPEG_ACCURATE       = 2;
  JPEG_QUALITYSUPERB  = $0080;
  JPEG_QUALITYGOOD    = $0100;
  JPEG_QUALITYNORMAL  = $0200;
  JPEG_QUALITYAVERAGE = $0400;
  JPEG_QUALITYBAD     = $0800;
  JPEG_CMYK           = $1000; // load separated CMYK "as is" (use | to combine with other flags)
  KOALA_DEFAULT       = 0;
  LBM_DEFAULT         = 0;
  MNG_DEFAULT         = 0;
  PCD_DEFAULT         = 0;
  PCD_BASE            = 1;     // load the bitmap sized 768 x 512
  PCD_BASEDIV4        = 2;     // load the bitmap sized 384 x 256
  PCD_BASEDIV16       = 3;     // load the bitmap sized 192 x 128
  PCX_DEFAULT         = 0;
  PNG_DEFAULT         = 0;
  PNG_IGNOREGAMMA     = 1;     // avoid gamma correction
  PNM_DEFAULT         = 0;
  PNM_SAVE_RAW        = 0;     // If set the writer saves in RAW format (i.e. P4, P5 or P6)
  PNM_SAVE_ASCII      = 1;     // If set the writer saves in ASCII format (i.e. P1, P2 or P3)
  PSD_DEFAULT         = 0;
  RAS_DEFAULT         = 0;
  SGI_DEFAULT         = 0;
  TARGA_DEFAULT       = 0;
  TARGA_LOAD_RGB888   = 1;     // If set the loader converts RGB555 and ARGB8888 -> RGB888.
  TIFF_DEFAULT        = 0;
  TIFF_CMYK	          = $0001;  // reads/stores tags for separated CMYK (use | to combine with compression flags)
  TIFF_PACKBITS       = $0100;  // save using PACKBITS compression
  TIFF_DEFLATE        = $0200;  // save using DEFLATE compression
  TIFF_ADOBE_DEFLATE  = $0400;  // save using ADOBE DEFLATE compression
  TIFF_NONE           = $0800;  // save without any compression
  TIFF_CCITTFAX3		  = $1000;  // save using CCITT Group 3 fax encoding
  TIFF_CCITTFAX4		  = $2000;  // save using CCITT Group 4 fax encoding
  TIFF_LZW			      = $4000; 	// save using LZW compression
  TIFF_JPEG			      = $8000;	// save using JPEG compression
  WBMP_DEFAULT        = 0;
  XBM_DEFAULT         = 0;
  XPM_DEFAULT         = 0;

// --------------------------------------------------------------------------
// Init/Error routines ------------------------------------------------------
// --------------------------------------------------------------------------

procedure FreeImage_Initialise(load_local_plugins_only : boolean = False); stdcall; external FIDLL name '_FreeImage_Initialise@4';
procedure FreeImage_DeInitialise; stdcall; external FIDLL name '_FreeImage_DeInitialise@0';

// --------------------------------------------------------------------------
// Version routines ---------------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_GetVersion : PChar; stdcall; external FIDLL name '_FreeImage_GetVersion@0';
function FreeImage_GetCopyrightMessage : PChar; stdcall; external FIDLL name '_FreeImage_GetCopyrightMessage@0';

// --------------------------------------------------------------------------
// Message output functions -------------------------------------------------
// --------------------------------------------------------------------------

procedure FreeImage_OutPutMessageProc(fif: Integer; fmt: PChar); stdcall; external FIDLL name 'FreeImage_OutputMessageProc';
type FreeImage_OutputMessageFunction = function(fif: FREE_IMAGE_FORMAT; msg: PChar): pointer; stdcall;
procedure FreeImage_SetOutputMessage(omf: FreeImage_OutputMessageFunction); stdcall; external FIDLL name '_FreeImage_SetOutputMessage@4';

// --------------------------------------------------------------------------
// Allocate/Unload routines -------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_Allocate(width, height, bpp: integer; red_mask: Cardinal = 0; green_mask: Cardinal = 0; blue_mask: Cardinal = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_Allocate@24';
function FreeImage_AllocateT(Atype: FREE_IMAGE_TYPE; Width, Height: Integer; bpp: Integer = 8; red_mask: Cardinal = 0; green_mask: Cardinal = 0; blue_mask: Cardinal = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_AllocateT@28';
function FreeImage_Clone(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_Clone@4';
procedure FreeImage_Unload(dib: PFIBITMAP); stdcall; external FIDLL name '_FreeImage_Unload@4';

// --------------------------------------------------------------------------
// Load / Save routines -----------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_Load(fif: FREE_IMAGE_FORMAT; const filename: PChar; flags: integer = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_Load@12';
function FreeImage_LoadU(fif: FREE_IMAGE_FORMAT; const filename: PWideChar; flags: Integer = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_LoadU@12';
function FreeImage_LoadFromHandle(fif: FREE_IMAGE_FORMAT; io: PFreeImageIO; handle: fi_handle; flags: integer = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_LoadFromHandle@16';
function FreeImage_Save(fif: FREE_IMAGE_FORMAT; dib: PFIBITMAP; filename: PChar; flags: integer = 0): Boolean; stdcall; external FIDLL name '_FreeImage_Save@16';
function FreeImage_SaveU(fif: FREE_IMAGE_FORMAT; dib: PFIBITMAP; const filename: PWideChar; flags: Integer = 0): Boolean; stdcall; external FIDLL name '_FreeImage_SaveU@16';
function FreeImage_SaveToHandle(fif: FREE_IMAGE_FORMAT; dib: PFIBITMAP; io : PFreeImageIO; handle : fi_handle; flags : integer = 0) : Boolean; stdcall; external FIDLL name '_FreeImage_SaveToHandle@20';

// --------------------------------------------------------------------------
// Memory I/O stream routines -----------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_OpenMemory(data: PByte = nil; size_in_bytes: DWORD = 0): PFIMEMORY; stdcall; external FIDLL name '_FreeImage_OpenMemory@8';
procedure FreeImage_CloseMemory(stream: PFIMEMORY); stdcall; external FIDLL name '_FreeImage_CloseMemory@4';
function FreeImage_LoadFromMemory(fif: FREE_IMAGE_FORMAT; stream: PFIMEMORY; flags: Integer = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_LoadFromMemory@12';
function FreeImage_SaveToMemory(fif: FREE_IMAGE_FORMAT; dib: PFIBITMAP; stream: PFIMEMORY; flags: Integer = 0): Boolean; stdcall; external FIDLL name '_FreeImage_SaveToMemory@16';
function FreeImage_TellMemory(stream: PFIMEMORY): Longint; stdcall; external FIDLL name '_FreeImage_TellMemory@4';
function FreeImage_SeekMemory(stream: PFIMEMORY; offset: Longint; origin: Integer): Boolean; stdcall; external FIDLL name '_FreeImage_SeekMemory@12';
function FreeImage_AcquireMemory(stream: PFIMEMORY; var data: PByte; var size_in_bytes: DWORD): Boolean; stdcall; external FIDLL name '_FreeImage_AcquireMemory@12';

// --------------------------------------------------------------------------
// Plugin Interface ---------------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_RegisterLocalPlugin(proc_address: FI_InitProc; format, description, extension, regexpr: PChar): FREE_IMAGE_FORMAT; stdcall; external FIDLL name '_FreeImage_RegisterLocalPlugin@20';
function FreeImage_RegisterExternalPlugin(path, format, description, extension, regexpr: PChar): FREE_IMAGE_FORMAT; stdcall; external FIDLL name '_FreeImage_RegisterExternalPlugin@20';
function FreeImage_GetFIFCount: Integer; stdcall; external FIDLL name '_FreeImage_GetFIFCount@0';
procedure FreeImage_SetPluginEnabled(fif: FREE_IMAGE_FORMAT; enable: Boolean); stdcall; external FIDLL Name '_FreeImage_SetPluginEnabled@8';
function FreeImage_IsPluginEnabled(fif: FREE_IMAGE_FORMAT): Integer; stdcall; external FIDLL Name '_FreeImage_IsPluginEnabled@4';
function FreeImage_GetFIFFromFormat(const format: PChar): FREE_IMAGE_FORMAT; stdcall; external FIDLL Name '_FreeImage_GetFIFFromFormat@4';
function FreeImage_GetFIFFromMime(const format: PChar): FREE_IMAGE_FORMAT; stdcall; external FIDLL Name '_FreeImage_GetFIFFromMime@4';
function FreeImage_GetFormatFromFIF(fif: FREE_IMAGE_FORMAT): PChar; stdcall; external FIDLL Name '_FreeImage_GetFormatFromFIF@4';
function FreeImage_GetFIFExtensionList(fif: FREE_IMAGE_FORMAT): PChar; stdcall; external FIDLL Name '_FreeImage_GetFIFExtensionList@4';
function FreeImage_GetFIFDescription(fif: FREE_IMAGE_FORMAT): PChar; stdcall; external FIDLL Name '_FreeImage_GetFIFDescription@4';
function FreeImage_GetFIFRegExpr(fif: FREE_IMAGE_FORMAT): PChar; stdcall; external FIDLL Name '_FreeImage_GetFIFRegExpr@4';
function FreeImage_GetFIFFromFilename(const fname: PChar): FREE_IMAGE_FORMAT; stdcall; external FIDLL Name '_FreeImage_GetFIFFromFilename@4';
function FreeImage_GetFIFFromFilenameU(const fname:PWideChar): FREE_IMAGE_FORMAT; stdcall; external FIDLL Name '_FreeImage_GetFIFFromFilenameU@4';
function FreeImage_FIFSupportsReading(fif: FREE_IMAGE_FORMAT): Boolean; stdcall; external FIDLL Name '_FreeImage_FIFSupportsReading@4';
function FreeImage_FIFSupportsWriting(fif: FREE_IMAGE_FORMAT): Boolean; stdcall; external FIDLL Name '_FreeImage_FIFSupportsWriting@4';
function FreeImage_FIFSupportsExportBPP(fif: FREE_IMAGE_FORMAT; bpp: Integer): Boolean; stdcall; external FIDLL Name '_FreeImage_FIFSupportsExportBPP@8';
function FreeImage_FIFSupportsICCProfiles(fif: FREE_IMAGE_FORMAT): Boolean; stdcall; external FIDLL Name '_FreeImage_FIFSupportsICCProfiles@4';
function FreeImage_FIFSupportsExportType(fif: FREE_IMAGE_FORMAT; image_type: FREE_IMAGE_TYPE): Boolean; stdcall; external FIDLL name '_FreeImage_FIFSupportsExportType@8';

// --------------------------------------------------------------------------
// Multipaging interface ----------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_OpenMultiBitmap(fif: FREE_IMAGE_FORMAT; filename: PChar; create_new, read_only, keep_cache_in_memory: Boolean; flags: integer = 0): PFIMULTIBITMAP; stdcall; external FIDLL Name '_FreeImage_OpenMultiBitmap@24';
function FreeImage_CloseMultiBitmap(bitmap: PFIMULTIBITMAP; flags: Integer = 0): Boolean; stdcall; external FIDLL Name '_FreeImage_CloseMultiBitmap@8';
function FreeImage_GetPageCount(bitmap: PFIMULTIBITMAP): Integer; stdcall; external FIDLL Name '_FreeImage_GetPageCount@4';
procedure FreeImage_AppendPage(bitmap: PFIMULTIBITMAP; data: PFIBITMAP); stdcall; external FIDLL Name '_FreeImage_AppendPage@8';
procedure FreeImage_InsertPage(bitmap: PFIMULTIBITMAP; page: Integer; data: PFIBITMAP); stdcall; external FIDLL Name '_FreeImage_InsertPage@12';
procedure FreeImage_DeletePage(bitmap: PFIMULTIBITMAP; page: Integer); stdcall; external FIDLL Name '_FreeImage_DeletePage@8';
function FreeImage_LockPage(bitmap: PFIMULTIBITMAP; page: Integer): PFIBITMAP; stdcall; external FIDLL Name '_FreeImage_LockPage@8';
procedure FreeImage_UnlockPage(bitmap: PFIMULTIBITMAP; page: PFIBITMAP; changed: boolean); stdcall; external FIDLL Name '_FreeImage_UnlockPage@12';
function FreeImage_MovePage(bitmap: PFIMULTIBITMAP; target, source: Integer): Boolean; stdcall; external FIDLL Name '_FreeImage_MovePage@12';
function FreeImage_GetLockedPageNumbers(bitmap: PFIMULTIBITMAP; var pages: Integer; var count : integer): Boolean; stdcall; external FIDLL Name '_FreeImage_GetLockedPageNumbers@12';

// --------------------------------------------------------------------------
// Filetype request routines ------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_GetFileType(const filename: PChar; size: Integer): FREE_IMAGE_FORMAT; stdcall; external FIDLL name '_FreeImage_GetFileType@8';
function FreeImage_GetFileTypeU(const filename: PWideChar; size: Integer): FREE_IMAGE_FORMAT; stdcall; external FIDLL name '_FreeImage_GetFileTypeU@8';
function FreeImage_GetFileTypeFromHandle(io: PFreeImageIO; handle: FI_Handle; size: Integer = 0): FREE_IMAGE_FORMAT; stdcall; external FIDLL name '_FreeImage_GetFileTypeFromHandle@12';
function FreeImage_GetFileTypeFromMemory(stream: PFIMEMORY; size: Integer = 0): FREE_IMAGE_FORMAT; stdcall; external FIDLL name '_FreeImage_GetFileTypeFromMemory@8'; 

// --------------------------------------------------------------------------
// ImageType request routine ------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_GetImageType(dib: PFIBITMAP): FREE_IMAGE_TYPE; stdcall; external FIDLL name '_FreeImage_GetImageType@4';

// --------------------------------------------------------------------------
// FreeImage helper routines ------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_IsLittleEndian: Boolean; stdcall; external FIDLL name '_FreeImage_IsLittleEndian@0';
function FreeImage_LookupX11Color(const szColor: PChar; var nRed, nGreen, nBlue: PByte): Boolean; stdcall; external FIDLL name '_FreeImage_LookupX11Color@16';
function FreeImage_LookupSVGColor(const szColor: PChar; var nRed, nGreen, nBlue: PByte): Boolean; stdcall; external FIDLL name '_FreeImage_LookupSVGColor@16';

// --------------------------------------------------------------------------
// Pixels access routines ---------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_GetBits(dib: PFIBITMAP): PByte; stdcall; external FIDLL name '_FreeImage_GetBits@4';
function FreeImage_GetScanLine(dib: PFIBITMAP; scanline: Integer): PByte; stdcall; external FIDLL name '_FreeImage_GetScanLine@8';

function FreeImage_GetPixelIndex(dib: PFIBITMAP; X, Y: Longint; Value: PByte): Boolean; stdcall; external FIDLL name '_FreeImage_GetPixelIndex@16';
function FreeImage_GetPixelColor(dib: PFIBITMAP; X, Y: Longint; Value: PRGBQuad): Boolean; stdcall; external FIDLL name '_FreeImage_GetPixelColor@16';
function FreeImage_SetPixelIndex(dib: PFIBITMAP; X, Y: Longint; Value: PByte): Boolean; stdcall; external FIDLL name '_FreeImage_SetPixelIndex@16';
function FreeImage_SetPixelColor(dib: PFIBITMAP; X, Y: Longint; Value: PRGBQuad): Boolean; stdcall; external FIDLL name '_FreeImage_SetPixelColor@16';

// --------------------------------------------------------------------------
// DIB info routines --------------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_GetColorsUsed(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetColorsUsed@4';
function FreeImage_GetBPP(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetBPP@4';
function FreeImage_GetWidth(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetWidth@4';
function FreeImage_GetHeight(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetHeight@4';
function FreeImage_GetLine(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetLine@4';
function FreeImage_GetPitch(dib : PFIBITMAP) : Cardinal; stdcall; external FIDLL name '_FreeImage_GetPitch@4';
function FreeImage_GetDIBSize(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetDIBSize@4';
function FreeImage_GetPalette(dib: PFIBITMAP): PRGBQUAD; stdcall; external FIDLL name '_FreeImage_GetPalette@4';

function FreeImage_GetDotsPerMeterX(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetDotsPerMeterX@4';
function FreeImage_GetDotsPerMeterY(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetDotsPerMeterY@4';
procedure FreeImage_SetDotsPerMeterX(dib: PFIBITMAP; res: Cardinal); stdcall; external FIDLL name '_FreeImage_SetDotsPerMeterX@8';
procedure FreeImage_SetDotsPerMeterY(dib: PFIBITMAP; res: Cardinal); stdcall; external FIDLL name '_FreeImage_SetDotsPerMeterY@8';

function FreeImage_GetInfoHeader(dib: PFIBITMAP): PBITMAPINFOHEADER; stdcall; external FIDLL name '_FreeImage_GetInfoHeader@4';
function FreeImage_GetInfo(var dib: FIBITMAP): PBITMAPINFO; stdcall; external FIDLL name '_FreeImage_GetInfo@4';
function FreeImage_GetColorType(dib: PFIBITMAP): FREE_IMAGE_COLOR_TYPE; stdcall; external FIDLL name '_FreeImage_GetColorType@4';

function FreeImage_GetRedMask(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetRedMask@4';
function FreeImage_GetGreenMask(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetGreenMask@4';
function FreeImage_GetBlueMask(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetBlueMask@4';

function FreeImage_GetTransparencyCount(dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetTransparencyCount@4';
function FreeImage_GetTransparencyTable(dib: PFIBITMAP): PByte; stdcall; external FIDLL name '_FreeImage_GetTransparencyTable@4';
procedure FreeImage_SetTransparent(dib: PFIBITMAP; enabled: boolean); stdcall; external FIDLL name '_FreeImage_SetTransparent@8';
procedure FreeImage_SetTransparencyTable(dib: PFIBITMAP; table: PByte; count: integer); stdcall; external FIDLL name '_FreeImage_SetTransparencyTable@12';
function FreeImage_IsTransparent(dib: PFIBITMAP): boolean; stdcall; external FIDLL name '_FreeImage_IsTransparent@4';

function FreeImage_HasBackgroundColor(dib: PFIBITMAP): Boolean; stdcall; external FIDLL name '_FreeImage_HasBackgroundColor@4';
function FreeImage_GetBackgroundColor(dib: PFIBITMAP; var bkcolor: PRGBQUAD): Boolean; stdcall; external FIDLL name '_FreeImage_GetBackgroundColor@8';
function FreeImage_SetBackgroundColor(dib: PFIBITMAP; bkcolor: PRGBQUAD): Boolean; stdcall; external FIDLL name '_FreeImage_SetBackgroundColor@8';

// --------------------------------------------------------------------------
// ICC profile routines -----------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_GetICCProfile(var dib: FIBITMAP): PFIICCPROFILE; stdcall; external FIDLL name '_FreeImage_GetICCProfile@4';
function FreeImage_CreateICCProfile(var dib: FIBITMAP; data: Pointer; size: Longint): PFIICCPROFILE; stdcall; external FIDLL name 'FreeImage_CreateICCProfile@12';
procedure FreeImage_DestroyICCProfile(var dib : FIBITMAP); stdcall; external FIDLL name 'FreeImage_DestroyICCProfile@4';

// --------------------------------------------------------------------------
// Line conversion routines -------------------------------------------------
// --------------------------------------------------------------------------

procedure FreeImage_ConvertLine1To4(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine1To4@12';
procedure FreeImage_ConvertLine8To4(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQuad);  stdcall; external FIDLL name '_FreeImage_ConvertLine8To4@16';
procedure FreeImage_ConvertLine16To4_555(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16To4_555@12';
procedure FreeImage_ConvertLine16To4_565(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16To4_565@12';
procedure FreeImage_ConvertLine24To4(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine24To4@12';
procedure FreeImage_ConvertLine32To4(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine32To4@12';

procedure FreeImage_ConvertLine1To8(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine1To8@12';
procedure FreeImage_ConvertLine4To8(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine4To8@12';
procedure FreeImage_ConvertLine16To8_555(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16To8_555@12';
procedure FreeImage_ConvertLine16To8_565(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16To8_565@12';
procedure FreeImage_ConvertLine24To8(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine24To8@12';
procedure FreeImage_ConvertLine32To8(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine32To8@12';

procedure FreeImage_ConvertLine1To16_555(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine1To16_555@16';
procedure FreeImage_ConvertLine4To16_555(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine4To16_555@16';
procedure FreeImage_ConvertLine8To16_555(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine8To16_555@16';
procedure FreeImage_ConvertLine16_565_To16_555(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16_565_To16_555@12';
procedure FreeImage_ConvertLine24To16_555(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine24To16_555@12';
procedure FreeImage_ConvertLine32To16_555(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine32To16_555@12';

procedure FreeImage_ConvertLine1To16_565(target, source : PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine1To16_565@16';
procedure FreeImage_ConvertLine4To16_565(target, source : PBYTE; width_in_pixels : Integer; palette : PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine4To16_565@16';
procedure FreeImage_ConvertLine8To16_565(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine8To16_565@16';
procedure FreeImage_ConvertLine16_555_To16_565(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16_555_To16_565@12';
procedure FreeImage_ConvertLine24To16_565(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine24To16_565@12';
procedure FreeImage_ConvertLine32To16_565(target, source : PBYTE; width_in_pixels : Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine32To16_565@12';

procedure FreeImage_ConvertLine1To24(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine1To24@16';
procedure FreeImage_ConvertLine4To24(target, source : PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine4To24@16';
procedure FreeImage_ConvertLine8To24(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine8To24@16';
procedure FreeImage_ConvertLine16To24_555(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16To24_555@12';
procedure FreeImage_ConvertLine16To24_565(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16To24_565@12';
procedure FreeImage_ConvertLine32To24(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine32To24@12';

procedure FreeImage_ConvertLine1To32(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine1To32@16';
procedure FreeImage_ConvertLine4To32(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine4To32@16';
procedure FreeImage_ConvertLine8To32(target, source: PBYTE; width_in_pixels: Integer; palette: PRGBQUAD); stdcall; external FIDLL name '_FreeImage_ConvertLine8To32@16';
procedure FreeImage_ConvertLine16To32_555(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16To32_555@12';
procedure FreeImage_ConvertLine16To32_565(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine16To32_565@12';
procedure FreeImage_ConvertLine24To32(target, source: PBYTE; width_in_pixels: Integer); stdcall; external FIDLL name '_FreeImage_ConvertLine24To32@12';

// --------------------------------------------------------------------------
// Smart conversion routines ------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_ConvertTo4Bits(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertTo4Bits@4';
function FreeImage_ConvertTo8Bits(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertTo8Bits@4';
function FreeImage_ConvertToGreyscale(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertToGreyscale@4';
function FreeImage_ConvertTo16Bits555(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertTo16Bits555@4';
function FreeImage_ConvertTo16Bits565(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertTo16Bits565@4';
function FreeImage_ConvertTo24Bits(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertTo24Bits@4';
function FreeImage_ConvertTo32Bits(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertTo32Bits@4';
function FreeImage_ColorQuantize(dib: PFIBITMAP; quantize: FREE_IMAGE_QUANTIZE): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ColorQuantize@8';
function FreeImage_ColorQuantizeEx(dib: PFIBITMAP; quantize: FREE_IMAGE_QUANTIZE = FIQ_WUQUANT; PaletteSize: Integer = 256; ReserveSize: Integer = 0; ReservePalette: PRGBQuad = nil): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ColorQuantizeEx@20';
function FreeImage_Threshold(dib: PFIBITMAP; T: Byte): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_Threshold@8';
function FreeImage_Dither(dib: PFIBITMAP; algorithm: FREE_IMAGE_DITHER): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_Dither@8';

function FreeImage_ConvertFromRawBits(bits: PBYTE; width, height, pitch: Integer; bpp, red_mask, green_mask, blue_mask: LongWord; topdown: Boolean): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertFromRawBits@36';
procedure FreeImage_ConvertToRawBits(bits: PBYTE; dib: PFIBITMAP; pitch: Integer; bpp, red_mask, green_mask, blue_mask: LongWord; topdown: Boolean); stdcall; external FIDLL name '_FreeImage_ConvertToRawBits@32';

function FreeImage_ConvertToRGBF(dib: PFIBITMAP): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertToRGBF@4';

function FreeImage_ConvertToStandardType(src: PFIBITMAP; scale_linear: Boolean = True): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertToStandardType@8';
function FreeImage_ConvertToType(src: PFIBITMAP; dst_type: FREE_IMAGE_TYPE; scale_linear: Boolean = True): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ConvertToType@12';

// tone mapping operators
function FreeImage_ToneMapping(dib: PFIBITMAP; tmo: FREE_IMAGE_TMO; first_param: Double = 0; second_param: Double = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_ToneMapping@24';
function FreeImage_TmoDrago03(src: PFIBITMAP; gamma: Double = 2.2; exposure: Double = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_TmoDrago03@20';
function FreeImage_TmoReinhard05(src: PFIBITMAP; intensity: Double = 0; contrast: Double = 0): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_TmoReinhard05@20';

// --------------------------------------------------------------------------
// ZLib interface -----------------------------------------------------------
// --------------------------------------------------------------------------

function FreeImage_ZLibCompress(target: PBYTE; target_size: DWORD; source: PBYTE; source_size: DWORD): DWORD; stdcall; external FIDLL name '_FreeImage_ZLibCompress@16';
function FreeImage_ZLibUncompress(target: PBYTE; target_size: DWORD; source: PBYTE; source_size: DWORD): DWORD; stdcall; external FIDLL name '_FreeImage_ZLibUncompress@16';

function FreeImage_ZLibGZip(target: PBYTE; target_size: DWORD; source: PBYTE; source_size: DWORD): DWORD; stdcall; external FIDLL name '_FreeImage_ZLibGZip@16';
function FreeImage_ZLibGUnzip(target: PBYTE; target_size: DWORD; source: PBYTE; source_size: DWORD): DWORD; stdcall; external FIDLL name '_FreeImage_ZLibGUnzip@16';
function FreeImage_ZLibCRC32(crc: DWORD; source: PByte; source_size: DWORD): DWORD; stdcall; external FIDLL name '_FreeImage_ZLibCRC32@12';

// --------------------------------------------------------------------------
// Metadata routines --------------------------------------------------------
// --------------------------------------------------------------------------

// tag creation / destruction
function FreeImage_CreateTag: PFITAG; stdcall; external FIDLL name '_FreeImage_CreateTag@0';
procedure FreeImage_DeleteTag(tag: PFITAG); stdcall; external FIDLL name '_FreeImage_DeleteTag@4';
function FreeImage_CloneTag(tag: PFITAG): PFITAG; stdcall; external FIDLL name '_FreeImage_CloneTag@4';

// tag getters and setters
function FreeImage_GetTagKey(tag: PFITAG): PChar; stdcall; external FIDLL name '_FreeImage_GetTagKey@4';
function FreeImage_GetTagDescription(tag: PFITAG): PChar; stdcall; external FIDLL name '_FreeImage_GetTagDescription@4';
function FreeImage_GetTagID(tag: PFITAG): Word; stdcall; external FIDLL name '_FreeImage_GetTagID@4';
function FreeImage_GetTagType(tag: PFITAG): FREE_IMAGE_MDTYPE; stdcall; external FIDLL name '_FreeImage_GetTagType@4';
function FreeImage_GetTagCount(tag: PFITAG): DWORD; stdcall; external FIDLL name '_FreeImage_GetTagCount@4';
function FreeImage_GetTagLength(tag: PFITAG): DWORD; stdcall; external FIDLL name '_FreeImage_GetTagLength@4';
function FreeImage_GetTagValue(tag: PFITAG): Pointer; stdcall; external FIDLL name '_FreeImage_GetTagValue@4';

function FreeImage_SetTagKey(tag: PFITAG; const key: PChar): Boolean; stdcall; external FIDLL name '_FreeImage_SetTagKey@8';
function FreeImage_SetTagDescription(tag: PFITAG; const description: PChar): Boolean; stdcall; external FIDLL name '_FreeImage_SetTagDescription@8';
function FreeImage_SetTagID(tag: PFITAG; id: Word): Boolean; stdcall; external FIDLL name '_FreeImage_SetTagID@8';
function FreeImage_SetTagType(tag: PFITAG; atype: FREE_IMAGE_MDTYPE): Boolean; stdcall; external FIDLL name '_FreeImage_SetTagType@8';
function FreeImage_SetTagCount(tag: PFITAG; count: DWORD): Boolean; stdcall; external FIDLL name '_FreeImage_SetTagCount@8';
function FreeImage_SetTagLength(tag: PFITAG; length: DWORD): Boolean; stdcall; external FIDLL name '_FreeImage_SetTagLength@8';
function FreeImage_SetTagValue(tag: PFITAG; const value: Pointer): Boolean; stdcall; external FIDLL name '_FreeImage_SetTagValue@8';

// iterator
function FreeImage_FindFirstMetadata(model: FREE_IMAGE_MDMODEL; dib: PFIBITMAP; var tag: PFITAG): PFIMETADATA; stdcall; external FIDLL name '_FreeImage_FindFirstMetadata@12';
function FreeImage_FindNextMetadata(mdhandle: PFIMETADATA; var tag: PFITAG): Boolean; stdcall; external FIDLL name '_FreeImage_FindNextMetadata@8';
procedure FreeImage_FindCloseMetadata(mdhandle: PFIMETADATA); stdcall; external FIDLL name '_FreeImage_FindCloseMetadata@4';

// metadata setter and getter
function FreeImage_SetMetadata(model: FREE_IMAGE_MDMODEL; dib: PFIBITMAP; const key: PChar; tag: PFITAG): Boolean; stdcall; external FIDLL name '_FreeImage_SetMetadata@16';
function FreeImage_GetMetaData(model: FREE_IMAGE_MDMODEL; dib: PFIBITMAP; const key: PChar; var tag: PFITAG): Boolean; stdcall; external FIDLL name '_FreeImage_GetMetadata@16';

// helpers
function FreeImage_GetMetadataCount(model: FREE_IMAGE_MDMODEL; dib: PFIBITMAP): Cardinal; stdcall; external FIDLL name '_FreeImage_GetMetadataCount@8';

// tag to C string conversion
function FreeImage_TagToString(model: FREE_IMAGE_MDMODEL; tag: PFITAG; Make: PChar = nil): PChar; stdcall; external FIDLL name '_FreeImage_TagToString@12';

// --------------------------------------------------------------------------
// Image manipulation toolkit -----------------------------------------------
// --------------------------------------------------------------------------

// rotation and flipping
function FreeImage_RotateClassic(dib: PFIBITMAP; angle: Double): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_RotateClassic@12';
function FreeImage_RotateEx(dib: PFIBITMAP; angle, x_shift, y_shift, x_origin, y_origin: Double; use_mask: Boolean): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_RotateEx@48';
function FreeImage_FlipHorizontal(dib: PFIBITMAP): Boolean; stdcall; external FIDLL name '_FreeImage_FlipHorizontal@4';
function FreeImage_FlipVertical(dib: PFIBITMAP): Boolean; stdcall; external FIDLL name '_FreeImage_FlipVertical@4';
function FreeImage_JPEGTransform(const src_file: PChar; const dst_file: PChar; operation: FREE_IMAGE_JPEG_OPERATION; perfect: Boolean = False): Boolean; stdcall; external FIDLL name '_FreeImage_JPEGTransform@16';

// upsampling / downsampling
function FreeImage_Rescale(dib: PFIBITMAP; dst_width, dst_height: Integer; filter: FREE_IMAGE_FILTER): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_Rescale@16';
function FreeImage_MakeThumbnail(dib: PFIBITMAP; max_pixel_size: Integer; convert:boolean = TRUE): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_MakeThumbnail@12'; 

// color manipulation routines (point operations)
function FreeImage_AdjustCurve(dib: PFIBITMAP; LUT: PBYTE; channel: FREE_IMAGE_COLOR_CHANNEL): Boolean; stdcall; external FIDLL name '_FreeImage_AdjustCurve@12';
function FreeImage_AdjustGamma(dib: PFIBITMAP; gamma: Double): Boolean; stdcall; external FIDLL name '_FreeImage_AdjustGamma@12';
function FreeImage_AdjustBrightness(dib: PFIBITMAP; percentage: Double): Boolean; stdcall; external FIDLL name '_FreeImage_AdjustBrightness@12';
function FreeImage_AdjustContrast(dib: PFIBITMAP; percentage: Double): Boolean; stdcall; external FIDLL name '_FreeImage_AdjustContrast@12';
function FreeImage_Invert(dib: PFIBITMAP): Boolean; stdcall; external FIDLL name '_FreeImage_Invert@4';
function FreeImage_GetHistogram(dib: PFIBITMAP; histo: PDWORD; channel: FREE_IMAGE_COLOR_CHANNEL = FICC_BLACK): Boolean; stdcall; external FIDLL name '_FreeImage_GetHistogram@12';

// channel processing routines
function FreeImage_GetChannel(dib: PFIBITMAP; channel: FREE_IMAGE_COLOR_CHANNEL): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_GetChannel@8';
function FreeImage_SetChannel(dib, dib8: PFIBITMAP; channel: FREE_IMAGE_COLOR_CHANNEL): Boolean; stdcall; external FIDLL name '_FreeImage_SetChannel@12';
function FreeImage_GetComplexChannel(src: PFIBITMAP; channel: FREE_IMAGE_COLOR_CHANNEL): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_GetComplexChannel@8';
function FreeImage_SetComplexChannel(src: PFIBITMAP; channel: FREE_IMAGE_COLOR_CHANNEL): Boolean; stdcall; external FIDLL name '_FreeImage_SetComplexChannel@12';

// copy / paste / composite routines

function FreeImage_Copy(dib: PFIBITMAP; left, top, right, bottom: Integer): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_Copy@20';
function FreeImage_Paste(dst, src: PFIBITMAP; left, top, alpha: Integer): Boolean; stdcall; external FIDLL name '_FreeImage_Paste@20';
function FreeImage_Composite(fg: PFIBITMAP; useFileBkg: Boolean = False; appBkColor: PRGBQUAD = nil; bg: PFIBITMAP = nil): PFIBITMAP; stdcall; external FIDLL name '_FreeImage_Composite@16';
  
{$MINENUMSIZE 1}
implementation

end.
